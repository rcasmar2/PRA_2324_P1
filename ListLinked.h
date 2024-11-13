#include <ostream>
#include "List.h"
#include "Node.h"
#include <stdexcept>

template <typename T> class ListLinked : public List<T> {

    private:
        Node<T>* head;     // Puntero al primer nodo de la lista
        int elementCount;  // Número de elementos en la lista
        
    public:
        
        // Constructor que inicializa los atributos head y elementCount
        ListLinked() {
            head = nullptr;
            elementCount = 0;
        }   

        // Destructor que libera la memoria reservada para los nodos de la lista
        ~ListLinked() {
            while(head != nullptr) {   
                // Puntero auxiliar que apunta al siguiente nodo
                Node<T>* temp = head->next;   

                // Libera el nodo actual
                delete head;

                // Avanza el puntero head
                head = temp;
            } 
        }
        
        // Sobrecarga del operador [] que devuelve el elemento en la posición indicada
        T operator[](int pos) {
            if(pos >= 0 && pos < elementCount) {
                Node<T>* temp = head;  // Comienza desde el nodo principal
                int index = 0;
                while(temp != nullptr && index < pos) {
                    temp = temp->next;
                    index++;
                }
                return temp->data; // Devuelve el dato en la posición pos
            } else {
                throw std::out_of_range("Posición fuera de rango: pos = " + std::to_string(pos));
            }
        }
        
        // Sobrecarga del operador << para imprimir la lista
        friend std::ostream& operator<<(std::ostream &out, const ListLinked<T> &list) {
            if(list.elementCount == 0)
                out << "List => []";
            else {
                out << "List => [\n";
                Node<T>* temp = list.head;
                int index = 0;
                while(temp != nullptr && index < list.elementCount) {
                    out << "  " << temp->data;
                    temp = temp->next;
                    if(index != list.elementCount - 1) { // Evita la coma después del último elemento
                        out << "\n";
                    }
                    index++;
                }
                out << "\n]";
            }
            return out;
        }

        /******************* Implementación de los métodos de List<T> **************************/

        // Inserta un elemento en la posición indicada
        void insert(int pos, T e) override {
            if(pos >= 0 && pos <= elementCount) {
                Node<T>* previous = nullptr;
                Node<T>* current = head;
                int index = 0;
                while(current != nullptr && index < pos) {
                    previous = current;
                    current = current->next;
                    index++;
                }
                // Inserta al principio si pos es cero
                if(current == head) {
                    head = new Node<T>(e, head);
                } else {
                    previous->next = new Node<T>(e, current); 
                }
                elementCount++;
            } else {
                throw std::out_of_range("Posición fuera de rango: pos = " + std::to_string(pos));
            }
        }
        
        // Añade un elemento al final de la lista
        void append(T e) override {
            insert(elementCount, e);
        }
        
        // Añade un elemento al principio de la lista
        void prepend(T e) override {
            insert(0, e);
        }
        
        // Elimina y devuelve el elemento en la posición indicada
        T remove(int pos) override {
            if(pos >= 0 && pos < elementCount) {
                Node<T>* previous = nullptr;
                Node<T>* current = head;
                int index = 0;
                while(current != nullptr && index < pos) {
                    previous = current;
                    current = current->next;
                    index++;
                }
                // Si el nodo es el primero
                if(current == head) {
                    head = head->next;
                } else {
                    previous->next = current->next;
                }
                T removedValue = current->data;
                delete current;
                elementCount--;
                return removedValue;
            } else {
                throw std::out_of_range("Posición fuera de rango: pos = " + std::to_string(pos));
            }
        }

        // Devuelve el elemento en la posición indicada
        T get(int pos) override {
            if(pos >= 0 && pos < elementCount) {
                Node<T>* temp = head;
                int index = 0;
                while(temp != nullptr && index < pos) {
                    temp = temp->next;
                    index++;
                }
                return temp->data;
            } else {
                throw std::out_of_range("Posición fuera de rango: pos = " + std::to_string(pos));
            }
        }
        
        // Devuelve la posición del primer elemento encontrado o -1 si no está en la lista
        int search(T e) override {
            Node<T>* temp = head;
            int index = 0;
            while(temp != nullptr && temp->data != e) {
                temp = temp->next;
                index++;
            }
            return (temp != nullptr) ? index : -1;
        }
        
        // Indica si la lista está vacía
        bool empty() override {
            return elementCount == 0;
        }

        // Devuelve el número de elementos de la lista
        int size() override {
            return elementCount;
        }   
};

