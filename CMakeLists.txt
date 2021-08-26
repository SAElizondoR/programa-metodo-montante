cmake_minimum_required(VERSION 3.20)
project(programa_metodo_montante)

set(CMAKE_CXX_STANDARD 20)

find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-3.0)

link_directories(${GTKMM_LIBRARY_DIRS})
include_directories(${GTKMM_INCLUDE_DIRS})

add_executable(programa_metodo_montante main.cpp
        clases/MontanteSolver.h clases/MontanteSolver.cpp
        interfaz_grafica/VentanaPrincipal.cpp interfaz_grafica/VentanaPrincipal.h)

target_link_libraries(programa_metodo_montante ${GTKMM_LIBRARIES})