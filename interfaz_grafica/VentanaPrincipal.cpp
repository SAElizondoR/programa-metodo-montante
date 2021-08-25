//
// Created by sergioaer on 24/08/21.
//

#include "VentanaPrincipal.h"

#include <utility>


VentanaPrincipal::VentanaPrincipal(Gtk::ApplicationWindow::BaseObjectType *objeto_c,
                                   Glib::RefPtr<Gtk::Builder> constructor)
                                   : Gtk::ApplicationWindow(objeto_c),
                                   constructor{std::move(constructor)} {
    ajuste_cant_ecuaciones = nullptr;
    Gtk::Grid* tabla = nullptr;

    /*constructor->get_widget("Tabla", tabla);
    constructor->get_widget("AjusteCantEcuaciones", ajuste_cant_ecuaciones);

    ajuste_cant_ecuaciones->signal_value_changed().connect(sigc::mem_fun(*this,
                                                                         &VentanaPrincipal::al_cambiar_valor_ajuste));*/
}

void VentanaPrincipal::al_cambiar_valor_ajuste() {
    int cant_ecuaciones = int(ajuste_cant_ecuaciones->get_value());
    for (int indice_ren = 0; indice_ren < cant_ecuaciones; ++indice_ren) {
        Glib::RefPtr<Gtk::Builder> constructorRen = crearConstructor();
        Gtk::Label label;
        label.set_text("ola q tal");
        /* add(caja_hor);
        for (int indice_col = 0; indice_col < cant_ecuaciones - 1; ++indice_col) {
            caja_hor.pack_end()
        } */
    }
}

Glib::RefPtr<Gtk::Builder> VentanaPrincipal::crearConstructor() {
    return Gtk::Builder::create_from_file("../interfaz_grafica.glade");
}
