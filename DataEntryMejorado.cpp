/*Arturo Mata, Data Entry Mejorado
V1.0
*/

#include <iostream> //in y out, funciones de entrada de texto por teclado
#include <limits>
#include <vector> //uso de vectores para almacenamiento dinámico y relaciones entre clases
#include <list> 
#include <string> //cadenas de texto
#include <algorithm>
#include <stdexcept>
#include <ctime> // para uso de calculo de edad en clase Persona
using namespace std;


//----Clase Persona----


class Persona {
    private: //Atributos
        std::string name, last_name, address, gender, phone_number, email;
        int day, month, year, num_id; //fecha de nacimiento
    
    public: //Constructor
        Persona(std::string n, std::string ln, std::string addr, std::string g, std::string phone, std::string mail,
        int d, int m, int y)
        :name(n), last_name(ln), address(addr), gender(g), phone_number(phone), email(mail), day(d), month(m), year(y) {}

        //Métodos GET
        std::string getName() const { return name; } //método para obtener el nombre por teclado
        std::string getLastName() const { return last_name; }
        std::string getEmail() const { return email; }

        //Métodos SET
        void setName(const std::string& n) { name = n; } //métodos para guardar el nombre por teclado en la variable designada
        void setLastName(const std::string& ln) { last_name = ln;}
        void setEmail(const std::string& mail) { email = mail; }

        //Método para calcular edad
    int calcularEdad() const {
        time_t t = time(nullptr);
        tm* now = localtime(&t);
        
        int edad = (now->tm_year + 1900) - year;
        if ((now->tm_mon + 1 < month) ||
        ((now->tm_mon + 1 == month) && (now->tm_mday < day))) {
            edad--;
        }
         return edad;
        }

};