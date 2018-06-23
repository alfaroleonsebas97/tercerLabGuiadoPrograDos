/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Laberinto.cpp
 * Author: Alan
 * 
 * Created on 7 de febrero de 2018, 04:46 PM
 */

#include "Laberinto.h"

Laberinto::Laberinto(int cantidadVrts, double probabilidadAdy): laberintoPtr(shared_ptr< Grafo< int, Adyacencia > >(new Grafo< int, Adyacencia >(cantidadVrts,probabilidadAdy))),laberinto(*laberintoPtr) {
}

Laberinto::Laberinto(ifstream& archivo): laberintoPtr(shared_ptr< Grafo< int, Adyacencia > >(new Grafo< int, Adyacencia >(archivo))),laberinto(*laberintoPtr) {
}

Laberinto::Laberinto(const Laberinto& orig): laberintoPtr(shared_ptr< Grafo< int, Adyacencia > >(new Grafo< int, Adyacencia >(orig.laberinto))),laberinto(*laberintoPtr) {
}

Laberinto::~Laberinto() {
}

/* MÉTODOS OBSERVADORES BÁSICOS */
bool Laberinto::xstVrt(int idVrt) const {
    return laberinto.xstVrt(idVrt);
}

bool Laberinto::xstAdy(int idVrtO, int idVrtD) const {
    return laberinto.xstAdy(idVrtO,idVrtD);
}

int Laberinto::obtIdVrtInicial() const {
    return idVrtInicial;
}

int Laberinto::obtIdVrtFinal() const {
    return idVrtFinal;
}

void Laberinto::obtIdVrtAdys(int idVrt, vector< int >& rsp) const {
    try{
        laberinto.obtIdVrtAdys(idVrt,rsp);   
    } catch(error_grafo error){
        cout << error.what() << endl;
    }
}

Adyacencia Laberinto::obtDatoAdy(int idVrtO, int idVrtD) const {
    try{
        return laberinto.obtDatoAdy(idVrtO,idVrtD);   
    } catch(error_grafo error){
        cout << error.what() << endl;
    }
}

int Laberinto::obtTotAdy() const {
   return laberinto.obtTotAdy();
}

int Laberinto::obtTotVrt() const {
    return laberinto.obtTotVrt();
}

int Laberinto::caminoMasCorto(int idVrtO, int idVrtD, vector< int >& camino) const {
    try{
        return laberinto.caminoMasCorto(idVrtO,idVrtD,camino);
    } catch(error_grafo error){
        cout << error.what() << endl;
    }
}

int Laberinto::caminoEncontrado(int idVrtO, int idVrtD, vector<int>& camino) const {
    int longitud = 0;
    if( xstVrt(idVrtO) && xstVrt(idVrtD) ){                                 //si existe ambos vértices.
        int verticeActual = idVrtO;
        int verticeAdy;
        vector<int> vecAdy;
        bool encontrado = false;
        double cntFerormona;
        camino.push_back(verticeActual);                                    //Agrega el vertice origen al camino
        while(!encontrado){                                                 //Mientras no haya encontrado el vertice destino
            obtIdVrtAdys(verticeActual,vecAdy);                             //Encuentra los adyacentes del vertice actual
            cntFerormona = 0.0;
            for(auto current: vecAdy){                                      //Busca el vertice destino en la lista de adyacentes
                if(current==idVrtD){                                        //Si lo encontró
                    encontrado=true;                                        //Encontrado es verdadero
                    camino.push_back(current);                              //Lo agrega al camino
                    longitud++;                                             //Aumenta la longitud del camino encontrado
                }
            }
            if(!encontrado){                                                //Si no lo ha encontrado
                for(int i = 0 ;i < vecAdy.size(); i++ ){                    //Busca el adyacente con mayor ferormona
                    if( ( obtDatoAdy(verticeActual,vecAdy[i]).obtCntFerormona() >= cntFerormona )&& ( find( camino.begin(),camino.end(),vecAdy[i]) == camino.end() ) ){
                        verticeAdy = vecAdy[i];
                        cntFerormona = obtDatoAdy(verticeActual,vecAdy[i]).obtCntFerormona();
                    }
                }
                verticeActual=verticeAdy;                                   //Una vez encontrado se mueve de vértice
                camino.push_back(verticeActual);                            //Lo agraga al camino
                longitud++;                                                 //Aumenta la longitud del cmaino encontrado
            }
        }
    }
    
    return longitud;                                                        //Retorna la longitud del camino encontrado.
}

double Laberinto::sumaTotalFerormona() const {
    double suma = 0.0;
    vector<int> vec;
    for(int i = 0; i < laberinto.obtTotVrt(); i++){
        obtIdVrtAdys(i,vec);
        for(auto current: vec){
            suma += obtDatoAdy(i,current).obtCntFerormona();
        }
        vec.clear();
    }
    return suma;
}

void Laberinto::asgVrtInicial(int idVrtInicialN) {
    idVrtInicial = idVrtInicialN;
}

void Laberinto::asgVrtFinal(int idVrtFinalN) {
   idVrtFinal = idVrtFinalN;
}

void Laberinto::asgDatoAdy(int idVrtO, int idVrtD, const Adyacencia& ady) {
    laberinto.asgDatoAdy( idVrtO, idVrtD, ady );
}

void Laberinto::decrementarFerormonaAdys(double decrFerormona) {
    vector<int> rsp;
    for( int i = 0; i < laberinto.obtTotVrt(); i++ ){
        obtIdVrtAdys(i,rsp);
        for( auto current: rsp){
            obtDatoAdy(i,current).asgCntFerormona((laberinto.obtDatoAdy(i,current).obtCntFerormona()) * (decrFerormona));
        }
    }
}

void Laberinto::actualizarValoracionAdys() {
    vector<int> rsp;
    for( int i = 0; i < laberinto.obtTotVrt(); i++ ){
        obtIdVrtAdys(i,rsp);
        for( auto current: rsp){
            obtDatoAdy(i,current).asgValoracion((laberinto.obtDatoAdy(i,current).obtCntFerormona()) / (sumaTotalFerormona()));
        }
    }
}