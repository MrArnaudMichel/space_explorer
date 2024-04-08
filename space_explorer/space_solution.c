#include <stdbool.h>
#include "space_explorer.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct PlanetData {
    unsigned int planet_id;
    double distance_from_mixer;
    unsigned int* connections;
    int num_connections;
    bool visited;
} PlanetData;

typedef struct VisitedPlanets {
    PlanetData* planets;
    int number_planets_visited;
} VisitedPlanets;

typedef struct ShipState {
    VisitedPlanets* visitedPlanets;
} ShipState;

void add_planet(unsigned int crt_planet, unsigned int* connections,
                int num_connections,
                double distance_from_mixer,
                ShipState* state) {
    unsigned int index_planet = state->visitedPlanets->number_planets_visited;
    state->visitedPlanets->planets = realloc(state->visitedPlanets->planets,
                                             (index_planet + 1) * sizeof(PlanetData));
    state->visitedPlanets->planets[index_planet].planet_id = crt_planet;
    state->visitedPlanets->planets[index_planet].distance_from_mixer = distance_from_mixer;
    state->visitedPlanets->planets[index_planet].num_connections = num_connections;

    state->visitedPlanets->planets[index_planet].connections = malloc(num_connections * sizeof(unsigned int));
    memcpy(state->visitedPlanets->planets[index_planet].connections, connections,
           num_connections * sizeof(unsigned int));

    state->visitedPlanets->number_planets_visited++;
}

bool is_planet_visited(unsigned int planet_id, ShipState* state) {
    if (state == NULL) {
        return false;
    }

    for (int i = 0; i < state->visitedPlanets->number_planets_visited; i++) {
        if (state->visitedPlanets->planets[i].planet_id == planet_id) {
            return true;
        }
    }

    return false;
}

ShipAction space_hop(unsigned int crt_planet, unsigned int* connections,
                     int num_connections,
                     double distance_from_mixer,
                     void* ship_state) {
    ShipAction action;
    ShipState* state = ship_state;

    if (state == NULL) {
        state = (ShipState*)malloc(sizeof(ShipState));
        state->visitedPlanets = (VisitedPlanets*)malloc(sizeof(VisitedPlanets));
        state->visitedPlanets->number_planets_visited = 0;
        state->visitedPlanets->planets = malloc(sizeof(PlanetData));
        add_planet(crt_planet, connections, num_connections, distance_from_mixer, state);
    } else {
        add_planet(crt_planet, connections, num_connections, distance_from_mixer, state);
        // Crée un algorithme avec backtracking

    }

    action.ship_state = state;
    return action;
}

