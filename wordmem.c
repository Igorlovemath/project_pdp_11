#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <malloc.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

#define MEMSIZE 64*1024 // 64 Kb // 2^16 // 0000000000000000 -> 1111111111111111 // (2^4)^4 // 0000 -> FFFF
typedef unsigned char byte; // 8 bits
typedef unsigned short int word; //  16 bits
typedef word adr; // 16 bits
typedef adr test_t; // 16 bits

word mem [2 * MEMSIZE] = {}; //64 Kb
word reg [8];

typedef struct
{
    word mask;
    word opcode;
    char * name;
    void (*do_func)(void);
    int boolb;

} Command;

typedef struct
{
    word val;
    word adr;
}Arg;
Arg ss, dd;

typedef struct
{
    test_t adress;
    test_t amount;
} adramo;

typedef struct
{
    adramo * str;
    int count;

} stricoun;

Arg get_mr (word w, int boolb);
void run ();
void b_write (adr a, byte b, int regs);
byte b_read (adr a, int regs);
void w_write (adr a, word w, int regs);
word w_read (adr a, int regs);
void mem_dump (adr begin, word n);
void load_file ();
stricoun load_file_2 ();
void trace (char * string, ...);

void do_halt (); // stop
void do_mov ();  // d=s
void do_movb (); // d=s
void do_add ();  // d=s+d
void do_adcb (); // d=d+C
void do_aslb (); // d=d*2
void do_asrb (); // d=d/2
void do_cmpb (); // s-d
void do_comb (); // d=~d;
void do_decb (); // d=d-1
void do_incb (); // d=d+1
void do_jmp ();  // PC=d
void do_jsr ();  // r=PC, PC=d
void do_negb (); // d=-d
void do_sbc ();  // d=d-C
void do_sub ();  // d=d-s
void do_nothing ();

#include "functions.h"
#include "commands.h"
#include "run.h"

int main()
{
    stricoun a = load_file_2();

    for (int i = 0; i < a.count; i++)
    {
        trace ("Block %d:\n", i);
        mem_dump(a.str[i].adress, a.str[i].amount);
    }

    free (a.str);

    trace ("\n");

    run ();

    trace ("\n");

    return 0;
}