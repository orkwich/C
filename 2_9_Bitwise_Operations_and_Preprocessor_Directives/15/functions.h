#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define DEFINE_ARRAY(TYPE) \
    struct array_##TYPE##_t \
    { \
 	    int size; \
 	    int capacity; \
 	    TYPE *data; \
    };

#define CREATE_ARRAY(TYPE) \
    struct array_##TYPE##_t *create_array_##TYPE(int size) \
    { \
        if(size <= 0) \
            return NULL; \
        struct array_##TYPE##_t *arr = malloc(sizeof(struct array_##TYPE##_t)); \
        if(arr == NULL) \
            return NULL; \
        arr->data = malloc(sizeof(TYPE) * size); \
        if(arr->data == NULL) \
        { \
            free(arr); \
            return NULL; \
        } \
        arr->size = 0; \
        arr->capacity = size; \
        return arr; \
    }

#define FREE_ARRAY(TYPE) \
    void free_array_##TYPE(struct array_##TYPE##_t *array) \
    { \
        if(array == NULL) \
            return; \
        free(array->data); \
        free(array); \
    }

#define SAVE_ARRAY(TYPE) \
    int save_array_##TYPE(const struct array_##TYPE##_t *array, const char *filename) \
    { \
        if(array == NULL || filename == NULL || array->data == NULL || array->size <= 0 || array->capacity <= 0 || array->size > array->capacity) \
            return 1; \
        FILE *f = fopen(filename, "wb"); \
        if(f == NULL) \
            return 2; \
        fwrite(&(array->size), sizeof(int), 1, f); \
        fwrite(array->data, sizeof(TYPE), array->size, f); \
        fclose(f); \
        return 0; \
    }

#define LOAD_ARRAY(TYPE) \
    int load_array_##TYPE(struct array_##TYPE##_t **array, const char *filename) \
    { \
        if(array == NULL || filename == NULL) \
            return 1; \
        FILE *f = fopen(filename, "rb"); \
        if(f == NULL) \
            return 2; \
        int size = 0; \
        if(fread(&size, sizeof(int), 1, f) != 1) \
        { \
            fclose(f); \
            return 3; \
        } \
        if(size <= 0) \
        { \
            fclose(f); \
            return 3; \
        } \
        *array = create_array_##TYPE(size); \
        if(*array == NULL) \
        { \
            fclose(f); \
            return 4; \
        } \
        if(fread((*array)->data, sizeof(TYPE), size, f) != (size_t)size) \
        { \
            fclose(f); \
            free_array_##TYPE(*array); \
            *array = NULL; \
            return 3; \
        } \
        (*array)->size = size; \
        fclose(f); \
        return 0; \
    }

#define SORT_ARRAY(TYPE) \
    int sort_array_##TYPE(struct array_##TYPE##_t *array) \
    { \
        if(array == NULL || array->size <= 0 || array->capacity <= 0 || array->data == NULL || array->size > array->capacity) \
            return 1; \
        for(int i = 0; i < array->size; i++) \
        { \
            for(int j = 1; j < array->size - i; j++) \
                if(*(array->data + j - 1) > *(array->data + j)) \
                { \
                    TYPE tmp = *(array->data + j - 1); \
                    *(array->data + j - 1) = *(array->data + j); \
                    *(array->data + j) = tmp; \
                } \
        } \
        return 0; \
    }

#endif