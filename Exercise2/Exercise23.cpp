// Αλέξανδρος Γέροντας - ICSD15029

#include <iostream>

class arrayStack {
    int *stack, size, top;

public:
    /// Αρχικοποίηση τιμών
    arrayStack() {
        top = -1;
        size = 1;
        stack = new int[size];
    }

    /// Δυναμική καταχώριση τιμών
    void push(int value) {
        if (isFull()) newArray(size * 2);
        stack[++top] = value;
    }

    int pop() {
        int temp = stack[top--];

        /// Δεν γίνεται κατάχρηση της μνήμης
        if (top == -1) delete[] stack;
        else if ( size > (4 * top) ) newArray(size/2);

        return temp;
    }

    bool isFull() {
        return (top == size);
    }

    bool isEmpty() {
        return (top == -1);
    }

    // Διαγράφεται ο παλιός πίνακας και δημιουργείται νεος
    void newArray(int size) {
        this->size = size;

        int *newStack = new int[size];

        for (int i = 0; i <= top; i++)
            newStack[i] = stack[i];

        delete[] stack;
        this->stack = newStack;
    }
};

int main() {
    int num;
    arrayStack *s = new arrayStack;

    // Έλεγχος εισόδου
    do {
        std::cout << "Arithmos: ";
        std::cin >> num;
    } while (num < 1 || num > 255);

    // Ακέραια διαίρεση με το 2
    while (num != 0) {
        s->push(num % 2);
        num /= 2;
    }

    // Επανάληψη όσο η στοίβα δεν είναι άδεια
    while (!s->isEmpty()) std::cout << s->pop();
    std::cout << std::endl;

    return 0;
}
