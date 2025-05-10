#ifndef PLANET_H
#define PLANET_H

#include "Time.h"

typedef enum {
    ROCKY = 0,
    GAS_GIANT = 1,
    ICE_GIANT = 2,
    DWARF = 3
} PlanetType;

typedef struct {
    char name[20];
    PlanetType type;
    int hours_in_day;
    Time current_time;
    int population;
} Planet;

// Maksimum gezegen sayısı
#define MAX_PLANETS 10

// Dışarıdan erişim için extern bildirimi
extern int planet_count;
extern Planet planets[MAX_PLANETS];

// Fonksiyon prototipleri
void load_planets(const char* filename);
float get_aging_factor(PlanetType type);

#endif
