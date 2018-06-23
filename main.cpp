/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: alan.calderon
 *
 * Created on 2 de abril de 2018, 10:31 AM
 */

#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

#include "Laberinto.h"
#include "Simulador.h"
#include "Hormiga.h"
/*
 * 
 */
int main(int argc, char** argv) {
    
    //Primera prueba con laberinto pequeño.
    ifstream archivo("laberintop.txt");
    if (archivo.is_open()) {
        vector<int> vecCamino;
        Laberinto laberinto(archivo);
        int verticeInicial = 0;
        int verticeFinal = 8;
        Simulador simulador(laberinto);
        simulador.iniciar(verticeInicial,verticeFinal,30,0.95,0.11);
        simulador.ejecutar(1000);
        int longitud = laberinto.caminoEncontrado(verticeInicial,verticeFinal,vecCamino);
        cout<<"Primer camino encontrado en el laberinto pequeño: "<<endl;
        for(auto current: vecCamino){
            cout<<current<<endl;
        }
        cout<<"El camino más corto es: "<<endl;
        vector<int>caminoMasCorto;
        laberinto.caminoMasCorto(verticeInicial,verticeFinal,caminoMasCorto);
        for(auto current: caminoMasCorto){
            cout<<current<<endl;
        }
        cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
        archivo.close();
    }

    
    //Segunda prueba con laberinto pequeño.
    ifstream archivo2("laberintop.txt");
    if (archivo2.is_open()) {
        vector<int> vecCamino2;
        Laberinto laberinto2(archivo2);
        int verticeInicial = 0;
        int verticeFinal = 8;
        Simulador simulador2(laberinto2);
        simulador2.iniciar(verticeInicial,verticeFinal,300,0.95,0.11);
        simulador2.ejecutar(10000);
        int longitud = laberinto2.caminoEncontrado(verticeInicial,verticeFinal,vecCamino2);
        cout<<"Segundo camino encontrado en el laberinto pequeño: "<<endl;
        for(auto current: vecCamino2){
            cout<<current<<endl;
        }
        cout<<"El camino más corto es: "<<endl;
        vector<int>caminoMasCorto2;
        laberinto2.caminoMasCorto(verticeInicial,verticeFinal,caminoMasCorto2);
        for(auto current: caminoMasCorto2){
            cout<<current<<endl;
        }
        cout<<"------------------------------------------------------------------"<<endl;
        archivo2.close();
    }
    
    
    //Primera prueba con laberinto mediano.
    ifstream archivo3("laberintom.txt");
    if (archivo3.is_open()) {
        vector<int> vecCamino3;
        Laberinto laberinto3(archivo3);
        int verticeInicial = 0;
        int verticeFinal = 35;
        Simulador simulador3(laberinto3);
        simulador3.iniciar(verticeInicial,verticeFinal,30,0.95,0.99);
        simulador3.ejecutar(1000);
        int longitud = laberinto3.caminoEncontrado(verticeInicial,verticeFinal,vecCamino3);
        cout<<"Primer camino encontrado en el laberinto mediano: "<<endl;
        for(auto current: vecCamino3){
            cout<<current<<endl;
        }
        cout<<"El camino más corto es: "<<endl;
        vector<int>caminoMasCorto3;
        laberinto3.caminoMasCorto(verticeInicial,verticeFinal,caminoMasCorto3);
        for(auto current: caminoMasCorto3){
            cout<<current<<endl;
        }
        cout<<"''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''"<<endl;
        archivo3.close();
    }
    
    
    //Segunda prueba con laberinto mediano.
    ifstream archivo4("laberintom.txt");
    if (archivo4.is_open()) {
        vector<int> vecCamino4;
        Laberinto laberinto4(archivo4);
        int verticeInicial = 0;
        int verticeFinal = 35;
        Simulador simulador4(laberinto4);
        simulador4.iniciar(verticeInicial,verticeFinal,300,0.95,0.99);
        simulador4.ejecutar(10000);
        int longitud = laberinto4.caminoEncontrado(verticeInicial,verticeFinal,vecCamino4);
        cout<<"Segundo camino encontrado en el laberinto mediano: "<<endl;
        for(auto current: vecCamino4){
            cout<<current<<endl;
        }
        cout<<"El camino más corto es: "<<endl;
        vector<int>caminoMasCorto4;
        laberinto4.caminoMasCorto(verticeInicial,verticeFinal,caminoMasCorto4);
        for(auto current: caminoMasCorto4){
            cout<<current<<endl;
        }
        cout<<"*********************************************************************"<<endl;
        archivo4.close();
    }
    
    //Prueba con vértices que no existen en laberinto pequeño.
    ifstream archivo5("laberintop.txt");
    if (archivo5.is_open()) {
        vector<int> vecCamino5;
        Laberinto laberinto5(archivo5);
        int verticeInicial = 0;
        int verticeFinal = 80;
        Simulador simulador5(laberinto5);
        simulador5.iniciar(verticeInicial,verticeFinal,30,0.95,0.11);
        simulador5.ejecutar(1000);
        int longitud = laberinto5.caminoEncontrado(verticeInicial,verticeFinal,vecCamino5);
        cout<<"Prueba del camino encontrado cuando no existe tal camino: "<<endl;
        for(auto current: vecCamino5){
            cout<<current<<endl;
        }
        cout<<"El camino más corto es: "<<endl;
        vector<int>caminoMasCorto5;
        laberinto5.caminoMasCorto(verticeInicial,verticeFinal,caminoMasCorto5);
        for(auto current: caminoMasCorto5){
            cout<<current<<endl;
        }
        cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
        archivo5.close();
    }
    return 0;
}

