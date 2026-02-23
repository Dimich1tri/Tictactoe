#include "ArbolJuego.h"
#include <iostream>

ArbolJuego::ArbolJuego() {
    this->raiz = NULL;
}

ArbolJuego::ArbolJuego(EstadoJuego* val) {
    this->raiz = val;
}

ArbolJuego::~ArbolJuego() {
    delete this->raiz;
    this->raiz = NULL;
}

bool ArbolJuego::esVacio() const {
    return this->raiz == NULL;
}

EstadoJuego* ArbolJuego::obtenerRaiz() {
    return this->raiz;
}

void ArbolJuego::fijarRaiz(EstadoJuego* nraiz) {
    this->raiz = nraiz;
}

void ArbolJuego::actualizarRaiz(EstadoJuego* nuevaRaiz) {
    if (this->raiz != NULL && nuevaRaiz != NULL) {
        this->raiz->obtenerDesc().remove(nuevaRaiz);
        
        delete this->raiz; 
    }
    fijarRaiz(nuevaRaiz);
}