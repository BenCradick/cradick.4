//
// Created by Ben Cradick on 2019-04-09.
//

#include "BitVector.h"

int checkBit(unsigned int bit_vector, unsigned int pos){
    return ((bit_vector & (1 << (pos%32))) != 0); //pos mod 32 because ints are 32 bit, if !0 bit at pos is on.
}

void setBit(unsigned int *bit_vector, unsigned int pos){
    *bit_vector |= 1 << (pos%32);
}
void clearBit(unsigned int *bit_vector, unsigned int pos) {
    *bit_vector &= ~(1 << pos%32);
}