#include <iostream>
#include <queue>
#include <cmath>

struct enemigo {
    int vida_enemigo;
    int ataque_enemigo;
    int tipo_enemigo;
};

int main() {
    int vida_mechon, cantidad_enemigos, turno = 0, ataque_mechon = 2, mini_canos_derrotados = 0;
    float enemigos_derrotados = 0.0;
    std::cin >> vida_mechon >> cantidad_enemigos;

    if (vida_mechon <= 0 || cantidad_enemigos <= 0) return -1;

    enemigo Enemy[cantidad_enemigos];

    for (int i = 0; i < cantidad_enemigos; ++i) std::cin >> Enemy[i].vida_enemigo;
    for (int i = 0; i < cantidad_enemigos; ++i) std::cin >> Enemy[i].ataque_enemigo;
    for (int i = 0; i < cantidad_enemigos; ++i) std::cin >> Enemy[i].tipo_enemigo;

    std::queue<enemigo> cola_enemigos;
    for (int i = 0; i < cantidad_enemigos; ++i) {
        cola_enemigos.push(Enemy[i]);
    }

    int enemigos_derrotados_prev = 0;

    while (vida_mechon > 0 && !cola_enemigos.empty()) {
        enemigo actual = cola_enemigos.front();
        cola_enemigos.pop();

        int cantidad_golpes_cano = 0;

        // Mejora de martillo cada 5 enemigos derrotados completos
        if (floor(enemigos_derrotados) > enemigos_derrotados_prev && ((int)floor(enemigos_derrotados)) % 5 == 0) {
            std::cout << "------------------------\nTras haber derrotado a 5 enemigos, el mechon ha mejorado el martillo chillon\n";
            std::cout << "actualizacion de dano: " << ataque_mechon << " -> " << ataque_mechon + 1 << "\n";
            ataque_mechon++;
            enemigos_derrotados_prev = (int)floor(enemigos_derrotados);
        }

        std::string tipoNombre = actual.tipo_enemigo == 0 ? "esbirro" : actual.tipo_enemigo == 1 ? "CANO" : "Mini-CANO";

        std::cout << "------------------------\nEl siguiente enemigo es un " << tipoNombre << " y tiene los siguientes stats:\n";
        std::cout << "Vida: " << actual.vida_enemigo << ", Ataque: " << actual.ataque_enemigo << ", Tipo: " << actual.tipo_enemigo << std::endl;

        bool enemigo_dividido = false;

        while (actual.vida_enemigo > 0 && vida_mechon > 0) {
            turno++;
            std::cout << "------------------------\nTurno " << turno << "\n------------------------\n";
            std::cout << "El mechon ataca con " << ataque_mechon << " de dano\n";

            int vida_anterior = actual.vida_enemigo;
            actual.vida_enemigo -= ataque_mechon;
            if (actual.vida_enemigo < 0) actual.vida_enemigo = 0;

            std::cout << "Vida del enemigo: " << vida_anterior << " -> " << actual.vida_enemigo << std::endl;

            if (actual.vida_enemigo > 0) {
                int vida_anterior_mechon = vida_mechon;
                std::cout << "El " << tipoNombre << " contra-ataca, haciendo " << actual.ataque_enemigo << " de dano\n";
                vida_mechon -= actual.ataque_enemigo;
                std::cout << "Vida del mechon: " << vida_anterior_mechon << " -> " << vida_mechon << std::endl;
            }

            // División de CANO
            if (actual.tipo_enemigo == 1) {
                cantidad_golpes_cano++;
                if (cantidad_golpes_cano == 2 && actual.vida_enemigo > 0) {
                    while (mini_canos_derrotados < 2 && vida_mechon > 0){
                        turno++;
                        std::cout << "------------------------\nTurno " << turno << "\n------------------------\n";
                        std::cout << "El mechon ataca con " << ataque_mechon << " de dano\n";
                        
                        if (!enemigo_dividido && actual.vida_enemigo <= 0) {
                            if (actual.tipo_enemigo == 2) enemigos_derrotados += 0.5f;
                            else enemigos_derrotados += 1.0f;
                    }
                }
            }
        }

        if (!enemigo_dividido && actual.vida_enemigo <= 0) {
            if (actual.tipo_enemigo == 2) enemigos_derrotados += 0.5f;
            else enemigos_derrotados += 1.0f;

            std::cout << "------------------------\nEl " << tipoNombre << " ha sido derrotado.\n";
            std::cout << "Enemigos derrotados: " << enemigos_derrotados << "/" << cantidad_enemigos << "\n";
        }
    }

        std::cout << "------------------------\n\nFIN DE LA BATALLA\n";
        if (vida_mechon > 0) {
            std::cout << "El mechon ha sobrevivido con " << vida_mechon << " de vida!\nLARGA VIDA A OLOGNIA\n\n";
        } else {
            std::cout << "El mechon ha sido derrotado.\nOLOGNIA ESTA A LA MERCED DEL ENEMIGO\nQUE DIOS NOS AMPARE\n\n";
        }

        return 0;
    }
}