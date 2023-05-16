#include"structure.h"

void main()
{
	setlocale(LC_ALL, "Rus");
	int st = 0;
	printf("To use ready-made structures, enter 1\nTo enter the structures yourself, enter 2\n");
	get_st(&st);
	cars* car = NULL;
	int size_car = 0;
	if (st == 1)
	{
		car = init_arr(4);
		car[0] = create_cars(2000, 100, "Audi");
		car[1] = create_cars(2007, 110, "Mercedes");
		car[2] = create_cars(2001, 90, "Lada");
		car[3] = create_cars(2010, 80, "Maserati");
		car[4] = create_cars(2020, 300, "Bugatti");
		size_car = 5;
	}
	if(st == 2)
	{
		car = init_arr(256);
		size_car = get_car(car);
	}
	menu(car, size_car);

}