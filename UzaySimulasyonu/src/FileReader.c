#include "../include/FileReader.h"
#include "../include/Person.h"
#include "../include/Planet.h"
#include "../include/Spacecraft.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 256

void read_persons(const char* filename) {
    char filepath[MAX_LINE_LENGTH];
    snprintf(filepath, sizeof(filepath), "data/%s", filename);
    FILE* file = fopen(filepath, "r");
    if (!file) {
        perror("Kisiler.txt açılamadı");
        return;
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        if (person_count < MAX_PERSONS) {
            if (sscanf(line, "%19[^#]#%d#%d#%19s",
                       persons[person_count].name,
                       &persons[person_count].age,
                       &persons[person_count].remaining_life,
                       persons[person_count].spacecraft_name) == 4) {
                persons[person_count].alive = 1;
                person_count++;
            } else {
                fprintf(stderr, "Hatalı kişi satırı formatı: %s\n", line);
            }
        }
    }
    fclose(file);
}

void read_planets(const char* filename) {
    char filepath[MAX_LINE_LENGTH];
    snprintf(filepath, sizeof(filepath), "data/%s", filename);
    FILE* file = fopen(filepath, "r");
    if (!file) {
        perror("Gezegenler.txt açılamadı");
        return;
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        if (planet_count < MAX_PLANETS) {
            int type_int;
            if (sscanf(line, "%19[^#]#%d#%d#%d.%d.%d",
                       planets[planet_count].name,
                       &type_int,
                       &planets[planet_count].hours_in_day,
                       &planets[planet_count].current_time.day,
                       &planets[planet_count].current_time.month,
                       &planets[planet_count].current_time.year) == 6) {
                planets[planet_count].type = (PlanetType)type_int;
                planets[planet_count].current_time.hour = 0; // Başlangıç saati 00:00
                planet_count++;
            } else {
                fprintf(stderr, "Hatalı gezegen satırı formatı: %s\n", line);
            }
        }
    }
    fclose(file);
}

void read_spacecrafts(const char* filename) {
    char filepath[MAX_LINE_LENGTH];
    snprintf(filepath, sizeof(filepath), "data/%s", filename);
    FILE* file = fopen(filepath, "r");
    if (!file) {
        perror("Araclar.txt açılamadı");
        return;
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        if (spacecraft_count < MAX_SPACECRAFTS) {
            if (sscanf(line, "%19[^#]#%19[^#]#%19[^#]#%d.%d.%d#%d",
                       spacecrafts[spacecraft_count].name,
                       spacecrafts[spacecraft_count].departure_planet,
                       spacecrafts[spacecraft_count].arrival_planet,
                       &spacecrafts[spacecraft_count].departure_time.day,
                       &spacecrafts[spacecraft_count].departure_time.month,
                       &spacecrafts[spacecraft_count].departure_time.year,
                       &spacecrafts[spacecraft_count].distance) == 7) {
                spacecrafts[spacecraft_count].departure_time.hour = 0;
                spacecrafts[spacecraft_count].remaining_time = spacecrafts[spacecraft_count].distance;
                spacecrafts[spacecraft_count].destroyed = 0;
                spacecraft_count++;
            } else {
                fprintf(stderr, "Hatalı araç satırı formatı: %s\n", line);
            }
        }
    }
    fclose(file);
}