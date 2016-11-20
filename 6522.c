#include "6522.h"


inline void device_6522_init(uint8_t *a) {
}

inline void device_6522_set_dda_out(uint8_t *a, uint8_t bit_n) {
    *(a + DEVICE_6522_REG_DDRA) = *(a + DEVICE_6522_REG_DDRA) | (1<<bit_n); 
}

inline void device_6522_set_dda_in(uint8_t *a, uint8_t bit_n) {
    *(a + DEVICE_6522_REG_DDRA) = *(a + DEVICE_6522_REG_DDRA) & ~(1<<bit_n); 
}

inline void device_6522_set_ddb_out(uint8_t *a, uint8_t bit_n) {
    *(a + DEVICE_6522_REG_DDRB) = *(a + DEVICE_6522_REG_DDRB) | (1<<bit_n); 
}

inline void device_6522_set_ddb_out(uint8_t *a, uint8_t bit_n) {
    *(a + DEVICE_6522_REG_DDRB) = *(a + DEVICE_6522_REG_DDRB) & ~(1<<bit_n); 
}

inline uint8_t device_6522_read_a(uint8_t *a) {
return *(a + DEVICE_6522_REG_RA);
}

inline uint8_t device_6522_read_b(uint8_t *a) {
return *(a + DEVICE_6522_REG_RB);
}

inline void device_6522_write_a(uint8_t *a, uint8_t b) {
    *(a + DEVICE_6522_REG_RA) = b;
}

inline void device_6522_write_b(uint8_t *a, uint8_t b) {
    *(a + DEVICE_6522_REG_RB) = b;
}
~                                                                                                       
~                                          
