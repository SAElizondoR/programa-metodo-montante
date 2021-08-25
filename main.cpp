#include <gtkmm/application.h>


#include "interfaz_grafica/VentanaPrincipal.h"

int main() {
    Glib::RefPtr<Gtk::Application> ap = Gtk::Application::create("an_num.programa_montante");
    Glib::RefPtr<Gtk::Builder> constructor = Gtk::Builder::create_from_file("../interfaz_grafica.glade");
    VentanaPrincipal* ventana_principal = nullptr;
    constructor->get_widget_derived("VentanaPrincipal", ventana_principal);
    // ventana_principal = Glib::RefPtr<Gtk::Window>::cast_dynamic(constructor->get_object("VentanaPrincipal"));
    ventana_principal->signal_hide().connect([&ventana_principal] () {delete ventana_principal;});
    ventana_principal->show();

    return ap->run(*ventana_principal);

    /* std::string ruta;
    char sn; // recibe respuesta sí o no.
    do {
        std::cout << "Introduzca la ruta del archivo: ";
        std::cin >> ruta;
        LectorMatriz lectorMatriz(ruta);
        lectorMatriz.leerMatriz();

        std::cout << std::endl << "¿Desea probar otro archivo? [S/n] ";
        std::cin >> sn;
    }while(sn != 'n');

    return 0; */
}
