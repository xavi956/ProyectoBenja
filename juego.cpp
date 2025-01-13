#include "graphics.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <string>

using namespace std;
using namespace chrono;

// Tamaños
const int TAMAÑO_CELDA = 20;
const int TAMAÑO_PLAYER = 15;

// Estructura del jugador
struct Player {
    int x, y;
};

// Inicializar laberinto
vector<vector<int>> iniciarLab(int size) {
    vector<vector<int>> lab(size, vector<int>(size, 1)); // 1 representa muro
    // Crear bordes
    for (int i = 0; i < size; i++) {
        lab[0][i] = lab[size - 1][i] = 1;
        lab[i][0] = lab[i][size - 1] = 1;
    }
    return lab;
}

// Conectar inicio y final
void conecInicFin(vector<vector<int>>& laberinto) {
    int size = laberinto.size();
    int x = 1, y = 1;

    while (x < size - 2 || y < size - 2) {
        laberinto[y][x] = 0;

        // Dirección aleatoria
        int direction = rand() % 2; // 0 derecha, 1 abajo
        if (direction == 0 && x < size - 2) x++;
        else if (y < size - 2) y++;
    }

    laberinto[size - 2][size - 2] = 0; // Asegurar salida conectada
}

// Dibujar el laberinto
void dibujarLab(const vector<vector<int>>& laberinto) {
    int size = laberinto.size();
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (laberinto[i][j] == 1) { // Dibujar muro
                setfillstyle(SOLID_FILL, BLUE);
                bar(j * TAMAÑO_CELDA, i * TAMAÑO_CELDA, (j + 1) * TAMAÑO_CELDA, (i + 1) * TAMAÑO_CELDA);
            }
            else { // Dibujar suelo
                setfillstyle(SOLID_FILL, WHITE);
                bar(j * TAMAÑO_CELDA, i * TAMAÑO_CELDA, (j + 1) * TAMAÑO_CELDA, (i + 1) * TAMAÑO_CELDA);
            }
        }
    }
}

// Dibujar al jugador
void DibujarPlayer(const Player& player) {
    setfillstyle(SOLID_FILL, RED);
    int x1 = player.x * TAMAÑO_CELDA + (TAMAÑO_CELDA - TAMAÑO_PLAYER) / 2;
    int y1 = player.y * TAMAÑO_CELDA + (TAMAÑO_CELDA - TAMAÑO_PLAYER) / 2;
    int x2 = x1 + TAMAÑO_PLAYER;
    int y2 = y1 + TAMAÑO_PLAYER;
    bar(x1, y1, x2, y2);
}

// Mover al jugador
void movePlayer(Player& player, const vector<vector<int>>& lab, char direccion) {
    int newX = player.x;
    int newY = player.y;

    if (direccion == 'W' || direccion == 'w') newY--;
    else if (direccion == 'A' || direccion == 'a') newX--;
    else if (direccion == 'S' || direccion == 's') newY++;
    else if (direccion == 'D' || direccion == 'd') newX++;

    if (newX >= 0 && newX < static_cast<int>(lab.size()) &&
        newY >= 0 && newY < static_cast<int>(lab.size()) &&
        lab[newY][newX] == 0) {
        player.x = newX;
        player.y = newY;
    }
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    vector<int> niveles = { 16, 20, 24 }; // Tamaño niveles
    int nivelActual = 0;

    const int TIEMPO_LIMITE = 60; 

    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    while (nivelActual < static_cast<int>(niveles.size())) {
        int tamañoLab = niveles[nivelActual]; // Tamaño del laberinto actual
        vector<vector<int>> laber = iniciarLab(tamañoLab);
        conecInicFin(laber);

        Player player = { 1, 1 }; // Posición inicial del jugador
        bool juegoActivo = true;

        auto inicioTiempo = steady_clock::now();

        while (juegoActivo) {
            cleardevice();
            dibujarLab(laber);
            DibujarPlayer(player);

            // Tiempo restante
            auto tiempoActual = steady_clock::now();
            int tiempoRestante = TIEMPO_LIMITE - static_cast<int>(duration_cast<seconds>(tiempoActual - inicioTiempo).count());

            // Mostrar tiempo
            setcolor(WHITE);
            outtextxy(10, 10, const_cast<char*>(("Tiempo restante: " + to_string(max(0, tiempoRestante)) + " s").c_str()));

            // Verificar tiempo
            if (tiempoRestante <= 0) {
                outtextxy(200, 200, const_cast<char*>("Has perdido :("));
                juegoActivo = false;
                break;
            }

            // Verificar victoria
            if (player.x == tamañoLab - 2 && player.y == tamañoLab - 2) {
                outtextxy(200, 200, const_cast<char*>("¡Nivel completado!"));
                delay(2000); // Esperar antes de pasar al siguiente nivel
                nivelActual++; // Incrementar el nivel
                juegoActivo = false;
                break;
            }

            if (kbhit()) {
                char key = getch();
                movePlayer(player, laber, key);
            }

            delay(10);
        }

        if (nivelActual == static_cast<int>(niveles.size())) {
            outtextxy(200, 200, const_cast<char*>("¡Felicitaciones! Has completado todos los niveles."));
            break;
        }
    }

    delay(3000);
    closegraph();
    return 0;
}
