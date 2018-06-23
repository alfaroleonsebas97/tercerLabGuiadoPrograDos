/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PbsHormiga.cpp
 * Author: alfar
 *
 * Created on 17 de mayo de 2018, 10:34 AM
 */

#include <stdlib.h>
#include <iostream>
#include "Hormiga.h"
#include "Adyacencia.h"

/*
 * Simple C++ Test Suite
 */


void testMover() {
    
    ifstream archivo("LaberintoPruebaCaminoSimple.txt");
    if (archivo.is_open()) {
        Laberinto lbrt(archivo);
        Adyacencia ady(10.0,0.0);
        lbrt.asgDatoAdy(0,1,ady);
        lbrt.asgDatoAdy(1,2,ady);
        lbrt.asgDatoAdy(2,3,ady);
        Hormiga hormiga;
        hormiga.asgLaberinto(lbrt);
        lbrt.asgVrtInicial(0);
        hormiga.salir();
        for (int i = 0; i < 4; i++) {
            hormiga.mover();
        }
        if ( "{0,1,2,3}" == hormiga.obtMemoria() ) {
            std::cout << "%TEST_FAILED% time=0 testname=testMover (PbsHormiga) message=La hormiga llegó a camino sin salida y no retrocedió" << std::endl;
        }
        archivo.close();
    }

    ifstream archivo2("LaberintoPruebaCaminoEnciclado.txt");
    if (archivo2.is_open()) {
        Laberinto lbrt(archivo2);
        Adyacencia ady(10.0,0.0);
        lbrt.asgDatoAdy(0,1,ady);
        lbrt.asgDatoAdy(1,2,ady);
        lbrt.asgDatoAdy(2,3,ady);
        Hormiga hormiga2;
        hormiga2.asgLaberinto(lbrt);
        lbrt.asgVrtInicial(0);
        hormiga2.salir();
        for (int i = 0; i < 4; i++) {
            hormiga2.mover();
        }
        if ( hormiga2.obtMemoria().size() >= 9  ) {
            std::cout << "%TEST_FAILED% time=0 testname=testMover (PbsHormiga) message=La hormiga se encicló y no retrocedió" << std::endl;
        }
        archivo2.close();
    }
    
    ifstream archivo3("LaberintoPruebaCaminoSimple.txt");
    if (archivo3.is_open()) {
        Laberinto lbrt(archivo3);
        Adyacencia ady(10.0,0.0);
        lbrt.asgDatoAdy(0,1,ady);
        lbrt.asgDatoAdy(1,2,ady);
        lbrt.asgDatoAdy(2,3,ady);
        Hormiga hormiga3;
        hormiga3.asgLaberinto(lbrt);
        lbrt.asgVrtInicial(0);
        lbrt.asgVrtFinal(3);
        hormiga3.salir();
        for (int i = 0; i < 3; i++) {
            hormiga3.mover();
        }
        if ( hormiga3.obtMemoria() != "{0,1,2,3}" ) {
            std::cout << "%TEST_FAILED% time=0 testname=testMover (PbsHormiga) message=La hormiga no llegó al vértice final" << std::endl;
        }
        archivo3.close();
    }
    
    ifstream archivo4("LaberintoPruebaCaminoSimple.txt");
    if (archivo4.is_open()) {
        Laberinto lbrt(archivo4);
        Adyacencia ady(10.0,0.0);
        lbrt.asgDatoAdy(0,1,ady);
        lbrt.asgDatoAdy(1,2,ady);
        lbrt.asgDatoAdy(2,3,ady);
        Hormiga hormiga4;
        hormiga4.asgLaberinto(lbrt);
        lbrt.asgVrtInicial(0);
        lbrt.asgVrtFinal(3);
        hormiga4.salir();
        for (int i = 0; i < 6; i++) {
            hormiga4.mover();
        }
        if ( (hormiga4.obtMemoria() != "{}") && (hormiga4.regreso()) ) {
            std::cout << "%TEST_FAILED% time=0 testname=testMover (PbsHormiga) message=La hormiga no regresó" << std::endl;
        }
    }
    archivo4.close();
}

int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% PbsHormiga" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% testMover (PbsHormiga)" << std::endl;
    testMover();
    std::cout << "%TEST_FINISHED% time=0 testMover (PbsHormiga)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}

