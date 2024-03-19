#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "space_explorer.h"

#define DIST_THRESHOLD  1

#ifndef srand48
#define srand48(X) (srand(X))
#endif
#ifndef drand48
#define drand48() (rand()*((double)1/RAND_MAX))
#endif

/**
 * From https://preshing.com/20121224/how-to-generate-a-sequence-of-unique-random-integers/
 */
unsigned int permuteQPR(unsigned int x)
{
    static const unsigned int prime = 4294967291u;
    if (x >= prime)
        return x;  // The 5 integers out of range are mapped to themselves.
    unsigned int residue = ((unsigned long long) x * x) % prime;
    return (x <= prime / 2) ? residue : prime - residue;
}

unsigned int seedPRNG(unsigned int seed){
    return permuteQPR(permuteQPR(seed) + 0x46790905);
}

unsigned int gen_planet_id(unsigned int id, unsigned int intOffset){
    unsigned int planet_id = RAND_PLANET;
    while (planet_id == RAND_PLANET){
        planet_id = permuteQPR((permuteQPR(id) + intOffset) ^ 0x5bf03635);
    }
    return planet_id;
}

double get_distance(Point a, Point b){
    int val = (b.x-a.x)*(b.x-a.x)+(b.y-a.y)*(b.y-a.y);
    return sqrt(val);
}

/**
 * Generates the planets based on the points
 */
Planet *points_to_planets(Point *points, int num_points){
    int i,j;
    Planet *planets = malloc(num_points*sizeof(Planet));
    Planet *connections[num_points];
    int prng_seed = seedPRNG(1);

    // Create the planets
    for (i=0;i<num_points-1;i++){
        planets[i].planet_id = gen_planet_id(i, prng_seed);
        planets[i].point = points[i];
        planets[i].num_connections = 0;
        planets[i].has_mixer = 0;
    }

    // Create the connections
    for (i=0;i<num_points;i++){
        for (j=0;j<num_points;j++){
            if (j == i) continue;
            double dist = get_distance(points[i], points[j]);
            if (dist < DIST_THRESHOLD){
                connections[planets[i].num_connections++] = &planets[j];
            }
        }
        // Copy the connections to the planet
        planets[i].connections = malloc(sizeof(Planet*)*planets[i].num_connections);
        memcpy(planets[i].connections,
                connections,
                sizeof(Planet*)*planets[i].num_connections);
    }

    return planets;
}

Planet *find_by_id(Planet *planets, int num_planets, int id){
    for (int i=0;i<num_planets;i++){
        if (planets[i].planet_id == id) return &planets[i];
    }
    return NULL;
}

int check_candidate(double distance, double max_distance){
    if (distance > max_distance*0.6 && distance < max_distance*0.8) return 1;
    return 0;
}

/**
 * Selects the start planet and the treasure planet.
 */
void select_start_and_treasure(Planet *planets, int num_planets, Planet **start, Planet **treasure){
    double max_distance = 0;
    int i,j;

    for (i=0;i<num_planets;i++){
        for (j=i+1;j<num_planets;j++){
            double dist = get_distance(planets[i].point, planets[j].point);
            if (dist > max_distance) max_distance = dist;
        }
    }

    printf("Max distance is %0.2f\n", max_distance);
    // Select a start node
    *start = &planets[random()%num_planets];

    // Find candidate treasure planets
    Planet *candidates[num_planets];
    int num_candidates = 0;
    for (i=0;i<num_planets;i++){
        double dist = get_distance((*start)->point, planets[i].point);
        if (check_candidate(dist, max_distance)){
            candidates[num_candidates++] = &planets[i];
        }

    }

    // Select randomly from the candidates
    *treasure = candidates[random()%num_candidates];
    (*treasure)->has_mixer = 1;
}

Point* generate_poisson_points(double density, double xlim[2], double ylim[2],
                               int *num_points)
{
    double grid_size = 1.0;
    int num_cells_x = (int)ceil((xlim[1] - xlim[0]) / grid_size);
    int num_cells_y = (int)ceil((ylim[1] - ylim[0]) / grid_size);

    *num_points = 0;
    for (int i = 0; i < num_cells_x; i++) {
        for (int j = 0; j < num_cells_y; j++) {
            double expected_num_points = density * grid_size * grid_size;
            int num_points_in_cell = (int)round(expected_num_points + sqrt(expected_num_points) * (drand48() * 2 - 1));
            *num_points += num_points_in_cell;
        }
    }

    Point* points = (Point*)malloc(*num_points * sizeof(Point));
    if (points == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    int k = 0;
    for (int i = 0; i < num_cells_x; i++) {
        for (int j = 0; j < num_cells_y; j++) {
            double x_base = i * grid_size;
            double y_base = j * grid_size;
            double expected_num_points = density * grid_size * grid_size;
            int num_points_in_cell = (int)round(expected_num_points + sqrt(expected_num_points) * (drand48() * 2 - 1));
            for (int l = 0; l < num_points_in_cell; l++) {
                double x = x_base + drand48() * grid_size;
                double y = y_base + drand48() * grid_size;
                if (x <= xlim[1] && y <= ylim[1]) {
                    points[k].x = x;
                    points[k].y = y;
                    k++;
                }
                if (k == *num_points) {
                    return points;
                }
            }
        }
    }

    return points;
}

int main(int argc, char *argv[]) {
    // Define parameters
    double density = 3;  // Adjust density as needed
    double xlim[2] = {0, 10};  // X-axis limits
    double ylim[2] = {0, 10};  // Y-axis limits
    int num_points;

    // Seed for PRNG
    long int seed;
    if (argc > 1) {
        seed = strtol(argv[1], NULL, 10);
    } else {
        seed = 12;  // Default seed if not provided
    }
    srand48(seed);

    // Generate Poisson points
    Point* points = generate_poisson_points(density, xlim, ylim, &num_points);
    printf("Generated universe\n");

    // Convert to planets
    Planet *planets = points_to_planets(points, num_points);
    // Select the start and treasure
    Planet *start, *treasure;
    select_start_and_treasure(planets, num_points, &start, &treasure);
    printf("Selected start point\n");
    // Run the game
    void *ship_state = NULL;
    int num_hops = 0;  // limit number of steps to number of planets
    Planet *crt = start;
    int found_treasure = 0;
    while (num_hops < num_points){
        num_hops++;
        unsigned int crt_id = crt->planet_id;
        unsigned int *connections;
        connections = malloc(sizeof(unsigned int)*crt->num_connections);
        for (int i=0;i<crt->num_connections;i++){
            connections[i] = crt->connections[i]->planet_id;
        }
        double crt_dist = get_distance(crt->point, treasure->point);
        ShipAction next_action = space_hop(crt_id,
                                        connections,
                                        crt->num_connections,
                                        crt_dist,
                                        ship_state);
        ship_state = next_action.ship_state;
        unsigned int next_planet = next_action.next_planet;
        free(connections);
        // Find next planet
        if (next_planet == RAND_PLANET){
            crt = &planets[random()%num_points];
        }else{
            // Look first in the connections of the current
            int found = 0;
            for (int i=0;i<crt->num_connections;i++){
                if (crt->connections[i]->planet_id == next_planet){
                    crt = crt->connections[i];
                    found = 1;
                    break;
                }
            }
            if (!found){
                // Look at all the planets
                Planet *next = find_by_id(planets, num_points, next_planet);
                if (next != NULL){
                    crt = next;
                }
            }
        }
        if (crt->has_mixer){
            found_treasure = 1;
            break;
        }
    }

    if (found_treasure){
        printf("Congratulations you found it in %d hops!\n", num_hops);
    }else{
        printf("The hyper-engine dies, you're lost in space. Ghost riders in the sky...\n");
    }

    // Free allocated memory
    for (int i=0;i<num_points;i++){
        free(planets[i].connections);
    }
    free(planets);
    free(points);

    return num_hops;
}
