#ifndef PROJECT_PDP_11_FUNCTIONS_H
#define PROJECT_PDP_11_FUNCTIONS_H

void b_write (adr a, byte b, int regs)
{
    word w = (word) b;

    if (regs)
    {
        if (a % 2 == 0)
            reg [a] = (reg [a] & 0xFF00) | w;

        else
        {
            w = w << 8;
            reg [a - 1] = (reg [a - 1] & 0x00FF) | w;
        }
    }

    else
    {
        if (a % 2 == 0)
            mem [a] = (mem [a] & 0xFF00) | w;

        else
        {
            w = w << 8;
            mem [a - 1] = (mem [a - 1] & 0x00FF) | w;
        }
    }
}

byte b_read (adr a, int regs)
{
    word w;

    if (regs)
    {
        if (a % 2 == 0)
            return (byte) reg [a];

        w = reg [a - 1] >> 8;
    }

    else
    {
        if (a % 2 == 0)
            return (byte) mem [a];

        w = mem [a - 1] >> 8;
    }

    return (byte) w;
}

void w_write (adr a, word w, int regs)
{
    if (regs)
    {
        assert (a >= 0 && a <= 7);
        reg [a] = w;
    }

    else
    {
        assert (a % 2 == 0);
        mem [a] = w;
    }
}

word w_read (adr a, int regs)
{
    if (regs)
    {
        assert (a >= 0 && a <= 7);
        return reg [a];
    }

    assert (a % 2 == 0);
    return mem [a];
}

void mem_dump (adr begin, word n)
{
    assert (begin % 2 == 0);

    word w;

    for (adr i = 0; i < n / 2; i++)
    {
        w = w_read(begin + i * 2, 0);
        trace ("%06ho : %06ho\n", begin + i * 2, w);
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
            b_write(adress + f, b, 0);
        }
    }
}

stricoun load_file_2 ()
{
    byte b;
    int counter = 0, mall = 1;
    adramo * array = malloc (10 * sizeof (adramo));

    while (1)
    {
        if (counter > 10*mall)
        {
            mall++;
            array = realloc (array, 10*mall * sizeof (adramo));
        }

        if (scanf ("%hx%hx", &array[counter].adress, &array[counter].amount) == EOF)
            break;

        for (int f = 0; f < array[counter].amount; f++)
        {
            scanf ("%hhx", &b);
            b_write(array[counter].adress + f, b, 0);
        }
        counter++;
    }

    stricoun a;

    a.str = array;
    a.count = counter;

    return a;
}

void trace (char * string, ...)
{
    int a = 1;

    if (a)
    {
        va_list p;
        va_start(p, string);
        int int_type;
        long int lint_type;
        long long int llint_type;
        double double_type;
        long double ldouble_type;
        char char_type;
        char *str_type;

        char * result;
        int resi;

        for (int i = 0; string[i] != '\0'; i++) {

            if (string[i] != '%' && string[i] != '\\')
                printf("%c", string[i]);

            else if (string[i] == '%')
            {
                result = calloc (100, sizeof (char));
                result [0] = '%';
                resi = 1;

                i++;

                while (isdigit (string [i]))
                {
                    result [resi] = string[i];
                    resi++;
                    i++;
                }

                switch (string[i]) {

                    case 'h':
                        if (string[i + 1] == 'd')
                        {
                            int_type = va_arg (p, int);
                            strcat (result, "hd");
                            printf(result, int_type);
                            free (result);
                            i += 1;
                        }

                        else if (string[i + 1] == 'o')
                        {
                            int_type = va_arg (p, int);
                            strcat (result, "ho");
                            printf(result, int_type);
                            free (result);
                            i += 1;
                        }

                        else if (string[i + 1] == 'x')
                        {
                            int_type = va_arg (p, int);
                            strcat (result, "hx");
                            printf(result, int_type);
                            free (result);
                            i += 1;
                        }

                        else if (string[i + 1] == 'h')
                        {

                            if (string[i + 2] == 'd')
                            {
                                int_type = va_arg (p, int);
                                strcat (result, "hhd");
                                printf(result, int_type);
                                free (result);
                                i += 2;
                            }

                            else if (string[i + 2] == 'o')
                            {
                                int_type = va_arg (p, int);
                                strcat (result, "hho");
                                printf(result, int_type);
                                free (result);
                                i += 2;
                            }

                            else if (string[i + 2] == 'x')
                            {
                                int_type = va_arg (p, int);
                                strcat (result, "hhx");
                                printf(result, int_type);
                                free (result);
                                i += 2;
                            }

                            else
                            {
                                printf ("unknown type of parameter in function: trace (char * string, ...)");
                                free (result);
                                exit(0);
                            }
                        }
                        break;

                    case 'd':
                        int_type = va_arg(p, int);
                        strcat (result, "d");
                        printf(result, int_type);
                        free (result);
                        break;

                    case 'o':
                        int_type = va_arg(p, int);
                        strcat (result, "o");
                        printf(result, int_type);
                        free (result);
                        break;

                    case 'x':
                        int_type = va_arg(p, int);
                        strcat (result, "x");
                        printf(result, int_type);
                        free (result);
                        break;

                    case 'l':
                        if (string[i + 1] == 'd')
                        {
                            lint_type = va_arg (p, long int);
                            strcat (result, "ld");
                            printf(result, lint_type);
                            free (result);
                            i += 1;
                        }

                        else if (string[i + 1] == 'o')
                        {
                            lint_type = va_arg (p, long int);
                            strcat (result, "lo");
                            printf(result, lint_type);
                            free (result);
                            i += 1;
                        }

                        else if (string[i + 1] == 'x')
                        {
                            lint_type = va_arg (p, long int);
                            strcat (result, "lx");
                            printf(result, lint_type);
                            free (result);
                            i += 1;
                        }

                        else if (string[i + 1] == 'l')
                        {

                            if (string[i + 2] == 'd')
                            {
                                llint_type = va_arg (p, long long int);
                                strcat (result, "lld");
                                printf(result, llint_type);
                                free (result);
                                i += 2;
                            }

                            else if (string[i + 2] == 'o')
                            {
                                llint_type = va_arg (p, long long int);
                                strcat (result, "llo");
                                printf(result, llint_type);
                                free (result);
                                i += 2;
                            }

                            else if (string[i + 2] == 'x')
                            {
                                llint_type = va_arg (p, long long int);
                                strcat (result, "llx");
                                printf(result, llint_type);
                                free (result);
                                i += 2;
                            }

                            else
                            {
                                printf ("unknown type of parameter in function: trace (char * string, ...)");
                                free (result);
                                exit(0);
                            }
                        }
                        break;

                    case 'L':
                        if (string[i + 1] != 'f') {
                            printf("unknown type of parameter in function: trace (char * string, ...)");
                            free (result);
                            exit(0);
                        }

                        ldouble_type = va_arg (p, long double);
                        strcat (result, "Lf");
                        printf(result, ldouble_type);
                        free (result);
                        i += 1;
                        break;

                    case 'f':
                        double_type = va_arg (p, double);
                        strcat (result, "f");
                        printf(result, double_type);
                        free (result);
                        break;

                    case 'c':
                        char_type = va_arg (p, int);
                        strcat (result, "c");
                        printf(result, char_type);
                        free (result);
                        break;

                    case 's':
                        str_type = va_arg (p, char *);
                        strcat (result, "s");
                        printf(result, str_type);
                        free (result);
                        break;

                    default:
                        printf("unknown type of parameter in function: trace (char * string, ...)");
                        free (result);
                }
            }

            else
                switch (string[++i]) {
                    case 'n':
                        printf("\n");
                        break;

                    case '0':
                        break;

                    case 'a':
                        printf("\a");

                    case 'b':
                        printf("\b");

                    case 't':
                        printf("\t");

                    case 'v':
                        printf("\v");

                    case 'f':
                        printf("\f");

                    case 'r':
                        printf("\r");

                    default:
                        printf("unknown type of parameter in function: trace (char * string, ...)");
                }
        }

        va_end(p);
    }
}

void reg_print ()
{
    for (int i = 0; i < 8; i++)
    {
        trace ("R%d: %06ho ", i, reg[i]);

        if (i == 3)
            trace ("\n");
    }
}



#endif //PROJECT_PDP_11_FUNCTIONS_H
