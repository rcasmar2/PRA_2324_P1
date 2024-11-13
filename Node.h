#include <ostream>

template <typename T> class Node {
    public:

		// Atributos
		T data;				// Elemento guardado
		Node<T>* next;		// Puntero al siguiente nodo  (o a nullptr en caso de ser el último)
    	
		// Métodos

		// Constructor
		 Node(T data, Node<T>* next = nullptr){			
		 	this->data = data;
			this->next = next;
		 }
		 friend std::ostream& operator<<(std::ostream &out, const Node<T> &node){
			out << node.data;
			return out;
		}


};