#ifndef _AVL_FUNC_H_
#define _AVL_FUNC_H_

#include <iostream>
#include <algorithm>

using namespace std;

template <typename KeyType>
class AVLNode{
    public:
        KeyType key;
        AVLNode *left;
        AVLNode *right;
        AVLNode(KeyType k):key(k),left(nullptr),right(nullptr){}
};

template <typename KeyType>
class AVLTree{
    typedef AVLNode<KeyType> Node;
    private:
        Node *avlroot;
        int __getheight(const Node *root);//求树的高度
        int __diff(const Node *root);//求平衡因子
        Node *__insert(Node *&root,const KeyType key);//插入内部实现
        Node *__delnode(Node *root,const KeyType key);//删除内部实现
        Node *__balance(Node *root);//平衡操作
        //四种旋转操作
        Node *__rotation_ll(Node *root);
        Node *__rotation_rr(Node *root);
        Node *__rotation_lr(Node *root);
        Node *__rotation_rl(Node *root);
        Node *__search(Node *root,const KeyType key);//查找内部实现
        void __traversal(Node *root);//遍历(中序)内部实现
        void __deleteTree(Node *root);//删除树
        Node *__treeMax(Node *root);//前根节点最大
        Node *__treeMin(Node *root);//前根节点最小
    public:
        AVLTree(){avlroot = nullptr;} //默认构造函数
        ~AVLTree();
        AVLTree(const KeyType *arr,int len); //构造函数，数组构造
        bool insert(const KeyType key);//插入外部接口
        bool search(const KeyType key);//查找外部接口
        void traversal();//遍历(中序)外部接口
        bool delnode(const KeyType key);//删除外部接口
};

//所有内部实现
//求树的高度
template <typename KeyType>
int AVLTree<KeyType>::__getheight(const Node *root){
    if(root == nullptr) return 0;
    return max(__getheight(root->left) , __getheight(root->right)) + 1;
}

//求平衡因子
template <typename KeyType>
int AVLTree<KeyType>::__diff(const Node *root){
    if(root == nullptr) return 0;
    return __getheight(root->left) - __getheight(root->right);
}

//插入内部实现
template <typename KeyType>
AVLNode<KeyType> *AVLTree<KeyType>::__insert(Node *&root,const KeyType key){
    if(root == nullptr){
        root = new Node(key);
        return root;
    }
    if(key < root->key){
        __insert(root->left,key);
        root = __balance(root);
        return root;
    }else if(key > root->key){
        __insert(root->right,key);
        root = __balance(root);
        return root;
    }else{
        return root;
    }   
}

//平衡操作
template <typename KeyType>
AVLNode<KeyType> *AVLTree<KeyType>::__balance(Node *root){
    int dis = __diff(root);
    if(dis > 1){//左子树高于右子树
        if(__diff(root->left) > 0)
            root = __rotation_ll(root);
        else
            root = __rotation_lr(root);
    }else if(dis < -1){//右子树高于左子树
        if(__diff(root->right) < 0)
            root = __rotation_rr(root);
        else
            root = __rotation_rl(root);
    }
    return root;
}

//四种旋转
template <typename KeyType>
AVLNode<KeyType> *AVLTree<KeyType>::__rotation_ll(Node *root){
    Node *temp = root->left;
    root->left = temp->right;
    temp->right = root;
    return temp;
}
template <typename KeyType>
AVLNode<KeyType> *AVLTree<KeyType>::__rotation_rr(Node *root){
    Node *temp = root->right;
    root->right = temp->left;
    temp->left = root;
    return temp;
}
template <typename KeyType>
AVLNode<KeyType> *AVLTree<KeyType>::__rotation_lr(Node *root){
    root->left = __rotation_rr(root->left);
    return __rotation_ll(root);
}
template <typename KeyType>
AVLNode<KeyType> *AVLTree<KeyType>::__rotation_rl(Node *root){
    root->right = __rotation_ll(root->right);
    return __rotation_rr(root);
}

//查找内部实现
template <typename KeyType>
AVLNode<KeyType> *AVLTree<KeyType>::__search(Node *root,const KeyType key){
    if(root == nullptr) return nullptr;
    if(key == root->key)
        return root;
    else if(key < root->key)
        return __search(root->left,key);
    else
        return __search(root->right,key);
}

//遍历(中序)内部实现
template <typename KeyType>
void AVLTree<KeyType>::__traversal(Node *root){
    if(root == nullptr) return;
    __traversal(root->left);
    cout << root->key << " ";
    __traversal(root->right);
}

template <typename KeyType>
AVLNode<KeyType> *AVLTree<KeyType>::__treeMax(Node *root){
    return (root->right) ? __treeMax(root->right) : root;
}
template <typename KeyType>
AVLNode<KeyType> *AVLTree<KeyType>::__treeMin(Node *root){
    return (root->left) ? __treeMin(root->left) : root;
}

//删除结点内部实现
template <typename KeyType>
AVLNode<KeyType> *AVLTree<KeyType>::__delnode(Node *root,const KeyType key){
    if(root == nullptr) return root;
    if(!search(key)){
        cout << "Key not find!" << endl;
        return root;
    }
    if(key == root->key){
        if (root->left != nullptr && root->right != nullptr) {
            if(__diff(root) > 0){
                root->key = __treeMax(root->left)->key;
                root->left = __delnode(root->left, root->key);
            }else{
                root->key = __treeMin(root->right)->key;
                root->right = __delnode(root->right, root->key);
            }
        }else{
            Node * temp = root;
            root = (root->left) ? (root->left) : (root->right);
            delete temp;
            temp = nullptr;
        }
    }else if(key < root->key){
        root->left = __delnode(root->left,key);
        root = __balance(root);
    }else{
        root->right = __delnode(root->right,key);
        root = __balance(root);
    }
    return root;
}

//删除树
template <typename KeyType>
void AVLTree<KeyType>::__deleteTree(Node *root){
    if(root == nullptr) return;
    __deleteTree(root->left);
    __deleteTree(root->right);
    delete root;
    root = nullptr;
    return;
}

//所有外部接口
//构造函数-数组构造
template <typename KeyType>
AVLTree<KeyType>::AVLTree(const KeyType *arr,int len){
    avlroot = nullptr;
    for(int i = 0;i < len;i++){
        insert(*(arr + i));
    }
}

//插入外部接口
template <typename KeyType>
bool AVLTree<KeyType>::insert(const KeyType key){
    return __insert(avlroot,key) == nullptr ? false : true;
}

//查找外部接口
template <typename KeyType>
bool AVLTree<KeyType>::search(const KeyType key){
    return __search(avlroot,key) == nullptr ? false : true;
}

//遍历(中序)外部接口
template <typename KeyType>
void AVLTree<KeyType>::traversal(){
    __traversal(avlroot);
}

//删除外部接口
template <typename KeyType>
bool AVLTree<KeyType>::delnode(const KeyType key){
    return __delnode(avlroot,key) == nullptr ? false : true;
}

//析构函数
template <typename KeyType>
AVLTree<KeyType>::~AVLTree(){
    __deleteTree(avlroot);
}

#endif