#include <gtkmm/application.h>


#include "interfaz_grafica/VentanaPrincipal.h"

// Método principal
int main() {
    Glib::RefPtr<Gtk::Application> ap = Gtk::Application::create("an_num.programa_montante");
    Glib::RefPtr<Gtk::Builder> constructor = Gtk::Builder::create_from_file("../interfaz_grafica.glade");
    VentanaPrincipal* ventana_principal = nullptr;

    // trae la composición de la ventana principal del archivo de Glade
    constructor->get_widget_derived("VentanaPrincipal", ventana_principal);
    // cuando se cierra se libera la memoria de la ventana principal
    ventana_principal->signal_hide().connect([&ventana_principal] () {delete ventana_principal;});
    //termina el programa cuando se seleccione la X
    return ap->run(*ventana_principal);
}
