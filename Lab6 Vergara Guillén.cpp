/*
 * Tarea 8 - Analisis de complejidad algoritmica (Big O):
 *
 * La notacion O grande nos permite medir el limite superior del crecimiento en tiempo o espacio
 * de un algoritmo conforme aumenta la cantidad de datos (n).
 *
 * 1. Container::search - O(n):
 * En el peor de los casos, la busqueda secuencial tiene que revisar cada uno de los elementos
 * del arreglo si el valor buscado esta al final o si no existe del todo.
 *
 * 2. Container::sort - O(n^2):
 * Al implementar Bubble Sort, se hacen comparaciones mediante dos ciclos anidados. Esto hace
 * que el numero de operaciones crezca de forma cuadratica (aprox. n*(n-1)/2 comparaciones cuando
 * los datos estan en orden inverso).
 *
 * Referencias: GeeksforGeeks / Introduction to Algorithms (CLRS).
 */

#include <iostream>

const int CAPACITY = 100;

class Container {
protected:
    int data[CAPACITY] = {};
    int count = 0;
    static int containerCount;

public:
    Container() {
        count = 0;
        containerCount++;
    }

    bool isEmpty() const {
        return count == 0;
    }

    bool isFull() const {
        return count == CAPACITY;
    }

    int getCount() const {
        return count;
    }

    void print() const {
        if (isEmpty()) {
            std::cout << "[ ]\n";
            return;
        }
        std::cout << "[ ";
        for (int i = 0; i < count; i++) {
            std::cout << data[i] << " ";
        }
        std::cout << "]\n";
    }

    int search(int value) const {
        for (int i = 0; i < count; i++) {
            if (data[i] == value) {
                return i;
            }
        }
        return -1;
    }

    int countOccurrences(int value) const {
        int occurrences = 0;
        for (int i = 0; i < count; i++) {
            if (data[i] == value) {
                occurrences++;
            }
        }
        return occurrences;
    }

    void sort() {
        for (int i = 0; i < count - 1; i++) {
            for (int j = 0; j < count - 1 - i; j++) {
                if (data[j] > data[j + 1]) {
                    int temp = data[j];
                    data[j] = data[j + 1];
                    data[j + 1] = temp;
                }
            }
        }
    }

    static int getContainerCount() {
        return containerCount;
    }
};

int Container::containerCount = 0;

class Stack : public Container {
private:
    int top;

public:
    Stack() : Container() {
        top = -1;
    }

    void push(int value) {
        if (isFull()) {
            std::cout << "Error: Stack full\n";
            return;
        }
        data[++top] = value;
        count++;
    }

    int pop() {
        if (isEmpty()) {
            std::cout << "Error: Stack empty\n";
            return -1;
        }
        count--;
        return data[top--];
    }
};

/*
 * Explicacion Tarea 7:
 * En esta estructura lineal, cuando sacamos elementos de la cola (dequeue), los espacios antes
 * del indice 'front' quedan desaprovechados porque no se vuelven a ocupar. Esto provoca que 'back'
 * llegue al final del arreglo (CAPACITY - 1) y marque la cola como llena, aunque en realidad
 * queden pocos elementos almacenados.
 *
 * Para resolver esto y reutilizar las posiciones libres, habria que convertirla en una cola
 * circular apoyandonos en el operador modulo (%).
 */
class Queue : public Container {
private:
    int front;
    int back;

public:
    Queue() : Container() {
        front = 0;
        back = -1;
    }

    void enqueue(int value) {
        if (back == CAPACITY - 1) {
            std::cout << "Error: Queue full\n";
            return;
        }
        data[++back] = value;
        count++;
    }

    int dequeue() {
        if (isEmpty()) {
            std::cout << "Error: Queue empty\n";
            return -1;
        }
        count--;
        return data[front++];
    }
};

int main() {
    return 0;
}