#ifndef LAPS_H
#define LAPS_H
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void race_state(int *id, size_t size);
void add_car(int id, int current_count, int *car_ids, int *laps);

#endif