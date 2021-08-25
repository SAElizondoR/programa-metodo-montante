//
// Created by sergioaer on 24/08/21.
//

#include "VentanaPrincipal.h"

#include <iostream>


/*VentanaPrincipal::VentanaPrincipal() :
constructor{Gtk::Builder::create_from_file("../interfaz_grafica.glade")} {
    construir();
}*/

VentanaPrincipal::VentanaPrincipal(Gtk::ApplicationWindow::BaseObjectType *objeto_c,
                                   const Glib::RefPtr<Gtk::Builder>& constructor)
                                   : Gtk::ApplicationWindow(objeto_c),
                                   constructor(constructor) {
    tabla = nullptr;
    cuadro_lista = nullptr;
    constructor->get_widget("CuadroLista", cuadro_lista);
    ajuste_cant_ecuaciones = Glib::RefPtr<Gtk::Adjustment>::cast_dynamic(
            constructor->get_object("AjusteCantEcuaciones"));
    al_cambiar_valor_ajuste();

    ajuste_cant_ecuaciones->signal_value_changed().connect(sigc::mem_fun(*this,
                                                                         &VentanaPrincipal::al_cambiar_valor_ajuste));
}

void VentanaPrincipal::al_cambiar_valor_ajuste() {
    cuadro_lista->remove(*cuadro_lista->get_children().back());
    delete(tabla);
    tabla = new Gtk::Grid();
    int cant_ecuaciones = int(ajuste_cant_ecuaciones->get_value());
    for (int indice_col = 0; indice_col < 2 * cant_ecuaciones + 1; ++indice_col) {
        tabla->insert_column(indice_col);
    }

    for (int indice_ren = 0; indice_ren < cant_ecuaciones; ++indice_ren) {
        tabla->insert_row(indice_ren);
        for (int indice_col = 0; indice_col < 2 * cant_ecuaciones - 1; ++indice_col) {
            if (indice_col % 2 == 0) {
                Glib::RefPtr<Gtk::Builder> constructorCelda = crearConstructor();
                Glib::RefPtr<Gtk::SpinButton> btn = Glib::RefPtr<Gtk::SpinButton>::cast_dynamic(
                        constructorCelda->get_object("NumeroCelda"));
                btn->unparent();
                tabla->attach(*btn.operator->(), indice_col, indice_ren);
            } else {
                auto etiqueta = Gtk::make_managed<Gtk::Label>();
                etiqueta->set_text(" x_" + std::to_string((indice_col + 1) / 2) + " + ");
                tabla->attach(*etiqueta, indice_col, indice_ren);
            }
        }
        auto etiqueta = Gtk::make_managed<Gtk::Label>();
        etiqueta->set_text(" x_" + std::to_string((2 * cant_ecuaciones) / 2) + " = ");
        tabla->attach(*etiqueta, 2 * cant_ecuaciones - 1, indice_ren);
        Glib::RefPtr<Gtk::Builder> constructorCelda = crearConstructor();
        Glib::RefPtr<Gtk::SpinButton> btn = Glib::RefPtr<Gtk::SpinButton>::cast_dynamic(
                constructorCelda->get_object("NumeroCelda"));
        btn->unparent();
        tabla->attach(*btn.operator->(), 2 * cant_ecuaciones, indice_ren);
    }
    cuadro_lista->append(*tabla);
    show_all_children();
}

Glib::RefPtr<Gtk::Builder> VentanaPrincipal::crearConstructor() {
    return Gtk::Builder::create_from_file("../interfaz_grafica.glade");
}
