#include "main.h"
#include "uart.h"
#include "vop.h"
#include "hdmi.h"
#include "maliutgard.h"
#include "grf.h"
#include "cru.h"
#include "printf.h"

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


u8 *_mem = (u8 *)&_end;
u32 _arch_cntfreq,_usec_factor,_msec_factor;
u64 _start_tick;


static inline u32 arch_timer_get_cntfrq(void){
	u32 val;
	asm volatile("mrs %0,   cntfrq_el0" : "=r" (val));
	return val;
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
    printf("vop init end\n");


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
	HDMI_REGW(HDMI_FC_INVBLANK) =0x2a;
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

	printf("end\n");
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