/*
#include <stdio.h>
#include <assert.h>
#define MEMSIZE 64*1024 // 64 Kb // 2^16 // 0000000000000000 -> 1111111111111111 // (2^4)^4 // 0000 -> FFFF

typedef unsigned char byte; // 8 bits
typedef unsigned short int word; //  16 bits
typedef word adress; // 16 bits
word mem [MEMSIZE/2]; //32 Kb

void byte_write (adress adr, byte b)
{
    if (adr % 2 == 0)
        mem [adr] = (mem [adr] & 0xFF00) | (word) b;

    else
        mem [adr] = (mem [adr] & 0x00FF) | ((word) b << 8);
}

byte byte_read (adress adr)
{
    if (adr % 2 == 0)
        return (byte) mem [adr];

    return (byte) (mem [adr] >> 8);
}

void word_write (adress adr, word w)
{
    assert (adr % 2 == 0);
    mem [adr] = w;
}

word word_read (adress adr)
{
    assert (adr % 2 == 0);

    return mem [adr];
}

void test ()
{
    byte a = 0x0a;
    byte b = 0x0b;
    word w = 0x0b0a;
    adress ad = 6;

    word_write(ad, w);

    word w_read = word_read (ad);

    printf ("1: %0hx = %0hx\n", w_read, w);

    byte_write(ad, a);
    byte a_read = byte_read (ad);

    printf ("2: %0hhx = %0hhx\n", a, a_read);

    byte_write(ad + 1, b);
    byte b_read = byte_read (ad + 1);

    printf ("3: %0hhx = %0hhx\n", b, b_read);

    w_read = word_read (ad);
    printf ("4: %0hx = %0hx\n", w_read, w);

}

int main() {

    test ();

    return 0;
}
*/