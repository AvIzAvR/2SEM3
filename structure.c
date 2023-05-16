#include "structure.h"

void get_int(int* x)
{
    while (!scanf_s("%d", x) || getchar() != '\n' || *x <= 0)
    {
        rewind(stdin);
        printf("Invalid data type!\n");
    }
}

void get_st(int* st)
{
    while (!scanf_s("%d", st) || getchar() != '\n' || *st < 1 || *st > 2)
    {
        rewind(stdin);
        printf("Invalid data type!!\n");
    }
}

cars* init_arr(int size)
{
    return (cars*)malloc(size * sizeof(cars));
}

void show_struct(cars arr[], int size)
{
    for (int i = 0; i < size; i++)
        printf("Name: %s        Speed: %d        Year: %d\n", arr[i].name, arr[i].speed, arr[i].year);
}

cars create_cars(int year, int speed, char* name)
{
    cars a;
    a.speed = speed;
    a.year = year;
    a.name = name;
    return a;
}

int get_car(cars arr[])
{
    int size_car = 0;
    int size_z = 256;
    printf("Enter the name of the car to exit enter \'s\':");
    char* z = (char*)calloc(size_z, sizeof(char));
    int i = 0;
    while (1)
    {
        char letter;
        letter = getchar();
        if (letter != '\n')
        {
            if (i < 256)
            {
                z[i] = letter;
                i++;
            }
            else
            {
                size_z++;
                z = (char*)malloc(size_z * sizeof(char));
                z[i] = letter;
                i++;
            }
        }
        else
        {
            z[i] = '\0';
            if (z[0] == 's' && z[1] == '\0')
            {
                break;
            }
            arr[size_car].name = z;
            printf("Enter the maximum speed of the car:");
            get_int(&arr[size_car].speed);
            printf("Введите год выпуска автомобиля:");
            get_int(&arr[size_car].year);
            z = (char*)calloc(256, sizeof(char));
            size_car++;
            printf("\nEnter the name of the car to exit enter \'s\':");
            i = 0;
        }
    }
    return size_car;
}

int quick_year(cars arr[], int low, int high)
{
    int pivot = arr[high].year;
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j].year <= pivot) {
            i++;
            cars temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    cars temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}

void quick_sort_year(cars arr[], int low, int high)
{
    if (low < high) {
        int pi = quick_year(arr, low, high);

        quick_sort_year(arr, low, pi - 1);
        quick_sort_year(arr, pi + 1, high);
    }
}


int quick_speed(cars arr[], int low, int high)
{
    int pivot = arr[high].speed;
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j].speed <= pivot) {
            i++;
            cars temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    cars temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}

void quick_sort_speed(cars arr[], int low, int high)
{
    if (low < high) {
        int pi = quick_speed(arr, low, high);

        quick_sort_speed(arr, low, pi - 1);
        quick_sort_speed(arr, pi + 1, high);
    }
}



int quick_name(cars arr[], int low, int high)
{
    char pivot = arr[high].name[0];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j].name[0] <= pivot) {
            i++;
            cars temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    cars temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}

void quick_sort_name(cars arr[], int low, int high)
{
    if (low < high) {
        int pi = quick_name(arr, low, high);

        quick_sort_name(arr, low, pi - 1);
        quick_sort_name(arr, pi + 1, high);
    }
}

int sort_cars(cars arr[], int size_car)
{
int key;
printf("Choose which method you want to sort the structures by\n1-Alphabetically (names)\n2-By year\n3-By speed\n");
while (!scanf_s("%d", &key)|| key > 3 || key <= 0) {
printf("Invalid data type!\n");
rewind(stdin);
}
switch (key) {
case 1: {
quick_sort_name(arr, 0, size_car-1);
break;
}
case 2: {
quick_sort_year(arr, 0, size_car-1);
break;
}
case 3: {
quick_sort_speed(arr, 0, size_car-1);
break;
}
 }
}

void remove_struct(cars arr[], int* size_car)
{
int delete;
printf("Select the structure number you want to delete:\n");
for (int i = 0; i < (*size_car); ++i) {
printf("[%d]: Name: %s        Speed: %d        Year: %d\n", (i+1), arr[i].name, arr[i].speed, arr[i].year);
}
printf("\n");
rewind(stdin);
while (!scanf_s("%d", &delete) || getchar() != '\n' || delete < 1 || delete > size_car)
{
rewind(stdin);
printf("Invalid data type!!\n");
}

for (int i = delete-1; i < (*size_car); i++)
{
for (int j = i; j < (*size_car) - 1; j++)
{
arr[j] = arr[j + 1];
}
(*size_car)--;
break;
}
}

void menu(cars arr[], int size_car)
{
int key;
while (1) {
printf("What do you want to do?\n1) Show Struct\n2) Sort Struct\n3) Del struct\n");
while (!scanf_s("%d", &key) || key > 3 || key <= 0) {
printf("Invalid data type!\n");
rewind(stdin);
}
switch (key) {
case 1: {
show_struct(arr, size_car);
break;
}
case 2: {
sort_cars(arr, size_car);
show_struct(arr, size_car);
break;
}
case 3: {
remove_struct(arr, &size_car);
show_struct(arr, size_car);
break;
}
default: {
printf("Invalid data type!\n");
break;
}
}
}
}

