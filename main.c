#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "types.h" // structures
#include "file.c"

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

void add_vehicle()
{
    int bla;
    printf("Add vehicle\n"); 
    scanf("%i", &bla);
    printf("%i is now registered!\n", bla);
}

void info(vehicle_t registry[], int count)
{
    printf("You choose info about vehicle\n");
    printf("Please enter number between 1-%i to show vehicle in responding place\n", count);
    int input;
    scanf("%i", &input);

    if (input > 0 && input <= count)
    {
        printf("Info about vehicle on position %i:\n", input);
        printf("Type: %s\n", registry[input-1].type);
        printf("Brand: %s\n", registry[input-1].brand);
        printf("License plate: %s\n", registry[input-1].license_plate);
        printf("Owner: %s\n", registry[input-1].owner.name);
    } else {
        printf("Please enter a number between 1 & %i\n", count);
        info(registry, count);
    }
}

// Shows the whole registry
void show_all(vehicle_t registry[LIST_SIZE], int count)
{
    int i;
    printf("Showing entire registry:\n");
    for(i = 0; i < count; i++)
    {
        printf("%i. %s | %s | %s | %s \n", i+1, registry[i].brand, registry[i].type, registry[i].license_plate, registry[i].owner.name);
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

void act_upon_input(int choice, vehicle_t registry[LIST_SIZE], int count)
{
    switch(choice)
    {
        case 1: add_vehicle();
        break;
        case 2: printf("Remove vehicle\n");
        break;
        case 3: printf("Sort\n");
        break;
        case 4: info(registry, count);
        break;
        case 5: show_all(registry, count);
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
    vehicle_t registry[LIST_SIZE]; //storage
    init_cars();
    int input, count = 0;

    load_registry("registry.txt", registry, &count);

    do{
        print_menu();
        input = handle_user_input();
        act_upon_input(input, registry, count);
    } while(input !=0 );

    save_registry("registry.txt", registry, count);

    return 0;
}