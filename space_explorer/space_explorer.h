#ifndef __SPACE_EXPLORER_H
#define __SPACE_EXPLORER_H

typedef struct point {
    double x;
    double y;
} Point;

typedef struct planet {
    int planet_id;
    Point point;
    double distance_from_mixer;
    int has_mixer;
    struct planet **connections;
    int num_connections;
} Planet;

#define RAND_PLANET 111

typedef struct ship_action{
    unsigned int next_planet;
    void *ship_state;
} ShipAction;

ShipAction space_hop(unsigned int crt_planet,
                 unsigned int *connections,
                 int num_connections,
                 double distance_from_mixer,
                 void *ship_state);
#endif
