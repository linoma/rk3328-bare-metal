#include "main.h"

#ifndef __VOPH__
#define __VOPH__

#define VOP_CFG_DONE				0x0
#define VOP_VERSION_INFO			0x4
#define VOP_SYS_CTRL                0x8
#define VOP_SYS_CTRL1               0xc
#define VOP_DSP_CTRL0				0x10
#define VOP_DSP_CTRL1				0x14
#define VOP_DSP_BG					0x18
#define VOP_MCU_CTRL				0x1C
#define VOP_LINE_FLAG				0x00000040
#define VOP_VOP_STATUS				0x00000044
#define VOP_BLANKING_VALUE			0x00000048
#define VOP_WIN0_DSP_BG				0x00000050
#define VOP_WIN1_DSP_BG				0x00000054
#define VOP_INTR_EN0				0xe0
#define VOP_INTR_CLEAR0				0xe4
#define VOP_INTR_STATUS0			0xe8

#define VOP_WIN0_CTRL0				0x00000100
#define VOP_WIN0_CTRL1				0x00000104
#define VOP_WIN0_COLOR_KEY			0x00000108
#define VOP_WIN0_VIR				0x0000010c
#define VOP_WIN0_YRGB_MST			0x00000110
#define VOP_WIN0_CBR_MST			0x00000114
#define VOP_WIN0_ACT_INFO			0x00000118
#define VOP_WIN0_DSP_INFO			0x0000011c
#define VOP_WIN0_DSP_ST				0x00000120
#define VOP_WIN0_SCL_FACTOR_YRGB	0x00000124
#define VOP_WIN0_SCL_FACTOR_CBR		0x00000128
#define VOP_WIN0_SCL_OFFSET			0x0000012c
#define VOP_WIN0_SRC_ALPHA_CTRL		0x00000130
#define VOP_WIN0_DST_ALPHA_CTRL		0x00000134
#define VOP_WIN0_FADING_CTRL		0x00000138
#define VOP_WIN0_CTRL2				0x0000013c

#define VOP_WIN1_CTRL0				0x00000200
#define VOP_WIN1_CTRL1				0x00000204
#define VOP_WIN1_COLOR_KEY			0x00000208
#define VOP_WIN1_VIR				0x0000020c
#define VOP_WIN1_YRGB_MST			0x00000210
#define VOP_WIN1_CBR_MST			0x00000214
#define VOP_WIN1_ACT_INFO			0x00000218
#define VOP_WIN1_DSP_INFO			0x0000021c
#define VOP_WIN1_DSP_ST				0x00000220
#define VOP_WIN1_SCL_FACTOR_YRGB	0x00000224
#define VOP_WIN1_SCL_FACTOR_CBR		0x00000228
#define VOP_WIN1_SCL_OFFSET			0x0000022c
#define VOP_WIN1_SRC_ALPHA_CTRL		0x00000230
#define VOP_WIN1_DST_ALPHA_CTRL		0x00000234
#define VOP_WIN1_FADING_CTRL		0x00000238
#define VOP_WIN1_CTRL2				0x0000023c
#define VOP_WIN2_CTRL0				0x00000300
#define VOP_WIN2_CTRL1				0x00000304
#define VOP_WIN2_COLOR_KEY			0x00000308
#define VOP_WIN2_VIR				0x0000030c
#define VOP_WIN2_YRGB_MST			0x00000310
#define VOP_WIN2_CBR_MST			0x00000314
#define VOP_WIN2_ACT_INFO			0x00000318
#define VOP_WIN2_DSP_INFO			0x0000031c
#define VOP_WIN2_DSP_ST				0x00000320
#define VOP_WIN2_SCL_FACTOR_YRGB	0x00000324
#define VOP_WIN2_SCL_FACTOR_CBR		0x00000328
#define VOP_WIN2_SCL_OFFSET			0x0000032c
#define VOP_WIN2_SRC_ALPHA_CTRL		0x00000330
#define VOP_WIN2_DST_ALPHA_CTRL		0x00000334
#define VOP_WIN2_FADING_CTRL		0x00000338
#define VOP_WIN2_CTRL2				0x0000033c


#define VOP_POST_DSP_HACT_INFO		0x00000600
#define VOP_POST_DSP_VACT_INFO		0x00000604
#define VOP_POST_SCL_FACTOR_YRGB	0x00000608
#define VOP_POST_RESERVED			0x0000060c
#define VOP_POST_SCL_CTRL			0x00000610
#define VOP_POST_DSP_VACT_INFO_F1	0x00000614
#define VOP_DSP_HTOTAL_HS_END		0x00000618
#define VOP_DSP_HACT_ST_END			0x0000061c
#define VOP_DSP_VTOTAL_VS_END		0x00000620
#define VOP_DSP_VACT_ST_END			0x00000624
#define VOP_DSP_VS_ST_END_F1		0x00000628
#define VOP_DSP_VACT_ST_END_F1		0x0000062c
#define VOP_BCSH_COLOR_BAR			0x00000640
#define VOP_BCSH_BCS				0x00000644
#define VOP_BCSH_H					0x00000648
#define VOP_BCSH_CTRL				0x0000064c
#define VOP_FRC_LOWER01_0			0x00000678
#define VOP_FRC_LOWER01_1			0x0000067c
#define VOP_FRC_LOWER10_0			0x00000680
#define VOP_FRC_LOWER10_1			0x00000684
#define VOP_FRC_LOWER11_0			0x00000688
#define VOP_FRC_LOWER11_1			0x0000068c
#define VOP_DBG_POST_REG0			0x000006e8
#define VOP_DBG_POST_RESERVED		0x000006ec
#define VOP_DBG_DATAO				0x000006f0
#define VOP_DBG_DATAO_2				0x000006f4

/* sdr to hdr */
#define VOP_SDR2HDR_CTRL			0x00000700
#define VOP_EOTF_OETF_Y0			0x00000704
#define VOP_RESERVED0001			0x00000708
#define VOP_RESERVED0002			0x0000070c
#define VOP_EOTF_OETF_Y1			0x00000710
#define VOP_EOTF_OETF_Y64			0x0000080c
#define VOP_OETF_DX_DXPOW1			0x00000810
#define VOP_OETF_DX_DXPOW64			0x0000090c
#define VOP_OETF_XN1				0x00000910
#define VOP_OETF_XN63				0x00000a08

#define VOP_HDR2DR_CTRL				0x00000a10
#define VOP_HDR2DR_SRC_RANGE		0x00000a14
#define VOP_HDR2DR_NORMFACEETF		0x00000a18
#define VOP_HDR2DR_DST_RANGE		0x00000a20
#define VOP_HDR2DR_NORMFACGAMMA		0x00000a24
#define VOP_HDR2SDR_EETF_OETF_Y0	0x00000a28
#define VOP_HDR2DR_SAT_Y0			0x00000a2C
#define VOP_HDR2SDR_EETF_OETF_Y1	0x00000a30
#define VOP_HDR2DR_SAT_Y1			0x00000ab0

#define VOP_DBG_WIN0_REG0			0x000001f0
#define VOP_DBG_WIN0_REG1			0x000001f4
#define VOP_DBG_WIN0_REG2			0x000001f8
#define VOP_DBG_WIN0_RESERVED		0x000001fc

#define VOP_CABC_GAUSS_LINE0_0		0x01c8
#define VOP_CABC_GAUSS_LINE0_1		0x01cc
#define VOP_CABC_GAUSS_LINE1_0		0x01d0
#define VOP_CABC_GAUSS_LINE1_1		0x01d4
#define VOP_CABC_GAUSS_LINE2_0		0x01d8
#define VOP_CABC_GAUSS_LINE2_1		0x01dc

#define VOP_AFBCD0_CTRL				0x0200


#define VOP_REGW(a) REGW(VOP_BASE + a)
#define VOP_REG_SET(a,b,c,value) REG_SET((VOP_BASE+(a)),b,c,value,u32)
#define VOP_WIN_REG(w,reg,b,c,value) VOP_REG_SET(VOP_WIN0_CTRL0+(w*0x100)+(reg-0x100),b,c,value)

#define VOP_WIN_ENABLE(w,v) VOP_WIN_REG(w,VOP_WIN0_CTRL0,0x1,0x0,v);
#define VOP_WIN_SIZE(win,w,h,pf) \
	VOP_WIN_REG(win,VOP_WIN0_ACT_INFO,0x1fff1fff,0x0,((w-1)| ((h-1)<<16)));\
	VOP_WIN_REG(win,VOP_WIN0_DSP_INFO,0xfff0fff,0x0,((w-1)| ((h-1)<<16))); \
	VOP_WIN_REG(win,VOP_WIN0_CTRL0,7,1,pf);


#define VOP_CONFIG_DONE() VOP_REG_SET(VOP_CFG_DONE,0x1,0x0,0x1);

int vop_init();
int vop_enable();

#endif