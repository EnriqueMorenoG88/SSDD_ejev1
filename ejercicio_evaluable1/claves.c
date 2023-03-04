
#include <stdio.h>
#include <mqueue.h>
#include <string.h>
#include "claves.h"

struct tupla{
    int key;
    char* value1 = '\0';
    int value2 = 0;
    double value3 = 0.0;
}

struct solicitud{
    char* op;
    struct tupla content;
    int second_key = 0;
}



// Inicializa el servicio de almacenaje de tuplas <clave-valor1-valor2-valor3>
int init(){



    if (respuesta == -1) ? return -1 : return 0;
}



// Inserción del elemento <clave-valor1-valor2-valor3>
int set_value(int key, char* value1, int value2, double value3){

    mqd_t cola_servidor;
    int respuesta;
    struct tupla contenido = {key, value1, value2, value3};
    struct solicitud peticion = {"set", contenido};



    if (cola_servidor = mq_open("/COLA_SERVIDOR", O_RDONLY) == -1){
        perror("[CLIENTE] Cola del servidor no pudo abrirse");
        return -1;
    }

    if (mq_send(cola_servidor, const char* (peticion), sizeof(struct solicitud), 0) == -1){
        perror("[CLIENTE] No pudo enviarse el mensaje");
        if (mq_close(cola_servidor) == -1){
            perror("[CLIENTE] Cola del servidor no pudo cerrarse");
            return -2;
        }
        return -1; 
    }

    if (mq_receive(cola_servidor, char* (respuesta), sizeof(int), 0) == -1){
        perror("[CLIENTE] No pudo enviarse el mensaje");
        if (mq_close(cola_servidor) == -1){
            perror("[CLIENTE] Cola del servidor no pudo cerrarse");
            return -2;
        }
        return -1; 
    }


    if (mq_close(cola_servidor) == -1){
        perror("[CLIENTE] Cola del servidor no pudo cerrarse");
        return -1;
    }

    if (respuesta == -1) ? return -1 : return 0;
}



// Obtención de los valores asociados a la clave proporcionada
int get_value(int key, char* value1, int* value2, double* value3){

    mqd_t cola_servidor;
    int existe_respuesta;
    struct tupla respuesta;
    struct tupla contenido = {key};
    struct solicitud peticion = {"get", contenido};


    if (cola_servidor = mq_open("/COLA_SERVIDOR", O_RDONLY) == -1){
        perror("[CLIENTE] Cola del servidor no pudo abrirse");
        return -1;
    }

    if (mq_send(cola_servidor, const char* (peticion), sizeof(struct solicitud), 0) == -1){
        perror("[CLIENTE] No pudo enviarse el mensaje");
        if (mq_close(cola_servidor) == -1){
            perror("[CLIENTE] Cola del servidor no pudo cerrarse");
            return -2;
        }
        return -1; 
    }

    if (mq_receive(cola_servidor, char* (existe_respuesta), sizeof(int), 0) == -1){
        perror("[CLIENTE] No pudo enviarse el mensaje");
        if (mq_close(cola_servidor) == -1){
            perror("[CLIENTE] Cola del servidor no pudo cerrarse");
            return -2;
        }
        return -1; 
    }

    if (existe_respuesta == 0){
        if (mq_receive(cola_servidor, char* (respuesta), sizeof(struct tupla), 0) == -1){
            perror("[CLIENTE] No pudo enviarse el mensaje");
            if (mq_close(cola_servidor) == -1){
                perror("[CLIENTE] Cola del servidor no pudo cerrarse");
                return -2;
            }
            return -1; 
        } 

        strcpy(value1, respuesta -> value1);
        *value2 = respuesta -> value2;
        *value3 = respuesta -> value3;

        if (mq_close(cola_servidor) == -1){
            perror("[CLIENTE] Cola del servidor no pudo cerrarse");
            return -2;
        }

        return 0;
    }
    else{
        if (mq_close(cola_servidor) == -1){
            perror("[CLIENTE] Cola del servidor no pudo cerrarse");
            return -2;
        }
        return -1;
    }

}



// Modificación de los valores asociados a la clave proporcionada
int modify_value(int key, char* value1, int value2, double value3){
    mqd_t cola_servidor;
    int respuesta;
    struct tupla contenido = {key, value1, value2, value3};
    struct solicitud peticion = {"modify", contenido};

    if (cola_servidor = mq_open("/COLA_SERVIDOR", O_RDONLY) == -1){
        perror("[CLIENTE] Cola del servidor no pudo abrirse");
        return -1;
    }

    if (mq_send(cola_servidor, const char* (peticion), sizeof(struct solicitud), 0) == -1){
        perror("[CLIENTE] No pudo enviarse el mensaje");
        if (mq_close(cola_servidor) == -1){
            perror("[CLIENTE] Cola del servidor no pudo cerrarse");
            return -2;
        }
        return -1; 
    }

    if (mq_receive(cola_servidor, char* (respuesta), sizeof(int), 0) == -1){
        perror("[CLIENTE] No pudo enviarse el mensaje");
        if (mq_close(cola_servidor) == -1){
            perror("[CLIENTE] Cola del servidor no pudo cerrarse");
            return -2;
        }
        return -1; 
    }


    if (mq_close(cola_servidor) == -1){
        perror("[CLIENTE] Cola del servidor no pudo cerrarse");
        return -1;
    }

    if (respuesta == -1) ? return -1 : return 0;
}



// Eliminación de la tupla asociada a la clave proporcionada
int delete_key(int key){
    mqd_t cola_servidor;
    int respuesta;
    struct solicitud peticion = {"delete", {key}};


    if (cola_servidor = mq_open("/COLA_SERVIDOR", O_RDONLY) == -1){
        perror("[CLIENTE] Cola del servidor no pudo abrirse");
        return -1;
    }

    if (mq_send(cola_servidor, const char* (peticion), sizeof(struct solicitud), 0) == -1){
        perror("[CLIENTE] No pudo enviarse el mensaje");
        if (mq_close(cola_servidor) == -1){
            perror("[CLIENTE] Cola del servidor no pudo cerrarse");
            return -2;
        }
        return -1; 
    }

    if (mq_receive(cola_servidor, char* (respuesta), sizeof(int), 0) == -1){
        perror("[CLIENTE] No pudo enviarse el mensaje");
        if (mq_close(cola_servidor) == -1){
            perror("[CLIENTE] Cola del servidor no pudo cerrarse");
            return -2;
        }
        return -1; 
    }

    if (mq_close(cola_servidor) == -1){
        perror("[CLIENTE] Cola del servidor no pudo cerrarse");
        return -1;
    }

    if (respuesta == -1) ? return -1 : return 0;
    
}



// Comprobación de la existencia de algún elemento asociado a la clave proporcionada
int exist(int key){
    
    mqd_t cola_servidor;
    int respuesta;
    struct solicitud peticion = {"exist", {key}};


    if (cola_servidor = mq_open("/COLA_SERVIDOR", O_RDONLY) == -1){
        perror("[CLIENTE] Cola del servidor no pudo abrirse");
        return -1;
    }

    if (mq_send(cola_servidor, const char* (peticion), sizeof(struct solicitud), 0) == -1){
        perror("[CLIENTE] No pudo enviarse el mensaje");
        if (mq_close(cola_servidor) == -1){
            perror("[CLIENTE] Cola del servidor no pudo cerrarse");
            return -2;
        }
        return -1; 
    }

    if (mq_receive(cola_servidor, char* (respuesta), sizeof(int), 0) == -1){
        perror("[CLIENTE] No pudo enviarse el mensaje");
        if (mq_close(cola_servidor) == -1){
            perror("[CLIENTE] Cola del servidor no pudo cerrarse");
            return -2;
        }
        return -1; 
    }

    if (mq_close(cola_servidor) == -1){
        perror("[CLIENTE] Cola del servidor no pudo cerrarse");
        return -1;
    }

    switch(respuesta){
        case 1:
            return 1;
        
        case 0:
            return 0;

        default:
            return -1;
    }
    
}



// Creación e inserción de un nuevo elemento con la segunda clave proporcionada, copiando los valores de la primera
int copy_key(int key1, int key2){

    mqd_t cola_servidor;
    int respuesta;
    struct solicitud peticion = {"copy", {key1}, key2};


    if (cola_servidor = mq_open("/COLA_SERVIDOR", O_RDONLY) == -1){
        perror("[CLIENTE] Cola del servidor no pudo abrirse");
        return -1;
    }

    if (mq_send(cola_servidor, const char* (peticion), sizeof(struct solicitud), 0) == -1){
        perror("[CLIENTE] No pudo enviarse el mensaje");
        if (mq_close(cola_servidor) == -1){
            perror("[CLIENTE] Cola del servidor no pudo cerrarse");
            return -2;
        }
        return -1; 
    }

    if (mq_receive(cola_servidor, char* (respuesta), sizeof(int), 0) == -1){
        perror("[CLIENTE] No pudo enviarse el mensaje");
        if (mq_close(cola_servidor) == -1){
            perror("[CLIENTE] Cola del servidor no pudo cerrarse");
            return -2;
        }
        return -1; 
    }

    if (mq_close(cola_servidor) == -1){
        perror("[CLIENTE] Cola del servidor no pudo cerrarse");
        return -1;
    }

    if (respuesta == -1) ? return -1 : return 0;
}