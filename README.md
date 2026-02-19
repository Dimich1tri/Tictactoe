# 🎮 Tic-Tac-Toe Invencible | IA con Minimax en C++ 🤖

![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![Artificial Intelligence](https://img.shields.io/badge/IA-Minimax%20%2B%20Alpha--Beta-FF4B4B?style=for-the-badge)
![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg?style=for-the-badge)

> Un clásico juego de Tres en Raya (Tic-Tac-Toe) impulsado por Inteligencia Artificial y escrito en C++. Este proyecto implementa algoritmos de búsqueda adversarial para crear un oponente que nunca pierde. ¡Intenta ganarle (o al menos empatarle) a la máquina! ⚔️

---

## ✨ Características

* **Rendimiento C++:** Búsqueda en el árbol de decisiones a máxima velocidad.
* **Juego contra la IA:** Enfréntate a un algoritmo que toma decisiones matemáticas perfectas.
* **Algoritmos Optimizados:** Implementación pura de algoritmos de teoría de juegos sin depender de librerías externas.
* **Interfaz de Terminal:** Ejecución limpia y directa desde la consola.

---

## 🧠 ¿Cómo funciona la IA? (Bajo el capó)

Este proyecto no utiliza reglas estáticas. En su lugar, la IA *calcula* el futuro explorando los posibles estados del tablero:

### 🔍 1. Algoritmo Minimax
La IA simula **todas** las jugadas posibles hasta el final de la partida. Asigna una puntuación a cada resultado (Ej: `+10` si gana la IA, `-10` si ganas tú, `0` si es empate). Luego, asume que tú jugarás de manera perfecta y elige el camino que **maximiza** sus posibilidades de ganar, mientras **minimiza** las tuyas.



### ✂️ 2. Poda Alfa-Beta (Alpha-Beta Pruning)
Explorar todos los futuros posibles es costoso computacionalmente. La poda Alfa-Beta es una optimización que "corta" las ramas del árbol de decisiones que ya sabemos que son peores que una opción evaluada previamente. 
* **Resultado:** La IA toma la misma decisión perfecta, pero evaluando muchos menos nodos. ⚡

### 📏 3. Función Heurística
Si decidimos limitar la profundidad de búsqueda de Minimax para tableros más grandes (ej. 4x4), es imposible llegar hasta el final del juego. Aquí entra la heurística: una función que "evalúa" qué tan ventajoso es un estado del tablero contando líneas abiertas, piezas bloqueadas y control del centro.

---

## 🚀 Compilación y Uso

Asegúrate de tener un compilador de C++ instalado en tu sistema (como `g++` o `clang`).

```bash
# 1. Clona el repositorio
git clone [https://github.com/tu-usuario/tu-repo-tictactoe.git](https://github.com/tu-usuario/tu-repo-tictactoe.git)

# 2. Entra al directorio
cd tu-repo-tictactoe

# 3. Compila el código fuente
g++ -std=c++17 -O3 -o tictactoe main.cpp

# 4. Ejecuta el juego
./tictactoe
