
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "avl.h"



const int mediumArrayLength = 9;

bool isBalanced(Node *tree){
	if (tree == NULL) return true;
	int balance = getBalance(tree);
	if (balance < -1 || balance > 1) return false;
	return (isBalanced(tree->left) && isBalanced(tree->right));
}


int smallTreeTestHelper(int nodeVal1, int nodeVal2, int nodeVal3){

    Node *node1 = createNode(nodeVal1);
    Node *node2 = createNode(nodeVal2);
    Node *node3 = createNode(nodeVal3);


    Node *avlTree = insertToAVLTree(NULL, node1, 0, 0);
    avlTree = insertToAVLTree(avlTree, node2, 0, 0);
    avlTree = insertToAVLTree(avlTree, node3, 0, 0);

	int result = 0;

    if (avlTree->val != 2) result = -1;
    if (avlTree->left == NULL) result = -1;
    if (avlTree->left->val != 1) result = -1;
    if (avlTree->right == NULL) result = -1;
    if (avlTree->right->val != 3) result = -1;
	if (avlTree->left->height != 1) result = -1;
	if (avlTree->right->height != 1) result = -1;
	if (avlTree->height != 2) result = -1;
	
	freeTree(avlTree);

    return result;   
}

int testRRbalancingOnSmallTree(){
    return smallTreeTestHelper(1, 2, 3);
}

int testLLbalancingOnSmallTree(){
    return smallTreeTestHelper(3, 2, 1);
}

int testRLbalancingOnSmallTree(){
    return smallTreeTestHelper(1, 3, 2);
}

int testLRbalancingOnSmallTree(){
    return smallTreeTestHelper(3, 1, 2);
}

int mediumTreeTestHelper(int *valArray, int arrayLength){

	Node **nodeArray = (Node **)malloc(sizeof(Node *) * arrayLength);

	for (int i = 0; i < arrayLength; i++){
		nodeArray[i] = createNode(valArray[i]);
	}

    Node *avlTree = NULL;

	for (int i = 0; i < arrayLength; i++){
		avlTree = insertToAVLTree(avlTree, nodeArray[i], 0, 0);
	}
	
	int result = 0;

    if (!isBalanced(avlTree)) result = -1;

	freeTree(avlTree);

    return result;   
}


int testRRBalancingOnMediumTree(){

    return mediumTreeTestHelper((int []){1, 2, 3, 4, 5, 6, 7, 8, 9}, mediumArrayLength);
}

int testLLBalancingOnMediumTree(){

    return mediumTreeTestHelper((int []){9, 8, 7, 6, 5, 4, 3, 2, 1}, mediumArrayLength);
}

int testRLBalancingOnMediumTree(){

    return mediumTreeTestHelper((int []){1, 3, 5, 7, 9, 8, 6, 4, 2}, mediumArrayLength);
}

int testLRBalancingOnMediumTree(){

    return mediumTreeTestHelper((int []){9, 8, 6, 4, 2, 1, 3, 5, 7}, mediumArrayLength);
}


int deleteNodeInSmallTreeHelper(int nodeVal1, int nodeVal2, int nodeVal3, Node *nodeToDelete){
    /*
    Node *node1 = createNode(nodeVal1);
    Node *node2 = createNode(nodeVal2);
    Node *node3 = createNode(nodeVal3);


    Node *avlTree = insertToAVLTree(NULL, node1);
    avlTree = insertToAVLTree(avlTree, node2);
    avlTree = insertToAVLTree(avlTree, node3);
    */
	int result = 0;
    /*

    if (avlTree->val != 2) result = -1;
    if (avlTree->left == NULL) result = -1;
    if (avlTree->left->val != 1) result = -1;
    if (avlTree->right == NULL) result = -1;
    if (avlTree->right->val != 3) result = -1;
	if (avlTree->left->height != 1) result = -1;
	if (avlTree->right->height != 1) result = -1;
	if (avlTree->height != 2) result = -1;

	
	
	freeTree(avlTree);
    */

    return result;   

}

int(*testFunctions[])() = {
    testLLbalancingOnSmallTree,
    testRRbalancingOnSmallTree,
    testLRbalancingOnSmallTree,
    testRLbalancingOnSmallTree,
	testRRBalancingOnMediumTree,
    testLLBalancingOnMediumTree,
    testRLBalancingOnMediumTree,
    testLRBalancingOnMediumTree
};

char *testFunctionName[] = {
    "testLLbalancingOnSmallTree",
    "testRRbalancingOnSmallTree",
    "testLRbalancingOnSmallTree",
    "testRLbalancingOnSmallTree",
	"testRRBalancingOnMediumTree",
    "testLLBalancingOnMediumTree",
    "testRLBalancingOnMediumTree",
    "testLRBalancingOnMediumTree"
};

int main(){
    int numOfTests = (sizeof(testFunctions) / sizeof(testFunctions[0]));

    for (int i = 0; i < numOfTests; i++){
        int result = testFunctions[i]();
        if (result == -1) printf("Test %s failed\n", testFunctionName[i]);
        else if (result == 0) printf("Test %s passed\n", testFunctionName[i]);
    }

    return 1;
}