#include "gameComponents.h"

void initArray(DinArray arr, uint16_t size){
    arr.maxsize = size;
    arr.array = calloc(size,4);
    arr.end=arr.array;
}

void deleteArray(DinArray arr){
    free(arr.array);
    arr.array = NULL;
    arr.end = NULL;
    arr.maxsize = 0;
}

void insert(DinArray arr, Entity e){
    if(e == NULL) return;
    uint16_t size = getSize(arr);
    if(size >= arr.maxsize){
        arr.maxsize *= 2;
        realloc(arr.array,arr.maxsize);
        arr.end = (arr.array + size*4);
    }
    *(arr.end) = e;
    arr.end += 4;
}

void extract(DinArray arr, Entity * e){
    if(e < arr.array && e >= arr.end) return;
    arr.end -= 4;
    if (e != arr.end) *e = *(arr.end);
    *(arr.end) = NULL;
    uint16_t size = getSize(arr);
    if(size < arr.maxsize/4){
        arr.maxsize /= 2;
        realloc(arr.array,arr.maxsize);
        arr.end = (arr.array + size*4);
    }
}

inline uint32_t getSize(DinArray arr){
    return (arr.end-arr.array)/4;
}

void initEntity(Entity e, uint8_t _x, uint8_t _y, uint8_t _rad, uint8_t _xd, uint8_t _yd){
    srand(time(NULL));
    e.x = _x >= 0 ? _x : rand() % 256;
    e.x = _y >= 0 ? _y : rand() % 256;
    e.x = _rad >= 0 ? _rad : rand() % 16 ;
    e.x = _xd >= 0 ? _xd : rand() % 256 - 128;
    e.x = _yd >= 0 ? _yd : rand() % 256 - 128;
}
