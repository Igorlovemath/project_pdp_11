#ifndef PROJECT_PDP_11_RUN_H
#define PROJECT_PDP_11_RUN_H

/*extern word mem [];
extern word reg [];*/

#ifndef pc
#define pc reg [7]
#endif

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
        {0170000, 0010000, "mov", do_mov, 0},
        {0170000, 0060000, "add", do_add, 0},
        {0000000, 0000000, "\0" , do_nothing, 100}
};

Arg get_mr (word w, int boolb)
{
    Arg res;

    int reg_num = w & 7;
    int reg_mode = (w >> 3) & 7;

    switch (reg_mode)
    {
        case 0: // R1
            res.adr = reg_num;
            res.val = reg [reg_num];
            trace ("R%o ", reg_num);
            break;

        case 1: // (R1)
            res.adr = reg [reg_num];

            if (boolb)
                res.val = b_read (res.adr);
            else
                res.val = w_read (res.adr);

            trace ("(R%o) ", reg_num);
            break;

        case 2: // (R3)+   #3
            res.adr = reg [reg_num];

            if (boolb)
            {
                res.val = b_read (res.adr);
                reg [reg_num] += 1;
            }

            else
            {
                res.val = w_read (res.adr);
                reg [reg_num] += 2;
            }

            if (reg_num == 7)
                trace ("#%o ", res.val);
            else
                trace ("(R%o)+ ", reg_num);
            break;

        default:
            fprintf (stderr, "Mode %o NOT IMPLEMENTED YET!\n", reg_mode);
            exit (1);
    }

    return res;
}

void run ()
{
    pc = 01000;
    int k;
    word w;

    while (pc != 32 * 1024)
    {
        w = w_read (pc);
        trace ("%06o %06o: ", pc, w);
        pc += 2;

        k = 0;

        for (int i = 0; cmd[i].boolb != 100; i++)
        {
            if ((w & cmd[i].mask) == cmd[i].opcode)
            {
                trace ("%s ", cmd[i].name);

                ss = get_mr(w >> 6, cmd[i].boolb);
                dd = get_mr(w, cmd[i].boolb);

                cmd[i].do_func ();
                k = 1;

                trace ("\n");
            }
        }

        if (!k)
            trace ("unknown\n");
    }
}







#endif //PROJECT_PDP_11_RUN_H