#pragma  once

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/*
 * #define Entity uint32_t
 *
 * #define GETX(X) (uint8_t) ((X << 24) >> 24) // the x value are the lower 8 bits
 * #define GETY(X) (uint8_t) ((X << 16) >> 24) // the y value are the next 8 bits (after x)
 * #define GETRAD(X) (uint8_t) ((X << 12) >> 28) //radius value is the next 4 bits (max rad = 15)
 * #define GETXD(X) (int8_t) ((X << 6) >> 31) == 0 ? ((X << 6) >> 26) : (((X << 6) >> 26)|(3 << 6)) // the x movement are the next 6 bits (after rad)
 * #define GETYD(X) (int8_t) (X >> 31) == 0 ? (X >> 26) : ((X >> 26)|(3 << 6)) // the y movement are the next 6 bits (after x)
 *
 * #define XMASK  0xff //1's on the bits corresponding to the value
 * #define YMASK  0xff << 8
 * #define RADMASK  0xf << 16
 * #define XDMASK  0x3f << 20
 * #define YDMASK  0x3f << 26
 *
 * #define SETX(X,V) {X &= !XMASK;
 *                    X |= (V & XMASK);}
 * #define SETY(X,V) {X &= !YMASK;
 *                    X |= ((V << 8) & YMASK);}
 * #define SETRAD(X,V) {X &= !RADMASK
 *                      X |= (V << 16) & RADMASK);}
 * #define SETXD(X,V) {X &= !XDMASK;
 *                     X |= ((V << 20) & XDMASK);}
 * #define SETYD(X,V) {X &= !YDMASK;
 *                     X |= ((V << 26) & YDMASK);}
 *
 * //for pacman effect
 * #define REVXD(X) { int8_t dir = !GETXD(X) + 1;
 *                    SETXD(X,dir);}
 * #define REVYD(X) { int8_t dir = !GETYD(X) + 1;
 *                    SETYD(X,dir);}
 *
 */

typedef struct {
    uint8_t x, y, rad;
    float_t vel, alpha;
} Entity;

/*
 * typedef struct {
 *     uint8_t x, y;
 *     union color {
 *         uint32_t col;
 *         uint32_t * image; //raw image
 *     }
 *     uint32_t * bitmap; //values of the obj
 * } Texture;
 */
typedef struct {
    Entity * array = NULL;
    Entity * end = NULL;
    uint16_t maxsize = 0;
} DinArray;

void initArray(DinArray, uint16_t);
void deleteArray(DinArray);
void insert(DinArray, Entity);
void extract(DinArray, Entity *);
inline uint32_t getSize(DinArray);

void initEntity(Entity, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t);


