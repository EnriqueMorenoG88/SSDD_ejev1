#include <stdio.h>
#include <pthread.h>
#include <mqueue.h>

#define NUM_THREADS 10
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mfin = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t no_vacio = PTHREAD_COND_INITIALIZER;;
pthread_cond_t no_lleno = PTHREAD_COND_INITIALIZER;;

int n_elementos; // elementos en el buffer de peticiones
int pos_servicio = 0;
int fin=false;

int main(){

    mqd_t q_servidor; /* cola del servidor */
    struct peticion mess; /* mensaje a recibir */
    struct mq_attr q_attr; /* atributos de la cola */
    pthread_attr_t t_attr; /* atributos de los threads */
    pthread_t thid[MAX_THREADS];
    int error;
    int pos = 0;
    q_attr.mq_maxmsg = 10;
    q_attr.mq_msgsize = sizeof(struct peticion);
    q_servidor = mq_open("/SERVIDOR_SUMA", O_CREAT|O_RDONLY, 0700, &q_attr);
    if (q_servidor == -1) {
        perror("No se puede crear la cola de servidor");
        return 1;
    }


    pthread_t thread_pool[NUM_THREADS];
    pthread_attr_init(&t_attr);
    for (int i = 0; i < MAX_THREADS; i++){
        if (pthread_create(&thid[i], NULL, servicio, NULL) !=0){
            perror("Error creando el pool de threads\n");
            return -1;
        }
    }
    

    while(1){
        error = mq_receive(q_servidor, (char *) &mess, sizeof(struct peticion), 0);
        if (error == -1 ) break;
        pthread_mutex_lock(&mutex);
        while (n_elementos == MAX_PETICIONES)
        pthread_cond_wait(&no_lleno, &mutex);
        buffer_peticiones[pos] = mess;
        pos = (pos+1) % MAX_PETICIONES;
        n_elementos++;
        pthread_cond_signal(&no_vacio);
        pthread_mutex_unlock(&mutex);
    }

    pthread_mutex_lock(&mfin);
    fin=true;
    pthread_mutex_unlock(&mfin);


    pthread_mutex_lock(&mutex);
    pthread_cond_broadcast(&no_vacio);
    pthread_mutex_unlock(&mutex);


    for (int i=0;i<MAX_THREADS;i++){
        pthread_join(thid[i],NULL);
    }

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&no_lleno);
    pthread_cond_destroy(&no_vacio);
    pthread_mutex_destroy(&mfin);

    return 0;
}