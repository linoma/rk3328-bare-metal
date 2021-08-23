#include "main.h"

#ifndef __HDMIH__
#define __HDMIH__


#define EDID_I2C_MIN_SS_SCL_HIGH_TIME	9625
#define EDID_I2C_MIN_SS_SCL_LOW_TIME	10000

#define HDMI_PHY_CONF0                          0x3000
#define HDMI_PHY_TST0                           0x3001
#define HDMI_PHY_TST1                           0x3002
#define HDMI_PHY_TST2                           0x3003
#define HDMI_PHY_STAT0                          0x3004
#define HDMI_PHY_INT0                           0x3005
#define HDMI_PHY_MASK0                          0x3006
#define HDMI_PHY_POL0                           0x3007

#define HDMI_IH_MUTE_FC_STAT0					0x0180
#define HDMI_IH_MUTE_FC_STAT1					0x0181
#define HDMI_IH_MUTE_FC_STAT2					0x0182
#define HDMI_IH_MUTE_AS_STAT0					0x0183
#define HDMI_IH_MUTE_PHY_STAT0					0x0184
#define HDMI_IH_MUTE_I2CM_STAT0					0x0185
#define HDMI_IH_MUTE_CEC_STAT0					0x0186
#define HDMI_IH_MUTE_VP_STAT0					0x0187
#define HDMI_IH_MUTE_I2CMPHY_STAT0				0x0188
#define HDMI_IH_MUTE_AHBDMAAUD_STAT0			0x0189
#define HDMI_IH_MUTE							0x01ff
#define HDMI_TX_INVID0                          0x0200
#define HDMI_TX_INSTUFFING                      0x0201
#define HDMI_TX_GYDATA0                         0x0202
#define HDMI_TX_GYDATA1                         0x0203
#define HDMI_TX_RCRDATA0                        0x0204
#define HDMI_TX_RCRDATA1                        0x0205
#define HDMI_TX_BCBDATA0                        0x0206
#define HDMI_TX_BCBDATA1                        0x0207

#define	HDMI_A_APIINTMSK						0x5008

#define HDMI_FC_DBGFORCE			0x1200
#define	HDMI_FC_GCP				0x1018

#define	FC_DBGTMDS0			0x1219
#define	FC_DBGTMDS1			0x121a
#define	FC_DBGTMDS2			0x121b

#define HDMI_DESIGN_ID                          0x0000
#define HDMI_REVISION_ID                        0x0001
#define HDMI_PRODUCT_ID0                        0x0002
#define HDMI_PRODUCT_ID1                        0x0003
#define HDMI_CONFIG0_ID                         0x0004
#define HDMI_CONFIG1_ID                         0x0005
#define HDMI_CONFIG2_ID                         0x0006
#define HDMI_CONFIG3_ID                         0x0007

#define HDMI_IH_I2CMPHY_STAT0                   0x0108

#define HDMI_VP_STATUS                          0x0800
#define HDMI_VP_PR_CD                           0x0801
#define HDMI_VP_STUFF                           0x0802
#define HDMI_VP_REMAP                           0x0803
#define HDMI_VP_CONF                            0x0804
#define HDMI_VP_STAT                            0x0805
#define HDMI_VP_INT                             0x0806
#define HDMI_VP_MASK                            0x0807
#define HDMI_VP_POL                             0x0808

#define HDMI_FC_INVIDCONF                       0x1000
#define HDMI_FC_INHACTV0                        0x1001
#define HDMI_FC_INHACTV1                        0x1002
#define HDMI_FC_INHBLANK0                       0x1003
#define HDMI_FC_INHBLANK1                       0x1004
#define HDMI_FC_INVACTV0                        0x1005
#define HDMI_FC_INVACTV1                        0x1006
#define HDMI_FC_INVBLANK                        0x1007
#define HDMI_FC_HSYNCINDELAY0                   0x1008
#define HDMI_FC_HSYNCINDELAY1                   0x1009
#define HDMI_FC_HSYNCINWIDTH0                   0x100A
#define HDMI_FC_HSYNCINWIDTH1                   0x100B
#define HDMI_FC_VSYNCINDELAY                    0x100C
#define HDMI_FC_VSYNCINWIDTH                    0x100D
#define HDMI_FC_INFREQ0                         0x100E
#define HDMI_FC_INFREQ1                         0x100F
#define HDMI_FC_INFREQ2                         0x1010
#define HDMI_FC_CTRLDUR                         0x1011
#define HDMI_FC_EXCTRLDUR                       0x1012
#define HDMI_FC_EXCTRLSPAC                      0x1013
#define HDMI_FC_CH0PREAM                        0x1014
#define HDMI_FC_CH1PREAM                        0x1015
#define HDMI_FC_CH2PREAM                        0x1016
#define HDMI_FC_AVICONF3                        0x1017
#define HDMI_FC_GCP                             0x1018
#define HDMI_FC_AVICONF0                        0x1019
#define HDMI_FC_AVICONF1                        0x101A
#define HDMI_FC_AVICONF2                        0x101B
#define HDMI_FC_AVIVID                          0x101C
#define HDMI_FC_AVIETB0                         0x101D
#define HDMI_FC_AVIETB1                         0x101E
#define HDMI_FC_AVISBB0                         0x101F
#define HDMI_FC_AVISBB1                         0x1020
#define HDMI_FC_AVIELB0                         0x1021
#define HDMI_FC_AVIELB1                         0x1022
#define HDMI_FC_AVISRB0                         0x1023
#define HDMI_FC_AVISRB1                         0x1024
#define HDMI_FC_AUDICONF0                       0x1025
#define HDMI_FC_AUDICONF1                       0x1026
#define HDMI_FC_AUDICONF2                       0x1027
#define HDMI_FC_AUDICONF3                       0x1028
#define HDMI_FC_VSDIEEEID0                      0x1029
#define HDMI_FC_VSDSIZE                         0x102A
#define HDMI_FC_VSDIEEEID1                      0x1030
#define HDMI_FC_VSDIEEEID2                      0x1031
#define HDMI_FC_VSDPAYLOAD0                     0x1032
#define HDMI_FC_VSDPAYLOAD1                     0x1033
#define HDMI_FC_VSDPAYLOAD2                     0x1034
#define HDMI_FC_VSDPAYLOAD3                     0x1035
#define HDMI_FC_VSDPAYLOAD4                     0x1036
#define HDMI_FC_VSDPAYLOAD5                     0x1037
#define HDMI_FC_VSDPAYLOAD6                     0x1038
#define HDMI_FC_VSDPAYLOAD7                     0x1039
#define HDMI_FC_VSDPAYLOAD8                     0x103A
#define HDMI_FC_VSDPAYLOAD9                     0x103B
#define HDMI_FC_VSDPAYLOAD10                    0x103C
#define HDMI_FC_VSDPAYLOAD11                    0x103D
#define HDMI_FC_VSDPAYLOAD12                    0x103E
#define HDMI_FC_VSDPAYLOAD13                    0x103F
#define HDMI_FC_VSDPAYLOAD14                    0x1040
#define HDMI_FC_VSDPAYLOAD15                    0x1041
#define HDMI_FC_VSDPAYLOAD16                    0x1042
#define HDMI_FC_VSDPAYLOAD17                    0x1043
#define HDMI_FC_VSDPAYLOAD18                    0x1044
#define HDMI_FC_VSDPAYLOAD19                    0x1045
#define HDMI_FC_VSDPAYLOAD20                    0x1046
#define HDMI_FC_VSDPAYLOAD21                    0x1047
#define HDMI_FC_VSDPAYLOAD22                    0x1048
#define HDMI_FC_VSDPAYLOAD23                    0x1049
#define HDMI_FC_SPDVENDORNAME0                  0x104A
#define HDMI_FC_SPDVENDORNAME1                  0x104B
#define HDMI_FC_SPDVENDORNAME2                  0x104C
#define HDMI_FC_SPDVENDORNAME3                  0x104D
#define HDMI_FC_SPDVENDORNAME4                  0x104E
#define HDMI_FC_SPDVENDORNAME5                  0x104F
#define HDMI_FC_SPDVENDORNAME6                  0x1050
#define HDMI_FC_SPDVENDORNAME7                  0x1051
#define HDMI_FC_SDPPRODUCTNAME0                 0x1052
#define HDMI_FC_SDPPRODUCTNAME1                 0x1053
#define HDMI_FC_SDPPRODUCTNAME2                 0x1054
#define HDMI_FC_SDPPRODUCTNAME3                 0x1055
#define HDMI_FC_SDPPRODUCTNAME4                 0x1056
#define HDMI_FC_SDPPRODUCTNAME5                 0x1057
#define HDMI_FC_SDPPRODUCTNAME6                 0x1058
#define HDMI_FC_SDPPRODUCTNAME7                 0x1059
#define HDMI_FC_SDPPRODUCTNAME8                 0x105A
#define HDMI_FC_SDPPRODUCTNAME9                 0x105B
#define HDMI_FC_SDPPRODUCTNAME10                0x105C
#define HDMI_FC_SDPPRODUCTNAME11                0x105D
#define HDMI_FC_SDPPRODUCTNAME12                0x105E
#define HDMI_FC_SDPPRODUCTNAME13                0x105F
#define HDMI_FC_SDPPRODUCTNAME14                0x1060
#define HDMI_FC_SPDPRODUCTNAME15                0x1061
#define HDMI_FC_SPDDEVICEINF                    0x1062
#define HDMI_FC_AUDSCONF                        0x1063
#define HDMI_FC_AUDSSTAT                        0x1064
#define HDMI_FC_AUDSCHNLS0                      0x1067
#define HDMI_FC_AUDSCHNLS1                      0x1068
#define HDMI_FC_AUDSCHNLS2                      0x1069
#define HDMI_FC_AUDSCHNLS3                      0x106a
#define HDMI_FC_AUDSCHNLS4                      0x106b
#define HDMI_FC_AUDSCHNLS5                      0x106c
#define HDMI_FC_AUDSCHNLS6                      0x106d
#define HDMI_FC_AUDSCHNLS7                      0x106e
#define HDMI_FC_AUDSCHNLS8                      0x106f
#define HDMI_FC_DATACH0FILL                     0x1070
#define HDMI_FC_DATACH1FILL                     0x1071
#define HDMI_FC_DATACH2FILL                     0x1072
#define HDMI_FC_CTRLQHIGH                       0x1073
#define HDMI_FC_CTRLQLOW                        0x1074
#define HDMI_FC_ACP0                            0x1075
#define HDMI_FC_ACP28                           0x1076
#define HDMI_FC_ACP27                           0x1077
#define HDMI_FC_ACP26                           0x1078
#define HDMI_FC_ACP25                           0x1079
#define HDMI_FC_ACP24                           0x107A
#define HDMI_FC_ACP23                           0x107B
#define HDMI_FC_ACP22                           0x107C
#define HDMI_FC_ACP21                           0x107D
#define HDMI_FC_ACP20                           0x107E
#define HDMI_FC_ACP19                           0x107F
#define HDMI_FC_ACP18                           0x1080
#define HDMI_FC_ACP17                           0x1081
#define HDMI_FC_ACP16                           0x1082
#define HDMI_FC_ACP15                           0x1083
#define HDMI_FC_ACP14                           0x1084
#define HDMI_FC_ACP13                           0x1085
#define HDMI_FC_ACP12                           0x1086
#define HDMI_FC_ACP11                           0x1087
#define HDMI_FC_ACP10                           0x1088
#define HDMI_FC_ACP9                            0x1089
#define HDMI_FC_ACP8                            0x108A
#define HDMI_FC_ACP7                            0x108B
#define HDMI_FC_ACP6                            0x108C
#define HDMI_FC_ACP5                            0x108D
#define HDMI_FC_ACP4                            0x108E
#define HDMI_FC_ACP3                            0x108F
#define HDMI_FC_ACP2                            0x1090
#define HDMI_FC_ACP1                            0x1091
#define HDMI_FC_ISCR1_0                         0x1092
#define HDMI_FC_ISCR1_16                        0x1093
#define HDMI_FC_ISCR1_15                        0x1094
#define HDMI_FC_ISCR1_14                        0x1095
#define HDMI_FC_ISCR1_13                        0x1096
#define HDMI_FC_ISCR1_12                        0x1097
#define HDMI_FC_ISCR1_11                        0x1098
#define HDMI_FC_ISCR1_10                        0x1099
#define HDMI_FC_ISCR1_9                         0x109A
#define HDMI_FC_ISCR1_8                         0x109B
#define HDMI_FC_ISCR1_7                         0x109C
#define HDMI_FC_ISCR1_6                         0x109D
#define HDMI_FC_ISCR1_5                         0x109E
#define HDMI_FC_ISCR1_4                         0x109F
#define HDMI_FC_ISCR1_3                         0x10A0
#define HDMI_FC_ISCR1_2                         0x10A1
#define HDMI_FC_ISCR1_1                         0x10A2
#define HDMI_FC_ISCR2_15                        0x10A3
#define HDMI_FC_ISCR2_14                        0x10A4
#define HDMI_FC_ISCR2_13                        0x10A5
#define HDMI_FC_ISCR2_12                        0x10A6
#define HDMI_FC_ISCR2_11                        0x10A7
#define HDMI_FC_ISCR2_10                        0x10A8
#define HDMI_FC_ISCR2_9                         0x10A9
#define HDMI_FC_ISCR2_8                         0x10AA
#define HDMI_FC_ISCR2_7                         0x10AB
#define HDMI_FC_ISCR2_6                         0x10AC
#define HDMI_FC_ISCR2_5                         0x10AD
#define HDMI_FC_ISCR2_4                         0x10AE
#define HDMI_FC_ISCR2_3                         0x10AF
#define HDMI_FC_ISCR2_2                         0x10B0
#define HDMI_FC_ISCR2_1                         0x10B1
#define HDMI_FC_ISCR2_0                         0x10B2
#define HDMI_FC_DATAUTO0                        0x10B3
#define HDMI_FC_DATAUTO1                        0x10B4
#define HDMI_FC_DATAUTO2                        0x10B5
#define HDMI_FC_DATMAN                          0x10B6
#define HDMI_FC_DATAUTO3                        0x10B7
#define HDMI_FC_RDRB0                           0x10B8
#define HDMI_FC_RDRB1                           0x10B9
#define HDMI_FC_RDRB2                           0x10BA
#define HDMI_FC_RDRB3                           0x10BB
#define HDMI_FC_RDRB4                           0x10BC
#define HDMI_FC_RDRB5                           0x10BD
#define HDMI_FC_RDRB6                           0x10BE
#define HDMI_FC_RDRB7                           0x10BF
#define HDMI_FC_STAT0                           0x10D0
#define HDMI_FC_INT0                            0x10D1
#define HDMI_FC_MASK0                           0x10D2
#define HDMI_FC_POL0                            0x10D3
#define HDMI_FC_STAT1                           0x10D4
#define HDMI_FC_INT1                            0x10D5
#define HDMI_FC_MASK1                           0x10D6
#define HDMI_FC_POL1                            0x10D7
#define HDMI_FC_STAT2                           0x10D8
#define HDMI_FC_INT2                            0x10D9
#define HDMI_FC_MASK2                           0x10DA
#define HDMI_FC_POL2                            0x10DB
#define HDMI_FC_PRCONF                          0x10E0
#define HDMI_FC_SCRAMBLER_CTRL                  0x10E1
#define HDMI_FC_PACKET_TX_EN			0x10E3

#define HDMI_PHY_I2CM_SLAVE_ADDR                0x3020
#define HDMI_PHY_I2CM_ADDRESS_ADDR              0x3021
#define HDMI_PHY_I2CM_DATAO_1_ADDR              0x3022
#define HDMI_PHY_I2CM_DATAO_0_ADDR              0x3023
#define HDMI_PHY_I2CM_DATAI_1_ADDR              0x3024
#define HDMI_PHY_I2CM_DATAI_0_ADDR              0x3025
#define HDMI_PHY_I2CM_OPERATION_ADDR            0x3026
#define HDMI_PHY_I2CM_INT_ADDR                  0x3027
#define HDMI_PHY_I2CM_CTLINT_ADDR               0x3028
#define HDMI_PHY_I2CM_DIV_ADDR                  0x3029
#define HDMI_PHY_I2CM_SOFTRSTZ_ADDR             0x302a
#define HDMI_PHY_I2CM_SS_SCL_HCNT_1_ADDR        0x302b
#define HDMI_PHY_I2CM_SS_SCL_HCNT_0_ADDR        0x302c
#define HDMI_PHY_I2CM_SS_SCL_LCNT_1_ADDR        0x302d
#define HDMI_PHY_I2CM_SS_SCL_LCNT_0_ADDR        0x302e
#define HDMI_PHY_I2CM_FS_SCL_HCNT_1_ADDR        0x302f
#define HDMI_PHY_I2CM_FS_SCL_HCNT_0_ADDR        0x3030
#define HDMI_PHY_I2CM_FS_SCL_LCNT_1_ADDR        0x3031
#define HDMI_PHY_I2CM_FS_SCL_LCNT_0_ADDR        0x3032

#define HDMI_AUD_CONF0                          0x3100
#define HDMI_AUD_CONF1                          0x3101
#define HDMI_AUD_INT                            0x3102
#define HDMI_AUD_CONF2                          0x3103
#define HDMI_AUD_N1                             0x3200
#define HDMI_AUD_N2                             0x3201
#define HDMI_AUD_N3                             0x3202
#define HDMI_AUD_CTS1                           0x3203
#define HDMI_AUD_CTS2                           0x3204
#define HDMI_AUD_CTS3                           0x3205
#define HDMI_AUD_INPUTCLKFS                     0x3206
#define HDMI_AUD_SPDIFINT						0x3302
#define HDMI_AUD_CONF0_HBR                      0x3400
#define HDMI_AUD_HBR_STATUS                     0x3401
#define HDMI_AUD_HBR_INT                        0x3402
#define HDMI_AUD_HBR_POL                        0x3403
#define HDMI_AUD_HBR_MASK                       0x3404

#define HDMI_GP_CONF0                           0x3500
#define HDMI_GP_CONF1                           0x3501
#define HDMI_GP_CONF2                           0x3502
#define HDMI_GP_STAT                            0x3503
#define HDMI_GP_INT                             0x3504
#define HDMI_GP_MASK                            0x3505
#define HDMI_GP_POL                             0x3506


#define HDMI_CSC_CFG                            0x4100
#define HDMI_CSC_SCALE                          0x4101
#define HDMI_CSC_COEF_A1_MSB                    0x4102
#define HDMI_CSC_COEF_A1_LSB                    0x4103
#define HDMI_CSC_COEF_A2_MSB                    0x4104
#define HDMI_CSC_COEF_A2_LSB                    0x4105
#define HDMI_CSC_COEF_A3_MSB                    0x4106
#define HDMI_CSC_COEF_A3_LSB                    0x4107
#define HDMI_CSC_COEF_A4_MSB                    0x4108
#define HDMI_CSC_COEF_A4_LSB                    0x4109
#define HDMI_CSC_COEF_B1_MSB                    0x410A
#define HDMI_CSC_COEF_B1_LSB                    0x410B
#define HDMI_CSC_COEF_B2_MSB                    0x410C
#define HDMI_CSC_COEF_B2_LSB                    0x410D
#define HDMI_CSC_COEF_B3_MSB                    0x410E
#define HDMI_CSC_COEF_B3_LSB                    0x410F
#define HDMI_CSC_COEF_B4_MSB                    0x4110
#define HDMI_CSC_COEF_B4_LSB                    0x4111
#define HDMI_CSC_COEF_C1_MSB                    0x4112
#define HDMI_CSC_COEF_C1_LSB                    0x4113
#define HDMI_CSC_COEF_C2_MSB                    0x4114
#define HDMI_CSC_COEF_C2_LSB                    0x4115
#define HDMI_CSC_COEF_C3_MSB                    0x4116
#define HDMI_CSC_COEF_C3_LSB                    0x4117
#define HDMI_CSC_COEF_C4_MSB                    0x4118
#define HDMI_CSC_COEF_C4_LSB                    0x4119

#define HDMI_A_HDCPCFG0                         0x5000
#define HDMI_A_HDCPCFG1                         0x5001
#define HDMI_A_HDCPOBS0                         0x5002
#define HDMI_A_HDCPOBS1                         0x5003
#define HDMI_A_HDCPOBS2                         0x5004
#define HDMI_A_HDCPOBS3                         0x5005
#define HDMI_A_APIINTCLR                        0x5006
#define HDMI_A_APIINTSTAT                       0x5007
#define HDMI_A_APIINTMSK                        0x5008
#define HDMI_A_VIDPOLCFG                        0x5009
#define HDMI_A_OESSWCFG                         0x500A
#define HDMI_A_TIMER1SETUP0                     0x500B
#define HDMI_A_TIMER1SETUP1                     0x500C
#define HDMI_A_TIMER2SETUP0                     0x500D
#define HDMI_A_TIMER2SETUP1                     0x500E
#define HDMI_A_100MSCFG                         0x500F
#define HDMI_A_2SCFG0                           0x5010
#define HDMI_A_2SCFG1                           0x5011
#define HDMI_A_5SCFG0                           0x5012
#define HDMI_A_5SCFG1                           0x5013
#define HDMI_A_SRMVERLSB                        0x5014
#define HDMI_A_SRMVERMSB                        0x5015
#define HDMI_A_SRMCTRL                          0x5016
#define HDMI_A_SFRSETUP                         0x5017
#define HDMI_A_I2CHSETUP                        0x5018
#define HDMI_A_INTSETUP                         0x5019
#define HDMI_A_PRESETUP                         0x501A
#define HDMI_A_SRM_BASE                         0x5020

#define HDMI_I2CM_SLAVE                         0x7E00
#define HDMI_I2CM_ADDRESS                       0x7E01
#define HDMI_I2CM_DATAO                         0x7E02
#define HDMI_I2CM_DATAI                         0x7E03
#define HDMI_I2CM_OPERATION                     0x7E04
#define HDMI_I2CM_INT                           0x7E05
#define HDMI_I2CM_CTLINT                        0x7E06
#define HDMI_I2CM_DIV                           0x7E07
#define HDMI_I2CM_SEGADDR                       0x7E08
#define HDMI_I2CM_SOFTRSTZ                      0x7E09
#define HDMI_I2CM_SEGPTR                        0x7E0A
#define HDMI_I2CM_SS_SCL_HCNT_1_ADDR            0x7E0B
#define HDMI_I2CM_SS_SCL_HCNT_0_ADDR            0x7E0C
#define HDMI_I2CM_SS_SCL_LCNT_1_ADDR            0x7E0D
#define HDMI_I2CM_SS_SCL_LCNT_0_ADDR            0x7E0E
#define HDMI_I2CM_FS_SCL_HCNT_1_ADDR            0x7E0F
#define HDMI_I2CM_FS_SCL_HCNT_0_ADDR            0x7E10
#define HDMI_I2CM_FS_SCL_LCNT_1_ADDR            0x7E11
#define HDMI_I2CM_FS_SCL_LCNT_0_ADDR            0x7E12
#define HDMI_I2CM_SDA_HOLD                      0x7E13
#define HDMI_I2CM_SCDC_READ_UPDATE              0x7E14

#define HDMI_I2CM_READ_REQ_EN_MSK               BIT(4)
#define HDMI_I2CM_READ_REQ_EN_OFFSET            4
#define HDMI_I2CM_READ_UPDATE_MSK               BIT(0)
#define HDMI_I2CM_READ_UPDATE_OFFSET            0
#define HDMI_I2CM_I2CM_UPRD_VSYNC_EN_MSK        BIT(5)
#define HDMI_I2CM_I2CM_UPRD_VSYNC_EN_OFFSET     5
#define	HDMI_I2CM_READ_BUFF0                    0x7E20
#define	HDMI_I2CM_SCDC_UPDATE0                  0x7E30
#define	HDMI_I2CM_SCDC_UPDATE1                  0x7E31
#define DDC_I2C_EDID_ADDR                       0x50
#define DDC_I2C_SEG_ADDR                        0x30
#define DDC_I2C_SCDC_ADDR                       0x54
#define HDMI_EDID_BLOCK_SIZE                    128
#define EDID_I2C_MIN_SS_SCL_HIGH_TIME           9625
#define EDID_I2C_MIN_SS_SCL_LOW_TIME            10000
#define I2C_DIV_FACTOR                          1000000


/* Interrupt Registers */
#define HDMI_IH_FC_STAT0                        0x0100
#define HDMI_IH_FC_STAT1                        0x0101
#define HDMI_IH_FC_STAT2                        0x0102
#define HDMI_IH_AS_STAT0                        0x0103
#define HDMI_IH_PHY_STAT0                       0x0104
#define HDMI_IH_I2CM_STAT0                      0x0105
#define HDMI_IH_CEC_STAT0                       0x0106
#define HDMI_IH_VP_STAT0                        0x0107
#define HDMI_IH_I2CMPHY_STAT0                   0x0108
#define HDMI_IH_AHBDMAAUD_STAT0                 0x0109

#define HDMI_MC_SFRDIV                          0x4000
#define HDMI_MC_CLKDIS                          0x4001
#define HDMI_MC_SWRSTZ                          0x4002
#define HDMI_MC_OPCTRL                          0x4003
#define HDMI_MC_FLOWCTRL                        0x4004
#define HDMI_MC_PHYRSTZ                         0x4005
#define HDMI_MC_LOCKONCLOCK                     0x4006
#define HDMI_MC_HEACPHY_RST                     0x4007



#define EXT_PHY_PLL_BW			0xe7
#define EXT_PHY_PPLL_BW			0xec
#define EXT_PHY_TERM_RESIS_AUTO		0xf4
#define EXT_PHY_TERM_CAL		0x03
#define EXT_PHY_TERM_CAL_DIV_L		0x04
#define EXT_PHY_AUTO_R50_OHMS			0
#define EXT_PHY_AUTO_R75_OHMS			BIT(2)
#define EXT_PHY_AUTO_R100_OHMS			(2 << 2)
#define EXT_PHY_AUTO_ROPEN_CIRCUIT		(3 << 2)

#define EXT_PHY_SIGNAL_CTRL		0xee

#define HDMI_PHY_I2CM_INT_ADDR_DONE_POL  0x08
#define HDMI_PHY_I2CM_INT_ADDR_DONE_MASK  0x04
#define HDMI_PHY_I2CM_CTLINT_ADDR_NAC_POL 0x80
#define HDMI_PHY_I2CM_CTLINT_ADDR_NAC_MASK  0x40
#define HDMI_PHY_I2CM_CTLINT_ADDR_ARBITRATION_POL 0x08
#define HDMI_PHY_I2CM_CTLINT_ADDR_ARBITRATION_MASK  0x04

#define HDMI_IH_PHY_STAT0_RX_SENSE3  0x20
#define HDMI_IH_PHY_STAT0_RX_SENSE2  0x10
#define HDMI_IH_PHY_STAT0_RX_SENSE1  0x8
#define HDMI_IH_PHY_STAT0_RX_SENSE0  0x4
#define HDMI_IH_PHY_STAT0_TX_PHY_LOCK  0x2
#define HDMI_IH_PHY_STAT0_HPD  0x1


enum{
	HDMI_A_VIDPOLCFG_UNENCRYPTCONF_MASK = 0x60,
	HDMI_A_VIDPOLCFG_UNENCRYPTCONF_OFFSET = 5,
	HDMI_A_VIDPOLCFG_DATAENPOL_MASK = 0x10,
	HDMI_A_VIDPOLCFG_DATAENPOL_ACTIVE_HIGH = 0x10,
	HDMI_A_VIDPOLCFG_DATAENPOL_ACTIVE_LOW = 0x0,
	HDMI_A_VIDPOLCFG_VSYNCPOL_MASK = 0x8,
	HDMI_A_VIDPOLCFG_VSYNCPOL_ACTIVE_HIGH = 0x8,
	HDMI_A_VIDPOLCFG_VSYNCPOL_ACTIVE_LOW = 0x0,
	HDMI_A_VIDPOLCFG_HSYNCPOL_MASK = 0x2,
	HDMI_A_VIDPOLCFG_HSYNCPOL_ACTIVE_HIGH = 0x2,
	HDMI_A_VIDPOLCFG_HSYNCPOL_ACTIVE_LOW = 0x0,

	HDMI_A_HDCPCFG0_HDMIDVI_MASK = 0x1,
	HDMI_A_HDCPCFG0_HDMIDVI_HDMI = 0x1,
	HDMI_A_HDCPCFG0_HDMIDVI_DVI = 0x0,

	HDMI_MC_CLKDIS_PREPCLK_DISABLE = 0x4,

	HDMI_MC_FLOWCTRL_FEED_THROUGH_OFF_MASK = 0x1,
	HDMI_MC_FLOWCTRL_FEED_THROUGH_OFF_CSC_IN_PATH = 0x1,
	HDMI_MC_FLOWCTRL_FEED_THROUGH_OFF_CSC_BYPASS = 0x0,

	HDMI_AUD_CTS3_CTS_MANUAL = 0x10,

	HDMI_AUD_CTS3_N_SHIFT_MASK = 0xe0,

	HDMI_TX_INSTUFFING_BDBDATA_STUFFING_MASK = 0x4,
	HDMI_TX_INSTUFFING_BDBDATA_STUFFING_ENABLE = 0x4,
	HDMI_TX_INSTUFFING_BDBDATA_STUFFING_DISABLE = 0x0,
	HDMI_TX_INSTUFFING_RCRDATA_STUFFING_MASK = 0x2,
	HDMI_TX_INSTUFFING_RCRDATA_STUFFING_ENABLE = 0x2,
	HDMI_TX_INSTUFFING_RCRDATA_STUFFING_DISABLE = 0x0,
	HDMI_TX_INSTUFFING_GYDATA_STUFFING_MASK = 0x1,
	HDMI_TX_INSTUFFING_GYDATA_STUFFING_ENABLE = 0x1,
	HDMI_TX_INSTUFFING_GYDATA_STUFFING_DISABLE = 0x0,

	HDMI_IH_I2CM_STAT0_DONE = 0x2,
	HDMI_IH_I2CM_STAT0_ERROR = 0x1,

	HDMI_I2CM_OPERATION_WRITE = 0x10,
	HDMI_I2CM_OPERATION_READ_EXT = 0x2,
	HDMI_I2CM_OPERATION_READ = 0x1,

	HDMI_I2CM_INT_DONE_POL = 0x8,
	HDMI_I2CM_INT_DONE_MASK = 0x4,

	HDMI_I2CM_CTLINT_NAC_POL = 0x80,
	HDMI_I2CM_CTLINT_NAC_MASK = 0x40,
	HDMI_I2CM_CTLINT_ARB_POL = 0x8,
	HDMI_I2CM_CTLINT_ARB_MASK = 0x4,

	HDMI_I2CM_DIV_FAST_STD_MODE = 0x8,
	HDMI_I2CM_DIV_FAST_MODE = 0x8,
	HDMI_I2CM_DIV_STD_MODE = 0,

	HDMI_IH_MUTE_FC_STAT2_OVERFLOW_MASK = 0x03,
	HDMI_IH_MUTE_FC_STAT2_LOW_PRIORITY_OVERFLOW = 0x02,
	HDMI_IH_MUTE_FC_STAT2_HIGH_PRIORITY_OVERFLOW = 0x01,

	HDMI_PHY_RX_SENSE3 = 0x80,
	HDMI_PHY_RX_SENSE2 = 0x40,
	HDMI_PHY_RX_SENSE1 = 0x20,
	HDMI_PHY_RX_SENSE0 = 0x10,
	HDMI_PHY_HPD = 0x02,
	HDMI_PHY_TX_PHY_LOCK = 0x01,
};

#define HDMI_PHY_RX_SENSE (HDMI_PHY_RX_SENSE0 | HDMI_PHY_RX_SENSE1 | HDMI_PHY_RX_SENSE2 | HDMI_PHY_RX_SENSE3)
#define HDMI_IH_PHY_STAT0_RX_SENSE (HDMI_IH_PHY_STAT0_RX_SENSE0 | HDMI_IH_PHY_STAT0_RX_SENSE1 | HDMI_IH_PHY_STAT0_RX_SENSE2 | HDMI_IH_PHY_STAT0_RX_SENSE3)

#define HDMIPHY_REGW(a) REGW(HDMIPHY_BASE + ((a)*4))
#define HDMIPHY_REG_UPD(a,m,value) {u32 val = HDMIPHY_REGW(a); HDMIPHY_REGW(a) = (val & ~(m)) | (value & m);}
#define HDMI_REGW(a)  REGW(HDMI_BASE + (a*4))
#define HDMI_REG_SET(a,m,s,value) REG_SET((HDMI_BASE+(a*4)),m,s,value,u32)
#define HDMI_REG_UPD(a,m,value) {u32 val = HDMI_REGW(a); HDMI_REGW(a) = (val & ~(m)) | value;}

#define HDMI_EDID_LEN		512
#define DDC_SEGMENT_ADDR    0x30
#define DDC_ADDR 			0x50
#define I2C_M_TEN			0x0010	/* this is a ten bit chip address */
#define I2C_M_RD			0x0001	/* read data, from slave to master */
#define I2C_M_STOP			0x8000	/* if I2C_FUNC_PROTOCOL_MANGLING */
#define I2C_M_NOSTART		0x4000	/* if I2C_FUNC_NOSTART */
#define I2C_M_REV_DIR_ADDR	0x2000	/* if I2C_FUNC_PROTOCOL_MANGLING */
#define I2C_M_IGNORE_NAK	0x1000	/* if I2C_FUNC_PROTOCOL_MANGLING */
#define I2C_M_NO_RD_ACK		0x0800	/* if I2C_FUNC_PROTOCOL_MANGLING */
#define I2C_M_RECV_LEN		0x0400	/* length will be first received byte */

struct i2c_msg {
	u8 addr;
	u16 flags;
	u16 len;
	u8 *buf;
};

struct i2c{
	u8 is_segment,is_regaddr,cmp;
	u16 slave_reg;
	u32 stat;
};

struct est_timings {
	u8 t1;
	u8 t2;
	u8 mfg_rsvd;
} __attribute__((packed));

struct std_timing {
	u8 hsize; /* need to multiply by 8 then add 248 */
	u8 vfreq_aspect;
} __attribute__((packed));

struct detailed_pixel_timing {
	u8 hactive_lo;
	u8 hblank_lo;
	u8 hactive_hblank_hi;
	u8 vactive_lo;
	u8 vblank_lo;
	u8 vactive_vblank_hi;
	u8 hsync_offset_lo;
	u8 hsync_pulse_width_lo;
	u8 vsync_offset_pulse_width_lo;
	u8 hsync_vsync_offset_pulse_width_hi;
	u8 width_mm_lo;
	u8 height_mm_lo;
	u8 width_height_mm_hi;
	u8 hborder;
	u8 vborder;
	u8 misc;
} __attribute__((packed));


struct detailed_data_string {
	u8 str[13];
} __attribute__((packed));

struct detailed_data_monitor_range {
	u8 min_vfreq;
	u8 max_vfreq;
	u8 min_hfreq_khz;
	u8 max_hfreq_khz;
	u8 pixel_clock_mhz; /* need to multiply by 10 */
	u8 flags;
	union {
		struct {
			u8 reserved;
			u8 hfreq_start_khz; /* need to multiply by 2 */
			u8 c; /* need to divide by 2 */
			__le16 m;
			u8 k;
			u8 j; /* need to divide by 2 */
		} __attribute__((packed)) gtf2;
		struct {
			u8 version;
			u8 data1; /* high 6 bits: extra clock resolution */
			u8 data2; /* plus low 2 of above: max hactive */
			u8 supported_aspects;
			u8 flags; /* preferred aspect and blanking support */
			u8 supported_scalings;
			u8 preferred_refresh;
		} __attribute__((packed)) cvt;
	} formula;
} __attribute__((packed));

struct detailed_data_wpindex {
	u8 white_yx_lo; /* Lower 2 bits each */
	u8 white_x_hi;
	u8 white_y_hi;
	u8 gamma; /* need to divide by 100 then add 1 */
} __attribute__((packed));

struct cvt_timing {
	u8 code[3];
} __attribute__((packed));

struct detailed_non_pixel {
	u8 pad1;
	u8 type; /* ff=serial, fe=string, fd=monitor range, fc=monitor name
		    fb=color point data, fa=standard timing data,
		    f9=undefined, f8=mfg. reserved */
	u8 pad2;
	union {
		struct detailed_data_string str;
		struct detailed_data_monitor_range range;
		struct detailed_data_wpindex color;
		struct std_timing timings[6];
		struct cvt_timing cvt[4];
	} data;
} __attribute__((packed));

struct detailed_timing {
	__le16 pixel_clock; /* need to multiply by 10 KHz */
	union {
		struct detailed_pixel_timing pixel_data;
		struct detailed_non_pixel other_data;
	} data;
} __attribute__((packed));

struct edid {
	u8 header[8];
	/* Vendor & product info */
	u8 mfg_id[2];
	u8 prod_code[2];
	u32 serial; /* FIXME: byte order */
	u8 mfg_week;
	u8 mfg_year;
	/* EDID version */
	u8 version;
	u8 revision;
	/* Display info: */
	u8 input;
	u8 width_cm;
	u8 height_cm;
	u8 gamma;
	u8 features;
	/* Color characteristics */
	u8 red_green_lo;
	u8 black_white_lo;
	u8 red_x;
	u8 red_y;
	u8 green_x;
	u8 green_y;
	u8 blue_x;
	u8 blue_y;
	u8 white_x;
	u8 white_y;
	struct est_timings established_timings;
	struct std_timing standard_timings[8];
	struct detailed_timing detailed_timings[4];
	u8 extensions;
	u8 checksum;
} __attribute__((packed));

int drm_do_probe_ddc_edid(u8 *buf, unsigned int block, int len);
int inno_hdmi_phy_rk3328_init();
int dw_hdmi_i2c_init();
int inno_hdmi_phy_rk3328_power_on();
int initialize_hdmi_ih_mutes();
struct edid *drm_do_get_edid(u8 *data);
int inno_hdmi_phy_rk3328_pre_pll_update();


#endif