#include "main.h"

#ifndef __VOPH__
#define __VOPH__

#define VOP_CFG_DONE				0x0
#define VOP_VERSION_INFO			0x4
#define VOP_SYS_CTRL                0x8
#define VOP_SYS_CTRL1               0xc
#define VOP_DSP_CTRL0				0x10
#define VOP_DSP_CTRL1				0x14
#define VOP_MCU_CTRL			0x1C

#define VOP_WIN0_CTRL0			0x00000100
#define VOP_WIN0_CTRL1			0x00000104
#define VOP_WIN1_CTRL0			0x00000200
#define VOP_WIN1_CTRL1			0x00000204

#define VOP_CABC_GAUSS_LINE0_0		0x01c8
#define VOP_CABC_GAUSS_LINE0_1		0x01cc
#define VOP_CABC_GAUSS_LINE1_0		0x01d0
#define VOP_CABC_GAUSS_LINE1_1		0x01d4
#define VOP_CABC_GAUSS_LINE2_0		0x01d8
#define VOP_CABC_GAUSS_LINE2_1		0x01dc

#define VOP_FRC_LOWER01_0			0x01e0
#define VOP_FRC_LOWER01_1			0x01e4
#define VOP_FRC_LOWER10_0			0x01e8
#define VOP_FRC_LOWER10_1			0x01ec
#define VOP_FRC_LOWER11_0			0x01f0
#define VOP_FRC_LOWER11_1			0x01f4
#define VOP_AFBCD0_CTRL				0x0200
#define VOP_DSP_HTOTAL_HS_END		0x618
#define VOP_INTR_EN0				0xe0
#define VOP_INTR_CLEAR0				0xe4


#define VOP_REGW(a) REGW(VOP_BASE + a)
#define VOP_REG_SET(a,b,c,value) REG_SET((VOP_BASE+a),b,c,value,u32)




int vop_init();
int vop_enable();

#endif