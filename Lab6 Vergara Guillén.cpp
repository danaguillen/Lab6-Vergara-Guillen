/*
 * Peso de los algoritmos (investigacion - Tarea 8)
 * La notacion O grande mide la cota superior del crecimiento del tiempo de ejecucion
 * o espacio a medida que crece el tamano de los datos (n).
 * Container::search: O(n) en el peor caso porque debe recorrer todo el arreglo secuencialmente
 * si el elemento esta en la ultima posicion o no se encuentra.
 * Container::sort: O(n^2) en el peor caso porque Bubble Sort realiza comparaciones anidadas
 * alcanzando aproximadamente n*(n-1)/2 operaciones cuando los datos estan invertidos.
 * Fuente: GeeksforGeeks (Data Structures and Algorithms) / Introduction to Algorithms (CLRS).
 */

#include <iostream>

const int CAPACITY = 100;

class Container {
protected:
    int data[CAPACITY];
    int count;
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

int main() {
    return 0;
}