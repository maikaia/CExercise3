#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"

// remove newline helper
static void strip_newline(char *s) {
    s[strcspn(s, "\n")] = '\0';
}

int load_registry(const char *filename, vehicle_t registry[], int *count) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        *count = 0; // no file → empty registry
        return 0;
    }

    char buf[SIZE];
    if (!fgets(buf, sizeof(buf), f)) {
        fclose(f);
        *count = 0;
        return 0;
    }

    *count = atoi(buf); // first line = count
    if (*count > LIST_SIZE) *count = LIST_SIZE;

    for (int i = 0; i < *count; i++) {
        if (!fgets(buf, sizeof(buf), f)) break;
        strip_newline(buf);

        // split line by '|'
        char *brand = strtok(buf, "|");
        char *type = strtok(NULL, "|");
        char *plate = strtok(NULL, "|");
        char *owner = strtok(NULL, "|");
        char *age_s = strtok(NULL, "|");

        if (brand && type && plate && owner && age_s) {
            strncpy(registry[i].brand, brand, SIZE-1);
            strncpy(registry[i].type, type, SIZE-1);
            strncpy(registry[i].license_plate, plate, SIZE-1);
            strncpy(registry[i].owner.name, owner, SIZE-1);
            registry[i].owner.age = atoi(age_s);
        }
    }

    fclose(f);
    return 0;
}

int save_registry(const char *filename, const vehicle_t registry[], int count) {
    FILE *f = fopen(filename, "w");
    if (!f) return -1;

    fprintf(f, "%d\n", count);
    for (int i = 0; i < count; i++) {
        fprintf(f, "%s|%s|%s|%s|%d\n",
            registry[i].brand,
            registry[i].type,
            registry[i].license_plate,
            registry[i].owner.name,
            registry[i].owner.age
        );
    }

    fclose(f);
    return 0;
}
