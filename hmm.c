

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


