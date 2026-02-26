#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include "EstadoJuego.h"
#include "MiniMax.h"
#include "ArbolJuego.h"

/*g++ main.cpp EstadoJuego.cxx ArbolJuego.cxx Minimax.cxx -o tictactoe*/

using namespace std;

enum gameFSM {
    TURNO_HUMANO,
    TURNO_IA_MAX,
    TURNO_IA_MIN,
    FIN_PARTIDA
};

void imprimirTablero(const vector<vector<int>>& tab) {
    cout << "\033[2J\033[1;1H";
    cout << "\n    0   1   2\n";
    for (int i = 0; i < 3; i++) {
        cout << i << " ";
        for (int j = 0; j < 3; j++) {
            if (tab[i][j] == FICHA_MAX)
                cout << " \033[1;31mX\033[0m ";
            else if (tab[i][j] == FICHA_MIN)
                cout << " \033[1;34mO\033[0m ";
            else
                cout << " . ";

            if (j < 2) cout << "|";
        }
        cout << "\n";
        if (i < 2) cout << "   ---+---+---\n";
    }
}

int main() {

    ArbolJuego arbol(new EstadoJuego(true));
    Minimax ia(&arbol);

    bool jugadorIA;
    cout << "Elegir tipo de jugador \n\t0.Manual\n\t1.Automatico" << endl;
    cin >> jugadorIA;

    gameFSM estadoActual = jugadorIA ? TURNO_IA_MAX : TURNO_HUMANO;

    while (estadoActual != FIN_PARTIDA) {
        EstadoJuego* raizActual = arbol.obtenerRaiz();
        imprimirTablero(raizActual->obtenerTablero());

        switch (estadoActual) {
        case TURNO_HUMANO: {
            int f, c;
            cout << "Tu turno (Fila Columna): ";
            cin >> f >> c;

            if (f >= 0 && f <= 2 && c >= 0 && c <= 2 && raizActual->obtenerCasilla(f, c) == VACIO) {
                vector<vector<int>> nuevoTablero = raizActual->obtenerTablero();
                nuevoTablero[f][c] = FICHA_MAX;

                EstadoJuego* nuevoEstado = new EstadoJuego(nuevoTablero, true);
                arbol.actualizarRaiz(nuevoEstado);

                estadoActual = TURNO_IA_MIN;
            }
            else {
                cout << "Movimiento invalido.\n";
            }
            break;
        }

        case TURNO_IA_MAX: {
            ia.expandirArbol();
            ia.evaluarDFS();
            ia.ejecutarMejorJugada();
            imprimirTablero(arbol.obtenerRaiz()->obtenerTablero());
            this_thread::sleep_for(chrono::seconds(2));

            estadoActual = TURNO_IA_MIN;
            break;
        }

        case TURNO_IA_MIN: {
            cout << "IA ...\n";

            ia.expandirArbol();
            ia.evaluarDFS();
            ia.ejecutarMejorJugada();

            estadoActual = jugadorIA ? TURNO_IA_MAX : TURNO_HUMANO;
            break;
        }

        default:
            break;
        }

        if (arbol.obtenerRaiz()->revisarFinPartida().first) {
            imprimirTablero(arbol.obtenerRaiz()->obtenerTablero());
            cout << arbol.obtenerRaiz()->revisarFinPartida().second << endl;
            estadoActual = FIN_PARTIDA;
        }
    }

    return 0;
}