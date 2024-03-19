#include <stdbool.h>

#include "space_explorer.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct {
	unsigned int planet;
	unsigned int* connections;
	int num_connections;
	double distance_from_mixer;
	bool visited;
	bool blocked;
} SpaceHopState;

typedef struct {
	SpaceHopState* path;
	int path_length;
} ShipState;

void add_planet_to_path(ShipState* state, unsigned int crt_planet, unsigned int* connections, int num_connections, double distance_from_mixer) {
    state->path = realloc(state->path, (state->path_length + 1) * sizeof(SpaceHopState));
    state->path[state->path_length].planet = crt_planet;
    state->path[state->path_length].connections = malloc(sizeof(unsigned int) * num_connections);
    memcpy(state->path[state->path_length].connections, connections, sizeof(unsigned int) * num_connections);
    state->path[state->path_length].num_connections = num_connections;
    state->path[state->path_length].distance_from_mixer = distance_from_mixer;
    state->path[state->path_length].visited = false;
    state->path[state->path_length].blocked = false;
    state->path_length++;
}

ShipAction space_hop(unsigned int crt_planet, unsigned int* connections,
                     int num_connections,
                     double distance_from_mixer,
                     void* ship_state) {
	ShipAction action;
	ShipState* state = ship_state;
	if (state == NULL) {
		state = malloc(sizeof(ship_state));
		state->path = malloc(sizeof(SpaceHopState));
		state->path_length = 0;
		state->path[state->path_length - 1].distance_from_mixer = RAND_MAX;
	}
	bool blocked = distance_from_mixer - state->path[state->path_length - 1].distance_from_mixer > 0;
	printf("Past distance %f Actual %f result %f\n", state->path[state->path_length - 1].distance_from_mixer, distance_from_mixer, distance_from_mixer - state->path[state->path_length - 1].distance_from_mixer);
	bool visited = false;
	unsigned int next_planet = RAND_PLANET;
	for (int i = 0; i < num_connections; i++) {
		if (blocked) {
			next_planet = state->path[state->path_length - 1].planet;
			printf("Blocked\n");
			break;
		}
		for (int j = 0; j < state->path_length; ++j) {
			if (connections[i] == state->path[j].planet) {
				visited = true;
				break;
			}
		}
		if (!visited) {
			next_planet = connections[i];
			break;
		}
	}

	add_planet_to_path(state, next_planet, connections, num_connections, distance_from_mixer);
	action.ship_state = state;
	action.next_planet = next_planet;

	return action;
}
