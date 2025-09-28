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

// Functions

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

int add_vehicle()
{
    int bla;
    printf("Add vehicle\n"); 
    scanf("%i", &bla);
    printf("%i is now registered!\n", bla);
}

int info()
{
    printf("You choose info about vehicle\n");
    printf("Please enter number to show vehicle in responding place\n");
    int input;
    scanf("%i", &input);

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
    vehicle_t car[LIST_SIZE] = 
    {
        {"307 CC", "Peugeot", "WUD786", person[input-1]},
        {"A3", "Audi", "ATO717", person[input-1]},
        {"307 CC", "BMW", "3", person[input-1]},
        {"307 CC", "Volvo", "4", person[input-1]},
        {"307 CC", "Mercedes", "5", person[input-1]},
        {"307 CC", "Volkswagen", "6", person[input-1]},
        {"307 CC", "Kia", "7", person[input-1]},
        {"307 CC", "Mazda", "8", person[input-1]},
        {"307 CC", "Tesla", "9", person[input-1]},
        {"307 CC", "Fiat", "10", person[input-1]},
    };

    printf("Info about vehicle on position %i:\n", input);
    printf("Type: %s\n", car[input-1].type);
    printf("Brand: %s\n", car[input-1].brand);
    printf("License plate: %s\n", car[input-1].license_plate);
    printf("Owner: %s\n", car[input-1].owner.name);
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
        case 1: 
            add_vehicle();
        break;
        case 2: printf("Remove vehicle\n");
        break;
        case 3: printf("Sort\n");
        break;
        case 4: 
            info();
        break;
        case 5: printf("Show all\n");
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
    int input;

    do{
        print_menu();
        input = handle_user_input();
        act_upon_input(input);
    } while(input !=0 );

    return 0;
}