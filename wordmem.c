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

#include "interface.h"
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

    return 0;
}