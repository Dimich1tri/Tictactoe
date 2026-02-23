#ifndef __ARBOLJUEGO_H__
#define __ARBOLJUEGO_H__

#include "EstadoJuego.h"
#include <queue>

class ArbolJuego {
protected:
    EstadoJuego* raiz;

public:
    ArbolJuego();
    ArbolJuego(EstadoJuego* val);
    ~ArbolJuego();

    bool esVacio() const;
    EstadoJuego* obtenerRaiz();
    void fijarRaiz(EstadoJuego* nraiz);
    void actualizarRaiz(EstadoJuego* nuevaRaiz);
};

#endif