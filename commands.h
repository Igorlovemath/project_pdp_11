#ifndef PROJECT_PDP_11_COMMANDS_H
#define PROJECT_PDP_11_COMMANDS_H

void do_halt ()  // stop
{
    printf ("THE END");
    exit (0);
}

void do_mov ()   // d=s
{
    trace ("> %06o <", dd.adr);
    w_write (dd.adr, ss.val);

}

void do_movb (); // d=s
void do_add ()  // d=s+d
{

}
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
void do_nothing () {}




#endif //PROJECT_PDP_11_COMMANDS_H
