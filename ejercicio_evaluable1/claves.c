
#include <stdio.h>
#include <mqueue.h>
#include <string.h>
#include "claves.h"
#include "comunicacion.h"

#define MAX_MSG 10



// Inicializa el servicio de almacenaje de tuplas <clave-valor1-valor2-valor3>
int init(){
    
    mqd_t cola_cliente;
    struct mq_attr qattr_cliente;
    qattr_cliente.mq_maxmsg = MAX_MSG;
    qattr_cliente.mq_msgsize = sizeof(int);

    mqd_t cola_servidor;
    Service respuesta;
    Request peticion = default_request;
    peticion.op = 'i';

    if ((cola_servidor = mq_open("/COLA_SERVIDOR.txt", O_WRONLY)) == -1){
        perror("[CLIENTE] Cola del servidor no pudo abrirse\n");
        return -1;
    }

    if (mq_send(cola_servidor, (const char*) &peticion, sizeof(Request), 0) == -1){
        perror("[CLIENTE] No pudo enviarse el mensaje\n");
        if (mq_close(cola_servidor) == -1)
            perror("[CLIENTE] Cola del servidor no pudo cerrarse\n");
        return -1; 
    }

    if (mq_close(cola_servidor) == -1){
        perror("[CLIENTE] Cola del servidor no pudo cerrarse\n");
        return -1;
    }

    if ((cola_cliente = mq_open("/COLA_CLIENTE", O_CREAT|O_RDONLY, 0700, &qattr_cliente)) == -1){
        perror("[CLIENTE] Cola cliente no pudo abrise\n");
        return -1;
    }

    if (mq_receive(cola_cliente, (char*) &respuesta, sizeof(Service), 0) == -1){
        perror("[CLIENTE] No pudo enviarse el mensaje\n");
        if (mq_close(cola_cliente) == -1)
            perror("[CLIENTE] Cola del cliente no pudo cerrarse\n");
        if (mq_unlink("/COLA_CLIENTE.txt") == -1)
            perror("[CLIENTE] Cola cliente no pudo desvincularse\n");
        return -1; 
    }

    if (mq_close(cola_cliente) == -1){
        perror("[CLIENTE] Cola del servidor no pudo cerrarse\n");
        return -1;
    }

    /*
    if (mq_unlink("/COLA_CLIENTE.txt") == -1){
        perror("[CLIENTE] Cola cliente no pudo desvincularse\n");
        return -1;
    }
    */

    if (respuesta.status == 0)
        return 0;
    return -1;
}



// Inserción del elemento <clave-valor1-valor2-valor3>
int set_value(int key, char* value1, int value2, double value3){

    mqd_t cola_cliente;
    struct mq_attr qattr_cliente;
    qattr_cliente.mq_maxmsg = MAX_MSG;
    qattr_cliente.mq_msgsize = sizeof(int);

    mqd_t cola_servidor;
    Service respuesta;
    Tuple contenido = {key, {*value1}, value2, value3};
    Request peticion = default_request;
    peticion.op = 's';
    peticion.content = contenido;

    if ((cola_servidor = mq_open("/COLA_SERVIDOR.txt", O_WRONLY)) == -1){
        perror("[CLIENTE] Cola del servidor no pudo abrirse\n");
        return -1;
    }

    if (mq_send(cola_servidor, (const char*) &peticion, sizeof(Request), 0) == -1){
        perror("[CLIENTE] No pudo enviarse el mensaje\n");
        if (mq_close(cola_servidor) == -1)
            perror("[CLIENTE] Cola del servidor no pudo cerrarse\n");
        return -1; 
    }

    if (mq_close(cola_servidor) == -1){
        perror("[CLIENTE] Cola del servidor no pudo cerrarse\n");
        return -1;
    }

    if ((cola_cliente = mq_open("/COLA_CLIENTE", O_CREAT|O_RDONLY, 0700, &qattr_cliente)) == -1){
        perror("[CLIENTE] Cola cliente no pudo abrise\n");
        return -1;
    }

    if (mq_receive(cola_cliente, (char*) &respuesta, sizeof(Service), 0) == -1){
        perror("[CLIENTE] No pudo enviarse el mensaje\n");
        if (mq_close(cola_cliente) == -1)
            perror("[CLIENTE] Cola del cliente no pudo cerrarse\n");
        if (mq_unlink("/COLA_CLIENTE.txt") == -1)
            perror("[CLIENTE] Cola cliente no pudo desvincularse\n");
        return -1; 
    }

    if (mq_close(cola_cliente) == -1){
        perror("[CLIENTE] Cola del servidor no pudo cerrarse\n");
        return -1;
    }

    /*
    if (mq_unlink("/COLA_CLIENTE.txt") == -1){
        perror("[CLIENTE] Cola cliente no pudo desvincularse\n");
        return -1;
    }
    */

    if (respuesta.status == 0){
        return 0;
    }
    
    return -1;
}



// Obtención de los valores asociados a la clave proporcionada
int get_value(int key, char* value1, int* value2, double* value3){

    mqd_t cola_cliente;
    struct mq_attr qattr_cliente;
    qattr_cliente.mq_maxmsg = MAX_MSG;
    qattr_cliente.mq_msgsize = sizeof(int);

    mqd_t cola_servidor;
    Service respuesta;
    Request peticion = default_request;
    peticion.op = 'g';
    peticion.content.key = key;


    if ((cola_servidor = mq_open("/COLA_SERVIDOR.txt", O_WRONLY)) == -1){
        perror("[CLIENTE] Cola del servidor no pudo abrirse\n");
        return -1;
    }

    if (mq_send(cola_servidor, (const char*) &peticion, sizeof(Request), 0) == -1){
        perror("[CLIENTE] No pudo enviarse el mensaje\n");
        if (mq_close(cola_servidor) == -1)
            perror("[CLIENTE] Cola del servidor no pudo cerrarse\n");
        return -1; 
    }

    if (mq_close(cola_servidor) == -1){
        perror("[CLIENTE] Cola del servidor no pudo cerrarse\n");
        return -1;
    }

    if ((cola_cliente = mq_open("/COLA_CLIENTE", O_CREAT|O_RDONLY, 0700, &qattr_cliente)) == -1){
        perror("[CLIENTE] Cola cliente no pudo abrise\n");
        return -1;
    }

    if (mq_receive(cola_cliente, (char*) &respuesta, sizeof(Service), 0) == -1){
        perror("[CLIENTE] No pudo enviarse el mensaje\n");
        if (mq_close(cola_cliente) == -1)
            perror("[CLIENTE] Cola del cliente no pudo cerrarse\n");
        if (mq_unlink("/COLA_CLIENTE.txt") == -1)
            perror("[CLIENTE] Cola cliente no pudo desvincularse\n");
        return -1; 
    }

    if (mq_close(cola_cliente) == -1){
        perror("[CLIENTE] Cola del servidor no pudo cerrarse\n");
        return -1;
    }

    if (respuesta.status == -1) {
        return -1;
    }

    strcpy(value1, respuesta.content.value1);
    *value2 = respuesta.content.value2;
    *value3 = respuesta.content.value3;

    return 0;
    /*
    if (mq_receive(cola_cliente, char* (existe_respuesta), sizeof(int), 0) == -1){
        perror("[CLIENTE] No pudo enviarse el mensaje");
        if (mq_close(cola_servidor) == -1){
            perror("[CLIENTE] Cola del servidor no pudo cerrarse");
            return -2;
        }
        return -1; 
    }

    if (existe_respuesta == 0){
        if (mq_receive(cola_cliente, char* (respuesta), sizeof(struct tupla), 0) == -1){
            perror("[CLIENTE] No pudo enviarse el mensaje");
            return -1; 
        } 

        strcpy(value1, respuesta -> value1);
        *value2 = respuesta -> value2;
        *value3 = respuesta -> value3;

        return 0;
    }
    */

}



// Modificación de los valores asociados a la clave proporcionada
int modify_value(int key, char* value1, int value2, double value3){
    mqd_t cola_cliente;
    struct mq_attr qattr_cliente;
    qattr_cliente.mq_maxmsg = MAX_MSG;
    qattr_cliente.mq_msgsize = sizeof(int);

    mqd_t cola_servidor;
    Service respuesta;
    Tuple contenido = {key, {*value1}, value2, value3};
    Request peticion;
    peticion.op = 'm';
    peticion.content = contenido;

    if ((cola_servidor = mq_open("/COLA_SERVIDOR.txt", O_WRONLY)) == -1){
        perror("[CLIENTE] Cola del servidor no pudo abrirse\n");
        return -1;
    }

    if (mq_send(cola_servidor, (const char*) &peticion, sizeof(Request), 0) == -1){
        perror("[CLIENTE] No pudo enviarse el mensaje\n");
        if (mq_close(cola_servidor) == -1)
            perror("[CLIENTE] Cola del servidor no pudo cerrarse\n");
        return -1; 
    }

    if (mq_close(cola_servidor) == -1){
        perror("[CLIENTE] Cola del servidor no pudo cerrarse\n");
        return -1;
    }

    if ((cola_cliente = mq_open("/COLA_CLIENTE", O_CREAT|O_RDONLY, 0700, &qattr_cliente)) == -1){
        perror("[CLIENTE] Cola cliente no pudo abrise\n");
        return -1;
    }

    if (mq_receive(cola_cliente, (char*) &respuesta, sizeof(Service), 0) == -1){
        perror("[CLIENTE] No pudo enviarse el mensaje\n");
        if (mq_close(cola_cliente) == -1)
            perror("[CLIENTE] Cola del cliente no pudo cerrarse\n");
        if (mq_unlink("/COLA_CLIENTE.txt") == -1)
            perror("[CLIENTE] Cola cliente no pudo desvincularse\n");
        return -1; 
    }

    if (mq_close(cola_cliente) == -1){
        perror("[CLIENTE] Cola del servidor no pudo cerrarse\n");
        return -1;
    }

    if (respuesta.status == -1){
        return -1;
    }
    
    return 0;
}



// Eliminación de la tupla asociada a la clave proporcionada
int delete_key(int key){
    mqd_t cola_cliente;
    struct mq_attr qattr_cliente;
    qattr_cliente.mq_maxmsg = MAX_MSG;
    qattr_cliente.mq_msgsize = sizeof(int);

    mqd_t cola_servidor;
    Service respuesta;
    Request peticion;
    peticion.op = 'd';
    peticion.content.key = key;


    if ((cola_servidor = mq_open("/COLA_SERVIDOR.txt", O_WRONLY)) == -1){
        perror("[CLIENTE] Cola del servidor no pudo abrirse\n");
        return -1;
    }

    if (mq_send(cola_servidor, (const char*) &peticion, sizeof(Request), 0) == -1){
        perror("[CLIENTE] No pudo enviarse el mensaje\n");
        if (mq_close(cola_servidor) == -1)
            perror("[CLIENTE] Cola del servidor no pudo cerrarse\n");
        return -1; 
    }

    if (mq_close(cola_servidor) == -1){
        perror("[CLIENTE] Cola del servidor no pudo cerrarse\n");
        return -1;
    }

    if ((cola_cliente = mq_open("/COLA_CLIENTE", O_CREAT|O_RDONLY, 0700, &qattr_cliente)) == -1){
        perror("[CLIENTE] Cola cliente no pudo abrise\n");
        return -1;
    }

    if (mq_receive(cola_cliente, (char*) &respuesta, sizeof(Service), 0) == -1){
        perror("[CLIENTE] No pudo enviarse el mensaje\n");
        if (mq_close(cola_cliente) == -1)
            perror("[CLIENTE] Cola del cliente no pudo cerrarse\n");
        if (mq_unlink("/COLA_CLIENTE.txt") == -1)
            perror("[CLIENTE] Cola cliente no pudo desvincularse\n");
        return -1; 
    }

    if (mq_close(cola_cliente) == -1){
        perror("[CLIENTE] Cola del servidor no pudo cerrarse\n");
        return -1;
    }

    if (respuesta.status == -1){
        return -1;
    }
    
    return 0;
    
}



// Comprobación de la existencia de algún elemento asociado a la clave proporcionada
int exist(int key){
    mqd_t cola_cliente;
    struct mq_attr qattr_cliente;
    qattr_cliente.mq_maxmsg = MAX_MSG;
    qattr_cliente.mq_msgsize = sizeof(int);
    
    mqd_t cola_servidor;
    Service respuesta;
    Request peticion = default_request;
    peticion.op = 'e';
    peticion.content.key = key;


    if ((cola_servidor = mq_open("/COLA_SERVIDOR.txt", O_WRONLY)) == -1){
        perror("[CLIENTE] Cola del servidor no pudo abrirse\n");
        return -1;
    }

    if (mq_send(cola_servidor, (const char*) &peticion, sizeof(Request), 0) == -1){
        perror("[CLIENTE] No pudo enviarse el mensaje\n");
        if (mq_close(cola_servidor) == -1)
            perror("[CLIENTE] Cola del servidor no pudo cerrarse\n");
        return -1; 
    }

    if (mq_close(cola_servidor) == -1){
        perror("[CLIENTE] Cola del servidor no pudo cerrarse\n");
        return -1;
    }

    if ((cola_cliente = mq_open("/COLA_CLIENTE", O_CREAT|O_RDONLY, 0700, &qattr_cliente)) == -1){
        perror("[CLIENTE] Cola cliente no pudo abrise\n");
        return -1;
    }

    if (mq_receive(cola_cliente, (char*) &respuesta, sizeof(Service), 0) == -1){
        perror("[CLIENTE] No pudo enviarse el mensaje\n");
        if (mq_close(cola_cliente) == -1)
            perror("[CLIENTE] Cola del cliente no pudo cerrarse\n");
        if (mq_unlink("/COLA_CLIENTE.txt") == -1)
            perror("[CLIENTE] Cola cliente no pudo desvincularse\n");
        return -1; 
    }

    if (mq_close(cola_cliente) == -1){
        perror("[CLIENTE] Cola del servidor no pudo cerrarse\n");
        return -1;
    }

    switch(respuesta.status){
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
    mqd_t cola_cliente;
    struct mq_attr qattr_cliente;
    qattr_cliente.mq_maxmsg = MAX_MSG;
    qattr_cliente.mq_msgsize = sizeof(int);

    mqd_t cola_servidor;
    Service respuesta;
    Request peticion;
    peticion.op = 'd';
    peticion.content.key = key1;
    peticion.second_key = key2;


    if ((cola_servidor = mq_open("/COLA_SERVIDOR.txt", O_WRONLY)) == -1){
        perror("[CLIENTE] Cola del servidor no pudo abrirse\n");
        return -1;
    }

    if (mq_send(cola_servidor, (const char*) &peticion, sizeof(Request), 0) == -1){
        perror("[CLIENTE] No pudo enviarse el mensaje\n");
        if (mq_close(cola_servidor) == -1)
            perror("[CLIENTE] Cola del servidor no pudo cerrarse\n");
        return -1; 
    }

    if (mq_close(cola_servidor) == -1){
        perror("[CLIENTE] Cola del servidor no pudo cerrarse\n");
        return -1;
    }

    if ((cola_cliente = mq_open("/COLA_CLIENTE", O_CREAT|O_RDONLY, 0700, &qattr_cliente)) == -1){
        perror("[CLIENTE] Cola cliente no pudo abrise\n");
        return -1;
    }

    if (mq_receive(cola_cliente, (char*) &respuesta, sizeof(Service), 0) == -1){
        perror("[CLIENTE] No pudo enviarse el mensaje\n");
        if (mq_close(cola_cliente) == -1)
            perror("[CLIENTE] Cola del cliente no pudo cerrarse\n");
        if (mq_unlink("/COLA_CLIENTE.txt") == -1)
            perror("[CLIENTE] Cola cliente no pudo desvincularse\n");
        return -1; 
    }

    if (mq_close(cola_cliente) == -1){
        perror("[CLIENTE] Cola del servidor no pudo cerrarse\n");
        return -1;
    }

    if (respuesta.status == -1) {
        return -1;
    }
    
    return 0;
}