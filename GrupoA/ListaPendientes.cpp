
#include "ListaPendientes.hpp"

#include "NodoPendiente.hpp"

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

void ListaPendientes::agregarPaquete(int codSeg,  std::string destinat,  std::string zonaEntrega, int peso, int nivelserv)
{
    NodoPendiente* nuevoPaquete= new NodoPendiente(codSeg, destinat, zonaEntrega, peso, nivelserv);

    //ingresa el paquete segun el orden de prioridad
    // EXPRESS(1) >PRIORITARIO(2)>ESTANDAR(3)
    if (nivelserv==1) //CASO 1: El paquete es prioridad express,se ingresa al principio de la lista
    {
        nuevoPaquete->siguiente=comienzo;
        comienzo=nuevoPaquete;
    }
    else
    {
        //CASO 2: es prioridad prioritario, se ingrsa tipo en el medio de la lista
        //CASO 3: es prioridad estandar, se ingresa al final de la lista
        //COMPLETAR <------------------------

    }
}







///Metodo que busca un paquete a partir del codigo de seguimiento
///Deberia pasarle como parametro tambien una lista?
NodoPendiente* ListaPendientes::buscar(int codSeguimiento)
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
            if (aux-> codigoDeSeguimiento==codSeguimiento) //Lo encontro, rome el ciclo
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
            return nullptr //Que se retorna si no lo encuentra? un null o un throw error?
        }
        else
        {
            return aux;  //retorna una referencia al paquete
        }
    }
}




//metodo que reprograma(cambia de estado de envio? cambia la cantidad de visitas?)
//param el codigo de seguimiento


void ListaPendientes::reprogramar(int codSeguimiento)
{
   NodoPendiente* nodoReprogramar= buscar(codSeguimiento); //trae el nodo solicitado
    // reprograma lo que sea
    //COMPLETAR <------------------------

}






//metodo que despacha un paquete
//es decir que lo busca, lo hace cambiar de estado (que implica eso???)
// lo elimina de la lista pero lo retorna


NodoPendiente* ListaPendientes::despachar(int codSeguimiento)
{
    NodoPendiente* aux=comienzo;
    NodoPendiente* nodoDespachado;
    //COMPLETAR <------------------------

}




// metodo que muestra la lista completa de paquetes pendientes?
// pero que dato de la muestra muestra?? todos?

void ListaPendientes::mostrar()
{
    NodoPendiente* aux=comienzo;
    while (aux!=nullptr)  //recorre la lista mostrando la info de cada paquete
    {
        std::cout<<"---Paquete: "<<aux->codigoDeSeguimiento<<" ---" std::endl;
        std::cout<<"●Destinatario: "<<aux->destinatario<< std::endl;
        std::cout<<"●Zona de entrega: "<<aux->zonaDeEntrega<< std::endl;
        std::cout<<"●Peso: "<<aux->peso<< std::endl;
        std::cout<<"●Nivel de servicio: "<<aux->nivelDeServicio<< std::endl;
        std::cout<<"●Estado actual: "<<aux->estadoActual<< std::endl;
        std::cout<<"●Cantidad de intentos de entrega: "<<aux->cantidadDeIntentosEntregal<< std::endl;
        std::cout<<""<< std::endl;
        std::cout<<""<< std::endl;

        aux=aux->siguiente;
    }
}



//metodo que sirve para cambiar el estado de un paquete??
// la cantidad de visitas??


void ListaPendientes::registrar(int codSeguimiento, Estados nuevoEstado)
    {
        NodoPendiente* nodoRegistrar= buscar(codSeguimiento);
        nodoRegistrar-> estadoActual=nuevoEstado;
        //COMPLETAR <------------------------
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

