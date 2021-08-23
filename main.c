#include "main.h"
#include "uart.h"
#include "vop.h"
#include "hdmi.h"
#include "maliutgard.h"
#include "grf.h"
#include "cru.h"
#include "printf.h"
#include "sdmmc.h"
#include "gic.h"

#define  GRF_GPIO4B_IOMUX			(*(volatile unsigned int *)(GRF_BASE + 0xe024))

#define  GPIO0_BASE                	0xff210000
#define  GPIO1_BASE                	0xff220000
#define  GPIO2_BASE                	0xff230000
#define  GPIO3_BASE                	0xff240000

#define GPIO0                   ((p_gpio_reg)GPIO0_BASE)
#define GPIO1                   ((p_gpio_reg)GPIO1_BASE)
#define GPIO2                   ((p_gpio_reg)GPIO2_BASE)
#define GPIO3                   ((p_gpio_reg)GPIO3_BASE)
#define GPIO4                   ((p_gpio_reg)GPIO4_BASE)

#define HZ	1000

extern volatile u8 _end;

u8 *_mem = (u8 *)&_end;
u32 _arch_cntfreq,_usec_factor,_msec_factor;
u64 _start_tick;
u32 _lino = 0;

void memset(void *dst,u32 val,u32 size);

void NOINLINE mdelay(u32 msec){
	udelay(msec*1000);
}

static INLINE u32 arch_timer_get_cntfrq(void){
	u32 val;
	asm volatile("mrs %0,   cntfrq_el0" : "=r" (val));
	return val;
}

static NOINLINE u32 arch_get_el(void){
	u32 val;
	asm volatile("mrs %0,CurrentEL" : "=r" (val));
	return val;
}

static inline void arch_local_irq_enable(void){
	asm volatile("msr daifclr, #15" : :	: "memory");
}

static inline void arch_local_irq_disable(void){
	asm volatile("msr daifset, #15" : : : "memory");
}

void NOINLINE syscall(u32 val){
	u64 ret;

	asm volatile("str	lr, [sp, #-16]!\n"
		"hvc	#0\n"
		"ldr	lr, [sp], #16\n"
	: : : "memory");
//	return 0;
}

void prepare_frame(){
	u32 *p,color;

	p = (u32 *)0x4000000;
	memset(p,0,1280*1024*4);

	for(int y=200;y<400;y++){
		u32 *pp = &p[y*1280];
		for(int x = 200;x<700;x++)
			pp[x] = 0xFF8040;
	 }
	__flush_dcache_area(p,1280*4*1024);
}

int lino(){
	VOP_REG_SET(VOP_INTR_CLEAR0,0x1000,0x0,0x1000);
	VOP_REG_SET(VOP_SYS_CTRL1,0x1,0x1c,0x0);
	VOP_REG_SET(VOP_SYS_CTRL1,0x1,0x1b,0x0);

	//VOP_REG_SET(VOP_DSP_BG,0xffffffff,0x0,0x801080);
	VOP_REGW(VOP_WIN0_YRGB_MST)=(u32)0x4000000;

	VOP_REG_SET(VOP_WIN0_CTRL0,0x1,0x15,0x0);
	VOP_REG_SET(VOP_WIN0_CTRL0,0x1,0x16,0x0);
	//VOP_REG_SET(VOP_WIN0_CTRL0,0x7,0x1,0x0);//format

	VOP_REG_SET(VOP_WIN0_VIR,0x3fff,0x0,0x500);//pitch

	//VOP_REG_SET(0x110,0xffffffff,0,0x0);
	VOP_REG_SET(VOP_WIN0_CTRL0,0x7,0x4,0x0);
	VOP_REG_SET(VOP_WIN0_CTRL0,0x7,0x5,0x4);
	VOP_REG_SET(VOP_WIN0_SCL_FACTOR_YRGB,0xffff,0x0,0x1000);
	VOP_REG_SET(VOP_WIN0_SCL_FACTOR_YRGB,0xffff,0x10,0x1000);
	VOP_REG_SET(VOP_WIN0_CTRL1,0x1,0x4,0x0);
	VOP_REG_SET(VOP_WIN0_CTRL1,0x1,0x5,0x0);
	VOP_REG_SET(VOP_WIN0_CTRL1,0x3,0x10,0x0);
	VOP_REG_SET(VOP_WIN0_CTRL1,0x3,0x12,0x0);
	VOP_REG_SET(VOP_WIN0_CTRL1,0x3,0x14,0x0);
	VOP_REG_SET(VOP_WIN0_CTRL1,0x1,0x17,0x0);
	VOP_REG_SET(VOP_WIN0_CTRL1,0x1,0x16,0x1);

	//VOP_REG_SET(VOP_WIN0_ACT_INFO,0x1fff1fff,0x0,0x3ff04ff);
	//VOP_REG_SET(VOP_WIN0_DSP_INFO,0xfff0fff,0x0,0x3ff04ff);
	VOP_WIN_SIZE(0,1280,1024,0);

	VOP_REG_SET(VOP_WIN0_DSP_ST,0x1fff1fff,0x0,0x290168);
	//VOP_REG_SET(VOP_WIN0_DSP_ST,0x1fff1fff,0x0,0);

	VOP_REG_SET(VOP_WIN0_CTRL0,0x1,0xc,0x0);
	VOP_REG_SET(VOP_WIN0_SRC_ALPHA_CTRL,0xffff,0x0,0x0);
	VOP_REG_SET(VOP_WIN0_SRC_ALPHA_CTRL,0xff,0x10,0xff);
	VOP_REG_SET(VOP_WIN0_CTRL0,0x3,0xa,0x0);

	VOP_REG_SET(VOP_SDR2HDR_CTRL,0x1,0x9,0x0);
	VOP_REG_SET(VOP_SDR2HDR_CTRL,0x1,0x5,0x0);
	VOP_REG_SET(VOP_SDR2HDR_CTRL,0x1,0x8,0x0);

	VOP_REG_SET(VOP_DSP_CTRL0,0x1f,0xc,0x0);
	VOP_REG_SET(VOP_DSP_CTRL0,0xf,0x0,0xf);//outmode
	VOP_REG_SET(VOP_DSP_CTRL1,0x1,0x2,0x0);//dither
	VOP_REG_SET(VOP_DSP_CTRL1,0x1,0x1,0x0);
	VOP_REG_SET(VOP_DSP_CTRL1,0x1,0x4,0x0);

	VOP_REG_SET(VOP_DSP_CTRL0,0x1,0x8,0x0);
	VOP_REG_SET(VOP_SYS_CTRL,0x1,0x10,0x0);//overlay
	VOP_REG_SET(VOP_POST_SCL_CTRL,0x1,0x2,0x0);//dsp_out_yuv

	VOP_REG_SET(VOP_DSP_BG,0xffffffff,0x0,0x0);
	VOP_REG_SET(VOP_BCSH_CTRL,0x1,0x4,0x0);
	VOP_REG_SET(VOP_BCSH_CTRL,0x1,0x0,0x0);
	VOP_REG_SET(VOP_BCSH_CTRL,0x3,0x6,0x1);
	VOP_REG_SET(VOP_BCSH_CTRL,0x3,0x2,0x1);
	VOP_REG_SET(0x640,0x1,0x0,0x0);
	VOP_REG_SET(VOP_DSP_CTRL1,0xff,0x8,1);//dsp_layer_sel

	VOP_REG_SET(0x600,0x1fff1fff,0x0,0x1680668);
	VOP_REG_SET(0x604,0x1fff1fff,0x0,0x290429);
	VOP_REG_SET(0x608,0xffffffff,0x0,0x10001000);
	VOP_REG_SET(VOP_POST_SCL_CTRL,0x3,0x0,0x0);
	VOP_REG_SET(0xa10,0x1,0x0,0x0);
	VOP_REG_SET(VOP_SDR2HDR_CTRL,0x1,0x0,0x0);
	VOP_REG_SET(VOP_SDR2HDR_CTRL,0x1,0x4,0x0);
	VOP_REG_SET(VOP_SDR2HDR_CTRL,0x1,0x1,0x0);
	VOP_REG_SET(VOP_SDR2HDR_CTRL,0x1,0x2,0x0);
	VOP_REG_SET(VOP_SDR2HDR_CTRL,0x1,0x3,0x0);
	VOP_REG_SET(VOP_SDR2HDR_CTRL,0x1,0x5,0x0);
	VOP_REG_SET(VOP_SDR2HDR_CTRL,0x1,0x6,0x0);
	VOP_REG_SET(VOP_SDR2HDR_CTRL,0x1,0x7,0x0);
	VOP_REG_SET(VOP_SDR2HDR_CTRL,0x1,0x1f,0x1);

	VOP_WIN_ENABLE(0,1);

	VOP_CONFIG_DONE();

	return 0;
}

void main(){
	u32 l;

	/*GPIO0->SWPORTA_DDR |=  (0x01 << (1 * 8 + 5));
    GPIO2->SWPORTA_DDR |=  (0x01 << (3 * 8 + 3));

    GPIO0->SWPORTA_DR  &= ~(0x01 << (1 * 8 + 5));
    GPIO2->SWPORTA_DR  &= ~(0x01 << (3 * 8 + 3));

	GPIO2->SWPORTA_DR  |=  (0x01 << (3 * 8 + 3));

	GRF_GPIO4B_IOMUX = (3 << 18) | (3 << 16) | (2 << 2) | (2 << 0);*/

    /*UART2_SFE = 0x01;
    UART2_SRT = 0x03;
    UART2_STET = 0x01;*/

	_arch_cntfreq = arch_timer_get_cntfrq();
	_msec_factor = (_arch_cntfreq / 1000);
	_usec_factor = (_arch_cntfreq / 1000000);
	_start_tick = get_cycles();

	gic_init();

	syscall(1);

	sdmmc_init();

	inno_hdmi_phy_rk3328_init();

	//prod_id0 = hdmi_readb(hdmi, HDMI_PRODUCT_ID0);
	//prod_id1 = hdmi_readb(hdmi, HDMI_PRODUCT_ID1);

	initialize_hdmi_ih_mutes();

	//hdmi_set_cts_n
	HDMI_REG_UPD(HDMI_AUD_CTS3,HDMI_AUD_CTS3_CTS_MANUAL,0);
	HDMI_REG_UPD(HDMI_AUD_CTS3,HDMI_AUD_CTS3_N_SHIFT_MASK,0);

	l = 74250;
	HDMI_REGW(HDMI_AUD_CTS3) = ((l >> 16) & 0xF) | HDMI_AUD_CTS3_CTS_MANUAL;
	HDMI_REGW(HDMI_AUD_CTS2) =  (l >> 8) & 0xff;
	HDMI_REGW(HDMI_AUD_CTS1) = l & 0xff;
	//N=6144
	HDMI_REGW(HDMI_AUD_N3)= 0;
	HDMI_REGW(HDMI_AUD_N2) = 0;
	HDMI_REGW(HDMI_AUD_N1) = 0;

	HDMI_REGW(HDMI_PHY_I2CM_INT_ADDR) = HDMI_PHY_I2CM_INT_ADDR_DONE_POL;
	HDMI_REGW(HDMI_PHY_I2CM_CTLINT_ADDR) =HDMI_PHY_I2CM_CTLINT_ADDR_NAC_POL|HDMI_PHY_I2CM_CTLINT_ADDR_ARBITRATION_POL;
	HDMI_REGW(HDMI_PHY_POL0) = HDMI_PHY_HPD|HDMI_PHY_RX_SENSE;
	HDMI_REGW(HDMI_PHY_MASK0) = (u8)~(HDMI_PHY_HPD | HDMI_PHY_RX_SENSE);
	HDMI_REGW(HDMI_IH_MUTE_PHY_STAT0) = ~(HDMI_IH_PHY_STAT0_HPD | HDMI_IH_PHY_STAT0_RX_SENSE);

	HDMI_REGW(HDMI_IH_MUTE_PHY_STAT0) = 0xc2;
	HDMI_REGW(HDMI_IH_I2CM_STAT0) = 0x1;
	HDMI_REGW(HDMI_IH_MUTE_PHY_STAT0) = 0xff;
	HDMI_REGW(HDMI_PHY_POL0) = 0xf0;

	HDMI_REGW(HDMI_PHY_MASK0) = 0xfd;
	HDMI_REGW(HDMI_IH_PHY_STAT0) = 0x3;
	HDMI_REGW(HDMI_IH_MUTE_PHY_STAT0) = 0xc2;

	dw_hdmi_i2c_init();

	struct edid *p = drm_do_get_edid(_mem);
	if(p != NULL)
		printf("edit %d %d\n",p->width_cm,p->height_cm);
	vop_init();
	inno_hdmi_phy_rk3328_pre_pll_update();

    VOP_REG_SET(VOP_CFG_DONE,0x1,0x0,0x1);

	HDMI_REGW(HDMI_IH_MUTE_FC_STAT2) = HDMI_IH_MUTE_FC_STAT2_OVERFLOW_MASK;

	//hdmi_av_composer
	HDMI_REGW(HDMI_FC_INVIDCONF) = 0xf0;
	HDMI_REGW(HDMI_FC_SCRAMBLER_CTRL) = 0;
	HDMI_REGW(HDMI_FC_INHACTV1) = (0x500 >> 8);
	HDMI_REGW(HDMI_FC_INHACTV0) = (0x500 & 0xFF);
	HDMI_REGW(HDMI_FC_INVACTV1) = (0x400 >> 8);
	HDMI_REGW(HDMI_FC_INVACTV0) = (0x400 & 0xff);
	HDMI_REGW(HDMI_FC_INHBLANK1) = (0x198 >> 8);
	HDMI_REGW(HDMI_FC_INHBLANK0) = (0x198 & 0xFF);
	HDMI_REGW(HDMI_FC_INVBLANK) = 0x2a;
	HDMI_REGW(HDMI_FC_HSYNCINDELAY1) = 0;
	HDMI_REGW(HDMI_FC_HSYNCINDELAY0)= 0x30;
	HDMI_REGW(HDMI_FC_VSYNCINDELAY) = 1;
	HDMI_REGW(HDMI_FC_HSYNCINWIDTH1) = 0;
	HDMI_REGW(HDMI_FC_HSYNCINWIDTH0) =0x70;
	HDMI_REGW(HDMI_FC_VSYNCINWIDTH) = 3;

	inno_hdmi_phy_rk3328_power_on();

	//dw_hdmi_enable_video_path
	HDMI_REGW(HDMI_FC_CTRLDUR) = 12;
	HDMI_REGW(HDMI_FC_EXCTRLDUR) = 32;
	HDMI_REGW(HDMI_FC_EXCTRLSPAC) = 1;
	HDMI_REGW(HDMI_FC_CH0PREAM) = 0xB;
	HDMI_REGW(HDMI_FC_CH1PREAM) = 0x16;
	HDMI_REGW(HDMI_FC_CH2PREAM) = 0x21;
	HDMI_REGW(HDMI_MC_CLKDIS) = 0x7e;
	HDMI_REGW(HDMI_MC_CLKDIS) = 0x7c;
	HDMI_REGW(HDMI_MC_CLKDIS) = 0x7c & ~HDMI_MC_CLKDIS_PREPCLK_DISABLE;
	HDMI_REGW(HDMI_MC_FLOWCTRL) = HDMI_MC_FLOWCTRL_FEED_THROUGH_OFF_CSC_BYPASS;

	//hdmi_video_packetize
	HDMI_REGW(HDMI_VP_PR_CD) = 0x0;
	HDMI_REGW(HDMI_VP_STUFF) = 0x1;
	HDMI_REGW(HDMI_VP_CONF) = 0x24;
	HDMI_REGW(HDMI_VP_STUFF) = 0x21;
	HDMI_REGW(HDMI_VP_REMAP) = 0x0;
	HDMI_REGW(HDMI_VP_CONF) = 0x44;
	HDMI_REGW(HDMI_VP_STUFF) = 0x27;
	HDMI_REGW(HDMI_VP_CONF) = 0x47;

	//hdmi_video_csc
	HDMI_REGW(HDMI_CSC_CFG) = 0x0;
	HDMI_REGW(HDMI_CSC_SCALE) = 0x1;
	HDMI_REGW(0x4103) = 0x0;
	HDMI_REGW(0x4102) = 0x20;
	HDMI_REGW(0x410b) = 0x0;
	HDMI_REGW(0x410a) = 0x0;
	HDMI_REGW(0x4113) = 0x0;
	HDMI_REGW(0x4112) = 0x0;
	HDMI_REGW(0x4105) = 0x0;
	HDMI_REGW(0x4104) = 0x0;
	HDMI_REGW(0x410d) = 0x0;
	HDMI_REGW(0x410c) = 0x20;
	HDMI_REGW(0x4115) = 0x0;
	HDMI_REGW(0x4114) = 0x0;
	HDMI_REGW(0x4107) = 0x0;
	HDMI_REGW(0x4106) = 0x0;
	HDMI_REGW(0x410f) = 0x0;
	HDMI_REGW(HDMI_CSC_COEF_B3_MSB) = 0x0;
	HDMI_REGW(0x4117) = 0x0;
	HDMI_REGW(HDMI_CSC_COEF_C3_MSB) = 0x20;
	HDMI_REGW(0x4109) = 0x0;
	HDMI_REGW(0x4108) = 0x0;
	HDMI_REGW(0x4111) = 0x0;
	HDMI_REGW(0x4110) = 0x0;
	HDMI_REGW(0x4119) = 0x0;
	HDMI_REGW(0x4118) = 0x0;
	HDMI_REGW(HDMI_CSC_SCALE) = 0x1;

	//hdmi_video_sample
	HDMI_REGW(HDMI_TX_INVID0) = 1;
	HDMI_REGW(HDMI_TX_INSTUFFING) = HDMI_TX_INSTUFFING_BDBDATA_STUFFING_ENABLE | HDMI_TX_INSTUFFING_RCRDATA_STUFFING_ENABLE | HDMI_TX_INSTUFFING_GYDATA_STUFFING_ENABLE;
	HDMI_REGW(HDMI_TX_GYDATA0) = 0;
	HDMI_REGW(HDMI_TX_GYDATA1) = 0;
	HDMI_REGW(HDMI_TX_RCRDATA0) = 0;
	HDMI_REGW(HDMI_TX_RCRDATA1) = 0;
	HDMI_REGW(HDMI_TX_BCBDATA0) = 0;
	HDMI_REGW(HDMI_TX_BCBDATA1) = 0;

	//hdmi_tx_hdcp_config
	HDMI_REG_UPD(HDMI_A_VIDPOLCFG,HDMI_A_VIDPOLCFG_VSYNCPOL_MASK|HDMI_A_VIDPOLCFG_HSYNCPOL_MASK|HDMI_A_VIDPOLCFG_DATAENPOL_MASK,0x8|0x2|0x10);
	HDMI_REG_UPD(HDMI_A_HDCPCFG0,HDMI_A_HDCPCFG0_HDMIDVI_MASK,HDMI_A_HDCPCFG0_HDMIDVI_DVI);

	//dw_hdmi_clear_overflow
	HDMI_REGW(HDMI_MC_SWRSTZ) = ~2;
	l = HDMI_REGW(HDMI_FC_INVIDCONF);
	HDMI_REGW(HDMI_FC_INVIDCONF) = l;//0xf0

	//dw_hdmi_update_phy_mask
	HDMI_REGW(HDMI_PHY_MASK0) &= ~HDMI_PHY_RX_SENSE;//0xd

	vop_enable();
	prepare_frame();

	VOP_REG_SET(VOP_INTR_CLEAR0,0x1fe3,0x0,0x1fe0);
	VOP_REG_SET(VOP_INTR_EN0,0x1fe3,0x0,0x1fF0);
	VOP_REG_SET(VOP_INTR_CLEAR0,0x1fe3,0x0,0x1fe0);
	VOP_REG_SET(VOP_WIN0_CTRL0,0x1,0x9,0x0); //axi

	VOP_CONFIG_DONE();
	printf("done %x\n",_lino);
	while(1){
		int i=0;
		l = VOP_REGW(VOP_INTR_STATUS0);
		VOP_REGW(VOP_INTR_CLEAR0) = l;
		if(l)
			printf("irq %x %x\n",l,_lino);
		lino();
	}
}

s64 __div(s64 v,s64 d) {
	s64 res;
	asm volatile("udiv %0, %1, %2\n" : "=r" (res) : "r" (v), "r" (d));
	return res;
}

INLINE u64 get_cycles(void){
	u64 cval;

	isb();
	asm volatile("mrs %0, cntvct_el0" : "=r" (cval));
	return cval;
}

void NOINLINE udelay(u32 usec){
	u64 delay = (usec * _usec_factor);
	u64 start = get_cycles();
	delay += start;
	while (get_cycles() < delay)
		__asm("nop\n");
}

void exc_handler(unsigned long *type){
	_lino++;
}

void NOINLINE memset(void *dst,u32 val,u32 size){
	u32 s;
	u8 *d;

	{
		u64 v = val;
		v = (v<<32) | val;
		for(d = (u8 *)dst,s=size;s > 7;s -= 8){
			*((u64 *)d) = v;
			d +=  8;
		}
	}
	for(;s > 3;s -= 4){
		*((u32 *)d) = val;
		d += 4;
	}
	for(;s > 0;s--)
		*d++ = val;
}