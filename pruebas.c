#include "testing.h"
#include "abb.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include<time.h>


static void prueba_crear_abb_vacio() {
	printf("\n");
	printf("PRUEBAS ABB CREAR VACIO\n");
	printf("\n");

	
    abb_t* abb = abb_crear(strcmp,NULL);

    print_test("Prueba ABB crear ABB vacio", abb);
    print_test("Prueba ABB la cantidad de elementos es 0", abb_cantidad(abb) == 0);
    print_test("Prueba ABB obtener clave A, es NULL, no existe", !abb_obtener(abb, "A"));
    print_test("Prueba ABB pertenece clave A, es false, no existe", !abb_pertenece(abb, "A"));
    print_test("Prueba ABB borrar clave A, es NULL, no existe", !abb_borrar(abb, "A"));

    abb_destruir(abb);

}

static void prueba_abb_insertar() {
	printf("\n");
	printf("PRUEBAS ABB INSERTAR\n");
	printf("\n");

    char* clave_1 = "5", *valor_1 = "cinco";
    char* clave_2 = "11", *valor_2 = "once";
    char* clave_3 = "9", *valor_3 = "nueve";


    abb_t* abb = abb_crear(strcmp,NULL);

    print_test("Prueba ABB insertar clave_1",abb_guardar(abb,clave_1,valor_1));
    print_test("Prueba ABB obtener clave_1 es valor_1",abb_obtener(abb,clave_1) == valor_1);
    print_test("Prueba ABB pertenece clave_1 es true",abb_pertenece(abb,clave_1));
    print_test("Prueba ABB la cantidad de elementos es 1",abb_cantidad(abb) == 1);
    print_test("Prueba ABB borrar clave_1 devuelve valor_1",abb_borrar(abb,clave_1) == valor_1);
    print_test("Prueba ABB la cantidad de elementos es 0",abb_cantidad(abb) == 0);

    print_test("Prueba ABB insertar clave_2",abb_guardar(abb,clave_2,valor_2));
    print_test("Prueba ABB obtener clave_2 es valor_2",abb_obtener(abb,clave_2) == valor_2);
    print_test("Prueba ABB insertar clave_3",abb_guardar(abb,clave_3,valor_3));
    print_test("Prueba ABB obtener clave_3 es valor_3",abb_obtener(abb,clave_3) == valor_3);
    print_test("Prueba ABB pertenece clave_2 es true",abb_pertenece(abb,clave_2));
    print_test("Prueba ABB pertenece clave_3 es true",abb_pertenece(abb,clave_3));
    print_test("Prueba ABB la cantidad de elementos es 2",abb_cantidad(abb) == 2);

    abb_destruir(abb);

}

static void prueba_abb_borrar() {
	printf("\n");
	printf("PRUEBAS ABB BORRAR\n");
	printf("\n");

    char* clave_1 = "8", *valor_1 = "ocho";
    char* clave_3 = "2", *valor_2 = "dos";
    char* clave_2 = "45", *valor_3 = "cuarenta y cinco";
    char* clave_4 = "11", *valor_4 = "once";
    char* clave_5 = "0", *valor_5 = "cero";

    abb_t* abb = abb_crear(strcmp,NULL);

    print_test("Prueba ABB insertar clave_1",abb_guardar(abb,clave_1,valor_1));
    print_test("Prueba ABB insertar clave_2",abb_guardar(abb,clave_2,valor_2));
    print_test("Prueba ABB insertar clave_3",abb_guardar(abb,clave_3,valor_3));
    print_test("Prueba ABB insertar clave_4",abb_guardar(abb,clave_4,valor_4));
    print_test("Prueba ABB insertar clave_5",abb_guardar(abb,clave_5,valor_5));

    print_test("Prueba ABB la cantidad de elementos es 5",abb_cantidad(abb) == 5);

    print_test("Prueba ABB borrar clave_5 devuelve valor_5",abb_borrar(abb,clave_5) == valor_5);
    print_test("Prueba ABB la cantidad de elementos es 4",abb_cantidad(abb) == 4);
    print_test("Prueba ABB borrar clave_5 devuelve NULL",!abb_borrar(abb,clave_5));
    print_test("Prueba ABB pertenece clave_5 es falso",!abb_pertenece(abb,clave_5));
    print_test("Prueba ABB obtener clave_5 devuelve NULL",!abb_obtener(abb,clave_5));

    print_test("Prueba ABB borrar clave_4 devuelve valor_4",abb_borrar(abb,clave_4) == valor_4);
    print_test("Prueba ABB la cantidad de elementos es 3",abb_cantidad(abb) == 3);
    print_test("Prueba ABB borrar clave_4 devuelve NULL",abb_borrar(abb,clave_4) == NULL);
    print_test("Prueba ABB pertenece clave_4 es falso",!abb_pertenece(abb,clave_4));
    print_test("Prueba ABB obtener clave_4 devuelve NULL",!abb_obtener(abb,clave_4));

   	print_test("Prueba ABB borrar clave_3 devuelve valor_3",abb_borrar(abb,clave_3) == valor_3);
   	print_test("Prueba ABB borrar clave_2 devuelve valor_2",abb_borrar(abb,clave_2) == valor_2);
   	print_test("Prueba ABB borrar clave_1 devuelve valor_1",abb_borrar(abb,clave_1) == valor_1);
   	print_test("Prueba ABB la cantidad de elementos es 0",abb_cantidad(abb) == 0);


    abb_destruir(abb);

}


static void prueba_abb_clave_vacia() {

	printf("\n");
	printf("PRUEBAS ABB CLAVE VACÍA\n");
	printf("\n");

    abb_t* abb = abb_crear(strcmp,NULL);

    char *clave = "", *valor = "";

    print_test("Prueba ABB insertar clave vacia", abb_guardar(abb, clave, valor));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Prueba abb obtener clave vacia es valor", abb_obtener(abb, clave) == valor);
    print_test("Prueba abb pertenece clave vacia, es true", abb_pertenece(abb, clave));
    print_test("Prueba abb borrar clave vacia, es valor", abb_borrar(abb, clave) == valor);
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    abb_destruir(abb);
}

char* generar_cadena_random(size_t largo_clave) {
	char* cadena = malloc(sizeof(char)*largo_clave);
    for (int i = 0; i < largo_clave-1; i++) {
        char randomletter = "0123456789"[rand()%9];
        cadena[i] = randomletter;
    }
    cadena[largo_clave-1] = '\0';
    return cadena;
}


static void prueba_abb_volumen(size_t largo, bool debug) {
	printf("\n");
	printf("PRUEBAS ABB VOLUMEN\n");
	printf("\n");

    abb_t* abb = abb_crear(strcmp,free);
    const size_t largo_clave = 10;
    char (*claves)[largo_clave] = malloc(largo * largo_clave);

    size_t* valores[largo];
    size_t claves_repetidas = 0;

    /* Inserta 'largo' parejas en el abb */
    bool ok = true;
    for (size_t i = 0; i < largo; i++) {
        valores[i] = malloc(sizeof(int*));
        char* cad_random = generar_cadena_random(largo_clave);
		if(abb_pertenece(abb, cad_random))claves_repetidas++;
        strcpy(claves[i],cad_random);
        *valores[i] = i;
        ok = abb_guardar(abb, claves[i], valores[i]);
        free(cad_random);
        if (!ok) break;
    }
    if (debug) print_test("Prueba abb almacenar muchos elementos", ok);
    if (debug) print_test("Prueba abb la cantidad de elementos es correcta", abb_cantidad(abb) == largo-claves_repetidas);

    /* Verifica que devuelva los valores correctos */
    for (size_t i = 0; i < largo; i++) {
        ok = abb_pertenece(abb, claves[i]);
        if (!ok) break;

        ok = abb_obtener(abb, claves[i]) == valores[i];
        if (!ok) break;
    }

    if (debug) print_test("Prueba abb pertenece y obtener muchos elementos", ok);
    if (debug) print_test("Prueba abb la cantidad de elementos es correcta", abb_cantidad(abb) == largo-claves_repetidas);

    /* Verifica que borre y devuelva los valores correctos */
    for (size_t i = 0; i < largo; i++) {
        ok = abb_borrar(abb, claves[i]) == valores[i];
        if (!ok) break;
    }


    if (debug) print_test("Prueba abb borrar muchos elementos", ok);
    if (debug) print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    abb_destruir(abb);

    abb = abb_crear(strcmp,free);

    /* Inserta 'largo' parejas en el abb */
    ok = true;
    for (size_t i = 0; i < largo; i++) {
        ok = abb_guardar(abb, claves[i], valores[i]);
        if (!ok) break;
    }

    /* Destruye el abb - debería liberar los enteros */
    abb_destruir(abb);
    free(claves);
}

static void prueba_abb_valor_null() {
	printf("\n");
	printf("PRUEBAS ABB VALOR NULL\n");
	printf("\n");
    abb_t* abb = abb_crear(strcmp,NULL);

    char *clave = "", *valor = NULL;

    /* Inserta 1 valor y luego lo borra */
    print_test("Prueba abb insertar clave vacia valor NULL", abb_guardar(abb, clave, valor));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Prueba abb obtener clave vacia es valor NULL", abb_obtener(abb, clave) == valor);
    print_test("Prueba abb pertenece clave vacia, es true", abb_pertenece(abb, clave));
    print_test("Prueba abb borrar clave vacia, es valor NULL", abb_borrar(abb, clave) == valor);
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    abb_destruir(abb);

}

static void prueba_abb_reemplazar() {

	printf("\n");
	printf("PRUEBAS ABB REEMPLAZAR\n");
	printf("\n");

    abb_t* abb = abb_crear(strcmp,NULL);

    char *clave1 = "9", *valor1a = "nueve", *valor1b = "nine";
    char *clave2 = "11", *valor2a = "once", *valor2b = "eleven";

    /* Inserta 2 valores y luego los reemplaza */
    print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1a));
    print_test("Prueba abb obtener clave1 es valor1a", abb_obtener(abb, clave1) == valor1a);
    print_test("Prueba abb obtener clave1 es valor1a", abb_obtener(abb, clave1) == valor1a);
    print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2a));
    print_test("Prueba abb obtener clave2 es valor2a", abb_obtener(abb, clave2) == valor2a);
    print_test("Prueba abb obtener clave2 es valor2a", abb_obtener(abb, clave2) == valor2a);
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    print_test("Prueba abb insertar clave1 con otro valor", abb_guardar(abb, clave1, valor1b));
    print_test("Prueba abb obtener clave1 es valor1b", abb_obtener(abb, clave1) == valor1b);
    print_test("Prueba abb obtener clave1 es valor1b", abb_obtener(abb, clave1) == valor1b);
    print_test("Prueba abb insertar clave2 con otro valor", abb_guardar(abb, clave2, valor2b));
    print_test("Prueba abb obtener clave2 es valor2b", abb_obtener(abb, clave2) == valor2b);
    print_test("Prueba abb obtener clave2 es valor2b", abb_obtener(abb, clave2) == valor2b);
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    abb_destruir(abb);
}

static void prueba_abb_reemplazar_con_destruir() {
	printf("\n");
	printf("PRUEBAS ABB REEMPLAZAR CON DESTRUIR\n");
	printf("\n");

    abb_t* abb = abb_crear(strcmp,free);

    char *clave1 = "1", *valor1a, *valor1b;
    char *clave2 = "2", *valor2a, *valor2b;

    /* Pide memoria para 4 valores */
    valor1a = malloc(10 * sizeof(char));
    valor1b = malloc(10 * sizeof(char));
    valor2a = malloc(10 * sizeof(char));
    valor2b = malloc(10 * sizeof(char));

    /* Inserta 2 valores y luego los reemplaza (debe liberar lo que reemplaza) */
    print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1a));
    print_test("Prueba abb obtener clave1 es valor1a", abb_obtener(abb, clave1) == valor1a);
    print_test("Prueba abb obtener clave1 es valor1a", abb_obtener(abb, clave1) == valor1a);
    print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2a));
    print_test("Prueba abb obtener clave2 es valor2a", abb_obtener(abb, clave2) == valor2a);
    print_test("Prueba abb obtener clave2 es valor2a", abb_obtener(abb, clave2) == valor2a);
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    print_test("Prueba abb insertar clave1 con otro valor", abb_guardar(abb, clave1, valor1b));
    print_test("Prueba abb obtener clave1 es valor1b", abb_obtener(abb, clave1) == valor1b);
    print_test("Prueba abb obtener clave1 es valor1b", abb_obtener(abb, clave1) == valor1b);
    print_test("Prueba abb insertar clave2 con otro valor", abb_guardar(abb, clave2, valor2b));
    print_test("Prueba abb obtener clave2 es valor2b", abb_obtener(abb, clave2) == valor2b);
    print_test("Prueba abb obtener clave2 es valor2b", abb_obtener(abb, clave2) == valor2b);
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    /* Se destruye el abb (se debe liberar lo que quedó dentro) */
    abb_destruir(abb);
}



static void prueba_abb_iterar() {
	printf("\n");
	printf("PRUEBAS ABB ITERAR\n");
	printf("\n");

    abb_t* abb = abb_crear(strcmp,NULL);

    char *claves[] = {"18", "25", "73", "14"};
    char *valores[] = {"gato", "perro", "loro","pez"};

    /* Inserta 4 valores */
    print_test("Prueba abb insertar clave1", abb_guardar(abb, claves[0], valores[0]));
    print_test("Prueba abb insertar clave2", abb_guardar(abb, claves[1], valores[1]));
    print_test("Prueba abb insertar clave3", abb_guardar(abb, claves[2], valores[2]));
	print_test("Prueba abb insertar clave4", abb_guardar(abb, claves[3], valores[3]));

    // Prueba de iteración sobre las claves almacenadas.
    abb_iter_t* iter = abb_iter_in_crear(abb);
    const char *clave;

    print_test("Prueba abb iterador esta al final, es false", !abb_iter_in_al_final(iter));

    /* Primer valor */
    clave = abb_iter_in_ver_actual(iter);
    print_test("Actual es el correcto", strcmp(abb_iter_in_ver_actual(iter),claves[3])==0);
    print_test("Prueba abb iterador ver actual, no es el mismo puntero", clave != claves[3]);
    print_test("Prueba abb iterador avanzar es true", abb_iter_in_avanzar(iter));
    print_test("Prueba abb iterador esta al final, es false", !abb_iter_in_al_final(iter));

    /* Segundo valor */
    clave = abb_iter_in_ver_actual(iter);
    print_test("Actual es el correcto", strcmp(abb_iter_in_ver_actual(iter),claves[0])==0);
    print_test("Prueba abb iterador ver actual, no es el mismo puntero", clave != claves[0]);
    print_test("Prueba abb iterador avanzar es true", abb_iter_in_avanzar(iter));
    print_test("Prueba abb iterador esta al final, es false", !abb_iter_in_al_final(iter));

    /* Tercer valor */
    clave = abb_iter_in_ver_actual(iter);
    print_test("Actual es el correcto", strcmp(abb_iter_in_ver_actual(iter),claves[1])==0);
    print_test("Prueba abb iterador ver actual, no es el mismo puntero", clave != claves[1]);
    print_test("Prueba abb iterador avanzar es true", abb_iter_in_avanzar(iter));
    print_test("Prueba abb iterador esta al final, es false", !abb_iter_in_al_final(iter));

    /* Cuarto valor */
    clave = abb_iter_in_ver_actual(iter);
    print_test("Actual es el correcto", strcmp(abb_iter_in_ver_actual(iter),claves[2])==0);
    print_test("Prueba abb iterador ver actual, no es el mismo puntero", clave != claves[2]);
    print_test("Prueba abb iterador avanzar es true", abb_iter_in_avanzar(iter));
    print_test("Prueba abb iterador esta al final, es true", abb_iter_in_al_final(iter));

    /* Vuelve a tratar de avanzar, por las dudas */
    print_test("Prueba abb iterador ver actual, es NULL", !abb_iter_in_ver_actual(iter));
    print_test("Prueba abb iterador avanzar es false", !abb_iter_in_avanzar(iter));
    print_test("Prueba abb iterador esta al final, es true", abb_iter_in_al_final(iter));

    abb_iter_in_destruir(iter);
    abb_destruir(abb);
}

typedef struct visitar_aux{
	char* anterior;
	bool* es_inorder;
}visitar_aux_t;

visitar_aux_t* visitar_aux_crear(char* clave, bool* es_inorder){
	visitar_aux_t* visitar_aux = malloc(sizeof(visitar_aux_t));
	if(!visitar_aux) return NULL;
	visitar_aux->anterior = malloc(sizeof(clave));
	strcpy(visitar_aux->anterior, clave);
	visitar_aux->es_inorder = es_inorder;
	return visitar_aux;
}

bool imprimir(const char* clave,void* dato, void* extra) {
	char* clave_aux = malloc((sizeof(char)*strlen(clave))+sizeof(char));
	strcpy(clave_aux, clave);
	visitar_aux_t* auxiliar = (visitar_aux_t*)extra; 
	if(strcmp(clave_aux, auxiliar->anterior)>=0 && auxiliar->es_inorder) {
		free(auxiliar->anterior);
		auxiliar->anterior = clave_aux;
		*auxiliar->es_inorder = true;
		return true;
	}else  auxiliar->es_inorder = false;
	free(clave_aux);
	return false;
}

static void prueba_abb_iterar_interno(size_t largo, bool debug) {
	printf("\n");
	printf("PRUEBAS ITERADOR INTERNO\n");
	printf("\n");

    abb_t* abb = abb_crear(strcmp,free);
    const size_t largo_clave = 10;
    char (*claves)[largo_clave] = malloc(largo * largo_clave);

    size_t* valores[largo];
    size_t claves_repetidas = 0;

    /* Inserta 'largo' parejas en el abb */
    bool ok = true;
    for (size_t i = 0; i < largo; i++) {
        valores[i] = malloc(sizeof(int*));
        char* cad_random = generar_cadena_random(largo_clave);
		if(abb_pertenece(abb, cad_random))claves_repetidas++;
        strcpy(claves[i],cad_random);
        *valores[i] = i;
        ok = abb_guardar(abb, claves[i], valores[i]);
        free(cad_random);
        if (!ok) break;
    }

    if (claves_repetidas) printf("CLAVES REPETIDAS: %ld\n",claves_repetidas);

    if (debug) print_test("Prueba abb almacenar muchos elementos", ok);
    if (debug) print_test("Prueba abb la cantidad de elementos es correcta", abb_cantidad(abb) == largo-claves_repetidas);

    /*size_t e = 0;
    size_t* extra = &e;*/

	bool es_inorder = true;
	char* anterior = "0";
	visitar_aux_t* auxiliar = visitar_aux_crear(anterior, &es_inorder);
	if(!auxiliar) return;
    abb_in_order(abb,imprimir, auxiliar);
    print_test("Prueba abb iterador interno cumple que es inorder", auxiliar->es_inorder);
	free(auxiliar->anterior);
	free(auxiliar);

	 /* Verifica que borre y devuelva los valores correctos */
        if (!claves_repetidas) {
        for (size_t i = 0; i < largo; i++) {
            ok = abb_borrar(abb, claves[i]) == valores[i];
            free(valores[i]);
            if (!ok) break;
        }

        if (debug) print_test("Prueba abb borrar muchos elementos", ok);
        if (debug) print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);
    }
    else print_test("No se pueden realizar las pruebas de iteración con claves reptidas",true);
    /* Destruye el abb y crea uno nuevo que sí libera */
    abb_destruir(abb);
    free(claves);

}


static void prueba_abb_iterar_volumen(size_t largo, bool debug) {
    printf("\n");
    printf("PRUEBAS ABB ITERAR EN VOLUMEN\n");
    printf("\n");

    abb_t* abb = abb_crear(strcmp,free);
    const size_t largo_clave = 10;
    char (*claves)[largo_clave] = malloc(largo * largo_clave);

    size_t* valores[largo];
    size_t claves_repetidas = 0;

    /* Inserta 'largo' parejas en el abb */
    bool ok = true;
    for (size_t i = 0; i < largo; i++) {
        valores[i] = malloc(sizeof(int*));
        char* cad_random = generar_cadena_random(largo_clave);
        if(abb_pertenece(abb, cad_random))claves_repetidas++;
        strcpy(claves[i],cad_random);
        *valores[i] = i;
        ok = abb_guardar(abb, claves[i], valores[i]);
        free(cad_random);
        if (!ok) break;
    }

    if (debug) print_test("Prueba abb almacenar muchos elementos", ok);
    if (debug) print_test("Prueba abb la cantidad de elementos es correcta", abb_cantidad(abb) == largo-claves_repetidas);

    abb_iter_t* iter = abb_iter_in_crear(abb);
    print_test("Prueba abb iterador esta al final, es false", !abb_iter_in_al_final(iter));

    ok = true;
    unsigned i;
    const char *clave;
    size_t *valor;

    if (!claves_repetidas) {
        printf("CLAVES REPETIDAS: %ld\n",claves_repetidas);
        for (i = 0; i < largo; i++) {
            if (abb_iter_in_al_final(iter)) {
                ok = false;
                break;
            }
            clave = abb_iter_in_ver_actual(iter);
            if (clave == NULL) {
                ok = false;
                break;
            }
            
            valor = abb_obtener(abb, clave);
            if (valor == NULL) {
                ok = false;
                break;
            }
            *valor = largo;
            abb_iter_in_avanzar(iter);
        }
        print_test("Prueba abb iteración en volumen", ok);
        print_test("Prueba abb iteración en volumen, recorrio todo el largo", i == largo-claves_repetidas);
        print_test("Prueba abb iterador esta al final, es true", abb_iter_in_al_final(iter));

        ok = true;
        for (i = 0; i < largo; i++) {
            if ( *valores[i] != largo ) {
                ok = false;
                break;
            }
        }
        print_test("Prueba abb iteración en volumen, se cambiaron todo los elementos", ok);
    }
    else print_test("No se pueden realizar las pruebas de iteración con claves reptidas",true);

    free(claves);
    abb_iter_in_destruir(iter);
    abb_destruir(abb);
}







void pruebas_abb_alumno() {
    /* Ejecuta todas las pruebas unitarias. */
    prueba_crear_abb_vacio();
    prueba_abb_insertar();
    prueba_abb_borrar();
    prueba_abb_clave_vacia();
    prueba_abb_valor_null();
    prueba_abb_volumen(5000,true);
    prueba_abb_reemplazar();
    prueba_abb_reemplazar_con_destruir();
    prueba_abb_iterar();
    prueba_abb_iterar_volumen(5000,true);
    prueba_abb_iterar_interno(50,true);
}






