#include "laps.h"
#include <stdio.h>

/**
 * add_car - inserts new car in ascending order of IDs
 * @id:             ID of new car
 * @current_count:  number of cars currently in race
 * @car_ids:        pointer to car ID
 * @laps:           pointer to lap counts array
 *
 * Description: This function ensures the car list remains sorted
 * when adding a new car (with 0 initial laps).
 */
void add_car(int id, int current_count, int *car_ids, int *laps)
{
    int i;

    printf("Car %d joined the race\n", id);

    /* find insertion point */
    for (i = current_count; i > 0 && car_ids[i - 1] > id; i--)
    {
        car_ids[i] = car_ids[i - 1]; /* shift car IDs */
        laps[i] = laps[i - 1];       /* shift lap counts */
    }

    car_ids[i] = id;  /* insert new car */
    laps[i] = 0; /* new car starts with 0 laps */
}
