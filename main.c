#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
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

// Removes one vehicle which user chooses
void remove_vehicle(vehicle_t registry[], int *count){
    // Check if registry is empty
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

    // Removes given position
    for (int i = input - 1; i < *count - 1; i++) {
        registry[i] = registry[i + 1];
    }

    (*count)--;
    printf("Vehicle at position %i is now removed\n", input);

    save_registry("registry.txt", registry, *count);
}

// Compares 
int compare_by_owner(const void *a, const void *b) {
    const vehicle_t *va = (const vehicle_t *)a;
    const vehicle_t *vb = (const vehicle_t *)b;
    return strcmp(va->owner.name, vb->owner.name);
}

// Sort the registry by owner name
void sort_registry(vehicle_t registry[], int count){
    if(count <= 1){
        printf("List is to small to sort\n");
        return;
    }

    qsort(registry, count, sizeof(vehicle_t), compare_by_owner);
    printf("Registry sorted by owner!\n");

    save_registry("registry.txt", registry, count);
}

void add_random_vehicle(vehicle_t registry[], int *count){
    if(*count >= LIST_SIZE){
        printf("Registry is full\n");
        return;
    }

    const char *brand[] = {"BMW", "Audi", "Peugeot", "Kia", "Nissan", "Mercedes", "Toyota", "Ford", "Fiat", "Porsche"};
    const char *type[] = {"SUV", "Sedan", "Pickup truck", "Convertible", "Hatchback", "Coupe", "Minivan", "Crossover", "Luxury", "Limousine"};
    const char *name[] = {"Nils-Olov Olsson", "Samuel Grafström", "Carl Nordenadler", "Niklas Sköld", "Edward Bergström", "Theodor Fahami", "Johannes Schoeneck", "Ingela Hedlund", "Jörgen Olsson", "Petra Olsson"};
    const char *letter[] = {"A", "G", "F", "E", "O", "T", "N", "I", "R"};

    snprintf(registry[*count].brand, SIZE, "%s", brand[rand() % 10]);
    snprintf(registry[*count].type, SIZE, "%s", type[rand() % 10]);
    snprintf(registry[*count].license_plate, SIZE, "%c%c%c%03d", 'A' + (rand()%26), 'A' + (rand()%26), 'A' + (rand()%26), rand() % 1000);
    snprintf(registry[*count].owner.name, SIZE, "%s", name[rand() % 10]);
    registry[*count].owner.age = 18 + rand() % 63; // random age 18-80

    (*count)++;
    printf("Random vehicle added!\n");
    save_registry("registry.txt", registry, *count);
}

void search_owner(vehicle_t registry[], int count){
    char query[SIZE];
    input_string("Enter owner name to search: ", query, SIZE);

    int found=0;
    for (int i = 0; i < count; i++){
        if(strcasecmp(registry[i].owner.name, query) == 0){
            printf("%i. %s | %s | %s | %s | %i\n",
                i+1,
                registry[i].brand,
                registry[i].type,
                registry[i].license_plate,
                registry[i].owner.name,
                registry[i].owner.age
            );
            found++;
        }
    }

    if(!found){
        printf("No vehicles found for owner '%s'\n", query);
    }
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
        printf("Age: %s\n", registry[input-1].owner.age);
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
        case 3: sort_registry(registry, *count); break;
        case 4: info(registry, *count); break;
        case 5: show_all(registry, *count); break;
        case 6: add_random_vehicle(registry, count); break;
        case 7: search_owner(registry, *count); break;
        case 0: printf("Exiting program!\n"); break;
        default: printf("Not a valid input, try using a number you see on the menu\n"); break;
    }
}

// Main

int main()
{
    vehicle_t registry[LIST_SIZE]; //storage of registry
    int input, count = 0;

    srand(time(NULL));

    load_registry("registry.txt", registry, &count);

    do{
        print_menu();
        input = handle_user_input();
        act_upon_input(input, registry, &count);
    } while(input !=0 );

    save_registry("registry.txt", registry, count);

    return 0;
}