#ifndef COLA_H_INCLUDED
#define COLA_H_INCLUDED
#include <iostream>
#include <string>
#include<cstring>
#include <utility>
#include"lista_doble.h"
using namespace std;


template <typename tipo>

class cola
{
public:
    cola()
    {
        head=nullptr;
        tail=nullptr;
        longitud=0;
    }
    cola(const cola &rhs)
    {
        head=rhs.head;
        tail=rhs.tail;
        longitud=rhs.longitud;

    }
    cola(cola &&rhs)
    {
        head=move(rhs.head);
        tail=move(rhs.tail);
        longitud=move(rhs.longitud);
    }
    ~cola()
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
    void enqueue(tipo valor)
    {
        nodo<tipo> *nuevo = new nodo<tipo>(valor);
        if(vacia()) {
        head = tail = nuevo;
        nuevo->next = nullptr;
        nuevo->prev = nullptr;
        longitud++;
        }
        else if(head==tail)
        {
            head->next=nuevo;
            tail=nuevo;
            tail->prev=head;
            tail->next=head;
            head->prev=tail;
            longitud++;

        }

        else
        {
            nuevo->prev=tail;
            tail->next=nuevo;
            tail=nuevo;
            tail->next=head;
            head->prev=tail;
            longitud++;

        }

    }
    void dequeue()
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


#endif // COLA_H_INCLUDED
