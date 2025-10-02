#ifndef FILE_H
#define FILE_H

#include "types.h"

// function prototypes
int load_registry(const char *filename, vehicle_t registry[], int *count);
int save_registry(const char *filename, const vehicle_t registry[], int count);

#endif
