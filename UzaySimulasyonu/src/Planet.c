#include "Planet.h"
#include <stdio.h>
#include <string.h>

#define MAX_PLANETS 10

int planet_count = 0;
Planet planets[MAX_PLANETS];

void load_planets(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) return;

    while (fscanf(file, "%[^#]#%d#%d#%d.%d.%d\n",
                  planets[planet_count].name,
                  (int*)&planets[planet_count].type,
                  &planets[planet_count].hours_in_day,
                  &planets[planet_count].current_time.day,
                  &planets[planet_count].current_time.month,
                  &planets[planet_count].current_time.year) == 6) {
        planets[planet_count].current_time.hour = 0;
        planet_count++;
    }

    fclose(file);
}

float get_aging_factor(PlanetType type) {
    switch (type) {
        case ROCKY: return 1.0f;
        case GAS_GIANT: return 0.1f;
        case ICE_GIANT: return 0.5f;
        case DWARF: return 0.01f;
        default: return 1.0f;
    }
}
