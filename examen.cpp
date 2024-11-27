#include "graphics.h"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <math.h>
using namespace std;
int factorial(int num) {
    int resultado = 1; 
    for (int i = 1; i <= num; i++) { 
        resultado *= i; 
    }
    return resultado; 
}
int validarNum(num, 25) {
    if (num > 25) {
       main()
    }
}
/// <summary>
/// programa entre 1 y 25 
/// </summary>
/// <returns>1!,2!,3!,...,25!</returns>
int main() {
    string continuar = "s";
    while (continuar == "s") {
        int num, resultado;
        cout << "\n\n[+] Introduce el numero: ";
        cin >> num;
        validarNum(num);
        cout << "\n\n[?] ¿Quieres volver a probar? (s/n): ";
        cin >> continuar;
    }
    return 0;
}