#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define INPUT_MAX_SIZE 500

int my_cmp(const char *str1, const char *str2)
{
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    if(len1 > len2)
        return 1;
    if(len1 < len2)
        return -1;
    int i = 0;
    while(i < len1 && i < len2)
    {
        if(*(str1 + i) > *(str2 + i))
            return 1;
        if(*(str1 + i) < *(str2 + i))
            return -1;
        i++;
    }
    return 0;
}

int validate(const char *number)
{
    if(number == NULL)
        return -1;
    int i = 0;
    if(*number == '-')
        i++;
    if((*(number + i) == '0' && strlen(number) > 1) || *(number + i) == '\0')
        return 2;
    int len = strlen(number + i);
    for(; i < len; i++)
        if(!isdigit(*(number + i)))
            return 2;
    if(i == 0)
        return 2;
    return 0;
}

int validate_expression(const char *expr)
{
    if(expr == NULL)
        return 2;
    int i = 0;
    if(*expr == '-')
        i++;
    if(*expr == '\0')
        return 1;
    while(*(expr + i) != '\0')
    {
        int j = 0;
        while(isdigit(*(expr + i + j)))
            j++;
        if(j == 0)
            return 1;
        if(*(expr + i + j) == '-')
        {
            j++;
            if(isdigit(*(expr + i + j)))
            {
                i += j;
                continue;
            }
            if(*(expr + i + j) == '-')
            {
                i += j + 1;
                continue;
            }
            return 1;
        }
        if(*(expr + i + j) == '+')
        {
            j++;
            if(isdigit(*(expr + i + j)))
            {
                i += j;
                continue;
            }
            if(*(expr + i + j) == '-')
            {
                i += j + 1;
                continue;
            }
            return 1;
        }
        if(*(expr + i + j) == '*')
        {
            j++;
            if(isdigit(*(expr + i + j)))
            {
                i += j;
                continue;
            }
            if(*(expr + i + j) == '-')
            {
                i += j + 1;
                continue;
            }
            return 1;
        }
        i += j;
    }
    return 0;
}

char digit_to_val(char c)
{
    return -('0' - c);
}

char val_to_digit(char val)
{
    return '0' + val;
}

int add_minus(char **number)
{
    int len = strlen(*number);
    char *new = realloc(*number, sizeof(char) * (len + 2));
    if(new == NULL)
    {
        free(*number);
        return 1;
    }
    *number = new;
    for(int i = len + 1; i > 0; i--)
        *((*number) + i) = *((*number) + i - 1);
    **number = '-';
    return 0;
}

int add(const char* number1, const char* number2, char** result);

int subtract(const char* number1, const char* number2, char** result)
{
    if(number1 == NULL || number2 == NULL || result == NULL)
        return 1;
    if(validate(number1) != 0 || validate(number2) != 0)
        return 2;
    if(*number1 == '-' && *number2 == '-')
    {
        (char*)number1++;
        (char*)number2++;
        return subtract(number2, number1, result);
    }
    if(*number1 == '-' && *number2 != '-')
    {
        (char*)number1++;
        int ret_val = add(number1, number2, result);
        if(ret_val != 0)
            return ret_val;
        if(add_minus(result))
            return 3;
        return 0;
    }
    if(*number1 != '-' && *number2 == '-')
    {
        (char*)number2++;
        return add(number1, number2, result);
    }
    if(my_cmp((char*)number1, (char*)number2) == -1)
    {
        int ret_val = subtract(number2, number1, result);
        if(ret_val != 0)
            return ret_val;
        if(add_minus(result))
            return 3;
        return 0;
    }
    int len1 = strlen(number1);
    int len2 = strlen(number2);
    *result = calloc(len1 + 1, sizeof(char));
    if(*result == NULL)
        return 3;
    int next = 0;
    for(int i = len1 - 1, j = len2 - 1; i >= 0; i--, j--)
    {
        int val1 = digit_to_val(*(number1 + i));
        int val2 = 0;
        if(j >= 0)
            val2 = digit_to_val(*(number2 + j));
        if(val1 - val2 - next < 0)
        {
            *((*result) + i) = val_to_digit((val1 + 10 - next) - val2);
            next = 1;
        } else
        {
            *((*result) + i) = val_to_digit(val1 - next - val2);
            next = 0;
        }
    }
    int i = 0;
    while(*((*result) + i) == '0')
        i++;
    for(int  j = 0; j + i < len1 + 1; j++)
        *((*result) + j) = *((*result) + j + i);
    if(**result == '\0')
    {
        **result = '0';
        *((*result) + 1) = '\0';
    }
    return 0;
}

int add(const char* number1, const char* number2, char** result)
{
    if(number1 == NULL || number2 == NULL || result == NULL)
        return 1;
    if(validate(number1) != 0 || validate(number2) != 0)
        return 2;
    if(*number1 == '-' && *number2 == '-')
    {
        (char*)number1++;
        (char*)number2++;
        int ret_val = add(number1, number2, result);
        if(ret_val != 0)
            return ret_val;
        if(add_minus(result))
            return 3;
        return 0;
    }
    if(*number1 == '-' && *number2 != '-')
    {
        (char*)number1++;
        return subtract(number2, number1, result);
    }
    if(*number1 != '-' && *number2 == '-')
    {
        (char*)number2++;
        return subtract(number1, number2, result);
    }
    if(my_cmp(number1, number2) == -1)
        return add(number2, number1, result);
    int len1 = strlen(number1);
    int len2 = strlen(number2);
    *result = calloc(len1 + 2, sizeof(char));
    if(*result == NULL)
        return 3;
    for(int i = 0; i < len1 + 1; i++)
        *((*result) + i) = '0';
    for(int i = len1 - 1, j = len2 - 1; i >= 0; i--, j--)
    {
        int val1 = digit_to_val(*(number1 + i));
        int val2 = 0;
        if(j >= 0)
            val2 = digit_to_val(*(number2 + j));
        if(val1 + val2 + digit_to_val(*((*result) + i + 1)) >= 10)
        {
            *((*result) + i) = '1';
            *((*result) + i + 1) = val_to_digit(val1 + val2 + digit_to_val(*((*result) + i + 1)) - 10);
        } else
            *((*result) + i + 1) = val_to_digit(val1 + val2 + digit_to_val(*((*result) + i + 1)));
    }
    if(**result == '0')
        for(int i = 1; i < len1 + 2; i++)
            *((*result) + i - 1) = *((*result) + i);
    return 0;
}

int multiply(const char* number1, const char* number2, char** result)
{
    if(number1 == NULL || number2 == NULL || result == NULL)
        return 1;
    if(validate(number1) != 0 || validate(number2) != 0)
        return 2;
    if(*number1 == '-' && *number2 == '-')
    {
        (char*)number1++;
        (char*)number2++;
    }
    int sign_flag = 0;
    if(*number1 != '-' && *number2 == '-')
    {
        sign_flag = 1;
        (char*)number2++;
    }
    if(*number1 == '-' && *number2 != '-')
    {
        sign_flag = 1;
        (char*)number1++;
    }
    if(*number1 == '0' || *number2 == '0')
        sign_flag = 0;
    int len1 = strlen(number1);
    int len2 = strlen(number2);
    *result = calloc((len1 + len2 + 1), sizeof(char));
    if(*result == NULL)
        return 3;
    for(int i = len1 - 1; i >= 0; i--)
        for(int j = len2 - 1; j >= 0; j--)
        {
            int val1 = digit_to_val(*(number1 + i));
            int val2 = digit_to_val(*(number2 + j));
            int cur_multi = (val1 * val2) + *((*result) + i + j + 1);
            *((*result) + i + j + 1) = cur_multi % 10;
            *((*result) + i + j) += cur_multi / 10;
        }
    for(int i = 0; i < len1 + len2; i++)
        *((*result) + i) = val_to_digit(*((*result) + i));
    int i = 0;
    while(*((*result) + i) == '0')
        i++;
    for(int  j = 0; j + i < len1 + len2 + 1; j++)
        *((*result) + j) = *((*result) + j + i);
    if(sign_flag)
        if(add_minus(result))
            return 3;
    if(**result == '\0')
    {
        **result = '0';
        *((*result) + 1) = '\0';
    }
    return 0;
}

int calculate(const char* expr, char **result)
{
    if(expr == NULL || result == NULL)
        return 1;
    if(validate_expression(expr) != 0)
        return 2;
    *result = malloc(sizeof(char) * 2);
    if(*result == NULL)
        return 3;
    **result = '0';
    *((*result) + 1) = '\0';
    char operator = '+';
    int i = 0;
    char *not_const_expr = malloc(sizeof(char) * (strlen(expr) + 1));
    if(not_const_expr == NULL)
    {
        free(*result);
        return 3;
    }
    not_const_expr = memcpy(not_const_expr, expr, sizeof(char) * (strlen(expr) + 1));
    while(*(not_const_expr + i) != '\0')
    {
        int j = 0;
        if(*(not_const_expr + i) == '-')
            j++;
        while(*(not_const_expr + i + j) != '\0' && isdigit(*(not_const_expr + i + j)))
            j++;
        char tmp_operator = *(not_const_expr + i + j);
        int flag = 1;
        if(*(not_const_expr + i + j) == '\0')
            flag = 0;
        *(not_const_expr + i + j) = '\0';
        char *tmp_result;
        char *ptr_to_free = *result;
        int ret = 0;
        if(operator == '+')
            ret = add(*result, not_const_expr + i, &tmp_result);
        if(operator == '-')
            ret = subtract(*result, not_const_expr + i, &tmp_result);
        if(operator == '*')
            ret = multiply(*result, not_const_expr + i, &tmp_result);
        free(ptr_to_free);
        if(ret != 0)
            return ret;
        *result = tmp_result;
        operator = tmp_operator;
        i += j;
        if(flag)
            i++;
    }
    free(not_const_expr);
    return 0;
}

int main(void)
{
    char *expr = malloc(sizeof(char) * (INPUT_MAX_SIZE + 1));
    if(expr == NULL)
    {
        printf("Failed to allocate memory");
        return 8;
    }
    printf("Podaj wyrazenie: ");
    char *result;
    scanf("%500s", expr);
    int ret = calculate(expr, &result);
    if(ret == 2)
    {
        printf("Incorrect input");
        free(expr);
        return 1;
    }
    if(ret == 3)
    {
        printf("Failed to allocate memory");
        free(expr);
        return 8;
    }
    printf("%s", result);
    free(expr);
    free(result);
    return 0;
}