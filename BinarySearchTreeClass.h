#ifndef BINARYSEARCHTREECLASS_H_INCLUDED
#define BINARYSEARCHTREECLASS_H_INCLUDED

#include <cstddef>

struct node
{
    int info;
    struct node *left;
    struct node *right;
}*root;

class BST
{
    public:
        void find(int, node **, node **);
        void insert(node *, node *);
        void deletion(int);
        void route1(node *,node *);
        void route2(node *,node *);
        void route3(node *,node *);
        void preorder(node *);
        void reverseInorder(node *);
        void inorder(node *);
        void postorder(node *);
        void display(node *, int);
        void sumOfLongRootToLeafPath(node*, int, int, int&, int&);
        int sumOfLongRootToLeafPathUtil(node*);
        //constructor
        BST()
        {
            root = NULL;
        }
};


#endif // BINARYSEARCHTREECLASS_H_INCLUDED
