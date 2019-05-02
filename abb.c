#include "abb.h"
#include "pila.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>


typedef struct abb_nodo {
	char* clave;
	void* dato;
	struct abb_nodo* izq;
	struct abb_nodo* der; 
}abb_nodo_t;

struct abb {
	abb_nodo_t* raiz;
	abb_comparar_clave_t cmp;
	abb_destruir_dato_t destruir_dato;
	size_t cantidad;
};

struct abb_iter {
	const abb_t* abb;
	pila_t* pila;
};



// PRIMITIVAS DEL ABB_NODO //


abb_nodo_t* abb_nodo_crear(const char* clave,void* dato) {
	abb_nodo_t* abb_nodo = malloc(sizeof(abb_nodo_t));
	if (!abb_nodo) return NULL;
	char* copia_clave = malloc(sizeof(char)*strlen(clave)+1);
	if (!copia_clave) {
		free(abb_nodo);
		return NULL;
	}
	strcpy(copia_clave,clave);
	abb_nodo -> clave = copia_clave;
	abb_nodo -> dato = dato;
	abb_nodo -> izq = NULL;
	abb_nodo -> der = NULL;
	return abb_nodo;
}

abb_nodo_t* _buscar_nodo(abb_nodo_t* nodo,const abb_t* arbol, const char* clave){
	if(!nodo)return NULL;
	int comparacion = arbol->cmp(nodo->clave, clave);
	if(comparacion == 0) return nodo;
	if(comparacion < 0) return _buscar_nodo(nodo->der, arbol, clave);
	return _buscar_nodo(nodo->izq, arbol, clave);
}

void abb_nodo_destruir(abb_nodo_t* abb_nodo,abb_destruir_dato_t destruir_dato) {
	if (!abb_nodo) return;
	free(abb_nodo->clave);
	if (destruir_dato) destruir_dato(abb_nodo->dato);
	free(abb_nodo);
}


// AUXILIARES DE PRIMITIVAS DEL ABB //

bool abb_guardar_raiz(abb_t* arbol,const char* clave,void* dato) {
	// Sólo se ejecuta si el Árbol no tiene raíz. Crea y agrega la raíz del Árbol.
	abb_nodo_t* abb_nodo = abb_nodo_crear(clave,dato);
	if (!abb_nodo) return false;
	arbol->raiz = abb_nodo;
	arbol->cantidad++;
	return true;
}

bool _abb_guardar(abb_t* arbol,abb_nodo_t* actual,const char* clave,void* dato,abb_nodo_t* padre,bool es_izquierdo) {
	if (!actual) {
		abb_nodo_t* nuevo_abb_nodo = abb_nodo_crear(clave,dato);
		if (!nuevo_abb_nodo) return false;
		if (es_izquierdo) padre -> izq = nuevo_abb_nodo;
		else padre -> der = nuevo_abb_nodo;
		arbol->cantidad++;
		return true;
	}
	int comparacion = arbol->cmp(clave, actual->clave);
	if (comparacion == 0) {
		if (arbol->destruir_dato) arbol->destruir_dato(actual->dato);
		actual->dato = dato;
		return true;
		}
	if (comparacion < 0) return _abb_guardar(arbol,actual->izq,clave,dato,actual,true);
	return _abb_guardar(arbol,actual->der,clave,dato,actual,false);
}



void _abb_destruir(abb_nodo_t* abb_nodo,abb_destruir_dato_t destruir_dato) {
	if (!abb_nodo) return;
	if (!abb_nodo->izq && !abb_nodo->der) {
		abb_nodo_destruir(abb_nodo,destruir_dato);
		return;
	}
	_abb_destruir(abb_nodo->izq,destruir_dato);
	_abb_destruir(abb_nodo->der,destruir_dato);
	abb_nodo_destruir(abb_nodo,destruir_dato);
	return;
}

void swappear_nodos(abb_nodo_t* actual, abb_nodo_t* hijo) {
	// Recibe dos nodos e intercambia sus claves y valores
	char* aux_clave = actual->clave;
	void* aux_dato = actual->dato;
	actual->clave = hijo->clave;
	actual->dato = hijo->dato;
	hijo->clave = aux_clave;
	hijo->dato = aux_dato;
}

abb_nodo_t* buscar_nodo_a_swappear(abb_nodo_t* abb_nodo) {
	// Función auxiliar para destruir_padre_completo: devuelve el menor de sus nietos izquierdo (o su hijo derecho, de no tener)
	if (!abb_nodo->izq) return abb_nodo;
	return buscar_nodo_a_swappear(abb_nodo->izq);
}

abb_nodo_t* buscar_padre_nodo_a_swappear(abb_nodo_t* abb_nodo,abb_nodo_t* nodo_a_swappear) {
	// Recibe un nodo seleccionado para swappear, y devuelve su padre
	if (!abb_nodo) return NULL;
	if (abb_nodo->izq == nodo_a_swappear) return abb_nodo;
	return buscar_padre_nodo_a_swappear(abb_nodo->izq,nodo_a_swappear);
}

void* destruir_hoja(abb_t* arbol,abb_nodo_t* actual, abb_nodo_t* padre) {
	// Auxiliar para _abb_borrar: recibe un nodo padre, su hijo, intercambia su clave y valor, y destruye al hijo
	void* dato = actual -> dato;
	if (!padre) arbol -> raiz = NULL;
	else {
		if (actual == padre->izq) padre->izq = NULL;
		else padre->der = NULL;
	}
	abb_nodo_destruir(actual,NULL);
	return dato;
}

void* destruir_padre_parcial(abb_nodo_t* actual,abb_nodo_t* padre,bool tiene_hijo_izquierdo) {
	// Auxiliar para _abb_borrar: recibe un padre, su hijo, intercambia su clave,valor, modifica los hijos y destruye al hijo original
	void* dato = actual->dato;
	abb_nodo_t* nodo_a_swappear;
	if (tiene_hijo_izquierdo) nodo_a_swappear = actual->izq;
	else nodo_a_swappear = actual->der;
	swappear_nodos(actual,nodo_a_swappear);
	actual->izq = nodo_a_swappear -> izq;
	actual->der = nodo_a_swappear -> der;
	abb_nodo_destruir(nodo_a_swappear,NULL);
	return dato;
}


void* destruir_padre_completo(abb_nodo_t* actual,abb_nodo_t* padre) {
	// Auxiliar para _abb_borrar: recibe un padre, su hijo, busca un nodo a swappear, intercambia valor,clave,hijos y lo destruye
	void* dato = actual->dato;
	abb_nodo_t* nodo_a_swappear = buscar_nodo_a_swappear(actual->der);
	if (nodo_a_swappear == actual->der) {
		swappear_nodos(actual,nodo_a_swappear);
		actual->der = nodo_a_swappear->der;
		}
	else {
		abb_nodo_t* padre_nodo_a_swappear = buscar_padre_nodo_a_swappear(actual->der,nodo_a_swappear);
		swappear_nodos(actual,nodo_a_swappear);
		padre_nodo_a_swappear->izq = nodo_a_swappear->der;
		
	}
	abb_nodo_destruir(nodo_a_swappear,NULL);
	return dato;
}



void* _abb_borrar(abb_t* arbol,abb_nodo_t* actual,const char* clave,abb_comparar_clave_t cmp,abb_nodo_t* padre) {
	if (!actual) return NULL;
	int comparacion = cmp(clave,actual->clave);
	if (comparacion == 0) {
		arbol->cantidad --;
		if (!actual->izq && !actual->der) {
			return (void*) destruir_hoja(arbol,actual,padre);
		}
		if (!actual->izq) return (void*) destruir_padre_parcial(actual,padre,false);
		if (!actual->der) return (void*) destruir_padre_parcial(actual,padre,true);
		return (void*) destruir_padre_completo(actual,padre);
	}
	if (comparacion < 0) return _abb_borrar(arbol,actual->izq,clave,cmp,actual);
	return _abb_borrar(arbol,actual->der,clave,cmp,actual);
}



// PRIMITIVAS DEL ABB //


abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato) {
	abb_t* abb = malloc(sizeof(abb_t));
	if (!abb) return NULL;
	abb -> raiz = NULL;
	abb -> cmp = cmp;
	abb -> destruir_dato = destruir_dato;
	abb -> cantidad = 0;
	return abb;
}

bool abb_guardar(abb_t* arbol, const char* clave, void* dato) {
	bool guardado_ok;
	if (!arbol->raiz) guardado_ok = abb_guardar_raiz(arbol,clave,dato);
	else guardado_ok = _abb_guardar(arbol,arbol->raiz,clave,dato,NULL,true);
	return guardado_ok;
}


void* abb_borrar(abb_t* arbol, const char* clave) {
	void* dato = _abb_borrar(arbol,arbol->raiz,clave,arbol->cmp,NULL);
	return dato;
}


void* abb_obtener(const abb_t* arbol, const char* clave) {
	if (!arbol) return NULL;
	abb_nodo_t* nodo_buscado = _buscar_nodo(arbol->raiz, arbol, clave);
	if(!nodo_buscado)return NULL;
	return nodo_buscado->dato;
}

bool abb_pertenece(const abb_t *arbol, const char* clave) {
	if (!arbol) return false;
	if(!_buscar_nodo(arbol->raiz, arbol, clave))return false;
	return true;
}

size_t abb_cantidad(abb_t *arbol) {
	return arbol -> cantidad;
}

void abb_destruir(abb_t *arbol) {
	_abb_destruir(arbol->raiz,arbol->destruir_dato);
	free(arbol);
}

// ITERADOR INTERNO //


bool _abb_in_order(abb_nodo_t* abb_nodo, bool visitar(const char*, void*, void*), void *extra) {
	if (!abb_nodo) return true;
	if(!_abb_in_order(abb_nodo->izq,visitar,extra) || !visitar(abb_nodo->clave,abb_nodo->dato,extra) || !_abb_in_order(abb_nodo->der,visitar,extra))return false;
	return true;
}


void abb_in_order(abb_t *arbol, bool visitar(const char*, void*, void*), void *extra) {
	_abb_in_order(arbol->raiz,visitar,extra);
}



// PRIMITIVAS DEL ITERADOR EXTERNO //

void apilar_nodos(pila_t* pila,abb_nodo_t* abb_nodo) {
	if (!abb_nodo) return;
	pila_apilar(pila,abb_nodo);
	apilar_nodos(pila,abb_nodo->izq);
}

abb_iter_t* abb_iter_in_crear(const abb_t *arbol) {
	abb_iter_t* abb_iter_in = malloc(sizeof(abb_iter_t));
	if (!abb_iter_in) return NULL;
	abb_iter_in -> abb = arbol;
	abb_iter_in -> pila = pila_crear();
	if (!abb_iter_in -> pila) {
		free(abb_iter_in);
		return NULL;
	}
	if (arbol->raiz) {
		apilar_nodos(abb_iter_in->pila,arbol->raiz);
	}
	return abb_iter_in;
}


bool abb_iter_in_avanzar(abb_iter_t* iter) {
	if (pila_esta_vacia(iter->pila)) return false;
	abb_nodo_t* desapilado = pila_desapilar(iter->pila);
	if (desapilado->der) {
		apilar_nodos(iter->pila,desapilado->der);
	}
	return true;
}


const char* abb_iter_in_ver_actual(const abb_iter_t* iter) {
	if (pila_esta_vacia(iter->pila)) return NULL;
	abb_nodo_t* desapilado = pila_ver_tope(iter->pila);
	return desapilado->clave;
}

bool abb_iter_in_al_final(const abb_iter_t* iter) {
	return pila_esta_vacia(iter->pila);
}

void abb_iter_in_destruir(abb_iter_t* iter) {
	pila_destruir(iter->pila);
	free(iter);
}
