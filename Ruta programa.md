El juego tendrá 3 laberintos( 16x16, 20x20, 24x24).

## *Generar los laberintos*

**Habrá una capa de lava la cual suba a medida que pase el tiempo para meter prisa al jugador**

- Mediante ***random*** seleccionar las casillas de entrada y las de salida, solo pueden ser las casillas de los laterales. 
- Para todas las casilla =1(muro)
- Crear los muros exteriores(casilla=1) y las casillas de entrada y salida vaciarlos(casilla=0). 
- Si la casilla es 60 solo puede ir a 59,61,62(preferencia a este, mediante random definiremos las posibilidades, nunca hacia atrás o la casilla anterior). 
- Crear un número aleatorio, dependiendo del nivel, de la tabla del 16,20,24 para crear la casilla inicial.(num aleatorio = i, casilla inicial = 16xi)
- Si o si la primera debe se hacia adelante, después crear las posibilidades de ir a izquierda derecha o recto(20,20,60)
- Solo podemos usar las casillas =1, la casilla hacia atrás =1 pero no se puede usar.
- Seguir el bucle hasta crear una salida
- Calcular en que rango se ha creado el camino principal(correcto) para restringir la dirección de los caminos secundarios. 
- Con ello crear las bifurcaciones, si pasa por (6,5) crear un camino desde (6,1) a (6,5).
- De estos caminos secundarios crear 1 bifurcación(nivel 1), 2 bifurcaciones(nivel 2) y 3 bifurcaciones +1 de cada una de estas(nivel 3)
- Al renderizar el juego casilla=1 textura muro casilla=0 suelo
![[16x16_times_table.png]]
![[Pasted image 20241210082719.png]]![[Pasted image 20241210081552.png]]

## *Generar Objetos*

- Los objetos para ayudar al jugador, antorcha(tier 1 ), reloj parar tiempo(tier 2), escudo(tier 1), poción de pasividad(10s)(tier 3).
- Cada uno de estos objetos tiene un nivel de rareza(1-3), dependiendo de este nivel se creará el objeto mas lejos o mas cerca de la entrada + un porcentaje de aleatoriedad para la creación de este.

## *Jugadores*

- Se creará un jugador con cierta temática
- El jugador ya estará en la primera casilla del laberinto(se renderiza antes el juego que el jugador)
- Cada casilla será de 20x20 píxel y el jugador ocupará 15x15, El jugador se moverá con W,A,S,D.
- El jugador podrá elegir entre espada o arco, ambos atacaran con la tecla space.

## *Enemigos*

- Se creará un enemigo con cierta temática
- También ocupará un 15x15
- El enemigo se colocará en el mapa de forma aleatoria, al acercarse a 5 casillas el enemigo irá a tu última posición.
- Dependiendo del nivel habrá un rango de enemigos, nivel 1 de 3-5 enemigos, nivel 2 de 8-10 enemigos y el nivel 3 de 15-20 enemigos

