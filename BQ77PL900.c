/*
 * BQ77PL900.c
 *
 *  Created on: Sep 2, 2022
 *      Author: NatmateeP
 */
#include "main.h"
#include "i2c.h"
#include "stm32f4xx_it.h"
#include "BQ77PL900.h"


/*=============================================================================*/
/**
 * @brief	Initial Function
 * @param  	None
 * @retval 	None
 */
void BQ77PL900_Init(){
	bq77pl900.handle 	= &hi2c1;
	bq77pl900.addr		= 0x20;
	bq77pl900.timeout	= 1000; //1000ms
	i2cdata.err 		= 0;
	i2cdata.err_rw 		= 0;
}

/*=============================================================================*/
/**
 * @brief	Read I2C data
 * @param  	None
 * @retval 	None
 */
void BQ77PL900_ReadData(BQ77PL900_HandleTypedef *hbq77, uint8_t cmd,uint8_t num){
	HAL_I2C_Mem_Read(hbq77->handle, hbq77->addr, cmd, I2C_MEMADD_SIZE_8BIT, i2cdata.rbuf, num, hbq77->timeout);
}

/*=============================================================================*/
/**
 * @brief	Write I2C data
 * @param  	None
 * @retval 	None
 */
void BQ77PL900_WriteData(BQ77PL900_HandleTypedef *hbq77, uint8_t cmd,uint8_t num){
	HAL_I2C_Mem_Write(hbq77->handle, hbq77->addr, cmd, I2C_MEMADD_SIZE_8BIT, i2cdata.wbuf, num, hbq77->timeout);
}

/*=============================================================================*/
/**
 * @brief	Read BQ77PL900's status register
 * @param  	None
 * @retval 	None
 */
void BQ77PL900_Status(BQ77PL900_HandleTypedef *hbq77){
	BQ77PL900_ReadData(hbq77,BQ77PL900_ADDR_STAT,1);
}

/*=============================================================================*/
/**
 * @brief	Read/Write BQ77PL900's output control register
 * @param  	rw : read/write ; rw = 0 write
 * 							; rw = 1 read
 * @retval 	None
 */
void BQ77PL900_OutCtrl(BQ77PL900_HandleTypedef *hbq77, uint8_t rw){
	if(rw == 0){
		i2cdata.err_rw = 0;
		BQ77PL900_WriteData(hbq77, BQ77PL900_ADDR_OUTPUT_CTRL, 1);
	}
	else if(rw == 1){
		i2cdata.err_rw = 0;
		BQ77PL900_ReadData(hbq77, BQ77PL900_ADDR_OUTPUT_CTRL, 1);
		status.STATUS 	= i2cdata.rbuf[0];
		status.CHG 		= (status.STATUS & 0x80) >> 7;
		status.DSG 		= (status.STATUS & 0x40) >> 6;
		status.VGOOD 	= (status.STATUS & 0x20) >> 5;
		status.OVTEMP 	= (status.STATUS & 0x10) >> 4;
		status.UV 		= (status.STATUS & 0x08) >> 3;
		status.OV 		= (status.STATUS & 0x04) >> 2;
		status.OCD 		= (status.STATUS & 0x02) >> 1;
		status.SCD 		= (status.STATUS & 0x01);
	}
	else{
		i2cdata.err_rw = 1;
	}
}

/*=============================================================================*/
/**
 * @brief	Read/Write BQ77PL900's state control register
 * @param  	rw : read/write ; rw = 0 write
 * 							; rw = 1 read
 * @retval 	None
 */
void BQ77PL900_StateCtrl(BQ77PL900_HandleTypedef *hbq77, uint8_t rw){
	if(rw == 0){
		i2cdata.err_rw = 0;
		BQ77PL900_WriteData(hbq77, BQ77PL900_ADDR_STATE_CTRL, 1);
	}
	else if(rw == 1){
		i2cdata.err_rw = 0;
		BQ77PL900_ReadData(hbq77, BQ77PL900_ADDR_STATE_CTRL, 1);
		state_ctrl.STATE_CTRL 		= i2cdata.rbuf[0];
		state_ctrl.IGAIN 			= (state_ctrl.STATE_CTRL & 0x80) >> 7;
		state_ctrl.VGAIN 			= (state_ctrl.STATE_CTRL & 0x40) >> 6;
		state_ctrl.HOST 			= (state_ctrl.STATE_CTRL & 0x02) >> 1;
		state_ctrl.SHDN 			= (state_ctrl.STATE_CTRL & 0x01);
	}
	else{
		i2cdata.err_rw = 1;
	}
}

/*=============================================================================*/
/**
 * @brief	Read/Write BQ77PL900's function control register
 * @param  	rw : read/write ; rw = 0 write
 * 							; rw = 1 read
 * @retval 	None
 */
void BQ77PL900_FuncCtrl(BQ77PL900_HandleTypedef *hbq77, uint8_t rw){
	if(rw == 0){
		i2cdata.err_rw = 0;
		BQ77PL900_WriteData(hbq77, BQ77PL900_ADDR_FUNC_CTRL, 1);
	}
	else if(rw == 1){
		i2cdata.err_rw = 0;
		BQ77PL900_ReadData(hbq77, BQ77PL900_ADDR_FUNC_CTRL, 1);
		func_ctrl.FUNC_CTRL 	= i2cdata.rbuf[0];
		func_ctrl.CBAL10 		= (func_ctrl.FUNC_CTRL & 0x80) >> 7;
		func_ctrl.CBAL9 		= (func_ctrl.FUNC_CTRL & 0x40) >> 6;
		func_ctrl.TOUT 			= (func_ctrl.FUNC_CTRL & 0x20) >> 5;
		func_ctrl.BAT 			= (func_ctrl.FUNC_CTRL & 0x10) >> 4;
		func_ctrl.PACK 			= (func_ctrl.FUNC_CTRL & 0x08) >> 3;
		func_ctrl.IACAL 		= (func_ctrl.FUNC_CTRL & 0x04) >> 2;
		func_ctrl.IAEN 			= (func_ctrl.FUNC_CTRL & 0x02) >> 1;
		func_ctrl.VAEN 			= (func_ctrl.FUNC_CTRL & 0x01);
	}
	else{
		i2cdata.err_rw = 1;
	}
}

/*=============================================================================*/
/**
 * @brief	Read/Write BQ77PL900's cell balance register
 * @param  	rw : read/write ; rw = 0 write
 * 							; rw = 1 read
 * @retval 	None
 */
void BQ77PL900_CellBal(BQ77PL900_HandleTypedef *hbq77, uint8_t rw){
	if(rw == 0){
		i2cdata.err_rw = 0;
		BQ77PL900_WriteData(hbq77, BQ77PL900_ADDR_CELL_BAL, 1);
	}
	else if(rw == 1){
		i2cdata.err_rw = 0;
		BQ77PL900_ReadData(hbq77, BQ77PL900_ADDR_CELL_BAL, 1);
		cellbal.CELL_BAL 		= i2cdata.rbuf[0];
		cellbal.CBAL8 			= (cellbal.CELL_BAL & 0x80) >> 7;
		cellbal.CBAL7 			= (cellbal.CELL_BAL & 0x40) >> 6;
		cellbal.CBAL6 			= (cellbal.CELL_BAL & 0x20) >> 5;
		cellbal.CBAL5 			= (cellbal.CELL_BAL & 0x10) >> 4;
		cellbal.CBAL4 			= (cellbal.CELL_BAL & 0x08) >> 3;
		cellbal.CBAL3 			= (cellbal.CELL_BAL & 0x04) >> 2;
		cellbal.CBAL2 			= (cellbal.CELL_BAL & 0x02) >> 1;
		cellbal.CBAL1 			= (cellbal.CELL_BAL & 0x01);
	}
	else{
		i2cdata.err_rw = 1;
	}
}

/*=============================================================================*/
/**
 * @brief	Read/Write BQ77PL900's cell select register
 * @param  	rw : read/write ; rw = 0 write
 * 							; rw = 1 read
 * @retval 	None
 */
void BQ77PL900_CellSel(BQ77PL900_HandleTypedef *hbq77, uint8_t rw){
	if(rw == 0){
		i2cdata.err_rw = 0;
		BQ77PL900_WriteData(hbq77, BQ77PL900_ADDR_CELL_SEL, 1);
	}
	else if(rw == 1){
		i2cdata.err_rw = 0;
		BQ77PL900_ReadData(hbq77, BQ77PL900_ADDR_CELL_SEL, 1);
		cellsel.CELL_SEL		= i2cdata.rbuf[0];
		cellsel.CAL2 			= (cellsel.CELL_SEL & 0x40) >> 6;
		cellsel.CAL1 			= (cellsel.CELL_SEL & 0x20) >> 5;
		cellsel.CAL0 			= (cellsel.CELL_SEL & 0x10) >> 4;
		cellsel.CELL4 			= (cellsel.CELL_SEL & 0x08) >> 3;
		cellsel.CELL3 			= (cellsel.CELL_SEL & 0x04) >> 2;
		cellsel.CELL2 			= (cellsel.CELL_SEL & 0x02) >> 1;
		cellsel.CELL1 			= (cellsel.CELL_SEL & 0x01);
	}
	else{
		i2cdata.err_rw = 1;
	}
}

/*=============================================================================*/
/**
 * @brief	Read/Write BQ77PL900's over voltage configuration register
 * @param  	rw : read/write ; rw = 0 write
 * 							; rw = 1 read
 * @retval 	None
 */
void BQ77PL900_OvCfg(BQ77PL900_HandleTypedef *hbq77, uint8_t rw){
	if(rw == 0){
		i2cdata.err_rw = 0;
		BQ77PL900_WriteData(hbq77, BQ77PL900_ADDR_OV_CFG, 1);
	}
	else if(rw == 1){
		i2cdata.err_rw = 0;
		BQ77PL900_ReadData(hbq77, BQ77PL900_ADDR_OV_CFG, 1);
		ovcfg.OV_CFG 		= i2cdata.rbuf[0];
		ovcfg.OVD2 			= (ovcfg.OV_CFG & 0x80) >> 7;
		ovcfg.OVD1 			= (ovcfg.OV_CFG & 0x40) >> 6;
		ovcfg.OVD0 			= (ovcfg.OV_CFG & 0x20) >> 5;
		ovcfg.OVH1 			= (ovcfg.OV_CFG & 0x10) >> 4;
		ovcfg.OVH0 			= (ovcfg.OV_CFG & 0x08) >> 3;
		ovcfg.OV2 			= (ovcfg.OV_CFG & 0x04) >> 2;
		ovcfg.OV1 			= (ovcfg.OV_CFG & 0x02) >> 1;
		ovcfg.OV0 			= (ovcfg.OV_CFG & 0x01);
	}
	else{
		i2cdata.err_rw = 1;
	}
}

/*=============================================================================*/
/**
 * @brief	Read/Write BQ77PL900's under voltage configuration register
 * @param  	rw : read/write ; rw = 0 write
 * 							; rw = 1 read
 * @retval 	None
 */
void BQ77PL900_UvCfg(BQ77PL900_HandleTypedef *hbq77, uint8_t rw){
	if(rw == 0){
		i2cdata.err_rw = 0;
		BQ77PL900_WriteData(hbq77, BQ77PL900_ADDR_UV_CFG, 1);
	}
	else if(rw == 1){
		i2cdata.err_rw = 0;
		BQ77PL900_ReadData(hbq77, BQ77PL900_ADDR_UV_CFG, 1);
		uvcfg.UV_CFG 		= i2cdata.rbuf[0];
		uvcfg.UVFET_DIS 	= (uvcfg.UV_CFG & 0x40) >> 6;
		uvcfg.UVH1 			= (uvcfg.UV_CFG & 0x20) >> 5;
		uvcfg.UVH0 			= (uvcfg.UV_CFG & 0x10) >> 4;
		uvcfg.UV3 			= (uvcfg.UV_CFG & 0x08) >> 3;
		uvcfg.UV2 			= (uvcfg.UV_CFG & 0x04) >> 2;
		uvcfg.UV1 			= (uvcfg.UV_CFG & 0x02) >> 1;
		uvcfg.UV0 			= (uvcfg.UV_CFG & 0x01);
	}
	else{
		i2cdata.err_rw = 1;
	}
}

/*=============================================================================*/
/**
 * @brief	Read/Write BQ77PL900's over voltage level under voltage delay time register
 * @param  	rw : read/write ; rw = 0 write
 * 							; rw = 1 read
 * @retval 	None
 */
void BQ77PL900_OCUVDelay(BQ77PL900_HandleTypedef *hbq77, uint8_t rw){
	if(rw == 0){
		i2cdata.err_rw = 0;
		BQ77PL900_WriteData(hbq77, BQ77PL900_ADDR_OCV_UV_DELAY, 1);
	}
	else if(rw == 1){
		i2cdata.err_rw = 0;
		BQ77PL900_ReadData(hbq77, BQ77PL900_ADDR_OCV_UV_DELAY, 1);
		ocuvdelay.OCUV_DELAY 		= i2cdata.rbuf[0];
		ocuvdelay.UVD3 			= (ocuvdelay.OCUV_DELAY & 0x80) >> 7;
		ocuvdelay.UVD2 			= (ocuvdelay.OCUV_DELAY & 0x40) >> 6;
		ocuvdelay.UVD1 			= (ocuvdelay.OCUV_DELAY & 0x20) >> 5;
		ocuvdelay.UVD0 			= (ocuvdelay.OCUV_DELAY & 0x10) >> 4;
		ocuvdelay.OCD3 			= (ocuvdelay.OCUV_DELAY & 0x08) >> 3;
		ocuvdelay.OCD2 			= (ocuvdelay.OCUV_DELAY & 0x04) >> 2;
		ocuvdelay.OCD1 			= (ocuvdelay.OCUV_DELAY & 0x02) >> 1;
		ocuvdelay.OCD0 			= (ocuvdelay.OCUV_DELAY & 0x01);
	}
	else{
		i2cdata.err_rw = 1;
	}
}

/*=============================================================================*/
/**
 * @brief	Read/Write BQ77PL900's overload delay time register
 * @param  	rw : read/write ; rw = 0 write
 * 							; rw = 1 read
 * @retval 	None
 */
void BQ77PL900_OcdCfg(BQ77PL900_HandleTypedef *hbq77, uint8_t rw){
	if(rw == 0){
		i2cdata.err_rw = 0;
		BQ77PL900_WriteData(hbq77, BQ77PL900_ADDR_OCD_CFG, 1);
	}
	else if(rw == 1){
		i2cdata.err_rw = 0;
		BQ77PL900_ReadData(hbq77, BQ77PL900_ADDR_OCD_CFG, 1);
		ocdcfg.OCD_CFG 			= i2cdata.rbuf[0];
		ocdcfg.CBEN 			= (ocdcfg.OCD_CFG & 0x80) >> 7;
		ocdcfg.ZVC 				= (ocdcfg.OCD_CFG & 0x40) >> 6;
		ocdcfg.SOR 				= (ocdcfg.OCD_CFG & 0x20) >> 5;
		ocdcfg.OCDD4 			= (ocdcfg.OCD_CFG & 0x10) >> 4;
		ocdcfg.OCDD3 			= (ocdcfg.OCD_CFG & 0x08) >> 3;
		ocdcfg.OCDD2 			= (ocdcfg.OCD_CFG & 0x04) >> 2;
		ocdcfg.OCDD1 			= (ocdcfg.OCD_CFG & 0x02) >> 1;
		ocdcfg.OCDD0 			= (ocdcfg.OCD_CFG & 0x01);
	}
	else{
		i2cdata.err_rw = 1;
	}
}

/*=============================================================================*/
/**
 * @brief	Read/Write BQ77PL900's short circuit in discharge register
 * @param  	rw : read/write ; rw = 0 write
 * 							; rw = 1 read
 * @retval 	None
 */
void BQ77PL900_ScdCfg(BQ77PL900_HandleTypedef *hbq77, uint8_t rw){
	if(rw == 0){
		i2cdata.err_rw = 0;
		BQ77PL900_WriteData(hbq77, BQ77PL900_ADDR_SCD_CFG, 1);
	}
	else if(rw == 1){
		i2cdata.err_rw = 0;
		BQ77PL900_ReadData(hbq77, BQ77PL900_ADDR_SCD_CFG, 1);
		scdcfg.SCD_CFG 			= i2cdata.rbuf[0];
		scdcfg.SCDD3 			= (scdcfg.SCD_CFG & 0x80) >> 7;
		scdcfg.SCDD2 			= (scdcfg.SCD_CFG & 0x40) >> 6;
		scdcfg.SCDD1 			= (scdcfg.SCD_CFG & 0x20) >> 5;
		scdcfg.SCDD0 			= (scdcfg.SCD_CFG & 0x10) >> 4;
		scdcfg.SCD3 			= (scdcfg.SCD_CFG & 0x08) >> 3;
		scdcfg.SCD2 			= (scdcfg.SCD_CFG & 0x04) >> 2;
		scdcfg.SCD1 			= (scdcfg.SCD_CFG & 0x02) >> 1;
		scdcfg.SCD0 			= (scdcfg.SCD_CFG & 0x01);
	}
	else{
		i2cdata.err_rw = 1;
	}
}


/*=============================================================================*/
/**
 * @brief	Read/Write BQ77PL900's over voltage configuration register
 * @param  	rw : read/write ; rw = BQ77PL900_EEPROM_RW (0x62)
 * 							; rw = BQ77PL900_EEPROM_W (0x41)
 * 							; rw = BQ77PL900_EEPROM_R (0x00)
 * @retval 	None
 */
void BQ77PL900_EEPROM_Mode(BQ77PL900_HandleTypedef *hbq77, uint8_t rw){
	i2cdata.err_rw = 0;
	i2cdata.wbuf[0] = rw;
	BQ77PL900_WriteData(hbq77, BQ77PL900_ADDR_EEPROM, 1);
}
