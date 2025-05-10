#include "Spacecraft.h"
#include "Time.h" // Time struct'ını kullanmak için
#include "Planet.h"
#include <stdio.h>
#include <string.h>
Spacecraft spacecrafts[MAX_SPACECRAFTS];  // Dizi burada bellekte oluşturuluyor.
int spacecraft_count = 0;  // Burada dizinin uzunluğunu sayan değişkeni tanımlıyoruz

void load_spacecrafts(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) return;

    while (fscanf(file, "%[^#]#%[^#]#%[^#]#%d.%d.%d#%d\n",
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
        // Başlangıçta varış zamanı tanımsız olabilir
        spacecrafts[spacecraft_count].arrival_time.day = 0;
        spacecrafts[spacecraft_count].arrival_time.month = 0;
        spacecrafts[spacecraft_count].arrival_time.year = 0;
        spacecrafts[spacecraft_count].arrival_time.hour = 0;
        spacecraft_count++;
    }

    fclose(file);
}

void update_spacecrafts() {
    for (int i = 0; i < spacecraft_count; i++) {
        if (!spacecrafts[i].destroyed) {
            // Kalkış kontrolü
            int departure_comparison = -1; // Henüz kalkmadı
            for (int p = 0; p < planet_count; p++) {
                if (strcmp(spacecrafts[i].departure_planet, planets[p].name) == 0) {
                    departure_comparison = compare_dates(planets[p].current_time, spacecrafts[i].departure_time);
                    break;
                }
            }

            if (departure_comparison >= 0 && spacecrafts[i].remaining_time > 0) {
                spacecrafts[i].remaining_time -= 1;
                if (spacecrafts[i].remaining_time <= 0) {
                    spacecrafts[i].remaining_time = 0;
                    // Hedefe varış zamanını hesapla
                    for (int p = 0; p < planet_count; p++) {
                        if (strcmp(spacecrafts[i].departure_planet, planets[p].name) == 0) {
                            spacecrafts[i].arrival_time = spacecrafts[i].departure_time;
                            spacecrafts[i].arrival_time.hour = planets[p].current_time.hour;
                            for (int h = 0; h < spacecrafts[i].distance; h++) {
                                increment_time(&spacecrafts[i].arrival_time, 1);
                            }
                            break;
                        }
                    }
                }
            }
        }
    }
}
