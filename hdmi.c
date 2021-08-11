#include "hdmi.h"
#include "grf.h"
#include "printf.h"

int inno_hdmi_phy_rk3328_pre_pll_update(){
	//inno_hdmi_phy_rk3328_pre_pll_update
	HDMIPHY_REG_UPD(0xa0,1,0x1);
	HDMIPHY_REG_UPD(0xa0,2,0x0);
	HDMIPHY_REGW(0xa1) = 0x1;
	HDMIPHY_REGW(0xa2) = 0xf0;
	HDMIPHY_REGW(0xa3) = 0x5a;
	HDMIPHY_REGW(0xa5) = 0x1;
	HDMIPHY_REGW(0xa6) = 0x5;
	HDMIPHY_REGW(0xa4) = 0x30;
	HDMIPHY_REGW(0xd3) = 0x0;
	HDMIPHY_REGW(0xd2) = 0x0;
	HDMIPHY_REGW(0xd1) = 0x0;
	HDMIPHY_REG_UPD(0xa0,1,0x0);
	return 0;
}

int inno_hdmi_phy_rk3328_power_off(){
	HDMIPHY_REGW(0xb2) = 0;
	HDMIPHY_REG_UPD(0xb0,4,0);
	HDMIPHY_REG_UPD(0xaa,1,1);
	HDMIPHY_REGW(0x05) = 0;
	HDMIPHY_REGW(0x07) = 0;
	return 0;
}

int inno_hdmi_phy_rk3328_init(){
	REGW(GRF_BASE+RK3328_GRF_SOC_CON4)=RK3328_IO_3V_DOMAIN|RK3328_HPD_3V;
	REGW(GRF_BASE+RK3328_GRF_SOC_CON3)=RK3328_IO_CTRL_BY_HDMI;
	REGW(GRF_BASE+RK3328_GRF_SOC_CON2)=RK3328_DDC_MASK_EN|BIT(18);

	HDMIPHY_REGW(0x1) = 7;
	HDMIPHY_REGW(0x2) = 0x91;
	if ((HDMIPHY_REGW(0xc8) & 0xc0))
		inno_hdmi_phy_rk3328_power_off();
	return 0;
}

int inno_hdmi_phy_rk3328_power_on(){
	HDMIPHY_REG_UPD(02,1,0);
	HDMIPHY_REG_UPD(0xaa,1,1);
	HDMIPHY_REGW(0xac) = 0x28;

	HDMIPHY_REGW(0xad)=1;
	HDMIPHY_REGW(0xab)=2;
	HDMIPHY_REGW(0xaa)= 0x0e;

	//regs
	{
		u8 regs[]={0x07, 0x0a, 0x0a, 0x0a, 0x00, 0x00, 0x08, 0x08, 0x08,0x00, 0xac, 0xcc, 0xcc, 0xcc};

		for (u8 val = 0; val < 14; val++)
			HDMIPHY_REGW(0xb5 + val)= regs[val];
	}

	HDMIPHY_REGW(0xc8) = 0;
	HDMIPHY_REGW(0xc9) = 0;
	HDMIPHY_REGW(0xca) = 0;
	HDMIPHY_REGW(0xcb) = 0;

	HDMIPHY_REGW(0xc5) = 0x81;
	HDMIPHY_REGW(0xc9) = 0x10;
	HDMIPHY_REGW(0xca) = 0x10;
	HDMIPHY_REGW(0xcb) = 0x10;

	HDMIPHY_REGW(0xd8)= 1;
	HDMIPHY_REGW(0xd9)= 0xb8;

	HDMIPHY_REG_UPD(0xaa,1,0);
	HDMIPHY_REG_UPD(0xb0,4,4);
	HDMIPHY_REGW(0xb2) = 0xf;

	{
		u8 val;

		for (val = 0; val < 5; val++) {
			if (HDMIPHY_REGW(0xaf) & 1)
				break;
			udelay(10000);
		}
		if (!(HDMIPHY_REGW(0xaf) & 1))
			printf("HDMI PHY Post PLL unlock\n");
	}
	HDMIPHY_REG_UPD(0x02, 1, 1);
	HDMIPHY_REGW(0x05) = 0x22;
	HDMIPHY_REGW(0x07) = 0x22;
	return 0;
}

int initialize_hdmi_ih_mutes(){
	HDMI_REGW(HDMI_IH_MUTE) |= 3;

	HDMI_REGW(HDMI_VP_MASK) = 0xff;
	HDMI_REGW(HDMI_FC_MASK0) = 0xff;
	HDMI_REGW(HDMI_FC_MASK1) = 0xff;
	HDMI_REGW(HDMI_FC_MASK2) = 0xff;
	HDMI_REGW(HDMI_PHY_MASK0) =  0xFF;
	HDMI_REGW(HDMI_PHY_I2CM_INT_ADDR) = 0xFF;
	HDMI_REGW(HDMI_PHY_I2CM_CTLINT_ADDR) = 0xFF;
	HDMI_REGW(HDMI_AUD_INT) = 0xFF;
	HDMI_REGW(HDMI_AUD_SPDIFINT) = 0xFF;
	HDMI_REGW(HDMI_AUD_HBR_MASK) = 0xFF;
	HDMI_REGW(HDMI_GP_MASK) = 0xFF;
	HDMI_REGW(HDMI_A_APIINTMSK)= 0xff;
	HDMI_REGW(HDMI_I2CM_CTLINT) = 0xFF;
	HDMI_REGW(HDMI_IH_MUTE_FC_STAT0)= 0xff;
	HDMI_REGW(HDMI_IH_MUTE_FC_STAT1)= 0xff;
	HDMI_REGW(HDMI_IH_MUTE_FC_STAT2)= 0xff;
	HDMI_REGW(HDMI_IH_MUTE_AS_STAT0)= 0xff;
	HDMI_REGW(HDMI_IH_MUTE_PHY_STAT0)= 0xff;
	HDMI_REGW(HDMI_IH_MUTE_I2CM_STAT0)= 0xff;
	HDMI_REGW(HDMI_IH_MUTE_CEC_STAT0)= 0xff;
	HDMI_REGW(HDMI_IH_MUTE_VP_STAT0)= 0xff;
	HDMI_REGW(HDMI_IH_MUTE_I2CMPHY_STAT0)= 0xff;
	HDMI_REGW(HDMI_IH_MUTE_AHBDMAAUD_STAT0)= 0xff;

	HDMI_REGW(HDMI_IH_MUTE) &= ~3;
	return 0;
}

int dw_hdmi_i2c_init(){
	HDMI_REGW(HDMI_I2CM_SOFTRSTZ) = 0x00;
	//HDMI_REG_SET(HDMI_I2CM_DIV,1,HDMI_I2CM_DIV_FAST_STD_MODE,HDMI_I2CM_DIV_STD_MODE);
	HDMI_REGW(HDMI_I2CM_DIV) = 0x3;
	HDMI_REGW(HDMI_I2CM_INT) = HDMI_I2CM_INT_DONE_POL;
	HDMI_REGW(HDMI_I2CM_CTLINT) = HDMI_I2CM_CTLINT_NAC_POL | HDMI_I2CM_CTLINT_ARB_POL;
	HDMI_REGW(HDMI_IH_I2CM_STAT0) = HDMI_IH_I2CM_STAT0_ERROR | HDMI_IH_I2CM_STAT0_DONE;
	HDMI_REGW(HDMI_IH_MUTE_I2CM_STAT0) = HDMI_IH_I2CM_STAT0_ERROR | HDMI_IH_I2CM_STAT0_DONE;
	HDMI_REGW(HDMI_I2CM_SDA_HOLD) = 0x48;
//dw_hdmi_i2c_set_divs
	HDMI_REGW(HDMI_I2CM_SS_SCL_HCNT_0_ADDR) = 0xe7;
	HDMI_REGW(HDMI_I2CM_SS_SCL_HCNT_1_ADDR) = 0;
	HDMI_REGW(HDMI_I2CM_SS_SCL_LCNT_0_ADDR) = 0xe0;
	HDMI_REGW(HDMI_I2CM_SS_SCL_LCNT_1_ADDR) = 0;
	return 0;
}

static int hdmi_wait_i2c_done(struct i2c *i2c,u32 msec){
	while(msec) {
		u32 w = msec > 100 ? 100 : msec;
		udelay(w);
		i2c->stat = HDMI_REGW(HDMI_IH_I2CM_STAT0);
		if (i2c->stat)
			HDMI_REGW(HDMI_IH_I2CM_STAT0) = i2c->stat;
		if (i2c->stat & (HDMI_IH_I2CM_STAT0_DONE | HDMI_IH_I2CM_STAT0_ERROR))
			return i2c->stat;
		msec -= w;
	}
	return 0;
}

static int hdmi_i2c_read(struct i2c *i2c, unsigned char *buf, unsigned int length){
	int stat;

	if (!i2c->is_regaddr) {
		i2c->slave_reg = 0x00;
		i2c->is_regaddr = 1;
	}

	while (length--) {
		HDMI_REGW(HDMI_I2CM_ADDRESS) = i2c->slave_reg++;
		if (i2c->is_segment)
			HDMI_REGW(HDMI_I2CM_OPERATION) = HDMI_I2CM_OPERATION_READ_EXT;
		else
			HDMI_REGW(HDMI_I2CM_OPERATION) = HDMI_I2CM_OPERATION_READ;
		stat = hdmi_wait_i2c_done(i2c, 1000);
		if (!stat)
			return -1;
		if (i2c->stat & HDMI_IH_I2CM_STAT0_ERROR)
			return -2;
		*buf++ = HDMI_REGW(HDMI_I2CM_DATAI);
	}
	i2c->is_segment = 0;
	return 0;
}

static int hdmi_i2c_write(struct i2c *i2c,unsigned char *buf, unsigned int length){
	int stat;

	if (!i2c->is_regaddr) {
		i2c->slave_reg = buf[0];
		length--;
		buf++;
		i2c->is_regaddr = 1;
	}
	while (length--) {
		HDMI_REGW(HDMI_I2CM_DATAO) = *buf++;
		HDMI_REGW(HDMI_I2CM_ADDRESS) = i2c->slave_reg++;
		HDMI_REGW(HDMI_I2CM_OPERATION) = HDMI_I2CM_OPERATION_WRITE;
		stat = hdmi_wait_i2c_done(i2c,1000);
		if (!stat)
			return -1;
		if (i2c->stat & HDMI_IH_I2CM_STAT0_ERROR)
			return -2;
	}
	return 0;
}

int hdmi_i2c_xfer(struct i2c_msg *msgs, int num){
	u8 addr = msgs[0].addr;
	int i, ret;
	struct i2c i2c={0};

	for (i = 0; i < num; i++) {
		if (msgs[i].len == 0)
			return -4;
	}
	ret = 0;
	HDMI_REGW(HDMI_IH_MUTE_I2CM_STAT0) = 0;
	if (addr == DDC_SEGMENT_ADDR && msgs[0].len == 1)
		addr = DDC_ADDR;
	HDMI_REGW(HDMI_I2CM_SLAVE) = addr;

	for (i = 0; i < num; i++) {
		if (msgs[i].addr == DDC_SEGMENT_ADDR && msgs[i].len == 1) {
			i2c.is_segment = 1;
			HDMI_REGW(HDMI_I2CM_SEGADDR) = DDC_SEGMENT_ADDR;
			HDMI_REGW(HDMI_I2CM_SEGPTR) = *msgs[i].buf;
		}
		else {
			if (msgs[i].flags & I2C_M_RD)
				ret = hdmi_i2c_read(&i2c,msgs[i].buf, msgs[i].len);
			else
				ret = hdmi_i2c_write(&i2c,msgs[i].buf,msgs[i].len);
		}
		if (ret < 0)
			break;
	}
	if (!ret)
		ret = num;
	HDMI_REGW(HDMI_IH_MUTE_I2CM_STAT0) = HDMI_IH_I2CM_STAT0_ERROR | HDMI_IH_I2CM_STAT0_DONE;
	return ret;
}

int drm_edid_header_is_valid(const u8 *raw_edid){
	int i, score = 0;
	u8 edid_header[] = {0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00};

	for (i = 0; i < sizeof(edid_header); i++)
		if (raw_edid[i] == edid_header[i])
			score++;
	return score;
}

struct edid *drm_do_get_edid(u8 *data){
	int i, j = 0, valid_extensions = 0;
	u8 *block, *new;

	if (drm_do_probe_ddc_edid(data, 0, HDMI_EDID_LEN))
		return NULL;
	printf("drm_do_get_edid %d %d\n",drm_edid_header_is_valid(data),data[0x7e]);
	if (data[0x7e] == 0)
		return (struct edid *)data;
	return NULL;
}

int drm_do_probe_ddc_edid(u8 *buf, unsigned int block, int len){
	unsigned char start = block * HDMI_EDID_LEN;
	unsigned char segment = block >> 1;
	unsigned char xfers = segment ? 3 : 2;
	int ret, retries = 5;

	if(HDMI_REGW(HDMI_PHY_STAT0) & HDMI_PHY_HPD)
		REGW(GRF_BASE+RK3328_GRF_SOC_CON4)=RK3328_IO_5V_DOMAIN;
	else
		REGW(GRF_BASE+RK3328_GRF_SOC_CON4)=RK3328_IO_3V_DOMAIN;

	do {
		struct i2c_msg msgs[] = {
			{
				.addr	= DDC_SEGMENT_ADDR,
				.flags	= 0,
				.len	= 1,
				.buf	= &segment,
			}, {
				.addr	= DDC_ADDR,
				.flags	= 0,
				.len	= 1,
				.buf	= &start,
			}, {
				.addr	= DDC_ADDR,
				.flags	= I2C_M_RD,
				.len	= len,
				.buf	= buf,
			}
		};
		ret = hdmi_i2c_xfer(&msgs[3 - xfers],xfers);
	} while (ret != xfers && --retries);
	return ret == xfers ? 0 : -1;
}