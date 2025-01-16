#include "laps.h"

// Head of LL
static Car *head = NULL;

// find a car by id
Car *find_car(int id) {
    Car *current = head;
    while (current != NULL) {
        if (current->id == id) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// add new car
void add_car(int id) {
    Car *new_car = (Car *)malloc(sizeof(Car));
    if (new_car == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    new_car->id = id;
    new_car->laps = 0;
    new_car->next = head;
    head = new_car;
    printf("Car %d joined the race\n", id);
}

void free_all_cars() {
    Car *current = head;
    Car *next_car;
    while (current != NULL) {
        next_car = current->next;
        free(current);
        current = next_car;
    }
    head = NULL;
}

// compare cars
int compare_cars(const void *a, const void *b) {
    Car *car_a = *(Car **)a;
    Car *car_b = *(Car **)b;
    return car_a->id - car_b->id;
}

// free cars if value is 0
void race_state(int *id, size_t size) {
    if (size == 0) {
        free_all_cars();
        return;
    }

    // Update new cars
    Car **new_cars = (Car **)malloc(size * sizeof(Car *));
    if (new_cars == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    size_t new_car_count = 0;

    // Condition for each car id
    for (size_t i = 0; i < size; ++i) {
        Car *car = find_car(id[i]);
        if (car == NULL) {
            add_car(id[i]);
            car = head;
            new_cars[new_car_count++] = car;
        }
        car->laps++;
    }

    // sorted array of cars by id
    Car *current = head;
    size_t car_count = 0;
    while (current != NULL) {
        car_count++;
        current = current->next;
    }

    Car **sorted_cars = (Car **)malloc(car_count * sizeof(Car *));
    if (sorted_cars == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    current = head;
    for (size_t i = 0; i < car_count; ++i) {
        sorted_cars[i] = current;
        current = current->next;
    }

    qsort(sorted_cars, car_count, sizeof(Car *), compare_cars);

    puts("Race state:\n");
    for (size_t i = 0; i < car_count; ++i) {
        printf("Car %d [%d laps]\n", sorted_cars[i]->id, sorted_cars[i]->laps);
    }

    // Free temp pointers
    free(new_cars);
    free(sorted_cars);
}
