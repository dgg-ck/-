#include"BinaryTree.h"

int main()
{
	//创建一个树先(里面已经有一个根结点了)
	BinaryTree<char>* pBT = new BinaryTree<char>('Z');

	//先创建一堆结点
	pTreeNode<char> A = pBT->TreeNodeCreate('A');
	pTreeNode<char> B = pBT->TreeNodeCreate('B');
	pTreeNode<char> C = pBT->TreeNodeCreate('C');
	pTreeNode<char> D = pBT->TreeNodeCreate('D');
	pTreeNode<char> E = pBT->TreeNodeCreate('E');
	pTreeNode<char> F = pBT->TreeNodeCreate('F');

	//傻瓜链接
	pBT->TreeNodeInsert(pBT->m_pRoot, A, B);
	pBT->TreeNodeInsert(A, C, D);
	pBT->TreeNodeInsert(B, E,F);

	//先序遍历
	std::cout << "先序遍历:";
	pBT->PreOrder(pBT->m_pRoot);
	std::cout << std::endl;

	//中序遍历
	std::cout << "中序遍历:";
	pBT->InOrder(pBT->m_pRoot);
	std::cout << std::endl;

	//后续遍历
	std::cout << "后序遍历:";
	pBT->PostOrder(pBT->m_pRoot);
	std::cout << std::endl;

	//非迭代先序遍历
	std::cout << "非迭代先序遍历:";
	pBT->NoRecurPreOrder(pBT->m_pRoot);
	std::cout << std::endl;

	return 0;
}