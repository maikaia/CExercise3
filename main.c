#include <stdio.h>      // printf, FILE, fopen, fclose, fgets, fprintf
#include <string.h>     // strcmp, strncpy, strtok, strcspn
#include <ctype.h>      // isalpha, isdigit
#include <stdlib.h>     // atoi, qsort, bsearch, rand, srand
#include <time.h>       // time
#include "types.h"      // vehicle_t, person_t
#include <string.h>     // Windows (_stricmp)
#include "file.h"       // load/save registry

#ifdef _WIN32
    #define strcasecmp _stricmp
#endif

// Functions

//The menu shown to user
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

// Sanitize input string by removing unwanted characters
void sanitize_string(char *s) {
    char clean[SIZE];
    int j = 0;

    for (int i = 0; s[i] != '\0' && j < SIZE - 1; i++) {
        unsigned char c = s[i];

        // Skip control characters entirely (\n, \r, \t, etc.)
        if (iscntrl(c)) continue;

        // Skip backslashes (don't allow '\')
        if (c == '\\') continue;

        // Allow safe characters
        if (isalnum(c) || isspace(c) || c == '-' || c == '_' || c == '.' || c == ',') {
            clean[j++] = c;
        } else {
            // Replace all other symbols with '_'
            clean[j++] = '_';
        }
    }

    clean[j] = '\0';

    // Trim trailing whitespace
    int len = strlen(clean);
    while (len > 0 && isspace((unsigned char)clean[len - 1])) {
        clean[--len] = '\0';
    }

    strcpy(s, clean);
}

// Input string with prompt and sanitize
void input_string(const char *prompt, char *dest, size_t size) {
    printf("%s", prompt);
    if (fgets(dest, size, stdin)) {
        strtok(dest, "\n"); // remove newline
        sanitize_string(dest); // remove unwanted characters
    }
}

// Input string with prompt and ensure non-empty
void safe_input_string(const char *prompt, char *dest, size_t size){
    while(1){
        input_string(prompt, dest, size);
        if(strlen(dest) == 0){
            printf("Input cannot be empty, try again.\n");
        } else {
            break;
        }
    }
}

// Adds one vehicle to the registry
void add_vehicle(vehicle_t registry[], int *count)
{
    // Check if registry is full
    if(*count >= LIST_SIZE){
        printf("Registry is full\n");
    } else {
        char buffer[SIZE];
        int invalid = 0;

        do{
            printf("Enter vehicle details:\n");
            input_string("Enter brand: ", registry[*count].brand, SIZE);
            input_string("Enter type: ", registry[*count].type, SIZE);
            input_string("Enter license number: ", registry[*count].license_plate, SIZE);
            input_string("Enter owners name: ", registry[*count].owner.name, SIZE);

            printf("Enter owners age: ");
            fgets(buffer, SIZE, stdin);
            strtok(buffer, "\n");

            // Validate age input (should be a number between 18 and 100)
            if(!isdigit((unsigned char) buffer[0]) || atoi(buffer) < 18 || atoi(buffer) > 100){
                registry[*count].owner.age = 0;
                printf("Invalid age input. Age must be a number between 18 and 100.\n");
            } else {
                registry[*count].owner.age = atoi(buffer);
            }

            // Determine if any field is invalid (empty text fields or invalid age)
            invalid = (strlen(registry[*count].brand) == 0) ||
                      (strlen(registry[*count].type) == 0) ||
                      (strlen(registry[*count].license_plate) == 0) ||
                      (strlen(registry[*count].owner.name) == 0) ||
                      (registry[*count].owner.age == 0);

            // If invalid, inform the user and repeat the input process
            if (invalid) {
                printf("One or more inputs were invalid. All text fields must be non-empty and owner's age must be a number between 18 and 100.\n");
                printf("Please re-enter the details. The prompt will repeat until all fields are valid.\n");
            }
        } while (invalid);


        (*count)++;
        printf("Vehicle added!\n");

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

// Comparison function for qsort and bsearch
int compare_by_owner(const void *a, const void *b) {
    const vehicle_t *va = (const vehicle_t *)a;
    const vehicle_t *vb = (const vehicle_t *)b;
    return strcmp(va->owner.name, vb->owner.name);
}

// Sort the registry by owner name
void sort_registry(vehicle_t registry[], int count) {
    if (count <= 1) {
        printf("List is too small to sort\n");
        return;
    }

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (strcasecmp(registry[j].owner.name, registry[j+1].owner.name) > 0) {
                vehicle_t temp = registry[j];
                registry[j] = registry[j+1];
                registry[j+1] = temp;
            }
        }
    }

    printf("Registry sorted by owner!\n");
}

// Adds a random vehicle to the registry
void add_random_vehicle(vehicle_t registry[], int *count){
    if(*count >= LIST_SIZE){
        printf("Registry is full\n");
        return;
    }

    // Some example data to choose from
    const char *brand[] = {"BMW", "Audi", "Peugeot", "Kia", "Nissan", "Mercedes", "Toyota", "Ford", "Fiat", "Porsche"};
    const char *type[] = {"SUV", "Sedan", "Pickup truck", "Convertible", "Hatchback", "Coupe", "Minivan", "Crossover", "Luxury", "Limousine"};
    const char *name[] = {"Nils-Olov Olsson", "Samuel Grafstrom", "Carl Nordenadler", "Niklas Skold", "Edward Bergstrom", "Theodor Fahami", "Johannes Schoeneck", "Ingela Hedlund", "Jorgen Olsson", "Petra Olsson"};

    // Randomly generate a vehicle
    snprintf(registry[*count].brand, SIZE, "%s", brand[rand() % 10]);
    snprintf(registry[*count].type, SIZE, "%s", type[rand() % 10]);
    snprintf(registry[*count].license_plate, SIZE, "%c%c%c%03d", 'A' + (rand()%26), 'A' + (rand()%26), 'A' + (rand()%26), rand() % 1000);
    snprintf(registry[*count].owner.name, SIZE, "%s", name[rand() % 10]);
    registry[*count].owner.age = 18 + rand() % 63; // random age 18-80

    (*count)++;
    printf("Random vehicle added!\n");
    save_registry("registry.txt", registry, *count);
}

int binary_search_owner(vehicle_t registry[], int count, const char *query) {
    int left = 0, right = count - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        int cmp = strcasecmp(query, registry[mid].owner.name);

        if (cmp == 0) {
            return mid;     // found exact match
        } else if (cmp < 0) {
            right = mid - 1;    // search left
        } else {
            left = mid + 1;     // search right
        }
    }
    return -1; // not found
}

// Search for a vehicle by owner name
void search_owner(vehicle_t registry[], int count) {
    char query[SIZE];
    safe_input_string("Enter owner name to search: ", query, SIZE);

    // Ensure the list is sorted before searching
    sort_registry(registry, count); 

    int pos = binary_search_owner(registry, count, query);
    if (pos >= 0) {
        printf("%i. %s | %s | %s | %s | %i\n",
            pos+1,
            registry[pos].brand,
            registry[pos].type,
            registry[pos].license_plate,
            registry[pos].owner.name,
            registry[pos].owner.age
        );
    } else {
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
        printf("%i. %s | %s | %s | %s | %i \n", 
            i+1, 
            registry[i].brand, 
            registry[i].type, 
            registry[i].license_plate, 
            registry[i].owner.name, 
            registry[i].owner.age
        );
    }
}

// Handles user input and converts to int, returns -1 on invalid input
int handle_user_input()
{
    char buffer[SIZE];
    fgets(buffer, SIZE, stdin);
    if(isalpha((unsigned char) buffer[0])) 
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
        printf("Age: %i\n", registry[input-1].owner.age);
    } else {
        printf("Invalid input, try again\n");
    }
}

// Acts upon user input
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

// Main function
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