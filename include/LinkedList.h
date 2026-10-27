//
// Created by Junio Moreira on 24/09/26.
//

#ifndef ED1_LIST_CPP_ARRAYLIST_H
#define ED1_LIST_CPP_ARRAYLIST_H

#include "List.h"
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <string>

template <typename T>
class LinkedList : public List<T> {
private:
    T* items;
    int count;
    int capacity;

    const int NOT_FOUND = -1;
    const std::string DOES_NOT_EXIST = "Position does not exist.";
    const std::string LIST_FULL = "Error: List is full!";
    const std::string LIST_EMPTY = "List is empty.";

    bool positionDoesNotExist(int position) const {
        return !(position >= 0 && position < count);
    }

public:
    explicit LinkedList(int size) {
        this->capacity = size;
        this->items = new T[capacity];
        this->count = 0;
    }

    // Destructor to free dynamically allocated memory
    ~LinkedList() override {
        delete[] items;
    }

    bool isFull() const {
        return count == capacity;
    }

    bool isEmpty() const {
        return count == 0;
    }

    void addFirst(const T& item) override {
        insertAt(0, item);
    }

    void addLast(const T& item) override {
        if (isFull()) {
            std::cout << LIST_FULL << std::endl;
            return;
        }
        items[count++] = item;
    }

    void insertAt(int i, const T& item) override {
        if (isFull()) {
            std::cout << LIST_FULL << std::endl;
            return;
        }
        if (i < 0 || i > count) {
            throw std::invalid_argument(DOES_NOT_EXIST);
        }

        for (int j = count; j > i; j--) {
            items[j] = items[j - 1];
        }
        items[i] = item;
        count++;
    }

    void addSorted(const T& element) override {
        if (isFull()) {
            std::cout << LIST_FULL << std::endl;
            return;
        }

        int i = 0;
        // In C++, T must have the '<' operator defined
        while (i < count && items[i] < element) {
            i++;
        }
        insertAt(i, element);
    }

    T removeFirst() override {
        return removeAt(0);
    }

    T removeLast() override {
        if (isEmpty()) {
            throw std::runtime_error(LIST_EMPTY);
        }
        T removedItem = items[count - 1];
        count--;
        return removedItem;
    }

    T removeAt(int i) override {
        if (positionDoesNotExist(i)) {
            throw std::invalid_argument(DOES_NOT_EXIST);
        }

        T removedItem = items[i];

        for (int j = i; j < count - 1; j++) {
            items[j] = items[j + 1];
        }

        count--;
        return removedItem;
    }

    bool remove(const T& item) override {
        int position = find(item);

        if (position == NOT_FOUND) {
            return false;
        }

        removeAt(position);
        return true;
    }

    void clear() override {
        this->count = 0;
    }

    int find(const T& item) const override {
        for (int i = 0; i < count; i++) {
            if (items[i] == item) {
                return i;
            }
        }
        return NOT_FOUND;
    }

    T get(int i) const override {
        if (positionDoesNotExist(i)) {
            throw std::invalid_argument(DOES_NOT_EXIST);
        }
        return items[i];
    }

    void set(int i, const T& item) override {
        if (positionDoesNotExist(i)) {
            throw std::invalid_argument(DOES_NOT_EXIST);
        }
        items[i] = item;
    }

    int size() const override {
        return count;
    }

    std::string toString() const {
        if (count == 0) {
            return "[]";
        }

        std::ostringstream builder;
        builder << "[";
        for (int i = 0; i < count; i++) {
            builder << items[i];
            if (i < count - 1) {
                builder << ", ";
            }
        }
        builder << "]";
        return builder.str();
    }
};

#endif //ED1_LIST_CPP_ARRAYLIST_H