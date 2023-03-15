#include <stdio.h>
#include "claves.h"

int total_correctos = 0;

// El cliente inicia el servidor
int Test1_C(){
    int resultado = init();
    if (resultado == 0) {
        return 1;
    } else {
        printf("[ERROR] Error en test 1_C (cliente inicia el servidor). Valor retornado %i, se esperaba 0\n",resultado);
        return 0;
    }
}

// El cliente crea una tupla
int Test2_C(){
    init();
    int key = 4;
    char *value1 = "Prueba1";
    int value2 = 2;
    double value3 = 8;

    int resultado = set_value(key, value1, value2, value3);
    if (resultado == 0) {
        return 1;
    } else {
        printf("[ERROR] Error en test 2_C (cliente crea una tupla). Valor retornado %i, se esperaba 0\n",resultado);
        return 0;
    }
}

// El cliente lee una tupla
int Test3_C(){
    init();
    // Se crea tupla primero
    int key1 = 4;
    char *value10 = "Prueba1";
    int value20 = 2;
    double value30 = 8;

    set_value(key1, value10, value20, value30);

    // Se lee tupla
    int key = 4;

    char* value1 = "";   int value2; double value3;
    
    int resultado = get_value(key, value1, &value2, &value3);
    if (resultado == 0) {
        return 1;
    } else {
        printf("[ERROR] Error en test 3_C (cliente lee una tupla). Valor retornado %i, se esperaba 0\n",resultado);
        return 0;
    }
}

// El cliente modifica una tupla
int Test4_C(){
    init();
    // Se crea tupla primero
    int key1 = 4;
    char *value10 = "Prueba1";
    int value20 = 2;
    double value30 = 8;

    set_value(key1, value10, value20, value30);

    // Se modifica tupla
    int key = 4;
    char *value1 = "Prueba2";
    int value2 = 3;
    double value3 = 10;

    int resultado = modify_value(key, value1, value2, value3);
    if (resultado == 0) {
        return 1;
    } else {
        printf("[ERROR] Error en test 4_C (cliente modifica una tupla). Valor retornado %i, se esperaba 0\n",resultado);
        return 0;
    }
}

// El cliente elimina una tupla
int Test5_C(){
    init();
    // Se crea tupla primero
    int key1 = 4;
    char *value10 = "Prueba1";
    int value20 = 2;
    double value30 = 8;

    set_value(key1, value10, value20, value30);

    // Se elimina tupla
    int key = 4;

    int resultado = delete_key(key);
    if (resultado == 0) {
        return 1;
    } else {
        printf("[ERROR] Error en test 5_C (cliente elimina una tupla). Valor retornado %i, se esperaba 0\n",resultado);
        return 0;
    }
}

// El cliente comprueba si existe una tupla existente
int Test6_C(){
    init();
    // Se crea tupla primero
    int key1 = 4;
    char *value10 = "Prueba1";
    int value20 = 2;
    double value30 = 8;

    set_value(key1, value10, value20, value30);

    // Se comprueba si existe
    int key = 4;

    int resultado = exist(key);
    if (resultado == 1) {
        return 1;
    } else {
        printf("[ERROR] Error en test 6_C (cliente comprueba que existe una tupla). Valor retornado %i, se esperaba 1\n",resultado);
        return 0;
    }
}

// El cliente copia tupla a key nueva
int Test7_C(){
    init();
    // Se crea tupla primero
    int key1 = 4;
    char *value10 = "Prueba1";
    int value20 = 2;
    double value30 = 8;

    set_value(key1, value10, value20, value30);

    // Se copia a key2
    int key2 = 2;

    int resultado = copy_key(key1,key2);
    if (resultado == 0) {
        return 1;
    } else {
        printf("[ERROR] Error en test 7_C (cliente copia una tupla en nueva key). Valor retornado %i, se esperaba 0\n",resultado);
        return 0;
    }
}

// El cliente comprueba si existe una tupla no existente
int Test8_C(){
    init();
    // Se comprueba si existe
    int key = 4;

    int resultado = exist(key);
    if (resultado == 0) {
        return 1;
    } else {
        printf("[ERROR] Error en test 8_C (cliente comprueba que existe una tupla no existente). Valor retornado %i, se esperaba 0\n",resultado);
        return 0;
    }
}

// El cliente copia tupla a key nueva
int Test9_C(){
    init();
    // Se crea tupla primero
    int key1 = 4;
    char *value10 = "Prueba1";
    int value20 = 2;
    double value30 = 8;

    set_value(key1, value10, value20, value30);

    // Se crea segunda tupla
    int key2 = 2;
    char *value11 = "Prueba2";
    int value21 = 4;
    double value31 = 10;

    set_value(key2, value11, value21, value31);

    // Se copia a key2
    int resultado = copy_key(key1,key2);
    if (resultado == 0) {
        return 1;
    } else {
        printf("[ERROR] Error en test 9_C (cliente copia una tupla en key ya en uso). Valor retornado %i, se esperaba 0\n",resultado);
        return 0;
    }
}

// El cliente crea una tupla (ya existe una con la misma key)
int Test1_NC(){
    init();
    // Se crea tupla primero
    int key1 = 4;
    char *value10 = "Prueba1";
    int value20 = 2;
    double value30 = 8;

    set_value(key1, value10, value20, value30);

    // Se crea segunda tupla
    int key2 = 4;
    char *value1 = "Prueba2";
    int value2 = 4;
    double value3 = 10;

    int resultado = set_value(key2, value1, value2, value3);
    if (resultado == -1) {
        return 1;
    } else {
        printf("[ERROR] Error en test 1_NC (cliente crea una tupla con una key que ya existe). Valor retornado %i, se esperaba -1\n",resultado);
        return 0;
    }
}

// El cliente lee una tupla que no existe
int Test2_NC(){
    init();
    // Se lee tupla
    int key = 4;

    char* value1 = "";   int value2; double value3;
    
    int resultado = get_value(key, value1, &value2, &value3);
    if (resultado == -1) {
        return 1;
    } else {
        printf("[ERROR] Error en test 2_NC (cliente lee una tupla que no existe). Valor retornado %i, se esperaba -1\n",resultado);
        return 0;
    }
}

// El cliente modifica una tupla que no existe
int Test3_NC(){
    init();
    // Se modifica tupla
    int key = 4;
    char *value1 = "Prueba2";
    int value2 = 3;
    double value3 = 10;

    int resultado = modify_value(key, value1, value2, value3);

    if (resultado == -1) {
        return 1;
    } else {
        printf("[ERROR] Error en test 3_NC (cliente crea una tupla con una key que ya existe). Valor retornado %i, se esperaba -1\n",resultado);
        return 0;
    }
}

// El cliente elimina una tupla que no existe
int Test4_NC(){
    init();
    // Se elimina tupla
    int key = 4;

    int resultado = delete_key(key);
    if (resultado == -1) {
        return 1;
    } else {
        printf("[ERROR] Error en test 4_NC (cliente elimina una tupla que no existe). Valor retornado %i, se esperaba -1\n",resultado);
        return 0;
    }
}

// El cliente copia una tupla que no existe
int Test5_NC(){
    init();
    // Se copia tupla
    int key1 = 4;
    int key2 = 2;

    int resultado = copy_key(key1,key2);
    if (resultado == -1) {
        return 1;
    } else {
        printf("[ERROR] Error en test 5_NC (cliente copia una tupla que no existe). Valor retornado %i, se esperaba -1\n",resultado);
        return 0;
    }
}


int main(){
    printf("----------EJECUTANDO TESTS----------\n");
    total_correctos += Test1_C();
    total_correctos += Test2_C();
    total_correctos += Test3_C();
    total_correctos += Test4_C();
    total_correctos += Test5_C();
    total_correctos += Test6_C();
    total_correctos += Test7_C();
    total_correctos += Test8_C();
    total_correctos += Test9_C();
    total_correctos += Test1_NC();
    total_correctos += Test2_NC();
    total_correctos += Test3_NC();
    total_correctos += Test4_NC();
    total_correctos += Test5_NC();
    printf("\n");
    if (total_correctos == 14) {
        printf("[OK] Todos los tests funcionaron correctamente (%i correctos)",total_correctos);
    } else {
        printf("[TESTS PASADOS CON ERRORES] Los tests se pasaron con errores (%i correctos)",total_correctos);
    }
    return 0;
}