
Entregable laboratorio 1: Larga vida a Olognia  
503230 Estructura de Datos  
Ingeniería Civil Informática  
Universidad de Concepción  

Lucas Morales Oyanedel y Valentina Serón Canales  

---

## Aclaraciones

- El código está pensado para sistema operativo Windows, no se garantiza que funcione para otros sistemas operativos
  
- El orden de ataque es:
    1. Ataca primero el mechón
    2. Luego ataca el enemigo (si aún sobrevive)

- Al dividirse un CANO, los enemigos resultantes se llaman *miniCANOs*
- A los miniCANOs se les asigna el tipo de enemigo `'2'`
- El daño inicial del mechón es **2**

---

## Cómo trabajar con el código:

Para **compilar** el código por CMD (Windows), debe ir a la carpeta del proyecto y utilizar uno de los siguientes comandos:

    c++ ./src/Olognia.cpp -o ./src/Olognia.exe -Wall -g -O2
.      

    g++ ./src/Olognia.cpp -o ./src/Olognia.exe -Wall -g -O2
.

    gcc ./src/Olognia.cpp -o ./src/Olognia.exe -Wall -g -O2
.

    cpp ./src/Olognia.cpp -o ./src/Olognia.exe -Wall -g -O2

En caso de estar ya en la carpeta 'src', simplemente use:
    
    c++ Olognia.cpp -o Olognia.exe -Wall -g -O2

Para **ejecutar** el código por CMD (en caso de querer hacer una entrada manual de datos):

desde la raíz del proyecto  
    
    ./src/Olognia.exe

Si está dentro de la carpeta 'src'
    
    Olognia.exe 

Si desea probar el código con uno de los casos de prueba descritos más abajo, puede usar el siguiente comando:

    ./src/Olognia.exe < "casos de prueba/caso1.txt"

.

    ./src/Olognia.exe < "casos de prueba/caso2.txt"

.

    ./src/Olognia.exe < "casos de prueba/caso3.txt"


o en caso de no estar dentro de la carpeta 'src'

    ./Olognia.exe < "casos de prueba/caso1.txt"

.

    ./Olognia.exe < "casos de prueba/caso1.txt"

.

    ./Olognia.exe < "casos de prueba/caso1.txt"

---

## Sobre el archivo `Olognia.cpp`:

Este archivo contiene el código para compilar y ejecutar el programa solicitado.  
El input debe ser en 5 líneas, correspondientes a:

    vida_mechon
    cantidad_enemigos
    vida_enemigo         (arreglo)
    ataque_enemigo       (arreglo)
    tipo_enemigo         (arreglo)

El programa imprimirá:

    - "EZ pizi" si el mechón gana
    - "RIP mechon" si el mechón pierde

---

## Estructura de datos utilizada:

Se utilizó una estructura `deque` (doble cola) para almacenar a los enemigos.  
Esto permite que el mechón enfrente a los enemigos en orden, y que los *miniCANOs* generados tras dividir un CANO sean enfrentados inmediatamente (insertados al frente de la deque).

---

## Casos de prueba y sus outputs:

**Caso 1:**

Input:
```
50  
7  
7 3 3 3 3 3 3  
1 2 1 2 1 2 1  
1 0 0 0 0 0 0
```

Output:
```
24  
EZ pizi
```

---

**Caso 2:**

Input:
```
20  
4  
3 3 3 3  
3 3 3 3  
0 0 0 0
```

Output:
```
12  
EZ pizi
```

---

**Caso 3:**

Input:
```
10  
1  
10  
4  
1
```

Output:
```
6  
RIP mechon
```
