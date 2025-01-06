#include <graphics.h>
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

const int CELL_SIZE = 20; // Tamaño de cada celda en píxeles
const int PLAYER_SIZE = 15; // Tamaño del jugador en píxeles

struct Player {
    int x, y; // Posición del jugador en el laberinto
};

// Función para inicializar un laberinto vacío con muros exteriores
vector<vector<int>> initializeMaze(int size) {
    vector<vector<int>> maze(size, vector<int>(size, 1)); // 1 representa un muro

    // Crear bordes exteriores como muros
    for (int i = 0; i < size; i++) {
        maze[0][i] = maze[size - 1][i] = 1;
        maze[i][0] = maze[i][size - 1] = 1;
    }

    return maze;
}

// Función para dibujar el laberinto
void drawMaze(const vector<vector<int>>& maze) {
    int size = maze.size();
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (maze[i][j] == 1) { // Dibujar muro
                setfillstyle(SOLID_FILL, BLUE);
                bar(j * CELL_SIZE, i * CELL_SIZE, (j + 1) * CELL_SIZE, (i + 1) * CELL_SIZE);
            } else { // Dibujar suelo
                setfillstyle(SOLID_FILL, WHITE);
                bar(j * CELL_SIZE, i * CELL_SIZE, (j + 1) * CELL_SIZE, (i + 1) * CELL_SIZE);
            }
        }
    }
}

// Función para dibujar al jugador
void drawPlayer(const Player& player) {
    setfillstyle(SOLID_FILL, RED);
    int x1 = player.x * CELL_SIZE + (CELL_SIZE - PLAYER_SIZE) / 2;
    int y1 = player.y * CELL_SIZE + (CELL_SIZE - PLAYER_SIZE) / 2;
    int x2 = x1 + PLAYER_SIZE;
    int y2 = y1 + PLAYER_SIZE;
    bar(x1, y1, x2, y2);
}

// Función para mover al jugador
void movePlayer(Player& player, const vector<vector<int>>& maze, char direction) {
    int newX = player.x;
    int newY = player.y;

    if (direction == 'W' || direction == 'w') newY--;
    else if (direction == 'A' || direction == 'a') newX--;
    else if (direction == 'S' || direction == 's') newY++;
    else if (direction == 'D' || direction == 'd') newX++;

    // Verificar si la nueva posición está dentro de los límites y no es un muro
    if (newX >= 0 && newX < maze.size() && newY >= 0 && newY < maze.size() && maze[newY][newX] == 0) {
        player.x = newX;
        player.y = newY;
    }
}

int main() {
    int mazeSize = 16; // Tamaño del laberinto (16x16 para el nivel 1)
    vector<vector<int>> maze = initializeMaze(mazeSize);

    // Crear una entrada y una salida en el laberinto
    maze[1][0] = 0; // Entrada
    maze[mazeSize - 2][mazeSize - 1] = 0; // Salida

    // Generar caminos simples para prueba
    for (int i = 1; i < mazeSize - 1; i++) {
        maze[i][1] = 0;
    }

    Player player = {1, 1}; // Posición inicial del jugador

    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    while (true) {
        cleardevice();

        drawMaze(maze);
        drawPlayer(player);

        if (kbhit()) {
            char key = getch();
            movePlayer(player, maze, key);
        }

        delay(100);
    }

    closegraph();
    return 0;
}
