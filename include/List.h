#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "List.h"
#include <stdexcept>
#include <string>
#include <sstream>

template <typename T>
class LinkedList : public List<T> {
private:
    struct Node {
        T element;
        Node* next;

        Node(const T& elem, Node* n = nullptr) : element(elem), next(n) {}
    };

    Node* head;
    Node* tail;
    int sizeCount;

    Node* searchNode(int position) const {
        if (position < 0 || position >= sizeCount) {
            throw std::out_of_range("Index out of bounds");
        }
        Node* current = head;
        for (int i = 0; i < position; ++i) {
            current = current->next;
        }
        return current;
    }

public:
    LinkedList() : head(nullptr), tail(nullptr), sizeCount(0) {}

    ~LinkedList() override {
        clear();
    }

    void addFirst(const T& element) override {
        Node* newNode = new Node(element, head);
        head = newNode;
        if (sizeCount == 0) {
            tail = head;
        }
        sizeCount++;
    }

    void addLast(const T& element) override {
        Node* newNode = new Node(element);
        if (sizeCount == 0) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        sizeCount++;
    }

    void insertAt(int index, const T& element) override {
        if (index < 0 || index > sizeCount) throw std::out_of_range("Index out of bounds");

        if (index == 0) {
            addFirst(element);
        } else if (index == sizeCount) {
            addLast(element);
        } else {
            Node* prev = searchNode(index - 1);
            Node* newNode = new Node(element, prev->next);
            prev->next = newNode;
            sizeCount++;
        }
    }

    void addSorted(const T& element) override {
        if (sizeCount == 0 || head->element >= element) {
            addFirst(element);
            return;
        }
        Node* current = head;
        while (current->next != nullptr && current->next->element < element) {
            current = current->next;
        }
        Node* newNode = new Node(element, current->next);
        current->next = newNode;
        if (newNode->next == nullptr) {
            tail = newNode;
        }
        sizeCount++;
    }

    void removeFirst() override {
        if (sizeCount == 0) throw std::underflow_error("List is empty");

        Node* temp = head;
        head = head->next;
        delete temp;
        sizeCount--;

        if (sizeCount == 0) {
            tail = nullptr;
        }
    }

    void removeLast() override {
        if (sizeCount == 0) throw std::underflow_error("List is empty");

        if (sizeCount == 1) {
            removeFirst();
            return;
        }
        Node* prev = searchNode(sizeCount - 2);
        delete tail;
        tail = prev;
        tail->next = nullptr;
        sizeCount--;
    }

    void removeAt(int index) override {
        if (index < 0 || index >= sizeCount) throw std::out_of_range("Index out of bounds");

        if (index == 0) {
            removeFirst();
        } else if (index == sizeCount - 1) {
            removeLast();
        } else {
            Node* prev = searchNode(index - 1);
            Node* toDelete = prev->next;
            prev->next = toDelete->next;
            delete toDelete;
            sizeCount--;
        }
    }

    bool remove(const T& element) override {
        int index = find(element);
        if (index != -1) {
            removeAt(index);
            return true;
        }
        return false;
    }

    void clear() override {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
        sizeCount = 0;
    }

    int find(const T& element) const override {
        Node* current = head;
        int index = 0;
        while (current != nullptr) {
            if (current->element == element) {
                return index;
            }
            current = current->next;
            index++;
        }
        return -1;
    }

    T get(int index) const override {
        return searchNode(index)->element;
    }

    void set(int index, const T& element) override {
        searchNode(index)->element = element;
    }

    int size() const override {
        return sizeCount;
    }

    // Auxiliary method to help validating states during tests
    std::string toString() const {
        std::stringstream ss;
        ss << "[";
        Node* current = head;
        while (current != nullptr) {
            ss << current->element;
            if (current->next != nullptr) {
                ss << ", ";
            }
            current = current->next;
        }
        ss << "]";
        return ss.str();
    }
};

#endif // LINKED_LIST_H