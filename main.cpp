#include "AVLtree.h"
#include <cassert>
#include <iostream>


void test1() {
    AVLTree<int> tree;

    // Test wstawiania i balansowania (wszystkie przypadki rotacji)
    tree.insert(30);
    tree.insert(20);
    tree.insert(10); // Test LL
    assert(tree.search(30) && tree.search(20) && tree.search(10));
    assert(tree.isValid());

    tree.insert(40);
    tree.insert(50); // Test RR
    assert(tree.search(40) && tree.search(50));
    assert(tree.isValid());

    tree.insert(35); // Test RL
    assert(tree.search(35));
    assert(tree.isValid());

    tree.insert(25); // Test LR
    assert(tree.search(25));
    assert(tree.isValid());

    // Test usuwania i balansowania
    tree.remove(50);
    assert(!tree.search(50));
    assert(tree.isValid());

    tree.remove(30);
    assert(!tree.search(30));
    assert(tree.isValid());

    tree.remove(10);
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
    copiedTree.insert(60);
    assert(copiedTree.search(60) && !tree.search(60));
    assert(copiedTree.isValid());

    // Test usuwania w skopiowanym drzewie
    copiedTree.remove(20);
    assert(!copiedTree.search(20) && tree.search(20));
    assert(copiedTree.isValid());

    // Test w dużym drzewie
    AVLTree<int> largeTree;
    for (int i = 1; i <= 100; ++i) {
        largeTree.insert(i);
    }
    assert(largeTree.isValid());
    for (int i = 1; i <= 100; ++i) {
        assert(largeTree.search(i));
    }
    for (int i = 1; i <= 100; i += 2) {
        largeTree.remove(i);
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
        largeTree.insert(i);
    }
    assert(largeTree.find_min() == 2);
    assert(largeTree.find_max() == 200);
    assert(largeTree.isValid());
}


void test2() {
    AVLTree<int> tree;

    // Test LL
    tree.insert(30);
    tree.insert(20);
    tree.insert(10);
    assert(tree.isValid());

    // Test RR
    tree.insert(40);
    tree.insert(50);
    assert(tree.isValid());

    // Test LR
    tree.insert(25);
    assert(tree.isValid());

    // Test RL
    tree.insert(45);
    tree.insert(35);
    assert(tree.isValid());
}

void test3() {
    AVLTree<int> tree;

    tree.insert(20);
    tree.insert(10);
    tree.insert(30);
    tree.insert(25);
    tree.insert(35);

    // remove zwykły
    tree.remove(10);
    assert(tree.isValid());

    // Test LL remove
    tree.remove(35);
    assert(tree.isValid());

    // Test RR remove
    tree.remove(25);
    assert(tree.isValid());

    // Test RL remove
    tree.insert(40);
    tree.insert(45);
    tree.remove(20);
    assert(tree.isValid());

    // Test LR remove
    tree.insert(15);
    tree.insert(17);
    tree.remove(30);
    assert(tree.isValid());
}

void test4() {
    AVLTree<int> tree;

    tree.insert(10);
    tree.insert(20);
    tree.insert(5);

    assert(tree.find_min() == 5);
    assert(tree.find_max() == 20);
}

void test5() {
    AVLTree<int> tree1;
    tree1.insert(10);
    tree1.insert(20);
    tree1.insert(5);

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

void test6() {
    AVLTree<int> tree;
    for (int i = 1; i <= 15; ++i) {
        tree.insert(i);
    }

    assert(tree.countNodes() == 15);
    assert(tree.getHeight() == 4);

    tree.clear();
    assert(tree.empty());

    tree.insert(10);
    tree.insert(20);
    tree.insert(5);

    int balance = tree.getBalanceFactor(10);
    assert(balance == 0);

}
int main() {
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();

    std::cout << "Wszystkie testy zostały zaliczone!" << std::endl;
    return 0;
}
