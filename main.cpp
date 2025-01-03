#include "AVLtree.h"
#include <cassert>
#include <iostream>

void testInsertAndBalance() {
    AVLTree<int> tree;

    // Test LL rotation
    tree.insert(30);
    tree.insert(20);
    tree.insert(10); // Should trigger LL rotation
    assert(tree.isValid());

    // Test RR rotation
    tree.insert(40);
    tree.insert(50); // Should trigger RR rotation
    assert(tree.isValid());

    // Test LR rotation
    tree.insert(25); // Should trigger LR rotation
    assert(tree.isValid());

    // Test RL rotation
    tree.insert(45);
    tree.insert(35); // Should trigger RL rotation
    assert(tree.isValid());
}

void testRemoveAndBalance() {
    AVLTree<int> tree;

    tree.insert(20);
    tree.insert(10);
    tree.insert(30);
    tree.insert(25);
    tree.insert(35);

    // Test remove with no imbalance
    tree.remove(10);
    assert(tree.isValid());

    // Test remove causing LL rotation
    tree.remove(35);
    assert(tree.isValid());

    // Test remove causing RR rotation
    tree.remove(25);
    assert(tree.isValid());

    // Test remove causing RL rotation
    tree.insert(40);
    tree.insert(45);
    tree.remove(20);
    assert(tree.isValid());

    // Test remove causing LR rotation
    tree.insert(15);
    tree.insert(17);
    tree.remove(30);
    assert(tree.isValid());
}

void testFindMinMax() {
    AVLTree<int> tree;

    tree.insert(10);
    tree.insert(20);
    tree.insert(5);

    assert(tree.find_min() == 5);
    assert(tree.find_max() == 20);
}

void testCloneAndAssignment() {
    AVLTree<int> tree1;
    tree1.insert(10);
    tree1.insert(20);
    tree1.insert(5);

    // Test copy constructor
    AVLTree<int> tree2(tree1);
    assert(tree2.find_min() == 5);
    assert(tree2.find_max() == 20);

    // Test assignment operator
    AVLTree<int> tree3;
    tree3 = tree1;
    assert(tree3.find_min() == 5);
    assert(tree3.find_max() == 20);
}

int main() {
    testInsertAndBalance();
    testRemoveAndBalance();
    testFindMinMax();
    testCloneAndAssignment();

    std::cout << "All tests passed successfully!" << std::endl;
    return 0;
}
