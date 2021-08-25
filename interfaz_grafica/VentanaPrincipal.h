//
// Created by sergioaer on 24/08/21.
//

#ifndef PROGRAMA_METODO_MONTANTE_VENTANAPRINCIPAL_H
#define PROGRAMA_METODO_MONTANTE_VENTANAPRINCIPAL_H


#include <gtkmm.h>

class VentanaPrincipal : public Gtk::ApplicationWindow {
public:
    // VentanaPrincipal();
    VentanaPrincipal(Gtk::ApplicationWindow::BaseObjectType* objeto_c, const Glib::RefPtr<Gtk::Builder>& constructor);

protected:
    Glib::RefPtr<Gtk::Builder> constructor;
    Gtk::ListBox* cuadro_lista;
    Gtk::Grid* tabla;
    Glib::RefPtr<Gtk::Adjustment> ajuste_cant_ecuaciones;

    void al_cambiar_valor_ajuste();
    static Glib::RefPtr<Gtk::Builder> crearConstructor();
};


#endif //PROGRAMA_METODO_MONTANTE_VENTANAPRINCIPAL_H
