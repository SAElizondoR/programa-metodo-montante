//
// Created by sergioaer on 24/08/21.
//

#ifndef PROGRAMA_METODO_MONTANTE_VENTANAPRINCIPAL_H
#define PROGRAMA_METODO_MONTANTE_VENTANAPRINCIPAL_H


#include <gtkmm.h>

class VentanaPrincipal : public Gtk::ApplicationWindow {
public:
    VentanaPrincipal(Gtk::ApplicationWindow::BaseObjectType* objeto_c, Glib::RefPtr<Gtk::Builder>  refConstructor);

protected:
    Glib::RefPtr<Gtk::Builder> constructor;
    Gtk::Adjustment* ajuste_cant_ecuaciones;
    std::vector<Gtk::HBox*> vector_cajas;
    std::vector<std::vector<int>> a;

    void al_cambiar_valor_ajuste();
    static Glib::RefPtr<Gtk::Builder> crearConstructor();
};


#endif //PROGRAMA_METODO_MONTANTE_VENTANAPRINCIPAL_H
