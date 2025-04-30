
Entregable laboratorio 1: Larga vida a Olognia  
503230 Estructura de Datos  
Ingeniería Civil Informática  
Universidad de Concepción  

Lucas Morales Oyanedel y Valentina Serón Canales  

---

## Cómo trabajar con el código:

Para **compilar** el código por CMD (Windows), debe ir a la carpeta del proyecto y utilizar uno de los siguientes comandos:

    c++ ./src/Olognia.cpp -o ./src/Olognia.exe -Wall -g -O2
    o
    g++ ./src/Olognia.cpp -o ./src/Olognia.exe -Wall -g -O2

    (En caso de estar ya en la carpeta 'src', simplemente use:)
        c++ Olognia.cpp -o Olognia.exe -Wall -g -O2

Para **ejecutar** el código por CMD (en caso de querer hacer una entrada manual de datos):

    ./src/Olognia.exe     ← desde la raíz del proyecto  
    Olognia.exe           ← si estás dentro de la carpeta 'src'

---

## Aclaraciones

- El orden de ataque es:
    1. Ataca primero el mechón
    2. Luego ataca el enemigo (si aún sobrevive)

- Al dividirse un CANO, los enemigos resultantes se llaman *miniCANOs*
- A los miniCANOs se les asigna el tipo de enemigo `'2'`
- El daño inicial del mechón es **2**

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