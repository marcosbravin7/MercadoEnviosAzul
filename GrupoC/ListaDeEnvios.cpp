//
// Created by santiago on 7/9/26.
//
#include "ListaDeEnvios.hpp"
#include <iostream>

ListaDeEnvios::ListaDeEnvios()
    : comienzo(nullptr), ultimo(nullptr), cantidad(0) {}

// Destructor. Aca se ve la diferencia entre destruir un nodo y
// destruir el objeto apuntado: se hacen LAS DOS COSAS, porque esta
// lista es la duena de los envios. Es el unico lugar del programa
// donde se ejecuta 'delete envio'.
ListaDeEnvios::~ListaDeEnvios()
{
    NodoEnvio* actual = comienzo;
    while (actual != nullptr)
    {
        NodoEnvio* aux = actual->siguiente;  // guardar antes de borrar
        delete actual->envio;                // destruye el envio (y su historial)
        delete actual;                       // destruye el nodo
        actual = aux;
    }
    comienzo = nullptr;
    ultimo = nullptr;
    cantidad = 0;
}

// Agrega al final.
void ListaDeEnvios::agregar(Envio* e)
{
    if (e == nullptr) return;

    NodoEnvio* nuevo = new NodoEnvio(e);

    if (comienzo == nullptr)      // caso lista vacia
    {
        comienzo = nuevo;
        ultimo = nuevo;
    }
    else                          // caso general: enganchar al final
    {
        ultimo->siguiente = nuevo;
        ultimo = nuevo;
    }
    cantidad++;
}

// Recorrido secuencial.
Envio* ListaDeEnvios::buscar(const std::string& codigo) const
{
    NodoEnvio* actual = comienzo;
    while (actual != nullptr)
    {
        if (actual->envio->getCodigo() == codigo)
        {
            return actual->envio;   // devuelve el envio, no el nodo
        }
        actual = actual->siguiente;
    }
    return nullptr;                 // no existe
}

bool ListaDeEnvios::existeCodigo(const std::string& codigo) const
{
    return buscar(codigo) != nullptr;
}

void ListaDeEnvios::mostrarTodos() const
{
    if (comienzo == nullptr)
    {
        std::cout << "No hay envios registrados." << std::endl;
        return;
    }
    NodoEnvio* actual = comienzo;
    while (actual != nullptr)
    {
        actual->envio->mostrar();
        actual = actual->siguiente;
    }
}
