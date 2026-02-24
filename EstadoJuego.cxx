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

std::pair<bool,std::string> EstadoJuego::revisarFinPartida() {
    int columnaN = 0;
    int filaN = 0;
    std::pair<int, int> diagonal = {0,0};
    std::pair<bool,std::string> res;

    diagonal.first = tablero[0][0] + tablero[1][1] + tablero[2][2];
    diagonal.second = tablero[0][2] + tablero[1][1] + tablero[2][0];

    bool d1 = diagonal.first == VICTORIA || diagonal.second == VICTORIA;
    bool d2 = diagonal.first == DERROTA || diagonal.second == DERROTA;
    bool empate = false;

    for (int i = 0; i < 3; ++i) {

        columnaN = tablero[i][0] + tablero[i][1] + tablero[i][2];
        
        filaN = tablero[0][i] + tablero[1][i] + tablero[2][i];

        if (columnaN == VICTORIA || filaN == VICTORIA || d1) {
            return res = {true, " \033[1;31m Jugador X Gano\033[0m "};
        }else if (columnaN == DERROTA || filaN == DERROTA || d2) {
            return res = {true," \033[1;34mJugador O Gano\033[0m "};
        }
    }

    // Empate
    int casillaUsada = 0;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (std::abs(tablero[i][j])) {
                casillaUsada++;
            }
        }
    }

    if(casillaUsada == 9){
        return res = {true," \033[1;34mEmpate\033[0m "};
    } 

    return res = {false, ""};
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
