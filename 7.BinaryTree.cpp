template<class E>
structure BinTreeNode
{
	E data;
	BinTreeNode<E> *leftchild;
	BinTreeNode<E> *rightchild;

	BinTreeNode();
	BinTreeNode(const E &val, BinTreeNode<E> *lc = NULL, BinTreeNode *rc = NULL);
};

template<class E>
BinTreeNode<E>::BinTreeNode()
{
	leftchild = NULL;
	rightchild = NULL;
}

template<class E>
BinTreeNode<E>::BinTreeNode(const E &val, BinTreeNode<E> *lc = NULL, BinTreeNode *rc = NULL)
{
	data = val;
	leftchild = lc;
	rightchild = rc;
}



class BinaryTree
{
pubilc:
	BinaryTree();
	void PreOrderTraverse(BinTreeNode<E> *p);//前序遍历
	void InOrderTraverse(BinTreeNode<E> *p);//中序遍历
	void PostOrderTraverse(BinTreeNode<E> *p);//后序遍历
	int maxDepth(BinTreeNode<E> *root);//给定树的根节点求树的深度
	BinTreeNode* mergeTrees(BinTreeNode* t1, BinTreeNode* t2);//合并两棵二叉树 位置相同的值相加
	BinTreeNode* searchBST(BinTreeNode* root, int val);//二叉搜索树

private:
	BinTreeNode<E> *root;//最重要的指针 头指针
};


template<class E>
BinaryTree<E>::BinaryTree()
{
}



/*递归算法*/
template <class E>
void BinaryTree<E>::PrEOrderTraverse(BinTreeNode<E> *p)
{
	if (p != NULL)
	{
		cout << p->data;
		PreOrderTraverse(p->leftchild);//断点1
		/*调用之前 先保存了函数返回的断点1 以及指针的值（压栈）*/
		PreOrderTraverse(p->rightchild);//断点2
	}

}

template <class E>
void BinaryTree<E>::InOrderTraverse(BinTreeNode<E> *p)
{
	if (p != NULL)
	{
		InOrderTraverse(p->leftchild);
		cout << p->data;
		InOrderTraverse(p->rightchild);
	}

}

template<class E>
void BinaryTree<E>::PostOrderTraverse(BinTreeNode<E> *p)
{
	if (p != NULL)
	{
		PostOrderTraverse(p->leftchild);
		PostOrderTraverse(p->rightchild);
		cout << p->data;
	}
}


/*
上溢 避免
下溢 控制循环
*/
int leafnum = 0;
template<class E>
void BinaryTree<E>::LeafNum(BinTreeNode<E> *p)
{
	if (p != NULL)
	{
		if (p->leftchild == NULL&&p->rightchild == NULL) leafnum++;
		LeafNum(p->leftchild);
		LeafNum(p->rightchild);
	}
}

int depth = 0;
template<class E>
void BinaryTree<E>::TreeDepth(BinTreeNode<E> *p)
{
	if (p == NULL)  return 0;
	return 1+TreeDepth/*...*/
}

/*层次遍历  队列*/

/*非递归算法*/
template<class E>
void BinaryTree<E>::PreOrder(BinTreeNode<E> *p)
{
	do
	{
		while (p != NULL)
		{
			cout << p->data;
			push(s, p);
			p = p->Lchild;
		}
		if (!Empty(s))
		{
			p = pop(s);
			p = p->Rchild;
		}
	}while((!Empty(s))||(p!=NULL))
}

//求树的深度 leetcode104
template<class E>
int BinaryTree<E>::maxDepth(BinTreeNode* root)
{
	int length = 0;
	if (root != NULL)
	{
		length = max(maxDepth(root->Lchild), maxDepth(root->Rchild));
		length++;
	}
	return length;
}

//合并两棵二叉树 位置相同的值相加 leetcode617
template<class E>
TreeNode* BinaryTree<E>::mergeTrees(BinTreeNode* t1, BinTreeNode* t2) 
{
	if (t1 == NULL) return t2;
	if (t2 == NULL) return t1;
	BinTreeNode* newtree = new BinTreeNode(t1->val + t2->val);
	if (t1 != NULL&&t2 != NULL)
	{

		newtree->left = mergeTrees(t1->left, t2->left);
		newtree->right = mergeTrees(t1->right, t2->right);

	}
	return newtree;
}

//leetcode700 
template<class E>
TreeNode* BinaryTree<E>::searchBST(BinTreeNode* root, int val)
{
	// TreeNode* subtree;
	if (root == NULL) return NULL;
	else
	{
		if (root->val == val)
			return root;
		else if (root->val>val)
			return searchBST(root->left, val);
		else return searchBST(root->right, val);
	}
}