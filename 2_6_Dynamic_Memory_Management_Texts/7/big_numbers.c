#include "big_numbers.h"

int validate(const char *number)
{
    if(number == NULL)
        return -1;
    int i = 0;
    if(*number == '-')
        i++;
    if((*(number + i) == '0' && strlen(number) > 1) || *(number + i) == '\0')
        return 2;
    int len = strlen(number);
    for(; i < len; i++)
        if(!isdigit(*(number + i)))
            return 2;
    if(i == 0)
        return 2;
    return 0;
}

int create(struct big_numbers_t *bn, int capacity)
{
    if(bn == NULL || capacity <= 0)
        return 1;
    bn->big_number = malloc(sizeof(char*) * capacity);
    if(bn->big_number == NULL)
        return 2;
    bn->size = 0;
    bn->capacity = capacity;
    return 0;
}

int create_big_numbers(struct big_numbers_t **bn, int capacity)
{
    if(bn == NULL || capacity <= 0)
        return 1;
    *bn = malloc(sizeof(struct big_numbers_t));
    if(*bn == NULL)
        return 2;
    if(create(*bn, capacity) == 2)
    {
        free(*bn);
        *bn = NULL;
        return 2;
    }
    return 0;
}

void destroy(struct big_numbers_t *bn)
{
    if(bn == NULL || bn->size < 0 || bn->capacity <= 0 || bn->big_number == NULL || bn->size > bn->capacity)
        return;
    for(int i = 0; i < bn->size; i++)
        free(*(bn->big_number + i));
    free(bn->big_number);
}

void destroy_big_numbers(struct big_numbers_t **bn)
{
    if(bn == NULL || *bn == NULL || (*bn)->size < 0 || (*bn)->capacity <= 0 || (*bn)->size > (*bn)->capacity || (*bn)->big_number == NULL)
        return;
    destroy(*bn);
    free(*bn);
    *bn = NULL;
}

int add_big_number(struct big_numbers_t *bn, const char *big_number)
{
    if(bn == NULL || bn->size < 0 || bn->capacity <= 0 || bn->big_number == NULL || big_number == NULL || validate(big_number) == 2)
        return 1;
    if(bn->size == bn->capacity)
        return 3;
    *(bn->big_number + bn->size) = malloc(sizeof(char) * (strlen(big_number) + 1));
    if(*(bn->big_number + bn->size) == NULL)
        return 2;
    memcpy(*(bn->big_number + bn->size), big_number, strlen(big_number) + 1);
    bn->size++;
    return 0;
}

void display(const struct big_numbers_t *bn)
{
    if(bn == NULL || bn->size < 0 || bn->capacity <= 0 || bn->big_number == NULL || bn->size > bn->capacity)
        return;
    for(int i = 0; i < bn->size; i++)
        printf("%s\n", *(bn->big_number + i));
}

int save_big_numbers_b(const struct big_numbers_t *bn, const char *filename)
{
    if(bn == NULL || bn->size < 0 || bn->capacity <= 0 || bn->big_number == NULL || bn->size > bn->capacity || filename == NULL)
        return 1;
    FILE *f = fopen(filename, "wb");
    if(f == NULL)
        return 2;
    fwrite(&bn->size, sizeof(int), 1, f);
    for(int i = 0; i < bn->size; i++)
    {
        int len = strlen(*(bn->big_number + i));
        fwrite(&len, sizeof(int), 1, f);
        fwrite(*(bn->big_number + i), sizeof(char), len, f);
    }
    fclose(f);
    return 0;
}

int load_big_numbers_b(struct big_numbers_t **bn, const char *filename)
{
    if(bn == NULL || filename == NULL)
        return 1;
    FILE *f = fopen(filename, "rb");
    if(f == NULL)
        return 3;
    int size = -1;
    fread(&size, sizeof(int), 1, f);
    if(size <= 0)
    {
        fclose(f);
        return 4;
    }
    if(create_big_numbers(bn, size) == 2)
    {
        fclose(f);
        return 2;
    }
    for(int i = 0; i < size; i++)
    {
        int len = -1;
        fread(&len, sizeof(int), 1, f);
        if(len <= 0)
        {
            fclose(f);
            destroy_big_numbers(bn);
            return 4;
        }
        *((*bn)->big_number + i) = malloc(sizeof(char) * (len + 1));
        if(*((*bn)->big_number + i) == NULL)
        {
            fclose(f);
            destroy_big_numbers(bn);
            return 2;
        }
        (*bn)->size++;
        if(fread(*((*bn)->big_number + i), sizeof(char), len, f) != (size_t)len)
        {
            fclose(f);
            destroy_big_numbers(bn);
            return 4;
        }
        *(*((*bn)->big_number + i) + len) = '\0';
        if(validate(*((*bn)->big_number + i)))
        {
            fclose(f);
            destroy_big_numbers(bn);
            return 4;
        }
    }
    fclose(f);
    return 0;
}

int my_cmp(const void *str1, const void *str2)
{
    if(*(const char *)str1 == '-' && *(const char *)str2 != '-')
        return -1;
    if(*(const char *)str1 != '-' && *(const char *)str2 == '-')
        return 1;
    if(*(const char *)str1 == '-' && *(const char *)str2 == '-')
    {
        int len1 = strlen((const char *)str1);
        int len2 = strlen((const char *)str2);
        if(len1 > len2)
            return -1;
        if(len1 < len2)
            return 1;
        int i = 1;
        while(i < len1 && i < len2)
        {
            if(*((const char *)str1 + i) > *((const char *)str2 + i))
                return -1;
            if(*((const char *)str1 + i) < *((const char *)str2 + i))
                return 1;
            i++;
        }
    } else
    {
        int len1 = strlen((const char *)str1);
        int len2 = strlen((const char *)str2);
        if(len1 > len2)
            return 1;
        if(len1 < len2)
            return -1;
        int i = 0;
        while(i < len1 && i < len2)
        {
            if(*((const char *)str1 + i) > *((const char *)str2 + i))
                return 1;
            if(*((const char *)str1 + i) < *((const char *)str2 + i))
                return -1;
            i++;
        }
    }

    return 0;
}

int sort_big_numbers_asc(struct big_numbers_t *bn)
{
    if(bn == NULL || bn->size < 0 || bn->capacity <= 0 || bn->big_number == NULL || bn->size > bn->capacity)
        return 1;
    for(int i = 0; i < bn->size; i++)
        if(validate(*(bn->big_number + i)) != 0)
            return 1;
    for(int i = 0; i < bn->size; i++)
        for(int j = 1; j < bn->size - i; j++)
            if(my_cmp(*(bn->big_number + j - 1), *(bn->big_number + j)) == 1)
            {
                char *tmp = *(bn->big_number + j - 1);
                *(bn->big_number + j - 1) = *(bn->big_number + j);
                *(bn->big_number + j) = tmp;
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

char* total_sum_big_numbers(const struct big_numbers_t *bn, int *err_code)
{
    if(bn == NULL || bn->size < 0 || bn->capacity <= 0 || bn->big_number == NULL || bn->size > bn->capacity)
    {
        if(err_code != NULL)
            *err_code = 1;
        return NULL;
    }
    char *sum = calloc(2, sizeof(char));
    if(sum == NULL)
    {
        if(err_code != NULL)
            *err_code = 3;
        return NULL;
    }
    *sum = '0';
    for(int i = 0; i < bn->size; i++)
    {
        char *result;
        int res = add(sum, *(bn->big_number + i), &result);
        if(res != 0)
        {
            if(err_code != NULL)
                *err_code = res;
            free(sum);
            return NULL;
        }
        char *to_free = sum;
        sum = result;
        free(to_free);
    }
    if(err_code != NULL)
        *err_code = 0;
    return sum;
}