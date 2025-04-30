/**
 * @authors 
 * Lucas Morales Oyanedel y Valentina Serón Canales
 * @date 26 de abril 2025
 **/

 #include <iostream>
 #include <queue>
 #include <cmath>
 

 struct enemigo {
     int vida_enemigo;
     int ataque_enemigo;
     int tipo_enemigo; // (esbirros:0 CANOs:1 miniCANOs:2)
 };
 
 /**
  * Programa principal
  
  * @param vida_mechon: guardará el número de vidas del mechon
  * @param cantidad_enemigos: será el número de esbirros total (CANO o no) a los que el mechon debe enfrentarse
  * @param turno: contador del número de turnos jugados por el mechon
  * @param ataque_mechon: número de daño que hace el mechon (este valor aumenta cada 5 esbirros derrotados exitosamente)
  * @param mini_canos_derrotados: número de mini CANOs derrotados por el mechon
  * @param enemigos_derrotados: número float de enemigos derrotados (esbirros y CANOs:1 miniCANOs:0.5)
  */
 int main() {
     int vida_mechon, cantidad_enemigos, turno = 0, ataque_mechon = 2, mini_canos_derrotados = 0, dano_provocado = 0;
     float enemigos_derrotados = 0.0;
     std::cin >> vida_mechon >> cantidad_enemigos;
 
     if (vida_mechon <= 0 || cantidad_enemigos <= 0) return -1;
     // @struct enemigo, se define la estructura según la cantidad de enemigos que se ingresa 

     enemigo Enemy[cantidad_enemigos];

     // cada ciclo irá llenando los tres parametros que conforman un enemigo (sus stats)

     for (int i = 0; i < cantidad_enemigos; ++i) std::cin >> Enemy[i].vida_enemigo;
     for (int i = 0; i < cantidad_enemigos; ++i) std::cin >> Enemy[i].ataque_enemigo;
     for (int i = 0; i < cantidad_enemigos; ++i) std::cin >> Enemy[i].tipo_enemigo;
 
     /**
     * La siguiente adt queue (cola) será usada para colocar todos los enemigos.
     * El primer enemigo en atacar será el primero en la cola del queue. 
     */
     std::queue<enemigo> cola_enemigos;
     for (int i = 0; i < cantidad_enemigos; ++i) {
         cola_enemigos.push(Enemy[i]);
     }
 
     int enemigos_derrotados_prev = 0; // auxiliar para mejorar daño
     // siembre que existan enemigos en la cola y el mechon este vivo, jugamos
     while (vida_mechon > 0 && !cola_enemigos.empty()) {
         enemigo actual = cola_enemigos.front();
         cola_enemigos.pop();
 
         /** @param cantidad_golpes_cano: cantidad entera de golpes que tiene un enemigo tipo CANO antes de su división */
         int cantidad_golpes_cano = 0;
         mini_canos_derrotados = 0;
        
         // Mejora del martillo cada 5 enemigos derrotados completos
         if (floor(enemigos_derrotados) > enemigos_derrotados_prev && ((int)floor(enemigos_derrotados)) % 5 == 0) {
             std::cout << "------------------------\nTras haber derrotado a 5 enemigos, el mechon ha mejorado el martillo chillon\n";
             std::cout << "actualizacion de dano: " << ataque_mechon << " -> " << ataque_mechon + 1 << "\n";
             ataque_mechon++;
             enemigos_derrotados_prev = (int)floor(enemigos_derrotados);
         }
         
         /** @param tipoNombre: será nuestra variable de tipo string con la palabra esbirro, CANO o Mini-CANO según el valor de actual.tipo_enemigo*/
         std::string tipoNombre = actual.tipo_enemigo == 0 ? "esbirro" : actual.tipo_enemigo == 1 ? "CANO" : "Mini-CANO";
         // mensaje que indica cuál es el siguiente enemigo y sus stats
         std::cout << "------------------------\nEl siguiente enemigo es un " << tipoNombre << " y tiene los siguientes stats:\n";
         std::cout << "Vida: " << actual.vida_enemigo << ", Ataque: " << actual.ataque_enemigo << ", Tipo: " << actual.tipo_enemigo << std::endl;
        
         // la siguiente variable booleana será usada en caso que el enemigo se divida en mini-CANOs
         bool enemigo_dividido = false;
        
         // Simpre que el enemigo aún tenfa vida y el mechon esté vivo...
         while (actual.vida_enemigo > 0 && vida_mechon > 0) {
             turno++; // contador de turnos
             std::cout << "------------------------\nTurno " << turno << "\n------------------------\n";
             std::cout << "El mechon ataca con " << ataque_mechon << " de dano\n";
             
             int vida_anterior = actual.vida_enemigo;
 
             /** 
              * Daño efectivo: el menor entre el ataque del mechon y la vida restante del enemigo
              * Será usado para calcular el daño total causado al enemigo
              */ 
             int dano_efectivo = std::min(ataque_mechon, actual.vida_enemigo);
             
             // daño provocado al enemigo por el ataque del mechon
             actual.vida_enemigo -= ataque_mechon;
             // en caso que la vida del enemigo quede en cifra negativa, se inicializa en 0 
             if (actual.vida_enemigo < 0) actual.vida_enemigo = 0; 
 
             dano_provocado += dano_efectivo;
 
             std::cout << "Vida del enemigo: " << vida_anterior << " -> " << actual.vida_enemigo << std::endl;
            
             // siempre que el enemigo tenga vida, podrá causar daño al mechon
             if (actual.vida_enemigo > 0) {
                 int vida_anterior_mechon = vida_mechon;
                 std::cout << "El " << tipoNombre << " contra-ataca, haciendo " << actual.ataque_enemigo << " de dano\n";
                 vida_mechon -= actual.ataque_enemigo;
                 std::cout << "Vida del mechon: " << vida_anterior_mechon << " -> " << vida_mechon << std::endl;
             }
             // si el enemigo es de tipo CANO
             if (actual.tipo_enemigo == 1) {
                 cantidad_golpes_cano++;
                 // si el el enemigo sigue vivo y aun no se divide, se fracciona en mini-CANOs!
                 if (cantidad_golpes_cano == 2 && actual.vida_enemigo > 0 && !enemigo_dividido) {
                     enemigo_dividido = true;
                     std::cout << "------------------------\nEl CANO se divide en 2 Mini-CANOS!\n";
 
                     int vida_mini = std::floor(actual.vida_enemigo / 2); 
                     int ataque_mini = actual.ataque_enemigo - 1;
 
                     if (vida_mini < 1) vida_mini = 1;
                     if (ataque_mini < 1) ataque_mini = 1;
                     // los mini-CANOs van a la cola del queue 
                     cola_enemigos.push({vida_mini, ataque_mini, 2});
                     cola_enemigos.push({vida_mini, ataque_mini, 2});
                     break;
                 }
             }
         }
         // Cuando el enemigo haya sido derrotado, su vida será 0 o negativa
         if (actual.vida_enemigo <= 0) {
             if (actual.tipo_enemigo == 2) enemigos_derrotados += 0.5f;
             else enemigos_derrotados += 1.0f;
 
             std::cout << "------------------------\nEl " << tipoNombre << " ha sido derrotado.\n";
             std::cout << "Enemigos derrotados: " << enemigos_derrotados << "/" << cantidad_enemigos << "\n";
         }
     }
     // Mensaje final para el caso en que el mechón gane o no...
     std::cout << "------------------------\n\nFIN DE LA BATALLA\n";
     if (vida_mechon > 0) {
         std::cout << "El mechon ha sobrevivido con " << vida_mechon << " de vida!\n";
         std::cout << "El mechon ha proporcionado un dano de " << dano_provocado << " a los enemigos!\nLARGA VIDA A OLOGNIA\n\n";
         std::cout << "EZ pizi\n";
     } else {
         std::cout << "El mechon ha sido derrotado.\nOLOGNIA ESTA A LA MERCED DEL ENEMIGO\nQUE DIOS NOS AMPARE\n\n";
     }
 
     return 0;
 } 