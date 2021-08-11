#include "cru.h"
#include "printf.h"

static CRUCLOCK _clocks[] = {
	{PCLK_HDMI,RK3328_CLKGATE_CON(22),4, GFLAGS,branch_gate},
	{SCLK_HDMI_SFC,RK3328_CLKGATE_CON(5), 4, GFLAGS,branch_gate},

	{SCLK_RTC32K, RK3328_CLKGATE_CON(0),11, GFLAGS,branch_composite,{RK3328_CLKSEL_CON(38), 14, 2, MFLAGS},{0,0, 14, DFLAGS}},
	{PCLK_HDMIPHY, RK3328_CLKGATE_CON(17), 7, GFLAGS,branch_gate},
	{HCLK_HDCP, RK3328_CLKGATE_CON(22), 0, GFLAGS,branch_gate},

	{HCLK_VIO_PRE,-1,0,0,branch_divider,{RK3328_CLKSEL_CON(37)},{0, 8, 5, DFLAGS}},
	{ACLK_VIO_PRE,RK3328_CLKGATE_CON(5), 2, GFLAGS,branch_composite,{RK3328_CLKSEL_CON(37), 6, 2, MFLAGS},{0, 0, 5, DFLAGS}},
	{HCLK_VOP, RK3328_CLKGATE_CON(21), 3, GFLAGS,branch_gate},
	{ACLK_VOP_PRE,RK3328_CLKGATE_CON(5), 5, GFLAGS,branch_composite},
	{DCLK_LCDC_SRC,RK3328_CLKGATE_CON(5), 5, GFLAGS,branch_composite},
};

/*
 *
 * clocks = <&cru PCLK_HDMIPHY>, <&xin24m>, <&cru DCLK_HDMIPHY>;
 *
 * COMPOSITE(ACLK_VOP_PRE, "aclk_vop_pre", mux_4plls_p, 0,
			RK3328_CLKSEL_CON(39), 6, 2, MFLAGS, 0, 5, DFLAGS,
			RK3328_CLKGATE_CON(5), 5, GFLAGS),
	COMPOSITE(DCLK_LCDC_SRC, "dclk_lcdc_src", mux_gpll_cpll_p, 0,
			RK3328_CLKSEL_CON(40), 0, 1, MFLAGS, 8, 8, DFLAGS,
			RK3328_CLKGATE_CON(5), 6, GFLAGS),
	GATE(HCLK_VOP, "hclk_vop", "hclk_vio_pre", 0, RK3328_CLKGATE_CON(21), 3, GFLAGS),
	*
	*
	DIV(DCLK_HDMIPHY, "dclk_hdmiphy", "dclk_lcdc_src", 0,
			RK3328_CLKSEL_CON(40), 3, 3, DFLAGS),
*/

static CRUCLOCK *_get_clock(u32 ID){
	CRUCLOCK *p = _clocks;

	for(u32 i = 0;i<sizeof(_clocks) / sizeof(CRUCLOCK);i++,p++){
		if(p->id == ID)
			return p;
	}
	printf("Unsupported clock ID %x\n",ID);
	return NULL;
}

static s32 _cru_clk_enable(CRUCLOCK *p,s8 s){
	u32 reg;

	int set = p->flags & CLK_GATE_SET_TO_DISABLE ? 1 : 0;
	set ^= s;
	if (p->flags & CLK_GATE_HIWORD_MASK) {
		reg = BIT(p->shift + 16);
		if (set)
			reg |= BIT(p->shift);
	}
	else {
		reg = REGW(CRU_BASE+p->offset);
		if (set)
			reg |= BIT(p->shift);
		else
			reg &= ~BIT(p->shift);
	}
	REGW(CRU_BASE + p->offset) = reg;
	return 0;
}

s32 cru_clk_enable(u32 ID){
	CRUCLOCK *p;

	if((p = _get_clock(ID)) == NULL)
		return -1;
	return _cru_clk_enable(p,1);
}

s32 cru_clk_disable(u32 ID){
	CRUCLOCK *p;

	if((p = _get_clock(ID)) == NULL)
		return -1;
	return _cru_clk_enable(p,0);
}