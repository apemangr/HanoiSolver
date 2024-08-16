#include "../include/Hanoi.hpp"


void hanoi(int n, int from_tower, int to_tower, int aux_tower, std::vector<std::pair<int, int>> &moves) {
    if (n == 1) {
        // Caso base: si solo hay un disco, moverlo directamente al destino
        moves.push_back({from_tower, to_tower});
        return;
    }

    // Mover n-1 discos de la torre origen a la torre auxiliar
    hanoi(n - 1, from_tower, aux_tower, to_tower, moves);

    // Mover el disco restante de la torre origen a la torre destino
    moves.push_back({from_tower, to_tower});

    // Mover los n-1 discos de la torre auxiliar a la torre destino
    hanoi(n - 1, aux_tower, to_tower, from_tower, moves);
}
