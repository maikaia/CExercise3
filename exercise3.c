// Nils-Olov Olsson & Samuel Grafström
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// Constants

#define SIZE 100
#define LIST_SIZE 10

// Structures

struct Person {
    char name[SIZE];
    int age;
};
typedef struct Person person_t;

struct Vehicle {
    char type[SIZE];
    char brand[SIZE];
    char license_plate[SIZE];
    person_t owner;
};
typedef struct Vehicle vehicle_t;

person_t person[LIST_SIZE] = 
{
    {"Nils-Olov Olsson", 24}, 
    {"Samuel Grafström", 23},
    {"3", 23},
    {"4", 23},
    {"5", 23},
    {"6", 23},
    {"7", 23},
    {"8", 23},
    {"9", 23},
    {"10", 23},
};
vehicle_t car[LIST_SIZE];

// Functions

// Temporary hard coded list of cars, will change later
void init_cars()
{
    car[0] = (vehicle_t){"307 CC", "Peugeot", "WUD786", person[0]};
    car[1] = (vehicle_t){"A3", "Audi", "ATO717", person[1]};
    car[2] = (vehicle_t){"307 CC", "BMW", "3", person[2]};
    car[3] = (vehicle_t){"307 CC", "BMW", "4", person[3]};
    car[4] = (vehicle_t){"307 CC", "BMW", "5", person[4]};
    car[5] = (vehicle_t){"307 CC", "BMW", "6", person[5]};
    car[6] = (vehicle_t){"307 CC", "BMW", "7", person[6]};
    car[7] = (vehicle_t){"307 CC", "BMW", "8", person[7]};
    car[8] = (vehicle_t){"307 CC", "BMW", "9", person[8]};
    car[9] = (vehicle_t){"307 CC", "BMW", "10", person[9]};
}

void print_menu()
{
    printf("-----------------------------\n");
    printf("1. Add vehicle\n");
    printf("2. Remove vehicle\n");
    printf("3. Sort\n");
    printf("4. Info\n");
    printf("5. Show all\n");
    printf("6. Add random\n");
    printf("7. Search\n");
    printf("0. Quit\n");
    printf("-----------------------------\n");
}

void add_vehicle()
{
    int bla;
    printf("Add vehicle\n"); 
    scanf("%i", &bla);
    printf("%i is now registered!\n", bla);
}

void info()
{
    printf("You choose info about vehicle\n");
    printf("Please enter number to show vehicle in responding place\n");
    int input;
    scanf("%i", &input);

    printf("Info about vehicle on position %i:\n", input);
    printf("Type: %s\n", car[input-1].type);
    printf("Brand: %s\n", car[input-1].brand);
    printf("License plate: %s\n", car[input-1].license_plate);
    printf("Owner: %s\n", car[input-1].owner.name);
}

// Shows the whole registry
void show_all()
{
    int i;
    printf("Showing entire registry:\n");
    for(i = 0; i < LIST_SIZE; i++)
    {
        printf("%i. %s | %s | %s | %s\n", i+1, car[i].type, car[i].brand, car[i].license_plate, car[i].owner.name);
    }
}

int handle_user_input()
{
    char buffer[SIZE];
    int temp;
    scanf("%s", buffer);
    if(isalpha(buffer[0]) || strlen(buffer) > 1)
    {
        return -1;
    }
    temp = atoi(buffer);
    
    return temp;
}

void act_upon_input(int choice)
{
    switch(choice)
    {
        case 1: add_vehicle();
        break;
        case 2: printf("Remove vehicle\n");
        break;
        case 3: printf("Sort\n");
        break;
        case 4: info();
        break;
        case 5: show_all();
        break;
        case 6: printf("Add random\n");
        break;
        case 7: printf("Searh\n");
        break;
        case 0: printf("Exiting program!\n");
        break;
        default: printf("Not a valid input, try using a number you see on the menu\n");
        break;
    }
}


// Main

int main()
{
    init_cars();
    int input;

    do{
        print_menu();
        input = handle_user_input();
        act_upon_input(input);
    } while(input !=0 );

    return 0;
}