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
	TreeNode() :m_Element(), m_TreeHeight(0), m_pRightChild(nullptr), m_pLeftChild(nullptr) {}
	TreeNode(const T& e) :m_Element(e), m_TreeHeight(0), m_pRightChild(nullptr), m_pLeftChild(nullptr) {}
	~TreeNode() = default;
	//数据域
	T m_Element;
	//树高
	int m_TreeHeight;
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


	// 完全二叉树插入（逐个插入）
	void CompleteInsert(const T& e)
	{
		pTreeNode<T> pNewNode = new TreeNode<T>(e);  // 创建新节点

		//看看是否为空树
		if (m_pRoot == nullptr) {
			m_pRoot = pNewNode;
			return;
		}

		//队列，存储当前结点的指针
		std::queue<pTreeNode<T>> q;
		//开头存储根节点，然后向左节点和右节点插入数据
		q.push(m_pRoot);

		while (!q.empty()) {
			//进入循环，获取队列头指针，然后完成结点的左右孩子的插入
			pTreeNode<T> pCur = q.front();
			//出队
			q.pop();

			// 检查左孩子,左孩子为空则插入
			if (pCur->m_pLeftChild == nullptr) {
				pCur->m_pLeftChild = pNewNode;
				return;
			}
			//检查左孩子, 左孩子不空则不插入，保存该左节点指针入队
			else {
				q.push(pCur->m_pLeftChild);
			}

			// 同理
			if (pCur->m_pRightChild == nullptr) {
				pCur->m_pRightChild = pNewNode;
				return;
			}
			else {
				q.push(pCur->m_pRightChild);
			}
		}
	}

	//递归销毁树
	void DestroyTree(pTreeNode<T> node)
	{
		if (node == nullptr) return;
		DestroyTree(node->m_pLeftChild);
		DestroyTree(node->m_pRightChild);
		delete node;
	}

	//获取平衡因子
	int GetBalance(pTreeNode<T> node)
	{
		if (node == nullptr) return 0;
		//左子树高度
		int leftH = (node->m_pLeftChild) ? node->m_pLeftChild->m_TreeHeight : 0;
		//右子树高低
		int rightH = (node->m_pRightChild) ? node->m_pRightChild->m_TreeHeight : 0;
		return leftH - rightH;
	}


	//更新树高函数
	void UpdateHeight(pTreeNode<T> node)
	{
		//空则直接返回，默认树高为0；
		if (node == nullptr) return;
		//左子树最高度
		int leftH = (node->m_pLeftChild) ? node->m_pLeftChild->m_TreeHeight : 0;
		//右子树最高度
		int rightH = (node->m_pRightChild) ? node->m_pRightChild->m_TreeHeight : 0;
		//保存当前结点的子树高度
		node->m_TreeHeight = 1 + (leftH > rightH ? leftH : rightH);
	}



	//左旋规则
	//1.当前结点的 右子树 会作为 新树的根节点
	//2.当前的结点 会作为 新树的根节点的 左子树
	//3.如果新树的根节点有 左子树，那么此左子树 作为 旧根节点的右子树
	pTreeNode<T> LeftRoate(pTreeNode<T> oldroot)
	{

		if (oldroot == nullptr || oldroot->m_pRightChild == nullptr)
			return oldroot;   // 无法旋转

		//临时存储
		pTreeNode<T> pTmp = nullptr;

		//当前结点的 右子树 会作为 新树的根节点
		pTreeNode<T> pNewroot = oldroot->m_pRightChild;

		//如果新树的根节点有 左子树，那么此左子树 作为 旧根节点的右子树
		if (pNewroot->m_pLeftChild != nullptr)
		{
			//保存新根的左子树
			pTmp = pNewroot->m_pLeftChild;
		}
		//当前的结点 会作为 新树的根节点的 左子树
		pNewroot->m_pLeftChild = oldroot;
		//规则3
		oldroot->m_pRightChild = pTmp;

		//更新树高
		// 先更新旧根，再更新新根，因为新根依赖旧根
		UpdateHeight(oldroot);
		UpdateHeight(pNewroot);

		return pNewroot;
	}

	//右旋规则
	//1.当前结点的 左子树 会作为 新树的根节点
	//2.当前的结点 会作为 新树的根节点的 右子树
	//3.如果新树的根节点有 右子树，那么此右子树 作为 旧根节点的左子树
	pTreeNode<T> RightRoate(pTreeNode<T> oldroot)
	{
		if (oldroot == nullptr || oldroot->m_pLeftChild == nullptr)
			return oldroot;   // 无法旋转

		//临时存储
		pTreeNode<T> pTmp = nullptr;
		//当前结点的  左子树 会作为 新树的根节点
		pTreeNode<T> pNewroot = oldroot->m_pLeftChild;

		//如果新树的根节点有 右子树，那么此右子树 作为 旧根节点的左子树
		if (pNewroot->m_pRightChild != nullptr)
		{
			//保存新根的右子树
			 pTmp = pNewroot->m_pRightChild;
		}
		//当前的结点 会作为 新树的根节点的 右子树
		pNewroot->m_pRightChild = oldroot;
		//规则3
		oldroot->m_pLeftChild = pTmp;

		// 更新高度
		UpdateHeight(oldroot);
		UpdateHeight(pNewroot);

	}


	// LL 型（右旋）
	pTreeNode<T> RotateLL(pTreeNode<T> node)
	{
		return RightRoate(node);
	}

	// RR 型（左旋）
	pTreeNode<T> RotateRR(pTreeNode<T> node)
	{
		return LeftRoate(node);
	}

	// LR 型（先左旋左子树，再右旋）
	pTreeNode<T> RotateLR(pTreeNode<T> node)
	{
		node->m_pLeftChild = LeftRoate(node->m_pLeftChild);
		return RightRoate(node);
	}

	// RL 型（先右旋右子树，再左旋）
	pTreeNode<T> RotateRL(pTreeNode<T> node)
	{
		node->m_pRightChild = RightRoate(node->m_pRightChild);
		return LeftRoate(node);
	}


	// 平衡调整
	pTreeNode<T> BalanceNode(pTreeNode<T> node)
	{
		if (node == nullptr) return nullptr;

		// 先更新当前节点高度（因为递归返回后可能已改变）
		UpdateHeight(node);

		int balance = GetBalance(node);

		// 左子树过高（balance > 1）
		if (balance > 1)
		{
			// 检查左孩子的平衡因子，判断是 LL 还是 LR
			if (GetBalance(node->m_pLeftChild) >= 0)
				return RotateLL(node);          //LL
			else
				return RotateLR(node);          //LR
		}
		// 右子树过高（balance < -1）
		else if (balance < -1)
		{
			if (GetBalance(node->m_pRightChild) <= 0)
				return RotateRR(node);          //RR
			else
				return RotateRL(node);          //RL
		}

		// 已平衡，返回原节点
		return node;
	}

	// 寻找最小节点（用于删除） 
	pTreeNode<T> FindMin(pTreeNode<T> node)
	{
		if (node == nullptr) return nullptr;
		while (node->m_pLeftChild != nullptr)
			node = node->m_pLeftChild;
		return node;
	}

	// 递归插入
	pTreeNode<T> InsertRec(pTreeNode<T> node, const T& e)
	{
		// 1. 普通 BST 插入
		if (node == nullptr)
			return new TreeNode<T>(e);

		if (e < node->m_Element)
			node->m_pLeftChild = InsertRec(node->m_pLeftChild, e);
		else if (e > node->m_Element)
			node->m_pRightChild = InsertRec(node->m_pRightChild, e);
		else
			return node;          // 元素已存在，不插入

		//更新高度并平衡
		return BalanceNode(node);
	}

	//递归删除
	pTreeNode<T> DeleteRec(pTreeNode<T> node, const T& e)
	{
		if (node == nullptr)
			return nullptr;     // 未找到

		// 1. BST 删除
		if (e < node->m_Element)
			node->m_pLeftChild = DeleteRec(node->m_pLeftChild, e);
		else if (e > node->m_Element)
			node->m_pRightChild = DeleteRec(node->m_pRightChild, e);
		else
		{
			// 找到待删除节点
			if (node->m_pLeftChild == nullptr || node->m_pRightChild == nullptr)
			{
				// 情况1：叶子节点 或 只有一个孩子
				pTreeNode<T> temp = (node->m_pLeftChild) ? node->m_pLeftChild : node->m_pRightChild;
				if (temp == nullptr)
				{
					// 叶子：直接删除
					delete node;
					return nullptr;
				}
				else
				{
					// 只有一个孩子：用孩子替代
					*node = *temp;          // 复制节点内容
					delete temp;
					//这里 *node 复制了 temp 的 m_TreeHeight 等，后续会重新更新
				}
			}
			else
			{
				// 情况2：有两个孩子 用后继（右子树最小节点）替换
				pTreeNode<T> minNode = FindMin(node->m_pRightChild);
				node->m_Element = minNode->m_Element;   // 复制数据
				// 递归删除后继（注意后继一定没有左孩子）
				node->m_pRightChild = DeleteRec(node->m_pRightChild, minNode->m_Element);
			}
		}

		//更新高度并平衡（如果节点被删除了，递归返回后可能为null）
		if (node == nullptr)
			return nullptr;

		return BalanceNode(node);
	}


	//插入（自动平衡）
	void Insert(const T& e)
	{
		m_pRoot = InsertRec(m_pRoot, e);
	}

	//删除（自动平衡）
	void Delete(const T& e)
	{
		m_pRoot = DeleteRec(m_pRoot, e);
	}


	//根结点指针
	pTreeNode<T> m_pRoot;
	//非递归迭代栈(记录指针)
	std::stack<pTreeNode<T>> m_sPNode;
};