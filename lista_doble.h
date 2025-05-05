#ifndef LISTA_DOBLE_H_INCLUDED
#define LISTA_DOBLE_H_INCLUDED
#include <iostream>
#include <string>
#include<cstring>
#include <utility>
using namespace std;

template <typename tipo>

class nodo
{
    public:
        tipo data;
        nodo *next;
        nodo *prev;
        nodo(tipo d)
        {
            data=d;
            next=nullptr;
            prev=nullptr;
        }
        nodo()
        {
            next=nullptr;
            prev=nullptr;
        }

};

template <typename tipo>

class lista_doble
{
public:
    lista_doble()
    {
        head=nullptr;
        tail=nullptr;
        longitud=0;
    }
    lista_doble(const lista_doble &rhs)
    {
        head=rhs.head;
        tail=rhs.tail;
        longitud=rhs.longitud;

    }
    lista_doble(lista_doble &&rhs)
    {
        head=move(rhs.head);
        tail=move(rhs.tail);
        longitud=move(rhs.longitud);
    }
    ~lista_doble()
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
    void insertar(tipo valor, int i)
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

        else if(i==longitud+1)
        {
            nuevo->prev=tail;
            tail->next=nuevo;
            tail=nuevo;
            tail->next=head;
            head->prev=tail;
            longitud++;

        }
        else if(i==1)
        {
            nuevo->next=head;
            head->prev=nuevo;
            head=nuevo;
            head->prev=tail;
            tail->next=head;
            longitud++;

        }
        else if(i>1&&i<=longitud)
        {
            nodo<tipo> *tmp=head;
            for(int j=1;j<i-1;j++)
            {
                tmp=tmp->next;
            }
            nuevo->prev=tmp;
            nuevo->next=tmp->next;
            tmp->next=nuevo;
            nuevo->next->prev=nuevo;
            longitud++;

        }

    }
    void push_final(tipo valor)
    {
        insertar(valor,longitud+1);
    }
    void push_inicio(tipo valor)
    {
        insertar(valor,1);
    }
    void push_i(tipo valor,int i)
    {
        insertar(valor,i);
    }
    void eliminar(int i)
    {
        nodo<tipo> *tmp=head;
        if(!vacia())
        {
            if(i==1)
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
            else if(i==longitud)
            {

                tail=tail->prev;
                delete tail->next;
                tail->next=head;
                head->prev=tail;
                longitud--;

            }
            else
            {
                for(int j=1;j<i-1;j++)
                {
                    tmp=tmp->next;
                }
                tmp->next=tmp->next->next;
                delete tmp->next->prev;
                tmp->next->prev=tmp;
                longitud--;

            }
        }
        else
           throw std::out_of_range("lista vacía");
    }
    void pop_final()
    {
        eliminar(longitud);
    }
    void pop_inicio()
    {
        eliminar(1);
    }
    void pop_i(int i)
    {
        eliminar(i);
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
    nodo<tipo>* get_tipo(int k) {
    if (vacia() || k < 1 || k > longitud) return nullptr;
    nodo<tipo>* tmp = head;
    for (int j = 1; j < k; ++j)
        tmp = tmp->next;
    return tmp;
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

#endif // LISTA_DOBLE_H_INCLUDED
