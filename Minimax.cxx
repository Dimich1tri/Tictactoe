#include "MiniMax.h"
#include <iostream>

Minimax::Minimax(ArbolJuego *ptrArbol) {
    this->arbol = ptrArbol;
}

bool Minimax::estaLleno(const std::vector<std::vector<int>> &tab) {
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (tab[i][j] == VACIO)
                return false;
        }
    }
    return true;
}

/******************************************************************************/
/*                                                                            */
/* int Minimax::calcularHeuristica(EstadoJuego* estado);                      */
/*                                                                            */
/* Purpose: Calcula el valor heurístico de un estado para la IA.              */
/* Asigna pesos a las líneas según la cantidad de fichas.                     */
/*                                                                            */
/* Parameters:                                                                */
/* estado - El estado del juego a evaluar.                                    */
/*                                                                            */
/* Returns: Valor entero que representa la ventaja del jugador.               */
/*                                                                            */
/* Plan:                                                                      */
/* Parte 1 : Configuración de pesos y definición de fichas (Max/Min).         */
/* Parte 2 : Conteo de fichas en filas, columnas y diagonales.                */
/* Parte 3 : Cálculo del índice heurístico basado en los arreglos de          */
/* pesos.                                                                     */
/* Parte 4 : Retorno ajustado según si es el turno de Max o Min.              */
/*                                                                            */
/******************************************************************************/
int Minimax::calcularHeuristica(EstadoJuego *estado) {

    /* Parte 1 --------------------------*/
    std::vector<std::vector<int>> tab = estado->obtenerTablero();
    int ind = 0;

    int w[4] = {1, 10, 100, 1000};

    bool esMax = estado->obtenerTurno();
    int ficha = esMax ? FICHA_MAX : FICHA_MIN;
    int fichaRival = esMax ? FICHA_MIN : FICHA_MAX;

    int fichasDiag1 = 0, rivalDiag1 = 0;
    int fichasDiag2 = 0, rivalDiag2 = 0;

    /* Parte 2 --------------------------*/
    for (int i = 0; i < 3; i++)
    {
        int fichasFila = 0, rivalFila = 0;
        int fichasCol = 0, rivalCol = 0;

        for (int j = 0; j < 3; j++)
        {
            fichasFila += (tab[i][j] == ficha);
            rivalFila += (tab[i][j] == fichaRival);

            fichasCol += (tab[j][i] == ficha);
            rivalCol += (tab[j][i] == fichaRival);
        }
        /* Parte 3 --------------------------*/
        ind += w[fichasFila] * !rivalFila;
        ind += w[fichasCol] * !rivalCol;

        fichasDiag1 += (tab[i][i] == ficha);
        rivalDiag1 += (tab[i][i] == fichaRival);

        fichasDiag2 += (tab[i][2 - i] == ficha);
        rivalDiag2 += (tab[i][2 - i] == fichaRival);
    }

    ind += w[fichasDiag1] * !rivalDiag1;
    ind += w[fichasDiag2] * !rivalDiag2;
    /* Parte 4 --------------------------*/

    return esMax ? ind : -ind;
}

void Minimax::expandirArbol() {
    if (!arbol->esVacio())
    {
        expandirRecursivo(arbol->obtenerRaiz(), 0);
    }
}

void Minimax::evaluarDFS() {
    if (!arbol->esVacio())
    {
        evaluarRecursivo(arbol->obtenerRaiz());
    }
}

/******************************************************************************/
/*                                                                            */
/* void Minimax::expandirRecursivo(EstadoJuego* nodoActual,                   */
/* int profundidadActual);                                                    */
/*                                                                            */
/* Purpose: Expande el arbol de juego de forma recursiva simulando            */
/* movimientos posibles.                                                      */
/*                                                                            */
/* Plan:                                                                      */
/* Parte 1 : Límite de profundidad.                                           */
/* Parte 2 : Determinación de la ficha a colocar según el turno.              */
/* Parte 3 : Iteración sobre casillas vacías para crear nodos hijos.          */
/*                                                                            */
/******************************************************************************/
void Minimax::expandirRecursivo(EstadoJuego *nodoActual, int profundidadActual) {
    /* Parte 1 --------------------------*/
    if (profundidadActual == 2)
        return;

    
    /* Parte 2 --------------------------*/
    std::vector<std::vector<int>> tableroActual = nodoActual->obtenerTablero();

    EstadoCasilla fichaAColocar = nodoActual->obtenerTurno() ? FICHA_MIN : FICHA_MAX;
    
    /* Parte 3 --------------------------*/
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (tableroActual[i][j] == VACIO)
            {
                std::vector<std::vector<int>> nuevoTablero = tableroActual;
                nuevoTablero[i][j] = fichaAColocar;

                EstadoJuego *hijo = new EstadoJuego(nuevoTablero, !nodoActual->obtenerTurno());
                nodoActual->adicionarDesc(hijo);

                expandirRecursivo(hijo, profundidadActual + 1);
            }
        }
    }
}


/******************************************************************************/
/*                                                                            */
/* void Minimax::evaluarRecursivo(EstadoJuego* nodoActual);                   */
/*                                                                            */
/* Purpose: Evalúa los nodos del árbol siguiendo el algoritmo Minimax.        */
/*                                                                            */
/* Plan:                                                                      */
/* Parte 1 : Caso base para nodos hoja.                                       */
/* Parte 2 : Backtracking del valor Minimax hacia el nodo actual.             */
/*                                                                            */
/******************************************************************************/
void Minimax::evaluarRecursivo(EstadoJuego *nodoActual) {
    /* Parte 1 --------------------------*/
    if (nodoActual->esHoja())
    {
        int h = calcularHeuristica(nodoActual);
        nodoActual->asignarHeuristica(h);
        return;
    }

    /* Parte 2 --------------------------*/
    int valorPropagado = hijos.front()->obtenerHeuristica();

    for (EstadoJuego *hijo : hijos)
    {
        evaluarRecursivo(hijo);
        int valorHijo = hijo->obtenerHeuristica();

        if (!nodoActual->obtenerTurno())
        {
            valorPropagado = (valorHijo > valorPropagado) ? valorHijo : valorPropagado;
        }
        else
        {
            valorPropagado = (valorHijo < valorPropagado) ? valorHijo : valorPropagado;
        }
    }

    nodoActual->asignarHeuristica(valorPropagado);
}

void Minimax::ejecutarMejorJugada() {
    EstadoJuego *raiz = arbol->obtenerRaiz();
    int mejorH = raiz->obtenerHeuristica();
    EstadoJuego *mejorJugada = nullptr;

    for (EstadoJuego *hijo : raiz->obtenerDesc())
    {
        if (hijo->obtenerHeuristica() == mejorH)
        {
            mejorJugada = hijo;
            break;
        }
    }

    if (mejorJugada != nullptr)
    {
        arbol->actualizarRaiz(mejorJugada);
    }
}
