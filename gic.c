#include "gic.h"

static LPIRQFUNC irq_map[128]={0};
extern u32 _lino;

static void gic_poke_irq(u32 d,u32 offset){
	u32 val = REGW(GIC_BASE+offset + ((d / 32) * 4));
	REGW(GIC_BASE+offset + ((d / 32) * 4)) = val | (1 << (d % 32));
}

static void gic_group_irq(u32 d,u32 flag){
	u32 off = d >> 5;
	u32 mask = 1 << (d - (off << 5));
	u32 val = REGW(GIC_BASE+GIC_DIST_IGROUP + off*4);
	if(flag)
		val |= mask;
	else
		val &= ~mask;
	REGW(GIC_BASE+GIC_DIST_IGROUP + off*4) = mask;
}

int gic_fiq_handler(u64 *regs){
	u32 irqstat,irqnr;

	printf("gic_fiq_handler\n");
/*	do{
		irqstat =__le32_to_cpu( REGW(GIC_BASE+GIC_CPU_INTACK));

		irqnr = irqstat & GICC_IAR_INT_ID_MASK;
		REGW(GIC_BASE + GIC_CPU_EOI) = irqstat;
		if(irqnr < 16)
			REGW(GIC_BASE+ GIC_CPU_DEACTIVATE) = irqstat;
		if(irq_map[irqnr])
			irq_map[irqnr]();
		printf("FIQ %d %x\n",irqnr,irqstat);
		break;
	}while(1);*/
	return 0;
}

int gic_irq_handler(u64 *regs){
	u32 irqstat,irqnr;

	_lino++;
	printf("gic_irq_handler\n");
	irqstat = REGW(GIC_BASE+GIC_CPU_INTACK);
	irqnr = irqstat & GICC_IAR_INT_ID_MASK;
	REGW(GIC_BASE + GIC_CPU_EOI) = irqstat;

	if(irqnr > 15 && irqnr < 1020){
		printf("IRQ %d %x\n",irqnr,irqstat);
		if(irq_map[irqnr])
			irq_map[irqnr]();
	}
	else {
		REGW(GIC_BASE + GIC_CPU_DEACTIVATE) = irqstat;
	}
	return 0;
}

int gic_init(){
	u32 gic_irqs,val,i;

	printf("GIC: %x %x\n",REGW(GIC_BASE+GIC_DIST_CTR),REGW(GIC_BASE+GIC_CPU_CTRL));

	gic_irqs = (REGW(GIC_BASE+GIC_DIST_CTR) & 0x1f) * 32;

	//initialize dist interface
	REGW(GIC_BASE+GIC_DIST_CTRL) = GICD_DISABLE;

	for (i = 32; i < gic_irqs; i += 4)
		REGW(GIC_BASE+ GIC_DIST_TARGET + i * 4 / 4) = 0x01010101;

	for (i = 32; i < gic_irqs; i += 16)
		REGW(GIC_BASE+ GIC_DIST_CONFIG + i / 4) = GICD_INT_ACTLOW_LVLTRIG;

	for (i = 32; i < gic_irqs; i += 4)
		REGW(GIC_BASE+ GIC_DIST_PRI + i) = GICD_INT_DEF_PRI_X4;

	for (i = 32; i < gic_irqs; i += 32) {
		REGW(GIC_BASE+ GIC_DIST_ACTIVE_CLEAR + i / 8) = GICD_INT_EN_CLR_X32;
		REGW(GIC_BASE+ GIC_DIST_ENABLE_CLEAR + i / 8) = GICD_INT_EN_CLR_X32;
	}
	REGW(GIC_BASE+GIC_DIST_CTRL) = GICD_ENABLE;

	val = REGW(GIC_BASE+GIC_CPU_CTRL);
	REGW(GIC_BASE+GIC_CPU_CTRL) = val & ~(GICC_ENABLE|GICC_ENABLENS);

	//intialize cpu interface
	REGW(GIC_BASE+ GIC_DIST_ACTIVE_CLEAR) = GICD_INT_EN_CLR_X32;
	REGW(GIC_BASE+ GIC_DIST_ENABLE_CLEAR) = GICD_INT_EN_CLR_PPI;
	REGW(GIC_BASE+ GIC_DIST_ENABLE_SET) = GICD_INT_EN_SET_SGI;
	for (i = 0; i < 32; i += 4)
		REGW(GIC_BASE+ GIC_DIST_PRI + i * 4 / 4) = GICD_INT_DEF_PRI_X4;

	REGW(GIC_BASE+GIC_CPU_PRIMASK) = GICC_INT_PRI_THRESHOLD;
	val = REGW(GIC_BASE+GIC_CPU_CTRL) & ~(GICC_ENABLE|GICC_ENABLENS);
	REGW(GIC_BASE+GIC_CPU_CTRL) = val | GICC_ENABLE;

	return 0;
}

int gic_configure_irq(unsigned int irq, unsigned int type){
	u32 confmask = 0x2 << ((irq % 16) * 2);
	u32 confoff = (irq / 16) * 4;
	u32 val, oldval;
	int ret = 0;

	if (irq < 16)
		return -1;
	if (irq >= 32 && type != IRQ_TYPE_LEVEL_HIGH && type != IRQ_TYPE_EDGE_RISING)
		return -2;
	val = oldval = REGW(GIC_BASE+GIC_DIST_CONFIG + confoff);
	if (type & IRQ_TYPE_LEVEL_MASK)
		val &= ~confmask;
	else if (type & IRQ_TYPE_EDGE_BOTH)
		val |= confmask;
	REGW(GIC_BASE+GIC_DIST_CONFIG + confoff) = val;
	if (REGW(GIC_BASE+GIC_DIST_CONFIG + confoff) != val && val != oldval)
		ret = -1;
	return ret;
}

int gic_register_irq_routine(u32 irq,LPIRQFUNC p,u32 type){
	irq_map[irq] = p;
	int i = gic_configure_irq(irq,type);
	REGW(GIC_BASE+GIC_DIST_ENABLE_SET + ((irq / 32) * 4)) = 1 << (irq % 32);
	printf("GIC %d=>%d\n",irq,i);
	return 0;
}