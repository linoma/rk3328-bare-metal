#include "main.h"

#ifndef __MALIUTGARDH__
#define __MALIUTGARDH__

#define MALI_OFFSET_GP                    0x00000
#define MALI_OFFSET_GP_MMU                0x03000

#define MALI_OFFSET_PP0                   0x08000
#define MALI_OFFSET_PP0_MMU               0x04000
#define MALI_OFFSET_PP1                   0x0A000
#define MALI_OFFSET_PP1_MMU               0x05000
#define MALI_OFFSET_PP2                   0x0C000
#define MALI_OFFSET_PP2_MMU               0x06000
#define MALI_OFFSET_PP3                   0x0E000
#define MALI_OFFSET_PP3_MMU               0x07000

#define MALI_OFFSET_PP4                   0x28000
#define MALI_OFFSET_PP4_MMU               0x1C000
#define MALI_OFFSET_PP5                   0x2A000
#define MALI_OFFSET_PP5_MMU               0x1D000
#define MALI_OFFSET_PP6                   0x2C000
#define MALI_OFFSET_PP6_MMU               0x1E000
#define MALI_OFFSET_PP7                   0x2E000
#define MALI_OFFSET_PP7_MMU               0x1F000

#define MALI_OFFSET_L2_RESOURCE0          0x01000
#define MALI_OFFSET_L2_RESOURCE1          0x10000
#define MALI_OFFSET_L2_RESOURCE2          0x11000

#define MALI400_OFFSET_L2_CACHE0          MALI_OFFSET_L2_RESOURCE0
#define MALI450_OFFSET_L2_CACHE0          MALI_OFFSET_L2_RESOURCE1
#define MALI450_OFFSET_L2_CACHE1          MALI_OFFSET_L2_RESOURCE0
#define MALI450_OFFSET_L2_CACHE2          MALI_OFFSET_L2_RESOURCE2
#define MALI470_OFFSET_L2_CACHE1          MALI_OFFSET_L2_RESOURCE0

#define MALI_OFFSET_BCAST                 0x13000
#define MALI_OFFSET_DLBU                  0x14000

#define MALI_OFFSET_PP_BCAST              0x16000
#define MALI_OFFSET_PP_BCAST_MMU          0x15000

#define MALI_OFFSET_PMU                   0x02000
#define MALI_OFFSET_DMA                   0x12000


typedef volatile struct gpio_reg{
    unsigned int SWPORTA_DR;        //0x0000 Port A data register
    unsigned int SWPORTA_DDR;       //0x0004 Port A data direction register
    unsigned int RESERVED0[10];     //0x0008
    unsigned int INTEN;	            //0x0030 Interrupt enable register
    unsigned int INTMASK;           //0x0034 Interrupt mask register
    unsigned int INTTYPE_LEVEL;     //0x0038 Interrupt level register
    unsigned int INT_POLARITY;      //0x003C Interrupt polarity register
    unsigned int INT_STATUS;        //0x0040 Interrupt status of port A
    unsigned int INT_RAWSTATUS;     //0x0044 Raw Interrupt status of port A
    unsigned int DEBOUNCE;          //0x0048 Debounce enable register
    unsigned int PORTA_EOI;         //0x004c Port A clear interrupt register
    unsigned int EXT_PORTA;         //0x0050 Debounce enable register
    unsigned int RESERVED1[3];      //0x0054
    unsigned int LS_SYNC;           //0x0060 Level_sensitive synchronization enable register
} gpio_reg, *p_gpio_reg;

typedef enum {
	MALIGP2_REG_ADDR_MGMT_VSCL_START_ADDR           = 0x00,
	MALIGP2_REG_ADDR_MGMT_VSCL_END_ADDR             = 0x04,
	MALIGP2_REG_ADDR_MGMT_PLBUCL_START_ADDR         = 0x08,
	MALIGP2_REG_ADDR_MGMT_PLBUCL_END_ADDR           = 0x0c,
	MALIGP2_REG_ADDR_MGMT_PLBU_ALLOC_START_ADDR     = 0x10,
	MALIGP2_REG_ADDR_MGMT_PLBU_ALLOC_END_ADDR       = 0x14,
	MALIGP2_REG_ADDR_MGMT_CMD                       = 0x20,
	MALIGP2_REG_ADDR_MGMT_INT_RAWSTAT               = 0x24,
	MALIGP2_REG_ADDR_MGMT_INT_CLEAR                 = 0x28,
	MALIGP2_REG_ADDR_MGMT_INT_MASK                  = 0x2C,
	MALIGP2_REG_ADDR_MGMT_INT_STAT                  = 0x30,
	MALIGP2_REG_ADDR_MGMT_PERF_CNT_0_ENABLE         = 0x3C,
	MALIGP2_REG_ADDR_MGMT_PERF_CNT_1_ENABLE         = 0x40,
	MALIGP2_REG_ADDR_MGMT_PERF_CNT_0_SRC            = 0x44,
	MALIGP2_REG_ADDR_MGMT_PERF_CNT_1_SRC            = 0x48,
	MALIGP2_REG_ADDR_MGMT_PERF_CNT_0_VALUE          = 0x4C,
	MALIGP2_REG_ADDR_MGMT_PERF_CNT_1_VALUE          = 0x50,
	MALIGP2_REG_ADDR_MGMT_PERF_CNT_0_LIMIT          = 0x54,
	MALIGP2_REG_ADDR_MGMT_STATUS                    = 0x68,
	MALIGP2_REG_ADDR_MGMT_VERSION                   = 0x6C,
	MALIGP2_REG_ADDR_MGMT_VSCL_START_ADDR_READ      = 0x80,
	MALIGP2_REG_ADDR_MGMT_PLBCL_START_ADDR_READ     = 0x84,
	MALIGP2_CONTR_AXI_BUS_ERROR_STAT                = 0x94,
	MALIGP2_REGISTER_ADDRESS_SPACE_SIZE             = 0x98,
} maligp_reg_addr_mgmt_addr;

enum mali200_mgmt_reg {
	MALI200_REG_ADDR_MGMT_VERSION                              = 0x1000,
	MALI200_REG_ADDR_MGMT_CURRENT_REND_LIST_ADDR               = 0x1004,
	MALI200_REG_ADDR_MGMT_STATUS                               = 0x1008,
	MALI200_REG_ADDR_MGMT_CTRL_MGMT                            = 0x100c,

	MALI200_REG_ADDR_MGMT_INT_RAWSTAT                          = 0x1020,
	MALI200_REG_ADDR_MGMT_INT_CLEAR                            = 0x1024,
	MALI200_REG_ADDR_MGMT_INT_MASK                             = 0x1028,
	MALI200_REG_ADDR_MGMT_INT_STATUS                           = 0x102c,

	MALI200_REG_ADDR_MGMT_BUS_ERROR_STATUS                     = 0x1050,

	MALI200_REG_ADDR_MGMT_PERF_CNT_0_ENABLE                    = 0x1080,
	MALI200_REG_ADDR_MGMT_PERF_CNT_0_SRC                       = 0x1084,
	MALI200_REG_ADDR_MGMT_PERF_CNT_0_LIMIT                     = 0x1088,
	MALI200_REG_ADDR_MGMT_PERF_CNT_0_VALUE                     = 0x108c,

	MALI200_REG_ADDR_MGMT_PERF_CNT_1_ENABLE                    = 0x10a0,
	MALI200_REG_ADDR_MGMT_PERF_CNT_1_SRC                       = 0x10a4,
	MALI200_REG_ADDR_MGMT_PERF_CNT_1_VALUE                     = 0x10ac,

	MALI200_REG_ADDR_MGMT_PERFMON_CONTR                        = 0x10b0,
	MALI200_REG_ADDR_MGMT_PERFMON_BASE                         = 0x10b4,

	MALI200_REG_SIZEOF_REGISTER_BANK                           = 0x10f0

};

#endif