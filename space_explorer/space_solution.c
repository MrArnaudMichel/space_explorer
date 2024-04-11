#include <stdbool.h>
#include "space_explorer.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <float.h>
#define INF DBL_MAX

// Structure pour représenter un noeud (planète) dans le graphe
typedef struct {
    unsigned int id; // ID de la planète
    double distance; // Distance à partir du départ
    bool visited; // Indicateur si la planète a été visitée
    unsigned int prev_planet; // ID de la planète précédente dans le chemin optimal
    unsigned int* connections; // Tableau des IDs des planètes connectées
    int num_connections; // Nombre de planètes connectées
} Node;

// Fonction pour initialiser un noeud
Node* init_node(unsigned int id, unsigned int* connections, int num_connections) {
    Node* node = malloc(sizeof(Node));
    if (node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    node->id = id;
    node->distance = INF; // Initialiser la distance à l'infini
    node->visited = false;
    node->prev_planet = RAND_PLANET; // Initialiser la planète précédente à une planète aléatoire
    node->connections = connections;
    node->num_connections = num_connections;
    return node;
}

// Fonction pour libérer la mémoire allouée pour un noeud
void free_node(Node* node) {
    free(node);
}

// Fonction pour trouver l'index du noeud non visité avec la plus petite distance
int min_distance_node_index(Node** nodes, int num_nodes) {
    int min_index = -1;
    double min_distance = INF;
    for (int i = 0; i < num_nodes; i++) {
        if (!nodes[i]->visited && nodes[i]->distance < min_distance) {
            min_distance = nodes[i]->distance;
            min_index = i;
        }
    }
    return min_index;
}

// Fonction pour exécuter l'algorithme de Dijkstra
void dijkstra(Node** nodes, int num_nodes) {
    nodes[0]->distance = 0; // La distance de la planète de départ est mise à 0

    for (int count = 0; count < num_nodes - 1; count++) {
        int u = min_distance_node_index(nodes, num_nodes);
        if (u == -1) break; // Aucun nœud valide trouvé, sortir de la boucle
        nodes[u]->visited = true;

        // Mettre à jour les distances des planètes connectées à la planète sélectionnée
        for (int v = 0; v < nodes[u]->num_connections; v++) {
            unsigned int connection_id = nodes[u]->connections[v];
            for (int i = 0; i < num_nodes; i++) {
                if (nodes[i]->id == connection_id) {
                    double alt = nodes[u]->distance + 1; // Poids de l'arête est de 1 pour chaque saut
                    if (alt < nodes[i]->distance) {
                        nodes[i]->distance = alt;
                        nodes[i]->prev_planet = nodes[u]->id;
                    }
                    break;
                }
            }
        }
    }
}

// Fonction pour trouver le prochain noeud (planète) à visiter selon l'algorithme de Dijkstra
unsigned int find_next_planet(Node** nodes, int num_nodes, unsigned int current_planet) {
    for (int i = 0; i < num_nodes; i++) {
        if (nodes[i]->id == current_planet) {
            return nodes[i]->prev_planet;
        }
    }
    return RAND_PLANET; // Si aucun noeud n'a été trouvé, retourner une planète aléatoire
}

// Fonction principale pour effectuer le saut dans l'espace
ShipAction space_hop(unsigned int crt_planet, unsigned int* connections,
                     int num_connections,
                     double distance_from_mixer,
                     void* ship_state) {
    // Créer les noeuds à partir des données de connexion
    Node** nodes = malloc(num_connections * sizeof(Node*));
    if (nodes == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    for (int i = 0; i < num_connections; i++) {
        nodes[i] = init_node(connections[i], NULL, 0);
    }

    // Exécuter l'algorithme de Dijkstra
    dijkstra(nodes, num_connections);

    // Trouver le prochain noeud à visiter
    unsigned int next_planet_id = find_next_planet(nodes, num_connections, crt_planet);

    // Libérer la mémoire allouée pour les noeuds
    for (int i = 0; i < num_connections; i++) {
        free_node(nodes[i]);
    }
    free(nodes);

    // Créer et retourner l'action du saut dans l'espace
    ShipAction action;
    action.ship_state = ship_state;
    action.next_planet = next_planet_id;
    return action;
}
