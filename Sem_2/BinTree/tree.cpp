#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>


using namespace std;

//структура дерева, состоящая из:
struct tree {
    int data; // данных
    tree* left; //левого элемента дерева
    tree* right; //правого элемента дерева
};

class BinaryTree {

public:
    tree* BinTree = nullptr;

    void createTree(int dt) {
        BinTree = new tree;
        BinTree->data = dt;
    }

    tree* insert(tree* root, int elem) {
        if (root == nullptr) {
            root = new tree;
            root->data = elem;
        }
        else if (elem < root->data) {

           root->left = insert(root->left, elem);
        }
        else {
           root->right = insert(root->right, elem);
        }
    return root;
    }

    //поиск элемента по ключу
    tree* searchElem(tree* root, int key) { //на входе текущее дерево и значение для поиска
        if (root == nullptr) { return nullptr; } //если значение в root пустое - вовзращаем нулпоинтер
        else if (root->data == key) { //иначе если значение = искомому значению
            return root; //вот наше дерево, мы его нашли
        } else if (key < root->data) { //иначе если искомое значение < значения в дереве
            return searchElem(root->left, key); //идем влево со значением и ищем там рекурсивно
        } else { return searchElem(root->right, key);} //иначе - идем право со значением и ищем там рекурсивно

    }

    //прямой обход дерева (от корня влево, затем право)
    void printPreOrdered(tree* cur) { //на вход - текущий элемент дерева
        cout << "Data = " << cur->data << endl;
        if (cur->left != nullptr) { //если текущий элемент слева не пустой
            printPreOrdered(cur->left); //рекурсивно обрабатываем левое поддерево (выводим, у нас же сверху cout)
        }
        if (cur->right != nullptr) { //затем если текущий элемент справа не пустой
            printPreOrdered(cur->right); //рекурсивно выводим правое поддерево
        }
    }

    //обратный обход дерева (лево, корень, право) - по смыслу все то же самое, что выше
    void printPostOrdered(tree* cur) {
        if (cur->left != nullptr) {
            printPostOrdered(cur->left);
        }
        if (cur->right != nullptr) {
            printPostOrdered(cur->right);
        }
        cout << "Data = " << cur->data << endl;
    }

    //симметричный обход дерева (лево, право, корень) - по смыслу все то же самое, что выше
    void printInOrdered(tree* cur) {
        if (cur->left != nullptr) {
            printInOrdered(cur->left);
        }
        cout << "Data = " << cur->data << endl;
        if (cur->right != nullptr) {
            printInOrdered(cur->right);
        }
    }

    /****************Вспомогательные функции для балансировки дерева****************/
    void sortingElem(tree* root, vector<int>& elements) { //функция сортровки элементов. На вход: дерево и ссылка на вектор элементов, которые надо отсортировать
        if (!root) {return;} // Если дерево пустое, вернуть его неизменным
        sortingElem(root->left, elements); //рекурсивно обходим левое поддерево
        elements.push_back(root->data); //добавляем в вектор элементов текущий элемент в поддереве
        sortingElem(root->right, elements); //то же самое, только справа
    }

    tree* createBalancedTree(const vector<int>& elements) { //функция создания сбалансированного дерева. На входе: вектор элементов
        if (elements.empty()) {return nullptr;} //если вектор пуст, вернуть нулпоинтер
        int mid = elements.size() / 2; //середина вектора
        tree* newNode = new tree[elements[mid]]; //создаем новое дерево состоящее из элементов середины вектора
        newNode->left = createBalancedTree(vector<int>(elements.begin(), elements.begin() + mid)); //рекурсивно создаем левое поддерево. На вход: первая половина отсортированных элементов в векторе.
        newNode->right = createBalancedTree(vector<int>(elements.begin() + mid + 1, elements.end())); //рекурсивно создаем правое поддерево. На вход: вторая половина отсортированных элементов в векторе.
        return newNode; //вернуть сбалансированное дерево
    }
    /*******************************************************************************/
    //балансировка дерева. На вход: дерево
    tree* balanceTree(tree* root) {
        if (!root) {return nullptr;} // Если дерево пустое, вернуть nullptr
        vector<int>elements; // создаем вектор элементов, которые мы сейчас отсортируем. Тут сейчас пусто
        sortingElem(root, elements); //функция для сортировки элементов: на входе дерево и вектор элементов.
        tree* newRoot = createBalancedTree(elements); //создаем переменную-вектор "новое дерево" из отсортированных элементов.
        return newRoot; //возвращаем новое дерево
    }

    /****************вспомогательная функция для удалительной функции, чтобы найти минимальный узел в поддереве. На вход: узел****************/
    tree* findMinNode(tree* node) {
        if (node->left == nullptr) {return node;} //если левое поддерево отсутствует - значит этот узел единственный минимальный - возвращаем минимальный узел
        else {return findMinNode(node->left);} //иначе рекурсивно ищем минимальный слева элемент
    }
    /*******************************************************************************/

    //удаление. На вход; дерево и значение для удаления
    tree* deleteElem(tree *root, int key) {
        if (root == nullptr) { return nullptr;} //проверка: если дерева нет, то возвращаем и ничего не делаем

        // ТУТ ИЩЕМ НУЖНЫЙ УЗЕЛ
        if (key < root->data) { root->left = deleteElem(root->left, key);} //если искомое значение меньше текущего, то ищем элемент в левом поддереве
        else if (key > root->data) {root->right = deleteElem(root->right, key);}  //иначе если искомое значение больше текущего, то ищем рекурсивно его в правом поддереве
        //иначе (то есть если искомое значение равно корню)
        else {
            if (root->left == nullptr) { //если левое значение отсутствует
                tree* temp = root->right; //создаем новую временную переменную-указатель на правое поддерево
                delete root; //удаляем корень
                return temp; //возвращаем правое поддерево
            }
            else if (root->right == nullptr) { //иначе если правая часть отсутствует
                tree* temp = root->left; //создаем новую временную переменную-указатель на левое поддерево
                delete root; //удаляем корень
                return temp; //возвращаем левое поддерево
            }
            tree* minNode = findMinNode(root->right); //новая переменная-указатель на минимальный узел в дереве справа (выше проверили другие варианты)
            root->data = minNode->data; //текущему узлу присваиваем новое минимальное значение
            root->right = deleteElem(root->right, minNode->data); //рекурсивно удаляем минимальный элемент из правого поддерева
        }
        return root;
    }


    /********************Вот тут то и начинается песня********************/

    //горизонтальная печать
    //на вход - текущее дерево, символ для вставки, флаг на "корень ли сейчас", флаг на "последний ли это элемент"
    void printHorizontal(const tree *root, const string& symbol = "", bool rootFlag = true, bool last = true) {
        //печатаем символ и дальше по условию
        //(rootFlag ? "" : (last ? "└─" : "├─")) - если это корневой символ, то печатаем пустоту, ИНАЧЕ проверяем является ли этот символ последним, и если ДА - то печатаем └─, ИНАЧЕ ├─
        //(root ? to_string(root->data) : "") - если у нас есть элемент (а не пустота), то переводим в строку текущее значение (и выводим), ИНАЧЕ пустой элемент
        cout << symbol << (rootFlag ? "" : (last ? "└─" : "├─")) << (root ? to_string(root->data) : "") << endl;
        if (!root) {return;} //если же у нас нет дерева - возвращаем его, ничего не делая.

        vector<tree*> v = {root->left, root->right}; //создаем вектор-указатель с типом заданной структуры tree и заполняем его поддеревом слева и поддеревом справа.

        //перебираем каждое дерево и печатаем
        //чтобы узнать размер дерева - используем size(), результат которого представляется в байтах
        //чтобы не было различий между инт и байтами, используем size_t (байтовый тип), начиная с начала и до конца размерности вектора v
        for (size_t i = 0; i < v.size(); i++) {
            //рекурсивно печатаем дерево:
            //v[i] - указатель на текущий элемент,
            //symbol символ в строке (у нас это "", а чтобы был какой-то смысловой элемент, мы складываем его (symbol) и элемент (+ "..."), поэтому...)
            // + (проверяем: если элемент корневой, то пробел "", (ИНАЧЕ проверяем: если он корневой и последний, то пробел, ИНАЧЕ │)),
            // rootFlag = false (у нас не корень, а листья),
            // i + 1 > v.size() - булевое значение для проверки продолжается ли дерево. То есть является ли текущий узел последним (или равно последнему).
            //как только стало являться последним - символ ветвлелния больше не печатается ("└─", "├─", "│ ").
            printHorizontal(v[i], symbol + (rootFlag ? "" : (last ? "   " : "│ ")), false, i + 1 >= v.size());
        }
    }

    //вертикальная печать
    //на вход текущее root и по умолчанию пустые правая, левая и центральная части печати
    void printVertical(const tree* root, const string& rightPart = " ", const string& centralPart = " ", const string& leftPart = " ") {
        if (!root) { return; } //если дерево пустое, то возвращаем, ничего не делая с ним
        if (root->right) {  //если право не пустое
            printVertical(root->right, rightPart + " ", rightPart + "┌─", rightPart + "│ "); //выводим отформатированную правую часть
        }
        cout << centralPart << root->data << endl; //сам корешок (буквально) вставляем тоже
        if (root->left) { //печатаем левую часть, если не пустая
            printVertical(root->left, leftPart + "│ ", leftPart + "└─", leftPart + " ");
        }
    }
};


