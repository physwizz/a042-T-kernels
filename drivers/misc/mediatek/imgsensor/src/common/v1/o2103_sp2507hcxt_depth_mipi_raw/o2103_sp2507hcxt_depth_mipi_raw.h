/*****************************************************************************
 *
 * Filename:
 * ---------
 *     gc02m1mipi_Sensor.h
 *
 * Project:
 * --------
 *     ALPS
 *
 * Description:
 * ------------
 *     CMOS sensor header file
 *
 ****************************************************************************/
#ifndef __O2103_SP2507HCXT_DEPTH_MIPI_RAW_H__
#define __O2103_SP2507HCXT_DEPTH_MIPI_RAW_H__

#include "kd_camera_typedef.h"
#include "kd_imgsensor.h"
#include "kd_imgsensor_define.h"
#include "kd_imgsensor_errcode.h"
/* hs03s code for CAM-AL5625-01-247 by majunfeng at 2021/05/27 start */
enum{
	IMGSENSOR_MODE_INIT,
	IMGSENSOR_MODE_PREVIEW,
	IMGSENSOR_MODE_CAPTURE,
	IMGSENSOR_MODE_VIDEO,
	IMGSENSOR_MODE_HIGH_SPEED_VIDEO,
	IMGSENSOR_MODE_SLIM_VIDEO,
	IMGSENSOR_MODE_CUSTOM1,
	IMGSENSOR_MODE_CUSTOM2,
};
/* hs03s code for CAM-AL5625-01-247 by majunfeng at 2021/05/27 end */
/* 表示几种（不同工作模式状态下）的sensor参数信息 */
struct imgsensor_mode_struct {
	kal_uint32 pclk;	/* record different mode's pclk */
	kal_uint32 linelength;	/* record different mode's linelength */
	kal_uint32 framelength;	/* record different mode's framelength */

	kal_uint8 startx; /* record different mode's startx of grabwindow */
	kal_uint8 starty; /* record different mode's startx of grabwindow */

	/* record different mode's width of grabwindow */
	kal_uint16 grabwindow_width;

	/* record different mode's height of grabwindow */
	kal_uint16 grabwindow_height;

	/* following for MIPIDataLowPwr2HighSpeedSettleDelayCount
	 * by different scenario
	 */
	kal_uint8 mipi_data_lp2hs_settle_dc;

	/*	 following for GetDefaultFramerateByScenario()	*/
	kal_uint16 max_framerate;
	kal_uint32 mipi_pixel_rate;

};

/* SENSOR PRIVATE STRUCT FOR VARIABLES*/
struct imgsensor_struct {
	kal_uint8 mirror;	/* mirrorflip information */

	kal_uint8 sensor_mode;	/* record IMGSENSOR_MODE enum value */

	kal_uint32 shutter;	/* current shutter */
	kal_uint16 gain;	/* current gain */

	kal_uint32 pclk;	/* current pclk */

	kal_uint32 frame_length;	/* current framelength */
	kal_uint32 line_length;	/* current linelength */

	kal_uint32 min_frame_length; //current min framelength to max
	kal_int32 dummy_pixel;			//current dummypixel
	kal_int32 dummy_line;			//current dummline

	kal_uint16 current_fps;			//current max fps
	kal_bool   autoflicker_en; //record autoflicker enable or disable
	kal_bool test_pattern; //record test pattern mode or not
	enum MSDK_SCENARIO_ID_ENUM current_scenario_id; //current scenario
	kal_bool  ihdr_en;				//ihdr enable or disable

	kal_uint8 i2c_write_id; //record current sensor's i2c write id
	kal_uint8 pdaf_mode;
};

/* SENSOR PRIVATE STRUCT FOR CONSTANT*/
/* hs03s code for CAM-AL5625-01-247 by majunfeng at 2021/05/27 start */
struct imgsensor_info_struct {
	kal_uint16 sensor_id;	/*record sensor id defined in Kd_imgsensor.h*/
	kal_uint32 checksum_value;	/*checksum value for Camera Auto Test*/

	/*preview scenario relative information*/
	struct imgsensor_mode_struct pre;

	/* capture scenario relative information */
	struct imgsensor_mode_struct cap;

	struct imgsensor_mode_struct cap1;
	struct imgsensor_mode_struct normal_video;

	/* high speed video scenario relative information */
	struct imgsensor_mode_struct hs_video;

	/* slim video for VT scenario relative information */
	struct imgsensor_mode_struct slim_video;

	struct imgsensor_mode_struct custom1;
	struct imgsensor_mode_struct custom2;

	kal_uint8 ae_shut_delay_frame;	/* shutter delay frame for AE cycle */

	/* sensor gain delay frame for AE cycle */
	kal_uint8 ae_sensor_gain_delay_frame;
	kal_uint8 ae_ispGain_delay_frame;/* isp gain delay frame for AE cycle */
	kal_uint8 ihdr_support;	/* 1, support; 0,not support */
	kal_uint8 ihdr_le_firstline;	/* 1,le first ; 0, se first */
	kal_uint8 sensor_mode_num;	/* support sensor mode num */

	kal_uint8 cap_delay_frame;	/* enter capture delay frame num */
	kal_uint8 pre_delay_frame;	/* enter preview delay frame num */
	kal_uint8 video_delay_frame;	/* enter video delay frame num */

	/* enter high speed video  delay frame num */
	kal_uint8 hs_video_delay_frame;
	kal_uint8 slim_video_delay_frame; /* enter slim video delay frame num */

	kal_uint8  custom1_delay_frame;
	kal_uint8  custom2_delay_frame;

	kal_uint8 margin;	/* sensor framelength & shutter margin */
	kal_uint32 min_shutter;	/* min shutter */

	/* max framelength by sensor register's limitation */
	kal_uint32 max_frame_length;
	kal_uint8  isp_driving_current;
	kal_uint8  sensor_interface_type;
	kal_uint8  mipi_sensor_type;
	kal_uint8  mipi_settle_delay_mode;
	/*0, high speed signal auto detect; 1, use settle delay,unit is ns,
	 *default is auto detect, don't modify this para
	 */
	kal_uint8  sensor_output_dataformat;/*sensor output first pixel color*/
	kal_uint8  mclk; /*mclk value, suggest 24 or 26 for 24Mhz or 26Mhz*/

	kal_uint8  mipi_lane_num;		/*mipi lane num*/

	/*record sensor support all write id addr,
	 * only supprt 4must end with 0xff
	 */
	kal_uint8  i2c_addr_table[5];
	kal_uint32  i2c_speed;     //i2c speed
};
/* hs03s code for CAM-AL5625-01-247 by majunfeng at 2021/05/27 end */

extern int iReadRegI2C(u8 *a_pSendData, u16 a_sizeSendData, u8 *a_pRecvData,
				u16 a_sizeRecvData, u16 i2cId);
extern int iWriteRegI2C(u8 *a_pSendData, u16 a_sizeSendData, u16 i2cId);
extern void kdSetI2CSpeed(u16 i2cSpeed);
extern int iBurstWriteReg(u8 *pData, u32 bytes, u16 i2cId);

extern int iBurstWriteReg_multi(u8 *pData, u32 bytes, u16 i2cId,
			u16 transfer_length, u16 timing);
#endif
