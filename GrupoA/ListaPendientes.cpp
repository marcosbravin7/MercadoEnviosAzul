
#include "ListaPendientes.hpp"

#include "NodoPendiente.hpp"
#include <stdexcept>

////implementacion de los metodos del .hpp

ListaPendientes::ListaPendientes() //Constructor
{
   comienzo=nullptr;
}




ListaPendientes::~ListaPendientes() //Destructor
{
    NodoPendiente* aux=comienzo;
    while (aux!=nullptr)
    {
        comienzo= aux->siguiente;
        delete aux;
        aux=comienzo;
    }
}






//Metodo para agregar un paquete a la lista, segun el orden de prioridad

void ListaPendientes::agregarPaquete(Envio* envio)
{
    NodoPendiente* nuevoPaquete = new NodoPendiente(envio);

    // Los niveles tienen el valor numerico de su prioridad:
    // EXPRESS (1), PRIORITARIO (2), ESTANDAR (3).
    // Se inserta despues de los envios de igual prioridad para
    // conservar el orden de llegada.
    if (comienzo == nullptr or ((envio->getNivel()) < (comienzo->envio->getNivel())))
    {
        nuevoPaquete->siguiente = comienzo;
        comienzo = nuevoPaquete;
        return;
    }

    NodoPendiente* actual = comienzo;
    while (actual->siguiente != nullptr && (actual->siguiente->envio->getNivel() <= (envio->getNivel())))
    {
        actual = actual->siguiente;
    }

    nuevoPaquete->siguiente = actual->siguiente;
    actual->siguiente = nuevoPaquete;
}

void ListaPendientes::reordenar(Envio* envio) //realmente seria mas facil si fuese doblemente enlazada
{
    // Si se introduce una refencia nula no hace nada, quizas deberia tirar un error?
    if (envio == nullptr)
    {
        return;
    }


    NivelServicio prioridadEnvio = envio->getNivel();

    // Buscamos el nodo que contiene el envio y el nodo anterior.
    NodoPendiente* nodoAnterior = nullptr;
    NodoPendiente* nodoReordenar = comienzo;

    while (nodoReordenar != nullptr && nodoReordenar->envio != envio)
    {
        nodoAnterior = nodoReordenar;
        nodoReordenar = nodoReordenar->siguiente;
    }

    // Si el envio no esta en la lista, no hay nada para reordenar.
    if (nodoReordenar == nullptr)
    {
        return;
    }

    // Saco el nodo de su posicion actual.
    if (nodoAnterior == nullptr)
    {
        comienzo = nodoReordenar->siguiente;
    }
    else
    {
        nodoAnterior->siguiente = nodoReordenar->siguiente;
    }

    nodoReordenar->siguiente = nullptr;

    // Si tiene mayor prioridad que el primer nodo, pasa a ser el primero.
    if (comienzo == nullptr ||
        prioridadEnvio < comienzo->envio->getNivel())
    {
        nodoReordenar->siguiente = comienzo;
        comienzo = nodoReordenar;
        return;
    }

    // Avanzo hasta encontrar el nodo anterior a la nueva posicion.
    NodoPendiente* nodoAnteriorAInsertar = comienzo;
    while (nodoAnteriorAInsertar->siguiente != nullptr &&
           nodoAnteriorAInsertar->siguiente->envio->getNivel() <= prioridadEnvio)
    {
        nodoAnteriorAInsertar = nodoAnteriorAInsertar->siguiente;
    }

    // Insertamos el nodo en la posicion que corresponde.
    nodoReordenar->siguiente = nodoAnteriorAInsertar->siguiente;
    nodoAnteriorAInsertar->siguiente = nodoReordenar;
}




///Metodo que busca un paquete a partir del codigo de seguimiento
///Deberia pasarle como parametro tambien una lista?
NodoPendiente* ListaPendientes::buscar(std::string codSeguimiento)
{
    NodoPendiente* aux=comienzo;
    if (comienzo==nullptr)
    {
        return nullptr; //Que se retorna si no lo encuentra? un null o un throw error?
    }
    else
    {
        bool encontrado=false;
        while (aux!=nullptr)
        {
            if (aux->envio->getCodigo()==codSeguimiento) //Lo encontro, rome el ciclo
            {
                encontrado=true;
                break;
            }
            else
            {
                aux=aux->siguiente;
            }
        }
        if (encontrado==false)
        {
            return nullptr;//Que se retorna si no lo encuentra? un null o un throw error?
        }
        else
        {
            return aux;  //retorna una referencia al paquete
        }
    }
}




//metodo que reprograma(cambia de estado de envio? cambia la cantidad de visitas?)
//param el codigo de seguimiento


void ListaPendientes::reprogramar(Envio* envio,Estados nuevoEstado, std::string observacion)
{
    envio->cambiarEstado(nuevoEstado,observacion);
    reordenar(envio);
}






//metodo que despacha un paquete
//es decir que lo busca, lo hace cambiar de estado (que implica eso???)
// lo elimina de la lista pero lo retorna


NodoPendiente* ListaPendientes::despachar(const std::string& codigoSeguimiento)
{
    // buscamos el nodo por el codigo de seguimiento.
    NodoPendiente* nodoDespachado = buscar(codigoSeguimiento);

    // si no existe, no hay ningun envio para despachar (devuelvo nullptr, por ahi hay que poner un error?).
    if (nodoDespachado == nullptr)
    {
        return nullptr;
    }

    // buscamos el nodo anterior para poder quitarlo de la lista. (limitacion de que es una lista simplemente enlazada,
    // si fuese doblemente me ahorraria tener que recorrerla denuevo)
    NodoPendiente* nodoAnterior = nullptr;
    NodoPendiente* nodoRecorrido = comienzo;
    while (nodoRecorrido != nodoDespachado)
    {
        nodoAnterior = nodoRecorrido;
        nodoRecorrido = nodoRecorrido->siguiente;
    }

    // Lo quitamos de la lista de pendientes.
    if (nodoAnterior == nullptr)
    {
        comienzo = nodoDespachado->siguiente;
    }
    else
    {
        nodoAnterior->siguiente = nodoDespachado->siguiente;
    }

    // El nodo queda desvinculado.
    nodoDespachado->siguiente = nullptr;
    nodoDespachado->envio->cambiarEstado(Estados::EN_REPARTO,"Envio despachado de la lista de pendientes");

    return nodoDespachado; //no estoy seguro que haya que devolver esto la verdad pero bue \(*_*)/
}




// metodo que muestra la lista completa de paquetes pendientes?
// pero que dato de la muestra muestra?? todos?

void ListaPendientes::mostrar()
{
    NodoPendiente* aux=comienzo;
    while (aux!=nullptr)  //recorre la lista mostrando la info de cada paquete
    {
        std::cout<<"---Paquete: "<<aux->envio->getCodigo()<<" ---" <<std::endl;
        std::cout<<"●Destinatario: "<<aux->envio->getDestinatario()<< std::endl;
        std::cout<<"●Zona de entrega: "<<aux->envio->getZona()<< std::endl;
        std::cout<<"●Peso: "<<aux->envio->getPeso()<< std::endl;
        std::cout<<"●Nivel de servicio: "<< std::to_string(static_cast<int>(aux->envio->getNivel()))<< std::endl;
        std::cout<<"●Estado actual: "<<aux->envio->getEstadoTexto()<< std::endl;
        std::cout<<"●Cantidad de intentos de entrega: "<<aux->envio->getIntentos()<< std::endl;
        std::cout<<""<< std::endl;
        std::cout<<""<< std::endl;

        aux=aux->siguiente;
    }
}




    //===================================================================================================
    //Recursividad//Recursividad//Recursividad//Recursividad//Recursividad//Recursividad//Recursividad//
    //===================================================================================================
  ResumenZona ListaPendientes::resumirZona(NodoPendiente* nodo, const std::string& zona){
        if (nodo == nullptr) {
            return ResumenZona { 0,0.0,0}; //Caso Base (Devuelve neutro)
        }

        ResumenZona r = resumirZona(nodo->siguiente, zona); //Llamada recutsiva

        Envio* e = nodo->envio;
        if (e->getZona()==zona)
        {
            r.cantidad += 1;                                //SUMA 1 A LLA CANTIDAD EN ESA ZONA
            r.pesoTotal += e->getPeso();                    //sUMA EL PESO DEL PAQUETE  
            if (e->getNivel()== NivelServicio::EXPRESS) {   //SE ASEGURA QUE EL PAQUETE SEA EXPRESS Y AHI SUMA A LA CANT DE PAQUETES EXPRESS
                r.cantidadExpress += 1;
            }
        }
    return r;
}

ResumenZona ListaPendientes::resumenPorZona(const std::string& zona) const    //Se encarga de conseguir el Nodo Cabeza para comenzar la recursividad
{
    return resumirZona(comienzo, zona);
}


//========================
//Desafio Adicional
//========================
Envio* ListaPendientes::masPesadoDeZona(NodoPendiente* nodo, const std::string& zona)
{
    if (nodo == nullptr)
    {
        return nullptr;                                  // CASO BASE
    }

    Envio* mejorDelResto = masPesadoDeZona(nodo->siguiente, zona);
    Envio* actual = nodo->envio;

    if (actual->getZona() != zona) return mejorDelResto;
    if (mejorDelResto == nullptr)  return actual;

    return (actual->getPeso() >= mejorDelResto->getPeso()) ? actual : mejorDelResto; //El >= es para que en caso de empate gane el primero que ingreso
}

Envio* ListaPendientes::envioMasPesadoDeZona(const std::string& zona) const
{
    return masPesadoDeZona(comienzo, zona);
}
