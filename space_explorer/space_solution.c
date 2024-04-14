//
// Created by arnaud on 21/03/24.
//

#include <stdbool.h>
#include "space_explorer.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <float.h>
#define INF DBL_MAX

typedef struct Node {
    unsigned int id;
    double distance;
    unsigned int* connections;
    int num_connections;
    struct Node* previous;
} Node;

typedef struct shipState {
    Node** nodes;
    int num_nodes;
    unsigned int previous_planet;
    bool search_other;
} ShipState;


bool is_visited(ShipState* state, unsigned int id) {
    for (int i = 0; i < state->num_nodes; i++) {
        if (state->nodes[i]->id == id) {
            return true;
        }
    }
    return false;
}

Node* get_node(ShipState* state, unsigned int id) {
    for (int i = 0; i < state->num_nodes; i++) {
        if (state->nodes[i]->id == id) {
            return state->nodes[i];
        }
    }
    return NULL;
}

Node* init_node(unsigned int id, double distance, unsigned int* connections, int num_connections) {
    Node* node = malloc(sizeof(Node));
    if (node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    node->id = id;
    node->distance = distance;
    node->connections = connections;
    node->num_connections = num_connections;
    return node;
}


ShipAction space_hop(unsigned int crt_planet,
                     unsigned int *connections,
                     int num_connections,
                     double distance_from_mixer,
                     void *ship_state_ptr) {
    ShipAction action;
    ShipState *state = (ShipState *) ship_state_ptr;
    action.ship_state = ship_state_ptr;

    if (state == NULL) {
        state = malloc(sizeof(ShipState));
        if (state == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(1);
        }
        state->num_nodes = 0;
        state->nodes = NULL;
        state->previous_planet = 0;
        state->search_other = false;
    }

    if (!is_visited(state, crt_planet)) {
        state->nodes = realloc(state->nodes, (state->num_nodes + 1) * sizeof(Node *));
        state->nodes[state->num_nodes] = init_node(crt_planet, distance_from_mixer, connections, num_connections);
        state->nodes[state->num_nodes]->previous = get_node(state, state->previous_planet);
        state->num_nodes++;

        if (state->search_other) {
            state->search_other = false;
            get_node(state, crt_planet)->previous = NULL;
        }

        if (state->nodes[state->num_nodes - 1]->previous != NULL) {
            if (state->nodes[state->num_nodes - 1]->distance > state->nodes[state->num_nodes - 1]->previous->distance) {
                for (int i = 0; i < state->nodes[state->num_nodes - 1]->previous->num_connections; i++) {
                    if (!is_visited(state, state->nodes[state->num_nodes - 1]->previous->connections[i])) {
                        action.next_planet = state->nodes[state->num_nodes - 1]->previous->connections[i];
                        state->previous_planet = state->nodes[state->num_nodes - 1]->previous->id;
                        action.ship_state = state;
                        return action;
                    }
                }
            }
        }
    } else if (state->search_other) {
        action.next_planet = RAND_PLANET;
        action.ship_state = state;
        return action;
    }

    for (int i = 0; i < num_connections; i++) {
        if (!is_visited(state, connections[i])) {
            state->previous_planet = crt_planet;
            action.next_planet = connections[i];
            action.ship_state = state;
            return action;
        }
    }

    // Graph not fully connected
    if (get_node(state, crt_planet)->previous == NULL) {
        action.next_planet = RAND_PLANET;
        state->search_other = true;
        action.ship_state = state;
        return action;
    }
    action.next_planet = get_node(state, crt_planet)->previous->id;
    action.ship_state = state;

    return action;
}