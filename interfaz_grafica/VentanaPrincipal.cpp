//
// Created by sergioaer on 24/08/21.
//


#include "VentanaPrincipal.h"

VentanaPrincipal::VentanaPrincipal() : VentanaPrincipal(new Gtk::ApplicationWindow::BaseObjectType(),
                                                        Glib::RefPtr<Gtk::Builder>()) { }

VentanaPrincipal::VentanaPrincipal(Gtk::ApplicationWindow::BaseObjectType *objeto_c,
                                   const Glib::RefPtr<Gtk::Builder>& constructor)
                                   : Gtk::ApplicationWindow(objeto_c),
                                   constructor(constructor) {
    lista_cuadros = nullptr;
    tabla = nullptr;
    ajuste_cant_ecuaciones = Glib::RefPtr<Gtk::Adjustment>::cast_dynamic(
            constructor->get_object("AjusteCantEcuaciones"));
    btn_resolver = Glib::RefPtr<Gtk::Button>::cast_dynamic(
            constructor->get_object("Resolver"));

    constructor->get_widget("CuadroLista", lista_cuadros);
    cambiar_valor_ajuste(); // se adapta el valor del ajuste una vez que se conoce
    // aplicar el método cambiar_valor_ajuste cuando este cambia
    ajuste_cant_ecuaciones->signal_value_changed().connect(sigc::mem_fun(*this,
                                                                         &VentanaPrincipal::cambiar_valor_ajuste));
    //utiliza el método de obtener_matriz de la clase VentanaPrincipal para leer desde la interfaz
    // se llena la matriz con los números que se leen
    btn_resolver->signal_clicked().connect(sigc::mem_fun(*this, &VentanaPrincipal::obtener_matriz));
}

void VentanaPrincipal::cambiar_valor_ajuste() {
    Gtk::Grid* tabla_anterior = dynamic_cast<Gtk::Grid *>(lista_cuadros->get_children().back());
    lista_cuadros->remove(*tabla_anterior);   // borrar la tabla anterior
    delete(tabla_anterior); // liberar memoria
    tabla = new Gtk::Grid();
    int cant_ecuaciones = int(ajuste_cant_ecuaciones->get_value()); // obtener nuevo número de ecuaciones
    // insertar 2 * n + 1 columnas (n + 1 para las entradas, n para los separadores)
    for (int indice_col = 0; indice_col < 2 * cant_ecuaciones + 1; ++indice_col) {
        tabla->insert_column(indice_col);
    }
    // llenar la tabla
    for (int indice_ren = 0; indice_ren < cant_ecuaciones; ++indice_ren) {
        tabla->insert_row(indice_ren);  // insertar n renglones
        for (int indice_col = 0; indice_col < 2 * cant_ecuaciones - 1; ++indice_col) {
            // insertar entrada y separador (uno y uno)
            if (indice_col % 2 == 0) {
                imprimir_btn_aumentar(indice_ren, indice_col);
            } else {
                imprimir_etiqueta("+", indice_ren, indice_col);
            }
        }
        imprimir_etiqueta("=", indice_ren, 2 * cant_ecuaciones - 1);
        imprimir_btn_aumentar(indice_ren, 2 * cant_ecuaciones);
    }
    lista_cuadros->append(*tabla);
    show_all_children();    // muestra los cambios
}

Glib::RefPtr<Gtk::Builder> VentanaPrincipal::crear_constructor() {
    return Gtk::Builder::create_from_file("../interfaz_grafica.glade");
}

void VentanaPrincipal::imprimir_btn_aumentar(int indice_ren, int indice_col) {
    Glib::RefPtr<Gtk::Builder> constructorCelda = crear_constructor();
    // trae el objeto de botón
    Glib::RefPtr<Gtk::SpinButton> btn = Glib::RefPtr<Gtk::SpinButton>::cast_dynamic(
            constructorCelda->get_object("NumeroCelda"));
    btn->unparent();    // elimina referencia a padre
    tabla->attach(*btn.operator->(), indice_col, indice_ren);   // se inserta en la tabla
}

void VentanaPrincipal::imprimir_etiqueta(const std::string& sim, int indice_ren, int indice_col) {
    auto etiqueta = Gtk::make_managed<Gtk::Label>();
    // separador
    etiqueta->set_text(" x_" + std::to_string((indice_col + 1) / 2) + " " + sim + " ");
    tabla->attach(*etiqueta, indice_col, indice_ren);
}

void VentanaPrincipal::hacer_resolver_matriz() {
    MontanteSolver solucionador(matriz);
    //empieza a resolver la matriz / sistemas de ecuaciones
    std::vector<float> respuesta = solucionador.resolver();
    std::string respuesta_cadena("Respuesta: ");
    int cant_ecuaciones = int(ajuste_cant_ecuaciones->get_value());

    if (respuesta.empty())
        respuesta_cadena += "No tiene solución única";
    else {
        for (int i = 0; i < cant_ecuaciones; ++i) {
            // cadena de respuesta
            respuesta_cadena += "x_" + std::to_string(i + 1) + ": " + std::to_string(respuesta.at(i)) + ", ";
        }
        respuesta_cadena = respuesta_cadena.substr(0, respuesta_cadena.size() - 2);
    }
    // configurar etiqueta que muestra cadena
    auto etiqueta = Gtk::make_managed<Gtk::Label>();
    etiqueta->set_text(respuesta_cadena);
    etiqueta->set_visible();
    auto etiqueta_anterior = lista_cuadros->get_children().at(2);
    // eliminar la respuesta anterior
    lista_cuadros->remove(*etiqueta_anterior);
    delete(etiqueta_anterior);
    // insertar la nueva
    lista_cuadros->insert(*etiqueta, 2);
}

void VentanaPrincipal::obtener_matriz() {
    std::vector<std::vector<float>> mat;
    int cant_ecuaciones = int (ajuste_cant_ecuaciones->get_value());
    mat.reserve(cant_ecuaciones);   // reserva espacio en la matriz (n valores)
    // llena la matriz con los valores que introdujo el usuario
    for (int indice_ren = 0; indice_ren < cant_ecuaciones; ++indice_ren) {
        std::vector<float> ren;
        ren.reserve(cant_ecuaciones + 1);
        for (int indice_col = 0; indice_col < 2 * cant_ecuaciones + 1; indice_col += 2) {
            // obtiene un apuntador a un botón de la tabla
            auto btn = dynamic_cast<Gtk::SpinButton *>(tabla->get_child_at(indice_col, indice_ren));
            ren.push_back(float (btn->get_value()));
        }
        mat.push_back(ren);
    }

    matriz = mat;
    hacer_resolver_matriz();   // resolver la matriz que se consiguió
}
