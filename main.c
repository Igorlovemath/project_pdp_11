#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#define MEMSIZE 64*1024 // 64 Kb // 2^16 // 0000000000000000 -> 1111111111111111 // (2^4)^4 // 0000 -> FFFF

typedef unsigned char byte; // 8 bits
typedef unsigned short int word; //  16 bits
typedef word adress; // 16 bits
typedef adress test_t; // 16 bits

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

void mem_dump (adress begin, adress end)
{
    byte b;

    for (int i = 0; i < end - begin + 1; i++)
    {
        b = byte_read(begin + i);
        printf ("%hhx\n", b);
    }
}

void test ()
{
    byte b;
    int counter = 0, mall = 1;
    test_t * adresses = malloc (10 * sizeof (test_t));
    test_t * amount = malloc (10 * sizeof (test_t));

    while (1)
    {
        if (counter > 10*mall)
        {
            mall++;
            adresses = realloc (adresses, 10*mall * sizeof (test_t));
            amount = realloc (amount, 10*mall * sizeof (test_t));
        }

        if (scanf ("%hx%hx", &adresses[counter], &amount[counter]) == EOF)
            break;

        for (int f = 0; f < amount[counter]; f++)
        {
            scanf ("%hhx", &b);
            byte_write(adresses[counter] + f, b);
        }
        counter++;
    }

    for (int i = 0; i < counter; i++)
    {
        printf ("Block %d:\n", i);
        mem_dump(adresses[i], adresses[i] + amount[i] - 1);
    }

    free (adresses);
    free (amount);
}

int main() {

    test ();

    return 0;
}

