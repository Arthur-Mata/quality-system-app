/*Arturo Mata
SGC - Sistema de Gestión de Calidad
Fecha: 2024-06-15
Versión: v0.2.0-alpha
*/

#include <iostream> //in y out, funciones de entrada de texto por teclado
#include <limits>
#include <vector> //uso de vectores para almacenamiento dinámico y relaciones entre clases
#include <list> 
#include <string> //cadenas de texto
#include <algorithm>
#include <stdexcept>
#include <ctime> // para uso de calculo de edad en clase Persona
#include <time.h>
using namespace std;

/* Librerías para un futuro:
#include <iomanip> //Para formatear salida (setprecision, setw, etc).
#include <fstream> //Si vamos a guardar o leer archivos (reportes, logs).
#include <map> // o bien <unorder_mao> si usamos diccionarios o índices.
#include <chrono> //Si decidimos migrar de std::tm a std::chrono para fechas modernas
*/


//----Clase Person----


class Person {
    private: //Atributos
        std::string name;
        std::string last_name;
        std::string address;
        std::string gender;
        std::string phone_number;
        std::string email;
        std::string num_id;
        int day;
        int month;
        int year; //fecha de nacimiento
    
    public: //Constructor
        Person();
        Person(std::string n, std::string ln, std::string addr, std::string g, std::string phone, std::string mail, std::string _num_id,
        int d, int m, int y)
        :name(n), last_name(ln), address(addr), gender(g), phone_number(phone), email(mail), day(d), month(m), year(y) {}

        //Métodos GET
        std::string getName() const { return name; } //método para obtener el nombre por teclado
        std::string getLastName() const { return last_name; }
        std::string getAddress() const { return address; }
        std::string getGender() const { return gender; }
        std::string getPhoneNumber() const { return phone_number; }
        std::string getEmail() const { return email; }
        std::string getNumId() const { return num_id; }
        int getDay() const { return day; }
        int getMonth() const { return month; }
        int getYear() const { return year; }
        

        //Métodos SET
        void setName(const std::string& n) { name = n; } //métodos para guardar el nombre por teclado en la variable designada
        void setLastName(const std::string& ln) { last_name = ln;}

        //Validación de formato de correo electrónico
        void setEmail(const std::string& mail) {
            if (mail.find('@') != std::string::npos && 
                mail.find('.', mail.find('@')) != std::string::npos)
                {
                this->email = mail;
                }
            else  {
                throw std::invalid_argument("Invalid email format, try again");
            }
        }

    //Método para calcular edad
    int calculateAge() const {
        time_t t = time(nullptr);
        tm* now = localtime(&t);
        
        int edad = (now->tm_year + 1900) - year;
        if ((now->tm_mon + 1 < month) ||
        ((now->tm_mon + 1 == month) && (now->tm_mday < day))) {
            edad--;
        }
         return edad;
        }
    
    void showInformation() const {
        std::cout << "Name: " << name << " " <<  last_name << "\n"
                    << "Address: " << address << "\n"
                    << "Gender: " << gender << "\n"
                    << "Phone: " << phone_number << "\n"
                    << "Email: " << email << "\n"
                    << "ID: " << num_id << "\n"
                    << "Birthdate: " << day << "/" << month << "/" << year << "\n"
                    << "Age: " << calculateAge() << " years\n";

    }
};

Person::Person() //constructor por defecto
    :name(""), last_name(""), address(""), gender(""), phone_number(""), email(""), num_id(""), day(0), month(0), year(0) {}


//---- Clase Employee ----

class Employee :  public Person {
    private:
        std::string payroll_number;
        std::string job_position;
        std::string department;
        std::string status; //status (Activo/ Inactivo).
        std::tm date_entry;
        std::tm date_end; //fecha de ingreso y fin de labores.
        float salary;

    public:
    Employee(); //Constructor por defecto (sólo declaración)

    //Constructor completo
    Employee(std::string pn, std::string jp, std::string dep, std::string stat, const std::tm& dentry, const std::tm& dend,
             float salary, std::string n, std::string ln, std::string addr, std::string g, std::string phone,
              std::string mail, std::string _num_id, int d, int m, int y)
        :Person(n, ln, addr, g, phone, mail, _num_id, d, m, y), 
        payroll_number(pn),
        job_position(jp),
        department(dep),
        status(stat),
        date_entry(dentry),
        date_end(dend),
        salary(salary)
    {}

        //Métodos GET
        std::string getPayrollNumber() const { return payroll_number; }
        std::string getJobPosition() const { return job_position; }
        std::string getDepartment() const { return department; }
        std::string getStatus() const { return status; }
        bool isActive() const { return status == "Activo"; }
        std::tm getDateEntry() const { return date_entry; }
        std::tm getDateEnd() const { return date_end; }
        float getSalary() const { return salary; }

        //Cálculo de antigüedad
        int calculateSeniority() const {
            std::time_t now = std::time(nullptr);
            std::tm end = isActive() ? *std::localtime(&now) : date_end;

            std::tm entryCopy = date_entry;

            std::time_t entry_time = std::mktime(&entryCopy);
            std::time_t end_time = std::mktime(&end);

            double seconds = std::difftime(end_time, entry_time);
            return static_cast<int>(seconds / (365.25 * 24 * 60 * 60)); // años
    }

        //Mostrar información del empleado
        void showInformation() const {
            std::cout << "Payroll Number: " << payroll_number << "\n"
                        << "Position: " << job_position << "\n"
                        << "Department: " << department << "\n"
                        << "Status: " << status << "\n"
                        << "Salary: " << salary << "\n";
                        //agregar fecha de ingreso y/o fin (opcional)
                    
        }
};

//Implementación del constructor por defecto
Employee::Employee()
    :Person(),
    payroll_number(""),
    job_position(""),
    department(""),
    status(""),
    date_entry({}),
    date_end({}),
    salary(0.0f)
    
    {}


//----Clase AdministrativeStaff (herencia Person)----

class AdministrativeStaff : public Employee {
    private:
        std::string responsible_area;
        int access_level;

    public: //constructor
        AdministrativeStaff(std::string pn, std::string jp, std::string dep, std::string stat, const std::tm& dentry, const std::tm& dend,
             float salary, std::string n, std::string ln, std::string addr, std::string g, std::string phone,
              std::string mail, std::string _num_id, int d, int m, int y, std::string ra, int accl)
              : Employee(pn, jp, dep, stat, dentry, dend, salary, n, ln, addr, g, phone, mail, _num_id, d, m, y),
              responsible_area(ra), access_level(accl) {}
    
    //Métodos SET
    std::string getResponsibleArea() const { return responsible_area; }
    int getAccessLevel() const { return access_level; }

    //Lógica de permisos
    bool hasPermission(int requiredLevel) const {
        return access_level >= requiredLevel;
    }
    //Acción típica de administrativo
    void showInformation() const {
        Employee::showInformation();
        std::cout << "Responsible área: " << responsible_area << "\n"
                    << "Access level: " << access_level << "\n";
    }

    //Método de crear documentación
    void generateDocument(const std::string& docName) const { std::cout <<"Generando documento: " << docName << "\n"; }  
};


int main() {
    //1.- Inicializamos la fecha de ingreso
    std::tm entry = {};
    entry.tm_mday = 10;
    entry.tm_mon = 0; //enero (0 = enero)
    entry.tm_year = 2020 - 1900; //año - 1900

    //2.- Inicializamos la fecha de salida
    std::tm end = {} ;
    end.tm_mday = 5;
    end.tm_mon = 11; //diciembre
    end.tm_year = 2024 -1900;

    //3.- Creamos el empleado regular
    Employee emp(
        " ", " ", " ", " ", entry, end, 0.0f, " ", " ", " ",
         " ", " ", " ", " ", 0, 0, 0
    );
    
    std::cout << "\n--- Información del empleado---\n";
    emp.showInformation();
    std::cout << "Antigüedad: " << emp.calculateSeniority() << " años\n";

    //4.- Creamos un administrativo

    AdministrativeStaff admin(
        " ", " ", " ", " ", entry, end, 0.0f, " ", " ", " ",
         " ", " ", " ", " ", 0, 0, 0, " ", 0
    );

    std::cout << "\n---Información del administrativo---\n";
    admin.showInformation();
    std::cout << "Antigüedad: " << admin.calculateSeniority() << " años\n";

    //5.- Prueba de permisos (considerar un rango de permisos)
    std::cout << "¿Tiene acceso nivel 3? " << (admin.hasPermission(3) ? "Sí" : "No") << "\n";
    std::cout << "¿Tiene acceso nivel 5? " << (admin.hasPermission(5) ? "Sí" : "No") << "\n";

    //6.- Simulación de acción administrativa
    admin.generateDocument("Reporte mensual");
    
    return 0;
}