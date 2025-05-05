#ifndef PILA_H_INCLUDED
#define PILA_H_INCLUDED
#include <iostream>
#include <string>
#include<cstring>
#include <utility>
#include"lista_doble.h"
using namespace std;


template <typename tipo>

class pila
{
public:
    pila()
    {
        head=nullptr;
        tail=nullptr;
        longitud=0;
    }
    pila(const pila &rhs)
    {
        head=rhs.head;
        tail=rhs.tail;
        longitud=rhs.longitud;

    }
    pila(pila &&rhs)
    {
        head=move(rhs.head);
        tail=move(rhs.tail);
        longitud=move(rhs.longitud);
    }
    ~pila()
    {
        if(head!=nullptr)
        delete head;
        if(tail!=nullptr&&longitud>1)
        delete tail;
    }
    int vacia()
    {
        if(head==nullptr)
            return 1;
        else
            return 0;
    }
    void push(tipo valor)
    {
        nodo<tipo> *nuevo = new nodo<tipo>(valor);
        if(vacia()) {
        head = tail = nuevo;
        nuevo->next = nullptr;
        nuevo->prev = nullptr;
        longitud++;
        }
        else
        {
            nuevo->next=head;
            head->prev=nuevo;
            head=nuevo;
            head->prev=tail;
            tail->next=head;
            longitud++;

        }
    }

    void pop()
    {
        nodo<tipo> *tmp=head;
        if(!vacia())
        {

                if(longitud==1)
                {
                    delete head;
                    head=tail=nullptr;
                }
                else
                {
                    head=head->next;
                    delete head->prev;
                    head->prev=tail;
                    tail->next=head;

                }
                longitud--;

        }
        else
            throw std::out_of_range("lista vacía");
    }

    tipo get(int i)
    {
        nodo<tipo> *tmp=head;
        if(!vacia())
        {
            if(i==1)
            {
                return tmp->data;
            }
            else if(i==longitud)
            {
                return tail->data;
            }
            else
            {
                for(int j=1;j<i;j++)
                tmp=tmp->next;
                return tmp->data;

            }
        }
        else
        {
            throw std::out_of_range("Índice fuera de rango o lista vacía");
        }
    }
    int get_longitud()
    {
        return longitud;
    }
    nodo<tipo>* recorrer(int k){
        nodo<tipo>*tmp=nullptr;
        if(!vacia()){
         tmp=head;
        for(int j=1;j<k;j++)
            tmp=tmp->next;
        }else
            return nullptr;
        return tmp;
    }
    nodo<tipo>* get_head(){
        return head;
    }
    nodo<tipo>* get_tail(){
        return tail;
    }
private:

    nodo<tipo> *head;
    nodo<tipo> *tail;
    int longitud;
};


#endif // PILA_H_INCLUDED
