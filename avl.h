/**
 *  AVL Tree Implementation.
 *
 * @author: Aliya Salmanova
 * @class: CS 5008
 * @term: Fall 2025
 */


#include <stdlib.h>
#include <stdio.h>


/* nodes in tree should have a value, height, left, right */
typedef struct Node{
    int val;
    struct Node *left;
    struct Node *right;
    int height;  
} Node;


/* helper function to return the max of two ints */
int getMax(int a, int b){
    if (a > b) return a;
    else return b;
}

/* helper func - returns height of current node */
int getHeight(Node *node){
    // return 0 if null
    if (node == NULL) return 0;
    else return node->height;
}

/* helper function for if existing height was changed */
int recalculateHeightOfTree(Node *tree){
    //edge case - if tree is null height is 0
    if (tree == NULL) return 0;
    // get children's max height and add 1
    return 1 + getMax(getHeight(tree->left), getHeight(tree->right));
}

/* helper function */
int getBalance(Node *root){
    if (root == NULL) return 0;
    return getHeight(root->left) - getHeight(root->right);
}

/* helper function for deleting nodes - finds min node 
 (when you delete a node you find the min under its right child) */
Node *findMinNode(Node *tree){
    Node *curr = tree;
    if (curr == NULL) return curr;
    // traverse all the way left (until you hit null)
    while (curr->left != NULL){
        curr = curr->left;
    }
    return curr;
}

/* balancing function for 'left-left' case */
Node *rightRotate(Node *newRight, long *balanceOps){
    //edge case
    if (newRight == NULL || newRight->left == NULL){
        return newRight;
    }
    if (balanceOps != NULL) (*balanceOps)++;

    Node *newMiddle = newRight->left; //left child will now be middle child
    // save right of new middle child to avoid overwriting 
    Node *newLeftOfRight = newMiddle->right; 
    newMiddle->right = newRight; // make root node become left child
    newRight->left = newLeftOfRight; // set node we saved to be left of right node of root

    //change height of right node, then height of middle. order matters - lower node needs to be changed first
    newRight->height = 1 + getMax(getHeight(newRight->left), getHeight(newRight->right));
    newMiddle->height = 1 + getMax(getHeight(newMiddle->left), getHeight(newMiddle->right));
    
    return newMiddle;
}

/* balancing function for 'right-right' case */
Node *leftRotate(Node *newLeft, long *balanceOps){
    //edge case
    if (newLeft == NULL || newLeft->right == NULL){
        return newLeft;
    }
    if (balanceOps != NULL) (*balanceOps)++;
    
    Node *newMiddle = newLeft->right; //right child will now be middle child
    // save left of new middle child to avoid overwriting 
    Node *newRightOfLeft = newMiddle->left;
    newMiddle->left = newLeft; // make root node become right child
    newLeft->right = newRightOfLeft; // set node we saved to be right of left node of root
    
    //change height of left node, then height of middle. order matters - lower node needs to be changed first
    newLeft->height = 1 + getMax(getHeight(newLeft->left), getHeight(newLeft->right));
    newMiddle->height = 1 + getMax(getHeight(newMiddle->left), getHeight(newMiddle->right));

    return newMiddle;
}

/* important function for re-blancing tree */
Node *performTreeBalancing(Node *root, long *balanceOps){
    //edge case
    if (root == NULL) return root;

    //storing balance of root and both children
    int balance = getBalance(root);
    int balanceOfLeft = getBalance(root->left);
    int balanceOfRight = getBalance(root->right);

    // cheat sheet:
    // if balance if positive, tree is slanted left, if negative tree is slanted right

    //left-left case
    if (balance > 1 && balanceOfLeft >= 0){
        return rightRotate(root, balanceOps);
    }
    //right-right case
    else if (balance < -1 && balanceOfRight <= 0){
        return leftRotate(root, balanceOps);
    }
    //left-right case
    else if (balance > 1 && balanceOfLeft <= 0){
        //rotate left child to the left and then rotate root to the right
        root->left = leftRotate(root->left, balanceOps);
        return rightRotate(root, balanceOps);
    }
    //right-left case
    else if (balance < -1 && balanceOfRight >= 0){
        //rotate right child to the right and then rotate root to the left
        root->right = rightRotate(root->right, balanceOps);
        return leftRotate(root, balanceOps);
    }
    return root;
}

/* main function */
Node *insertToAVLTree(Node *tree, Node *nodeToInsert, long *searchOps, long *balanceOps){
    //base case & edge case
    if (tree == NULL || nodeToInsert == NULL) return nodeToInsert;

    //if node belongs on the left side of tree
    if (nodeToInsert->val < tree->val){
        if (searchOps != NULL) (*searchOps)++;
        tree->left = insertToAVLTree(tree->left, nodeToInsert, searchOps, balanceOps);
    } 
    //if node belongs on the right side of tree
    else if (nodeToInsert->val > tree->val){
        if (searchOps != NULL) (*searchOps)++;
        tree->right = insertToAVLTree(tree->right, nodeToInsert, searchOps, balanceOps);  
    } 
    //if node has equal val to root
    else {
        // free the unused node to avoid a leak
        free(nodeToInsert);
        return tree;
    }

    //as new node was inserted, update height
    tree->height = recalculateHeightOfTree(tree);
  
    //balance tree   
    return performTreeBalancing(tree, balanceOps);

}

/* deleting from tree */
Node *deleteFromAVLTree(Node *tree, Node *nodeToDelete, long *balanceOps){
    //if node not found in tree or node is null
    if (tree == NULL || nodeToDelete == NULL) return tree;

    // if node val is less than root val search left
    if (tree->val > nodeToDelete->val){
        tree->left = deleteFromAVLTree(tree->left, nodeToDelete, balanceOps);
    } 
    // if node val is greater than root val search left
    else if (tree->val < nodeToDelete->val){
        tree->right = deleteFromAVLTree(tree->right, nodeToDelete, balanceOps);
    } 
    //when/if node to delete is found
    else {
        //if node to delete has no left child, replace it with right child
        if (tree->left == NULL){
            //save right child, free tree, return right child
            Node *right = tree->right;
            free(tree); //avoid memory leak!
            return right;
        } 
        //if node to delete has no right child, replace it with left child
        else if (tree->right == NULL){
            //save left child, free tree, return left child
            Node *left = tree->left;
            free(tree); //avoid memory leak!
            return left;
        }
        //if node to delete has two children, replace it with min on right side
        else {      
            Node *minInRight = findMinNode(tree->right);
            tree->val = minInRight->val;
            tree->right = deleteFromAVLTree(tree->right, minInRight, balanceOps);
        }
    }

    //edge case if tree was deleted
    if (tree == NULL) return NULL;

    //as node was deleted, height changes - recalculate height
    tree->height = recalculateHeightOfTree(tree);
    
    //re-balance tree
    return performTreeBalancing(tree, balanceOps);

}

/* searching in tree */
Node *findNode(Node *tree, Node *nodeToFind){
    //if node not found in tree or node is null
    if (tree == NULL || nodeToFind == NULL) return NULL;

    // if node val is less than root val search left
    if (tree->val > nodeToFind->val){
        return findNode(tree->left, nodeToFind);
    } 
    // if node val is greater than root val search right
    else if (tree->val < nodeToFind->val){
        return findNode(tree->right, nodeToFind);
    } 

    //if found
    return tree;

}

/* helper function to create a node */
Node *createNode(int val){
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    node->height = 1; //initial height is 1
    return node;
}

/* helper function to recursively free whole tree */
void freeTree(Node *tree){
    //base case & edge case
	if (tree == NULL) return;

    //recursively traverse left and right 
	freeTree(tree->left);
	freeTree(tree->right);

	free(tree);
}



