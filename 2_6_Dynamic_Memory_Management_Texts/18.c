#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFORS_COUNT 4
#define BUFFOR_LEN 10

void destroy(char **words)
{
    if(words == NULL)
        return;
    int i = 0;
    while(*(words + i) != NULL)
        free(*(words + i++));
    free(words);
}

int not_abs(int x)
{
    if(x > 0)
        return -x;
    return x;
}

int validate(char *str)
{
    int i = 0;
    while(*(str + i) != '\0')
    {
        if(*(str + i) < 'A' || *(str + i) > 'Z')
            return 1;
        i++;
    }
    return 0;
}

int are_words_crossable(const char *first, const char *second)
{
    if(first == NULL || second == NULL)
        return -1;
    int len = strlen(second);
    int i;
    for(i = 0; i < len; i++)
        if(strchr(first, (int)*(second + i)) != NULL)
            return i;
    return -1;
}

int create_leading_word_cross(const char *first, const char *second, char ***result)
{
    if(first == NULL || second == NULL || result == NULL || validate((char*)first) || validate((char*)second))
        return -1;
    int cross = are_words_crossable(first, second);
    if(cross < 0)
    {
        *result = NULL;
        return -2;
    }
    int len1 = strlen(first);
    int len2 = strlen(second);
    *result = malloc(sizeof(char*) * (len1 + 1));
    if(*result == NULL)
        return -3;
    int flag = 1;
    for(int i = 0; i < len1; i++)
    {
        if(*(first + i) == *(second + cross) && flag)
        {
            *((*result) + i) = malloc(sizeof(char) * (len2 + 1));
            flag = 0;
        }
        else
            *((*result) + i) = malloc(sizeof(char) * (cross + 2));
        if(*((*result) + i) == NULL)
        {
            for(; i >= 0; i--)
                free(*((*result) + i));
            free(*result);
            *result = NULL;
            return -3;
        }
    }
    *((*result) + len1) = NULL;
    int ret = -4;
    for(int i = 0; i < len1; i++)
    {
        if(*(first + i) == *(second + cross) && ret == -4)
        {
            ret = i;
            memcpy(*((*result) + i), second, sizeof(char) * (len2 + 1));
        } else
        {
            int j;
            for(j = 0; j < cross; j++)
                *(*((*result) + i) + j) = ' ';
            *(*((*result) + i) + j++) = *(first + i);
            *(*((*result) + i) + j) = '\0';
        }
    }
    return ret;
}

int create_double_leading_word_cross(const char *first, const char *second, const char *third, const char *fourth, char ***result, char ***first_cross, char ***second_cross)
{
    if(first == NULL || second == NULL || third == NULL || fourth == NULL || result == NULL || first_cross == NULL || second_cross == NULL || validate((char*)first) || validate((char*)second) || validate((char*)third) || validate((char*)fourth))
        return 1;
    int res1 = create_leading_word_cross(second, first, first_cross);
    if(res1 == -2)
    {
        *result = NULL;
        *second_cross = NULL;
        return 2;
    }
    if(res1 == -3)
    {
        *result = NULL;
        *second_cross = NULL;
        return 3;
    }
    int res2 = create_leading_word_cross(fourth, third, second_cross);
    if(res2 == -2)
    {
        *result = NULL;
        destroy(*first_cross);
        *first_cross = NULL;
        return 2;
    }
    if(res2 == -3)
    {
        *result = NULL;
        destroy(*first_cross);
        *first_cross = NULL;
        return 3;
    }
    int cross_row = res1;
    if(cross_row < res2)
        cross_row = res2;
    int len_cross1 = strlen(second);
    int len_cross2 = strlen(fourth);
    int width_cross1 = strlen(first);
    int rows, k, l;
    for(rows = 1, k = not_abs(cross_row - res1), l = not_abs(cross_row - res2); k < len_cross1 || l < len_cross2; rows++, k++, l++);
    *result = malloc(sizeof(char*) * rows);
    if(*result == NULL)
    {
        destroy(*first_cross);
        destroy(*second_cross);
        *first_cross = NULL;
        *second_cross = NULL;
        return 3;
    }
    int i;
    for(i = 0, k = not_abs(cross_row - res1), l = not_abs(cross_row - res2); i < rows - 1; i++, k++, l++)
    {
        if(k < len_cross1 && k >= 0 && (l < 0 || l >= len_cross2))
            *((*result) + i) = calloc((strlen(*((*first_cross) + k)) + 1), sizeof(char));
        else if(l >= 0 && l < len_cross2)
            *((*result) + i) = calloc((width_cross1 + 3 + strlen(*((*second_cross) + l)) + 1), sizeof(char));
        if(*((*result) + i) == NULL)
        {
            for(; i >= 0; i--)
                free(*((*result) + i));
            free(*result);
            *result = NULL;
            destroy(*first_cross);
            destroy(*second_cross);
            *first_cross = NULL;
            *second_cross = NULL;
            return 3;
        }
    }
    *((*result) + rows - 1) = NULL;
    for(i = 0, k = not_abs(cross_row - res1), l = not_abs(cross_row - res2); i < rows - 1; i++, k++, l++)
    {
        if(k >= 0 && k < len_cross1)
            strcpy(*((*result) + i), *((*first_cross) + k));
        if(l >= 0 && l < len_cross2)
        {
            for(int j = strlen(*((*result) + i)); j < width_cross1 + 3; j++)
                *(*((*result) + i) + j) = ' ';
            strcat(*((*result) + i), *((*second_cross) + l));
        }
    }
    return 0;
}

int main(void)
{
    char *word1 = malloc(sizeof(char) * (BUFFOR_LEN + 1));
    if(word1 == NULL)
    {
        printf("Failed to allocate memory");
        return 8;
    }
    char *word2 = malloc(sizeof(char) * (BUFFOR_LEN + 1));
    if(word2 == NULL)
    {
        printf("Failed to allocate memory");
        free(word1);
        return 8;
    }
    char *word3 = malloc(sizeof(char) * (BUFFOR_LEN + 1));
    if(word3 == NULL)
    {
        printf("Failed to allocate memory");
        free(word1);
        free(word2);
        return 8;
    }
    char *word4 = malloc(sizeof(char) * (BUFFOR_LEN + 1));
    if(word4 == NULL)
    {
        printf("Failed to allocate memory");
        free(word1);
        free(word2);
        free(word3);
        return 8;
    }
    printf("Enter words: ");
    if(scanf("%10s %10s %10s %10s", word1, word2, word3, word4) != BUFFORS_COUNT)
    {
        printf("Incorrect input");
        free(word1);
        free(word2);
        free(word3);
        free(word4);
        return 1;
    }
    if(validate(word1) || validate(word2) || validate(word3) || validate(word4))
    {
        printf("Incorrect input");
        free(word1);
        free(word2);
        free(word3);
        free(word4);
        return 1;
    }
    char **res;
    char **first;
    char **second;
    int ret = create_double_leading_word_cross(word1, word2, word3, word4, &res, &first, &second);
    free(word1);
    free(word2);
    free(word3);
    free(word4);
    if(ret == 2)
    {
        printf("Unable to make two crosses");
        return 0;   
    }
    if(ret == 3)
    {
        printf("Failed to allocate memory");
        return 8;
    }
    int i = 0;
    while(*(first + i) != NULL)
        printf("%s\n", *(first + i++));
    printf("\n");
    i = 0;
    while(*(second + i) != NULL)
        printf("%s\n", *(second + i++));
    printf("\n");
    i = 0;
    while(*(res + i) != NULL)
        printf("%s\n", *(res + i++));
    destroy(res);
    destroy(first);
    destroy(second);
    return 0;
}