//
// Created by Ben Cradick on 2019-04-09.
//

#include "Bit_Vector.h"

int checkBit(unsigned int bitVector, unsigned int pos){
    return ((bitVector & (1 << (pos%32))) != 0); //pos mod 32 because ints are 32 bit, if !0 bit at pos is on.
}

void setBit(unsigned int *bitVector, unsigned int pos){
    *bitVector |= 1 << (pos%32);
}
void clearBit(unsigned int *bitVector, unsigned int pos) {
    *bitVector &= ~(1 << pos%32);
}