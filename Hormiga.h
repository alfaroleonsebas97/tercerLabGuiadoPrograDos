/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Hormiga.h
 * Author: Alan
 *
 * Created on 7 de febrero de 2018, 05:53 PM
 */

#ifndef HORMIGA_H
#define HORMIGA_H

#include <stdlib.h>     /* para srand, rand al moverse*/
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

#include "Laberinto.h"

class Hormiga {
public:
    
    // EFE: construye un hormiga en el nido y con destino == nodoFinal.
    Hormiga();
    
    // EFE: construye una copia idéntica e independiente de orig.
    Hormiga(const Hormiga& orig);
    
    virtual ~Hormiga();

    /* MÉTODOS OBSERVADORES */
    
    // EFE: retorna true si la hormiga ya salió al laberinto.obtIdVrtInicial().
    bool salio();
    
    // EFE: retorna true si la hormiga ya regresó al laberinto.obtIdVrtFinal().
    bool regreso();
    
    // EFE: retorna 'F' o 'I' para indicar el destino de la hormiga.
    char obtDestino();
    
    // EFE: retorna una hilera con la memoria de la hormiga.
    // EJEMPLO: "[2,6,7,12,54]" indicaría que la hormiga salió por 2 y viajó en
    // el orden de la secuencia hasta 54.
    string obtMemoria();

    /* MÉTODOS MODIFICADORES */

    // EFE: activa la hormiga y la ubica en laberinto.obtIdVrtInicial().
    void salir();

    // REQ: que la hormiga (*this) esté activa.
    // EFE: la hormiga avanza a un vértice adyacente al que está en el laberinto.
    void mover();
    
    // EFE: asigna la referencia al laberinto que accesarán todas las hormigas.
    static void asgLaberinto(Laberinto& lbrt);
    
private:

    /* ATRIBUTOS ESTÁTICOS PRIVADOS ACCESIBLES POR TODAS LAS HORMIGAS */
    static Laberinto* laberinto_p; // puntero a laberinto
    
    //EFE: retrocede n veces(n=random entre 1 y memoria.size()-1) en el laberinto.
    void retroceder();
    
    // EFE: retorna -1 en caso de que la hormiga llegue a camino sin salida,
    // y un idVrt válido en caso de que la hormiga pueda continuar.
    int seleccionaAdyMasCargada();

    /* MÉTODOS AUXILIARES */
    // REQ: que los idVrt en vrtsPosibles sean índices válidos de vértices en el laberinto que está recorriendo la hormiga.
    // EFE: elimina de vrtsPosibles los idVrt que ya aparecen en la memoria.
    void filtraVrtsPosibles(vector<int> &vrtsPosibles);
    
    /* ATRIBUTOS PRIVADOS OBLIGATORIOS */
    vector<int> memoria; // vector de idVrt que representa el recorrido de la hormiga
    int idVrtActual; // idVrt del vértice donde se encuentra la hormiga actualmente    
    bool haSalido; // false mientras no haya salido, true si ya salió
    bool haRegresado; // false mientras no haya regresado de idVrtFinal a idVrtInicial
    char destino; // 'F' o 'I', indica hacia adónde se dirige la hormiga
    int enRetroceso; // si es mayor a cero, la hormiga está retrocediendo esta cantidad de pasos porque topó con un camino sin salida o un ciclo-
    int longitudSolucion; // registra la longitud de la solución encontrada para moderar su aporte de ferormona en su retorno
    double deltaFerormona; // representa cuánta ferormona aporta la hormiga a cada link y se calcula como 1 / longitudSolucion.
};
#endif /* HORMIGA_H */


