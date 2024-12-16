#include "graphics.h"

// tamaño cuadrados
const int squareSize = 50;//--> variable const NO se puede modificar

// Posiciones iniciales
int grayX = 200, grayY = 200; // Cuadrado mov
const int whiteX = 300, whiteY = 200; // Cuadrado  

// colisión  
bool colison(int x1, int y1, int x2, int y2, int size) { //Bool = True/false
    // Verifica si los cuadrados se solapan horizontal y verticalmente
    if (x1 + size >= x2 && x1 <= x2 + size && y1 + size >= y2 && y1 <= y2 + size) {
        return true; 
    }
    else {
        return false; 
    }
}

int main() {
    // Inicializar el modo gráfico
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    // Dibujar cuadrados iniciales
    while (true) {
        cleardevice();

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
        floodfill(grayX + 1, grayY + 1, LIGHTGRAY);

        // Detectar colisión
        if (colison(grayX, grayY, whiteX, whiteY, squareSize)) {
            outtextxy(10, 10, "Colision detectada!");
        }

        // Mover cuadrado 
        if (GetAsyncKeyState(VK_UP)) grayY -= 10;    // Flecha arriba
        if (GetAsyncKeyState(VK_DOWN)) grayY += 10;  // Flecha abajo
        if (GetAsyncKeyState(VK_LEFT)) grayX -= 10;  // Flecha izquierda
        if (GetAsyncKeyState(VK_RIGHT)) grayX += 10; // Flecha derecha

        delay(50); 
    }
    closegraph();
    return 0;
}
