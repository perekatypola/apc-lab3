#include <dos.h>
#include <stdio.h>

struct VIDEO
{
 unsigned char symb;
 unsigned char attr;
};

void get_reg();
unsigned char col = 0x5E;

void interrupt(*old08) (...);
void interrupt(*old09) (...);
void interrupt(*old0A) (...);
void interrupt(*old0B) (...);
void interrupt(*old0C) (...);
void interrupt(*old0D) (...);
void interrupt(*old0E) (...);
void interrupt(*old0F) (...);

void interrupt(*old78) (...);
void interrupt(*old79) (...);
void interrupt(*old80) (...);
void interrupt(*old81) (...);
void interrupt(*old82) (...);
void interrupt(*old83) (...);
void interrupt(*old84) (...);
void interrupt(*old85) (...);

void interrupt new08(...);
void interrupt new09(...);
void interrupt new0A(...);
void interrupt new0B(...);
void interrupt new0C(...);
void interrupt new0D(...);
void interrupt new0E(...);
void interrupt new0F(...);

void interrupt new78(...);
void interrupt new79(...);
void interrupt new80(...);
void interrupt new81(...);
void interrupt new82(...);
void interrupt new81(...);
void interrupt new84(...);
void interrupt new85(...);

void print(int offset, int val)
{
 VIDEO far* screen = (VIDEO far*) MK_FP(0xB800, 0);
 screen += offset;
 for (int i = 7; i >= 0; --i)
 {
 screen->symb = val % 2 + '0';
 screen->attr = col;
 screen++;
 val /= 2;
 }
}

void get_reg()
{
print(0, inp(0x21)); //вывод регистра масок ведущего

outp(0x20, 0x0A); // вывод регистра запросов 
print(32, inp(0x20));

outp(0x20, 0x0B);
print(16, inp(0x20));

print(48, inp(0xA1));

outp(0xA0, 0x0A);
print(80, inp(0xA0));

outp(0xA0, 0x0B);
print(64, inp(0xA0));
}

void interrupt new08(...)
{
 get_reg();
 old08();
}

void interrupt new09(...)
{
 get_reg();
 col += 0x06;
 get_reg();
 old09();
}

void interrupt new0A(...)
{
 get_reg();
 old0A();
}

void interrupt new0B(...)
{
 get_reg();
 old0B();
}

void interrupt new0C(...)
{
 get_reg();
 old0C();
}

void interrupt new0D(...)
{
 get_reg();
 old0D();
}

void interrupt new0E(...)
{
 get_reg();
 old0E();
}

void interrupt new0F(...)
{
 get_reg();
 old0F();
}


void interrupt new78(...)
{
 get_reg();
 old78();
}

void interrupt new79(...)
{
 get_reg();
 old79();
}

void interrupt new80(...)
{
 get_reg();
 old80();
}

void interrupt new81(...)
{
 get_reg();
 old81();
}

void interrupt new82(...)
{
 get_reg();
 col += 0x06;
 get_reg();
 old82();
}

void interrupt new83(...)
{
 get_reg();
 old83();
}

void interrupt new84(...)
{
 get_reg();
 old84();
}

void interrupt new85(...)
{
 get_reg();
 old85();
}

void init()
{
 old08 = getvect(0x08);
 old09 = getvect(0x09);
 old0A = getvect(0x0A);
 old0B = getvect(0x0B);
 old0C = getvect(0x0C);
 old0D = getvect(0x0D);
 old0E = getvect(0x0E);
 old0F = getvect(0x0F);

 setvect(0x08, new08);
 setvect(0x09, new09);
 setvect(0x0A, new0A);
 setvect(0x0B, new0B);
 setvect(0x0C, new0C);
 setvect(0x0D, new0D);
 setvect(0x0E, new0E);
 setvect(0x0F, new0F);

 old78 = getvect(0x78);
 old79 = getvect(0x79);
 old80 = getvect(0x80);
 old81 = getvect(0x81);
 old82 = getvect(0x82);
 old83 = getvect(0x83);
 old84 = getvect(0x84);
 old85 = getvect(0x85);

 setvect(0x78, new78);
 setvect(0x79, new79);
 setvect(0x80, new80);
 setvect(0x81, new81);
 setvect(0x82, new82);
 setvect(0x83, new83);
 setvect(0x84, new84);
 setvect(0x85, new85);

 _disable();

 outp(0x20, 0x11);
 outp(0x21, 0x08);
 outp(0x21, 0x04);
 outp(0x21, 0x01);

 outp(0xA0, 0x11);
 outp(0xA1, 0x78);
 outp(0xA1, 0x02);
 outp(0xA1, 0x01);

 _enable();
}

int main()
{

 unsigned far *fp;
 init();

 FP_SEG(fp) = _psp;
 FP_OFF(fp) = 0x2c;

 _dos_freemem(*fp);

 _dos_keep(0, (_DS - _CS) + (_SP / 16) + 1);

 return 0;
}
