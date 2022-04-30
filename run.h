#ifndef PROJECT_PDP_11_RUN_H
#define PROJECT_PDP_11_RUN_H

extern word mem [];
extern word reg [];

#ifndef pc
#define pc reg [7]
#endif

typedef struct
{
    word mask;
    word opcode;
    char * name;
    void (*do_func)(void);

} Command;

//       code   SS     DD
//mask : 0000 xxxxxx xxxxxx
//       0001 xxxxxx xxxxxx
//      0 001  0  0   0  0
//      0  1   0  0   0  0
//      0 010000
//       1111 000000 000000
//      1 111 000 000 000 000
//      1  7   0   0   0   0
//      0 170000


Command cmd [] = {
        {0170000, 0010000, "mov", do_mov},
        {0170000, 0060000, "add", do_add},
        {0000000, 0000000, "\0" , do_nothing}
};

void run ()
{
    pc = 01000;
    int k;
    word w;

    while (pc != 32 * 1024)
    {
        w = w_read (pc);
        pc += 2;

        printf ("%06o %06o: ", pc, w);

        k = 0;

        for (int i = 0; strcmp (cmd[i].name, "\0") != 0; i++)
        {
            if ((w & cmd[i].mask) == cmd[i].opcode)
            {
                printf ("%s", cmd[i].name);
                cmd[i].do_func ();
                k = 1;
            }
        }

        if (!k)
            printf ("unknown");
    }
}







#endif //PROJECT_PDP_11_RUN_H