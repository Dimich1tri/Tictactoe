#ifndef __ESTADOJUEGO_H__
#define __ESTADOJUEGO_H__

#include <vector>
#include <list>
#include <string>

enum EstadoCasilla
{
    VACIO = 0,
    FICHA_MIN = -1,
    FICHA_MAX = 1
};

enum EstadoFinal
{
    VICTORIA = 3,
    DERROTA = -3
};

class EstadoJuego
{
protected:
    std::vector<std::vector<int>> tablero;
    int heuristica;
    bool esMax;

    std::list<EstadoJuego *> desc;

public:
    EstadoJuego(bool iniciaMax);
    EstadoJuego(std::vector<std::vector<int>> nuevoTablero, bool turnoMax, int valorHeuristico = 0);
    ~EstadoJuego();

    EstadoCasilla obtenerCasilla(int fila, int col) const;
    void asignarCasilla(int fila, int col, EstadoCasilla ficha);
    std::vector<std::vector<int>> obtenerTablero() const;
    int obtenerHeuristica() const;
    void asignarHeuristica(int h);
    bool obtenerTurno() const;
    void asignarTurno(bool turnoMax);
    std::pair<bool,std::string> revisarFinPartida();

    void limpiarLista();
    void adicionarDesc(EstadoJuego *nval);
    std::list<EstadoJuego *> &obtenerDesc();
    bool esHoja() const;
};

#endif