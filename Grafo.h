/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Grafo.h
 * Author: Alan
 *
 * Created on 5 de febrero de 2018, 05:49 PM
 */

#ifndef GRAFO_H
#define GRAFO_H

#include <fstream>
#include <vector>
#include <list>
#include <unordered_map>
#include <stack>
#include <algorithm>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <climits>

#include <iostream>     // std::cout, std::ios
#include <sstream>      // std::ostringstream
using namespace std;

#include "error_grafo.h"


template < typename V, typename A >
class Grafo {
    // Representa un grafo con vértices de tipo V y adyacencias de tipo A.
    /* SUPUESTOS:
     * 1. Los vértices son identificados con números de 0 a N-1, dada N la cantidad
     * total de vértices.
     * 2. El tipo V tiene definido su constructor estándar V().
     * 3. El tipo V tiene definido su constructor de copias V(const V& orig);
     * 4. El tipo A tiene definido su constructor estándar A().
     * 5. El tipo A tiene definido su constructor de copias A(const A& orig);
     */

public:
    /* CONSTRUCTORES */

    // REQ: cantidadVrt > 0. En este caso, N es igual a cantidadVrt.
    // REQ: 0 < probabilidadAdy < 1.
    // Construye un grafo con cantidadVrt de vértices en el que el conjunto de
    // adyacencias se determina aleatoriamente utilizando probabilidadAdy. Esto
    // implica que la probabilidad de que un arco exista entre cualesquiera dos
    // dos vértices es igual a probabilidadAdy
    Grafo(int cantidadVrt, double probabilidadAdy);

    // Construye una red con base en los datos en el archivo.
    // El archivo debe ser de texto (extensión txt) con datos separados por comas.
    // En la primera línea aparecerá un entero que representa la cantidad N de vértices.
    // Los vértices tienen un índice que va de 0 a N-1.
    // Luego en cada línea aparecerán los índices de los vértices asociados o
    // adyacentes, a cada vértice: 0, 1...N-1.
    // NOTA: todos los vértices son inicializados con V().
    Grafo(ifstream& archivo);

    // Construye una copia idéntica a orig.
    Grafo(const Grafo< V, A >& orig);

    // Destructor
    ~Grafo();

    /* MÉTODOS OBSERVADORES BÁSICOS */

    // EFE: retorna true si 0 <= idVrt < N.
    // NOTA: idVrt significa "identificador de vértice".
    bool xstVrt(int idVrt) const;

    // REQ: 0 <= idVrtO < N && 0 <= idVrtD < N.
    // EFE: retorna true si existe adyacencia entre los vértices idVrtO e idVrtD.
    bool xstAdy(int idVrtO, int idVrtD)const ;

    // REQ: 0 <= idVrt < N.
    // EFE: retorna en "rsp" los identificadores idVrtj de todos los vértices 
    // adyacentes a idVrt en el grafo.
    void obtIdVrtAdys(int idVrt, vector< int >& rsp) const throw( error_grafo );

    // REQ: 0 <= idVrt < N.
    // EFE: retorna el vértice con índice idVrt.
    // NOTA: retorna por valor para que NO pueda ser modificado.
    V operator[](int idVrt) const throw( error_grafo );

    // REQ: 0 <= idVrt1 < N && 0 <= idVrt2 < N
    // EFE: retorna los datos de la adyacencia entre <idVrtO, idVrtD>.
    // NOTA: retorna por valor para que NO pueda ser modificado.    
    A obtDatoAdy(int idVrtO, int idVrtD) const throw( error_grafo );

    // EFE: retorna el total de arcos o adyacencias en el grafo.
    int obtTotAdy() const;

    // EFE: retorna el total de vértices en el grafo.
    int obtTotVrt() const;

    /* MÉTODOS OBSERVADORES NO BÁSICOS*/

    // REQ: 0 <= idVrt1 < N && 0 <= idVrt2 < N
    // EFE: retorna en "camino" los índices de los vértices que conforman el
    //      camino más corto entre idVrtO y idVrtD.
    int caminoMasCorto(int idVrtO, int idVrtD, vector< int >& camino) const throw( error_grafo );

    /* MÉTODOS MODIFICADORES BÁSICOS */

    // REQ: 0 <= idVrt < N.
    // EFE: retorna el vértice con índice idVrt.
    // NOTA: retorna por referencia para que pueda ser modificado en el contexto
    // invocador.
    V& operator[](int idVrt) throw( error_grafo );

    // REQ: 0 <= idVrt1 < N && 0 <= idVrt2 < N
    // EFE: asigna el valor "a" a la adyacencia <idVrtO, idVrtD>.
    void asgDatoAdy(int idVrtO, int idVrtD, const A& a);

private:

    template < typename W >
    struct Vrt {
        W w;
        list< int > lstAdy;

        Vrt< W >() : w(W()), lstAdy() {
        }; // constructor estándar de Vrt

        Vrt< W >(const W& ww) : w(ww), lstAdy() {
        }; // constructor con dato de vértice

        Vrt< W >(const Vrt< W >& vrt) : w(vrt.w), lstAdy(vrt.lstAdy) {
        }; // constructor de copias de Vrt
    };

    // REQ: (f >= 0) && (c >= 0) && (N > 0)
    // RET: valor único asociado a f y c con base en N = vectorVrts.size().

    static long fIdUnico(int f, int c, int N) {
        if (f > c) {
            int t = f;
            f = c;
            c = t;
        }
        return f * N + c - f * (f + 1) / 2;
    };

    vector< Vrt< V > > vectorVrts;                                          // vector de vértices
    unordered_map< long, A > mapAdys;                                       // map basado en hashing de adyacencias
};

template < typename V, typename A >
Grafo< V, A >::Grafo(int cantidadVrt, double probabilidadAdy) {
    if( ( cantidadVrt > 0 ) && ( ( probabilidadAdy > 0.0) && ( probabilidadAdy < 1.0 ) ) ){
        vectorVrts.resize(cantidadVrt);                                     //le da tamaño al vector de vértices
        mapAdys.reserve( ( cantidadVrt *(cantidadVrt-1) ) / 2 );
        A adys;                                                             //crea el objeto adyacencia
        double numeroAleatorio = 0.0;                                       //inicializa en 0.
        srand(time(NULL));
        for (int i = 0; i < cantidadVrt; i++) {                             //para cada vértice del laberinto
            for (int j = i + 1; j < cantidadVrt; j++) {                     //en cada posible adyacencia.
                numeroAleatorio = (rand() % 1000 + 1) / 1000.0;             //genera un número aleatorio entre 0 y 1.
                if (numeroAleatorio <= probabilidadAdy) {                   //si es menor o igual a la probabilidad.
                    mapAdys.insert( typename unordered_map< long, A >::value_type( fIdUnico(i,j,vectorVrts.size()), adys ));//agrega la adyacencia entre ambos vértices.
                    vectorVrts[i].lstAdy.push_back(j);                      //agrega j como adyacencia de i.
                    vectorVrts[j].lstAdy.push_back(i);                      //agrega i como adyacencia de j.
                }
            }
        }
    }
}

template < typename V, typename A >
Grafo< V, A >::Grafo(ifstream& archivo) {
    string hileraActual;                                                    //hilera actual.
    getline(archivo, hileraActual);                                         //lee la primer línea del archivo y la agrega a la hileraActual
    int cntVrts = stoi(hileraActual);                                       //convierte la hileraActual en un entero que representa la cantidad  de vértices.
    A adys;                                                                 //crea objeto adyacencia.
    vectorVrts.resize(cntVrts);                                             //le da tamaño al vector de vértices.
    mapAdys.reserve( ( cntVrts *(cntVrts-1) ) / 2 );
    int numeroDeAdyacencia;                                                 //entero temporal para vértices adyacentes.
    string hileraTemporal = "";                                             //hilera temporal de cada vértice adyacente.
    int numeroDeLinea = 0;                                                  //número de línea en el archivo.
    while (getline(archivo, hileraActual)) {                                //recorre el archivo hasta el final.
        int i = 0;                                                          //índice en la hileraActual.
        while (hileraActual[i] != '\r') {                                   //recorre la hileraActual hasta el final de la línea.
            if (hileraActual[i] != ' ') {                                   //si no ha llegado a un blanco,
                hileraTemporal += hileraActual[i];                          //copia el número en la hilera temporal.
            } else {                                                        //cuando encuentra un blanco, agrega la adyacencia entre el vértice numeroDeLinea y el vértice que hay en hileraTemporal.
                numeroDeAdyacencia = stoi(hileraTemporal);
                hileraTemporal = "";
                mapAdys.insert( typename unordered_map< long, A >::value_type( fIdUnico(numeroDeLinea,numeroDeAdyacencia,vectorVrts.size()), adys) );
                vectorVrts[numeroDeLinea].lstAdy.push_back(numeroDeAdyacencia);
            }
            i++;
        }
        numeroDeLinea++;
    }
}

template < typename V, typename A >
Grafo< V, A >::Grafo(const Grafo< V, A >& orig) {
    int cntVrts = orig.vectorVrts.size();
    vectorVrts.reserve(cntVrts);
    vectorVrts = orig.vectorVrts;
    mapAdys = orig.mapAdys;
}

template < typename V, typename A >
Grafo< V, A >::~Grafo() {
}

template < typename V, typename A >
bool Grafo< V, A >::xstVrt(int idVrt) const {
    bool existencia = false;
    if ( (0<=idVrt) && (idVrt<vectorVrts.size()) ){
        existencia = true;
    }
    return existencia;
}

template < typename V, typename A >
bool Grafo< V, A >::xstAdy(int idVrtO, int idVrtD) const {
    bool adyacencia = false;
    if ((xstVrt(idVrtO)) && (xstVrt(idVrtD))) {                             //si ambos vértices existen,                                  //busca si hay adyacencia entre el vértice origen y el destino.
        for (auto current: vectorVrts[idVrtO].lstAdy ){                     //recorre la lista de adyacencias del vértice origen.
            if (idVrtD == current){                                         //si encuentra el vértice destino,
                adyacencia = true;                                          //asigna true.
            }
        }
    }
    return adyacencia;
}

template < typename V, typename A >
void Grafo< V, A >::obtIdVrtAdys(int idVrt, vector< int >& rspRetornar) const throw( error_grafo ){
    if (xstVrt(idVrt)) {                                                    //si existe el vértice,
        for (auto current: vectorVrts[idVrt].lstAdy ){                      //recorre su lista de adyacencias
            rspRetornar.push_back(current);                                 //agregando cada una al vector rsp.
        } 
    }else{
        ostringstream errorSalida;
        errorSalida << idVrt;
        throw error_grafo(1, errorSalida.str());
    }
}

template < typename V, typename A >
V Grafo< V, A >::operator[](int idVrt) const throw( error_grafo ) {
    V vertice;
    if(xstVrt(idVrt)){
        vertice = vectorVrts[idVrt];
    }else{
        ostringstream errorSalida;
        errorSalida << idVrt;
        throw error_grafo(1, errorSalida.str());
    }
    return vertice;
}

template < typename V, typename A >
A Grafo< V, A >::obtDatoAdy(int idVrtO, int idVrtD) const throw( error_grafo ){
    A result;
    if ((xstVrt(idVrtO)) && (xstVrt(idVrtD))){                              //si existen ambos vértices,
        if ( xstAdy(idVrtO, idVrtD) ) {                                     //y si existe adyacencia entre ambos.
            long k = fIdUnico( idVrtO, idVrtD, vectorVrts.size() );         //obtiene la clave,
            result = mapAdys.at(k);                                         //y devuelve el objeto ady de la clave k.
        }
    }else{
        ostringstream errorSalida;
        errorSalida << idVrtO;
        errorSalida <<  " y ";
        errorSalida << idVrtD;
        throw error_grafo(2, errorSalida.str());
    }
    return result;
}

template < typename V, typename A >
int Grafo< V, A >::obtTotAdy() const {
    int cntTtlAdy = 0;
    for (int i = 0; i < vectorVrts.size(); i++) {                           //obtiene la cantidad total de adyacencias, sumandolas vértice por vértice.
        cntTtlAdy += vectorVrts[i].lstAdy.size();
    }
    return cntTtlAdy;
}

template < typename V, typename A >
int Grafo< V, A >::obtTotVrt() const {
    return vectorVrts.size();
}

template < typename V, typename A >
V& Grafo< V, A >::operator[](int idVrt) throw( error_grafo ) {
    V& vertice;
    if(xstVrt(idVrt)){
        vertice = vectorVrts[idVrt];
    }
    else{
        ostringstream errorSalida;
        errorSalida << idVrt;
        throw error_grafo(1, errorSalida.str());
    }
    return vertice;
}

template < typename V, typename A >
int Grafo< V, A >::caminoMasCorto(int idVrtO, int idVrtD, vector< int >& camino) const throw( error_grafo ){
    int size = -1;                                                          //inicializa el tamaño del camino más corto en inválido.
    if (xstVrt(idVrtO) && xstVrt(idVrtD)) {                                 //verifica la existencia de ambos vértices.
        int cntVrts = vectorVrts.size();                                    //variable para saber la cantidad de vértices del laberinto.
        int distancia[cntVrts];                                             //distancias de los caminos más cortos.
        bool visto[cntVrts];                                                //para controlar los vértices visitados.
        for (auto& currentElement: visto) {                                 //inicializa el arreglo visto en false
           currentElement = false;
        }
        int antecesores[cntVrts];                                           //arreglo de antecesores.
        for (int i = 0; i < cntVrts; i++) {                                 //recorre todos los vérties.
            if (!xstAdy(idVrtO, i)) {                                       //si no existe adyacencia con el vértice origen,
                distancia[i] = INT_MAX;                                     //asigna infinito.
                antecesores[i] = -2;                                        //y un antecesor inválido.
            } else {                                                        //en el caso de que si exista adyacencia
                distancia[i] = 1;                                           //asigna peso 1
                antecesores[i] = idVrtO;                                    //y asigna antecesor el vértice origen.
            }
        }
        distancia[idVrtO] = 0;                                              //invalida el vértice origen y lo pone visitado
        antecesores[idVrtO] = -1;
        visto[idVrtO] = true;

        while (visto[idVrtD] == false) {                                    //mientras no estén todos en visto.
                                                                            //encuentra el menor del arreglo distancia y que no esté visto:
            int verticeMinimo = 0;                                          //lo inicializa en 0.
            while( visto[verticeMinimo] ){                                  //y encuentra el primer vértice no visitado.
                verticeMinimo++;
            }
            for (int m = 0; m < cntVrts; m++) {                             //encuentra si hay algún vértice menor no visitado.
                if ( ( !visto[m] ) && ( distancia[m] < distancia[verticeMinimo] ) ) {
                    verticeMinimo = m;                                      //y lo asigna.
                }
            }
            
            visto[verticeMinimo] = true;                                    //pone en visitado el vértice minimo.
            
            list<int> sucesores = vectorVrts[verticeMinimo].lstAdy;         //al vector sucesores le asigna la lista de adyacencias del vértice minimo.
            for (int& current: sucesores){                                  // sucesores[j] = current
                if( distancia[current] > ( distancia[verticeMinimo] + 1 ) ){//si el nuevo peso es menor.
                    distancia[current] = distancia[verticeMinimo] + 1;      //asigna el nuevo peso.
                    antecesores[current] = verticeMinimo;                   //y cambia el antecesor.
                }
            }
        }
        
        //recorre el camino más corto, desde el vértice destino hasta el vértice origen agregándolo en caminoTemp
        int k = idVrtD;
        vector<int> caminoTemp;                                             //donde se almacenatá el camino más corto temporalmente.
        while( antecesores[k] != -1){                                       //mientras no llegue al primer vértice.
            caminoTemp.push_back(k);                                        //agregue el último del camino más corto.
            k = antecesores[k];                                             //cambia el último por el antecesor de este.
        }
        caminoTemp.push_back(idVrtO);                                       //agrega el vértie origen.
        size = distancia[idVrtD];                                           //distancia del camino más corto.
        
        for (int i = caminoTemp.size(); i > 0 ; i--){                       //le da vuelta y lo agrega en camino.
            camino.push_back( caminoTemp.at(i-1) );
        }
    }else{
        ostringstream errorSalida;
        errorSalida << idVrtO;
        errorSalida <<  " y ";
        errorSalida << idVrtD;
        throw error_grafo(3, errorSalida.str());
    }
    return size;
}

template < typename V, typename A >
void Grafo< V, A >::asgDatoAdy(int idVrtO, int idVrtD, const A& a) {
    if( (xstVrt(idVrtO)) && (xstVrt(idVrtD)) ){                             //si existen ambos vértices,
        if(xstAdy(idVrtO,idVrtD)){
            long clave = fIdUnico(idVrtO, idVrtD, vectorVrts.size());
            mapAdys[clave] = a;                                             //asigna el dato de adyacencia.
        }
    }
}
#endif /* GRAFO_H */

