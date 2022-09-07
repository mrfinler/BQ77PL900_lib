/*
 * BQ77PL900.h
 *
 *  Created on: Sep 2, 2022
 *      Author: NatmateeP
 */

#ifndef INC_BQ77PL900_H_
#define INC_BQ77PL900_H_

#define BQ77PL900_ADDR_STAT	 						0x00
#define BQ77PL900_ADDR_OUTPUT_CTRL					0x01
#define BQ77PL900_ADDR_STATE_CTRL 					0x02
#define BQ77PL900_ADDR_FUNC_CTRL					0x03
#define BQ77PL900_ADDR_CELL_BAL						0x04
#define BQ77PL900_ADDR_CELL_SEL						0x05
#define BQ77PL900_ADDR_OV_CFG						0x06
#define BQ77PL900_ADDR_UV_CFG						0x07
#define BQ77PL900_ADDR_OCV_UV_DELAY					0x08
#define BQ77PL900_ADDR_OCD_CFG						0x09
#define BQ77PL900_ADDR_SCD_CFG						0x0a
#define BQ77PL900_ADDR_EEPROM						0x0b

#define BQ77PL900_EEPROM_RW							0b01100010
#define BQ77PL900_EEPROM_W							0b01000001
#define BQ77PL900_EEPROM_R							0b00000000

#define BQ77PL900_I2C_R								1
#define BQ77PL900_I2C_W								0

typedef struct {

	I2C_HandleTypeDef *handle;
	uint8_t addr;
	uint16_t timeout;

}BQ77PL900_HandleTypedef;

typedef struct {

	//STATUS BYTE
	uint8_t CHG;
	uint8_t DSG;
	uint8_t VGOOD;
	uint8_t OVTEMP;
	uint8_t UV;
	uint8_t OV;
	uint8_t OCD;
	uint8_t SCD;
	uint8_t STATUS;

}BQ77PL900_StatusByte;

typedef struct {

	//OUTPUT_CTRL
	uint8_t FS;
	uint8_t PFALT;
	uint8_t GPOD;
	uint8_t CHG_CTRL;
	uint8_t DSG_CTRL;
	uint8_t LTCLR;
	uint8_t OUTPUT_CTRL;

}BQ77PL900_OutCtrlByte;

typedef struct {

	//STATE_CTRL
	uint8_t IGAIN;
	uint8_t VGAIN;
	uint8_t HOST;
	uint8_t SHDN;
	uint8_t STATE_CTRL;

}BQ77PL900_StateCtrlByte;

typedef struct {

	//FUNCTION_CTRL
	uint8_t CBAL10;
	uint8_t CBAL9;
	uint8_t TOUT;
	uint8_t BAT;
	uint8_t PACK;
	uint8_t IACAL;
	uint8_t IAEN;
	uint8_t VAEN;
	uint8_t FUNC_CTRL;

}BQ77PL900_FuncCtrlByte;

typedef struct {

	//CELL_BAL
	uint8_t CBAL8;
	uint8_t CBAL7;
	uint8_t CBAL6;
	uint8_t CBAL5;
	uint8_t CBAL4;
	uint8_t CBAL3;
	uint8_t CBAL2;
	uint8_t CBAL1;
	uint8_t CELL_BAL;

}BQ77PL900_CellBalByte;

typedef struct {

	//CELL_SEL
	uint8_t CAL2;
	uint8_t CAL1;
	uint8_t CAL0;
	uint8_t CELL4;
	uint8_t CELL3;
	uint8_t CELL2;
	uint8_t CELL1;
	uint8_t CELL_SEL;

}BQ77PL900_CellSelByte;

typedef struct {

	//OV_CFG
	uint8_t OVD2;
	uint8_t OVD1;
	uint8_t OVD0;
	uint8_t OVH1;
	uint8_t OVH0;
	uint8_t OV2;
	uint8_t OV1;
	uint8_t OV0;
	uint8_t OV_CFG;

}BQ77PL900_OvCfgByte;

typedef struct {

	//UV_CFG
	uint8_t UVFET_DIS;
	uint8_t UVH1;
	uint8_t UVH0;
	uint8_t UV3;
	uint8_t UV2;
	uint8_t UV1;
	uint8_t UV0;
	uint8_t UV_CFG;

}BQ77PL900_UvCfgByte;

typedef struct {

	//OCV&UV_DELAY
	uint8_t UVD3;
	uint8_t UVD2;
	uint8_t UVD1;
	uint8_t UVD0;
	uint8_t OCD3;
	uint8_t OCD2;
	uint8_t OCD1;
	uint8_t OCD0;
	uint8_t OCUV_DELAY;

}BQ77PL900_OCUVDelayByte;

typedef struct {

	//OCD_CFG
	uint8_t CBEN;
	uint8_t ZVC;
	uint8_t SOR;
	uint8_t OCDD4;
	uint8_t OCDD3;
	uint8_t OCDD2;
	uint8_t OCDD1;
	uint8_t OCDD0;
	uint8_t OCD_CFG;

}BQ77PL900_OcdCfgByte;

typedef struct {

	//SCD_CFG
	uint8_t SCDD3;
	uint8_t SCDD2;
	uint8_t SCDD1;
	uint8_t SCDD0;
	uint8_t SCD3;
	uint8_t SCD2;
	uint8_t SCD1;
	uint8_t SCD0;
	uint8_t SCD_CFG;

}BQ77PL900_ScdCfgByte;

typedef struct {

	uint8_t rbuf[1];
	uint8_t wbuf[1];
	uint8_t rxflag;
	uint8_t txflag;
	uint8_t err;
	uint8_t err_rw;

}BQ77PL900_I2CData;

extern BQ77PL900_HandleTypedef 		bq77pl900;
extern BQ77PL900_StatusByte 		status;
extern BQ77PL900_OutCtrlByte 		out_ctrl;
extern BQ77PL900_StateCtrlByte 		state_ctrl;
extern BQ77PL900_FuncCtrlByte 		func_ctrl;
extern BQ77PL900_CellBalByte 		cellbal;
extern BQ77PL900_CellSelByte 		cellsel;
extern BQ77PL900_OvCfgByte 			ovcfg;
extern BQ77PL900_UvCfgByte 			uvcfg;
extern BQ77PL900_OCUVDelayByte 		ocuvdelay;
extern BQ77PL900_OcdCfgByte 		ocdcfg;
extern BQ77PL900_ScdCfgByte 		scdcfg;
extern BQ77PL900_I2CData			i2cdata;

void BQ77PL900_Init();
void BQ77PL900_ReadData(BQ77PL900_HandleTypedef *hbq77, uint8_t cmd,uint8_t num);
void BQ77PL900_WriteData(BQ77PL900_HandleTypedef *hbq77, uint8_t cmd,uint8_t num);


extern void BQ77PL900_Status(BQ77PL900_HandleTypedef *hbq77);
extern void BQ77PL900_OutCtrl(BQ77PL900_HandleTypedef *hbq77, uint8_t rw);
extern void BQ77PL900_StateCtrl(BQ77PL900_HandleTypedef *hbq77, uint8_t rw);
extern void BQ77PL900_FuncCtrl(BQ77PL900_HandleTypedef *hbq77, uint8_t rw);
extern void BQ77PL900_CellBal(BQ77PL900_HandleTypedef *hbq77, uint8_t rw);
extern void BQ77PL900_CellSel(BQ77PL900_HandleTypedef *hbq77, uint8_t rw);
extern void BQ77PL900_OvCfg(BQ77PL900_HandleTypedef *hbq77, uint8_t rw);
extern void BQ77PL900_UvCfg(BQ77PL900_HandleTypedef *hbq77, uint8_t rw);
extern void BQ77PL900_OCUVDelay(BQ77PL900_HandleTypedef *hbq77, uint8_t rw);
extern void BQ77PL900_OcdCfg(BQ77PL900_HandleTypedef *hbq77, uint8_t rw);
extern void BQ77PL900_ScdCfg(BQ77PL900_HandleTypedef *hbq77, uint8_t rw);
extern void BQ77PL900_EEPROM_Mode(BQ77PL900_HandleTypedef *hbq77, uint8_t rw);



#endif /* INC_BQ77PL900_H_ */
