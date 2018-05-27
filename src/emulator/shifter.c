#include<stdint.h>
#include"shifter.h"
#include<assert.h>
#define C_BIT 29
#define LSL_MASK 1<<31
#define LSR_MASK 1
#define ASL_MASK 1<<31
#define ROR_MASK 1

uint32_t shift(uint32_t a, uint32_t b, Shift_Type type, int32_t *cpsr) {
    assert(cpsr);
    uint32_t res;
    int32_t c = 0;

    switch(type) {
        case LSL:
            res = shift_lsl(a, b, &c);
            break;
        case LSR:
            res = shift_lsr(a, b, &c);
            break;
        case ASR:
            res = shift_asr(a, b, &c);
            break;
        case ROR:
            res = shift_ror(a, b, &c);
            break;
    }
    

    if (c) {
        *cpsr = (*cpsr) | (1 << C_BIT); 
    }

    return res;
}

uint32_t shift_lsl(uint32_t a, uint32_t b,int32_t *c) {
   
    while(b) {
        *c = (*c || (a & LSL_MASK));
        a <<= 1;
        b--;
    }
    return a;   
}

uint32_t shift_lsr(uint32_t a, uint32_t b,int32_t *c) {
    
    while (b) {
        *c = (*c || (a & LSR_MASK));
        a >>= 1;
        b--;
    }
    return a;   
}

uint32_t shift_asr(uint32_t a, uint32_t b,int32_t *c) {
 
    int32_t r = (int32_t) a;
    while(b) {
        *c = (*c || (r & ASL_MASK));
        r >>= 1;
        b--;
    }
    return (uint32_t) r;    
}

uint32_t shift_ror(uint32_t a, uint32_t b,int32_t *c) {
    
    while(b) {
        *c = (*c || (a & ROR_MASK));
        uint32_t tmp = (a & 1U) << 31;
        a >>= 1;
        a |= tmp;
        b--;
    }
    return a;   
}
