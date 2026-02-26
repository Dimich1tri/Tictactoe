#ifndef __MINIMAX_H__
#define __MINIMAX_H__

#include "ArbolJuego.h"
#include <vector>

class Minimax {
private:
    ArbolJuego* arbol;

public:
    Minimax(ArbolJuego* ptrArbol);

    EstadoCasilla verificarGanador(const std::vector<std::vector<int>>& tablero);
    bool estaLleno(const std::vector<std::vector<int>>& tablero);
    int calcularHeuristica(EstadoJuego* estado);

    void expandirRecursivo(EstadoJuego* nodoActual, int profundidadActual);
    void evaluarRecursivo(EstadoJuego* nodoActual, int alpha = -1000000, int beta = 1000000);
    void expandirArbol();
    void evaluarDFS();
    void ejecutarMejorJugada();
};

#endif