#include <stdio.h>
#include <string.h>
#define MAX_NUM_STR_LEN 5

char numbers[10][3][4] = {{{' ', '_', ' ', '\0'}, {'|', ' ', '|', '\0'}, {'|', '_', '|', '\0'}},  //0
                          {{' ', ' ', ' ', '\0'}, {' ', ' ', '|', '\0'}, {' ', ' ', '|', '\0'}},  //1
                          {{' ', '_', ' ', '\0'}, {' ', '_', '|', '\0'}, {'|', '_', ' ', '\0'}},  //2
                          {{' ', '_', ' ', '\0'}, {' ', '_', '|', '\0'}, {' ', '_', '|', '\0'}},  //3
                          {{' ', ' ', ' ', '\0'}, {'|', '_', '|', '\0'}, {' ', ' ', '|', '\0'}},  //4
                          {{' ', '_', ' ', '\0'}, {'|', '_', ' ', '\0'}, {' ', '_', '|', '\0'}},  //5
                          {{' ', '_', ' ', '\0'}, {'|', '_', ' ', '\0'}, {'|', '_', '|', '\0'}},  //6
                          {{' ', '_', ' ', '\0'}, {' ', ' ', '|', '\0'}, {' ', ' ', '|', '\0'}},  //7
                          {{' ', '_', ' ', '\0'}, {'|', '_', '|', '\0'}, {'|', '_', '|', '\0'}},  //8
                          {{' ', '_', ' ', '\0'}, {'|', '_', '|', '\0'}, {' ', '_', '|', '\0'}}}; //9

char signs[4][3][4] = {{{' ', ' ', ' ', '\0'}, {' ', '+', ' ', '\0'}, {' ', ' ', ' ', '\0'}},  //+
                       {{' ', ' ', ' ', '\0'}, {' ', '-', ' ', '\0'}, {' ', ' ', ' ', '\0'}},  //-
                       {{' ', ' ', ' ', '\0'}, {' ', '*', ' ', '\0'}, {' ', ' ', ' ', '\0'}},  //*
                       {{' ', ' ', ' ', '\0'}, {' ', '/', ' ', '\0'}, {' ', ' ', ' ', '\0'}}}; ///

int decode(char input[3][(MAX_NUM_STR_LEN * 4) * 2 + MAX_NUM_STR_LEN + 1])
{
    int results[100];
    char operators[100];
    for(int i = 0; i < 100; i++)
    {
        *(results + i) = -1;
        *(operators + i) = '\0';
    }
    int i = 0;
    int idx_r = 0;
    int idx_s = 0;

    char tmp_sign = '\0';
    int result = 0;

    do
    {
        i += 4;
        int flag;
        for(int k = 0; k < 10; k++)
        {
            flag = 0;
            for(int j = 0; j < 3; j++)
            {
                for(int ii = 0; ii < 3; ii++)
                {
                    if(*((*((*(numbers + k)) + j)) + ii) != *((*(input + j)) + ii + i - 4))
                    {
                        flag = 1;
                        break;
                    }
                }
                if(flag)
                    break;
            }
            if(!flag)
            {
                *(results + idx_r++) = k;
                flag = 2;
                break;
            }
        }
        if(flag != 2)
        {
            for(int k = 0; k < 4; k++)
            {
                flag = 0;
                int j = 1;
                for(int ii = 0; ii < 3; ii++)
                {
                    if(*((*((*(signs + k)) + j)) + ii) != *((*(input + j)) + ii + i - 4))
                    {
                        flag = 1;
                        break;
                    }
                }
                if(!flag)
                {
                    if(k == 0)
                        tmp_sign = '+';
                    if(k == 1)
                        tmp_sign = '-';
                    if(k == 2)
                        tmp_sign = '*';
                    if(k == 3)
                        tmp_sign = '/';
                    *(operators + idx_s++) = tmp_sign;
                    *(results + idx_r++) = -2;
                    break;
                }
            }
        }
    } while(input[0][i] != '\0');
    int num1 = 0;
    int num2 = 0;
    i = 0;
    while(*(results + i) != -2)
        i++;
    for(int j = i, k = 1; j > 0; j--, k *= 10)
        num1 += *(results + j - 1) * k;
    i++;
    while(*(results + i) != -1)
        i++;
    for(int j = i, k = 1; *(results + j - 1) != -2; j--, k *= 10)
        num2 += *(results + j - 1) * k;
    if(tmp_sign == '+')
        result = num1 + num2;
    if(tmp_sign == '-')
        result = num1 - num2;
    if(tmp_sign == '*')
        result = num1 * num2;
    if(tmp_sign == '/')
    {
        if(num2 != 0)
            result = num1 / num2;
        else
            return -1;
    }
    return result;
}

int num_len(int number)
{
    if(number == 0)
        return 1;
    int i = 0;
    while(number > 0)
    {
        i++;
        number /= 10;
    }
    return i;
}

int get_digit(int num, int n)
{
    if(n + 1 == num_len(num))
        return num % 10;
    else
        return get_digit(num / 10, n);
}

void code(int number)
{
    char output[3][(MAX_NUM_STR_LEN * 2 * 4) + 1];
    int idx = 0;
    if(number < 0)
    {
        for(int i = 0; i < 3; i++)
            for(int j = 0; j < 3; j++)
                *((*(output + i)) + j + idx) = *((*((*(signs + 1)) + i)) + j);
        idx += 3;
        number = -number;
        for(int i = 0; i < 3; i++)
            *((*(output + i)) + idx) = ' ';
        idx++;
    }
    int len = num_len(number);
    for(int k = 0; k < len; k++)
    {
        int digit = get_digit(number, k);
        for(int i = 0; i < 3; i++)
            for(int j = 0; j < 3; j++)
                *((*(output + i)) + j + idx) = *((*((*(numbers + digit)) + i)) + j);
        idx += 3;
        for(int i = 0; i < 3; i++)
            *((*(output + i)) + idx) = ' ';
        idx++;
    }
    for(int i = 0; i < 3; i++)
        *((*(output + i)) + idx) = '\0';
    for(int i = 0; i < 3; i++)
        printf("%s\n", *(output + i));
}

int main(void)
{
    printf("Podaj dzialanie:\n");
    char input[3][(MAX_NUM_STR_LEN * 4) * 2 + MAX_NUM_STR_LEN + 1];
    for(int i = 0; i < 3; i++)
    {
        char c;
        int j = 0;
        while((c = getchar()) != '\0' && c != '\n')
            input[i][j++] = c;
        input[i][j] = '\0';
    }
    int res = decode(input);
    if(res != -1)
        code(res);
    else
    {
        printf("Operation not permitted");
        return 4;
    }
    return 0;
}