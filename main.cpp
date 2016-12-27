//
//  main.cpp
//  search2
//
//  Created by Jep Xia on 2016/12/27.
//  Copyright © 2016年 Jep Xia. All rights reserved.
//
#include <iostream>
using namespace std;

//定义树的节点类型
typedef struct binaryTreeNode {
    int data;   //数据类型为int
    struct binaryTreeNode *leftChild,*rightChild;
}binaryTreeNode, *binaryTree;

//添加节点的方法
bool binaryTreeInsert(binaryTree &p, int element){
    if(NULL == p) // 空树
    {
        p = new binaryTreeNode;
        p->data = element;
        p->leftChild = p->rightChild = NULL;
        return true;
    }
    
    if(element == p->data) // 表中不能有相等的值
        return false;
    
    if(element < p->data)  // 递归
        return binaryTreeInsert(p->leftChild, element);
    
    return binaryTreeInsert(p->rightChild, element); // 递归
    
}

//根据数组建立二叉树二叉树
void createBinaryTree(binaryTree &T, int a[], int number) {
    
    T = NULL;
    for(int i = 0; i < number; i++) //遍历
    {
        binaryTreeInsert(T, a[i]);
    }
}

//删除操作
bool Delete (binaryTree &p) {
    if (!p->rightChild) { //右子树为空
        p = p-> leftChild;
    } else if (!p->leftChild) {  //左子树为空
        p = p->rightChild;
    } else {                //左右子树都不为空
        binaryTree f = p;
        f = f->leftChild;
        while (f->rightChild) {
            f = f->rightChild;
        }
        binaryTree node = p -> leftChild;
        delete p->leftChild;
        f->rightChild = p ->rightChild;
        p->data = node->data;
        p->leftChild = node->leftChild;
        p->rightChild = f;
    }
    return true;
}

//删除对应的节点
bool deleteBinaryTree (binaryTree &T, int data) {
    if (!T) {
        return false;
    } else {
        if (T->data == data) {
            return Delete(T);
        } else if (T->data > data) {
            return deleteBinaryTree(T->leftChild, data); //递归
        } else {
            return deleteBinaryTree(T->rightChild, data);
        }
    }
}


//查询二叉排序树
bool searchBinaryTree(binaryTree T, binaryTree parents, int data, binaryTree &res) {
    if (!T)
    {
        binaryTreeInsert(T, data);
        return false;
    } else {
        if (data == T->data)
        {
            res = T;
            return true;
        } else if (data < T->data) {
            return searchBinaryTree(T -> leftChild, T, data, res); //递归
        } else {
            return searchBinaryTree(T -> rightChild, T, data, res);
        }
    }
}

//MARK: 递归方法遍历二叉树
//先序遍历二叉树
void preOrderTraverse(binaryTree T){
    if(T){
        cout << T -> data;
        preOrderTraverse(T->leftChild);
        preOrderTraverse(T->rightChild);
    }
}

//中序遍历二叉树
void inOrderTraverse(binaryTree T){
    if (T) {
        inOrderTraverse(T -> leftChild);
        cout << T -> data << " ";
        inOrderTraverse(T -> rightChild);
        
    }
}

//后序遍历二叉树
void postOrderTraverse (binaryTree T) {
    if (T) {
        postOrderTraverse(T -> leftChild);
        postOrderTraverse(T -> rightChild);
        cout << T -> data;
        
    }
}

//递归法,折半查找
int IterBiSearch(int data[], const int x, int beg, int last)
{
    int mid = -1;
    mid = (beg + last) / 2;
    if (x == data[mid])
        return mid + 1;
    else if (x < data[mid])
        return IterBiSearch(data, x, beg, mid - 1);
    else if (x > data[mid])
        return IterBiSearch(data, x, mid + 1, last);
    return -1;
}

//折半查找的实现
void ShowIterBiSearch ()
{
    cout << "按大小输入10个数字";
    int data1[10] = {0};
    int siz = sizeof(data1)/sizeof(int);
    for (int i = 0; i < siz; i++) {
        std::cin >> data1[i];
    }
    cout << "The array is : " << "  ";
    for (int i = 0; i < siz; i++) {
        cout << data1[i];
    }
    cout << "\n";
    int searchObject = 0;
    cout << "Please enter your searchObject: " << endl;
    cin >> searchObject;
    cout << IterBiSearch(data1, searchObject, 0, siz);
    
    
}


int main(int argc, char const *argv[])
{
    int flag;
    cout << "输入1代表静态查找，输入2代表动态查找" << endl;
    cin >> flag;
    switch (flag) {
        case 1:
            ShowIterBiSearch();
            break;
        case 2:
            cout << "请输入元素集合的数量" << endl;
            int number = 0;
            cin >> number;
            int* a = (int *) malloc ( sizeof(int) * number );
            cout << "请输入元素" << endl;
            for (int i = 0; i < number; ++i)
            {
                cin >> a[i];
            }
            cout << "请确认刚刚输入的元素集合：" << endl;
            
            
            for (int i = 0; i < number; ++i)
            {
                cout << a[i] << " ";
            }
            cout << "正在创建动态表..." << endl;
            binaryTree Tree;
            createBinaryTree(Tree, a, number);
            cout << "创建成功" << endl << "以下是中序遍历的结果" << endl;
            inOrderTraverse(Tree);
            cout << endl;
            while (true) {
                cout << "请输入要查询的数值" << endl;
                int x;
                cin >> x;
                binaryTree searchTree;
                if (!searchBinaryTree(Tree, NULL, x, searchTree)) {
                    cout << "动态表中没有该数值 ..." << endl << "成功添加该数值！" << endl;
                    binaryTreeInsert(Tree, x);
                    cout << "输入1可重新遍历该表 \nor press any number to pass" << endl;
                    int d;
                    cin >> d;
                    if (d == 1) {
                        inOrderTraverse(Tree); cout << endl;
                    }
                    
                } else {
                    cout << "查找成功！\n" << "如果要删除该数值请输入1 \nor press any number to pass " << endl;
                    int c;
                    cin >> c;
                    switch (c) {
                        case 1:
                            if (deleteBinaryTree(Tree, x))
                                cout << "删除成功" << endl;
                            else
                                cout << "删除失败" << endl;
                            break;
                            
                        default:
                            break;
                    }
                    cout << "输入1可重新遍历该表 \nor press any number to pass" << endl;
                    int d;
                    cin >> d;
                    if (d == 1) {
                        inOrderTraverse(Tree); cout << endl;
                    }
                }
            }

            break;
    }
        return 0;
}
