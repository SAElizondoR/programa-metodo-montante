//
// Created by sergioaer on 24/08/21.
//

#ifndef PROGRAMA_METODO_MONTANTE_VENTANAPRINCIPAL_H
#define PROGRAMA_METODO_MONTANTE_VENTANAPRINCIPAL_H

//librerías para el manejo de interfaz
#include <gtkmm.h>

// Poder usar la otra clase
#include "../clases/MontanteSolver.h"


class VentanaPrincipal : public Gtk::ApplicationWindow {
public:
    // constructor que crea la ventana
    VentanaPrincipal();
    // toma el objeto de ventana de GTK y el constructor
    VentanaPrincipal(Gtk::ApplicationWindow::BaseObjectType* objeto_c, const Glib::RefPtr<Gtk::Builder>& constructor);

protected:
    Glib::RefPtr<Gtk::Builder> constructor;    // construye la interfaz con el XML
    Gtk::ListBox* lista_cuadros;    // lista de componentes
    Gtk::Grid* tabla;   // representación gráfica de la matriz
    Glib::RefPtr<Gtk::Adjustment> ajuste_cant_ecuaciones;   // modelo del número de ecuaciones
    Glib::RefPtr<Gtk::Button> btn_resolver;
    std::vector<std::vector<float>> matriz;

    void cambiar_valor_ajuste(); // se activa cuando cambia el valor de ajuste_cant_ecuaciones
    static Glib::RefPtr<Gtk::Builder> crear_constructor();   // crea un constructor con el archivo interfaz_grafica
    // método obtener_matriz en forma de un vector de enteros
    void imprimir_btn_aumentar(int indice_ren, int indice_col); // agrega selector de valores
    void imprimir_etiqueta(const std::string& sim, int indice_ren, int indice_col); // agrega separador (+ o =)
    void hacer_resolver_matriz();
    void obtener_matriz();
};


#endif //PROGRAMA_METODO_MONTANTE_VENTANAPRINCIPAL_H
