#include "bmp.h"

#define INITIAL_SIZE 3
#define SIZE_BMP 5

#define BITS_1 1
#define BITS_2 2
#define BITS_4 4
#define BITS_8 8
#define BITS_16 16
#define BITS_24 24
#define COLORTABLE_SIZE 1024

#define BITS_1 1
#define BITS_2 2
#define BITS_4 4
#define BITS_8 8
#define BITS_16 16
#define BITS_24 24
#define COLORTABLE_SIZE 1024

BMPFile* read_bmp_file(char* path) {
    BMPFile* bmp = malloc(sizeof(BMPFile));
    FILE *inputFile = fopen(path, "rb");
    if (inputFile == NULL) {
        printf("Error: Failed to open input file.");
        free(bmp);
        return NULL;
    }
    fread(&bmp->header, sizeof(BMPHeader), 1, inputFile);
    int width = bmp->header.width;
    int height = bmp->header.height;
    int bpp = bmp->header.bitsPerPixel;
    printf("%d\n", bpp);
    if(bpp != BITS_1 && bpp != BITS_2 && bpp != BITS_4 && bpp != BITS_8 && bpp != BITS_24) {
        printf("Error: This BMP not supported.");
        free(bmp);
        fclose(inputFile);
        return NULL;
    }
    if(bmp->header.compression) {
        printf("Error: Compression not supported.");
        free(bmp);
        fclose(inputFile);
        return NULL;
    }
    bmp->pixels = malloc(sizeof(Pixel *) * height);
    for (int i = 0; i < height; i++) {
        bmp->pixels[i] = malloc(sizeof(Pixel) * width);
    }
    if (bpp == BITS_1 || bpp == BITS_2 || bpp == BITS_4 || bpp == BITS_8) {
        int padding = (4 - ((width * bpp / 8) % 4)) % 4;
        fread(bmp->palette, sizeof(unsigned char), 1024, inputFile);
        for (int i = height - 1; i >= 0; i--) {
            for (int j = 0; j < width; j++) {
                unsigned char pixel;
                fread(&pixel, sizeof(unsigned char), 1, inputFile);
                bmp->pixels[i][j].red = pixel;
                bmp->pixels[i][j].green = pixel;
                bmp->pixels[i][j].blue = pixel;
            }
            if(bmp->header.bitsPerPixel == 8)
                fseek(inputFile, padding, SEEK_CUR);
        }
    }
    else if(bpp == BITS_24) {
        uint32_t offset = bmp->header.offset;
        fseek(inputFile, offset, SEEK_SET);
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                fread(&bmp->pixels[i][j], sizeof(Pixel), 1, inputFile);
            }
        }
    }
    fclose(inputFile);
    return bmp;
}

char* take_name_file()
{
    int size_string = INITIAL_SIZE;
    char* string = (char*)malloc(size_string * sizeof(char));
    strncpy(string, "../", size_string);

    int index = INITIAL_SIZE;
    char c;
    while ((c = getchar()) != '\n') {
        if (index >= size_string) {
            size_string *= 2;
            string = (char*)realloc(string, size_string * sizeof(char));
        }
        string[index++] = c;
    }
    string = (char*)realloc(string, (size_string + SIZE_BMP) * sizeof(char));
    strncpy(string + index, ".bmp", SIZE_BMP);
    string[size_string + SIZE_BMP] = '\0';

    return string;
}

void write_bmp_file(char* path, BMPFile* bmp) {
    FILE* outputFile = fopen(path, "wb");
    if (outputFile == NULL) {
        printf("Error: Failed to open output file.");
        return;
    }
    int width = bmp->header.width;
    int height = bmp->header.height;
    int bpp = bmp->header.bitsPerPixel;
    // Write header information to output file
    fwrite(&bmp->header, sizeof(BMPHeader), 1, outputFile);

    // Write palette if present
    if (bpp == BITS_1 || bpp == BITS_2 || bpp == BITS_4 || bpp == BITS_8) {
        int padding = (4 - ((width * bpp / 8) % 4)) % 4;
        fwrite(bmp->palette, sizeof(unsigned char), 1024, outputFile);
        // Write pixel data to output file
        for (int i = height - 1; i >= 0; i--) {
            for (int j = 0; j < width; j++) {
                unsigned  char pixel = bmp->pixels[i][j].red;
                fwrite(&pixel, sizeof(unsigned char), 1, outputFile);
            }if(bmp->header.bitsPerPixel == 8) {
                for (int j = 0; j < padding; j++) {
                    fputc(0x00, outputFile);
                }
            }
        }
    }
    else if(bpp == BITS_24) {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                fwrite(&bmp->pixels[i][j], sizeof(Pixel), 1, outputFile);
            }
        }
    }



    // Close output file
    fclose(outputFile);
}


void invert_colors(BMPFile *image)
{
    int width = image->header.width;
    int height = image->header.height;
    if(image->header.bitsPerPixel == BITS_24) {
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                Pixel pixel = image->pixels[i][j];
                pixel.red = 255 - pixel.red;
                pixel.green = 255 - pixel.green;
                pixel.blue = 255 - pixel.blue;
                image->pixels[i][j] = pixel;
            }
        }
    }
    else {
        for(int i = 0; i < COLORTABLE_SIZE; i++) {
            image->palette[i] = 255 - image->palette[i];
        }
    }
}

void black_white_colors(BMPFile *image)
{
    int width = image->header.width;
    int height = image->header.height;
    if(image->header.bitsPerPixel == BITS_24) {
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                Pixel pixel = image->pixels[i][j];
                uint8_t gray = (pixel.red + pixel.green + pixel.blue) / 3;
                pixel.red = gray;
                pixel.green = gray;
                pixel.blue = gray;
                image->pixels[i][j] = pixel;
            }
        }
    }
    else {
        for(int i = 0; i < COLORTABLE_SIZE/3; i+=3) {
            uint8_t gray = (image->palette[i] + image->palette[i+1] + image->palette[i+2]) / 3;
            image->palette[i] = gray;
            image->palette[i+1] = gray;
            image->palette[i+2] = gray;
        }
    }
}



