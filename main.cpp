class NodoSimple { // tipo de dato
  Nodo *siguiente;
  Nodo *previo;

    Nodo ( //tipo de datos) : siguiente(nullptr) , previo(nullptr) //contructor de nodo

}

class ListaSimple {

public:
  ListaSimple() ///////////////////////////////////////////////////////constructor
                ///de lista
  {
    head = nullptr
  }

  ~ListaSimple() //////////////////////////////////////////////////////////////////destructor
  {
    Nodo *actual = head;
    while (actual != nullptr) {
      Nodo *siguienteNodo = actual->siguiente;
      delete actual;
      actual = siguienteNodo;
    }
    head = nullptr
  }

  ////////////////////////////////////////////////////////////////////////////////////////
  /////metodos
    void add(   //tipo de dato                  )
    {
    Nodo *nuevo = new Nodo(tipo de dato);
    nuevo->siguiente = head;
    head = nuevo;

    }


private:
Nodo*  head;
}

class NodoSimple { // tipo de dato
  Nodo *siguiente;
  Nodo *previo;

    Nodo ( //tipo de datos) : siguiente(nullptr) , previo(nullptr) //contructor de nodo

}

class ListaDoble {

public:
  ListaDoble(); // constructor de lista
  {
  }

  ~ListaDoble(); // destructor

  // metodos
  void add2();

private:
  Nodo *head2;
}
