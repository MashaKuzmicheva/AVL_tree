#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
using namespace std;
int bal = 0;



    //template <class T>
template<class T, class V>
class Tree
{
private:
    struct TreeNode
    {
        T key;
        V value;
        TreeNode* left, * right, * parent;
        TreeNode() { left = right = parent = nullptr; }
        int balance; //разность между двумя длинами поддеревьев
    };

   
    //void DeleteAll(TreeNode* p); // для деструктора
TreeNode* root; //private

public: 
    
    class P_Iterator // итератор с использованием parent
    {
        Tree* tree;
        TreeNode* pos;
    public:
        P_Iterator(Tree* t = 0, TreeNode* p = 0) : tree(t), pos(p) {}
        P_Iterator(const P_Iterator& i) { tree = i.tree; pos = i.pos; }
        const P_Iterator& operator=(const P_Iterator& i) { tree = i.tree; pos = i.pos; return *this; }
        bool operator!=(const P_Iterator& i) { return pos != i.pos || tree != i.tree; }
        T& operator*() { return  pos->key; } //V value
        const P_Iterator& operator++();
    };

    P_Iterator pbegin() { return P_Iterator(this, root); }
    P_Iterator pend() { return P_Iterator(this, nullptr); }

    Tree() : root(nullptr) {} // пустое дерево
   
    void Print(FILE* f = stdout) const;
    void PrintRecursive(const TreeNode* r) const;
    void CreateSampleTree();
    TreeNode* create(T d, V y);
    void Add(TreeNode* A, const T& x, const V& y);
    TreeNode* getNode(TreeNode* A);
    int getBalance(TreeNode* A);  
    int getHeight(TreeNode* A);
    void rightRotate(TreeNode* y);
    void leftRotate(TreeNode* x);
    void balace(TreeNode* p, T key);
    void balace1(TreeNode* p, T key);
    //void insert(int key);
    void insert(T key, V value);
    void pop(T key);
    void searchKey(TreeNode*& curr, int key, TreeNode*& parent);
    TreeNode* getMinimumKey(TreeNode* curr);
    TreeNode* Search(T& x, V& y);
   int Height();
   V SearchValue(T& x);
   //T SearchKey(V& y);
    //void Height(int& l); 
   
   void DeleteAll(TreeNode*& tr)
    {
        if (tr != nullptr)
        {
            DeleteAll(tr->left);
            DeleteAll(tr->right);
            delete tr;
            tr = nullptr;
        }
    }

    ~Tree()
    {
        DeleteAll(root);
        if (root == nullptr)
        {
            cout << "!\n";
        }
    }

};


template<class T, class V>
typename Tree<T, V>::TreeNode* Tree<T, V>::Search(T& x, V& y)
{
    TreeNode* q = root;
    if (root == nullptr) return nullptr;
    TreeNode* p = root;
    while (p) {
        if (x == p->key && y == p->value) return p;
        p = (x > p->key) ? p->right : p->left;
    }
    return nullptr;
}

template<class T, class V>
V Tree<T, V>::SearchValue(T& x)
{
    TreeNode* q = root;
    if (root == nullptr) return -1;
    TreeNode* p = root;
    while (p) {
        if (x == p->key) return p->value;
        p = (x > p->key) ? p->right : p->left;
    }
    return -1;
}
/*
template<class T, class V>
T Tree<T, V>::SearchKey(V& y)
{
    TreeNode* q = root;
    if (root == nullptr) return -1;
    TreeNode* p = root;
    while (p) {
        if (y == p->value) return p->value;
        p = (y > p->value) ? p->right : p->left;
    }
    return -1;
}*/


template<class T, class V>
void Tree<T, V>::PrintRecursive( const typename Tree<T, V>::TreeNode* r) const
{
    if (!r) return;
    printf( " %d %d\n", r->key, r->value);
    PrintRecursive( r->left);
    PrintRecursive(r->right);
}

template<class T, class V>
void Tree<T, V>::Print(FILE* f) const
{
    fprintf(f, "Walking and printing the tree:\n");
    if (!root) {
        fprintf(f, "empty\n");
        return;
    }
    Tree<T, V>::PrintRecursive(f, root);
}

template<class T, class V>
const typename Tree<T, V>::P_Iterator& Tree<T, V>::P_Iterator::operator++()
{
    TreeNode* q;
    if (pos == 0) return *this;
    if (pos->left) { pos = pos->left; return *this; }
    if (pos->right) { pos = pos->right; return *this; }
    for (q = pos->parent; q; pos = q, q = q->parent) {
        if (q->right && q->right != pos) {
            pos = q->right;
            return *this;
        }
    }
    pos = nullptr;
    return *this;
}

template<class T, class V>
typename Tree<T, V>::TreeNode* Tree<T, V>::create(T d, V v) //int -> T
{
    TreeNode* p = new TreeNode();
    
    p->key = d;
    p->value = v;
    p->left = p->right = p->parent = NULL;
    return p;
}

// Просто добавляем в дерево
template<class T, class V>
void typename Tree<T, V>:: Add(typename Tree<T, V>::TreeNode* p, const T& d, const V& str)
{
        //struct 
        TreeNode* q = root, * r = 0;
        if (root == NULL)
        {
            
            root= p;
           // printf("\nRoot Node:%s is added", d);
        }
        else
        {
            while (q)
            {
                r = q;
                
                if (d >= q->key)
                    q = q->right;
                else
                    q = q->left;
            }
            if (d >= r->key)
            {
               // printf("\n\nNode:%s is added to right of %s", d, r->key);
               // r->value = str;
                r->right = p;
                p->parent = r;
            }
            else
            {
                //printf("\n\nNode:%s is added to left of %s", d, r->key);
              //  r->value = str;
                r->left = p;
                p->parent = r;
            }
        }
}

template<class T, class V>
typename Tree<T, V>::TreeNode* Tree<T,V>::getNode(typename Tree<T, V>::TreeNode* p)
{
    while (p)
    {
        bal = getBalance(p);
       // printf("\n\tBalance factor of %d node is %d", p->key, bal);
        if (bal > 1 || bal < -1)
        {
            return p;
        }
        else
            p = p->parent;
    }
    return p;
}

// Баланс
template<class T, class V>
int Tree<T, V>:: getBalance(TreeNode* p)
{
    return getHeight(p->left) - getHeight(p->right);
}

template<class T, class V>
int Tree<T, V>::getHeight(TreeNode* p)
{
    int i, j;
    if (!p)
        return 0;
    else
    {
        i = getHeight(p->left);
        j = getHeight(p->right);
        if (i > j)
            return i + 1;
        else
            return j + 1;
    }
}

template<class T, class V>
int Tree<T, V>::Height()
{
    TreeNode* p;
    return getHeight(root);
}

//Right rotation
template<class T, class V>
void Tree<T, V>::rightRotate(TreeNode* y)
{
    TreeNode* x = y->left, * Temp;

    Temp = x->right;
    if (y == root)
        root = x;
    else
    {
        if (y->parent->left == y)
            y->parent->left = x;
        else
            y->parent->right = x;
    }

    // Perform rotation
    x->parent = y->parent;
    y->parent = x;
    x->right = y;
    y->left = Temp;
    if (Temp != NULL)
        //Temp->parent = x;
    {
        Temp->parent = y;
    }
}

// Left Rotation
template<class T, class V>
void Tree<T, V>::leftRotate(TreeNode* x)
{
    TreeNode* y = x->right, * temp;

    temp = y->left;
    // Perform rotation
    if (x == root)
    {
        root = y;
    }
    else
    {
        if (x->parent->left == x)
            x->parent->left = y;
        else
            x->parent->right = y;
    }
    y->parent = x->parent;
    x->parent = y;
    y->left = x;
    x->right = temp;
    if (temp != NULL)
        temp->parent = x;
    //else
       // return;
}

template<class T, class V>
void Tree<T, V>::balace(TreeNode* p, T x) //int->T
{
    //right rotate
    if (bal > 1 && x < p->left->key)
    {
       // printf("\n\tRight rotation get performed on unbalanced node %d", p->key);
       // cout << endl;
        rightRotate(p);
    }
    else
        //left rotate
        if (bal<-1 && x > p->right->key)
        {
          //  printf("\n\tLeft rotation get performed on unbalanced node %d", p->key);
           // cout << endl;
            leftRotate(p);
        }
        else
            //left right
            if (bal > 1 && x > p->left->key)
            {
               // printf("\n\tLeft Right rotation get performed on unbalanced node %d", p->key);
               // cout << endl;
                leftRotate(p->left);
                rightRotate(p);
            }
            else
                //right left
                if (bal < -1 && x < p->right->key)
                {
                 //   printf("\n\tRight Left rotation get performed on unbalanced node %d", p->key);
                 //   cout << endl;
                    rightRotate(p->right);
                    leftRotate(p);
                }
   // cout << endl;
}

template<class T, class V>
void Tree<T, V>::balace1(TreeNode* p, T x) //int-> T
{
    //right rotate
    if (bal > 1 && x < p->left->key)
    {
       // printf("\n\tRight rotation get performed on unbalanced node %d", p->key);
       // cout << endl;
        rightRotate(p);
    }
    else
        //left rotate
        if (bal<-1 && x > p->right->key)
        {
           // printf("\n\tLeft rotation get performed on unbalanced node %d", p->key);
           // cout << endl;
            leftRotate(p);
        }
        else
            //left right
            if (bal > 1 && x > p->left->key)
            {
              //  printf("\n\ Right rotation get performed on unbalanced node %d", p->key);
              //  cout << endl;
                //leftRotate(p->left);
                rightRotate(p);
            }
            else
                //right left
                if (bal < -1 && x < p->right->key)
                {
              //      printf("\n\Left rotation get performed on unbalanced node %d", p->key);
              //      cout << endl;
                   // rightRotate(p->right);
                    leftRotate(p);
                }
    //cout << endl;
}


//To insert node 
template<class T, class V>
void Tree<T, V>::insert(T x, V y)
{
    TreeNode *p = create(x, y), *q;
    Add(p, x, y); //Просто добавление
   // printf("\n\t(Key, Value) = (%d, %d)",p->key, p->value);
    //cout << endl;
   q = getNode(p); //определить несбалансированный узел
   if (q != NULL)
   {
       balace(q, x);// Баланс несбалансированного узла
   }
}

//curr корень поддерева
template<class T, class V>
void Tree<T, V>::searchKey(Tree<T, V>::TreeNode*& curr, int data, Tree<T, V>::TreeNode*& parent)
{
    while (curr != nullptr && curr->key != data)
    {
        //обновляем родительский узел до текущего узла
        parent = curr;

        // если данный ключ меньше текущего узла, перейти к левому поддереву;
        // в противном случае переходим к правому поддереву
        if (data < curr->key) {
            curr = curr->left;
        }
        else {
            curr = curr->right;
        }
    }
}


template<class T, class V>
typename Tree<T, V>::TreeNode* Tree<T, V>::getMinimumKey(typename Tree<T,V>::TreeNode* curr)
{
    while (curr->left != nullptr) {
        curr = curr->left;
    }
    return curr;
}


template<class T, class V>
void Tree<T, V>::pop(T data)
{

    TreeNode* q;
    //указатель для хранения родителя текущего узла
    TreeNode* root1 = root;
    TreeNode* parent = nullptr;

    // начинаем с корневого узла
    TreeNode* curr = root1;

    // ищем ключ и устанавливаем его родительский указатель
    searchKey(curr, data, parent);

    // return if the key is not found in the tree
    if (curr == nullptr) {
        return;
    }

    // Case 1: node to be deleted has no children
    if (curr->left == nullptr && curr->right == nullptr)
    {
        if (curr != root1)
        {
            if (parent->left == curr) {
                parent->left = nullptr;
            }
            else {
                parent->right = nullptr;
            }
        }
        //если есть только корневой узел
        else {
            root = nullptr;
        }
       q = getNode(curr);  
        if (q != NULL)
        {
            balace1(q, data);
        }
             
    }

    // Case 2: node to be deleted has two children
    else if (curr->left && curr->right)
    {
        TreeNode* successor = getMinimumKey(curr->right);
       
        TreeNode* val = successor;
      
        
        pop(successor->key);
        val->left = curr->left;
        val->right = curr->right;
        val->parent = curr->parent;
      // curr = nullptr;
        curr = val;
       
        q = getNode(curr);
        if (q != NULL)
        {
            balace1(q, data);
        }
    }

   /* // Case 2: node to be deleted has two children
    else if (curr->left && curr->right)
    {
        // находим его узел-преемник в порядке
        TreeNode* successor = getMinimumKey(curr->right);
       // int val = successor->key;
        T val = successor->key;

        pop(successor->key); 

        curr->key = val;
    }*/
    // Case 3: node to be deleted has only one child
    else {
        TreeNode* child = (curr->left) ? curr->left : curr->right;


        if (curr != root1)
        {
            if (curr == curr->parent->left) {
                curr->parent->left = child;
                child->parent = curr->parent;
                //curr->left = nullptr;
                //curr->right = nullptr;
                //curr = child;


            }
            else {

                curr->parent->right = child;
                child->parent = curr->parent;

                //curr = child;

            }
        }
        else {
            root1 = child;
        }

        q = getNode(curr); //Identify imbalanced node
        if (q != NULL)
        {
            balace1(q, data);// Balance imbalanced Node
        }

    }
    /*// Case 3: node to be deleted has only one child
    else {
        TreeNode* child = (curr->left) ? curr->left : curr->right;

              
        if (curr != root1)
        {
            if (curr == parent->left) { 
                parent->left = child;
                //curr->left = nullptr;
                //curr->right = nullptr;
                //curr = child;
               

            }
            else {
               
                parent->right = child;
              
                //curr = child;
              
            }
        }
      
        else {
            root1 = child;
        }
       
        q = getNode(curr); //Identify imbalanced node
                if (q != NULL)
                {
                        balace(q, data);// Balance imbalanced Node
                }
             
      //free(curr);
    } */
}


#pragma once
