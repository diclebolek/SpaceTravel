#include "include/FileReader.h"
#include "include/Simulation.h"
#include "include/Person.h"
#include "include/Planet.h"
#include "include/Spacecraft.h"
#include "include/Time.h"
#include "include/display.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void display_simulation_state() {
    //system("cls");
    printf("Gezegenler:\n");

    // Gezegen adlarını formatlayıp yanyana yazdır
    for (int i = 0; i < planet_count; i++) {
        printf("%-12s", planets[i].name);
    }
    printf("\n");

    // Ayraçları yazdır
    for (int i = 0; i < planet_count; i++) {
        printf("------------");
    }
    printf("\n");

    // Tarih başlığını yazdır
    printf("%-12s", "Tarih");
    printf("\n");

    // Gerçek tarihleri hizalı şekilde yazdır
    printf("%-12s", ""); // Boşluk bırakıyoruz başlık hizası için
    for (int i = 0; i < planet_count; i++) {
        printf("%02d.%02d.%04d%-4s",
               planets[i].current_time.day,
               planets[i].current_time.month,
               planets[i].current_time.year,
               ""); // Sağa yaslama için boşluk
    }
    printf("\n");

    // Nüfus başlığını ve değerlerini hizalı şekilde yazdır
    printf("%-12s", "Nufus");
    printf("\n");
    for (int i = 0; i < planet_count; i++) {
        printf("%17d", planets[i].population);
    }
    printf("\n\n");

    printf("Uzay Araclari:\n");
    printf("%-10s %-10s %-10s %-20s %-15s %-15s\n",
           "Arac Adi", "Durum", "Cikis", "Varis", "Kalan Sure", "Varis Tarihi");
    for (int i = 0; i < spacecraft_count; i++) {
        char status[20];

        if (spacecrafts[i].destroyed) {
            strcpy(status, "IMHA");
            printf("%-10s %-10s %-10s %-20s %-15s --\n",
                   spacecrafts[i].name,
                   status,
                   spacecrafts[i].departure_planet,
                   spacecrafts[i].arrival_planet,
                   "--");
        } else if (spacecrafts[i].remaining_time > 0) {
            int departure_comparison = -1;
            for (int p = 0; p < planet_count; p++) {
                if (strcmp(spacecrafts[i].departure_planet, planets[p].name) == 0) {
                    departure_comparison = compare_dates(planets[p].current_time, spacecrafts[i].departure_time);
                    break;
                }
            }
            if (departure_comparison < 0) {
                strcpy(status, "Bekliyor");
            } else {
                strcpy(status, "Yolda");
            }
            printf("%-10s %-10s %-10s %-20s %-15d %02d.%02d.%04d\n",
                   spacecrafts[i].name,
                   status,
                   spacecrafts[i].departure_planet,
                   spacecrafts[i].arrival_planet,
                   spacecrafts[i].remaining_time,
                   spacecrafts[i].arrival_time.day,
                   spacecrafts[i].arrival_time.month,
                   spacecrafts[i].arrival_time.year);
        } else {
            strcpy(status, "Vardı");
            printf("%-10s %-10s %-10s %-20s %-15d %02d.%02d.%04d\n",
                   spacecrafts[i].name,
                   status,
                   spacecrafts[i].departure_planet,
                   spacecrafts[i].arrival_planet,
                   spacecrafts[i].remaining_time,
                   spacecrafts[i].arrival_time.day,
                   spacecrafts[i].arrival_time.month,
                   spacecrafts[i].arrival_time.year);
        }
    }
}
int main() {
    read_persons("Kisiler.txt");
    read_planets("Gezegenler.txt");
    read_spacecrafts("Araclar.txt");

    printf("Simulasyon Basliyor...\n");
    run_simulation();
    printf("Simulasyon Tamamlandıi!\n\n");
    display_simulation_state(); // display.c'deki fonksiyon çağrılıyor

    return 0;
}