#include <stdio.h>
#include <pthread.h>
#include <mqueue.h>
#include <string.h>
#include "comunicacion.h"


#define MAX_MSG 10      // Numero maximo de mensajes en cola

int mensaje_no_copiado = 1;                                // Condicion para el mutex
pthread_mutex_t mutex_msg = PTHREAD_MUTEX_INITIALIZER;     // Mutex para control de paso de mensajes
pthread_cond_t condvar_msg = PTHREAD_COND_INITIALIZER;     // Var. condicion asociada al mutex


/* Prototipos de la API del lado servidor */
int init_serv();
int set_value_serv(int key, char* value1, int value2, double value3);
int get_value_serv(int key, char* value1, int* value2, double* value3);
int modify_value_serv(int key, char* value1, int value2, double value3);
int delete_key_serv(int key);
int exist_serv(int key);
int copy_key_serv(int key1, int key2);



void cumplir_pet (void* pet){

    Request peticion;
    Service respuesta;
    mqd_t cola_cliente;

    pthread_mutex_lock(&mutex_msg);
    peticion = (*(Request *) pet);
    /* ya se puede despertar al servidor*/
    mensaje_no_copiado = 0;
    pthread_cond_signal(&condvar_msg);
    pthread_mutex_unlock(&mutex_msg);

    if ((cola_cliente = mq_open("/COLA_CLIENTE.txt", O_WRONLY)) == -1){
        perror("[SERVIDOR] Cola del cliente no pudo abrirse\n");
        pthread_exit(NULL);
    }

    respuesta.content.key = peticion.content.key;

    switch(peticion.op){

        case 'i':   // Operacion init() 

            respuesta.status = init_serv();
            if (mq_send(cola_cliente, (const char*) &respuesta, sizeof(Service), 0) == -1)
                perror("[ERROR] No se pudo enviar la respuesta al cliente\n");
            break;

        case 's':  // Operacion set_value()

            respuesta.status = set_value_serv(peticion.content.key, peticion.content.value1, 
                                                peticion.content.value2, peticion.content.value3);

            if (mq_send(cola_cliente, (const char*) &respuesta, sizeof(Service), 0) == -1)
                perror("[SERVIDOR] No pudo enviarse el mensaje\n");
            break;

        case 'g': // Operacion get_value()
            {
                char valor1[255] = "";
                int valor2 = 0;
                double valor3 = 0.0;
                respuesta.status = get_value_serv(peticion.content.key, valor1, &valor2, &valor3);
                strcat(respuesta.content.value1, valor1);
                respuesta.content.value2 = valor2;
                respuesta.content.value3 = valor3;


                if (mq_send(cola_cliente, (const char*) &respuesta, sizeof(Service), 0) == -1)
                    perror("[SERVIDOR] No pudo enviarse el mensaje\n");
                break;
            }
        case 'm':  // Operacion modify_value()

            respuesta.status = modify_value_serv(peticion.content.key, peticion.content.value1,
                                                peticion.content.value2, peticion.content.value2);
            


            if (mq_send(cola_cliente, (const char*) &respuesta, sizeof(Service), 0) == -1)
                perror("[SERVIDOR] No pudo enviarse el mensaje\n");
            break;

        case 'd':  //Operacion delete_value()

            respuesta.status = delete_key_serv(peticion.content.key);


            if (mq_send(cola_cliente, (const char*) &respuesta, sizeof(Service), 0) == -1)
                perror("[SERVIDOR] No pudo enviarse el mensaje\n");
            break;

        case 'e':   // Operacion exist()

            respuesta.status = exist_serv(peticion.content.key);


            if (mq_send(cola_cliente, (const char*) &respuesta, sizeof(Service), 0) == -1){
                perror("[SERVIDOR] No pudo enviarse el mensaje\n");
            }
            break;

        case 'c':    // Operacion copy_key()

            respuesta.status = copy_key_serv(peticion.content.key, peticion.second_key);


            if (mq_send(cola_cliente, (const char*) &respuesta, sizeof(Service), 0) == -1)
                perror("[SERVIDOR] No pudo enviarse el mensaje\n");
            break;

        default:
            perror("[SERVIDOR] Operacion solicitada no valida\n");
    }

    if (mq_close(cola_cliente) == -1){
        perror("[SERVIDOR] Cola del cliente no pudo cerrarse\n");
    }

    pthread_exit(NULL);

}



int main(){

    mqd_t cola_servidor;
    struct mq_attr qattr_servidor;
    qattr_servidor.mq_maxmsg = 10;
    qattr_servidor.mq_msgsize = sizeof(Request);


    // Mensaje recibido del cliente
    Request peticion;

    pthread_t thid;
    pthread_attr_t th_attr; 


    if((cola_servidor = mq_open("/COLA_SERVIDOR.txt", O_CREAT|O_RDONLY, 0700, &qattr_servidor)) == -1){
        perror("[SERVIDOR] No se puede crear la cola de servidor\n");
        return -1; 
    }

    pthread_attr_init(&th_attr);
    pthread_attr_setdetachstate(&th_attr,PTHREAD_CREATE_DETACHED);
    

    while(1){

        if(mq_receive(cola_servidor, (char *) &peticion, sizeof(Request), 0) == -1)
            break;
        if(pthread_create(&thid, &th_attr, (void*) &cumplir_pet, (void *) &peticion) == -1){
            perror("[SERVIDOR] Hilo no pudo ser creado\n");
        }
        pthread_mutex_lock(&mutex_msg);
        while (mensaje_no_copiado) pthread_cond_wait(&condvar_msg, &mutex_msg);
            mensaje_no_copiado = 1;
            pthread_mutex_unlock(&mutex_msg);
        }

    if (mq_close(cola_servidor) == -1){
        perror("[SERVIDOR] Cola del servidor no pudo cerrarse\n");
        return -1;
    }

    if (mq_unlink("/COLA_SERVIDOR.txt") == -1){
        perror("[SERVIDOR] Cola cliente no pudo desvincularse\n");
        return -1;
    }

    return 0;
}