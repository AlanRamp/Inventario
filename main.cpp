#include"inventario_tem.h"
int main(){

    Inventario inv;
    inv.agregarProducto("123456787","halo 1",120.50,2,10);
    inv.agregarProducto("123456788","apex",123.50,2,10);
    inv.agregarProducto("123456789","euro truck",122.50,2,10);
    //3 operaciones
    cout<<"Busqueda de producto por codigo(123456789)"<<endl;
    cout<<inv.buscarProductoPorCodigo("123456789")<<endl;
    //1 operacion
    //1 peticion
    system("pause");
    system("cls");
    cout<<"Lista de productos"<<endl;
    for(int k=1; k<4; k++)
        cout<<inv.getProd(k)<<endl;
    system("pause");
    system("cls");
    inv.ordenarPorNombre();
    //1 operacion
    //1 peticion
    cout<<"Lista de productos ordenada por nombre"<<endl;
    for(int k=1; k<4; k++)
        cout<<inv.getProd(k)<<endl;
    system("pause");
    system("cls");
    inv.ordenarPorPrecio();
    //1 operacion
    //1 peticion
    cout<<"Lista de productos ordenada por precio"<<endl;
    for(int k=1; k<4; k++)
        cout<<inv.getProd(k)<<endl;
    system("pause");
    system("cls");
    cout<<"Pila de operaciones"<<endl;
    for(int k=1; k<7; k++)
        cout<<inv.regresaOp(k)<<endl;
    cout<<"Cola de Peticiones"<<endl;
    for(int k=1; k<4; k++)
        cout<<inv.regresaPet(k)<<endl;

    return 0;
}
