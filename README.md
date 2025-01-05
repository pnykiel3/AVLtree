# **Drzewa AVL**

### **Autor**
Paweł Nykiel

---

## **1. Wstęp**
Projekt realizowany jako zadanie zaliczeniowe z przedmiotu **Algorytmy i Struktury Danych I**. Celem jest implementacja drzewa AVL — zbalansowanego drzewa binarnego poszukiwań, które gwarantuje logarytmiczną wysokość nawet przy wielokrotnych operacjach wstawiania i usuwania.

Drzewa AVL znajdują szerokie zastosowanie tam, gdzie kluczowe jest szybkie wyszukiwanie, np. w bazach danych czy strukturach indeksów.

---

## **2. Właściwości drzewa AVL**
Drzewa AVL spełniają następujące zasady:
1. Wysokość lewego i prawego poddrzewa dowolnego węzła różni się maksymalnie o 1.
2. Każdy węzeł przechowuje informację o wysokości swoich poddrzew, co umożliwia szybkie balansowanie.

---

## **3. Kluczowe operacje drzewa**
Program implementuje następujące funkcje:

1. **Wstawianie elementów** z automatycznym balansowaniem.
2. **Usuwanie elementów** przy zachowaniu własności AVL.
3. **Wyszukiwanie elementów** w drzewie.
4. **Znajdowanie wartości minimalnej i maksymalnej**.
5. **Przeglądanie drzewa** w różnych porządkach (inorder, preorder, postorder).
6. **Walidacja drzewa** sprawdzająca jego poprawność.
7. **Wizualizacja drzewa** w terminalu za pomocą ASCII ART.
8. **Obliczanie wysokości** drzewa i liczby węzłów.
9. **Przeszukiwanie wszerz (BFS)**.
10. **Obliczanie współczynnika równowagi** dla wybranego węzła.
11. **Czyszczenie drzewa** — usuwanie wszystkich węzłów.

---

## **4. Struktura programu**

Program składa się z dwóch głównych klas:
- **`AVLNode<T>`**: Reprezentuje pojedynczy węzeł drzewa, zawiera wartość, wysokość oraz wskaźniki na dzieci i rodzica.
- **`AVLTree<T>`**: Zarządza strukturą drzewa, implementuje operacje takie jak wstawianie, usuwanie i balansowanie.

---

## **5. Kluczowe operacje w kodzie**
### **Wstawianie i usuwanie elementów**
Podczas wstawiania lub usuwania elementu automatycznie przywracana jest równowaga drzewa AVL:

#### **Obliczanie współczynnika równowagi:**
```cpp
int balanceFactor(AVLNode<T>* node) const {
    return node ? height(node->left) - height(node->right) : 0;
}
```

#### **Rotacja w lewo:**
(Analogicznie wygląda rotacja w prawo)
```cpp
AVLNode<T>* rotateLeft(AVLNode<T>* x) {
    AVLNode<T>* y = x->right;
    AVLNode<T>* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
}
```

#### **Przywracanie równowagi drzewa:**
```cpp
AVLNode<T>* rebalance(AVLNode<T>* node) {
    if (!node) return nullptr;

    updateHeight(node);
    int balance = balanceFactor(node);

    if (balance > 1 && balanceFactor(node->left) >= 0) {
        return rotateRight(node);
    }

    if (balance > 1 && balanceFactor(node->left) < 0) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    if (balance < -1 && balanceFactor(node->right) <= 0) {
        return rotateLeft(node);
    }

    if (balance < -1 && balanceFactor(node->right) > 0) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}
```

---

## **6. Złożoność algorytmów**

### **Złożoność czasowa:**
- **Wstawianie, usuwanie, wyszukiwanie:** można wykonać z pesymistyczną złożonością czasową O(log n).

### **Złożoność pamięciowa:**
- Drzewo AVL wymaga O(n) dodatkowej pamięci na swoje atrybuty.

---

## **7. Instrukcja uruchomienia**
### Kompilacja i uruchomienie:
1. Aby skompilować projekt:
   ```bash
   make
   ```

2. Aby uruchomić program testowy:
   ```bash
   make run
   ```

3. Aby wyczyścić pliki:
   ```bash
   make clean
   ```

4. Aby spakować pliki projektu:
   ```bash
   make tar
   ```

---

## **8. Literatura**
Strona prof. Kapanowskiego: [ufkapano.github.io](https://ufkapano.github.io/) <br>
oraz:
- [AVL Tree Wikipedia](https://en.wikipedia.org/wiki/AVL_tree)
- [Binary Search Tree Wikipedia](https://en.wikipedia.org/wiki/Binary_search_tree)
- [Eduinf — Drzewa AVL](https://eduinf.waw.pl/inf/alg/001_search/0119.php)
