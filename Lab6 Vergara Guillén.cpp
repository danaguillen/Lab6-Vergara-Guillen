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

class Matrix {
private:
    int cells[3][3];

public:
    Matrix() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                cells[i][j] = 0;
            }
        }
    }

    void setValue(int row, int col, int value) {
        if (row >= 0 && row < 3 && col >= 0 && col < 3) {
            cells[row][col] = value;
        }
    }

    int getValue(int row, int col) const {
        if (row >= 0 && row < 3 && col >= 0 && col < 3) {
            return cells[row][col];
        }
        return 0;
    }

    int sum() const {
        int total = 0;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                total += cells[i][j];
            }
        }
        return total;
    }

    int sumRow(int row) const {
        if (row < 0 || row >= 3) return 0;
        int total = 0;
        for (int j = 0; j < 3; j++) {
            total += cells[row][j];
        }
        return total;
    }

    void multiply(const Matrix& other, Matrix& result) const {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                int sumCell = 0;
                for (int k = 0; k < 3; k++) {
                    sumCell += cells[i][k] * other.cells[k][j];
                }
                result.setValue(i, j, sumCell);
            }
        }
    }

    void print() const {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                std::cout << cells[i][j] << " ";
            }
            std::cout << "\n";
        }
    }
};

int main() {
    Stack stack;
    Queue queue;
    Matrix matA, matB, matResult;
    int option = 0;

    do {
        std::cout << "\n1. Push Stack\n2. Pop Stack\n3. Enqueue Queue\n4. Dequeue Queue\n"
            << "5. Search Stack\n6. Count Occurrences Stack\n7. Sort Copy Stack\n"
            << "8. Print Structures\n9. Matrix Operations\n10. Multiply Matrices\n"
            << "11. Container Count\n12. Exit\nOption: ";
        if (!(std::cin >> option)) break;

        switch (option) {
        case 1: {
            int val;
            std::cin >> val;
            stack.push(val);
            break;
        }
        case 2:
            std::cout << "Popped: " << stack.pop() << "\n";
            break;
        case 3: {
            int val;
            std::cin >> val;
            queue.enqueue(val);
            break;
        }
        case 4:
            std::cout << "Dequeued: " << queue.dequeue() << "\n";
            break;
        case 5: {
            int val;
            std::cin >> val;
            std::cout << "Index: " << stack.search(val) << "\n";
            break;
        }
        case 6: {
            int val;
            std::cin >> val;
            std::cout << "Occurrences: " << stack.countOccurrences(val) << "\n";
            break;
        }
        case 7: {
            Container sorted = stack;
            sorted.sort();
            std::cout << "Original: ";
            stack.print();
            std::cout << "Sorted copy: ";
            sorted.print();
            break;
        }
        case 8:
            std::cout << "Stack: ";
            stack.print();
            std::cout << "Queue: ";
            queue.print();
            break;
        case 9: {
            int val = 1;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    matA.setValue(i, j, val++);
                }
            }
            matA.print();
            std::cout << "Sum: " << matA.sum() << "\n";
            std::cout << "Sum Row 0: " << matA.sumRow(0) << "\n";
            break;
        }
        case 10: {
            matA.setValue(0, 0, 1); matA.setValue(0, 1, 2); matA.setValue(0, 2, 3);
            matA.setValue(1, 0, 4); matA.setValue(1, 1, 5); matA.setValue(1, 2, 6);
            matA.setValue(2, 0, 7); matA.setValue(2, 1, 8); matA.setValue(2, 2, 9);

            matB.setValue(0, 0, 1); matB.setValue(0, 1, 0); matB.setValue(0, 2, 0);
            matB.setValue(1, 0, 0); matB.setValue(1, 1, 1); matB.setValue(1, 2, 0);
            matB.setValue(2, 0, 0); matB.setValue(2, 1, 0); matB.setValue(2, 2, 1);

            matA.multiply(matB, matResult);
            matResult.print();
            break;
        }
        case 11:
            std::cout << "Containers: " << Container::getContainerCount() << "\n";
            break;
        }
    } while (option != 12);

    return 0;
}