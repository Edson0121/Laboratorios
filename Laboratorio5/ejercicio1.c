#include <stdio.h>
#include <stdlib.h>

// Definicion de la estructura del nodo
typedef struct nodo
{
    // Contenido de numeros
    int dato;
    // Puntero al nodo siguiente
    struct nodo *siguiente;
    // Puntero al nodo anterior
    struct nodo *anterior;
} NODO;

// Funciones
NODO *crearNodo(int dato);
// Doble asterisco porque se modifica
int insertarInicio(NODO **cabeza, int dato);
int insertarFinal(NODO **cabeza, int dato);
int eliminarNodo(NODO **cabeza, int dato);
void imprimirLista(NODO *cabeza);

int main()
{
    // Declaramos puntero cabeza
    NODO *cabeza = NULL;
    // Agregamos el valor de 1 al inicio
    insertarInicio(&cabeza, 1);
    insertarInicio(&cabeza, 2);
    insertarFinal(&cabeza, 3);
    insertarFinal(&cabeza, 4);
    eliminarNodo(&cabeza, 2);
    // Imprimimos la lista
    imprimirLista(cabeza);

    return 0;
}

// Recibe el dato a ingresar en el nodo
NODO *crearNodo(int dato)
{
    // Nueva estructura de nodo, inicializada en NULL
    NODO* nuevo = NULL;
    // Reservar memoria
    nuevo = (NODO*)malloc(sizeof(NODO));
    // Revisamos si se reservo la memoria
    if(nuevo != NULL)
    {
        // Asignamos el dato ingresado
        nuevo->dato = dato;
        // Asignamos los punteros
        nuevo->siguiente = NULL;
        nuevo->anterior = NULL;
    }
    return nuevo;
}

// Recibe el puntero de head y el dato a insertar
int insertarInicio(NODO **cabeza, int dato)
{
    // Se crea un nodo
    NODO* nuevo = NULL;
    // Se llama a la funcion de crear con el dato
    nuevo = crearNodo(dato);
    // Revisamos que se haya creado bien
    if(nuevo != NULL)
    {
        // Asignamos valores de los punteros
        nuevo->siguiente = *cabeza;
        nuevo->anterior = NULL;
        // Se revisa el puntero de cabeza, ya que si es diferente de NULL significa que ya existen datos en la lista
        if(*cabeza != NULL)
        {
            (*cabeza)->anterior = nuevo;
        }
        // Apuntar al nuevo nodo creado
        *cabeza = nuevo;
        // Se logro
        return 1;
    }
    // No se logro
    return 0;
}

int insertarFinal(NODO **cabeza, int dato)
{
    // Se define el nuevo nodo y un puntero auxiliar, para recorrer la lista
    NODO *nuevo = NULL, *nAux = *cabeza;
    // Creamos el nodo
    nuevo = crearNodo(dato);
    if(nuevo != NULL)
    {
        // Recorrer la lista hasta el final
        while (nAux->siguiente != NULL)
        {
            nAux = nAux->siguiente;
        }
        // Puntero anterior del nuevo nodo apunta al ultimo nodo
        nuevo->anterior = nAux;
        // Puntero siguiente del viejo nodo apunta al nuevo
        nAux->siguiente = nuevo;
        // Se logro
        return 1;
    }
    // No se logro
    return 0;
}

int eliminarNodo(NODO **cabeza, int dato)
{
    // Puntero al nodo actual, al nodo anterior y al nodo siguiente
    NODO *actual = *cabeza, *ant = NULL, *sig = NULL;
    // Revisamos el nodo actual
    while(actual != NULL)
    {
        // Buscamos el nodo con el mismo dato
        if(actual->dato == dato)
        {
            // Si es igual al primer nodo
            if(actual == *cabeza)
            {
                // Cambiamos la direccion de la cabeza
                *cabeza = actual->siguiente;
                // Revisamos si apunta a NULL
                if(actual->siguiente != NULL)
                {
                    // Eliminamos el enlace del nodo
                    actual->siguiente->anterior = NULL;
                }
            }
            // Si es el ultimo nodo
            else if(actual->siguiente == NULL)
            {
                // Se guarda el puntero de anterior en ant
                ant = actual->anterior;
                // Quitamos el enlace del nodo en la lista
                actual->anterior = NULL;
                // Al penultimo nodo lo definimos como el ultimo
                ant->siguiente = NULL;
            }
            else
            {
                // Guarda el puntero anterior del nodo actual
                ant = actual->anterior;
                // Borra la conexion del nodo actual con el nodo anterior
                actual->anterior = NULL;
                // Guarda el puntero siguiente del nodo actual
                sig = actual->siguiente;
                // Borra la conexion del nodo actual con el nodo siguiente
                actual->siguiente = NULL;
                // Reconecto los nodos anterior y siguiente
                ant->siguiente = sig;
                sig->anterior = ant;
            }
            // Se libera la memoria del nodo actual ya que no estaria mas en la lista
            free(actual);
            // Se logro eliminar
            return 1;
        }
        // Recorrer la lista
        actual = actual->siguiente;
    }
    // No se logro
    return 0;
}

void imprimirLista(NODO *cabeza)
{
    // Nodo auxiliar para no perder el puntero de la cabeza
    NODO *nAux = cabeza;
    // Recorrer la lista
    while (nAux != NULL)
    {
        // Imprimir dato
        printf("%d\n", nAux->dato);
        // Cambiar puntero por siguiente nodo
        nAux = nAux->siguiente;
    }
}