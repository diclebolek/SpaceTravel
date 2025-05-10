#ifndef SPACECRAFT_H
#define SPACECRAFT_H

#include "Time.h"

#define MAX_SPACECRAFTS 50

typedef struct {
    char name[20];
    char departure_planet[20];
    char arrival_planet[20];
    Time departure_time;
    int distance;         // in hours
    int remaining_time;   // in hours
    int destroyed;        // 1: destroyed, 0: active
    Time arrival_time;    // Hedefe varış tarihi için yeni alan
} Spacecraft;

extern Spacecraft spacecrafts[MAX_SPACECRAFTS];
extern int spacecraft_count;

void load_spacecrafts(const char* filename);
void update_spacecrafts();

#endif