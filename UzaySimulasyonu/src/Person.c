// src/Person.c
#include "Person.h"
#include "Planet.h"
#include "Spacecraft.h"
#include <stdio.h>
#include <string.h>

#define MAX_PERSONS 100
Person persons[MAX_PERSONS];
int person_count = 0;

void load_persons(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) return;

    while (fscanf(file, "%[^#]#%d#%d#%s\n", persons[person_count].name,
                  &persons[person_count].age,
                  &persons[person_count].remaining_life,
                  persons[person_count].spacecraft_name) == 4) {
        persons[person_count].alive = 1;
        person_count++;
    }

    fclose(file);
}

void update_persons() {
    for (int i = 0; i < person_count; i++) {
        if (persons[i].alive) {
            int on_planet = 0;
            char current_planet[20] = "";

            // Şu anda bir gezegende mi yoksa yolda mı kontrol et
            for (int j = 0; j < planet_count; j++) {
                for (int k = 0; k < spacecraft_count; k++) {
                    if (strcmp(persons[i].spacecraft_name, spacecrafts[k].name) == 0) {
                        if (spacecrafts[k].remaining_time == 0 && strcmp(spacecrafts[k].arrival_planet, planets[j].name) == 0) {
                            on_planet = 1;
                            strcpy(current_planet, planets[j].name);
                            break;
                        } else if (spacecrafts[k].remaining_time > 0) {
                            persons[i].remaining_life -= 1; // Yoldayken normal yaşlanma
                        }
                        break;
                    }
                }
                if (on_planet) break;
            }

            // Gezegendeyken yaşlanmayı uygula
            if (on_planet) {
                for (int j = 0; j < planet_count; j++) {
                    if (strcmp(current_planet, planets[j].name) == 0) {
                        switch (planets[j].type) {
                            case ROCKY:
                                persons[i].remaining_life -= 1;
                                break;
                            case GAS_GIANT:
                                persons[i].remaining_life -= 0.1;
                                break;
                            case ICE_GIANT:
                                persons[i].remaining_life -= 0.5;
                                break;
                            case DWARF:
                                persons[i].remaining_life -= 0.01;
                                break;
                            default:
                                persons[i].remaining_life -= 1;
                                break;
                        }
                        break;
                    }
                }
            }

            if (persons[i].remaining_life <= 0) {
                persons[i].alive = 0;
            }
        }
    }
}