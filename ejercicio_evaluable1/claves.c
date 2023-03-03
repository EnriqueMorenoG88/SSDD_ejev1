#include <stdio.h>
#include "claves.h"



// Inicializa el servicio de almacenaje de tuplas <clave-valor1-valor2-valor3>
int init(){
    return 0;
}



// Inserción del elemento <clave-valor1-valor2-valor3>
int set_value(int key, char* value1, int value2, double value3){
    return 0;
}



// Obtención de los valores asociados a la clave proporcionada
int get_value(int key, char* value1, int* value2, double* value3){
    return 0;
}



// Modificación de los valores asociados a la clave proporcionada
int modify_value(int key, char* value1, int value2, double value3){
    return 0;
}



// Eliminación de la tupla asociada a la clave proporcionada
int delete_key(int key){
    return 0;
}



// Comprobación de la existencia de algún elemento asociado a la clave proporcionada
int exist(int key){
    
}



// Creación e inserción de un nuevo elemento con la segunda clave proporcionada, copiando los valores de la primera
int copy_key(int key1, int key2){

}