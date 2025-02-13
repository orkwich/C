#include <stdio.h>
#define MAX_TEXT_LEN 1000
#define FNAME_SIZE 29

union bit_set
{
    unsigned char byte;
    struct
    {
        unsigned char bit1 : 1;
        unsigned char bit2 : 1;
        unsigned char bit3 : 1;
        unsigned char bit4 : 1;
        unsigned char bit5 : 1;
        unsigned char bit6 : 1;
        unsigned char bit7 : 1;
        unsigned char bit8 : 1;
    } bits;
};

void clear()
{
    char c;
    if((c = getchar()) != '\n' && c != '\0')
        clear();
}

int encode(const char *input, char *txt, const char *output)
{
    if(input == NULL || txt == NULL || output == NULL)
        return 1;
    FILE *in = fopen(input, "r");
    if(in == NULL)
        return 2;
    FILE *out = fopen(output, "w");
    if(out == NULL)
    {
        fclose(in);
        return 4;
    }
    int bytes_count = 0;
    union bit_set b;
    union bit_set txt_b;
    txt_b.byte = (unsigned char)*txt;
    while(fscanf(in, "%hhu%*1[ ]", &(b.byte)) != EOF)
    {
        bytes_count++;
        if(bytes_count % 8 == 1)
            b.bits.bit1 = txt_b.bits.bit8;
        if(bytes_count % 8 == 2)
            b.bits.bit1 = txt_b.bits.bit7;
        if(bytes_count % 8 == 3)
            b.bits.bit1 = txt_b.bits.bit6;
        if(bytes_count % 8 == 4)
            b.bits.bit1 = txt_b.bits.bit5;
        if(bytes_count % 8 == 5)
            b.bits.bit1 = txt_b.bits.bit4;
        if(bytes_count % 8 == 6)
            b.bits.bit1 = txt_b.bits.bit3;
        if(bytes_count % 8 == 7)
            b.bits.bit1 = txt_b.bits.bit2;
        if(bytes_count % 8 == 0)
        {
            b.bits.bit1 = txt_b.bits.bit1;
            if(*txt != '\0')
                txt++;
            if(*txt != '\0')
                txt_b.byte = (unsigned char)*txt;
            if(*txt == '\0')
                txt_b.byte = 0;
        }
        char c = getc(in);
        fprintf(out, "%hhu ", b.byte);
        if(c == '\n')
            fprintf(out, "\n");
        else if(c >= '0' && c <= '9')
            ungetc(c, in);
        else if(c != -1)
        {
            fclose(out);
            fclose(in);
            return 3;
        }
    }
    fclose(out);
    fclose(in);
    if(*txt != '\0')
        return 3;
    return 0;
}

int decode(const char *filename, char *txt, int size)
{
    if(filename == NULL || txt == NULL || size <= 0)
        return 1;
    FILE *f = fopen(filename, "r");
    if(f == NULL)
        return 2;
    int bytes_count = 0;
    union bit_set b;
    union bit_set answer;
    char *input_txt = txt;
    while(size - 1)
    {
        int tmp = fscanf(f, "%hhu", &(b.byte));
        if(tmp == EOF)
            break;
        if(tmp != 1)
        {
            fclose(f);
            return 3;
        }
        bytes_count++;
        if(bytes_count % 8 == 1)
            answer.bits.bit8 = b.bits.bit1;
        if(bytes_count % 8 == 2)
            answer.bits.bit7 = b.bits.bit1;
        if(bytes_count % 8 == 3)
            answer.bits.bit6 = b.bits.bit1;
        if(bytes_count % 8 == 4)
            answer.bits.bit5 = b.bits.bit1;
        if(bytes_count % 8 == 5)
            answer.bits.bit4 = b.bits.bit1;
        if(bytes_count % 8 == 6)
            answer.bits.bit3 = b.bits.bit1;
        if(bytes_count % 8 == 7)
            answer.bits.bit2 = b.bits.bit1;
        if(bytes_count % 8 == 0)
        {
            answer.bits.bit1 = b.bits.bit1;
            *txt++ = (char)answer.byte;
            size--;
        }
    }
    *txt = '\0';
    fclose(f);
    if(bytes_count % 8 != 0)
        return 3;
    char tmp[MAX_TEXT_LEN + 1];
    if(sscanf(input_txt, "%1000[^,.:\"- A-Za-z]", tmp) == 1)
        return 3;
    return 0;
}

int main(void)
{
    printf("Do you want to encode (E/e) or decode (D/d) a message? ");
    char input = '\0';
    if(scanf("%1[EeDd]", &input) != 1)
    {
        printf("Incorrect input data");
        return 1;
    }
    clear();
    if(input == 'e' || input == 'E')
    {
        printf("Enter a message to be encoded: ");
        char txt[MAX_TEXT_LEN + 1];
        scanf("%1000[^\n]", txt);
        clear();
        printf("Enter input file name: ");
        char fin_name[FNAME_SIZE + 1];
        scanf("%29s", fin_name);
        clear();
        printf("Enter output file name: ");
        char fout_name[FNAME_SIZE + 1];
        scanf("%29s", fout_name);
        int tmp = encode(fin_name, txt, fout_name);
        if(tmp == 2)
        {
            printf("Couldn't open file");
            return 4;
        }
        if(tmp == 3)
        {
            printf("File corrupted");
            return 6;
        }
        if(tmp == 4)
        {
            printf("Couldn't create file");
            return 5;
        }
        printf("File saved");
    } else
    {
        printf("Enter input file name: ");
        char fname[FNAME_SIZE + 1];
        scanf("%29s", fname);
        char txt[MAX_TEXT_LEN + 1];
        int tmp = decode(fname, txt, MAX_TEXT_LEN);
        if(tmp == 2)
        {
            printf("Couldn't open file");
            return 4;
        }
        if(tmp == 3)
        {
            printf("File corrupted");
            return 6;
        }
        printf("%s", txt);
    }
    return 0;
}