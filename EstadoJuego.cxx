#include "EstadoJuego.h"
#include <iostream>

EstadoJuego::EstadoJuego(bool iniciaMax) {
    tablero = std::vector<std::vector<int>>(3, std::vector<int>(3, VACIO));
    heuristica = 0;
    esMax = iniciaMax;
}

EstadoJuego::EstadoJuego(std::vector<std::vector<int>> nuevoTablero, bool turnoMax, int valorHeuristico) {
    tablero = nuevoTablero;
    esMax = turnoMax;
    heuristica = valorHeuristico;
}

EstadoJuego::~EstadoJuego() {
    limpiarLista();
}

void EstadoJuego::limpiarLista() {
    std::list<EstadoJuego*>::iterator it;
    for (it = this->desc.begin(); it != this->desc.end(); ++it) {
        delete *it;
    }
    this->desc.clear();
}

EstadoCasilla EstadoJuego::obtenerCasilla(int fila, int col) const {
    return static_cast<EstadoCasilla>(tablero[fila][col]);
}

void EstadoJuego::asignarCasilla(int fila, int col, EstadoCasilla ficha) {
    tablero[fila][col] = ficha;
}

std::vector<std::vector<int>> EstadoJuego::obtenerTablero() const { 
    return tablero; 
}

int EstadoJuego::obtenerHeuristica() const {
     return heuristica; 
}

void EstadoJuego::asignarHeuristica(int h) {
     heuristica = h; 
}

bool EstadoJuego::obtenerTurno() const {
     return esMax; 
}
    
void EstadoJuego::asignarTurno(bool turnoMax) {
     esMax = turnoMax; 
}

void EstadoJuego::adicionarDesc(EstadoJuego* nval) {
    this->desc.push_back(nval);
}

std::list<EstadoJuego*>& EstadoJuego::obtenerDesc() {
    return this->desc;
}

bool EstadoJuego::esHoja() const {
    return this->desc.empty();
}
