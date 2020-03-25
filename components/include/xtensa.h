#ifndef H_XTENSA
#define H_XTENSA

unsigned int get_ccount();
unsigned int get_ccompare0();
unsigned int get_ccompare1();
unsigned int get_ccompare2();

void set_ccompare0(unsigned int val);
void set_ccompare1(unsigned int val);
void set_ccompare2(unsigned int val);


#endif
