#include "xtensa.h"

unsigned int get_ccount() {
    unsigned int ccount;
    __asm__ __volatile__ (
    "rsr    %0, ccount"
    : "=a" (ccount) : : "memory" );
    return ccount;
}

unsigned int get_ccompare0() {
    unsigned int ccount;
    __asm__ __volatile__ (
    "rsr    %0, ccompare0"
    : "=a" (ccount) );
    return ccount;
}

unsigned int get_ccompare1() {
    unsigned int ccount;
    __asm__ __volatile__ (
        "rsr    %0, ccompare1"
        : "=a" (ccount) );
    return ccount;
}

unsigned int get_ccompare2() {
    unsigned int ccount;
    __asm__ __volatile__ (
        "rsr    %0, ccompare2"
        : "=a" (ccount) );
    return ccount;
}

void set_ccompare0(unsigned int val) {
    __asm__ __volatile__ (
        "wsr    %0, ccompare0 \n"
        "isync \n"
        : : "a" (val) );
}

void set_ccompare1(unsigned int val) {
    __asm__ __volatile__ (
        "wsr    %0, ccompare1 \n"
        "isync \n"
        : : "a" (val) );
}

void set_ccompare2(unsigned int val) {
    __asm__ __volatile__ (
        "wsr    %0, ccompare2 \n"
        "isync \n"
        : : "a" (val) );
}
