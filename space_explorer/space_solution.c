#include <stdbool.h>

#include "space_explorer.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct ShipState {
	unsigned int* visited_planets;
	int num_visited_planets;
	double last_distance_from_mixer;
	unsigned int last_planet;
} ShipState;

ShipAction space_hop(unsigned int crt_planet, unsigned int* connections,
                     int num_connections,
                     double distance_from_mixer,
                     void* ship_state) {
	ShipState* state;
	if (ship_state == NULL) {
		state = malloc(sizeof(ShipState));
		state->visited_planets = malloc(sizeof(unsigned int));
		state->visited_planets[0] = crt_planet;
		state->num_visited_planets = 1;
	} else {
		state = (ShipState *) ship_state;
		state->num_visited_planets++;
		state->visited_planets = realloc(state->visited_planets, sizeof(unsigned int) * state->num_visited_planets);
		state->visited_planets[state->num_visited_planets - 1] = crt_planet;
	}
	ShipAction action;
	action.ship_state = state;
	if (distance_from_mixer > state->last_distance_from_mixer) {
		state->last_distance_from_mixer = distance_from_mixer;
		state->last_planet = crt_planet;
		action.next_planet = crt_planet;
		printf("Returning to planet %d\n", crt_planet);
	}
	else {
		action.next_planet = RAND_PLANET;
		printf("Exploring from planet %d\n", crt_planet);
	}

	return action;
}
