/*  mma8452q.h - (c) 2017 - burin

     mma8452q i2c accelerometer driver

    Extends i2c.h
*/

#include "i2c.h"

#ifndef __MMA8452Q_H__
#define __MMA8452Q_H__

#include <stdint.h>

/* TODO: This whole addressing scheme needs to be redone
    It was originally written for an I2C eeprom, but does
    not fit into the general I2C addressing. Leaving for
    now because tsl2651 driver needs to be corrected too
*/
 
#define MMA8452Q_MSB        0x1 //001
#define MMA8452Q_ADDRESS    (MMA8452Q_MSB << I2C_LSB_BITS) 

//1101b - SA0 = 1  (sparkfun board open = pulled high),  0011101 = 0x1D
#define MMA8452Q_SEL_VDD     0xd
//1100b - SA0 = 0  (sparkfun board closed = pulled low),  0011100 = 0x1C
#define MMA8452Q_SEL_GND     0xc

#define DEVICE_I2C_MMA8452Q  MMA8452Q_SEL_VDD 


// Register addresses                   0x0 - 0x31
#define MMA8452Q_REG_STATUS             0x0
    #define MMA8452Q_STATUS_XDR                 (1<<0)
    #define MMA8452Q_STATUS_YDR                 (1<<1)
    #define MMA8452Q_STATUS_ZDR                 (1<<2)
    #define MMA8452Q_STATUS_ZYXDR               (1<<3)
    #define MMA8452Q_STATUS_XOW                 (1<<4)
    #define MMA8452Q_STATUS_YOW                 (1<<5)
    #define MMA8452Q_STATUS_ZOW                 (1<<6)
    #define MMA8452Q_STATUS_ZYXOW               (1<<7)
#define MMA8452Q_REG_OUT_X_MSB          0x1
    #define MMA8452Q_OUT_X_MSB_MASK             0xff
#define MMA8452Q_REG_OUT_X_LSB          0x2
    #define MMA8452Q_REG_X_LSB_MASK             0xf0
    #define MMA8452Q_REG_X_LSB_SHIFT            4 
#define MMA8452Q_REG_OUT_Y_MSB          0x3
    #define MMA8452Q_OUT_Y_MSB_MASK             0xff
#define MMA8452Q_REG_OUT_Y_LSB          0x4
    #define MMA8452Q_REG_Y_LSB_MASK             0xf0
    #define MMA8452Q_REG_Y_LSB_SHIFT            4 
#define MMA8452Q_REG_OUT_Z_MSB          0x5
    #define MMA8452Q_OUT_Z_MSB_MASK             0xff
#define MMA8452Q_REG_OUT_Z_LSB          0x6
    #define MMA8452Q_REG_Z_LSB_MASK             0xf0
    #define MMA8452Q_REG_Z_LSB_SHIFT            4 
#define MMA8452Q_REG_RES1               0x7
#define MMA8452Q_REG_RES2               0x8
#define MMA8452Q_REG_SYSMOD             0xb
    #define MMA8452Q_SYSMOD_MASK                0x3
    #define MMA8452Q_SYSMOD_STANDBY             0x0 
    #define MMA8452Q_SYSMOD_WAKE                0x1 
    #define MMA8452Q_SYSMOD_SLEEP               0x2
#define MMA8452Q_REG_INT_SOURCE         0xc
    #define MMA8452Q_INT_SRC_DRDY               (1<<0)
    #define MMA8452Q_INT_SRC_FF_MNT             (1<<2)
    #define MMA8452Q_INT_SRC_PULSE              (1<<3)
    #define MMA8452Q_INT_SRC_LNDPRT             (1<<4)
    #define MMA8452Q_INT_SRC_TRANS              (1<<5)
    #define MMA8452Q_INT_SRC_ASLP               (1<<7)
#define MMA8452Q_REG_WHO_AM_I           0xd
    #define MMA8452Q_WHO_AM_I                   0x2a    //always reads this 
#define MMA8452Q_REG_XYZ_DATA_CFG       0xe
    #define MMA8452Q_XYZ_DATA_CFG_FS_MASK       0x3
        #define MMA8452Q_XYZ_DATA_CFG_FS_2          0x0
        #define MMA8452Q_XYZ_DATA_CFG_FS_4          0x1
        #define MMA8452Q_XYZ_DATA_CFG_FS_8          0x2
        #define MMA8452Q_XYZ_DATA_CFG_FS_RES        0x3
#define MMA8452Q_REG_HP_FILTER_CUTOFF   0xf
    #define MMA8452Q_HP_FILTER_CUTOFF_SEL0      (1<<0) 
    #define MMA8452Q_HP_FILTER_CUTOFF_SEL1      (1<<1) 
    #define MMA8452Q_HP_FILTER_CUTOFF_PULSE_LPF_EN      (1<<4) 
    #define MMA8452Q_HP_FILTER_CUTOFF_PULSE_HPF_BYP     (1<<5) 
#define MMA8452Q_REG_PL_STATUS          0x10
    #define MMA8452Q_PL_STATUS_BARFRO           (1<<0) 
        #define MMA8452Q_PL_STATUS_BARFRO_FRONT         0x0 
        #define MMA8452Q_PL_STATUS_BARFRO_BACK          0x1 
    #define MMA8452Q_PL_STATUS_LAPO_SHIFT       1 
    #define MMA8452Q_PL_STATUS_LAPO_MASK        (3<<MMA8452Q_PL_STATUS_LAPO_SHIFT) 
        #define MMA8452Q_PL_STATUS_LAPO_PRTUP       0x0 
        #define MMA8452Q_PL_STATUS_LAPO_PRTDOWN     0x1 
        #define MMA8452Q_PL_STATUS_LAPO_LANDRIGHT   0x2 
        #define MMA8452Q_PL_STATUS_LAPO_LANDLEFT    0x3 
#define MMA8452Q_REG_PL_CFG             0x11
    #define MMA8452Q_PL_CFG_PL_EN               (1<<6) 
    #define MMA8452Q_PL_CFG_DBCNTM              (1<<7) 
#define MMA8452Q_REG_PL_COUNT           0x12
#define MMA8452Q_REG_PL_BF_ZCOMP        0x13
    #define MMA8452Q_PL_BF_ZCOMP_ZLOCK_MASK     0x07 
    #define MMA8452Q_PL_BF_ZCOMP_BKFR_MASK      0xc0
#define MMA8452Q_REG_P_L_THS_REG        0x14
    #define MMA8452Q_P_L_THS_REG_HYS_MASK       0x07 
    #define MMA8452Q_P_L_THS_REG_P_L_THS_MASK   0xf8
#define MMA8452Q_REG_FF_MT_CFG          0x15
    #define MMA8452Q_FF_MT_CFG_XEFE             (1<<3) 
    #define MMA8452Q_FF_MT_CFG_YEFE             (1<<4) 
    #define MMA8452Q_FF_MT_CFG_ZEFE             (1<<5) 
    #define MMA8452Q_FF_MT_CFG_OAE              (1<<6) 
    #define MMA8452Q_FF_MT_CFG_ELE              (1<<7) 
#define MMA8452Q_REG_FF_MT_SRC          0x16
    #define MMA8452Q_FF_MT_SRC_XHP              (1<<0) 
    #define MMA8452Q_FF_MT_SRC_XHE              (1<<1) 
    #define MMA8452Q_FF_MT_SRC_YHP              (1<<2) 
    #define MMA8452Q_FF_MT_SRC_YHE              (1<<3) 
    #define MMA8452Q_FF_MT_SRC_ZHP              (1<<4) 
    #define MMA8452Q_FF_MT_SRC_ZHE              (1<<5) 
    #define MMA8452Q_FF_MT_SRC_EA               (1<<7) 
#define MMA8452Q_REG_FF_MT_THS          0x17
    #define MMA8452Q_FF_MT_THS_MASK             0x7f         
    #define MMA8452Q_FF_MT_THS_DBCNTM           (1<<7)         
    #define MMA8452Q_FF_MT_THS_DBCNTM_CLEAR           0x1         
    #define MMA8452Q_FF_MT_THS_DBCNTM_DECREMENT       0x0         
#define MMA8452Q_REG_FF_MT_COUNT        0x18
#define MMA8452Q_REG_RES3               0x19
#define MMA8452Q_REG_RES4               0x1a
#define MMA8452Q_REG_RES5               0x1b
#define MMA8452Q_REG_RES6               0x1c
#define MMA8452Q_REG_TRANSIENT_CFG      0x1d
    #define MMA8452Q_TRANSIENT_CFG_HPF_BYP      (1<<0) 
    #define MMA8452Q_TRANSIENT_CFG_XTEFE        (1<<1) 
    #define MMA8452Q_TRANSIENT_CFG_YTEFE        (1<<2) 
    #define MMA8452Q_TRANSIENT_CFG_ZTEFE        (1<<3) 
    #define MMA8452Q_TRANSIENT_CFG_ELE          (1<<4) 
#define MMA8452Q_REG_TRANSIENT_SRC      0x1e
    #define MMA8452Q_TRANSIENT_SRC_X_TRANS_POL  (1<<0) 
    #define MMA8452Q_TRANSIENT_SRC_XTRANSE      (1<<1) 
    #define MMA8452Q_TRANSIENT_SRC_Y_TRANS_POL  (1<<2) 
    #define MMA8452Q_TRANSIENT_SRC_YTRANSE      (1<<3) 
    #define MMA8452Q_TRANSIENT_SRC_Z_TRANS_POL  (1<<4) 
    #define MMA8452Q_TRANSIENT_SRC_ZTRANSE      (1<<5) 
    #define MMA8452Q_TRANSIENT_SRC_EA           (1<<6) 
#define MMA8452Q_REG_TRANSIENT_THS      0x1f
    #define MMA8452Q_TRANSIENT_THS_MASK         0x7f 
    #define MMA8452Q_TRANSIENT_THS_DBCNTM       (1<<7) 
#define MMA8452Q_REG_TRANSIENT_COUNT    0x20
#define MMA8452Q_REG_PULSE_CFG          0x21
    #define MMA8452Q_PULSE_CFG_XSPEFE           (1<<0) 
    #define MMA8452Q_PULSE_CFG_XDPEFE           (1<<1) 
    #define MMA8452Q_PULSE_CFG_YSPEFE           (1<<2) 
    #define MMA8452Q_PULSE_CFG_YDPEFE           (1<<3) 
    #define MMA8452Q_PULSE_CFG_ZSPEFE           (1<<4) 
    #define MMA8452Q_PULSE_CFG_ZDPEFE           (1<<5) 
    #define MMA8452Q_PULSE_CFG_ELE              (1<<6) 
    #define MMA8452Q_PULSE_CFG_DPA              (1<<7) 
#define MMA8452Q_REG_PULSE_SRC          0x22
    #define MMA8452Q_PULSE_SRC_POLX             (1<<0) 
    #define MMA8452Q_PULSE_SRC_POLY             (1<<1) 
    #define MMA8452Q_PULSE_SRC_POLZ             (1<<2) 
    #define MMA8452Q_PULSE_SRC_DPE              (1<<3) 
    #define MMA8452Q_PULSE_SRC_AXX              (1<<4) 
    #define MMA8452Q_PULSE_SRC_AXY              (1<<5) 
    #define MMA8452Q_PULSE_SRC_AXZ              (1<<6) 
    #define MMA8452Q_PULSE_SRC_EA               (1<<7) 
#define MMA8452Q_REG_PULSE_THSX         0x23
#define MMA8452Q_REG_PULSE_THSY         0x24
#define MMA8452Q_REG_PULSE_THSZ         0x25
    #define MMA8452Q_REG_PULSE_THS_MASK         0x7f
#define MMA8452Q_REG_PULSE_TMLT         0x26
#define MMA8452Q_REG_PULSE_LTCY         0x27
#define MMA8452Q_REG_PULSE_WIND         0x28
#define MMA8452Q_REG_ASLP_COUNT         0x29
#define MMA8452Q_REG_CTRL_REG1          0x2a
    #define MMA8452Q_CTRL_REG1_ACTIVE           (1<<0) 
    #define MMA8452Q_CTRL_REG1_F_READ           (1<<1) 
    #define MMA8452Q_CTRL_REG1_LNOISE           (1<<2) 
    #define MMA8452Q_CTRL_REG1_DR_SHIFT         3 
    #define MMA8452Q_CTRL_REG1_DR_MASK          0x38 
        #define MMA8452Q_CTRL_REG1_DR_800               0x0
        #define MMA8452Q_CTRL_REG1_DR_400               0x1
        #define MMA8452Q_CTRL_REG1_DR_200               0x2
        #define MMA8452Q_CTRL_REG1_DR_100               0x3
        #define MMA8452Q_CTRL_REG1_DR_50                0x4
        #define MMA8452Q_CTRL_REG1_DR_12_5              0x5
        #define MMA8452Q_CTRL_REG1_DR_6_25              0x6
        #define MMA8452Q_CTRL_REG1_DR_1_56              0x7
    #define MMA8452Q_CTRL_REG1_ASLP_RATE_SHIFT  6 
    #define MMA8452Q_CTRL_REG1_ASLP_RATE_MASK   0xc0 
        #define MMA8452Q_CTRL_REG1_ASLP_RATE_50         0x0 
        #define MMA8452Q_CTRL_REG1_ASLP_RATE_12_5       0x1 
        #define MMA8452Q_CTRL_REG1_ASLP_RATE_6_25       0x2 
        #define MMA8452Q_CTRL_REG1_ASLP_RATE_1_56       0x3 
#define MMA8452Q_REG_CTRL_REG2          0x2b
    #define MMA8452Q_CTRL_REG2_MODS_MASK        0x3 
    #define MMA8452Q_CTRL_REG2_SLPE             (1<<2) 
    #define MMA8452Q_CTRL_REG2_SMODS_MASK       0x18 
    #define MMA8452Q_CTRL_REG2_SMODS_RST        (1<<6) 
    #define MMA8452Q_CTRL_REG2_SMODS_ST         (1<<7) 
#define MMA8452Q_REG_CTRL_REG3          0x2c
    #define MMA8452Q_CTRL_REG3_PP_OD            (1<<0) 
    #define MMA8452Q_CTRL_REG3_IPOL             (1<<1) 
    #define MMA8452Q_CTRL_REG3_WAKE_FF_MT       (1<<3) 
    #define MMA8452Q_CTRL_REG3_WAKE_PULSE       (1<<4) 
    #define MMA8452Q_CTRL_REG3_WAKE_LNDPRT      (1<<5) 
    #define MMA8452Q_CTRL_REG3_WAKE_TRANS       (1<<6) 
#define MMA8452Q_REG_CTRL_REG4          0x2d
    #define MMA8452Q_CTRL_REG4_INT_EN_DRDY      (1<<0) 
    #define MMA8452Q_CTRL_REG4_INT_EN_FF_MT     (1<<2) 
    #define MMA8452Q_CTRL_REG4_INT_EN_PULSE     (1<<3) 
    #define MMA8452Q_CTRL_REG4_INT_EN_LNDPRT    (1<<4) 
    #define MMA8452Q_CTRL_REG4_INT_EN_TRANS     (1<<5) 
    #define MMA8452Q_CTRL_REG4_INT_EN_ASLP      (1<<7) 
#define MMA8452Q_REG_CTRL_REG5          0x2e
    #define MMA8452Q_CTRL_REG5_INT_CFG_DRDY      (1<<0) 
    #define MMA8452Q_CTRL_REG5_INT_CFG_FF_MT     (1<<2) 
    #define MMA8452Q_CTRL_REG5_INT_CFG_PULSE     (1<<3) 
    #define MMA8452Q_CTRL_REG5_INT_CFG_LNDPRT    (1<<4) 
    #define MMA8452Q_CTRL_REG5_INT_CFG_TRANS     (1<<5) 
    #define MMA8452Q_CTRL_REG5_INT_CFG_ASLP      (1<<7) 
#define MMA8452Q_REG_OFF_X              0x2f
#define MMA8452Q_REG_OFF_Y              0x30
#define MMA8452Q_REG_OFF_Z              0x31


// Called to initialize and reset sensor 
void mma8452q_open();

// Called to turn off I2C GPIOs 
void mma8452q_close(); 

// Turn on/off device
/* Checks for device WHO_AM_I 0x2a
       returns true on ON, if I2C communication success with ID
       returns false on OFF, always 
*/ 
uint8_t mma8452q_on(uint8_t on);

// Clear interrupt
void mma8452q_int_clear();

// Read register from sensor 
uint8_t mma8452q_read_register(uint8_t reg);

// Write register to sensor
void mma8452q_write_register(uint8_t reg, uint8_t b);

#endif
