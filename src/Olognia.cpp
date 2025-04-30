/**
 * @authors
 * Lucas Morales Oyanedel y Valentina Serón Canales
 * @date 26 de abril 2025
 **/

#include <iostream>
#include <deque>
#include <cmath>
#include <limits>

struct enemigo{
    int vida_enemigo;
    int ataque_enemigo;
    int tipo_enemigo; // (esbirros:0 CANOs:1 miniCANOs:2)
};

/**
 * Programa principal
 *
 * @param vida_mechon: guardará el número de vidas del mechon
 * @param cantidad_enemigos: será el número de esbirros total (CANO o no) a los que el mechon debe enfrentarse
 * @param turno: contador del número de turnos jugados por el mechon
 * @param ataque_mechon: número de daño que hace el mechon (este valor aumenta cada 5 esbirros derrotados exitosamente)
 * @param enemigos_derrotados: número float de enemigos derrotados (esbirros y CANOs:1 miniCANOs:0.5)
 *
 */
int main() {
    int vida_mechon, cantidad_enemigos, turno = 0, ataque_mechon = 2, dano_provocado = 0;
    float enemigos_derrotados = 0.0;

    // Se ingresan las variables iniciales del mechón y la cantidad de enemigos
    std::cin >> vida_mechon >> cantidad_enemigos;

    // Validación: la vida del mechón debe ser positiva
    if (vida_mechon <= 0) {
        std::cout << "Entrada invalida primera fila, el dato debe ser mayor a 0";
        return -1;
    }
    // Validación: debe haber al menos un enemigo
    if (cantidad_enemigos <= 0) {
        std::cout << "Entrada invalida segunda fila, el dato debe ser mayor a 0";
        return -1;
    }

    // Declaración del arreglo de enemigos con el tamaño indicado
    enemigo Enemy[cantidad_enemigos];

    // Se ingresa la vida de cada enemigo
    for (int i = 0; i < cantidad_enemigos; ++i) {
        std::cin >> Enemy[i].vida_enemigo;
        // Validación: la vida debe ser un número positivo
        if (std::cin.fail() || Enemy[i].vida_enemigo <= 0) {
            std::cout << "Entrada invalida tercera fila, el dato debe ser mayor a 0";
            return -1;
        }
    }

    // Se ingresa el ataque de cada enemigo
    for (int i = 0; i < cantidad_enemigos; ++i) {
        std::cin >> Enemy[i].ataque_enemigo;
        // Validación: el ataque debe ser un número positivo
        if (std::cin.fail() || Enemy[i].ataque_enemigo <= 0) {
            std::cout << "Entrada invalida cuarta fila, el dato debe ser mayor a 0";
            return -1;
        }
    }

    // Se ingresa el tipo de cada enemigo (0 o 1 solamente)
    for (int i = 0; i < cantidad_enemigos; ++i) {
        std::cin >> Enemy[i].tipo_enemigo;
        // Validación: el tipo solo puede ser 0 (esbirro) o 1 (CANO)
        if (std::cin.fail() || (Enemy[i].tipo_enemigo != 0 && Enemy[i].tipo_enemigo != 1)) {
            std::cout << "Entrada invalida quinta fila, el dato debe ser igual a 0 o 1";
            return -1;
        }
    }

    /**
     * La siguiente adt deque (doble cola) será usada para colocar todos los enemigos.
     * El primer enemigo en atacar será el primero en la parte frontal de la deque.
     * Cuando un CANO se divide, sus miniCANOs se colocan al frente para ser enfrentados inmediatamente.
     */
    std::deque<enemigo> cola_enemigos;
    for (int i = 0; i < cantidad_enemigos; ++i) cola_enemigos.push_back(Enemy[i]);

    int enemigos_derrotados_prev = 0;

    // siembre que existan enemigos en la cola y el mechon este vivo, jugamos
    while (vida_mechon > 0 && !cola_enemigos.empty()) {
        enemigo actual = cola_enemigos.front();
        cola_enemigos.pop_front();

        int cantidad_golpes_cano = 0;

        // Mejora del martillo cada 5 enemigos derrotados completos
        if (floor(enemigos_derrotados) > enemigos_derrotados_prev && ((int)floor(enemigos_derrotados)) % 5 == 0) {
            ataque_mechon++;
            enemigos_derrotados_prev = (int)floor(enemigos_derrotados);
        }

        bool enemigo_dividido = false;

        // Simpre que el enemigo aún tenga vida y el mechon esté vivo...
        while (actual.vida_enemigo > 0 && vida_mechon > 0) {
            turno++; // contador de turnos

            /**
             * Daño efectivo: el menor entre el ataque del mechon y la vida restante del enemigo
             * Será usado para calcular el daño total causado al enemigo
             */
            int dano_efectivo = std::min(ataque_mechon, actual.vida_enemigo);

            actual.vida_enemigo -= ataque_mechon;
            if (actual.vida_enemigo < 0) actual.vida_enemigo = 0;

            dano_provocado += dano_efectivo;

            if (actual.vida_enemigo > 0) vida_mechon -= actual.ataque_enemigo;
            
            if (actual.tipo_enemigo == 1) {
                cantidad_golpes_cano++;
                if (cantidad_golpes_cano == 2 && actual.vida_enemigo > 0 && !enemigo_dividido) {
                    enemigo_dividido = true;

                    int vida_mini = std::floor(actual.vida_enemigo / 2);
                    int ataque_mini = actual.ataque_enemigo - 1;

                    if (vida_mini < 1) vida_mini = 1;
                    if (ataque_mini < 1) ataque_mini = 1;

                    cola_enemigos.push_front({vida_mini, ataque_mini, 2});
                    cola_enemigos.push_front({vida_mini, ataque_mini, 2});
                    break;
                }
            }
        }

        if (actual.vida_enemigo <= 0) {
            if (actual.tipo_enemigo == 2) enemigos_derrotados += 0.5f;
            else enemigos_derrotados += 1.0f;
        }
    }

    if (vida_mechon > 0) {
        std::cout << "\n" << dano_provocado;
        std::cout << "\nEZ pizi\n";
    } else {
        std::cout << "\n" << dano_provocado;
        std::cout << "\nRIP mechon\n";
    }

    return 0;
}