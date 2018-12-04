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
	void PreOrderTraverse(BinTreeNode<E> *p);//ǰ�����
	void InOrderTraverse(BinTreeNode<E> *p);//�������
	void PostOrderTraverse(BinTreeNode<E> *p);//�������
	int maxDepth(BinTreeNode<E> *root);//�������ĸ��ڵ����������
	BinTreeNode* mergeTrees(BinTreeNode* t1, BinTreeNode* t2);//�ϲ����ö����� λ����ͬ��ֵ���
	BinTreeNode* searchBST(BinTreeNode* root, int val);//����������

private:
	BinTreeNode<E> *root;//����Ҫ��ָ�� ͷָ��
};


template<class E>
BinaryTree<E>::BinaryTree()
{
}



/*�ݹ��㷨*/
template <class E>
void BinaryTree<E>::PrEOrderTraverse(BinTreeNode<E> *p)
{
	if (p != NULL)
	{
		cout << p->data;
		PreOrderTraverse(p->leftchild);//�ϵ�1
		/*����֮ǰ �ȱ����˺������صĶϵ�1 �Լ�ָ���ֵ��ѹջ��*/
		PreOrderTraverse(p->rightchild);//�ϵ�2
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
���� ����
���� ����ѭ��
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

/*��α���  ����*/

/*�ǵݹ��㷨*/
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

//��������� leetcode104
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

//�ϲ����ö����� λ����ͬ��ֵ��� leetcode617
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