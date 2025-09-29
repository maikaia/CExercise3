#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "types.h" 
#include "file.h" // load/save registry

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

void input_string(const char *prompt, char *dest, size_t size){
    printf("%s", prompt);
    fgets(dest, size, stdin);
    strtok(dest, "\n");
}

void add_vehicle(vehicle_t registry[], int *count)
{
    if(*count >= LIST_SIZE){
        printf("Registry is full\n");
    } else {
        char buffer[SIZE];
        int c;

        input_string("Enter brand: ", registry[*count].brand, SIZE);

        input_string("Enter type: ", registry[*count].type, SIZE);

        input_string("Enter license number: ", registry[*count].license_plate, SIZE);

        input_string("Enter owners name: ", registry[*count].owner.name, SIZE);

        printf("Enter owners age: ");
        fgets(buffer, SIZE, stdin); 
        strtok(buffer, "\n");
        registry[*count].owner.age = atoi(buffer);

        (*count)++;
        printf("Vehicle added!\n", *count);

        save_registry("registry.txt", registry, *count);
    }
}

void remove_vehicle(vehicle_t registry[], int *count){
    if (*count == 0){
        printf("Registry is empty!\n");
        return;
    }

    char buffer[SIZE];

    printf("Enter a number between 1-%i to remove that vehicle\n", *count);
    fgets(buffer, SIZE, stdin);
    int input = atoi(buffer);

    if (input < 1 || input > *count) {
        printf("Invalid position.\n");
        return;
    }

    for (int i = input - 1; i < *count - 1; i++) {
        registry[i] = registry[i + 1];
    }

    (*count)--;
    printf("Vehicle at position %i is now removed\n", input);

    save_registry("registry.txt", registry, *count);
}


// Shows the whole registry
void show_all(vehicle_t registry[], int count)
{
    int i;
    printf("Showing entire registry:\n");
    for(i = 0; i < count; i++)
    {
        printf("%i. %s | %s | %s | %s | %i \n", i+1, registry[i].brand, registry[i].type, registry[i].license_plate, registry[i].owner.name, registry[i].owner.age);
    }
}

// Safe input
int handle_user_input()
{
    char buffer[SIZE];
    fgets(buffer, SIZE, stdin);
    if(buffer == NULL || isalpha(buffer[0])) 
    {
        return -1;
    }
    strtok(buffer, "\n"); // remove newline
    
    return atoi(buffer); //convert to int
}

// Shows information about one vehicle
void info(vehicle_t registry[], int count)
{
    printf("You choose info about vehicle\n");
    printf("Please enter number between 1-%i to show vehicle in responding place\n", count);

    int input;
    input = handle_user_input();

    if (input > 0 && input <= count)
    {
        printf("Info about vehicle on position %i:\n", input);
        printf("Type: %s\n", registry[input-1].type);
        printf("Brand: %s\n", registry[input-1].brand);
        printf("License plate: %s\n", registry[input-1].license_plate);
        printf("Owner: %s\n", registry[input-1].owner.name);
    } else {
        printf("Invalid input, try again\n");
    }
}

void act_upon_input(int choice, vehicle_t registry[], int *count)
{
    switch(choice)
    {
        case 1: add_vehicle(registry, count); break;
        case 2: remove_vehicle(registry, count); break;
        case 3: printf("Sort\n"); break;
        case 4: info(registry, *count); break;
        case 5: show_all(registry, *count); break;
        case 6: printf("Add random\n"); break;
        case 7: printf("Searh\n"); break;
        case 0: printf("Exiting program!\n"); break;
        default: printf("Not a valid input, try using a number you see on the menu\n"); break;
    }
}

// Main

int main()
{
    vehicle_t registry[LIST_SIZE]; //storage of registry
    int input, count = 0;

    load_registry("registry.txt", registry, &count);

    do{
        print_menu();
        input = handle_user_input();
        act_upon_input(input, registry, &count);
    } while(input !=0 );

    save_registry("registry.txt", registry, count);

    return 0;
}