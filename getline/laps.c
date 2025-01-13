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

/**
 * race_state - tracks lap counts for each car
 * @id: current update of car IDs
 * @size: updated number of cars
 *
 * Description: This function maintains a static list of cars and
 * increments lap counts for each car in the update. If new cars are
 * detected, they are added to the list.
 * 
 * Return: void
 */
void race_state(int *id, size_t size)
{
    static int car_ids[10] = {0}; /* list of cars in race */
    static int laps[10] = {0};    /* lap counters for each car */
    static int count = 0;         /* current number of cars */
    int i, j, found;

    if (size == 0)
    {
        return;
    }

    for (i = 0; i < (int)size; i++)
    {
        found = 0;

        /* check if car already in race */
        for (j = 0; j < count; j++)
        {
            if (id[i] == car_ids[j]) /* increment lap count */
            {
                laps[j]++;
                found = 1;
                break;
                }
        }

        /* if car not found, add it */
        if (!found)
        {
            add_car(id[i], count, car_ids, laps);
            count++;
        }
    }

    /* print Race State */
    printf("Race state:\n");
    for (j = 0; j < count; j++)
    {
        printf("Car %d [%d laps]\n", car_ids[j], laps[j]);
    }
}

