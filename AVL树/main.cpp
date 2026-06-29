#include "VALTree.h"
using namespace std;

int main()
{
    BinaryTree<int> tree;
    // 插入
    tree.Insert(10);
    tree.Insert(20);
    tree.Insert(30);   // 会触发 RR 左旋
    tree.Insert(15);
    tree.Insert(5);
    tree.Insert(25);

    cout << "中序遍历（应有序）: ";
    tree.InOrder(tree.m_pRoot);   // 5 10 15 20 25 30
    cout << endl;

    cout << "层次遍历: ";
    tree.LevelOrder(tree.m_pRoot);
    cout << endl;

    tree.Delete(20);
    cout << "删除20后中序: ";
    tree.InOrder(tree.m_pRoot);   // 5 10 15 25 30
    cout << endl;

    return 0;
}