#include "LinkedList.h"
#include <iostream>
#include <cassert>
#include <string>

void printTestHeader(const std::string& testName) {
    std::cout << "========================================" << std::endl;
    std::cout << "Running: " << testName << std::endl;
}

void testInsertion() {
    printTestHeader("testInsertion");
    LinkedList<int> list;

    list.addFirst(10);
    assert(list.size() == 1);
    assert(list.toString() == "[10]");
    std::cout << "After addFirst(10): " << list.toString() << std::endl;

    list.addLast(30);
    assert(list.size() == 2);
    assert(list.toString() == "[10, 30]");
    std::cout << "After addLast(30): " << list.toString() << std::endl;

    list.insertAt(1, 20);
    assert(list.size() == 3);
    assert(list.toString() == "[10, 20, 30]");
    std::cout << "After insertAt(1, 20): " << list.toString() << std::endl;

    list.addSorted(25);
    assert(list.size() == 4);
    assert(list.toString() == "[10, 20, 25, 30]");
    std::cout << "After addSorted(25): " << list.toString() << std::endl;

    std::cout << "-> testInsertion PASSED\n\n";
}

void testRemoval() {
    printTestHeader("testRemoval");
    LinkedList<int> list;
    list.addLast(10); list.addLast(20); list.addLast(30);
    list.addLast(40); list.addLast(50);

    list.removeFirst();
    assert(list.size() == 4);
    assert(list.toString() == "[20, 30, 40, 50]");
    std::cout << "After removeFirst(): " << list.toString() << std::endl;

    list.removeLast();
    assert(list.size() == 3);
    assert(list.toString() == "[20, 30, 40]");
    std::cout << "After removeLast(): " << list.toString() << std::endl;

    list.removeAt(1);
    assert(list.size() == 2);
    assert(list.toString() == "[20, 40]");
    std::cout << "After removeAt(1): " << list.toString() << std::endl;

    list.clear();
    assert(list.size() == 0);
    assert(list.toString() == "[]");
    std::cout << "After clear(): " << list.toString() << std::endl;

    std::cout << "-> testRemoval PASSED\n\n";
}

void testQueryAndManagement() {
    printTestHeader("testQueryAndManagement");
    LinkedList<std::string> list;

    list.addLast("Apple");
    list.addLast("Banana");
    list.addLast("Cherry");

    assert(list.find("Banana") == 1);
    assert(list.find("Mango") == -1);
    std::cout << "find(\"Banana\") == 1" << std::endl;

    assert(list.get(2) == "Cherry");
    std::cout << "get(2) == \"Cherry\"" << std::endl;

    list.set(1, "Blueberry");
    assert(list.get(1) == "Blueberry");
    assert(list.toString() == "[Apple, Blueberry, Cherry]");
    std::cout << "After set(1, \"Blueberry\"): " << list.toString() << std::endl;

    std::cout << "-> testQueryAndManagement PASSED\n\n";
}

int main() {
    std::cout << "Starting LinkedList Test Suite...\n\n";

    testInsertion();
    testRemoval();
    testQueryAndManagement();

    std::cout << "========================================" << std::endl;
    std::cout << "ALL TESTS PASSED SUCCESSFULLY!" << std::endl;

    return 0;
}