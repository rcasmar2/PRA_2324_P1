#include "List.h"
#include <ostream>
#include <stdexcept>

template <typename T> class ListArray : public List<T> {

    // Miembros privados
private:
    T* elements;                     // Puntero al array que almacena los elementos de tipo  genérico T
    int capacity;                    // Capacidad del array (máxima cantidad de elementos antes de redimensionar)
    int count;                       // Cantidad actual de elementos en la lista
    static const int INITIAL_SIZE = 2;   // Capacidad mínima del array al inicio

    /* Redimensiona el array al tamanyo especificado (nuevo_tamanyo), ya sea para expandir si está lleno o reducir si hay demasiados espacios vacíos */
    void resize(int nuevo_tamanyo) {
        // 1) Crear un nuevo array de tamanyo nuevo_tamanyo usando new
        T* nuevo_array = new T[nuevo_tamanyo];

        // 2) Copiar los elementos actuales al nuevo array
        for (int i = 0; i < count; i++)
            nuevo_array[i] = elements[i];

        // 3) Liberar la memoria ocupada por el array anterior
        delete[] elements;

        // 4) Actualizar el puntero elements para que apunte al nuevo array
        elements = nuevo_array;

        // 5) Actualizar la capacidad
        capacity = nuevo_tamanyo;
    }

    // Métodos públicos, incluidos los heredados de la clase base List<T>
public:
    // Constructor de la clase
    ListArray() {
        count = 0;
        capacity = INITIAL_SIZE;
        elements = new T[INITIAL_SIZE];   // Inicializa un array dinámico con el tamanyo mínimo
    }

    // Destructor de la clase
    ~ListArray() {
        delete[] elements;
    }

    // Sobrecarga de operador []
    T operator[](int pos) {
        if (pos >= 0 && pos < count)   // Verifica que la posición esté dentro del rango válido
            return elements[pos];      // Devuelve el elemento en la posición solicitada
        else
            throw std::out_of_range("Posición fuera del rango del array");
    }

    // Sobrecarga del operador << para imprimir el contenido de la lista
    friend std::ostream& operator<<(std::ostream& out, const ListArray<T>& list) {

        // Imprime la lista
        if (list.count == 0)
            out << "List => []";
        else {
            out << "List => [\n";
            for (int i = 0; i < list.count; i++) {
                out << "  " << list.elements[i];
                if (i != list.count - 1) {
                    out << "\n";
                }
            }
            out << "\n]";
        }

        return out;
    }

    /******* Implementación de los métodos públicos heredados de List<T> *******/

    // Inserta el elemento e en la posición especificada
    void insert(int pos, T e) override {
        if (pos >= 0 && pos <= count) {
            if (count == capacity) {
                resize(2 * capacity);
            }

            for (int i = count; i > pos; i--) {
                elements[i] = elements[i - 1];
            }

            // Inserta el nuevo elemento en la posición indicada
            elements[pos] = e;
            count++;
        } else {
            throw std::out_of_range("Posición fuera del rango del array");
        }
    }

    // Inserta el elemento e al final de la lista
    void append(T e) override {
        insert(count, e);  // Usa insert para agregar al final
    }

    // Inserta el elemento e al principio de la lista
    void prepend(T e) override {
        insert(0, e);  // Usa insert para agregar al principio
    }

    // Elimina y devuelve el elemento en la posición especificada
    T remove(int pos) override {
        if (pos >= 0 && pos < count) {
            T valor_eliminado = elements[pos];
            for (int i = pos; i < count - 1; i++) {
                elements[i] = elements[i + 1];
            }
            count--;
            return valor_eliminado;
        } else {
            throw std::out_of_range("Posición fuera del rango del array");
        }
    }

    // Devuelve el elemento en la posición especificada
    T get(int pos) override {
        if (pos >= 0 && pos < count) {
            return elements[pos];
        } else {
            throw std::out_of_range("Posición fuera del rango del array");
        }
    }

    // Devuelve la primera posición en la que aparece el elemento e en el array, o -1 si no lo encuentra
    int search(T e) override {
        for (int i = 0; i < count; i++) {
            if (elements[i] == e)
                return i;
        }
        return -1; // Devuelve -1 si no encuentra el elemento
    }

    // Devuelve true si la lista está vacía
    bool empty() override {
        return count == 0;
    }

    // Devuelve la cantidad de elementos en la lista
    int size() override {
        return count;
    }
};
