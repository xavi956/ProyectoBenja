#include "graphics.h"
#include <iostream>
#include <math.h>
#include <stdlib.h> // Provides exit
#include <ctype.h>

// tamaño cuadrados
const int squareSize = 50;//--> variable const NO se puede modificar

// Posiciones iniciales
int grayX = 200, grayY = 200; // Cuadrado mov
const int whiteX = 300, whiteY = 200; // Cuadrado  

// colisión  
bool colision(int x1, int y1, int x2, int y2, int size) { //Bool = True/false
    // Verifica si los cuadrados se solapan horizontal y verticalmente

    if (x1 + size >= x2) {
        return true;
    }
    else if (x1 <= x2 + size) {
        return true;
    }
    else if (y1 + size >= y2) {
        return true;
    }
    else if (y1 <= y2 + size) {
        return true;
    }
    else {
        return false;
    }
}
void setblack(int x1, int y1, int x2, int y2) {
    setcolor(BLACK);
    setfillstyle(SOLID_FILL, BLACK);
    rectangle(x1, y1, x2, y2);
    floodfill((x1 + 1), (y1 + 1), BLACK);
}
int main() {
    // Inicializar el modo gráfico
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    // Dibujar cuadrados iniciales
    while (true) {
        

        // cuadrado rojo (estático)
        setcolor(RED);
        setfillstyle(SOLID_FILL, RED);
        rectangle(100, 200, 100 + squareSize, 200 + squareSize);
        floodfill(101, 201, RED);

        // cuadrado blanco (estático)
        setcolor(WHITE);
        setfillstyle(SOLID_FILL, WHITE);
        rectangle(whiteX, whiteY, whiteX + squareSize, whiteY + squareSize);
        floodfill(whiteX + 1, whiteY + 1, WHITE);

        // cuadrado gris (móvil)
        setcolor(LIGHTGRAY);
        setfillstyle(SOLID_FILL, LIGHTGRAY);
        rectangle(grayX, grayY, grayX + squareSize, grayY + squareSize);
        floodfill((grayX + 1), (grayY + 1), LIGHTGRAY);

        

        // Detectar colisión


            // Mover cuadrado 
            if (GetAsyncKeyState(VK_UP)) {// Flecha 
                    setblack(grayX, grayY, grayX + squareSize, grayY + squareSize);
                    grayY -= 10;
            }
            if (GetAsyncKeyState(VK_DOWN)) {// Flecha abajo
                setblack(grayX, grayY, grayX + squareSize, grayY + squareSize);
                grayY += 10;
            }
            if (GetAsyncKeyState(VK_LEFT)) {// Flecha izquierda
                setblack(grayX, grayY, grayX + squareSize, grayY + squareSize);
                grayX -= 10;
            }
            if (GetAsyncKeyState(VK_RIGHT)) {// Flecha derecha
                setblack(grayX, grayY, grayX + squareSize, grayY + squareSize);
                grayX += 10;
            }
        
        delay(20);
    }
    closegraph();
    return 0;
}
