#include <stdio.h>
#include <assert.h>
#define MEMSIZE 64*1024 // 64 Kb // 2^16 // 0000000000000000 -> 1111111111111111 // (2^4)^4 // 0000 -> FFFF

typedef unsigned char byte; // 8 bits
typedef unsigned short int word; //  16 bits
typedef word adress; // 16 bits
byte mem [MEMSIZE]; //64 Kb

void byte_write (adress adr, byte b)
{
    mem [adr] = b;
}

byte byte_read (adress adr)
{
    return mem [adr];
}

void word_write (adress adr, byte a, byte b)
{
    assert (adr % 2 == 0);
    mem [adr] = a;
    mem [adr + 1] = b;
}

word word_read (adress adr)
{
    assert (adr % 2 == 0);

    word w = (word) mem [adr + 1] << 8;
    w = w | (word) mem [adr];

    return w;
}

void test ()
{
    byte a = 0x0a;
    byte b = 0x0b;
    word w = 0x0b0a;
    adress ad = 6;

    word_write(6, a, b);

    word w_read = word_read (6);

    printf ("%0hx = %0hx", w_read, w);

}

int main() {

    test ();

    return 0;
}

