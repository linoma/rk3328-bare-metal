#include "sdmmc.h"
#include "gic.h"
#include "printf.h"

#define SDMMC_BASE 0xff500000
/*
 * sdmmc ff500000
 * emmc 0xff520000
 * stdio ff510000
 *
 *
 * 	*cmdr |= SDMMC_CMD_USE_HOLD_REG;
*/

static int sdmmc_reset(u32 reset){
	u32 ctrl;
	u64 timeout = get_cycles() + 500 * _usec_factor;

	ctrl = REGW(SDMMC_BASE+SDMMC_CTRL);
	ctrl |= reset;
	REGW(SDMMC_BASE+SDMMC_CTRL)= ctrl;
	do {
		ctrl = REGW(SDMMC_BASE+SDMMC_CTRL);
		if (!(ctrl & reset))
			return 1;
	} while (get_cycles() < timeout);
	printf("sdmmc_reset timeout \n");
	return 0;
}

static int sdmcc_irq(){
	printf("sd irq\n");
	return 0;
}

static int reset_dma(){
	u32 bmod = REGW(SDMMC_BASE+SDMMC_BMOD);
	bmod |= SDMMC_IDMAC_SWRESET;
	REGW(SDMMC_BASE+SDMMC_BMOD)= bmod;
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

	sdmmc_reset(SDMMC_CTRL_DMA_RESET);
	reset_dma();

	temp = REGW(SDMMC_BASE+SDMMC_CTRL);
	temp |= SDMMC_CTRL_USE_IDMAC;
	REGW(SDMMC_BASE+SDMMC_CTRL)= temp;

	wmb();

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

static void wait_while_busy(u32 cmd_flags){
	u64 timeout = get_cycles() + 500 * _msec_factor;

	if ((cmd_flags & SDMMC_CMD_PRV_DAT_WAIT) && !(cmd_flags & SDMMC_CMD_VOLT_SWITCH)) {
		while (REGW(SDMMC_BASE+SDMMC_STATUS) & SDMMC_STATUS_BUSY) {
			if (get_cycles() > timeout)
				break;
			udelay(10);
		}
	}
}

static u32 prepare_command(struct mmc_command *cmd){
	struct mmc_data	*data;
	u32 cmdr;

	cmdr = cmd->opcode;
	if (cmd->opcode == MMC_STOP_TRANSMISSION || cmd->opcode == MMC_GO_IDLE_STATE || cmd->opcode == MMC_GO_INACTIVE_STATE ||	(cmd->opcode == SD_IO_RW_DIRECT && ((cmd->arg >> 9) & 0x1FFFF) == SDIO_CCCR_ABORT))
		cmdr |= SDMMC_CMD_STOP;
	else if (cmd->opcode != MMC_SEND_STATUS && cmd->data)
		cmdr |= SDMMC_CMD_PRV_DAT_WAIT;
	if (cmd->flags & MMC_RSP_PRESENT) {
		cmdr |= SDMMC_CMD_RESP_EXP;
		if (cmd->flags & MMC_RSP_136)
			cmdr |= SDMMC_CMD_RESP_LONG;
	}
	if (cmd->flags & MMC_RSP_CRC)
		cmdr |= SDMMC_CMD_RESP_CRC;
	data = cmd->data;
	if (data) {
		cmdr |= SDMMC_CMD_DAT_EXP;
		if (data->flags & MMC_DATA_STREAM)
			cmdr |= SDMMC_CMD_STRM_MODE;
		if (data->flags & MMC_DATA_WRITE)
			cmdr |= SDMMC_CMD_DAT_WR;
	}
	cmdr |= SDMMC_CMD_USE_HOLD_REG;
	return cmdr;
}

static int start_command(struct mmc_command *cmd,u32 cmd_flags){
	REGW(SDMMC_BASE+SDMMC_CMDARG) = cmd->arg;
	wmb();
	wait_while_busy(cmd_flags);
	REGW(SDMMC_BASE+SDMMC_CMD) = cmd_flags | SDMMC_CMD_START;
	return 0;
}

static int sdmmc_submit_data(struct mmc_data	*data){
	return 0;
}

static int sdmmc_request(struct mmc_command *cmd,u32 cmdflags){
	struct mmc_data	*data;

	printf("sdmmc_request 0 \n");
	if(REGW(SDMMC_BASE+SDMMC_CDETECT) & 1)
		return -1;
	data = cmd->data;
	if (data) {
		reset_dma();
		REGW(SDMMC_BASE+SDMMC_TMOUT) = 0xFFFFFFFF;
		REGW(SDMMC_BASE+SDMMC_BYTCNT) = data->blksz*data->blocks;
		REGW(SDMMC_BASE+SDMMC_BLKSIZ) = data->blksz;
		start_dma();
	}
	if (data) {
		sdmmc_submit_data(data);
		wmb();
	}
	start_command(cmd,cmdflags);
	return 0;
}

int mmc_wait_for_cmd(struct mmc_command *cmd){
	printf("mmc_wait_for_cmd 0\n");
	u32 cmd_flags = prepare_command(cmd);
	sdmmc_request(cmd,cmd_flags);
	wait_while_busy(cmd_flags);
	return 0;
}

int sdmmc_init(){
	u32 hcon = REGW(SDMMC_BASE+SDMMC_HCON);
	u32 verid = REGW(SDMMC_BASE+SDMMC_VERID);
	u32 tmode = SDMMC_GET_TRANS_MODE(hcon);
	u32 addr_config = SDMMC_GET_ADDR_CONFIG(hcon);

	//IDMAC supports 32-bit address mode
	printf("MMC %x %x dataw:%x verid:%x dma:%x addr_cfg:%x\n",verid,hcon,SDMMC_GET_HDATA_WIDTH(hcon),SDMMC_GET_VERID(verid),tmode,addr_config);

	sdmmc_reset(SDMMC_CTRL_ALL_RESET_FLAGS);
	reset_dma();
	init_dma();

	REGW(SDMMC_BASE+SDMMC_RINTSTS)= 0xFFFFFFFF;
	REGW(SDMMC_BASE+SDMMC_INTMASK)= 0;
	REGW(SDMMC_BASE+SDMMC_TMOUT)= 0xFFFFFFFF;

	{
		u32 fifo_size = 0x100;
		u32 fifoth_val = SDMMC_SET_FIFOTH(0x2, fifo_size / 2 - 1, fifo_size / 2);

		REGW(SDMMC_BASE+SDMMC_FIFOTH) = fifoth_val;
		REGW(SDMMC_BASE+SDMMC_CLKENA) = 0;
		REGW(SDMMC_BASE+SDMMC_CLKSRC) = 0;
	}

	gic_register_irq_routine(32+12,sdmcc_irq,IRQ_TYPE_LEVEL_HIGH);

	REGW(SDMMC_BASE+SDMMC_RINTSTS)= 0xFFFFFFFF;
	REGW(SDMMC_BASE+SDMMC_INTMASK)= SDMMC_INT_CMD_DONE | SDMMC_INT_DATA_OVER | SDMMC_INT_TXDR | SDMMC_INT_RXDR | DW_MCI_ERROR_FLAGS;
	REGW(SDMMC_BASE+SDMMC_CTRL) = SDMMC_CTRL_INT_ENABLE;

	{
		u32 temp;
		REGW(SDMMC_BASE+SDMMC_INTMASK);
		temp |= SDMMC_INT_CD;
		REGW(SDMMC_BASE+SDMMC_INTMASK) = temp;
	}

	printf("sd cd %x\n",(REGW(SDMMC_BASE+SDMMC_CDETECT) & 1) == 0);
	{
		struct mmc_data data={0};
		struct mmc_command cmd={0};

		printf("sdmmc request start\n");
		cmd.data = &data;
		cmd.opcode = MMC_SEND_STATUS;
		cmd.resp[0] = MMC_RSP_R1;
//		cmd.arg = 0;

		data.blksz = 64;
		data.blocks = 1;
		data.flags = MMC_DATA_READ;

		mmc_wait_for_cmd(&cmd);
	}
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