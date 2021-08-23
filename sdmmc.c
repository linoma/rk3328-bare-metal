#include "sdmmc.h"
#include "printf.h"

static int reset_dma(){
	u32 bmod = REGW(SDMMC_BASE+SDMMC_BMOD);
	bmod |= SDMMC_IDMAC_SWRESET;
	REGW(SDMMC_BASE+SDMMC_BMOD)= bmod;
	return 0;
}

static int ctrl_reset_dma(u32 reset){
	u32 ctrl,timeout = get_cycles() + 500 * _usec_factor;

	ctrl = REGW(SDMMC_BASE+SDMMC_CTRL);
	ctrl |= reset;
	REGW(SDMMC_BASE+SDMMC_CTRL)= ctrl;
	do {
		ctrl = REGW(SDMMC_BASE+SDMMC_CTRL);
		if (!(ctrl & reset))
			return 1;
	} while (get_cycles() < timeout);
	return 0;
}

static int stop_dma(){
	u32 temp;

	temp = REGW(SDMMC_BASE+SDMMC_CTRL);
	temp &= ~SDMMC_CTRL_USE_IDMAC;
	temp |= SDMMC_CTRL_DMA_RESET;
	REGW(SDMMC_BASE+SDMMC_CTRL) = temp;

	temp = REGW(SDMMC_BASE+SDMMC_BMOD);
	temp &= ~(SDMMC_IDMAC_ENABLE | SDMMC_IDMAC_FB);
	temp |= SDMMC_IDMAC_SWRESET;
	REGW(SDMMC_BASE+SDMMC_BMOD)= temp;
}

static int start_dma(){
	u32 temp;
	int ret = 0;

	ctrl_reset_dma(SDMMC_CTRL_DMA_RESET);
	reset_dma();

	temp = REGW(SDMMC_BASE+SDMMC_CTRL);
	temp |= SDMMC_CTRL_USE_IDMAC;
	REGW(SDMMC_BASE+SDMMC_CTRL)= temp;

//	wmb();

	temp = REGW(SDMMC_BASE+SDMMC_BMOD);
	temp |= SDMMC_IDMAC_ENABLE | SDMMC_IDMAC_FB;
	REGW(SDMMC_BASE+SDMMC_BMOD)= temp;
	REGW(SDMMC_BASE+SDMMC_PLDMND) = 1;
	return 0;
}

static int init_dma(){
	REGW(SDMMC_BASE+SDMMC_IDSTS) = IDMAC_INT_CLR;
	REGW(SDMMC_BASE+SDMMC_IDINTEN) = SDMMC_IDMAC_INT_NI | SDMMC_IDMAC_INT_RI | SDMMC_IDMAC_INT_TI;
	REGW(SDMMC_BASE+SDMMC_DBADDR) =  (u32)&_mem[0x1000];
	return 0;
}

int sdmmc_init(){
	u32 hcon = REGW(SDMMC_BASE+SDMMC_HCON);
	u32 verid = REGW(SDMMC_BASE+SDMMC_VERID);

	printf("MMC %x %x dataw:%x verid:%x dma:%x addr_cfg:%x\n",verid,hcon,SDMMC_GET_HDATA_WIDTH(hcon),SDMMC_GET_VERID(verid),SDMMC_GET_TRANS_MODE(hcon),SDMMC_GET_ADDR_CONFIG(hcon));
	u32 fifo_size = 0x100;
	u32 fifoth_val = SDMMC_SET_FIFOTH(0x2, fifo_size / 2 - 1, fifo_size / 2);
	printf("MMC fifo:%x %x\n",fifo_size,fifoth_val);

	REGW(SDMMC_BASE+SDMMC_FIFOTH) = fifoth_val;
	REGW(SDMMC_BASE+SDMMC_CLKENA) = 0;
	REGW(SDMMC_BASE+SDMMC_CLKSRC) = 0;
	REGW(SDMMC_BASE+SDMMC_RINTSTS)= 0xFFFFFFFF;
	REGW(SDMMC_BASE+SDMMC_INTMASK)= SDMMC_INT_CMD_DONE | SDMMC_INT_DATA_OVER | SDMMC_INT_TXDR | SDMMC_INT_RXDR | DW_MCI_ERROR_FLAGS;
	REGW(SDMMC_BASE+SDMMC_CTRL) = SDMMC_CTRL_INT_ENABLE;

	init_dma();
	return 0;
}

static void dw_mci_pull_data32(void *buf, int cnt){
	u32 *pdata = buf;
	for (; cnt >= 4; cnt -= 4)
		*pdata++ = REGW(SDMMC_BASE+DATA_240A_OFFSET);
	buf = pdata;
	if (cnt) {
		u32 v = REGW(SDMMC_BASE+DATA_240A_OFFSET);
		for(;cnt>0;cnt--,v>>=8)
			*((u8 *)buf++) = (u8)v;
	}
}