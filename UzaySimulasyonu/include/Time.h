#ifndef TIME_H
#define TIME_H

typedef struct {
    int hour;
    int day;
    int month;
    int year;
} Time;

void increment_time(Time *time, int hours);
int compare_dates(Time t1, Time t2);
void print_time(Time time);

#endif
