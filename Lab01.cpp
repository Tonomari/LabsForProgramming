#include <iostream>
#include <string>

// Класс Node представляет узел списка
class Node {
public:
    int intData;
    double doubleData;
    std::string stringData;
    Node* next;

    Node(int intVal, double doubleVal, const std::string& strVal)
        : intData(intVal), doubleData(doubleVal), stringData(strVal), next(nullptr) {}
};

// Класс LinkedList управляет списком узлов
class LinkedList {
private:
    Node* head;

public:
    LinkedList() : head(nullptr) {}

    // Метод для добавления узла в начало списка
    void addToFront(int intVal, double doubleVal, const std::string& strVal) {
        Node* newNode = new Node(intVal, doubleVal, strVal);
        newNode->next = head;
        head = newNode;
    }

    // Метод для добавления узла в конец списка
    void addToEnd(int intVal, double doubleVal, const std::string& strVal) {
        Node* newNode = new Node(intVal, doubleVal, strVal);
        if (!head) {
            head = newNode;
            return;
        }
        Node* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    // Метод для добавления узла в начало по индексу
    void addToFrontIndex(int index, int intVal, double doubleVal, const std::string& strVal) {
        if (index == 0) {
            addToFront(intVal, doubleVal, strVal);
            return;
        }
        Node* newNode = new Node(intVal, doubleVal, strVal);
        Node* temp = head;
        for (int i = 0; temp != nullptr && i < index - 1; ++i) {
            temp = temp->next;
        }
        if (temp) {
            newNode->next = temp->next;
            temp->next = newNode;
        }
    }

    // Метод для добавления узла в конец по индексу
    void addToEndIndex(int index, int intVal, double doubleVal, const std::string& strVal) {
        if (index == 0) {
            addToEnd(intVal, doubleVal, strVal);
            return;
        }
        Node* newNode = new Node(intVal, doubleVal, strVal);
        Node* temp = head;
        for (int i = 0; temp != nullptr && i < index; ++i) {
            temp = temp->next;
        }
        if (temp) {
            newNode->next = temp->next;
            temp->next = newNode;
        }
    }

    // Метод для удаления узла по значению
    void remove(int intVal, double doubleVal, const std::string& strVal) {
        if (!head) return;

        if (head->intData == intVal && head->doubleData == doubleVal && head->stringData == strVal) {
            Node* temp = head;
            head = head->next;
            delete temp;
            return;
        }

        Node* temp = head;
        while (temp->next && !(temp->next->intData == intVal && temp->next->doubleData == doubleVal && temp->next->stringData == strVal)) {
            temp = temp->next;
        }
        if (temp->next) {
            Node* nodeToDelete = temp->next;
            temp->next = temp->next->next;
            delete nodeToDelete;
        }
    }

    // Метод для печати всех узлов списка
    void printAll() const {
        Node* temp = head;
        while (temp) {
            std::cout << "Int: " << temp->intData
                      << ", Double: " << temp->doubleData
                      << ", String: " << temp->stringData << "\n";
            temp = temp->next;
        }
    }

    // Деструктор для очистки памяти
    ~LinkedList() {
        Node* temp;
        while (head) {
            temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    LinkedList list;
    list.addToFront(1, 1.1, "First");
    list.addToEnd(2, 2.2, "Second");
    list.addToFrontIndex(1, 3, 3.3, "Third");
    list.addToEndIndex(1, 4, 4.4, "Fourth");

    std::cout << "List after additions:\n";
    list.printAll();

    list.remove(3, 3.3, "Third");

    std::cout << "\nList after removal:\n";
    list.printAll();

    return 0;
}
