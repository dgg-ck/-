#pragma once
#include<iostream>
#include<stack>
#include<queue>


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
	//层次遍历 ---广度搜索 BFS
	void LevelOrder(pTreeNode<T> node)
	{
		if (node == nullptr)
		{
			return;
		}
		//移动指针
		pTreeNode<T> pTmp = node;
		//队列，存储子节点，让顺序输出
		std::queue<pTreeNode<T>> qQueue;

		//根节点先入队
		qQueue.push(node);
		while (!qQueue.empty())
		{
			//获取队头
			pTmp = qQueue.front();
			std::cout << pTmp->m_Element << " ";
			//队头出队
			qQueue.pop();
			//判断队头有没有其它左子节点
			if (pTmp->m_pLeftChild != nullptr)
			{
				//有的话入队
				qQueue.push(pTmp->m_pLeftChild);
				//输出左子结点的信息
				//std::cout << pTmp->m_pLeftChild->m_Element << " ";
			}
			//在判断队头有没有其它右子节点
			if (pTmp->m_pRightChild != nullptr)
			{
				//有的话入队
				qQueue.push(pTmp->m_pRightChild);
				//输出右子结点的信息
				//std::cout << pTmp->m_pRightChild->m_Element << " ";
			}
		}


	}


	// 完全二叉树插入
	void CompleteInsert(const T& e)
	{
		pTreeNode<T> pNewNode = new TreeNode<T>(e);  // 创建新节点

		if (m_pRoot == nullptr) {
			m_pRoot = pNewNode;
			return;
		}

		std::queue<pTreeNode<T>> q;
		q.push(m_pRoot);

		while (!q.empty()) {
			pTreeNode<T> pCur = q.front();
			q.pop();

			// 检查左孩子
			if (pCur->m_pLeftChild == nullptr) {
				pCur->m_pLeftChild = pNewNode;
				return;
			}
			else {
				q.push(pCur->m_pLeftChild);
			}

			// 检查右孩子
			if (pCur->m_pRightChild == nullptr) {
				pCur->m_pRightChild = pNewNode;
				return;
			}
			else {
				q.push(pCur->m_pRightChild);
			}
		}
	}



	//根结点指针
	pTreeNode<T> m_pRoot;
	//非递归迭代栈(记录指针)
	std::stack<pTreeNode<T>> m_sPNode;
};