#ifndef TYPES_H
#define TYPES_H

#define LIST_SIZE 10
#define SIZE 100   // for strings

struct Person {
    char name[SIZE];
    int age;
}; typedef struct Person person_t;

struct Vehicle {
    char type[SIZE];
    char brand[SIZE];
    char license_plate[SIZE];
    person_t owner;
}; typedef struct Vehicle vehicle_t;

#endif