/* tsl2651.h - (c) 2017 - burin

    tsl2651 i2c Ambient Light Sensor driver

    Extends i2c.h
*/

#include "i2c.h"

#ifndef __TSL2651_H__
#define __TSL2651_H__

#include <stdint.h>

#define DEVICE_I2C_TSL2651  0x9 //1001b
#define TSL2651_SEL_ADDR_FLOAT   0x3 // floating selection on baoed
#define TSL2651_SEL_ADDR_GND     0x2 // floating selection on baoed
#define TSL2651_SEL_ADDR_VDD     0x4 // floating selection on baoed

#define TSL2651_ADDRESS         (TSL2651_SEL_ADDR_FLOAT<< I2C_ID_MSB_BIT_MASK)

#define TSL2651_REG_CMD           (1<<7)
#define TSL2651_REG_CLEAR         (1<<6)
#define TSL2651_REG_WORD          (1<<5)
#define TSL2651_REG_BLOCK         (1<<4)
#define TSL2651_REG_ADDR_MASK     0xf

// Register addresses                    0x0 - 0xf
#define TSL2651_ADDR_CONTROL             0x0
    #define TSL2651_CONTROL_RESV_MASK           0xfc
    #define TSL2651_CONTROL_POWER_MASK          0x3
#define TSL2651_ADDR_TIMING              0x1
    #define TSL2651_TIMING_RESV1_MASK           0xe0
    #define TSL2651_TIMING_GAIN                 (1<<4) 
    #define TSL2651_TIMING_MANUAL               (1<<3) 
    #define TSL2651_TIMING_RESV2                (1<<2) //always write 0 
    #define TSL2651_TIMING_INTEG_MASK           0x3 
         #define TSL2651_TIMING_INTEG_13_7_MS          0x0
         #define TSL2651_TIMING_INTEG_101_MS           0x1
         #define TSL2651_TIMING_INTEG_402_MS           0x2
#define TSL2651_ADDR_THRESHLOW_LOWB      0x2
#define TSL2651_ADDR_THRESHLOW_HIGHB     0x3
#define TSL2651_ADDR_THRESHHIGH_LOWB     0x4
#define TSL2651_ADDR_THRESHHIGH_HIGHB    0x5
#define TSL2651_ADDR_INT                 0x6
    #define TSL2651_INT_RESV_MASK               0xc0 
    #define TSL2651_INT_CTRL_MASK               0x30
    #define TSL2651_INT_CTRL_SHIFT              4 
        #define TSL2651_INT_CTRL_DISABLE               (0x0 << TSL2651_INT_CTRL_SHIFT)
        #define TSL2651_INT_CTRL_LEVEL                 (0x1 << TSL2651_INT_CTRL_SHIFT)
        #define TSL2651_INT_CTRL_SMB_CMPLY             (0x2 << TSL2651_INT_CTRL_SHIFT)
        #define TSL2651_INT_CTRL_TEST                  (0x3 << TSL2651_INT_CTRL_SHIFT)
    #define TSL2651_INT_PERSIST_MASK            0xf
        #define TSL2651_INT_PERSIST_EVERY              0x0
        #define TSL2651_INT_PERSIST_ANY                0x1
        #define TSL2651_INT_PERSIST_2                  0x2
        #define TSL2651_INT_PERSIST_3                  0x3
        #define TSL2651_INT_PERSIST_4                  0x4
        #define TSL2651_INT_PERSIST_5                  0x5
        #define TSL2651_INT_PERSIST_6                  0x6
        #define TSL2651_INT_PERSIST_7                  0x7
        #define TSL2651_INT_PERSIST_8                  0x8
        #define TSL2651_INT_PERSIST_9                  0x9
        #define TSL2651_INT_PERSIST_10                 0xa
        #define TSL2651_INT_PERSIST_11                 0xb
        #define TSL2651_INT_PERSIST_12                 0xc
        #define TSL2651_INT_PERSIST_13                 0xd
        #define TSL2651_INT_PERSIST_14                 0xe
        #define TSL2651_INT_PERSIST_15                 0xf
#define TSL2651_ADDR_RES_1               0x7
#define TSL2651_ADDR_CRC                 0x8
#define TSL2651_ADDR_RES_2               0x9
#define TSL2651_ADDR_ID                  0xa
    #define TSL2651_ID_PARTNO_MASK             0xf0
    #define TSL2651_ID_REVNO_MASK              0x0f
#define TSL2651_ADDR_RES_3               0xb
#define TSL2651_ADDR_DATA0_LOWB          0xc
#define TSL2651_ADDR_DATA0_HIGHB         0xd
#define TSL2651_ADDR_DATA1_LOWB          0xe
#define TSL2651_ADDR_DATA1_HIGHB         0xf

// Called to initialize and reset sensor 
void tsl2651_open();

// Called to turn off I2C GPIOs 
void tsl2651_close(); 

// Turn on/off device
void tsl2651_on(uint8_t on);

// Clear interrupt
void tsl2651_int_clear();


// Read register from sensor 
uint8_t tsl2651_read_register(uint8_t reg);

// Write register to sensor
void tsl2651_write_register(uint8_t reg, uint8_t b);

// Read 2 byte register from sensor 
uint16_t tsl2651_read_register16(uint16_t addy, uint16_t reg);

// Write 2 byte register to sensor
void tsl2651_write_register16(uint16_t addy, uint16_t reg, uint16_t b);


#endif
