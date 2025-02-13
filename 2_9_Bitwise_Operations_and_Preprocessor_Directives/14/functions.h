#ifndef FUNCTIONS_H
#define FUNCTIONS_h

#define CREATE_READ_FUNCTIONS(TYPE, FORMAT) \
    int read_##TYPE(TYPE *data, int size) \
    { \
        if(data == NULL || size <= 0) \
            return 1; \
        for(int i = 0; i < size; i++) \
            if(scanf(FORMAT, data + i) != 1) \
                return 2; \
        return 0; \
    }

#define CREATE_SORT_FUNCTIONS(TYPE) \
    int sort_##TYPE(TYPE *data, int size) \
    { \
        if(data == NULL || size <= 0) \
            return 1; \
        for(int i = 0; i < size; i++) \
        { \
            for(int j = 1; j < size - i; j++) \
            { \
                if(*(data + j - 1) > *(data + j)) \
                { \
                    TYPE tmp = *(data + j - 1); \
                    *(data + j - 1) = *(data + j); \
                    *(data + j) = tmp; \
                } \
            } \
        } \
        return 0; \
    }

#define CREATE_DISPLAY_FUNCTIONS(TYPE, FORMAT) \
    void display_##TYPE(const TYPE *data, int size) \
    { \
        if(data == NULL || size <= 0) \
            return; \
        for(int i = 0; i < size; i++) \
        { \
            printf(FORMAT, *(data + i)); \
            printf(" "); \
        } \
    }

#endif