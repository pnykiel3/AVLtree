#include "AVLtree.h"
#include <cassert>
#include <iostream>


void test1(bool debug) {
    std::cout << "\033[33m====================  TEST 1 ====================\033[0m" << std::endl;
    AVLTree<int> tree;

    // Test wstawiania i balansowania (wszystkie przypadki rotacji)
    tree.insert(30, debug);
    tree.insert(20, debug);
    tree.insert(10, debug); // Test LL
    assert(tree.search(30) && tree.search(20) && tree.search(10));
    assert(tree.isValid());

    tree.insert(40, debug);
    tree.insert(50, debug); // Test RR
    assert(tree.search(40) && tree.search(50));
    assert(tree.isValid());

    tree.insert(35, debug); // Test RL
    assert(tree.search(35));
    assert(tree.isValid());

    tree.insert(25, debug); // Test LR
    assert(tree.search(25));
    assert(tree.isValid());

    // Test usuwania i balansowania
    tree.remove(50, debug);
    assert(!tree.search(50));
    assert(tree.isValid());

    tree.remove(30, debug);
    assert(!tree.search(30));
    assert(tree.isValid());

    tree.remove(10, debug);
    assert(!tree.search(10));
    assert(tree.isValid());

    // Test znajdowania wartości minimalnej i maksymalnej
    assert(tree.find_min() == 20);
    assert(tree.find_max() == 40);

    // Test konstrukcji kopiującej
    AVLTree<int> copiedTree = tree;
    assert(copiedTree.search(20) && copiedTree.search(40) && copiedTree.search(25));
    assert(copiedTree.isValid());

    // Test operatora przypisania
    AVLTree<int> assignedTree;
    assignedTree = tree;
    assert(assignedTree.search(20) && assignedTree.search(40) && assignedTree.search(25));
    assert(assignedTree.isValid());

    // Test wstawiania do skopiowanego drzewa
    copiedTree.insert(60, debug);
    assert(copiedTree.search(60) && !tree.search(60));
    assert(copiedTree.isValid());

    // Test usuwania w skopiowanym drzewie
    copiedTree.remove(20, debug);
    assert(!copiedTree.search(20) && tree.search(20));
    assert(copiedTree.isValid());

    // Test w dużym drzewie
    AVLTree<int> largeTree;
    for (int i = 1; i <= 100; ++i) {
        largeTree.insert(i, debug);
    }
    assert(largeTree.isValid());
    for (int i = 1; i <= 100; ++i) {
        assert(largeTree.search(i));
    }
    for (int i = 1; i <= 100; i += 2) {
        largeTree.remove(i, debug);
    }
    assert(largeTree.isValid());
    for (int i = 1; i <= 100; ++i) {
        if (i % 2 == 0) {
            assert(largeTree.search(i));
        } else {
            assert(!largeTree.search(i));
        }
    }

    // Test balansowania w dużym drzewie
    for (int i = 101; i <= 200; ++i) {
        largeTree.insert(i, debug);
    }
    assert(largeTree.find_min() == 2);
    assert(largeTree.find_max() == 200);
    assert(largeTree.isValid());
}


void test2(bool debug) {
    std::cout << "\033[33m====================  TEST 2 ====================\033[0m" << std::endl;
    AVLTree<int> tree;

    // Test LL
    tree.insert(30, debug);
    tree.insert(20, debug);
    tree.insert(10, debug);
    assert(tree.isValid());

    // Test RR
    tree.insert(40, debug);
    tree.insert(50, debug);
    assert(tree.isValid());

    // Test LR
    tree.insert(25, debug);
    assert(tree.isValid());

    // Test RL
    tree.insert(45, debug);
    tree.insert(35, debug);
    assert(tree.isValid());
}

void test3(bool debug) {
    std::cout << "\033[33m====================  TEST 3 ====================\033[0m" << std::endl;
    AVLTree<int> tree;

    tree.insert(10, debug);
    tree.insert(20, debug);
    tree.insert(5, debug);

    assert(tree.find_min() == 5);
    assert(tree.find_max() == 20);
}

void test4(bool debug) {
    std::cout << "\033[33m====================  TEST 4 ====================\033[0m" << std::endl;
    AVLTree<int> tree;
    for (int i = 1; i <= 15; ++i) {
        tree.insert(i, debug);
    }

    assert(tree.countNodes() == 15);
    assert(tree.getHeight() == 4);

    tree.clear();
    assert(tree.empty());

    tree.insert(10, debug);
    tree.insert(20, debug);
    tree.insert(5, debug);

    int balance = tree.getBalanceFactor(10);
    assert(balance == 0);
}

void test5(bool debug) {
    std::cout << "\033[33m====================  TEST 5 ====================\033[0m" << std::endl;
    //Edge Cases
    AVLTree<int> tree;

    // Test na pustym drzewie
    try {
        tree.find_min();
        assert(false); // Powinno rzucić wyjątek
    } catch (const std::runtime_error&) {
        // Oczekiwany wyjątek
    }

    try {
        tree.find_max();
        assert(false); // Powinno rzucić wyjątek
    } catch (const std::runtime_error&) {
        // Oczekiwany wyjątek
    }

    try {
        tree.remove(10, debug);
        assert(false); // Powinno rzucić wyjątek
    } catch (const std::runtime_error&) {
        // Oczekiwany wyjątek
    }

    tree.insert(15, debug);
    assert(tree.find_min() == 15);
    assert(tree.find_max() == 15);
    tree.remove(15, debug);
    assert(tree.isValid());
}

void test6(bool debug) {
    std::cout << "\033[33m====================  TEST 6 ====================\033[0m" << std::endl;
    AVLTree<int> tree1;
    tree1.insert(10, debug);
    tree1.insert(20, debug);
    tree1.insert(5, debug);

    // Test copy constructor
    AVLTree<int> tree2(tree1);
    assert(tree2.find_min() == 5);
    assert(tree2.find_max() == 20);

    // Test = operator
    AVLTree<int> tree3;
    tree3 = tree1;
    assert(tree3.find_min() == 5);
    assert(tree3.find_max() == 20);
}

void test7(bool debug) {
    std::cout << "\033[33m====================  TEST 7 ====================\033[0m" << std::endl;
    AVLTree<int> tree;

    tree.insert(20, debug);
    tree.insert(10, debug);
    tree.insert(30, debug);
    tree.insert(25, debug);
    tree.insert(35, debug);

    // remove zwykły
    tree.remove(10, debug);
    assert(tree.isValid());

    // Test LL remove
    tree.remove(35, debug);
    assert(tree.isValid());

    // Test RR remove
    tree.remove(25, debug);
    assert(tree.isValid());

    // Test RL remove
    tree.insert(40, debug);
    tree.insert(45, debug);
    tree.remove(20, debug);
    assert(tree.isValid());

    // Test LR remove
    tree.insert(15, debug);
    tree.insert(17, debug);
    tree.remove(30, debug);
    assert(tree.isValid());
}

int main() {

    std::cout << "Czy chcesz zobaczyć wizualizację zmian następujących podczas wykonywania działań na drzewie AVL?: " << std::endl;
    std::string c;
    while (c != "y" && c != "Y" && c != "n" && c != "N") {
        std::cout << "[y/n]" << std::endl;
        std::cin >> c;
    }
    bool debug = (c == "y" || c == "Y");
    test1(debug);
    test2(debug);
    test3(debug);
    test4(debug);
    test5(debug);
    test6(debug);
    test7(debug);

    std::cout << "\033[32mWszystkie testy zostały zaliczone!\033[0m" << std::endl;
    return 0;
}
