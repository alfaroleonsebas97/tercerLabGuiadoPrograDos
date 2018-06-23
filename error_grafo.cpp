/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   error_grafo.cpp
 * Author: alfar
 * 
 * Created on 22 de junio de 2018, 12:45 PM
 */

#include "error_grafo.h"

error_grafo::error_grafo(int t_error, string elemento):t_error(t_error),elementoDelError(elemento) {
}

error_grafo::~error_grafo() {
}

const char* error_grafo::what() const noexcept {
    switch (t_error) {
        case 1:{
            string rsl1("Error, no existe el elemento: ");
            rsl1 = rsl1 + elementoDelError;
            return rsl1.c_str();
            break;
        }
        case 2:{
            string rsl2("Error, no existe la adyacencia entre: ");
            rsl2 = rsl2 + elementoDelError;
            return rsl2.c_str();
            break;
        }
        case 3:{
            string rsl3("Error, no existe camino entre vértices: ");
            rsl3 = rsl3 + elementoDelError;
            return rsl3.c_str();
            break;
        }
    }
}

