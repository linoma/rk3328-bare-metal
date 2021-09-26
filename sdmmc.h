#include "main.h"

#ifndef __SDMMCH__
#define __SDMMCH__

#define SDMMC_CTRL					0x000
#define SDMMC_PWREN					0x004
#define SDMMC_CLKDIV				0x008
#define SDMMC_CLKSRC				0x00c
#define SDMMC_CLKENA				0x010
#define SDMMC_TMOUT					0x014
#define SDMMC_CTYPE					0x018
#define SDMMC_BLKSIZ				0x01c
#define SDMMC_BYTCNT				0x020
#define SDMMC_INTMASK				0x024
#define SDMMC_CMDARG				0x028
#define SDMMC_CMD					0x02c
#define SDMMC_RESP0					0x030
#define SDMMC_RESP1					0x034
#define SDMMC_RESP2					0x038
#define SDMMC_RESP3					0x03c
#define SDMMC_MINTSTS				0x040
#define SDMMC_RINTSTS				0x044
#define SDMMC_STATUS				0x048
#define SDMMC_FIFOTH				0x04c
#define SDMMC_CDETECT				0x050
#define SDMMC_WRTPRT				0x054
#define SDMMC_GPIO					0x058
#define SDMMC_TCBCNT				0x05c
#define SDMMC_TBBCNT				0x060
#define SDMMC_DEBNCE				0x064
#define SDMMC_USRID					0x068
#define SDMMC_VERID					0x06c
#define SDMMC_HCON					0x070
#define SDMMC_UHS_REG				0x074
#define SDMMC_BMOD					0x080
#define SDMMC_PLDMND				0x084
#define SDMMC_DBADDR				0x088
#define SDMMC_IDSTS					0x08c
#define SDMMC_IDINTEN				0x090
#define SDMMC_DSCADDR				0x094
#define SDMMC_BUFADDR				0x098
#define SDMMC_CDTHRCTL				0x100
#define SDMMC_DATA(x)				(x)

#define DMA_INTERFACE_IDMA			(0x0)
#define DMA_INTERFACE_DWDMA			(0x1)
#define DMA_INTERFACE_GDMA			(0x2)
#define DMA_INTERFACE_NODMA			(0x3)

#define SDMMC_GET_TRANS_MODE(x)		(((x)>>16) & 0x3)
#define SDMMC_GET_SLOT_NUM(x)		((((x)>>1) & 0x1F) + 1)
#define SDMMC_GET_HDATA_WIDTH(x)	(((x)>>7) & 0x7)
#define SDMMC_GET_ADDR_CONFIG(x)	(((x)>>27) & 0x1)
#define SDMMC_GET_VERID(x)			((x) & 0xFFFF)
#define SDMMC_SET_RD_THLD(v, x)		(((v) & 0xFFF) << 16 | (x))

#define SDMMC_SET_FIFOTH(m, r, t)	(((m) & 0x7) << 28 | ((r) & 0xFFF) << 16 | ((t) & 0xFFF))

#define DW_MCI_DATA_ERROR_FLAGS		(SDMMC_INT_DRTO | SDMMC_INT_DCRC | SDMMC_INT_HTO | SDMMC_INT_SBE  |  SDMMC_INT_EBE | SDMMC_INT_HLE)
#define DW_MCI_CMD_ERROR_FLAGS		(SDMMC_INT_RTO | SDMMC_INT_RCRC | SDMMC_INT_RESP_ERR | SDMMC_INT_HLE)
#define DW_MCI_ERROR_FLAGS			(DW_MCI_DATA_ERROR_FLAGS | DW_MCI_CMD_ERROR_FLAGS)
#define DW_MCI_SEND_STATUS			1
#define DW_MCI_RECV_STATUS			2
#define DW_MCI_DMA_THRESHOLD		16

#define DW_MCI_FREQ_MAX	200000000	/* unit: HZ */
#define DW_MCI_FREQ_MIN	100000		/* unit: HZ */

#define IDMAC_INT_CLR		(SDMMC_IDMAC_INT_AI | SDMMC_IDMAC_INT_NI | SDMMC_IDMAC_INT_CES | SDMMC_IDMAC_INT_DU | SDMMC_IDMAC_INT_FBE | SDMMC_IDMAC_INT_RI | SDMMC_IDMAC_INT_TI)

#define DATA_OFFSET					0x100
#define DATA_240A_OFFSET			0x200

#define SDMMC_CTRL_USE_IDMAC		BIT(25)
#define SDMMC_CTRL_CEATA_INT_EN		BIT(11)
#define SDMMC_CTRL_SEND_AS_CCSD		BIT(10)
#define SDMMC_CTRL_SEND_CCSD		BIT(9)
#define SDMMC_CTRL_ABRT_READ_DATA	BIT(8)
#define SDMMC_CTRL_SEND_IRQ_RESP	BIT(7)
#define SDMMC_CTRL_READ_WAIT		BIT(6)
#define SDMMC_CTRL_DMA_ENABLE		BIT(5)
#define SDMMC_CTRL_INT_ENABLE		BIT(4)
#define SDMMC_CTRL_DMA_RESET		BIT(2)
#define SDMMC_CTRL_FIFO_RESET		BIT(1)
#define SDMMC_CTRL_RESET			BIT(0)

#define SDMMC_INT_SDIO(n)			BIT(16 + (n))
#define SDMMC_INT_EBE				BIT(15)
#define SDMMC_INT_ACD				BIT(14)
#define SDMMC_INT_SBE				BIT(13)
#define SDMMC_INT_HLE				BIT(12)
#define SDMMC_INT_FRUN				BIT(11)
#define SDMMC_INT_HTO				BIT(10)
#define SDMMC_INT_VSI           	SDMMC_INT_HTO
#define SDMMC_INT_DRTO				BIT(9)
#define SDMMC_INT_RTO				BIT(8)
#define SDMMC_INT_DCRC				BIT(7)
#define SDMMC_INT_RCRC				BIT(6)
#define SDMMC_INT_RXDR				BIT(5)
#define SDMMC_INT_TXDR				BIT(4)
#define SDMMC_INT_DATA_OVER			BIT(3)
#define SDMMC_INT_CMD_DONE			BIT(2)
#define SDMMC_INT_RESP_ERR			BIT(1)
#define SDMMC_INT_CD				BIT(0)
#define SDMMC_INT_ERROR				0xbfc2

/* Command register defines */
#define SDMMC_CMD_START				BIT(31)
#define SDMMC_CMD_USE_HOLD_REG		BIT(29)
#define SDMMC_CMD_VOLT_SWITCH		BIT(28)
#define SDMMC_CMD_CCS_EXP			BIT(23)
#define SDMMC_CMD_CEATA_RD			BIT(22)
#define SDMMC_CMD_UPD_CLK			BIT(21)
#define SDMMC_CMD_INIT				BIT(15)
#define SDMMC_CMD_STOP				BIT(14)
#define SDMMC_CMD_PRV_DAT_WAIT		BIT(13)
#define SDMMC_CMD_SEND_STOP			BIT(12)
#define SDMMC_CMD_STRM_MODE			BIT(11)
#define SDMMC_CMD_DAT_WR			BIT(10)
#define SDMMC_CMD_DAT_EXP			BIT(9)
#define SDMMC_CMD_RESP_CRC			BIT(8)
#define SDMMC_CMD_RESP_LONG			BIT(7)
#define SDMMC_CMD_RESP_EXP			BIT(6)
#define SDMMC_CMD_INDX(n)			((n) & 0x1F)
/* Status register defines */
#define SDMMC_GET_FCNT(x)			(((x)>>17) & 0x1FFF)
#define SDMMC_STATUS_DMA_REQ		BIT(31)
#define SDMMC_STATUS_BUSY			BIT(9)


#define SDMMC_IDMAC_INT_AI			BIT(9)
#define SDMMC_IDMAC_INT_NI			BIT(8)
#define SDMMC_IDMAC_INT_CES			BIT(5)
#define SDMMC_IDMAC_INT_DU			BIT(4)
#define SDMMC_IDMAC_INT_FBE			BIT(2)
#define SDMMC_IDMAC_INT_RI			BIT(1)
#define SDMMC_IDMAC_INT_TI			BIT(0)
#define SDMMC_IDMAC_ENABLE			BIT(7)
#define SDMMC_IDMAC_FB				BIT(1)
#define SDMMC_IDMAC_SWRESET			BIT(0)

#define SDMMC_CTRL_ALL_RESET_FLAGS (SDMMC_CTRL_RESET | SDMMC_CTRL_FIFO_RESET | SDMMC_CTRL_DMA_RESET)

struct request;
struct mmc_data;
struct mmc_request;

#define MMC_CMD23_ARG_REL_WR	(1 << 31)
#define MMC_CMD23_ARG_PACKED	((0 << 31) | (1 << 30))
#define MMC_CMD23_ARG_TAG_REQ	(1 << 29)
#define MMC_RSP_PRESENT			(1 << 0)
#define MMC_RSP_136				(1 << 1)		/* 136 bit response */
#define MMC_RSP_CRC				(1 << 2)		/* expect valid crc */
#define MMC_RSP_BUSY			(1 << 3)		/* card may send busy */
#define MMC_RSP_OPCODE			(1 << 4)		/* response contains opcode */

#define MMC_CMD_MASK			(3 << 5)		/* non-SPI command type */
#define MMC_CMD_AC				(0 << 5)
#define MMC_CMD_ADTC			(1 << 5)
#define MMC_CMD_BC				(2 << 5)
#define MMC_CMD_BCR				(3 << 5)

#define MMC_RSP_SPI_S1			(1 << 7)		/* one status byte */
#define MMC_RSP_SPI_S2			(1 << 8)		/* second byte */
#define MMC_RSP_SPI_B4			(1 << 9)		/* four data bytes */
#define MMC_RSP_SPI_BUSY (		1 << 10)		/* card may send busy */

#define MMC_RSP_NONE			(0)
#define MMC_RSP_R1	(MMC_RSP_PRESENT|MMC_RSP_CRC|MMC_RSP_OPCODE)
#define MMC_RSP_R1B	(MMC_RSP_PRESENT|MMC_RSP_CRC|MMC_RSP_OPCODE|MMC_RSP_BUSY)
#define MMC_RSP_R2	(MMC_RSP_PRESENT|MMC_RSP_136|MMC_RSP_CRC)
#define MMC_RSP_R3	(MMC_RSP_PRESENT)
#define MMC_RSP_R4	(MMC_RSP_PRESENT)
#define MMC_RSP_R5	(MMC_RSP_PRESENT|MMC_RSP_CRC|MMC_RSP_OPCODE)
#define MMC_RSP_R6	(MMC_RSP_PRESENT|MMC_RSP_CRC|MMC_RSP_OPCODE)
#define MMC_RSP_R7	(MMC_RSP_PRESENT|MMC_RSP_CRC|MMC_RSP_OPCODE)

#define mmc_resp_type(cmd)	((cmd)->flags & (MMC_RSP_PRESENT|MMC_RSP_136|MMC_RSP_CRC|MMC_RSP_BUSY|MMC_RSP_OPCODE))

#define MMC_RSP_SPI_R1	(MMC_RSP_SPI_S1)
#define MMC_RSP_SPI_R1B	(MMC_RSP_SPI_S1|MMC_RSP_SPI_BUSY)
#define MMC_RSP_SPI_R2	(MMC_RSP_SPI_S1|MMC_RSP_SPI_S2)
#define MMC_RSP_SPI_R3	(MMC_RSP_SPI_S1|MMC_RSP_SPI_B4)
#define MMC_RSP_SPI_R4	(MMC_RSP_SPI_S1|MMC_RSP_SPI_B4)
#define MMC_RSP_SPI_R5	(MMC_RSP_SPI_S1|MMC_RSP_SPI_S2)
#define MMC_RSP_SPI_R7	(MMC_RSP_SPI_S1|MMC_RSP_SPI_B4)

#define mmc_spi_resp_type(cmd)	((cmd)->flags & (MMC_RSP_SPI_S1|MMC_RSP_SPI_BUSY|MMC_RSP_SPI_S2|MMC_RSP_SPI_B4))
#define mmc_cmd_type(cmd)	((cmd)->flags & MMC_CMD_MASK)

/* Standard MMC commands (4.1)           type  argument     response */
   /* class 1 */
#define MMC_GO_IDLE_STATE         0   /* bc                          */
#define MMC_SEND_OP_COND          1   /* bcr  [31:0] OCR         R3  */
#define MMC_ALL_SEND_CID          2   /* bcr                     R2  */
#define MMC_SET_RELATIVE_ADDR     3   /* ac   [31:16] RCA        R1  */
#define MMC_SET_DSR               4   /* bc   [31:16] RCA            */
#define MMC_SLEEP_AWAKE		  5   /* ac   [31:16] RCA 15:flg R1b */
#define MMC_SWITCH                6   /* ac   [31:0] See below   R1b */
#define MMC_SELECT_CARD           7   /* ac   [31:16] RCA        R1  */
#define MMC_SEND_EXT_CSD          8   /* adtc                    R1  */
#define MMC_SEND_CSD              9   /* ac   [31:16] RCA        R2  */
#define MMC_SEND_CID             10   /* ac   [31:16] RCA        R2  */
#define MMC_READ_DAT_UNTIL_STOP  11   /* adtc [31:0] dadr        R1  */
#define MMC_STOP_TRANSMISSION    12   /* ac                      R1b */
#define MMC_SEND_STATUS          13   /* ac   [31:16] RCA        R1  */
#define MMC_BUS_TEST_R           14   /* adtc                    R1  */
#define MMC_GO_INACTIVE_STATE    15   /* ac   [31:16] RCA            */
#define MMC_BUS_TEST_W           19   /* adtc                    R1  */
#define MMC_SPI_READ_OCR         58   /* spi                  spi_R3 */
#define MMC_SPI_CRC_ON_OFF       59   /* spi  [0:0] flag      spi_R1 */

  /* class 2 */
#define MMC_SET_BLOCKLEN         16   /* ac   [31:0] block len   R1  */
#define MMC_READ_SINGLE_BLOCK    17   /* adtc [31:0] data addr   R1  */
#define MMC_READ_MULTIPLE_BLOCK  18   /* adtc [31:0] data addr   R1  */
#define MMC_SEND_TUNING_BLOCK    19   /* adtc                    R1  */
#define MMC_SEND_TUNING_BLOCK_HS200	21	/* adtc R1  */

  /* class 3 */
#define MMC_WRITE_DAT_UNTIL_STOP 20   /* adtc [31:0] data addr   R1  */

  /* class 4 */
#define MMC_SET_BLOCK_COUNT      23   /* adtc [31:0] data addr   R1  */
#define MMC_WRITE_BLOCK          24   /* adtc [31:0] data addr   R1  */
#define MMC_WRITE_MULTIPLE_BLOCK 25   /* adtc                    R1  */
#define MMC_PROGRAM_CID          26   /* adtc                    R1  */
#define MMC_PROGRAM_CSD          27   /* adtc                    R1  */

  /* class 6 */
#define MMC_SET_WRITE_PROT       28   /* ac   [31:0] data addr   R1b */
#define MMC_CLR_WRITE_PROT       29   /* ac   [31:0] data addr   R1b */
#define MMC_SEND_WRITE_PROT      30   /* adtc [31:0] wpdata addr R1  */

  /* class 5 */
#define MMC_ERASE_GROUP_START    35   /* ac   [31:0] data addr   R1  */
#define MMC_ERASE_GROUP_END      36   /* ac   [31:0] data addr   R1  */
#define MMC_ERASE                38   /* ac                      R1b */

  /* class 9 */
#define MMC_FAST_IO              39   /* ac   <Complex>          R4  */
#define MMC_GO_IRQ_STATE         40   /* bcr                     R5  */

  /* class 7 */
#define MMC_LOCK_UNLOCK          42   /* adtc                    R1b */

  /* class 8 */
#define MMC_APP_CMD              55   /* ac   [31:16] RCA        R1  */
#define MMC_GEN_CMD              56   /* adtc [0] RD/WR          R1  */

/*
 * MMC_SWITCH argument format:
 *
 *	[31:26] Always 0
 *	[25:24] Access Mode
 *	[23:16] Location of target Byte in EXT_CSD
 *	[15:08] Value Byte
 *	[07:03] Always 0
 *	[02:00] Command Set
 */

/*
  MMC status in R1, for native mode (SPI bits are different)
  Type
	e : error bit
	s : status bit
	r : detected and set for the actual command response
	x : detected and set during command execution. the host must poll
            the card by sending status command in order to read these bits.
  Clear condition
	a : according to the card state
	b : always related to the previous command. Reception of
            a valid command will clear it (with a delay of one command)
	c : clear by read
 */

#define R1_OUT_OF_RANGE			(1 << 31)	/* er, c */
#define R1_ADDRESS_ERROR		(1 << 30)	/* erx, c */
#define R1_BLOCK_LEN_ERROR		(1 << 29)	/* er, c */
#define R1_ERASE_SEQ_ERROR  	 (1 << 28)	/* er, c */
#define R1_ERASE_PARAM			(1 << 27)	/* ex, c */
#define R1_WP_VIOLATION			(1 << 26)	/* erx, c */
#define R1_CARD_IS_LOCKED		(1 << 25)	/* sx, a */
#define R1_LOCK_UNLOCK_FAILED	(1 << 24)	/* erx, c */
#define R1_COM_CRC_ERROR		(1 << 23)	/* er, b */
#define R1_ILLEGAL_COMMAND		(1 << 22)	/* er, b */
#define R1_CARD_ECC_FAILED		(1 << 21)	/* ex, c */
#define R1_CC_ERROR				(1 << 20)	/* erx, c */
#define R1_ERROR				(1 << 19)	/* erx, c */
#define R1_UNDERRUN				(1 << 18)	/* ex, c */
#define R1_OVERRUN				(1 << 17)	/* ex, c */
#define R1_CID_CSD_OVERWRITE	(1 << 16)	/* erx, c, CID/CSD overwrite */
#define R1_WP_ERASE_SKIP		(1 << 15)	/* sx, c */
#define R1_CARD_ECC_DISABLED	(1 << 14)	/* sx, a */
#define R1_ERASE_RESET			(1 << 13)	/* sr, c */
#define R1_STATUS(x)            (x & 0xFFFFE000)
#define R1_CURRENT_STATE(x)		((x & 0x00001E00) >> 9)	/* sx, b (4 bits) */
#define R1_READY_FOR_DATA		(1 << 8)	/* sx, a */
#define R1_SWITCH_ERROR			(1 << 7)	/* sx, c */
#define R1_EXCEPTION_EVENT		(1 << 6)	/* sr, a */
#define R1_APP_CMD				(1 << 5)	/* sr, c */

#define R1_STATE_IDLE	0
#define R1_STATE_READY	1
#define R1_STATE_IDENT	2
#define R1_STATE_STBY	3
#define R1_STATE_TRAN	4
#define R1_STATE_DATA	5
#define R1_STATE_RCV	6
#define R1_STATE_PRG	7
#define R1_STATE_DIS	8

/*
 * MMC/SD in SPI mode reports R1 status always, and R2 for SEND_STATUS
 * R1 is the low order byte; R2 is the next highest byte, when present.
 */
#define R1_SPI_IDLE				(1 << 0)
#define R1_SPI_ERASE_RESET		(1 << 1)
#define R1_SPI_ILLEGAL_COMMAND	(1 << 2)
#define R1_SPI_COM_CRC			(1 << 3)
#define R1_SPI_ERASE_SEQ		(1 << 4)
#define R1_SPI_ADDRESS			(1 << 5)
#define R1_SPI_PARAMETER		(1 << 6)
/* R1 bit 7 is always zero */
#define R2_SPI_CARD_LOCKED		(1 << 8)
#define R2_SPI_WP_ERASE_SKIP	(1 << 9)	/* or lock/unlock fail */
#define R2_SPI_LOCK_UNLOCK_FAIL	R2_SPI_WP_ERASE_SKIP
#define R2_SPI_ERROR			(1 << 10)
#define R2_SPI_CC_ERROR			(1 << 11)
#define R2_SPI_CARD_ECC_ERROR	(1 << 12)
#define R2_SPI_WP_VIOLATION		(1 << 13)
#define R2_SPI_ERASE_PARAM		(1 << 14)
#define R2_SPI_OUT_OF_RANGE		(1 << 15)	/* or CSD overwrite */
#define R2_SPI_CSD_OVERWRITE	R2_SPI_OUT_OF_RANGE


/* SDIO commands                         type  argument     response */
#define SD_IO_SEND_OP_COND          5 /* bcr  [23:0] OCR         R4  */
#define SD_IO_RW_DIRECT            52 /* ac   [31:0] See below   R5  */
#define SD_IO_RW_EXTENDED          53 /* adtc [31:0] See below   R5  */

/*
 * SD_IO_RW_DIRECT argument format:
 *
 *      [31] R/W flag
 *      [30:28] Function number
 *      [27] RAW flag
 *      [25:9] Register address
 *      [7:0] Data
 */

/*
 * SD_IO_RW_EXTENDED argument format:
 *
 *      [31] R/W flag
 *      [30:28] Function number
 *      [27] Block mode
 *      [26] Increment address
 *      [25:9] Register address
 *      [8:0] Byte/block count
 */

#define R4_18V_PRESENT (1<<24)
#define R4_MEMORY_PRESENT (1 << 27)

/*
  SDIO status in R5
  Type
	e : error bit
	s : status bit
	r : detected and set for the actual command response
	x : detected and set during command execution. the host must poll
            the card by sending status command in order to read these bits.
  Clear condition
	a : according to the card state
	b : always related to the previous command. Reception of
            a valid command will clear it (with a delay of one command)
	c : clear by read
 */

#define R5_COM_CRC_ERROR	(1 << 15)	/* er, b */
#define R5_ILLEGAL_COMMAND	(1 << 14)	/* er, b */
#define R5_ERROR		(1 << 11)	/* erx, c */
#define R5_FUNCTION_NUMBER	(1 << 9)	/* er, c */
#define R5_OUT_OF_RANGE		(1 << 8)	/* er, c */
#define R5_STATUS(x)		(x & 0xCB00)
#define R5_IO_CURRENT_STATE(x)	((x & 0x3000) >> 12) /* s, b */

/*
 * Card Common Control Registers (CCCR)
 */

#define SDIO_CCCR_CCCR		0x00

#define  SDIO_CCCR_REV_1_00	0	/* CCCR/FBR Version 1.00 */
#define  SDIO_CCCR_REV_1_10	1	/* CCCR/FBR Version 1.10 */
#define  SDIO_CCCR_REV_1_20	2	/* CCCR/FBR Version 1.20 */
#define  SDIO_CCCR_REV_3_00	3	/* CCCR/FBR Version 3.00 */

#define  SDIO_SDIO_REV_1_00	0	/* SDIO Spec Version 1.00 */
#define  SDIO_SDIO_REV_1_10	1	/* SDIO Spec Version 1.10 */
#define  SDIO_SDIO_REV_1_20	2	/* SDIO Spec Version 1.20 */
#define  SDIO_SDIO_REV_2_00	3	/* SDIO Spec Version 2.00 */
#define  SDIO_SDIO_REV_3_00	4	/* SDIO Spec Version 3.00 */

#define SDIO_CCCR_SD		0x01

#define  SDIO_SD_REV_1_01	0	/* SD Physical Spec Version 1.01 */
#define  SDIO_SD_REV_1_10	1	/* SD Physical Spec Version 1.10 */
#define  SDIO_SD_REV_2_00	2	/* SD Physical Spec Version 2.00 */
#define  SDIO_SD_REV_3_00	3	/* SD Physical Spev Version 3.00 */

#define SDIO_CCCR_IOEx		0x02
#define SDIO_CCCR_IORx		0x03

#define SDIO_CCCR_IENx		0x04	/* Function/Master Interrupt Enable */
#define SDIO_CCCR_INTx		0x05	/* Function Interrupt Pending */

#define SDIO_CCCR_ABORT		0x06	/* function abort/card reset */

#define SDIO_CCCR_IF		0x07	/* bus interface controls */

#define  SDIO_BUS_WIDTH_MASK	0x03	/* data bus width setting */
#define  SDIO_BUS_WIDTH_1BIT	0x00
#define  SDIO_BUS_WIDTH_RESERVED 0x01
#define  SDIO_BUS_WIDTH_4BIT	0x02
#define  SDIO_BUS_ECSI		0x20	/* Enable continuous SPI interrupt */
#define  SDIO_BUS_SCSI		0x40	/* Support continuous SPI interrupt */

#define  SDIO_BUS_ASYNC_INT	0x20

#define  SDIO_BUS_CD_DISABLE     0x80	/* disable pull-up on DAT3 (pin 1) */

#define SDIO_CCCR_CAPS		0x08

#define  SDIO_CCCR_CAP_SDC	0x01	/* can do CMD52 while data transfer */
#define  SDIO_CCCR_CAP_SMB	0x02	/* can do multi-block xfers (CMD53) */
#define  SDIO_CCCR_CAP_SRW	0x04	/* supports read-wait protocol */
#define  SDIO_CCCR_CAP_SBS	0x08	/* supports suspend/resume */
#define  SDIO_CCCR_CAP_S4MI	0x10	/* interrupt during 4-bit CMD53 */
#define  SDIO_CCCR_CAP_E4MI	0x20	/* enable ints during 4-bit CMD53 */
#define  SDIO_CCCR_CAP_LSC	0x40	/* low speed card */
#define  SDIO_CCCR_CAP_4BLS	0x80	/* 4 bit low speed card */

#define SDIO_CCCR_CIS		0x09	/* common CIS pointer (3 bytes) */

/* Following 4 regs are valid only if SBS is set */
#define SDIO_CCCR_SUSPEND	0x0c
#define SDIO_CCCR_SELx		0x0d
#define SDIO_CCCR_EXECx		0x0e
#define SDIO_CCCR_READYx	0x0f

#define SDIO_CCCR_BLKSIZE	0x10

#define SDIO_CCCR_POWER		0x12

#define  SDIO_POWER_SMPC	0x01	/* Supports Master Power Control */
#define  SDIO_POWER_EMPC	0x02	/* Enable Master Power Control */

#define SDIO_CCCR_SPEED		0x13

#define  SDIO_SPEED_SHS		0x01	/* Supports High-Speed mode */
#define  SDIO_SPEED_BSS_SHIFT	1
#define  SDIO_SPEED_BSS_MASK	(7<<SDIO_SPEED_BSS_SHIFT)
#define  SDIO_SPEED_SDR12	(0<<SDIO_SPEED_BSS_SHIFT)
#define  SDIO_SPEED_SDR25	(1<<SDIO_SPEED_BSS_SHIFT)
#define  SDIO_SPEED_SDR50	(2<<SDIO_SPEED_BSS_SHIFT)
#define  SDIO_SPEED_SDR104	(3<<SDIO_SPEED_BSS_SHIFT)
#define  SDIO_SPEED_DDR50	(4<<SDIO_SPEED_BSS_SHIFT)
#define  SDIO_SPEED_EHS		SDIO_SPEED_SDR25	/* Enable High-Speed */

#define SDIO_CCCR_UHS		0x14
#define  SDIO_UHS_SDR50		0x01
#define  SDIO_UHS_SDR104	0x02
#define  SDIO_UHS_DDR50		0x04

#define SDIO_CCCR_DRIVE_STRENGTH 0x15
#define  SDIO_SDTx_MASK		0x07
#define  SDIO_DRIVE_SDTA	(1<<0)
#define  SDIO_DRIVE_SDTC	(1<<1)
#define  SDIO_DRIVE_SDTD	(1<<2)
#define  SDIO_DRIVE_DTSx_MASK	0x03
#define  SDIO_DRIVE_DTSx_SHIFT	4
#define  SDIO_DTSx_SET_TYPE_B	(0 << SDIO_DRIVE_DTSx_SHIFT)
#define  SDIO_DTSx_SET_TYPE_A	(1 << SDIO_DRIVE_DTSx_SHIFT)
#define  SDIO_DTSx_SET_TYPE_C	(2 << SDIO_DRIVE_DTSx_SHIFT)
#define  SDIO_DTSx_SET_TYPE_D	(3 << SDIO_DRIVE_DTSx_SHIFT)
/*
 * Function Basic Registers (FBR)
 */

#define SDIO_FBR_BASE(f)	((f) * 0x100) /* base of function f's FBRs */

#define SDIO_FBR_STD_IF		0x00

#define  SDIO_FBR_SUPPORTS_CSA	0x40	/* supports Code Storage Area */
#define  SDIO_FBR_ENABLE_CSA	0x80	/* enable Code Storage Area */

#define SDIO_FBR_STD_IF_EXT	0x01

#define SDIO_FBR_POWER		0x02

#define  SDIO_FBR_POWER_SPS	0x01	/* Supports Power Selection */
#define  SDIO_FBR_POWER_EPS	0x02	/* Enable (low) Power Selection */

#define SDIO_FBR_CIS		0x09	/* CIS pointer (3 bytes) */


#define SDIO_FBR_CSA		0x0C	/* CSA pointer (3 bytes) */

#define SDIO_FBR_CSA_DATA	0x0F

#define SDIO_FBR_BLKSIZE	0x10	/* block size (2 bytes) */


struct mmc_command {
	u32		opcode;
	u32		arg;
	u32		resp[4];
	u32		flags;		/* expected response type */
	u32		retries;	/* max number of retries */
	int		error;		/* command error */
	u32		busy_timeout;	/* busy detect timeout in ms */
	s8				sanitize_busy;
	struct mmc_data		*data;		/* data segment associated with cmd */
	struct mmc_request	*mrq;		/* associated request */
};

#define MMC_DATA_WRITE	(1 << 8)
#define MMC_DATA_READ	(1 << 9)
#define MMC_DATA_STREAM	(1 << 10)

struct mmc_data {
	unsigned int		timeout_ns;	/* data timeout (in ns, max 80ms) */
	unsigned int		timeout_clks;	/* data timeout (in clocks) */
	unsigned int		blksz;		/* data block size */
	unsigned int		blocks;		/* number of blocks */
	int					error;		/* data error */
	unsigned int		flags;
	unsigned int		bytes_xfered;
	struct mmc_command	*stop;			/* stop command */
	struct mmc_request	*mrq;			/* associated request */
	unsigned int		sg_len;			/* size of scatter list */
	int					sg_count;		/* mapped sg entries */
	struct scatterlist	*sg;			/* I/O scatter list */
	s32					host_cookie;	/* host private data */
};

struct mmc_host;
struct mmc_request {
	struct mmc_command	*sbc;		/* SET_BLOCK_COUNT for multiblock */
	struct mmc_command	*cmd;
	struct mmc_data		*data;
	struct mmc_command	*stop;
	//struct completion	completion;
	void				(*done)(struct mmc_request *);/* completion function */
	struct 				mmc_host		*host;
	u64					io_start;
#ifdef CONFIG_BLOCK
	int			lat_hist_enabled;
#endif
};

int sdmmc_init();

#endif