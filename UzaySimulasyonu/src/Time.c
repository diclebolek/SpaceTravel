#include "Time.h"
#include <stdio.h>

void increment_time(Time* time, int hours) {
    time->hour += hours;
    while (time->hour >= 24) {
        time->hour -= 24;
        time->day += 1;
        if (time->day > 30) {
            time->day = 1;
            time->month += 1;
            if (time->month > 12) {
                time->month = 1;
                time->year += 1;
            }
        }
    }
}

int compare_dates(Time t1, Time t2) {
    if (t1.year != t2.year)
        return t1.year - t2.year;
    if (t1.month != t2.month)
        return t1.month - t2.month;
    if (t1.day != t2.day)
        return t1.day - t2.day;
    return t1.hour - t2.hour;
}

void print_time(Time time) {
    printf("%02d.%02d.%04d %02d:00\n", time.day, time.month, time.year, time.hour);
}
