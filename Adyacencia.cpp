/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Adyacencia.cpp
 * Author: Alan
 * 
 * Created on 7 de febrero de 2018, 04:49 PM
 */

#include "Adyacencia.h"

Adyacencia::Adyacencia() : cntFerormona(0.0), valoracion(0.0) {
}

Adyacencia::Adyacencia(double cf, double v) : cntFerormona(cf), valoracion(v) {
}

Adyacencia::Adyacencia(const Adyacencia& orig) : cntFerormona(orig.cntFerormona), valoracion(orig.valoracion) {
}

Adyacencia::~Adyacencia() {
}

/* MÉTODOS OBTENEDORES */
double Adyacencia::obtCntFerormona() const {
    return cntFerormona;
}

double Adyacencia::obtValoracion() const {
    return valoracion;
}

/* MÉTODOS ASIGNADORES */
void Adyacencia::asgCntFerormona(double cfn) {
    cntFerormona = cfn;
}

void Adyacencia::asgValoracion(double vn) {
    valoracion = vn;
}
