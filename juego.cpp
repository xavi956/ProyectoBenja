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
vector<vector<int>> iniciarLab(int size) {//se usa vector y no array porque es dinamico y no estatico como el array
    vector<vector<int>> lab(size, vector<int>(size, 1));
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
        int direction = rand() % 2;
        if (direction == 0 && x < size - 2) x++;
        else if (y < size - 2) y++;
    }
    laberinto[size - 2][size - 2] = 0;
}

// Dibujar una celda
void dibujarCelda(int x, int y, int color) {
    setfillstyle(SOLID_FILL, color);
    bar(x * TAMAÑO_CELDA, y * TAMAÑO_CELDA, (x + 1) * TAMAÑO_CELDA, (y + 1) * TAMAÑO_CELDA);
}

// Dibujar el laberinto
void dibujarLab(const vector<vector<int>>& laberinto) {
    int size = laberinto.size();
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (laberinto[i][j] == 1) {
                dibujarCelda(j, i, BLUE);
            }
            else {
                dibujarCelda(j, i, WHITE);
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

// Actualizar el juego
void actualizarJuego(Player& player, const vector<vector<int>>& lab, Player& prevPlayer) {
    dibujarCelda(prevPlayer.x, prevPlayer.y, WHITE);
    DibujarPlayer(player);
    prevPlayer = player;
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
    srand(static_cast<unsigned int>(time(0)));//num aleatorio

    vector<int> niveles = { 16, 20, 24 };
    int nivelActual = 0;
    const int TIEMPO_LIMITE = 60;

    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    while (nivelActual < static_cast<int>(niveles.size())) {
        int tamañoLab = niveles[nivelActual];
        vector<vector<int>> laber = iniciarLab(tamañoLab);
        conecInicFin(laber);
        //en vez de cleardevice solo dibuja al jugador otra vez
        Player player = { 1, 1 };
        Player prevPlayer = player;
        bool juegoActivo = true;

        auto inicioTiempo = steady_clock::now();

        dibujarLab(laber);
        DibujarPlayer(player);

        while (juegoActivo) {
            auto tiempoActual = steady_clock::now();
            int tiempoRestante = TIEMPO_LIMITE - static_cast<int>(duration_cast<seconds>(tiempoActual - inicioTiempo).count());

            setcolor(WHITE);
            string textoTiempo = "Tiempo restante: " + to_string(max(0, tiempoRestante)) + " s";
            char tiempoChar[100];
            strcpy(tiempoChar, textoTiempo.c_str());
            outtextxy(10, 10, tiempoChar);

            if (tiempoRestante <= 0) {
                outtextxy(200, 200, "Has perdido :(");
                juegoActivo = false;
                break;
            }

            if (player.x == tamañoLab - 2 && player.y == tamañoLab - 2) {
                outtextxy(200, 200, "¡Nivel completado!");
                delay(2000);
                nivelActual++;
                juegoActivo = false;
                break;
            }

            if (kbhit()) {
                char key = getch();
                movePlayer(player, laber, key);
                actualizarJuego(player, laber, prevPlayer);
            }

            delay(10);
        }

        if (nivelActual == static_cast<int>(niveles.size())) {
            outtextxy(200, 200, "¡Felicitaciones! Has completado todos los niveles.");
            break;
        }
    }

    delay(3000);
    closegraph();
    return 0;
}
