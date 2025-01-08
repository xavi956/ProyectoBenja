#include "graphics.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;
//tamaños
const int TAMAÑO_CELDA = 20; 
const int TAMAÑO_PLAYER = 15; 

struct Player {//struct pq son 2 datos(obj)
    int x, y; 
};

// Funcion inicializar  laberinto 
vector<vector<int>> iniciarLab(int size) {
    vector<vector<int>> maze(size, vector<int>(size, 1)); // 1 representa  muro / vector como array pero se puede modificar

    // Crear bordes
    for (int i = 0; i < size; i++) {
        maze[0][i] = maze[size - 1][i] = 1;
        maze[i][0] = maze[i][size - 1] = 1;
    }

    return maze;
}

// Funcion conectar inicio y final  
void conecInicFin(vector<vector<int>>& laberinto) {
    int size = laberinto.size();
    int x = 1, y = 1;

    while (x < size - 2 || y < size - 2) {//-2 por los bordes
        laberinto[y][x] = 0; // Crear camino--> varia valor celda a 0

        // direccion aleatoria
        int direction = rand() % 2; // 0 para derecha  1 para abajo
        if (direction == 0 && x < size - 2) {
            x++;
        }
        else if (y < size - 2) {
            y++;
        }
    }

    laberinto[size - 2][size - 2] = 0; // Asegurar salida conectada x,y=0,0
}

//  dibujar el laberinto
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

//  dibujar al jugador
void DibujarPlayer(const Player& player) {
    setfillstyle(SOLID_FILL, RED);
    int x1 = player.x * TAMAÑO_CELDA + (TAMAÑO_CELDA - TAMAÑO_PLAYER) / 2;
    int y1 = player.y * TAMAÑO_CELDA + (TAMAÑO_CELDA - TAMAÑO_PLAYER) / 2;
    int x2 = x1 + TAMAÑO_PLAYER;
    int y2 = y1 + TAMAÑO_PLAYER;
    bar(x1, y1, x2, y2);//BAR-->comando graphics para dibujar rectangulo
}

//  al jugador
void movePlayer(Player& player, const vector<vector<int>>& maze, char direccion) {
    int newX = player.x;
    int newY = player.y;

    if (direccion == 'W' || direccion == 'w') newY--;
    else if (direccion == 'A' || direccion == 'a') newX--;
    else if (direccion == 'S' || direccion == 's') newY++;
    else if (direccion == 'D' || direccion == 'd') newX++;

    // Verificar si  posición  dentro de los límites y no muro
    if (newX >= 0 && newX < maze.size() && newY >= 0 && newY < maze.size() && maze[newY][newX] == 0) {
        player.x = newX;
        player.y = newY;
    }
}

int main() {
    srand(time(0));

    int mazeSize = 16; // Tamaño del laberinto (16x16 nivel 1)
    vector<vector<int>> laber = iniciarLab(mazeSize);

    conecInicFin(laber);

    Player player = { 1, 1 }; // Posición inicial  jugador

    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    while (true) {
        cleardevice();

        dibujarLab(laber);
        DibujarPlayer(player);

        if (kbhit()) {
            char key = getch();
            movePlayer(player, laber, key);
        }

        delay(10); // 
    }

    closegraph();
    return 0;
}
