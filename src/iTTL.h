/**
 * @file iTTL.h
 *
 * Class declaration for iTTL class  and helper enums
 */

/**
 * iTTL commands defined on the bus
 *
 * Each command is sent by the camera to the flash
 */

typedef enum iTTL_Command {
    Flash_Setting = 0xa0,		//!< flash Settings,  send by flash
    Init_0 = 0xa1,              //!< first frame after camera switched on or flash detected, send by flash
    init_1 = 0xb1,              //!< second frame after camera switched on or flash detected, send by camera
    init_2 = 0xa2,              //!< third frame after camera switched on or flash detected, send by flash
    Cam_setting = 0xb0,         //!< camera setting, send by camera
    Postflash_1 = 0xc0,         //!< send after flash by flash
    Postflash_2 = 0xc0,         //!< send after flash by flash
    AF_Illumination = 0xd0,		//!< set AF illumination, send by camera
    Red_Eye_Reduction = 0xd1,	//!< set red eye reductuin, send by camera
    Modelling_Light = 0xd5,		//!< set modelling light, send by camera
    Preflash_1 = 0xd7,          //!< used to determine power, sent by camera
    Preflash_2 = 0xd8,          //!< used if first preflash was not strong enough, send by camera
    Flash_Power = 0xd3          //!< set flash power before flash, sent by camera
} iTLL_Command_e;

/**
 * Init 0 Message Definition
 *
 * 17 Bytes long
 * Purpose unkown
 */

typedef struct iTTL_Init_0_Msg {
    uint8_t[17] Unknown         //!< Unknown
} iTTL_Init_0_Msg_t;

typedef struct iTTL_Init_1_Msg {
    uint8_t[9] Unknown          //!< Unknown
} TTL_Init_1_Msg_t;

typedef struct iTTL_Init_2_Msg {
    uint8_t[45] Unknown         //!< Unknown
} iTTL_Init_2_Msg_t;

typedef struct iTTL_Flash_Setting_Msg {
    struct Status {
    Ready_Light: 1              //!< Set of ready light is on
        Display : 1             //!< Display illumination
        Reflector : 1	//!< clear if reflector facing fwd and not tilted, otherwise set
        Ready_Flash : 1	//!< Set of ready light is flashing
        Diffuser : 1	//!< Diffuser pulled out
        Soft_box : 1	//! Soft box attached
        False_0 : 1	//!< always 0
        False_1 : 1	//!< always 0
    }
    uint8_t Mode,	//!< 1= TTL/BL, 2=TTL, 3=AA, 4=A, 5=GN, 6=M, 7=RPT
    uint8_t Unknown_3,	//!< Always Unknown_8 + 102d
    struct Activity {
        button : 1	//!< Set for 1s after button press and for 5s if power of flash was not sufficient
        false_0 : 1 	//!< always 0
        true_0 : 1	//!< always 1
        mode_A_0 : 1	//!< Flash in mode A
        AF_Assist : 1	//!< AF assist light on
        false_1 : 1 	//!< always 0
        mode_A_1 : 1	//!< Flash in mode A
        false_2 : 1 	//!< always 0
    }
    uint8_t Unknown_5,	//!< Always 0d
    uint8_t Flash_Power,	//!< Output power 2^(-x / 6)
    uint8_t Unknown_7,	//!< Always Unknown_8 + 3 4d
    uint8_t Unknown_8,	//!< Reappears modified in Unknown_3 and Unknown_7
    uint8_t Unknown_9,	//!< Always 48d
    uint8_t	Reflector,	//!< zoom setting of reflector, focal length in mm
    uint8_t Strobo_Freq,	//!< Stroboscope frequency
    uint8_t Strobo_Num,	//!< Stroboscope number of flashes
    uint8_t Unknown_13,	//!< Unknown
    uint8_t Unknown_14,	//!< Unknown
    uint8_t Unknown_15,	//!< Unknown
    uint8_t Unknown_16,	//!< Unknown
    uint8_t CLS,		//!< Related to CLS setting, unknown
    uint8_t Menu,		//!< Changes when flash menu is accessed
    uint8_t CLS_Grp[3],	//!< Flash exposure compensation or flash power of CLS Groups A-C
} iTTL_Flash_Setting_Msg_t;

typedef struct iTTL_Camera_Setting_Msg {
    uint8_t Mode,		//!< Flash Mode, 0x00=AA/FP, 0x01=TTL/FP, 0x02,0x04=TTL/BL/FP, 0x05=TTL/BL, 0x08=AA/FP
    struct Configuration {
        Sync : 1	//!< Sync on 2nd curtain
        Red_Eye : 1	//!< Red Eye reduction
        Display : 1	//!< Camera display on
        False_0	: 1	//!< always 0
        FP_Req : 1 	//!< FP required
        FP_Avail : 1	//!< FP Available
        TTL_AVail : 1 	//!< TTL Available
        False_1 : 1     //!< always 0
    }
    uint8_t	Unknown_3,	//!< Unknown
    uint8_t	ISO,		//!< ISO Setting, ISO = 100 * 2^((x-30) / 6)
    uint8_t Exposure,	//!< Exposure time t[s] = 2^(-x / 6), 128d is bulb mode
    uint8_t F_Stop,		//!< f-Stop = 2^(x / 12)
    uint8_t Focal_Length, 	//!< f[mm] = 2^((x+55.4) / 24)
    uint8_t	Flash_Exp,	//!< Flash Exposure Compensation EV[stops] =-x / 6
    uint8_t Unknown_9,	//!< Always 0x30
    uint8_t Distance,	//!< Acrtual focus distance d[m]=2^((x-80) / 6)
    uint8_t Unknown_11,	//!< Strange value, seems to be combination of focal length and focus distance
    uint8_t Unknwon_12,	//!< Seems to be F-Stop, but changes +/- 1
    uint8_t Unknown_13,	//!< Seems to be related to ISO
    uint8_t Unknown_14	//!< Seems to be related to ISO
} iTTL_Camera_Setting_Msg_t;

typedef struct iTTL_Postflash_1_Msg {
    uint8_t Unknown 	//!< Unknown
} iTTL_Postflash_1_Msg_t;

typedef struct iTTL_Postflash_2_Msg {
    uint8_t Unknown[2] 	//!< Unknown
} iTTL_Postflash_2_Msg_t;

typedef struct iTTL_AF_Ill_Msg {
    uint8_t Enable 		//!< 0x01 = Enable, 0x00 = Disable AF Illumation light
    uint8_t False_1		//!< always 0
} iTTL_AF_Ill_Msg_t;

typedef struct iTTL_Red_Eye_Reduction_Msg {
    uint8_t Enable 		//!< 0x80 = Enable, 0x00 = Disable Red Eye reduction flashes
} iTTL_Red_Eye_Reduction_Msg_t;


typedef struct iTTL_Modelling_Light_Msg {
    uint8_t Enable 		//!< 0xD5 = Enable, flash fires flashes for 1,5s
} iTTL_Modelling_Light_Msg_t;

typedef struct iTTL_Preflash_2_Msg {
    uint8_t Power 		//!< 0d = weakest Power, 9d = 1/128+2/3ev, 24 maximum  1/32+1/3ev
} iTTL_Preflash_2_Msg_t;


/**
 * Driver for iTTL Protocol
 */

class iTTL
{
    /**
     * Arduino Constructor
     *
     * Creates a new instance of this driver.  Before using, you create an instance
     * and send in the unique pins that this chip is connected to.
     *
     * @param SyncPin   The pin attached to sync connector of the hotshoe
     * @param AckPin    The pin attached to ack connector of the hotshoe
     * @param DataPin   The pin attached to data connector of the hotshoe
     * @param ClockPin  The pin attached to clock connector of the hotshoe
     */
    
    iTTL(uint8_t SyncPin, uint8_t AckPin, uint8_t DataPin, uint8_t ClockPin);
/*
    //
    begin
	end
// status
BOOL isflashPresent
BOOL getFlashSetting()
	// Low Level Routines
	Listen
	Dump
	Send 
	Receive
	// High Level Routines
	sendCameraOff
	sendFlashPower
	sendModellingLight
	sendRedEye(BOOL)
	flash
Private:
	BOOL startTransfer
	BOOL receiveByte
	BOOL sendByte
	BOOL endTransfer
	uint8_t CRC (payload) 
	unit8_t getPayLoadSize(iTTLCommand);
*/
};


/**
 * @mainpage iTTL Protocol driver for Nikon SB flashes
 *
 * @section Credtits
 *
 * @li <a href="http://cms.diodenring.de/electronic/microcontroller/110-ittlanalysis">iTTL Protocol Analysis</a>
 * @li <a href="http://dptnt.com/2010/04/nikon-flash-interface/">Hardware Analysis</a>
 */