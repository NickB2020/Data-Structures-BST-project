/*
Nick Bischoff
Data Structures
Assignment 3
File Name: main.cpp, included is a .h header file called BinarySearchTreeClass that holds the class for the BST and the struct to hold the nodes.
Purpose: This program is Binary Search Tree operations menu. Starting the program the user will see a numbered menu that re-occurs after every user-selected option is successfully executed. The menu uses a switch statement to conduct the selection process and validates the user's choice for the menu option as well. The program file's in a list of numbers from an included test.txt file to pre-populate the BST for ease of testing of all the operations right away. The operations are as follows: insertion, deletion, print keys high to low, pre, post and inorder traversals, display the nodes in a tree format, search for nodes, the cost of the most expensive path, and of course a quit option to end the program. I understand that including operations for the three traversals of preorder, postorder and inorder were not required but I thought it would be good practice to include them as well. the program pauses and waits for input after each operation is complete, then clears the screen and returns to the menu for the user to choose another option without closing the program. This program utilizes a BST class which holds all the operations for the BST as well as a struct to hold the nodes for the operations. This is a linked list based Binary Search Tree implementation.
*/
#include "BinarySearchTreeClass.h"
#include <iostream>
#include <fstream>
#include <fstream>
#include <limits>

//using
using std::ifstream;
using std::cout;
using std::cin;
using std::endl;
using std::streamsize;
using std::numeric_limits;

//declarations
int menu();
struct node* search(node*, int);

// main just calls the menu function
int main()
{
    menu();

    return 0;
}

//***********************************************************************************************
//                          Menu Function For User Interface
//
//***********************************************************************************************
//pre: Class BST and struct for nodes needs to exist and functions supporting BST operations need to be operational so the menu has meaning
//post: The user can now navigate this program with the help of the function that provides a user interface complete if validation and file in reading to populate the BST for ease of testing.
int menu()
{
    // initialization of variables for switch statement, BST class object, and a node pointer.
    int choice, key;
    BST bst;
    node* temp;
    // This file stream in's the test.txt file to pre-fill the BST for ease of usage
    ifstream fin;
    fin.open("test.txt");
    while(!fin.eof())
    {
        temp = new node;
        fin>>temp->info;
        bst.insert(root, temp);
        system("cls");
    }
    // While loop controls the repeating functionality of the menu after each operation is completed.
    while (1)
    {
        cout << "This program reads in a list of numbers from test.txt so the BST is already created for the user\nto test and use all operations from the menu.\n" << endl;
        cout << "1.Insert Element " << endl;
        cout << "2.Delete Element " <<endl;
        cout << "3.Print keys sorted high to low:" << endl;
        cout << "4.Preorder Traversal" << endl;
        cout << "5.Postorder Traversal" << endl;
        cout << "6.inorder Traversal" << endl;
        cout << "7.Display" << endl;
        cout << "8.Search" << endl;
        cout << "9.Cost of most expensive path" << endl;
        cout << "10.Quit" << endl;
        // Menu choice input validation, will ONLY accept a choice of 1-9.
        do{
                cout << "Enter your choice: ";
                cin >> choice;
                if(cin.fail() || choice < 1 || choice > 10)
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                    cout << " \n* Please enter a numeric option from the selection above *\n" << endl;
                }
           }while(cin.fail() || choice < 1 || choice > 10);
        // Switch statement controls which BST function will be called based on the user's choice form the menu.
        switch(choice)
        {
            // Insert new node, call insert function
        case 1:
            temp = new node;
            cout << "\nEnter the number to be inserted : ";
            cin >> temp->info;
            bst.insert(root, temp);
            system("pause");
            system("cls");
            break;
            // Delete an existing node call delete function
        case 2:
            if (root == NULL)
            {
                cout << "Tree is empty, nothing to delete" << endl;
                continue;
            }
            cout << "\nEnter the number to be deleted: ";
            cin >> key;
            bst.deletion(key);
            system("pause");
            system("cls");
            break;
            // sort the nodes (keys) from high to low, call reverse inorder function
        case 3:
            cout << "\nKeys sorted high to low:" << endl;
            bst.reverseInorder(root);
            cout << endl << endl;
            system("pause");
            system("cls");
            break;
            // print the preorder traversal of the BST, call the preorder function
        case 4:
            cout << "\nPreorder Traversal of BST:" << endl;
            bst.preorder(root);
            cout << endl << endl;
            system("pause");
            system("cls");
            break;
             // print the postorder traversal of the BST, call the postorder function
        case 5:
            cout << "\nPostorder Traversal of BST:" << endl;
            bst.postorder(root);
            cout << endl << endl;
            system("pause");
            system("cls");
            break;
             // print the inorder traversal of the BST, call the inorder function
        case 6:
            cout << "\nInorder Traversal of BST:" << endl;
            bst.inorder(root);
            cout << endl << endl;
            system("pause");
            system("cls");
            break;
            //Print the BST in tree format, call the display function
        case 7:
            cout << "\nDisplay nodes in tree format:" << endl;
            bst.display(root,1);
            cout << endl;
            system("pause");
            system("cls");
            break;
            // search the BST for a particular key, call the search function
        case 8:
            cout << "\nEnter node to search: ";
            cin >> key;
            cout << "\nSearching..." << endl;
            temp = search(root, key);
            if (temp == NULL)
            {
                cout << "\nNot found in Binary Search Tree\n" << endl;
            }
            else
            {
                cout << endl << temp->info << " found in Binary Search Tree\n\n";
            }
            system("pause");
            system("cls");
            // Find the cost (sum) of the most expensive path, call the sumOfLongRootToLeafPathUtil
            break;
        case 9:
            cout << "\nSum of most expensive path = "<< bst.sumOfLongRootToLeafPathUtil(root) << endl << endl;
            system("pause");
            system("cls");
            break;
            // break loop for menu and exit the program
        case 10:
            return 0;
        }
    }
}
//***********************************************************************************************
//              Binary Search Tree Operation Methods And Supporting Functions
//
//***********************************************************************************************

//Find Element in the Tree (utility function for deletion function)
//pre: BST class and the struct "node" for the node pointers must exist. File in must exist, as well as the insertion function to populate BST
//post: This function can search through the tree and find the desired node, mostly used as a utility function for the deletion function
// to check if what the user wants to delete is in the tree or not.
void BST::find(int item, node **parent, node **location)
{
     //initiate one pointer to use then a second ptr to store.
    node *ptr, *ptr2;
    //if the root is NULL then make the location and parent pointers NULL as well
    if (root == NULL)
    {
        *location = NULL;
        *parent = NULL;
        return;
    }
    // if what we are looking for is the root then set the location
    if (item == root->info)
    {
        *location = root;
        *parent = NULL;
        return;
    }
    // if what we are looking for is less than the root go to left subtree
    if (item < root->info)
        ptr = root->left;
    else
        // if what we are looking for is more than the root go to right subtree
        ptr = root->right;
    // store the root
    ptr2 = root;
    while (ptr != NULL)
    {   // update location and the parent
        if (item == ptr->info)
        {
            *location = ptr;
            *parent = ptr2;
            return;
        }
        ptr2 = ptr;
        if (item < ptr->info)
            ptr = ptr->left;
        else
            ptr = ptr->right;
    }
    *location = NULL;
    *parent = ptr2;
}
//search (user search from the menu)
//Although the find function could be used in place of this function, I could not get accurate results so I made this function to ensure accuracy
//pre: BST class and the struct "node" for the node pointers must exist. File in must exist, as well as the insertion function to populate BST
//post: This function can now search through the tree recursively for the user input key.
struct node* search(node* root, int key)
{
    // Base Cases: root is null or key is present at root
    if (root == NULL || root->info == key)
    {
        return root;
    }

    // Key is greater than root's key
    if (root->info < key)
    {
        return search(root->right, key);
    }

    else
    {
        // Key is smaller than root's key
        return search(root->left, key);
    }

}

//Insertion
//pre: BST class and the struct "node" for the node pointers must exist.
//post: now we can add new nodes recursively into the BST, root, left and right subtrees with this function
void BST::insert(node *tree, node *newnode)
{
    // if root is NULL then make new node for the root
    if (root == NULL)
    {
        root = new node;
        root->info = newnode->info;
        root->left = NULL;
        root->right = NULL;
        cout << "\nRoot Node is Added\n" << endl;
        return;
    }
    //check to see if the node is already in the tree
    if (tree->info == newnode->info)
    {
        cout << "\nElement already in the tree\n" << endl;
        return;
    }
    // if key is less than root go to left subtree
    if (tree->info > newnode->info)
    {
        if (tree->left != NULL)
        {
            insert(tree->left, newnode);
        }
        else
        {
            // keep going to the left if smaller than rest of nodes
            tree->left = newnode;
            (tree->left)->left = NULL;
            (tree->left)->right = NULL;
            cout << "\nNode Added To Left\n" << endl;
            return;
        }
    }
    else
    {
        // if key is more than root go to right subtree
        if (tree->right != NULL)
        {
            insert(tree->right, newnode);
        }
        else
        {
            // keep going to the right if larger than rest of nodes
            tree->right = newnode;
            (tree->right)->left = NULL;
            (tree->right)->right = NULL;
            cout << "\nNode Added To Right\n" << endl;
            return;
        }
    }
}

//Deletion
//pre:  BST class and the struct "node" for the node pointers must exist. File in must exist, as well as the insertion function to populate BST and
// find function must exist to check if requested node is in the BST
//post: Now we can remove (delete) a node from the BST recursively with this function.
void BST::deletion(int item)
{
    //initialize parent and location pointers
    node *parent, *location;
    // if there is no root then the tree is empty, nothing to delete
    if (root == NULL)
    {
        cout << "\nTree empty\n" << endl;
        return;
    }
    // call find function to check and see if the node is in the BST
    find(item, &parent, &location);
    // if the node isn't node then alert user
    if (location == NULL)
    {
        cout << "\nItem not present in tree\n" << endl;
        return;
    }
    // move the nodes to get ready to delete the requested node
    if (location->left == NULL && location->right == NULL)
    {
        route1(parent, location);
    }
    if (location->left != NULL && location->right == NULL)
    {
        route2(parent, location);
    }
    if (location->left == NULL && location->right != NULL)
    {
        route2(parent, location);
    }
    if (location->left != NULL && location->right != NULL)
    {
        route3(parent, location);
    }
     // delete the node
    free(location);
    cout << "\nDeletion successful\n " << endl;
}
//***********************************************************************************************
//              Utility Functions for moving nodes for Deletion Function
//
//***********************************************************************************************
//route1
//pre: BST class and the struct "node" for the node pointers must exist. File in must exist, as well as the insertion function to populate BST and
// find function must exist to check if requested node is in the BST, deletion function must exist
//post: This function sets all to NULL if there parent and location are both NULL
void BST::route1(node *parent, node *location )
{
    // set all to NULL if parent is null
    if (parent == NULL)
    {
        root = NULL;
    }
    else
    {
        if (location == parent->left)
            parent->left = NULL;
        else
            parent->right = NULL;
    }
}

//route2
//pre: BST class and the struct "node" for the node pointers must exist. File in must exist, as well as the insertion function to populate BST and
// find function must exist to check if requested node is in the BST, deletion function must exist
//post: This function switches the parents and children nodes
void BST::route2(node *parent, node *location)
{
    //initialize a pointer for the child node
    node *child;
    // child is left
    if (location->left != NULL)
        child = location->left;
    else
        //child is right
        child = location->right;
    //if no root, then make the child the root
    if (parent == NULL)
    {
        root = child;
    }
    else
    {
        // switch the parent and child if parent if left
        if (location == parent->left)
            parent->left = child;
        else
            // switch the parent and child if parent if right
        if (location == parent->left)
            parent->right = child;
    }
}

//route3
//pre: BST class and the struct "node" for the node pointers must exist. File in must exist, as well as the insertion function to populate BST and
// find function must exist to check if requested node is in the BST, deletion function must exist
//post: This function moves the nodes to the right places in order to get ready to delete the requested node since both sides of the tree are populated.
void BST::route3(node *parent, node *location)
{
    //initialize some pointers, one to use, one to store, one to store if good spot and one to store if parent is in a good spot
    node *ptr, *ptr2, *good, *parentGood;
    //store the location
    ptr2 = location;
    // set the using pointer to the right
    ptr = location->right;
    // while not NULL, store the using pointer and then go left
    while (ptr->left != NULL)
    {
        ptr2 = ptr;
        ptr = ptr->left;
    }
    //good spot so store it
    good = ptr;
    // set the good spot for the parent with the last stored spot
    parentGood = ptr2;
    // if good spot left is NULL  AND Good spot right is NULL, follow route 1 because it deals with the complete NULL case
    if (good->left == NULL && good->right == NULL)
    {
        route1(parentGood, good);
    }
    // use route 2 to switch the spots
    else
    {
        route2(parentGood, good);
    }
     // if the parent is NULL now, Set root the the good spot
    if (parent == NULL)
    {
        root = good;
    }
    else
    {
        // if the location now is the left parent then good
        if (location == parent->left)
        {
            parent->left = good;
        }
         // else then the right parent is good
        else
        {
            parent->right = good;
        }
    }
    // move current location to the good spots for both sides
    good->left = location->left;
    good->right = location->right;
}

//preorder traversal
//pre: BST class and the struct "node" for the node pointers must exist. File in must exist, as well as the insertion function to populate BST
//post: We can now do a preorder traversal (can print in descending order) through recursion
void BST::preorder(node *ptr)
{
    if (root == NULL)
    {
        cout << "\nTree is empty\n" << endl;
        return;
    }
    if (ptr != NULL)
    {
        cout<<ptr->info<<"  ";
        preorder(ptr->left);
        preorder(ptr->right);
    }
}
//reverse inorder traversal
//pre: BST class and the struct "node" for the node pointers must exist. File in must exist, as well as the insertion function to populate BST
//post: We can now do a reverse inorder traversal (can print in descending order) through recursion
void BST::reverseInorder(node *ptr)
{
    if (root == NULL)
    {
        cout << "\nTree is empty\n" << endl;
        return;
    }
    if (ptr != NULL)
    {
        reverseInorder(ptr->right);
        cout<<ptr->info<<"  ";
        reverseInorder(ptr->left);
    }
}
//inorder traversal
//pre: BST class and the struct "node" for the node pointers must exist. File in must exist, as well as the insertion function to populate BST
//post: We can now do an inorder traversal through recursion
void BST::inorder(node *ptr)
{
    if (root == NULL)
    {
        cout << "\nTree is empty\n" << endl;
        return;
    }
    if (ptr != NULL)
    {
        inorder(ptr->left);
        cout<<ptr->info<<"  ";
        inorder(ptr->right);
    }
}
//postorder traversal
//pre: BST class and the struct "node" for the node pointers must exist. File in must exist, as well as the insertion function to populate BST
//post: We can now do a postorder traversal (can print in descending order) through recursion
void BST::postorder(node *ptr)
{
    if (root == NULL)
    {
        cout << "\nTree is empty\n" << endl;
        return;
    }
    if (ptr != NULL)
    {
        postorder(ptr->left);
        postorder(ptr->right);
        cout << ptr->info <<"  ";
    }
}

// Display the Tree
//pre: BST class and the struct "node" for the node pointers must exist. File in must exist, as well as the insertion function to populate BST
//post: We can now print the BST in a horizontal format using recursion to show the way the nodes are stored.
void BST::display(node *ptr, int level)
{
    // as long as its not NULL
    if (ptr != NULL)
    {
        // left side of the tree
        display(ptr->right, level+1);
        cout << endl;
        if (ptr == root)
            cout << "Root:  ";
        else
        {
            for (int i = 0;i < level;i++)
            {
                cout <<"       ";
            }

        }
        //right side of tree
        cout <<ptr->info;
        cout << "--->";
        display(ptr->left, level+1);
    }
}

// function to find the sum of nodes on the
// longest path from root to leaf node
//pre: BST class and the struct "node" for the node pointers must exist. File in must exist, as well as the insertion function to populate BST
//post: We can now calculate the sum of the nodes on the most expensive path with this function using recursion.
void BST::sumOfLongRootToLeafPath(node* root, int sum, int len, int& maxLen, int& maxSum)
{
   // if true, then we have traversed a
   // root to leaf path
   if (!root) {
       // update maximum length and maximum sum
       // according to the given conditions
       if (maxLen < len) {
           maxLen = len;
           maxSum = sum;
       } else if (maxLen == len && maxSum < sum)
           maxSum = sum;
       return;
   }
   // recur for left subtree
   sumOfLongRootToLeafPath(root->left, sum + root->info,
                           len + 1, maxLen, maxSum);

   // recur for right subtree
   sumOfLongRootToLeafPath(root->right, sum + root->info,
                           len + 1, maxLen, maxSum);
}

// utility function to find the sum of nodes on
// the longest path from root to leaf node
//pre: BST class and the struct "node" for the node pointers must exist. File in must exist, as well as the insertion function to populate BST
//post: We can use this utility to help the sumOfLongRootToLeafPath function to calculate the sum of the nodes on the most expensive path.
int BST::sumOfLongRootToLeafPathUtil(node* root)
{
   // if tree is NULL, then sum is 0
   if (!root)
       return 0;

   int maxSum = INT_MIN, maxLen = 0;

   // finding the maximum sum 'maxSum' for the
   // maximum length root to leaf path
   sumOfLongRootToLeafPath(root, 0, 0, maxLen, maxSum);

   // required maximum sum
   return maxSum;
}
