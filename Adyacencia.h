/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Adyacencia.h
 * Author: Alan
 *
 * Created on 7 de febrero de 2018, 04:49 PM
 */

#ifndef ADYACENCIA_H
#define ADYACENCIA_H

class Adyacencia {
public:
    Adyacencia();
    Adyacencia(double cf, double v);
    Adyacencia(const Adyacencia& orig);
    ~Adyacencia();
    
    /* MÉTODOS OBTENEDORES */
    double obtCntFerormona() const;
    double obtValoracion() const;
    
    /* MÉTODOS ASIGNADORES */
    void asgCntFerormona(double cfn);
    void asgValoracion(double vn);
    
private:
    double cntFerormona;
    double valoracion;
};

#endif /* ADYACENCIA_H */

