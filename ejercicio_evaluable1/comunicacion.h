#ifndef COMUNICACION_H
#define COMUNICACION_H

// Estructura para tuplas
typedef struct tuple{
    int key;
    char value1[255];
    int value2;
    double value3;
} Tuple;

// Inicializacion con los valores por defecto de las tuplas
const Tuple default_tuple = {.value1 = "", .value2 = 0,  .value3 = 0.0};


// Estructura para peticiones de cliente
typedef struct request{
    char op;
    Tuple content;
    int second_key;
} Request;

// Inicializacion con los valores por defecto de las peticiones
Request default_request = {.content = default_tuple, .second_key = 0};


// Estructura para respuesta del servidor a cliente
typedef struct service{
    int status;
    Tuple content;
} Service;

//  Inicializacion con los valores por defecto de las respuesta de servicio
Service default_service = {.content = default_tuple};

#endif