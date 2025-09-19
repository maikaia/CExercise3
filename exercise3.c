#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define SIZE 100

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

int handle_user_input()
{
    char buffer[SIZE];
    int temp;
    scanf("%s\n", buffer);
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
        case 1: printf("Add vehicle\n"); 
        break;
        case 2: printf("Remove vehicle\n");
        break;
        case 3: printf("Sort\n");
        break;
        case 4: printf("Info\n");
        break;
        case 5: printf("Show all\n");
        break;
        case 6: printf("Add random\n");
        break;
        case 7: printf("Searh\n");
        break;
        case 0: printf("Exiting program!\n");
        break;
    }
}

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