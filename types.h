#ifndef TYPES_H
#define TYPES_H

#define LIST_SIZE 10
#define SIZE 100   // for strings

typedef struct {
    char name[SIZE];
    int age;
} person_t;

typedef struct {
    char type[SIZE];
    char brand[SIZE];
    char license_plate[SIZE];
    person_t owner;
} vehicle_t;

#endif