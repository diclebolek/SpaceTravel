#include "../include/Simulation.h"
#include "../include/display.h"
#include "Time.h"
#include "Person.h"
#include "Spacecraft.h"
#include "Planet.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void run_simulation() {
    int simulation_hours = 0;
    int all_arrived = 0;

    while (!all_arrived) {
        display_simulation_state();        
        for (int i = 0; i < planet_count; i++) {
            increment_time(&planets[i].current_time, 1);
        }

        // Uzay araçlarını güncelle
        update_spacecrafts();

        // Kişileri güncelle (yaşlanma ve ölüm)
        update_persons();

        // Nüfusu güncelle ve araçları imha et
        for (int i = 0; i < planet_count; i++) {
            planets[i].population = 0; // Her adımda sıfırla
            for (int j = 0; j < person_count; j++) {
                if (persons[j].alive) {
                    for (int k = 0; k < spacecraft_count; k++) {
                        if (strcmp(persons[j].spacecraft_name, spacecrafts[k].name) == 0 && spacecrafts[k].remaining_time == 0 && strcmp(spacecrafts[k].arrival_planet, planets[i].name) == 0) {
                            planets[i].population++;
                            break;
                        }
                    }
                }
            }
        }
        for (int i = 0; i < spacecraft_count; i++) {
            if (!spacecrafts[i].destroyed) {
                int alive_passengers = 0;
                for (int j = 0; j < person_count; j++) {
                    if (persons[j].alive && strcmp(persons[j].spacecraft_name, spacecrafts[i].name) == 0) {
                        alive_passengers++;
                    }
                }
                if (alive_passengers == 0 && spacecrafts[i].remaining_time == 0) {
                    spacecrafts[i].destroyed = 1;
                }
            }
        }

        // Tüm araçlar vardı mı ve imha olmadı mı kontrol et
        all_arrived = 1;
        for (int i = 0; i < spacecraft_count; i++) {
            if (!spacecrafts[i].destroyed && spacecrafts[i].remaining_time > 0) {
                all_arrived = 0;
                break;
            }
        }

        simulation_hours++;
    }
}