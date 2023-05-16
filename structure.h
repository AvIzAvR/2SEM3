#ifndef structure
#define structure

#include<stdio.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<locale.h>
#include<stdlib.h>

typedef enum {
    Red,
    White,
    Black,
    Green
} color;


typedef struct {
    char* name;
    int speed;
    int year;
} cars;

void get_int(int* x);
cars* init_arr(int size);
void show_struct(cars arr[], int size);
int get_car(cars arr[]);
void quick_sort_year(cars arr[], int low, int high);
void quick_sort_speed(cars arr[], int low, int high);
void quick_sort_name(cars arr[], int low, int high);
void get_st(int* st);
cars create_cars(int year, int speed, char* name);
void menu(cars arr[], int size_car);


#endif