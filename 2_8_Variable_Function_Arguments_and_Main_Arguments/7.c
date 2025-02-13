#include <stdio.h>
#include <ctype.h>
#include <stdarg.h>
#define PREC 5

struct point_t
{
    int x;
    int y;
};

int int_len(int n)
{
    if(n == 0)
        return 1;
    int len = 0;
    if(n < 0)
        n = -n;
    while(n != 0)
    {
        n /= 10;
        len++;
    }
    return len;
}

int print_s(char *str)
{
    int res = 0;
    while(*str != '\0')
    {
        putchar(*str++);
        res++;
    }
    return res;
}

int print_d(int n)
{
    int res = 0;
    if(n < 0)
    {
        putchar('-');
        res++;
        n = -n;
    }
    if(n == 0)
    {
        putchar('0');
        res++;
        return res;
    }
    while(n != 0)
    {
        int tmp = n;
        int count = 0;
        while(tmp > 9)
        {
            tmp /= 10;
            count++;
        }
        putchar((char)('0' + tmp));
        res++;
        while(count--)
            tmp *= 10;
        int len1 = int_len(n);
        n -= tmp;
        int len2 = int_len(n);
        if(n == 0 && tmp > 9)
        {
            putchar('0');
            res++;
        }
        if(len1 - len2 > 1)
            for(int i = 0; i < len1 - len2 - 1; i++)
            {
                putchar('0');
                res++;
                tmp /= 10;
            }
    }
    return res;
}

int print_f(double n)
{
    int res = 0;
    if(n < 0)
    {
        putchar('-');
        res++;
        n = -n;
    }
    if(n == 0)
    {
        putchar('0');
        res++;
        putchar('.');
        res++;
        for(int i = 0; i < PREC; i++)
        {
            putchar('0');
            res++;
        }
        return res;
    }
    res += print_d((int)n);
    putchar('.');
    res++;
    n -= (int)n;
    for(int i = 0; i < PREC; i++)
    {
        n *= 10;
        res += print_d((int)n);
        n -= (int)n;
    }
    return res;
}

int print_p(struct point_t p)
{
    int res = 0;
    putchar('(');
    res++;
    res += print_d(p.x);
    putchar(' ');
    res++;
    res += print_d(p.y);
    putchar(')');
    res++;
    return res;
}

int my_printf(char *format, ...)
{
    if(format == NULL)
        return 0;
    int i = 0;
    va_list args;
    va_start(args, format);
    i = 0;
    int res = 0;
    while(*(format + i) != '\0')
    {
        if(*(format + i) == '%')
        {
            i++;
            if(*(format + i) == 's')
                res += print_s(va_arg(args, char*));
            else if(*(format + i) == 'd')
                res += print_d(va_arg(args, int));
            else if(*(format + i) == 'f')
                res += print_f(va_arg(args, double));
            else if(*(format + i) == 'p')
                res += print_p(va_arg(args, struct point_t));
            i++;
        } else
        {
            putchar((int)*(format + i));
            res++;
            i++;
        }
    }
    va_end(args);
    return res;
}

int scan_d(int *n)
{
    if(n == NULL)
        return 1;
    char c = (char)getchar();
    int sign = 0;
    if(c == '-')
    {
        sign = 1;
        c = (char)getchar();
    }
    if(!isdigit(c))
        return 1;
    *n = (int)(c - '0');
    while(isdigit(c = (char)getchar()))
    {
        (*n) *= 10;
        (*n) += (int)(c - '0');
    }
    if(sign)
        (*n) *= -1;
    ungetc((int)c, stdin);
    return 0;
}

int scan_f(double *n)
{
    if(n == NULL)
        return 1;
    char c = (char)getchar();
    int sign = 0;
    if(c == '-')
    {
        sign = 1;
        c = (char)getchar();
    }
    if(!isdigit(c))
        return 1;
    *n = (int)(c - '0');
    int flag = 0;
    int place = 1;
    while(isdigit(c = (char)getchar()) || c == '.')
    {
        if(c == '.')
        {
            flag = 1;
            continue;
        }
        if(!flag)
        {
            (*n) *= 10;
            (*n) += (double)(c - '0');
        } else
        {
            double tmp = (double)(c - '0');
            for(int i = 0; i < place; i++)
                tmp /= 10;
            (*n) += tmp;
            place++;
        }
    }
    if(sign)
        (*n) *= -1;
    ungetc((int)c, stdin);
    return 0;
}

int scan_p(struct point_t *p)
{
    if(p == NULL)
        return 1;
    char c = getchar();
    if(c != '(')
        return 1;
    if(scan_d(&p->x))
        return 1;
    c = getchar();
    if(c != ' ')
        return 1;
    if(scan_d(&p->y))
        return 1;
    c = getchar();
    if(c != ')')
        return 1;
    return 0;
}

int my_scanf(char *format, ...)
{
    if(format == NULL)
        return 0;
    int i = 0;
    va_list args;
    va_start(args, format);
    i = 0;
    int res = 0;
    while(*(format + i) != '\0')
    {
        if(*(format + i) == '%')
        {
            i++;
            if(*(format + i) == 'd')
            {
                if(scan_d(va_arg(args, int*)))
                {
                    va_end(args);
                    return res;
                }
            }
            else if(*(format + i) == 'f')
            {
                if(scan_f(va_arg(args, double*)))
                {
                    va_end(args);
                    return res;
                }
            }
            else if(*(format + i) == 'p')
            {
                if(scan_p(va_arg(args, struct point_t*)))
                {
                    va_end(args);
                    return res;
                }
                res++;
            }
            res++;
        } else if(*(format + i) != getchar())
        {
            va_end(args);
            return res;
        }
        i++;
    }
    va_end(args);
    return res;
}

int main(void)
{
    int n = 0;
    my_scanf("%d", &n);
    my_printf("%d", n);
    return 0;
}