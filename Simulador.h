/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Simulador.h
 * Author: Alan
 *
 * Created on 19 de febrero de 2018, 02:53 PM
 */

#ifndef SIMULADOR_H
#define SIMULADOR_H

#include <algorithm>    // std::count_if
#include <vector>
#include <time.h>       /* time para randomizar moviento al azar de las horimgas */
using namespace std;

#include "Laberinto.h"
#include "Hormiga.h"

class Simulador {
public:
    // EFE: construye un simulador de hormiguero para resolver el laberinto "lbr".
    Simulador(Laberinto& lbr);
    
    // EFE: construye una copia idéntica e independiente de orig.
    Simulador(const Simulador& orig);
    
    virtual ~Simulador();
    
    // REQ: laberinto.xstVrt(nodoInicial) && laberinto.xstVrt(nodoFinal).
    // MOD: *this.
    // EFE: inicia los parámetros: 
    // idVrtInicial: ubicación del nido de las hormigas, 
    // idVrtFinal: ubicación destino de las hormigas,
    // cntHrm: cantidad total de hormigas en el hormiguero,
    // decrFerormona: cuánto decrece la ferormona de las adyacencias con cada paso,
    // probMovmientoAzar: probabilidad de que una hormiga se mueva al azar en vez de escoger la adyacencia más cargada de ferormona.
    void iniciar(int idVrtInicial, int idVrtFinal, int cntHrm, double decrFerormona, double probMovimientoAzar);
    
    // REQ: p >= 1;
    // MOD: *this cambiando el estado del simulador y el laberinto.
    // EFE: ejecuta p pasos de simulación.    
    void ejecutar(int p);
    
private:
    
    Laberinto& laberinto;
    vector< Hormiga > hormigas;
    double decrFerormona;
    double probMovimientoAzar;
};

#endif /* SIMULADOR_H */

