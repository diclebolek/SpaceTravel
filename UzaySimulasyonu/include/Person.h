// include/Person.h
#ifndef PERSON_H
#define PERSON_H

#define MAX_PERSONS 100 // Tanım burada olmalı

typedef struct {
    char name[50];
    int age;
    float remaining_life; // in hours
    char spacecraft_name[20];
    int alive; // 1: alive, 0: dead
} Person;

extern Person persons[MAX_PERSONS]; // Bildirim (bellek başka yerde ayrılıyor)
extern int person_count;          // Bildirim

void load_persons(const char* filename);
void update_persons();

#endif