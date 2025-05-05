#ifndef INVENTARIO_TEM_H_INCLUDED
#define INVENTARIO_TEM_H_INCLUDED
#include <iostream>
#include <string.h>
#include<cstring>
#include <utility>
#include"lista_doble.h"
#include"pila.h"
#include"cola.h"
class Producto {
private:
    string codigo;
    string nombre;
    float precio;
    int categoria;
    int existencias;

public:
    // Constructor
    Producto() : codigo(""), nombre(""), precio(0), categoria(0), existencias(0) {}

    // Getters y Setters
    Producto& operator=(const Producto& otro) {
        if (this != &otro) {  // Prevenir autoasignación
            codigo = otro.codigo;
            nombre = otro.nombre;
            precio = otro.precio;
            categoria = otro.categoria;
            existencias = otro.existencias;
        }
        return *this;
    }

    void setCodigo(const string cod) {
        codigo=cod;
    }

    const string getCodigo() {
        return codigo;
    }

    void setNombre(const string nom) {
        nombre=nom;
    }

    const string getNombre() {
        return nombre;
    }

    void setPrecio(float p) {
        precio = p;
    }

    float getPrecio() const {
        return precio;
    }

    void setCategoria(int cat) {
        categoria = cat;
    }

    int getCategoria() const {
        return categoria;
    }

    void setExistencias(int ex) {
        existencias = ex;
    }

    int getExistencias() const {
        return existencias;
    }
};
class Inventario {
private:
    int opCont=0;
    int petCont=0;
    int producCont=0;
    int catCont=0;
    int storeCont=5;
    lista_doble <Producto> productos;
    lista_doble <lista_doble<int>*> ventasMensuales;
    lista_doble <string> categorias;
    lista_doble <lista_doble<bool>*>disponibilidad;
    pila<string> operaciones;
    cola<string> peticiones;

public:
    // Constructor
    Inventario(){
        //llenado de ventas

    }

    // Métodos para gestión de inventario
    void agregarProducto(const string codigo, const string nombre, float precio, int categoria, int existencias) {
            operaciones.push("Agregar producto");
            opCont++;
            Producto *nuevo= new Producto;
            nuevo->setCodigo(codigo);
            nuevo->setNombre(nombre);
            nuevo->setPrecio(precio);
            nuevo->setCategoria(categoria);
            nuevo->setExistencias(existencias);
            productos.push_final(*nuevo);
            auto* fila = new lista_doble<int>();
            auto* fila1 = new lista_doble<bool>();
            for(int k = 0; k<12; k++){
                fila->push_final(0);
            }

            for(int k = 0; k<storeCont; k++){
                fila1->push_final(0);


            }
            ventasMensuales.push_final(fila);
            disponibilidad.push_final(fila1);
            producCont++;

    }

    void agregarCategoria(int index, string nombre) {
        operaciones.push("Agregar categoria");
        opCont++;
        if (index >= 0 && index < catCont) {
            categorias.insertar(nombre, index);
        }
    }

    void registrarVenta(int mes, int producto, int cantidad) {
        operaciones.push("Registro de venta");
        opCont++;//se agregan nuevas operaciones a la pila para mantener el registro
        if (mes > 0 && mes < 12 && producto > 0 && producto < producCont) {
            //se obtiene la fila deseada
            nodo<lista_doble<int>*>* actualFila = ventasMensuales.recorrer(mes);
            if (actualFila) {
                lista_doble<int>* fila = actualFila->data;

                // Recorremos esa fila hasta el índice deseado
                nodo<int>* actualElemento = fila->get_head();
                int index = 0;
                while (actualElemento && index < producto) {
                    actualElemento = actualElemento->next;
                    index++;
                }

                if (actualElemento) {
                    actualElemento->data = cantidad;  // Modificar el valor en la posición
                }
}
        }
    }

    void actualizarDisponibilidad(int sucursal, int producto, bool disponible) {
        operaciones.push("Actualizar disponibilidad");
        opCont++;
        if (sucursal >= 0 && sucursal < storeCont && producto >= 0 && producto < producCont) {
            //se obtiene la fila deseada
            nodo<lista_doble<bool>*>* actualFila = disponibilidad.recorrer(sucursal);
            if (actualFila) {
                lista_doble<bool>* fila = actualFila->data;

                // Recorremos esa fila hasta el índice deseado
                nodo<bool>* actualElemento = fila->get_head();
                int index = 0;
                while (actualElemento && index < producto) {
                    actualElemento = actualElemento->next;
                    index++;
                }

                if (actualElemento) {
                    actualElemento->data = disponible;  // Modificar el valor en la posición
                }
        }
    }
}
    // Búsqueda binaria por código de producto
int buscarProductoPorCodigo(const string codigo) {
    peticiones.enqueue("Busqueda");
    operaciones.push("Busqueda");
    opCont++;
    petCont++;
    int izquierda = 1;
    int derecha = producCont;

    while (izquierda <= derecha) {
        int medio = izquierda + (derecha - izquierda) / 2;
        string codigoMedio = productos.get(medio).getCodigo();
        int comparacion = codigoMedio.compare(codigo);

        if (comparacion == 0) {
            return medio;
        } else if (comparacion < 0) {
            izquierda = medio + 1;
        } else {
            derecha = medio - 1;
        }
    }

    return -1; // No encontrado
}

    // Ordenamiento por burbuja
    void ordenarPorNombre() {
        peticiones.enqueue("Ordenar por nombre");
        operaciones.push("Ordenar por nombre");
        opCont++;
        petCont++;
    for (int i = 1; i < producCont+1; ++i) {
        for (int j = 1; j < producCont - i + 1; ++j) {
            nodo<Producto>* nodo1 = productos.get_tipo(j);
            nodo<Producto>* nodo2 = productos.get_tipo(j + 1);
            if (nodo1 && nodo2 && nodo1->data.getNombre() > nodo2->data.getNombre()) {
                Producto temp = nodo1->data;
                nodo1->data = nodo2->data;
                nodo2->data = temp;
            }
        }
    }
}

    // Ordenamiento por inserción
    void ordenarPorPrecio() {
        peticiones.enqueue("Ordenar por precio");
        operaciones.push("Ordenar por precio");
        opCont++;
        petCont++;
        for (int i = 2; i <= producCont; ++i) {  // Base 1
            nodo<Producto>* nodoKey = productos.get_tipo(i);
            Producto key = nodoKey->data;

            int j = i - 1;
            nodo<Producto>* nodoJ = productos.get_tipo(j);

            while (j >= 1 && nodoJ->data.getPrecio() > key.getPrecio()) {
                nodoJ->next->data = nodoJ->data;  // Desplaza hacia adelante
                j--;
                if (j >= 1) {
                    nodoJ = productos.get_tipo(j);  // Actualiza nodoJ
                }
            }

            productos.get_tipo(j + 1)->data = key;
        }
    }
    //localizar el punto pedido de una lista de listas
    lista_doble<int>* getVentas(int mes){
        nodo<lista_doble<int>*>* actualFila = ventasMensuales.recorrer(mes);
        return actualFila->data;
    }
    lista_doble<bool>* getDisp(int sucursal){
        nodo<lista_doble<bool>*>* actualFila = disponibilidad.recorrer(sucursal);
        return actualFila->data;
    }
    // Operaciones matriciales para reportes de ventas
    int totalVentasAnuales() {
        peticiones.enqueue("Ventas anuales");
        operaciones.push("Ventas anuales");
        opCont++;
        petCont++;
        int total = 0;
        for (int i = 1; i < 13; ++i) {
            for (int j = 1; j < producCont+1; ++j) {
                total += getVentas(i)->get(j);
            }
        }
        return total;
    }

    // Estadísticas por categoría
    int ventasPorCategoria(int categoria) {
        peticiones.enqueue("Ventas por categoria");
        operaciones.push("Ventas por categoria");
        opCont++;
        petCont++;
        int total = 0;
        for (int i = 1; i < 13; ++i) {
            for (int j = 1; j < producCont+1; ++j) {
                if (productos.get(j).getCategoria() == categoria) {
                    total += getVentas(i)->get(j);
                }
            }
        }
        return total;
    }

    // Estadísticas por sucursal
    int productosDisponiblesEnSucursal(int sucursal) {
        peticiones.enqueue("Disponibilidad por tienda");
        operaciones.push("Disponibilidad por tienda");
        opCont++;
        petCont++;
        int total = 0;
        for (int j = 1; j < producCont+1; ++j) {
            if (getDisp(sucursal)->get(j)) {
                total++;
            }
        }
        return total;
    }
    string getProd(int k){
        if(k<producCont+1){
            return productos.get(k).getNombre();
        }
        throw out_of_range("Índice fuera del rango de productos");

    }
    string regresaOp(int k){
        if(0<k<opCont)
            return operaciones.get(k);
        else
           throw out_of_range("Índice fuera del rango de operaciones");
    }
    string regresaPet(int k){
        if(0<k<opCont)
            return peticiones.get(k);
        else
           throw out_of_range("Índice fuera del rango de peticiones");

    }
};


#endif // INVENTARIO_TEM_H_INCLUDED
