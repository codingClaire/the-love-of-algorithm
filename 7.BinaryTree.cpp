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