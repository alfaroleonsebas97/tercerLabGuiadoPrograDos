/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   error_grafo.h
 * Author: alfar
 *
 * Created on 22 de junio de 2018, 12:45 PM
 */

#ifndef ERROR_GRAFO_H
#define ERROR_GRAFO_H

#include <exception>
#include <string>
using namespace std;

class error_grafo : public exception {
public:
    error_grafo(int t_error, string elemento);
    
    virtual ~error_grafo();
    
    virtual const char* what() const noexcept;
    
private:
    int t_error;
    string elementoDelError;
};

#endif /* ERROR_GRAFO_H */

