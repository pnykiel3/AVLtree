// AVLTree.h
#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
#include <queue>
#include <cassert>

// Struktura AVLNode przechowująca pojedynczą wartość i wskaźniki na dzieci oraz rodzica
template <typename T>
struct AVLNode {
    T value;
    int height;
    AVLNode *left, *right, *up;

    /**
     * @brief Domyślny konstruktor AVLNode.
     * Inicjalizuje wartość węzła jako domyślną dla typu T, a wysokość jako 1.
     */
    AVLNode() : value(T()), height(1), left(nullptr), right(nullptr), up(nullptr) {}

    /**
     * @brief Konstruktor inicjalizujący węzeł z podaną wartością.
     * @param item Wartość do przypisania nowemu węzłowi.
     */
    explicit AVLNode(const T& item) : value(item), height(1), left(nullptr), right(nullptr), up(nullptr) {}

    /**
     * @brief Destruktor AVLNode.
     * Usuwa rekurencyjnie lewe i prawe poddrzewo.
     */
    ~AVLNode() {
        delete left;
        delete right;
    }
};

// Template class dla AVLTree
template <typename T>
class AVLTree {
public:
    /**
     * @brief Konstruktor AVLTree.
     * Tworzy pustą strukturę drzewa AVL.
     */
    AVLTree() : root(nullptr) {}

    /**
     * @brief Destruktor AVLTree.
     * Usuwa całą strukturę drzewa AVL.
     */
    ~AVLTree() {
        root = nullptr;
    }

    /**
     * @brief Konstruktor kopiujący dla klasy AVLTree.
     *
     * Tworzy nową instancję drzewa AVL, będącą kopią innego drzewa AVL.
     *
     * @param other Obiekt AVLTree do skopiowania.
     */
    AVLTree(const AVLTree &other) {
        if (other.root == nullptr) {
            root = nullptr;
        } else {
            root = new AVLNode<T>(other.root->value);
            copyTree(root, other.root);
        }
    }

    /**
     * @brief Operator przypisania dla klasy AVLTree.
     * Kopiuje strukturę innego drzewa AVL do bieżącego obiektu.
     * @param other Obiekt AVLTree do skopiowania.
     * @return Referencja do bieżącego obiektu AVLTree.
     *
     * Funkcja tworzy kopię drzewa AVL "other" i przypisuje ją do aktualnego drzewa.
     * Sprawdza, czy bieżące drzewo i obiekt do skopiowania to różne instancje,
     * aby uniknąć zbędnego przepisywania danych.
     */
    AVLTree& operator=(const AVLTree& other) {
        if (this != &other) {
            // Usuń istniejące drzewo poprzez resetowanie
            while (root != nullptr) {
                remove(root->value);
            }

            // Skopiuj nowe drzewo
            if (other.root != nullptr) {
                root = new AVLNode<T>(other.root->value);
                copyTree(root, other.root);
            }
        }
        return *this;
    }

    /**
     @brief Czyści całe drzewo AVL, usuwając wszystkie węzły.
     */
    static void clear() {
        ~AVLTree();
    }

    /**
     * @brief Sprawdza, czy drzewo AVL jest puste.
     * @return true, jeśli drzewo jest puste; false w przeciwnym wypadku.
     */
    bool empty() const {
        return root == nullptr;
    }

    /**
     * @brief Zwraca wartość korzenia drzewa AVL.
     * @return Wartość znajdująca się w korzeniu drzewa AVL.
     */
    T& top() {
        assert(root != nullptr);
        return root->value;
    }

    /**
     * @brief Wstawia nową wartość do drzewa AVL.
     * @param value Wartość do dodania.
     * @return true, jeśli wstawienie się udało.
     */
bool insert(const T& value) {
    std::cout << "Wstawiono węzeł: " << value << std::endl;
    root = insert(root, value);
    display();
    return true;
    }

    /**
     * @brief Usuwa wartość z drzewa AVL.
     * @param value Wartość do usunięcia.
     * @return true, jeśli usunięcie się udało.
     */
bool remove(const T& value) {
    std::cout << "Usunięto węzeł: " << value << std::endl;
    root = remove(root, value);
    display();
    return true;
    }

    /**
     * @brief Znajduje najmniejszą wartość w drzewie AVL.
     * @return Najmniejsza wartość w drzewie AVL.
     */
    T find_min() const {
        assert(root != nullptr);
        return find_min(root)->value;
    }

    /**
     * @brief Znajduje największą wartość w drzewie AVL.
     * @return Największa wartość w drzewie AVL.
     */
    T find_max() const {
        assert(root != nullptr);
        return find_max(root)->value;
    }

    /**
     * @brief Wyszukuje wartość w drzewie AVL.
     * @param value Wartość do wyszukiwania.
     * @return true, jeśli wartość istnieje w drzewie AVL; w przeciwnym razie false.
     */
    bool search(const T& value) const {
        return search(root, value) != nullptr;
    }

    /**
     * @brief Wykonuje przejście preorder drzewa AVL i drukuje wartości.
     */
    void preorder() const {
        preorder(root);
        std::cout << std::endl;
    }

    /**
     * @brief Wykonuje przejście inorder drzewa AVL i drukuje wartości.
     */
    void inorder() const {
        inorder(root);
        std::cout << std::endl;
    }

    /**
     * @brief Wykonuje przejście postorder drzewa AVL i drukuje wartości.
     */
    void postorder() const {
        postorder(root);
        std::cout << std::endl;
    }

    /**
     * @brief Wykonuje przeszukiwanie drzewa AVL wszerz (BFS) i drukuje wartości.
     */
    void bfs() const {
        if (!root) return;
        std::queue<AVLNode<T>*> q;
        q.push(root);
        while (!q.empty()) {
            AVLNode<T>* current = q.front();
            q.pop();
            std::cout << current->value << " ";
            if (current->left) q.push(current->left);
            if (current->right) q.push(current->right);
        }
        std::cout << std::endl;
    }

    /**
* @brief Pobiera współczynnik równowagi dla węzła zawierającego podaną wartość w drzewie AVL.
*
* Współczynnik równowagi obliczany jest jako różnica wysokości lewego i prawego poddrzewa
* danego węzła. Pozytywny współczynnik oznacza, że lewe poddrzewo jest wyższe, negatywny
* współczynnik oznacza, że prawe poddrzewo jest wyższe, a współczynnik równy zero oznacza,
* że oba poddrzewa mają tę samą wysokość.
*
* @tparam T Typ danych przechowywanych w węzłach drzewa AVL.
* @param value Wartość, której węzeł ma zostać odnaleziony w drzewie AVL.
* @return Współczynnik równowagi dla węzła zawierającego podaną wartość.
* @throws std::runtime_error Jeśli wartość nie zostanie znaleziona w drzewie AVL.
*/
    int getBalanceFactor(const T& value) const {
        AVLNode<T>* node = search(root, value);
        if (!node) throw std::runtime_error("Wartość nie została znaleziona w drzewie AVL");
        return balanceFactor(node);
    }

    /**
 * @brief Sprawdza, czy drzewo AVL jest poprawne.
 *
 * Drzewo jest poprawne, jeśli spełnia poniższe warunki:
 * - Współczynnik wyważenia dla każdego węzła wynosi -1, 0 lub 1.
 * - Wszystkie poddrzewa są również poprawnymi drzewami AVL.
 *
 * @return true, jeśli drzewo AVL jest poprawne; false w przeciwnym razie.
 */
    bool isValid() const {
        return isValid(root);
    }

    void display() {
        display(root, 0);
        std::cout << std::endl;
        std::cout << std::endl;
    }

private:
    /**
     * Wskaźnik do korzenia drzewa AVL.
     */
    AVLNode<T>* root;

    /**
     * @brief Zwraca wysokość danego węzła w drzewie AVL.
     * @param node Wskaźnik do węzła, którego wysokość jest obliczana.
     * @return Wysokość węzła lub 0, jeśli węzeł jest pusty.
     */
    int height(AVLNode<T>* node) const {
        return node ? node->height : 0;
    }

    void display(AVLNode<T>* node, int level) {
        if (node == nullptr) return;
        display(node->right, level + 1);
        for (int i = 0; i < level; i++) {
            std::cout << "   |";
        }
        std::cout << "---" << node->value << std::endl;
        display(node->left, level + 1);
    }

    /**
     * @brief Oblicza współczynnik równowagi dla węzła w drzewie AVL.
     * @param node Wskaźnik do węzła, dla którego obliczany jest współczynnik równowagi.
     * @return Różnica wysokości lewego i prawego poddrzewa danego węzła.
     */
    int balanceFactor(AVLNode<T>* node) const {
        return node ? height(node->left) - height(node->right) : 0;
    }

    /**
     * @brief Aktualizuje wysokość danego węzła na podstawie jego poddrzew.
     * @param node Wskaźnik do węzła, którego wysokość jest aktualizowana.
     */
    void updateHeight(AVLNode<T>* node) const {
        if (node) {
            node->height = 1 + std::max(height(node->left), height(node->right));
        }
    }

    /**
     * @brief Wykonuje rotację w prawo na danym węźle.
     * @param y Wskaźnik do węzła, na którym wykonywana jest operacja rotacji.
     * @return Wskaźnik do nowego korzenia po rotacji.
     */
    AVLNode<T>* rotateRight(AVLNode<T>* y) {
        AVLNode<T>* x = y->left;
        AVLNode<T>* T2 = x->right;

        std::cout << "Rotacja w prawo węzła: " << y->value << std::endl;
        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);


        return x;
    }

    /**
     * @brief Wykonuje rotację w lewo na danym węźle.
     * @param x Wskaźnik do węzła, na którym wykonywana jest operacja rotacji.
     * @return Wskaźnik do nowego korzenia po rotacji.
     */
    AVLNode<T>* rotateLeft(AVLNode<T>* x) {

        AVLNode<T>* y = x->right;
        AVLNode<T>* T2 = y->left;

        std::cout << "Rotacja w lewo węzła: " << x->value << std::endl;

        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    /**
     * @brief Wykonuje operację wyważania (rebalansowania) danego węzła w drzewie AVL.
     * @param node Wskaźnik do węzła, który ma zostać zbalansowany.
     * @return Wskaźnik do potencjalnie nowego węzła po wyważeniu.
     */
    AVLNode<T>* rebalance(AVLNode<T>* node) {

        if (!node) return nullptr;
        updateHeight(node);
        int balance = balanceFactor(node);

        if (balance > 1 && balanceFactor(node->left) >= 0) {
            display();
            return rotateRight(node);
                }

        if (balance > 1 && balanceFactor(node->left) < 0) {
            display();
            node->left = rotateLeft(node->left);
            display();
            return rotateRight(node);
                }

        if (balance < -1 && balanceFactor(node->right) <= 0) {
            display();
            return rotateLeft(node);
                }

        if (balance < -1 && balanceFactor(node->right) > 0) {
            display();
            node->right = rotateRight(node->right);
            display();
            return rotateLeft(node);
                }


                return node;
        }

    /**
     * @brief Wstawia nową wartość do drzewa AVL.
     *
     * Metoda ta rekurencyjnie wstawia podaną wartość do drzewa AVL, zachowując
     * własność zrównoważenia drzewa. Wartość jest porównywana z bieżącymi
     * węzłami, aby znaleźć odpowiednie miejsce na jej wstawienie. W przypadku
     * naruszenia równowagi węzłów, wykonywane są operacje wyważania.
     *
     * @param node Wskaźnik do bieżącego węzła, od którego rozpoczyna się
     *             wyszukiwanie miejsca do wstawienia.
     * @param value Wartość do dodania do drzewa AVL.
     * @return Wskaźnik do potencjalnie nowego węzła po operacji wstawienia.
     */
    AVLNode<T>* insert(AVLNode<T>* node, const T& value) {
        if (!node) {
            return new AVLNode<T>(value);
        }

        if (value < node->value) {
            node->left = insert(node->left, value);
        } else if (value > node->value) {
            node->right = insert(node->right, value);
        } else {
            return node;
        }

        return rebalance(node);
    }

    /**
     * @brief Znajduje węzeł z minimalną wartością w poddrzewie rozpoczętym od danego węzła.
     *
     * Metoda rekurencyjnie schodzi w lewo, aby znaleźć węzeł o minimalnej wartości.
     *
     * @param node Wskaźnik do węzła początkowego.
     * @return Wskaźnik do węzła przechowującego najmniejszą wartość.
     */
    AVLNode<T>* minValueNode(AVLNode<T>* node) const {
        AVLNode<T>* current = node;
        while (current && current->left) {
            current = current->left;
        }
        return current;
    }
    /**
     * @brief Znajduje węzeł z maksymalną wartością w poddrzewie rozpoczętym od danego węzła.
     *
     * Metoda rekurencyjnie schodzi w prawo, aby znaleźć węzeł o maksymalnej wartości.
     *
     * @param node Wskaźnik do węzła początkowego.
     * @return Wskaźnik do węzła przechowującego największą wartość.
     */
    AVLNode<T>* maxValueNode(AVLNode<T>* node) const {
        AVLNode<T>* current = node;
        while (current && current->right) {
            current = current->right;
        }
        return current;
    }

    /**
     * @brief Usuwa węzeł z podaną wartością z drzewa AVL.
     *
     * Metoda usuwa węzeł zawierający podaną wartość, zachowując własność zrównoważenia drzewa AVL.
     *
     * @param node Wskaźnik do korzenia poddrzewa, w którym rozpoczęte jest usuwanie.
     * @param value Wartość do usunięcia.
     * @return Wskaźnik do potencjalnie nowego węzła po usunięciu.
     */
    AVLNode<T>* remove(AVLNode<T>* node, const T& value) {
        if (!node) {
            return node;
        }

        if (value < node->value) {
            node->left = remove(node->left, value);
        } else if (value > node->value) {
            node->right = remove(node->right, value);
        } else {
            if (!node->left || !node->right) {
                AVLNode<T>* temp = node->left ? node->left : node->right;

                if (!temp) {
                    temp = node;
                    node = nullptr;
                } else {
                    *node = *temp;
                }

                delete temp;
            } else {
                AVLNode<T>* temp = minValueNode(node->right);
                node->value = temp->value;
                node->right = remove(node->right, temp->value);
            }
        }



        if (!node) {
            return node;
        }

        return rebalance(node);
    }

    /**
     * @brief Znajduje węzeł z minimalną wartością w poddrzewie.
     *
     * Metoda korzysta z funkcji pomocniczej minValueNode w celu określenia węzła
     * przechowującego najmniejszą wartość w danym poddrzewie.
     *
     * @param node Wskaźnik do poddrzewa, w którym zaczyna się poszukiwanie.
     * @return Wskaźnik do węzła z minimalną wartością.
     */
    AVLNode<T>* find_min(AVLNode<T>* node) const {
            return minValueNode(node);
        }

    /**
     * @brief Znajduje węzeł z maksymalną wartością w poddrzewie.
     *
     * Metoda korzysta z funkcji pomocniczej maxValueNode w celu określenia węzła
     * przechowującego największą wartość w danym poddrzewie.
     *
     * @param node Wskaźnik do poddrzewa, w którym zaczyna się poszukiwanie.
     * @return Wskaźnik do węzła z maksymalną wartością.
     */
    AVLNode<T>* find_max(AVLNode<T>* node) const {
            return maxValueNode(node);
    }

    /**
     * @brief Wyszukuje węzeł z podaną wartością w drzewie AVL.
     *
     * Metoda rekurencyjna, która porównuje wartość w bieżącym węźle z wartościami w poddrzewach,
     * dopóki nie znajdzie danego węzła lub napotka pusty wskaźnik.
     *
     * @param node Wskaźnik do bieżącego węzła w czasie przeszukiwania.
     * @param value Wartość wyszukiwana.
     * @return Wskaźnik do węzła zawierającego podaną wartość; nullptr, jeśli nie znaleziono.
     */
    AVLNode<T>* search(AVLNode<T>* node, const T& value) const {
            if (!node || node->value == value) {
                return node;
            }
            if (value < node->value) {
                return search(node->left, value);
            }
            return search(node->right, value);
    }

   /**
    * @brief Wykonuje przejście preorder po drzewie AVL i drukuje wartości węzłów.
    *
    * W kolejności preorder najpierw przetwarzany jest korzeń, potem lewe poddrzewo,
    * a na końcu prawe poddrzewo.
    */
    void preorder(AVLNode<T>* node) const {
        if (node) {
            std::cout << node->value << " ";
            preorder(node->left);
            preorder(node->right);
        }
    }

   /**
    * @brief Wykonuje przejście inorder po drzewie AVL i drukuje wartości węzłów.
    *
    * W kolejności inorder najpierw przetwarzane jest lewe poddrzewo, potem korzeń,
    * a na końcu prawe poddrzewo.
    */
    void inorder(AVLNode<T>* node) const {
        if (node) {
            inorder(node->left);
            std::cout << node->value << " ";
            inorder(node->right);
        }
    }

   /**
    * @brief Wykonuje przejście postorder po drzewie AVL i drukuje wartości węzłów.
    *
    * W kolejności postorder najpierw przetwarzane jest lewe poddrzewo, potem prawe
    * poddrzewo, a na końcu korzeń.
    */
    void postorder(AVLNode<T>* node) const {
        if (node) {
            postorder(node->left);
            postorder(node->right);
            std::cout << node->value << " ";
        }
    }

    /**
    @brief Sprawdza, czy drzewo AVL jest poprawne.

    Metoda rekurencyjnie sprawdza, czy dane drzewo AVL spełnia zasady poprawności, tj.:
    1. Współczynnik wyważenia każdego węzła mieści się w zakresie [-1, 1].
    2. Lewa i prawa część poddrzewa również są poprawnymi drzewami AVL.

    @param node Wskaźnik na węzeł drzewa, który ma zostać sprawdzony.
    @return true, jeśli drzewo jest poprawne; false w przeciwnym razie.
    */
    bool isValid(AVLNode<T>* node) const {

        if (!node) return true; // Puste poddrzewo jest zawsze poprawne

        // Oblicz współczynnik wyważenia
        int balance = balanceFactor(node);

        // Jeśli współczynnik wyważenia jest poza zakresem [-1, 1], drzewo jest niepoprawne
        if (balance < -1 || balance > 1) {
            return false;
        }

        // Rekurencyjnie sprawdzaj poprawność lewego i prawego poddrzewa
        return isValid(node->left) && isValid(node->right);
    }

    /**
     * @brief Kopiuje poddrzewo drzewa AVL.
     *
     * Funkcja rekurencyjnie kopiuje węzły drzewa.
     * @param dest Wskaźnik na węzeł docelowy.
     * @param src Wskaźnik na węzeł źródłowy.
     */
    void copyTree(AVLNode<T>*& dest, AVLNode<T>* src) {
        if (src->left) {
            dest->left = new AVLNode<T>(src->left->value);
            copyTree(dest->left, src->left);
        }
        if (src->right) {
            dest->right = new AVLNode<T>(src->right->value);
            copyTree(dest->right, src->right);
        }
        dest->height = src->height;
    }

};

#endif // AVLTREE_H