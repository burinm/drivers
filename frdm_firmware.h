#ifndef __KL25Z_FIRMWARE_H__
#define __KL25Z_FIRMWARE_H__

#include "kl25z.arch/MKL25Z4.h"
#include <stdint.h>

#define FRDM_WAIT_8 \
    __asm__(        \
            "nop;"  \
            "nop;"  \
            "nop;"  \
            "nop;"  \
            "nop;"  \
            "nop;"  \
            "nop;"  \
            "nop;"  \
    );

enum return_value_e { FAILED =0, OK,
                        DMA_CHANNEL_ERROR,          //2
                        DMA_SIZE_ERROR,             //3        
                        DMA_SRC_ADDRESS_INVALID,    //4
                        DMA_DST_ADDRESS_INVALID,    //5
                        DMA_ADDRESS_CHECK_FAILED,   //6
                        DMA_CONFIGURATION_ERROR };  //7

// PWM/TPM Hardware 
enum rbg_color_e { RED, GREEN, BLUE };

typedef struct {
        uint8_t c;
        TPM_Type * TPM;
        uint8_t channel;
        int8_t brightness;
        uint8_t duty;
} color_addr_t;
color_addr_t COLORS_ADDR[3];

//DMA
#define DMA_ADDY_MASK       0xfff00000
#define DMA_MAX_SIZE        0x000fffff
#define DMA_ADDY_RANGE_0    0x00000000
#define DMA_ADDY_RANGE_1    0x1FF00000
#define DMA_ADDY_RANGE_2    0x20000000
#define DMA_ADDY_RANGE_3    0x40000000



//Initialize all clocks and turn on gates needed for this project
void frdm_clocks_init();

void setup_uart0();
void setup_uart1(uint32_t baud);

void start_uart0();
void stop_uart0();

// Turn on TPM channel for center aligned PWM
void setup_tpm_center(TPM_Type* tpm);

// Change duty cycle (percent) on TPM channel
void tpm_setup_duty(color_addr_t *c);
void tpm_set_duty(color_addr_t* c);

//Setup PIT timer
void setup_pit_timer();
void start_pit_timer();
void stop_pit_timer();
uint8_t is_pit_timer_running();
uint32_t pit_read_timer0(); 



void red_gpio_mode();
void green_gpio_mode();
void blue_gpio_mode();

//TODO: Move these to a utility file
//Put LEDs into GPIO mode for quick use
void set_leds(uint8_t s);
void led_set_color();
void blue_led_on();
void blue_led_off();

// colors
#define NUM_RGB 8
#define RED_BITS     (0x1)
#define GREEN_BITS   (0x2)
#define BLUE_BITS    (0x4)

void led_brightness_increase(color_addr_t*);
void led_brightness_decrease(color_addr_t*);

//DMA
void setup_dma0();
void disable_dma0();

typedef enum _dma_channel_e { DMA_CHANNEL0 =0, DMA_CHANNEL1,DMA_CHANNEL2,DMA_CHANNEL3} dma_channel_e;
uint8_t _dma0_memmove(uint8_t channel, uint32_t *source, uint32_t *dest, uint32_t size, uint8_t tsize);

uint8_t dma0_memmove_8(uint8_t channel, uint32_t *source, uint32_t *dest, uint32_t size);

uint8_t dma0_memmove(uint8_t channel, uint32_t *source, uint32_t *dest, uint32_t size);

uint8_t _is_valid_dma_address(uint32_t *addy);
uint8_t is_dma_done(uint8_t channel); 



#endif
