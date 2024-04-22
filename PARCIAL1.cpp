#include <cstdlib>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "include/nlohmann/json.hpp"

using json = nlohmann::json;

using namespace std;

template <class T> class Nodo {
private:
    T dato;
    Nodo* next;
public:
    Nodo() { next = NULL; };
    Nodo(T a) { dato = a; next = NULL; };
    void set_dato(T a) { dato = a; };
    void set_next(Nodo* n) { next = n; };
    T get_dato() { return dato; };
    Nodo* get_next() { return next; };
    bool es_vacio() { return next == NULL; }
};


template <class T> class Lista 
{
private: Nodo<T>* czo;
       void addO(T d, Nodo<T>* ant);
       void borrarD(T d, Nodo<T>* ant);
public:
    Lista() { czo = new Nodo<T>(); };
    Lista(Nodo<T>* n) { czo = n; };
    //~Lista(void);
    void add(T d); //sumar nodos a la lista
    bool esvacia(void);
    T cabeza(void); //retorna el dato del primer nodo
    Lista* resto(void); //retorna el puntero al "resto" de la lista
                        //resto= lo que queda de la lista sin la cabeza
    string toPrint(string p);
    void impre(void);
    T suma(T i);
    int size();
    bool esta(T d);// detecta si d esta en la lista
    void borrarDato(T d) { borrarD(d, NULL); }//borra el nodo que contiene d
    void borrar(void); //borra la cabeza
    void borrar_last();//borra el ultimo
    void concat(Lista<T>* l1);// le transfiere los datos de l1 a this
    Lista<T>* copy(void);// hace una copia de la lista
    void tomar(int n);//deja "vivos" los n primeros nodos y borra el resto
    void addOrdenado(T d) { addO(d, NULL); }; //sumar nodos a la lista Ordenados de menor a MAYOR

};


template <class T>
void Lista<T>::add(T d) //100
{
    Nodo<T>* nuevo = new Nodo<T>(d);
    nuevo->set_next(czo);
    czo = nuevo;
}


template <class T>
bool Lista<T>::esvacia(void)
{
    return czo->es_vacio();
}


template <class T>
T Lista<T>::cabeza(void)
{
    if (this->esvacia()) {
        cout << " Error, Cabeza de lista vacia";
        return NULL;
    }
    return czo->get_dato();
}


template <class T>
Lista<T>* Lista<T>::resto(void)
{
    Lista* l = new Lista(czo->get_next());
    return (l);
}


template <class T>
string Lista<T>::toPrint(string p)
{
    if (this->esvacia()) {
        return p;
    }
    else {
        //std::ostringstream stm;
        ostringstream stm;
        stm << this->cabeza() << "-" << this->resto()->toPrint(p) << endl;
        //cout<<endl<<" stm.str()= "<<stm.str()<<endl;
        return stm.str();
    }
}


template <class T>
T Lista<T>::suma(T i)
{    //cout<<" i al entrar= "<<i<<endl;
    if (this->esvacia()) {
        return i;
    }
    else {

        //cout<<"this->cabeza()= "<<this->cabeza()<<endl;   
        return this->resto()->suma(i + this->cabeza());
    }
}


template <class T> int Lista<T>::size()
{
    if (this->esvacia()) return 0;
    return 1 + this->resto()->size();
}


template <class T> void Lista<T>::borrar(void)
{ //borra el nodo cabeza
    if (!this->esvacia()) {
        Nodo<T>* tmp = czo;
        czo = czo->get_next();
        delete tmp;
    }
}


template <class T> void Lista<T>::borrar_last()
{ // borra el ultimo nodo
    if (!this->esvacia()) {
        if ((czo->get_next())->get_next() == NULL) {
            delete czo->get_next();
            czo->set_next(NULL);
        }
        else this->resto()->borrar_last();
    }
}


template <class T> void Lista<T>::concat(Lista<T>* l1)
{// le transfiere los datos de l1 a this
    if (!(l1->esvacia())) {
        this->concat(l1->resto());
        this->add(l1->cabeza());
    }
}


template <class T> Lista<T>* Lista<T>::copy(void)
{
    Lista<T>* aux = new Lista();
    aux->concat(this);
    return aux;
}


template <class T> void Lista<T>::tomar(int n)
{ //deja "vivos" los n primeros nodos y borra el resto
    if (this->size() > n) {
        this->borrar_last();
        this->tomar(n);
    }
}


template <class T> void Lista<T>::impre(void)
{
    Nodo<T>* aux;
    aux = czo;
    while (aux->get_next() != NULL) {
        cout << aux->get_dato() << endl;
        aux = aux->get_next();
    }
}


template <class T>
void Lista<T>::addO(T d, Nodo<T>* ant)
{
    if (this->esvacia()) {//el primero
        this->add(d);
    }
    else {
        if (d < czo->get_dato()) {
            if (ant == NULL) {//al principio
                this->add(d);
            }
            else {//entre medio
                Nodo<T>* nuevo = new Nodo<T>(d);
                nuevo->set_next(ant->get_next());
                ant->set_next(nuevo);
            }
        }
        else {
            if ((czo->get_next())->get_next() == NULL) {//al final
                Nodo<T>* nuevo = new Nodo<T>(d);
                nuevo->set_next(czo->get_next());
                czo->set_next(nuevo);

            }
            else this->resto()->addO(d, czo);

        }
    }
}


template <class T> bool Lista<T>::esta(T d)
{// busca d en la lista
    if (this->esvacia()) return false;
    if (this->cabeza() == d) return true;
    
    return this->resto()->esta(d);    
}

template <class T>
void Lista<T>::borrarD(T d, Nodo<T>* ant)
{
    if (!this->esvacia()) {
        if (d == this->cabeza()) {
            if (ant == NULL) {//al principio
                this->borrar();
            }
            else {//entre medio
                ant->set_next(czo->get_next());
                delete czo;
            }
        }
        else  this->resto()->borrarD(d, czo);

    }
}

template <class T> class Pila:public Lista<T>
{
      public:
             Pila(){Lista<T>();};
             void apilar(T d){this->add(d);};
             T tope(void){return this->cabeza();};
             void desapilar(void){this->borrar();};
             bool pilavacia(){return this->esvacia();};
             bool comprobarKV(Pila<char> pila);
};                  

template <class T> class Cola :public Lista<T> 
{
public:
    Cola(void) { Lista<T>(); };
    //~Cola(void);
    T tope() { return this->last(); };
    bool colavacia(void) { return this->esvacia(); };
    void encolar(T a) { this->add(a); };
    void desencolar(void) { this->borrar_last(); };
    T ultimo(void) { return this->cabeza(); };
    string imprimir(string s) { return this->toPrint(s); };
    
};

template <class T>
bool Pila<T>::comprobarKV(Pila<char> pila)
{
   Pila<char> aux = Pila<char>();
   if (pila.size() < 6)
   {
        return false;
   }
   // Verificar que la expresión comience y termine con comillas dobles
    if (pila.top() == ',' && pila.getnext() == '"' )
    {
       aux.apilar(pila.top());
       pila.desapilar;
       aux.apilar(pila.top());
       pila.desapilar;
        while (pila.top()!= '"' )
        {
            aux.apilar(pila.top);
            pila.desapilar;
        }
       if(pila.top()=='"' && pila.getnext() == ':' && pila.getnext()+1 == '"')
       {
            aux.apilar(pila.top());
            pila.desapilar;
            aux.apilar(pila.top());
            pila.desapilar;
            aux.apilar(pila.top());
            pila.desapilar;
        }else {return false;}
        while (pila.top()!= '"')
        {
            aux.apilar(pila.top);
            pila.desapilar;
        } 
        aux.apilar(pila.top);
        pila.desapilar;
        if(pila.size()>0)
        {
            return false; 
        }else
        {
            //metodo de la cola 
            return true;
        }

    } 
    return false;
         
}

string eliminarEspacios()
{
   // Creamos un string que contiene solo el nombre del archivo JSON que queremos leer
    string filename = "ArchivosJSON/ejemplo.json";

    // Abrimos el archivo JSON
    ifstream file(filename);

    // Verificamos si se pudo abrir el archivo
    if (!file.is_open()) 
    {
        cerr << "Error al abrir el archivo." << endl;

        return "ERROR";
    }

    // Leemos el contenido del archivo en una cadena
    string contenido_json((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());

    // Eliminamos saltos de linea de contenido_json generando una nueva cadena de 1 sola linea
    string singleline_json;
    for (char c : contenido_json) 
    {
        if (c != '\n' ) 
        {
            singleline_json += c;
        }
    }
    
    // Creamos un string similar a singleline_json pero eliminando todos los 
    // espacios existentes despues de cada coma, cada '{' y '['
    string cadena_json;

    bool espacioPrevio = false; // bool que va a determinar si en el espacio anterior se encuentra una coma, '{' o '[' y se inicializa en false

    for (char c : singleline_json)  // recorremos el string de 1 sola linea, caracter por caracter
    {
        if (c == ',' || c == '{' || c == '[' || c == ']')  
        {
            cadena_json += c;
            espacioPrevio = true;   // espacioPrevio = true significa que existe coma, '{' o '[' en la posicion 
                                    // actual de la pasada y queda asi para la pasada siguiente, 
                                    // en la que vamos a evaluar si el espacio previo contiene 
                                    // uno de nuestros caracteres de interes
        } 
                                  
        else 
            if (c == ' ')                  // si no existe coma, '{' o '[' en la posicion actual, preguntamos si estamos en presencia de                               
            {                              // un espacio vacio (no confundir con NULL)  
                 if (!espacioPrevio)       // si el espacio previo tiene coma, '{' o '[', espacioPrevio esta en true, entonces este if NO se ejecuta,
                 {                         // pero si el espacio previo no tiene ninguno, es decir, tiene cualquier otro, incluso un espacio vacio, 
                     cadena_json += c;     // espacioPrevio esta en false, se ejecuta el if y el caracter actual se agrega a la cadena
                 }
            } 
            else                           // si la pasada llego hasta aca, significa que el caracter actual no es coma, '{' o '[' ni espacio vacio, osea que  
            {                              // debemos establecer espacioPrevio = false, y agregamos el caracter a la cadena
               cadena_json += c; 
               espacioPrevio = false;
            }
    }

    // Cerrar el archivo
    file.close();

    return cadena_json;
}


int main() 
{

    Pila<char> kV = Pila<char>();  // puntero a una pila que contenga caracteres de una subexpresión Key:Value           (kV)
    Pila<char> kL = Pila<char>();  // puntero a una pila que contenga caracteres de una subexpresión Key:[List]          (kL)
    Pila<char> kS = Pila<char>();  // puntero a una pila que contenga caracteres de una subexpresión Key:{Subexpresión}  (kS)
    
    Cola<string> cola = Cola<string>();  // puntero al Buffer que contendra strings, donde cada uno es una subexpresión JSON

    string cadena_json = eliminarEspacios();  
    
    cout << "la cadena JSON es = " << cadena_json;


    if (cadena_json.at(0) == '{')      // comprobamos si el primer caracter de la cadena JSON es '{'
        {
            string caracter = "";           
            char c = cadena_json.at(0);
            caracter += c;
            cola.encolar(caracter); 

            int tipoPila;
            string subexp;             // String que va a guardar una subexpresion y se va a ir limpiando para guardar la siguiente
            int error = false;

            for (int i = 1; (i < cadena_json.length()) && (!error); i++)
            {
                subexp += cadena_json.at(i);

                if(cadena_json.at(i) == ':')
                {
                    if(cadena_json.at(i+1) == '"')
                    {
                        tipoPila = 1;
                    }
                    else if(cadena_json.at(i+1) == '[')
                    {
                        tipoPila = 2;
                    }
                    else if(cadena_json.at(i+1) == '{')
                    {
                        tipoPila = 3;
                    }
                    else
                    {
                        cout << "Error";
                        return 0;
                    }
                }
                
                if(cadena_json.at(i) == ',')
                {
                    if (tipoPila == 1)
                    {
                        if(cadena_json.at(i-1) == '"')
                        {
                            for(int j = 0;(j < subexp.length()) && (!error); j++ )
                            {
                                kV.apilar(subexp.at(j));
                            }
                            
                            subexp = "";
                        }
                        else
                        {
                            cout << "Error";
                            return 0;
                        }
                    }
                    else if (tipoPila == 2)
                    {
                        if(cadena_json.at(i-1) == ']')
                        {
                            for(int k = 0;(k < subexp.length()) && (!error); k++ )
                            {
                                kL.apilar(subexp.at(k));
                            }
                            
                            subexp = "";
                        }
                      
                    }
                    else if (tipoPila == 3)
                    {
                        if(cadena_json.at(i-1) == '}')
                        {
                            for(int n = 0;(n < subexp.length()) && (!error); n++ )
                            {
                                kL.apilar(subexp.at(n));
                            }
                            
                            subexp = "";
                        }
                      
                    }
                }

            }

        }
        else
        {
            cout << "Error";
            return 0;
        }


    return 0;
    
    
   /*cout << endl << "Ingrese cadena = "; cin >> cadena;
    int error = false;
    for (int i = 0; (i < cadena.length()) && (!error); i++) {
        if (cadena.at(i) == '{') p->apilar('{');
        if (cadena.at(i) == '[') p->apilar('[');
        if (cadena.at(i) == '(') p->apilar('(');

        if (cadena.at(i) == '}') {
            if (p->pilavacia()) error = true;
            else
                if (p->tope() != '{') error = true;
                else p->desapilar();
        }
        if (cadena.at(i) == ']') {
            if (p->pilavacia()) error = true;
            else
                if (p->tope() != '[') error = true;
                else p->desapilar();
        }
        if (cadena.at(i) == ')') {
            if (p->pilavacia()) error = true;
            else
                if (p->tope() != '(') error = true;
                else p->desapilar();
        }
    }//fin for i
    if ((!error) && p->pilavacia())cout << endl << "Todo OK";
    else cout << endl << "ERROR";
    */
    
   
    //cout << endl << endl;
    //system("PAUSE");
    //return EXIT_SUCCESS;

}