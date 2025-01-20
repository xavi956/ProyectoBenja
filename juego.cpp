#include "graphics.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <string>

using namespace std;
using namespace chrono;

const int TAMAÑO_PLAYER = 15;

// Colores -->
const int COLOR_FONDO = DARKGRAY;
const int COLOR_PAREDES = BLACK;
const int COLOR_CAMINOS = DARKGRAY;
const int COLOR_JUGADOR = LIGHTRED;
const int COLOR_TEXTO = WHITE;
const int COLOR_OPCION_HOVER = LIGHTBLUE;
const int COLOR_OPCION_NORMAL = COLOR_TEXTO;
const int COLOR_OSCURIDAD = BLACK;


const int RANGO_VISION = 2;

// Estructura del jugador
struct Player {
    int x, y;
};

// Inicializar laberinto
vector<vector<int>> iniciarLab(int size) {
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

// Dibujar celda
void dibujarCelda(int x, int y, int color, int tamañoCelda) {
    setfillstyle(SOLID_FILL, color);
    bar(x * tamañoCelda, y * tamañoCelda, (x + 1) * tamañoCelda, (y + 1) * tamañoCelda);
}

// Dibujar visibilidad restringida
void DibLabRest(const vector<vector<int>>& laberinto, int anchoPantalla, int altoPantalla, const Player& player) {
    int size = laberinto.size();
    int tamañoCelda = min(anchoPantalla / size, altoPantalla / size);

 
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {//doble para recorrer por x·y
            // Si la celda  dentro del rango  jugador
            //abs --> val absoluto
            if (abs(player.y - i) <= RANGO_VISION && abs(player.x - j) <= RANGO_VISION) {
                // Si es una pared (1), primer bucle para verificar si en rango, cambiar color paredes(o no)
                if (laberinto[i][j] == 1) {
                    dibujarCelda(j, i, COLOR_PAREDES, tamañoCelda);
                }
                else {
                    // Si es un camino (0), dibujar el camino
                    dibujarCelda(j, i, COLOR_CAMINOS, tamañoCelda);
                }
            }
            else {
                // Fuera del rango 
                dibujarCelda(j, i, COLOR_OSCURIDAD, tamañoCelda);
            }
        }
    }
}

// Dibujar al jugador
void DibujarPlayer(const Player& player, int tamañoCelda) {
    setfillstyle(SOLID_FILL, COLOR_JUGADOR);
    int x1 = player.x * tamañoCelda + (tamañoCelda - TAMAÑO_PLAYER) / 2;
    int y1 = player.y * tamañoCelda + (tamañoCelda - TAMAÑO_PLAYER) / 2;
    int x2 = x1 + TAMAÑO_PLAYER;
    int y2 = y1 + TAMAÑO_PLAYER;
    bar(x1, y1, x2, y2);
}

// Mover al jugador
void movePlayer(Player& player, const vector<vector<int>>& lab, char direccion) {
    int newX = player.x;
    int newY = player.y;

    if (direccion == 'W' || direccion == 'w' || direccion == KEY_UP) newY--;
    else if (direccion == 'A' || direccion == 'a' || direccion == KEY_LEFT) newX--;
    else if (direccion == 'S' || direccion == 's' || direccion == KEY_DOWN) newY++;
    else if (direccion == 'D' || direccion == 'd' || direccion == KEY_RIGHT) newX++;

    if (newX >= 0 && newX < static_cast<int>(lab.size()) &&
        newY >= 0 && newY < static_cast<int>(lab.size()) &&
        lab[newY][newX] == 0) {
        player.x = newX;
        player.y = newY;
    }
}

// Menú de inicio interactivo
int menuInicioInteractivo() {
    setbkcolor(COLOR_FONDO);
    cleardevice();

    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);

    const int OPCION_INICIAR = 0;
    const int OPCION_SALIR = 1;

    const int x = 200, yInicio = 150, separacion = 50;

    int opcionSeleccionada = OPCION_INICIAR;

    while (true) {
        cleardevice();
        char titulo[] = "LABERINTO ";
        outtextxy(200, 50, titulo);
        outtextxy(200, 100, const_cast<char*>("¡Así fue como te perdiste!"));
        outtextxy(200, 150, const_cast<char*>("Usa W/A/S/D para moverte."));

        char iniciar[] = "1. Iniciar Juego";
        char salir[] = "2. Salir";
        outtextxy(200, 200, iniciar);
        outtextxy(200, 250, salir);

        char key = getch();
        if (key == '1') return 1;
        if (key == '2') return 2;
    }
}

// Función principal
int main() {
    srand(static_cast<unsigned int>(time(0)));

    // Aumentar el tamaño de la ventana
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    
    int ancho = 1024;  
    int alto = 768;    

    // tamaño pantalla
    initwindow(ancho, alto);

    int tiempoRestante = 60; 
    int tiempoAnterior = 0; 

    while (true) {
        int opcion = menuInicioInteractivo();
        if (opcion == 2) break; // Salir del juego

        vector<int> niveles = { 16, 20, 24 };
        int nivelActual = 0;

        while (nivelActual < static_cast<int>(niveles.size())) {
            int tamañoLab = niveles[nivelActual];
            vector<vector<int>> laber = iniciarLab(tamañoLab);
            conecInicFin(laber);
            Player player = { 1, 1 };
            Player prevPlayer = player;
            bool juegoActivo = true;

            auto inicioTiempo = steady_clock::now();

            setbkcolor(COLOR_FONDO);
            cleardevice();
            //min valor menor
            int tamañoCelda = min(ancho / tamañoLab, alto / tamañoLab);//ajustar tamaño niveles a pantalla

            while (juegoActivo) {
                // Calcular tiempo restante
                auto tiempoActual = steady_clock::now();
                int tiempoPasado = static_cast<int>(duration_cast<seconds>(tiempoActual - inicioTiempo).count());
                if (tiempoPasado > tiempoAnterior) {
                    tiempoRestante--; // Disminuir el tiempo cada segundo
                    tiempoAnterior = tiempoPasado; // Actualizar tiempo anterior
                }

                
                setcolor(COLOR_TEXTO);
                string textoTiempo = "Tiempo: " + to_string(max(0, tiempoRestante)) + " s";
                char tiempoChar[100];
                strcpy_s(tiempoChar, textoTiempo.c_str());
                outtextxy(ancho - 200, 10, tiempoChar); // Mostrar  tiempo a la derecha

               
                if (tiempoRestante <= 0) {
                    outtextxy(200, 200, const_cast<char*>("¡Tiempo agotado! Has perdido."));
                    juegoActivo = false;
                    break;
                }

                //  player ha llegado al final del nivel
                if (player.x == tamañoLab - 2 && player.y == tamañoLab - 2) {
                    outtextxy(200, 200, const_cast<char*>("¡Nivel completado!"));
                    delay(2000);
                    nivelActual++;
                    juegoActivo = false;
                    break;
                }

                
                DibLabRest(laber, ancho, alto, player);
                DibujarPlayer(player, tamañoCelda);

                if (kbhit()) {
                    char key = getch();
                    movePlayer(player, laber, key);
                }

                delay(50);
            }

            if (nivelActual == static_cast<int>(niveles.size())) {
                outtextxy(200, 200, const_cast<char*>("¡Felicitaciones! Has completado todos los niveles."));
                break;
            }
        }

        delay(3000);
    }

    closegraph();
    return 0;
}
