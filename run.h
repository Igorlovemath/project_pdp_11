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

Command cmd [] = {
        {0170000, 0010000, "mov", }
};

void run ()
{
    pc = 01000;

    while (1)
    {
        word w = w_read (pc);
        pc += 2;




    }


}







#endif //PROJECT_PDP_11_RUN_H