//
// Created by santiago on 7/9/26.
//

#include <string>
#include "Envio.hpp"
#ifndef MERCADOENVIOSAZUL_LISTADEENVIOS_H
#define MERCADOENVIOSAZUL_LISTADEENVIOS_H
// ============================================================
//  NODO ENVIO
//  Nodo de la lista general. Solo estructura: apunta al envio
//  y al siguiente nodo. No contiene datos del paquete.
// ============================================================
class NodoEnvio
{
    friend class ListaDeEnvios;

    Envio* envio;
    NodoEnvio* siguiente;

    NodoEnvio(Envio* e) : envio(e), siguiente(nullptr) {}
};

// ============================================================
//  LISTA DE ENVIOS
//  Lista simplemente enlazada con TODOS los envios que el centro
//  conoce: los pendientes y tambien los ya despachados.
//
//  OWNERSHIP - esta es la pieza clave del diseno:
//  Esta lista es la UNICA DUENA de los objetos Envio. Su destructor
//  hace 'delete nodo->envio' ademas de 'delete nodo'.
//  ListaPendientes, en cambio, SOLO borra sus nodos y nunca los
//  envios. Por eso despachar un paquete elimina el nodo de
//  pendientes sin destruir el envio: el objeto sigue vivo aca, y
//  puede reprogramarse, entregarse o consultarse despues.
//
//  Los envios NO se eliminan de esta lista: un paquete entregado
//  sigue siendo consultable por codigo y conserva su historial.
// ============================================================
class ListaDeEnvios
{
    private:
        NodoEnvio* comienzo;
        NodoEnvio* ultimo;      // permite agregar al final en O(1)
        int cantidad;

    public:
        ListaDeEnvios();
        ~ListaDeEnvios();

        // Administra punteros crudos de los que es duena
        ListaDeEnvios(const ListaDeEnvios&) = delete;
        ListaDeEnvios& operator=(const ListaDeEnvios&) = delete;

        // Toma posesion del envio.
        void agregar(Envio* e);

        // busca en TODOS los envios, no solo en los pendientes.
        // Devuelve nullptr si no existe.
        Envio* buscar(const std::string& codigo) const;

        // verificar que el codigo no este repetido.
        bool existeCodigo(const std::string& codigo) const;

        void mostrarTodos() const;

        int getCantidad() const { return cantidad; }
        bool estaVacia()  const { return comienzo == nullptr; }
};

#endif //MERCADOENVIOSAZUL_LISTADEENVIOS_H
