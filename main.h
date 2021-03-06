#include "printf.h"

#ifndef __MAINH__
#define __MAINH__

typedef unsigned int u32;
typedef signed int s32;
typedef unsigned long u64;
typedef signed long s64;
typedef unsigned short u16;
typedef unsigned char u8;
typedef signed char s8;
typedef signed short __le16;

#define NOINLINE __attribute__((noinline))
#define INLINE inline

#define NULL	0
#define BIT(a)	(1 << (a))
#define REGB(a) *((volatile u8 *)(a))
#define REGW(a) *((volatile u32 *)(a))
#define REG_SET(a,b,c,value,sz) {sz d = REGW(a);d &= ~(b<<c);REGW(a)=d | (value << c);}

#define MMIO_BASE 					0xFF000000

#define GRF_BASE					0xFF100000
#define VOP_BASE					0xFF370000
#define CRU_BASE					0xFF440000
#define HDMI_BASE 					0xFF3C0000
#define GPU_BASE 					0xFF300000 //0xffa30000 ff300000
#define HDMIPHY_BASE				0xFF430000
#define SDIO_BASE					0xFF510000
#define EMMC_BASE					0xFF520000
#define GIC_BASE					0xFF811000
#define DMAC_BASE					0xFF1F0000

#define __nops(n)	".rept	" #n "\nnop\n.endr\n"
#define nops(n)		asm volatile(__nops(n))

#define sev()		asm volatile("sev" : : : "memory")
#define wfe()		asm volatile("wfe" : : : "memory")
#define wfi()		asm volatile("wfi" : : : "memory")

#define isb()		asm volatile("isb" : : : "memory")
#define dsb(option) __asm__ __volatile__ ("dsb " #option : : : "memory")
#define dmb(option) __asm__ __volatile__ ("dmb " #option : : : "memory")
#define mb()		dsb(sy)
#define rmb()		dsb(ld)
#define wmb()		dsb(st)

s64 __div(s64 v,s64 d);
u64 get_cycles(void);
void udelay(u32 usec);
extern void __flush_dcache_area(void *addr, u32 len);
NOINLINE u64 read_mpidr(void);
void arch_local_irq_enable(void);
void arch_local_irq_disable(void);

extern u8 *_mem;
extern u32 _usec_factor;
extern u32 _msec_factor;

#endif