/*
#include <cstdlib>
#include <iostream>
#include <sstream>
#include "include/nlohmann/json.hpp"

using json = nlohmann::json;

int main() {
    // Crear un objeto JSON
    
    json j;
    j["nombre"] = "Juan";
    j["edad"] = 30;

    // Imprimir el objeto JSON
    std::cout << "Objeto JSON generado:" << std::endl;
    std::cout << j.dump(4) << std::endl;

    return 0;
}
*/

#include <iostream>
#include <fstream>
#include "include/nlohmann/json.hpp"
#include <string>

using json = nlohmann::json;

using namespace std;

int main() {

    string filename = "ArchivosJSON/ejemplo.json";

    // Abrir el archivo JSON
    ifstream file(filename);

    // Verificar si se pudo abrir el archivo
    if (!file.is_open()) 
    {
        cerr << "Error al abrir el archivo." << endl;
        return 1;
    }

    // Leer el contenido del archivo en una cadena
    string cadena_json((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());

    cout << "la cadena json_content es = " << cadena_json;



    // Cerrar el archivo
    file.close();

    return 0;
}



string eliminarEspaciosDespuesDeSimbolos(const string& json) {
    string resultado;
    bool espacioPrevio = false;

    for (char c : json) 
    
    {
        if (c == ',' || c == '{' || c == '[') 
        {
            resultado += c;
            espacioPrevio = true;
        } 
        else 
            if (c == ' ') 
            {
                 if (!espacioPrevio) 
                 {
                     resultado += c;
                 }
            } 
            else 
            {
               resultado += c; 
            }
        
        espacioPrevio = false;

    }

    return resultado;
}