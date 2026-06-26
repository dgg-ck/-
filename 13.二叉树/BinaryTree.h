#pragma once
#include<iostream>
#include<stack>


template<class T>
class TreeNode;
template<class T>
using pTreeNode = TreeNode<T>*;


//树的结点
template<class T>
class TreeNode
{
public:
	TreeNode() :m_Element(), m_pRightChild(nullptr), m_pLeftChild(nullptr) {}
	TreeNode(const T& e) :m_Element(e), m_pRightChild(nullptr), m_pLeftChild(nullptr) {}
	~TreeNode() = default;
	T m_Element;
	//左孩子
	pTreeNode<T> m_pRightChild;
	//右孩子
	pTreeNode<T> m_pLeftChild;

};

//树类
template<class T>
class BinaryTree
{
public:
	//构造函数
	BinaryTree()
	{
		m_pRoot = nullptr;
	}
	BinaryTree(const T& e)
	{
		m_pRoot = new TreeNode<T>(e);
	}
	//析构函数
	~BinaryTree()
	{
		if (m_pRoot != nullptr)
		{
			delete m_pRoot;
		}
		m_pRoot = nullptr;
	}
	//创建结点
	pTreeNode<T> TreeNodeCreate(const T& e)
	{
		return new TreeNode<T>(e);
	}
	//结点插入
	void TreeNodeInsert(pTreeNode<T> parent, 
						pTreeNode<T> LChild, 
						pTreeNode<T> RChild)
	{
		parent->m_pLeftChild = LChild;
		parent->m_pRightChild = RChild;
	}
	//前序遍历(根左右)
	void PreOrder(pTreeNode<T> node)
	{
		
		if (node == nullptr)
		{
			return;
		}
		std::cout << node->m_Element << " ";
		PreOrder(node->m_pLeftChild);
		PreOrder(node->m_pRightChild);
	}
	//中序遍历
	void InOrder(pTreeNode<T> node)
	{
		
		if (node == nullptr)
		{
			return;
		}
		InOrder(node->m_pLeftChild);
		std::cout << node->m_Element << " ";
		InOrder(node->m_pRightChild);

	}
	//后序遍历
	void PostOrder(pTreeNode<T> node)
	{
		if (node == nullptr)
		{
			return;
		}
		PostOrder(node->m_pLeftChild);
		PostOrder(node->m_pRightChild);
		std::cout << node->m_Element << " ";
	}
	//非递归迭代
	//非递归之先序
	void NoRecurPreOrder(pTreeNode<T> node)
	{
		if (node == nullptr)
		{
			return;
		}
		//临时指针
		pTreeNode<T> pTmp = node;

		//正常运行
		while (pTmp != nullptr || !m_sPNode.empty())
		{
			while (pTmp != nullptr)
			{
				//输出当前结点 根左右
				std::cout << pTmp->m_Element << " ";
				//记录每一个树指针
				m_sPNode.push(pTmp);
				//指针往左走
				pTmp = pTmp->m_pLeftChild;
			}
			
			if (!m_sPNode.empty())
			{
				//回退到上一个指针
				pTmp = m_sPNode.top();
				m_sPNode.pop();
				//指针往右走
				pTmp = pTmp->m_pRightChild;
			}
		}
		

	}

	//根结点指针
	pTreeNode<T> m_pRoot;
	//非递归迭代栈(记录指针)
	std::stack<pTreeNode<T>> m_sPNode;
};