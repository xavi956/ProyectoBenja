# Generador de Laberintos Aleatorios

Este proyecto genera laberintos de forma aleatoria utilizando un mapeado por casillas. Se crea un camino principal desde una casilla inicial (en la primera fila) hasta una casilla meta (en la última fila), y caminos secundarios para aumentar la complejidad.

## 🚀 Funcionalidades

1. **Camino Principal**:  
   - Se selecciona de forma aleatoria una casilla de inicio (en la primera fila) y una casilla de meta (en la última fila).  
   - El camino principal se genera conectando estas casillas, respetando limitaciones en las casillas que puede usar (por ejemplo, solo las 3 columnas cercanas al inicio).  

2. **Caminos Secundarios**:  
   - A partir del camino principal, se generan caminos secundarios seleccionando casillas adyacentes.  
   - Los caminos secundarios tienen un límite de expansión configurable (por ejemplo, hasta 3 casillas adicionales).

3. **Mapeado Aleatorio**:  
   - Las posiciones del camino se almacenan en un array para facilitar la creación dinámica de caminos secundarios.  
   - Ejemplo de array: `meta[64] = {60, 52, 51, 43, 35, 27, 28, 29, 30, 22, 14, 6}`.

