/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Hormiga.cpp
 * Author: Alan
 * 
 * Created on 7 de febrero de 2018, 05:53 PM
 */

#include "Hormiga.h"

Laberinto* Hormiga::laberinto_p = 0; // inicialización de variable static privada

Hormiga::Hormiga() {
    idVrtActual = -1;
    haSalido = false; 
    haRegresado = false;
    destino = 'F'; 
    enRetroceso = 0;
    longitudSolucion = 0;
    deltaFerormona = 0.0;
}

Hormiga::Hormiga(const Hormiga& orig) {
    idVrtActual = orig.idVrtActual;
    memoria = orig.memoria;
    haSalido = orig.haSalido;
    haRegresado = orig.haRegresado;
    destino = orig.destino;
    enRetroceso = orig.enRetroceso;
    longitudSolucion = orig.longitudSolucion;
    deltaFerormona = orig.deltaFerormona;
}

Hormiga::~Hormiga() {
}

/* OBSERVADORES */

bool Hormiga::salio() {
    return haSalido;
}

bool Hormiga::regreso() {
    return haRegresado;
}

char Hormiga::obtDestino() {
     return destino; 
}

string Hormiga::obtMemoria() {
    string memoriaHilera = "{";                                             //Abre corchetes
    if (!memoria.empty()) {                                                 //Si la memoria no está vacía
        for (auto current: memoria) {                                       //Recorre la memoria 
            memoriaHilera += to_string(current);                            //Agrega cada elemento de la memoria en una hilera
            memoriaHilera.push_back(',');                                   //Agrega una coma después de cada elemento
        }
        memoriaHilera.pop_back();                                           //Borra la última coma
    }
    memoriaHilera += "}";                                                   //Cierra corchetes
    return memoriaHilera;                                                   //Retorna la memoria copiada en la hilera
}

/* MÉTODOS MODIFICADORES */

void Hormiga::salir() {
    Laberinto& laberinto = *laberinto_p;                                    // para evitar notación ->
    idVrtActual = laberinto.obtIdVrtInicial();                              //Obtiene el nodo inicial
    memoria.push_back(idVrtActual);                                         //Ubica la hormiga en el nodo inicial.
    haSalido = true;                                                        //Indica que la hormiga ha salido
}

void Hormiga::mover() {
    if(haSalido){                                                           //Si la hormiga salió
        Laberinto& laberinto = *laberinto_p;                                //para evitar notación ->
        if(destino == 'F'){                                                 //Si la hormiga va hacia el vértice final
            int sgt = seleccionaAdyMasCargada();                            //Selecciona la adyacencia más cargada de ferormona
            if(sgt == -1){                                                  //Si es una adyacencia inválida
                retroceder();                                               //Retrocede
            }else{                                                          //Si es una adyacencia válida
                if(sgt == laberinto.obtIdVrtFinal()){                       //Si la adyacencia a moverse es el vértice final
                    idVrtActual = sgt;                                      //La copia en la varible verticeActual
                    memoria.push_back(idVrtActual);                         //Agrega el vertice actual a la memoria
                    longitudSolucion++;                                     //Aumenta la longitud de la solucion
                    destino = 'I';                                          //Cambia la direccion de la hormiga hacia el inicio
                    deltaFerormona = (1.0/longitudSolucion);                //Asigna el valor de delta ferormona
                } else{                                                     //Si la adyacencia a moverse no es el vértice final
                    idVrtActual = sgt;                                      //El vertice actual es el siguiente
                    memoria.push_back(idVrtActual);                         //Agrega el vertice a la memoria
                    longitudSolucion++;                                     //Aumenta la longitud de la solucion
                }  
            }
        } else{
            if(destino == 'I'){                                             //Si la hormiga viene de regreso
                Adyacencia ady(deltaFerormona,0.0);                         //Crea una adyacencencia con delta ferormonas
                laberinto.asgDatoAdy(idVrtActual, memoria[memoria.size()-1] , ady);//Asigna delta ferormonas a la posicion de la que viene la hormiga
                idVrtActual = memoria[memoria.size()-1];                    //Actualiza el vertice actual                
                memoria.pop_back();                                         //Borra el vertice anterior de la memoria
                
                if(idVrtActual == laberinto.obtIdVrtInicial()){             //Verifica si el vertice actual es el vertice inicio
                    haRegresado = true;                                     //Dice que la hormiga ha regresado
                    memoria.clear();
                    idVrtActual = -1;
                }
            }
        }
    }
}

void Hormiga::retroceder() {
    srand (time(NULL));           
    enRetroceso = rand ()% (memoria.size()-1) + 1;                          //genera un random,
    for ( int i = 0; i <= enRetroceso; i++ ){                               //y retrocede esa cantidad de veces.
        memoria.pop_back();                                                 //Borra el ultimo elemento de la memoria
        longitudSolucion--;                                                 //Disminuye la longitud de la solucion
    }
    idVrtActual = memoria[memoria.size()-1];                                //Cambia la posicion actual como el ultimo vertice de la memoria
    enRetroceso = 0;                                                        //Termina de retroceder
}

int Hormiga::seleccionaAdyMasCargada(){
    Laberinto& laberinto = *laberinto_p;                                    //Para evitar notación ->
    int sgtVrt = -1;                                                        //Asigna inválido al siguiente
    vector<int> vrtsPosibles;                                               //Crea el vector para los vértices posibles
    laberinto.obtIdVrtAdys(idVrtActual,vrtsPosibles);                       //Encuentra los vértices adyacentes
    filtraVrtsPosibles(vrtsPosibles);                                       //Filtra los vértices posibles
    
    if(vrtsPosibles.size()>0){                                              //Si hay vértices posibles
        vector<double> vecFerormonas;                                       //Crea el vector de ferormonas
        double sumaFerormonas = 0.0;
        double ferormona=0.0;
        int cantidadDeCeros = 0;  
        for(auto current: vrtsPosibles){                                    //Recorre los vértices posibles
            ferormona = laberinto.obtDatoAdy(idVrtActual,current).obtCntFerormona();//Obtiene la cantidad de fermona para cada vértice posible
            vecFerormonas.push_back(ferormona);                             //Agrega la ferormona del vertice actual al vector de ferormonas
            sumaFerormonas += ferormona;                                    //Suma la ferormona actual a la suma total de ferormonas
            if(ferormona==0.0){                                             //Verifica si la ferormona es 0
                cantidadDeCeros++;                                          //Suma la cantidad de ceros en el vector
            }
        }
        
        if( sumaFerormonas == 0.0 ){
            srand (time(NULL));
            double random = rand() % cantidadDeCeros;                       //Hace un random
            sgtVrt = vrtsPosibles[random];
        }else{
            vector<double> vecPorcentajes;                                  //Crea un vector de porcentajes
            double porcentajeSumado = 0.0;                                  //Variable para sumar porcentajes, va de 0 a 1
            for (int k = 0; k < vecFerormonas.size(); k++) {                //Recorre el vector de ferormonas
                if (vecFerormonas[k] == 0.0) {                              //Si la ferormona es 0
                    vecPorcentajes.push_back(porcentajeSumado + 0.01);      //Agrega 0.01 de porcentaje a esa adyacencia
                    porcentajeSumado = porcentajeSumado + 0.01;             //Aumenta el porcentaje sumado
                } else {                                                    //Si no es 0
                    vecPorcentajes.push_back( porcentajeSumado + ( (vecFerormonas[k] / sumaFerormonas) * (1 - (cantidadDeCeros * (0.01))) ) );//Agrega al vector el porcentaje asignado a esa adyacencia, según la fórmula
                    porcentajeSumado = ((vecFerormonas[k] / sumaFerormonas) * (1 - (cantidadDeCeros * (0.01))));//Aumenta el porcentaje sumado
                }
            }
        
            srand (time(NULL));
            double numeroAleatorio = (rand() % 1000 + 1) / 1000.0;          //Hace un random
            int m = 0;                                                      //Posicion actual
            if (numeroAleatorio <= vecPorcentajes[m]) {                     //Si el random esta en el rango de la posicion actual
                sgtVrt = vrtsPosibles[m];                                   //El vertice siguiente es el vertice posible de la posicion actual
            } else {                                                            
                while ( numeroAleatorio > vecPorcentajes[m] ) {             //Sigue buscando el rango en el que se encuentra el random
                    m++;                                                    //Mueve la posicion actual
                    if ( numeroAleatorio <= vecPorcentajes[m] ) {           //Si está en el rango de la posicion actual
                        sgtVrt = vrtsPosibles[m];                           //El vertice siguiente es el vertice posible de la posicion actual
                    }
                }
            }
        }
    }
    return sgtVrt;                                                          //Devuelve el siguiente vertice
}

void Hormiga::filtraVrtsPosibles(vector<int> &vrtsPosibles){
    Laberinto& laberinto = *laberinto_p;
    vector<int> copia;                                                      //Vector temporal para los vértices posibles
    for(auto current: vrtsPosibles){                                        //Recorre los vértices posibles
        if( find(memoria.begin(), memoria.end(), current) == memoria.end() ){//Si es válido
            copia.push_back(current);                                       //Lo agrega al vector temporal
        }
    }
    vrtsPosibles = copia;                                                   //Le asigna al vector de vértices posibles el vector ya filtrado
}
    
void Hormiga::asgLaberinto(Laberinto& lbrt) {
    Hormiga::laberinto_p = &lbrt;                                           // asigna valor al puntero, indirectamente a referencia!!
}