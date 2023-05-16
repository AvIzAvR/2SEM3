#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct BMPHeader {
    uint16_t type;
    uint32_t fileSize;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t offset;
    uint32_t size;
    uint32_t width;
    uint32_t height;
    uint16_t planes;
    uint16_t bitsPerPixel;
    uint32_t compression;
    uint32_t imageSize;
    uint32_t xPixelsPerMeter;
    uint32_t yPixelsPerMeter;
    uint32_t totalColors;
    uint32_t importantColors;
} BMPHeader;

typedef struct Pixel {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} Pixel;
typedef struct BMPFile {
    BMPHeader header;
    unsigned char palette[1024];
    Pixel** pixels;
} BMPFile;

char* take_name_file();
BMPFile* read_bmp_file(char* path);
void write_bmp_file(char* path, BMPFile* bmp);
void invert_colors(BMPFile *image);
void black_white_colors(BMPFile *image);