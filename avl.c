#include <stdlib.h>
#include <stdio.h>

typedef struct Node{
    int val;
    struct Node *left;
    struct Node *right;
    int height;
    
} Node;


int getMax(int a, int b){
    if (a > b) return a;
    else return b;
}

int getHeight(Node *node){
    if (node == NULL) return 0;
    else return node->height;
}

int recalculateHeightOfTree(Node *tree){
    if (tree == NULL) return 0;
    return 1 + getMax(getHeight(tree->left), getHeight(tree->right));
}

int getBalance(Node *root){
    if (root == NULL) return 0;
    return getHeight(root->left) - getHeight(root->right);
}



//left left
Node *rightRotate(Node *newLeft){

    if (newLeft == NULL || newLeft->left == NULL){
        return newLeft;
    }
    Node *newMiddle = newLeft->left;
    Node *newRightOfLeft = newMiddle->right;
    newMiddle->right = newLeft;
    newLeft->left = newRightOfLeft;

    newLeft->height = 1 + getMax(getHeight(newLeft->left), getHeight(newLeft->right));
    newMiddle->height = 1 + getMax(getHeight(newMiddle->left), getHeight(newMiddle->right));
    
    return newMiddle;
}

//right right
Node *leftRotate(Node *newRight){

    if (newRight == NULL || newRight->right == NULL){
        return newRight;
    }
    Node *newMiddle = newRight->right;
    Node *newLeftOfRight = newMiddle->left;
    newMiddle->left = newRight;
    newRight->right = newLeftOfRight;
    
    newRight->height = 1 + getMax(getHeight(newRight->left), getHeight(newRight->right));
    newMiddle->height = 1 + getMax(getHeight(newMiddle->left), getHeight(newMiddle->right));

    return newMiddle;
}



Node *performTreeBalancing(Node *root){

    int balance = getBalance(root);
    int balanceOfLeft = getBalance(root->left);
    int balanceOfRight = getBalance(root->right);

    if (balance > 1 && balanceOfRight >= 0){
        return rightRotate(root);
    }
    else if (balance < -1 && balanceOfLeft >= 0){
        return leftRotate(root);
    }
    else if (balance > 1 && balanceOfRight <= 0){
        root->right = rightRotate(root->right);
        return leftRotate(root->right);
    }
    else if (balance < -1 && balanceOfLeft <= 0){
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    return root;
    
}

Node *insertToAVLTree(Node *tree, Node *nodeToInsert){
    if (tree == NULL || nodeToInsert == NULL) return nodeToInsert;

    if (nodeToInsert->val < tree->val){
        tree->left = insertToAVLTree(tree->left, nodeToInsert);
    } else if (nodeToInsert->val > tree->val){
        tree->right = insertToAVLTree(tree->right, nodeToInsert);  
    } else {
        return tree;
    }

    tree->height = recalculateHeightOfTree(tree);
    
    return performTreeBalancing(tree);

}

int main(int argc, char *argv[]){

}

