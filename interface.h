#ifndef PROJECT_PDP_11_INTERFACE_H
#define PROJECT_PDP_11_INTERFACE_H


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

void trace (char * string, ...)
{
    va_list p;
    va_start(p, string);
    int int_type;
    long int lint_type;
    long long int llint_type;
    double double_type;
    long double ldouble_type;
    char char_type;
    char * str_type;

    for (int i = 0; string [i] != '\0'; i++)
    {
        if (string [i] != '%' && string [i] != '\\')
            printf ("%c", string [i]);

        else if (string [i] == '%')
        {
            switch (string [++i])
            {
                case 'd':
                    int_type = va_arg(p, int);
                    printf ("%d", int_type);
                    break;

                case 'l':
                    if (string [i+1] == 'd')
                    {
                        lint_type = va_arg (p, long int);
                        printf ("%ld", lint_type);
                        i += 1;
                    }

                    else if (string [i+1] == 'l')
                    {
                        if (string [i+2] != 'd')
                        {
                            printf ("unknown type of parameter in function: trace (char * string, ...):  %%ll%c", string [i+2]);
                            exit (0);
                        }

                        llint_type = va_arg (p, long long int);
                        printf ("%lld", llint_type);
                        i += 2;
                    }

                    else
                        printf ("unknown type of parameter in function: trace (char * string, ...):  %%l%c", string [i+2]);
                        exit (0);
                    break;

                case 'L':
                    if (string [i+1] != 'f')
                    {
                        printf ("unknown type of parameter in function: trace (char * string, ...):  %%L%c", string [i+1]);
                        exit (0);
                    }

                    ldouble_type = va_arg (p, long double);
                    printf ("%Lf", ldouble_type);
                    i += 1;
                    break;

                case 'f':
                    double_type = va_arg (p, double);
                    printf ("%f", double_type);
                    break;

                case 'c':
                    char_type = va_arg (p, int);
                    printf ("%c", char_type);
                    break;

                case 's':
                    str_type = va_arg (p, char *);
                    printf ("%s", str_type);
                    break;

                default:
                    printf ("unknown type of parameter in function: trace (char * string, ...):  %%%c", string [i]);
            }
        }

        else
            switch (string [++i])
            {
                case 'n':
                    printf ("\n");
                    break;

                case '0':
                    break;

                case 'a':
                    printf ("\a");

                case 'b':
                    printf ("\b");

                case 't':
                    printf ("\t");

                case 'v':
                    printf ("\v");

                case 'f':
                    printf ("\f");

                case 'r':
                    printf ("\r");

                default:
                    printf ("unknown type of parameter in function: trace (char * string, ...):  \\%c", string [i]);
            }
    }

    va_end(p);
}



#endif //PROJECT_PDP_11_INTERFACE_H
