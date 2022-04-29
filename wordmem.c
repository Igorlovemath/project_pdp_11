#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <malloc.h>
#define MEMSIZE 64*1024 // 64 Kb // 2^16 // 0000000000000000 -> 1111111111111111 // (2^4)^4 // 0000 -> FFFF

typedef unsigned char byte; // 8 bits
typedef unsigned short int word; //  16 bits
typedef word adr; // 16 bits
word mem [MEMSIZE] = {}; //32 Kb
typedef adr test_t; // 16 bits

void b_write (adr a, byte b)
{
    word w = (word) b;

    if (a % 2 == 0)
        mem [a] = (mem [a] & 0xFF00) | w;

    else
    {
        w = w << 8;
        mem [a - 1] = (mem [a - 1] & 0x00FF) | w;
    }
}

byte b_read (adr a)
{
    if (a % 2 == 0)
        return (byte) mem [a];

    word w = mem [a - 1] >> 8;

    return (byte) w;
}

void w_write (adr a, word w)
{
    assert (a % 2 == 0);
    mem [a] = w;
}

word w_read (adr a)
{
    assert (a % 2 == 0);

    return mem [a];
}

void mem_dump (adr begin, word n)
{
    assert (begin % 2 == 0);

    word w;

    for (adr i = 0; i < n / 2; i++)
    {
        w = w_read(begin + i * 2);
        printf ("%06ho : %06ho\n", begin + i * 2, w);
    }
}

void load_file ()
{
    byte b;
    int counter = 0;
    test_t adress, amount;

    while (scanf ("%hx%hx", &adress, &amount) != EOF)
    {
        for (int f = 0; f < amount; f++)
        {
            scanf ("%hhx", &b);
            b_write(adress + f, b);
        }
    }
}

int main()
{


    return 0;
}




/*void test ()
{
    byte a = 0x0a;
    byte b = 0x0b;
    word w = 0x0b0a;
    adr ad = 6;

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

}*/