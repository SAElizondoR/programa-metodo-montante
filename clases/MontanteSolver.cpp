//
// Created by sergio on 22/08/21.
//

#include "MontanteSolver.h"

// constructor que recibe de parámetro un vector “matriz”
MontanteSolver::MontanteSolver(std::vector<std::vector<float>> &matriz) {
    this->matriz = matriz; // inicializa matriz
    // los renglones van a ser igual al tamaño de la matriz
    numero_renglones_matriz = int(matriz.size());
    // inicializamos pivote anterior y actual
    pivote_anterior = 1;
    pivote_actual = 1;
}

std::vector<float> MontanteSolver::resolver() {
    // variable bandera
    bool pivote_es_cero = false;
    // for que se mueve hasta que se acaben los renglones, para verificar todos los pivotes de la diagonal principal
    for (int indice_pivote = 0; indice_pivote < numero_renglones_matriz; ++indice_pivote) {
        // obtenemos el pivote anterior *en la primera iteración 1=1*
        pivote_anterior = pivote_actual;
        // pivote actual va a ser igual al pivote con el que se empiece a trabajar *siempre la diagonal*
        pivote_actual = matriz.at(indice_pivote).at(indice_pivote);
        // entra si el pivote es igual a 0
        if (pivote_actual == 0) {
            // bandera = true
            pivote_es_cero = true;
            // comienza un for desde un renglón abajo hasta que se terminen los renglones
            for (int indice_intercambio = indice_pivote + 1; indice_intercambio < numero_renglones_matriz;
            ++indice_intercambio) {
                // índice_intercambio empieza en el renglón de abajo y el índice de pivote es el de arriba
                // quiere decir que, si el pivote de la posición siguiente es diferente de 0, entra al if
                if (matriz.at(indice_intercambio).at(indice_pivote) != 0) {
                    // como es diferente de 0 cambia el renglón con el método cambiar_ren
                    cambiar_ren(indice_pivote, indice_intercambio);
                    // el pivote va a ser diferente de 0, por lo que ahora el pivote_es_cero se hace falso
                    pivote_es_cero = false;
                    //termina este for
                    break;
                }
            }
        }
        // si cae en este caso es porque toda la columna esta llena de 0´s
        // si el pivote sigue siendo 0 porque no se encontró otro diferente de este
        if (pivote_es_cero) {
            // tiene soluciones infinitas ya que son dependientes o no tiene solución
            return {};
        }
        // Calculamos los valores para la parte superior derecha a excepción los que están arriba del pivote
        for (int indice_ren = 0; indice_ren < indice_pivote; ++indice_ren) {
            for (int indice_col = indice_pivote + 1; indice_col < numero_renglones_matriz + 1; ++indice_col) {
                multiplicar_en_cruz(indice_pivote, indice_ren, indice_col);
            }
        }
        // Calculamos los valores para la parte inferior derecha a excepción los que están abajo del pivote
        for (int indice_ren = indice_pivote + 1; indice_ren < numero_renglones_matriz; ++indice_ren) {
            for (int indice_col = indice_pivote + 1; indice_col < numero_renglones_matriz + 1; ++indice_col) {
                multiplicar_en_cruz(indice_pivote, indice_ren, indice_col);
            }
        }
        // va cambiando la diagonal principal por el pivote actual con el que estamos trabajando
        for (int indice = 0; indice < indice_pivote; ++indice) {
            matriz.at(indice).at(indice) = pivote_actual;
        }
        // Llena de 0´s arriba del pivote
        for (int indice_ren = 0; indice_ren < indice_pivote; ++indice_ren) {
            matriz.at(indice_ren).at(indice_pivote) = 0;
        }
        // Llena de 0´s abajo del pivote
        for (int indice_ren = indice_pivote + 1; indice_ren < numero_renglones_matriz; ++indice_ren) {
            matriz.at(indice_ren).at(indice_pivote) = 0;
        }
    }
    std::vector<float> respuesta;
    respuesta.reserve(numero_renglones_matriz);
    // imprime las raíces
    for (int i = 0; i < numero_renglones_matriz; ++i) {
        respuesta.push_back(matriz.at(i).at(numero_renglones_matriz) / matriz.at(i).at(i));
    }

    return respuesta;
}

// método para cambiar renglones
// recibe índice_pivote e índice_intercambio respectivamente
void MontanteSolver::cambiar_ren(int a, int b) {
    float temp;
    // desde 0 hasta el número de renglones
    for (int i = 0; i < numero_renglones_matriz + 1; ++i) {
        // temp toma el valor del renglón de abajo
        temp = matriz.at(a).at(i);
        // se cambia el valor de abajo con el de arriba
        matriz.at(a).at(i) = matriz.at(b).at(i);
        // el valor de abajo se cambia por el de arriba
        matriz.at(b).at(i) = temp;
    }
    pivote_actual = matriz.at(a).at(a);
}

// Calculamos los valores para la parte superior/inferior derecha dependiendo el ciclo
void MontanteSolver::multiplicar_en_cruz(int indice_pivote, int indice_ren, int indice_columna) {
    matriz.at(indice_ren).at(indice_columna) = (matriz.at(indice_ren).at(indice_columna) *
                                                matriz.at(indice_pivote).at(indice_pivote) - matriz.at(indice_ren).at(indice_pivote) *
            matriz.at(indice_pivote).at(indice_columna)) / pivote_anterior;
}
