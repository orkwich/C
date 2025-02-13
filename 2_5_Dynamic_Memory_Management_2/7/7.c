#include "image_utils.h"
#define FNAME_SIZE 40

void clear()
{
    char c;
    if((c = getchar()) != '\n' && c != '\0')
        clear();
}

void fname_modify(char *fname)
{
    char *fextenction = malloc(sizeof(char) * 10);
    int i = 0;
    while(*(fname + i) != '.')
        i++;
    int j = 0;
    while(*(fname + i) != '\0')
    {
        if(*(fname + i) == '.')
            j = 0;
        *(fextenction + j++) = *(fname + i++);
    }
    *(fextenction + j) = '\0';
    char *tmp = strrchr(fname, '.');
    *tmp = '\0';
    strcat(fname, "_modified");
    strcat(fname, fextenction);
    free(fextenction);
}

int main(void)
{
    char *fname = malloc(sizeof(char) * FNAME_SIZE);
    if(fname == NULL)
    {
        printf("Failed to allocate memory");
        return 8;
    }
    printf("Enter destination image file name: ");
    scanf("%40s", fname);
    int err_code = 0;
    struct image_t *img = load_image_t(fname, &err_code);
    if(err_code == 2)
    {
        printf("Couldn't open file");
        free(fname);
        return 4;
    }
    if(err_code == 3)
    {
        printf("File corrupted");
        free(fname);
        return 6;
    }
    if(err_code == 4)
    {
        printf("Failed to allocate memory");
        free(fname);
        return 8;
    }
    clear();
    printf("How many subimages you want to draw: ");
    int images = 0;
    if(scanf("%d", &images) != 1)
    {
        printf("Incorrect input");
        destroy_image(&img);
        free(fname);
        return 1;
    }
    if(images <= 0)
    {
        printf("Incorrect input data");
        destroy_image(&img);
        free(fname);
        return 2;
    }
    char *fname2 = malloc(sizeof(char) * FNAME_SIZE);
    if(fname2 == NULL)
    {
        printf("Failed to allocate memory");
        destroy_image(&img);
        free(fname);
        return 8;
    }
    while(images--)
    {
        printf("Enter a name of a subimage: ");
        scanf("%39s", fname2);
        struct image_t *tmp_img = load_image_t(fname2, &err_code);
        if(err_code == 2)
        {
            printf("Couldn't open file\n");
            continue;
        }
        if(err_code == 3)
        {
            printf("File corrupted\n");
            continue;
        }
        if(err_code == 4)
        {
            printf("Failed to allocate memory");
            free(fname);
            free(fname2);
            destroy_image(&tmp_img);
            destroy_image(&img);
            return 8;
        }
        clear();
        int x = 0;
        int y = 0;
        printf("Enter coordinates (x, y): ");
        if(scanf("%d %d", &x, &y) != 2)
        {
            printf("Incorrect Input\n");
            free(fname);
            free(fname2);
            destroy_image(&tmp_img);
            destroy_image(&img);
            return 1;
        }
        if(draw_image(img, tmp_img, x, y))
            printf("Incorrect input data\n");
        destroy_image(&tmp_img);
    }
    free(fname2);
    fname_modify(fname);
    if(save_image_t(fname, img) != 0)
    {
        printf("Couldn't create file");
        free(fname);
        destroy_image(&img);
        return 5;
    }
    printf("File saved");
    free(fname);
    destroy_image(&img);
    return 0;
}