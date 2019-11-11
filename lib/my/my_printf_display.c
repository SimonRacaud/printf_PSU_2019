/*
** EPITECH PROJECT, 2019
** PSU_my_printf_2019
** File description:
** my_printf display
*/

#include "my.h"
#include "my_printf.h"
#include <stdarg.h>

const int (*TYPES[10])(arg_t *arg, va_list *ap) = {&disp_int, &disp_uint_xX,
&disp_uint_o, &disp_uint_b, &disp_uint_u, &disp_char, &disp_str, &disp_uint_p,
&disp_l_llq, &disp_ul_ullq};

static int display_if_invalid_arg(arg_t *arg, char *ptrformat)
{
    int i = 0;

    if (arg->spec[0] == '.') {
        while (*(ptrformat - i) != '%')
            i++;
        for (int j = 0; j <= i; j++)
            my_putchar(*(ptrformat - (i - j)));
        return i;
    }
    return 0;
}

static void display_arg_ext2(arg_t *arg, va_list *ap, int *len)
{
    if (arg->spec[0] == 'c' || arg->length[1] == 'h')
        *len = TYPES[5](arg, ap);
    if (what_type(arg->spec[0]) == 1)
        *len = TYPES[0](arg, ap);
    if (arg->spec[0] == 'x' || arg->spec[0] == 'X')
        *len = TYPES[1](arg, ap);
    if (arg->spec[0] == 'o')
        *len = TYPES[2](arg, ap);
    if (arg->spec[0] == 'b')
        *len = TYPES[3](arg, ap);
    if (arg->spec[0] == 'u')
        *len = TYPES[4](arg, ap);
    if (arg->spec[0] == 's' || arg->spec[0] == 'S')
        *len = TYPES[6](arg, ap);
    if (arg->spec[0] == 'p')
        *len = TYPES[7](arg, ap);
}

static void display_arg_ext1(arg_t *arg, va_list *ap, int *len)
{
    if (what_type(arg->spec[0]) == 1) {
        if (arg->length[0] == 'l' || arg->length[0] == 'q') {
            *len = TYPES[8](arg, ap);
        }
    }
    if (what_type(arg->spec[0]) == 2) {
        if (arg->length[0] == 'l' || arg->length[0] == 'q') {
            *len = TYPES[9](arg, ap);
        }
    }
}

int display_arg(arg_t *arg, va_list *ap, char *ptrformat)
{
    int len = 0;

    len = display_if_invalid_arg(arg, ptrformat);
    clean_flags(arg);
    if (arg->spec[0] == '%') {
        my_putchar('%');
        len = 1;
    } else if (arg->spec[0] != '.') {
        display_arg_ext1(arg, ap, &len);
        if (len == 0)
            display_arg_ext2(arg, ap, &len);
    }
    return len;
}