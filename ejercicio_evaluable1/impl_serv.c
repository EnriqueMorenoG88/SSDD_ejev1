#include <stdio.h>
#include <pthread.h>
#include <mqueue.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>


const char* filename = "./tuples/tupla_";     // Ruta relativa del fichero de tupla (sin num. clave)
const char* ext = ".txt";                     // Extension del fichero de tupla

// Estructura para tuplas
typedef struct tuple{
    int key;
    char value1[255];
    int value2;
    double value3;
} Tuple;


int init_serv(){

    if (remove("./tuples") == -1){
        perror("[ERROR] El directorio no pudo ser eliminado\n");
        return -1;
    }
    if (mkdir("tuples", 0777) == -1){
        perror("[ERROR] El directorio no pudo ser creado\n");
        return -1;
    }
    return 0;
}


// Inserción del elemento <clave-valor1-valor2-valor3>
int set_value_serv(int key, char* value1, int value2, double value3){

    #define INT_CHAR_LEN(key) ((sizeof(key) * CHAR_BIT)/3 + 3)

    char tuple_file[strlen(filename) + 1 + INT_CHAR_LEN(key) + 1];
    sprintf(tuple_file, "%s%d%s", filename, key, ext);
    

    if (!access(tuple_file, F_OK))
        return -1;

    FILE* tpl_fp;
    tpl_fp = fopen(tuple_file, "w");
    if (tpl_fp == NULL){
        perror("[ERROR] El archivo para la tupla no pudo ser creado\n");
        return -1;
    }

    Tuple tupla = {key, {*value1}, value2, value3};
    if (fwrite(&tupla, sizeof(Tuple), 1, tpl_fp) == 0){
        perror("[ERROR] No se pudo escribir en el archivo\n");
        fclose(tpl_fp);
        return -1;
    }
    
    fclose(tpl_fp);
    return 0;
}


// Obtención de los valores asociados a la clave proporcionada
int get_value_serv(int key, char* value1, int* value2, double* value3){

    #define INT_CHAR_LEN(key) ((sizeof(key) * CHAR_BIT)/3 + 3)

    char tuple_file[strlen(filename) + 1 + INT_CHAR_LEN(key) + 1];
    sprintf(tuple_file, "%s%d%s", filename, key, ext);
    

    if (access(tuple_file, F_OK))
        return -1;
    
    FILE* tpl_fp;
    tpl_fp = fopen(tuple_file, "r");
    if (tpl_fp == NULL){
        perror("[ERROR] El archivo para la tupla no pudo abrirse\n");
        return -1;
    }

    Tuple tupla;
    while (fread(&tupla, sizeof(Tuple), 1, tpl_fp)){}
    
    fclose(tpl_fp);

    sprintf(value1, "%s", tupla.value1);
    *value2 = tupla.value2;
    *value3 = tupla.value3;

    return 0;
}


// Modificación de los valores asociados a la clave proporcionada
int modify_value_serv(int key, char* value1, int value2, double value3){

    #define INT_CHAR_LEN(key) ((sizeof(key) * CHAR_BIT)/3 + 3)

    char tuple_file[strlen(filename) + 1 + INT_CHAR_LEN(key) + 1];
    sprintf(tuple_file, "%s%d%s", filename, key, ext);
    

    if (access(tuple_file, F_OK))
        return -1;
    
    if (remove(tuple_file) == -1){
        perror("[ERROR] El directorio no pudo ser eliminado\n");
        return -1;
    }

    FILE* tpl_fp;
    tpl_fp = fopen(tuple_file, "w");
    if (tpl_fp == NULL){
        perror("[ERROR] El archivo para la tupla no pudo ser creado\n");
        return -1;
    }

    Tuple tupla = {key, {*value1}, value2, value3};
    if (fwrite(&tupla, sizeof(Tuple), 1, tpl_fp) == 0){
        perror("[ERROR] No se pudo escribir en el archivo\n");
        fclose(tpl_fp);
        return -1;
    }
    
    fclose(tpl_fp);

    return 0;
}


// Eliminación de la tupla asociada a la clave proporcionada
int delete_key_serv(int key){

    #define INT_CHAR_LEN(key) ((sizeof(key) * CHAR_BIT)/3 + 3)

    char tuple_file[strlen(filename) + 1 + INT_CHAR_LEN(key) + 1];
    sprintf(tuple_file, "%s%d%s", filename, key, ext);
    

    if (access(tuple_file, F_OK))
        return -1;
    
    if (remove(tuple_file) == -1){
        perror("[ERROR] El directorio no pudo ser eliminado\n");
        return -1;
    }
    return 0;
}


// Comprobacion de la existencia de algun elemento asociado a la clave proporcionada
int exist_serv(int key){

    #define INT_CHAR_LEN(key) ((sizeof(key) * CHAR_BIT)/3 + 3)

    char tuple_file[strlen(filename) + 1 + INT_CHAR_LEN(key) + 1];
    sprintf(tuple_file, "%s%d%s", filename, key, ext);
    

    if (!access(tuple_file, F_OK))
        return 1;

    return 0;
}


// Creacion e insercion de un nuevo elemento con la segunda clave proporcionada, copiando los valores de la primera
int copy_key_serv(int key1, int key2){

    #define INT_CHAR_LEN(key) ((sizeof(key) * CHAR_BIT)/3 + 3)

    char original_tpl_file[strlen(filename) + 1 + INT_CHAR_LEN(key1) + 1];
    sprintf(original_tpl_file, "%s%d%s", filename, key1, ext);
    

    if (access(original_tpl_file, F_OK))
        return -1;

    FILE* original_tpl_fp;
    FILE* copy_tpl_fp;

    char copy_tpl_file[strlen(filename) + 1 + INT_CHAR_LEN(key2) + 1];
    sprintf(copy_tpl_file, "%s%d%s", filename, key2, ext);


    original_tpl_fp = fopen(original_tpl_file, "r");
    if (original_tpl_fp == NULL){
        perror("[ERROR] El archivo para la tupla no pudo ser abierto\n");
        return -1;
    }


    Tuple tupla;
    while (fread(&tupla, sizeof(Tuple), 1, original_tpl_fp)){}
    
    fclose(original_tpl_fp);

    tupla.key = key2;

    copy_tpl_fp = fopen(copy_tpl_file, "w");
    if (copy_tpl_fp == NULL){
        perror("[ERROR] El archivo para la tupla no pudo ser creado/abierto\n");
        return -1;
    }

    if (fwrite(&tupla, sizeof(Tuple), 1, copy_tpl_fp) == 0){
        perror("[ERROR] No se pudo escribir en el archivo\n");
        fclose(copy_tpl_fp);
        return -1;
    }

    return 0;
}
