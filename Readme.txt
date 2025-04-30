Entregable laboratorio 1: Larga vida a Olognia
503230 Estructura de Datos
Ingeniería Civil Informática 
Universidad de Concepción

Lucas Morales Oyanedel y Valentina Serón Canales

El archivo de extensión .cpp contiene el código para compilar y ejecutar lo solicitado:
- El input correspondiente a lo pedido (4 lineas de datos)
- El output con el mensaje "EZ pizi" en caso de ganar o de caso contrario "RIP mechón"

La estructura de datos elegida e implementada es un queue el cual almacena los enemigos
a los que se debe enfrentar el mechón por cada turno (según el numero de enemigos y sus
divisiones en mini-CANOs si corresponde). 

Añadiendo a la salida del código, nos tomamos la libertad creativa de imprimir en pantalla
los turnos, stats del enemigo, vida del mechón, daño provocado, etc., de la siguiente manera:

------------------------
El siguiente enemigo es un esbirro y tiene los siguientes stats:
Vida: 3, Ataque: 3, Tipo: 0
------------------------
Turno 1
------------------------
El mechon ataca con 2 de dano
Vida del enemigo: 3 -> 1
El esbirro contra-ataca, haciendo 3 de dano
Vida del mechon: 20 -> 17
------------------------
El estracto anterior corresponde al test realizado con valores de prueba en el archivo
"valores_de_prueba.txt".