
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

bool contains(Node *tree, int val){
    if (tree == NULL) return false;
    if (tree->val == val) return true;
    return (contains(tree->left, val) || contains(tree->right, val));
}

Node *makeSmallTree(int nodeVal1, int nodeVal2, int nodeVal3){

    Node *node1 = createNode(nodeVal1);
    Node *node2 = createNode(nodeVal2);
    Node *node3 = createNode(nodeVal3);

    long a = 0;
    long b = 0;    
    
    Node *avlTree = NULL;

    avlTree = insertToAVLTree(avlTree, node1, &a, &b);
    avlTree = insertToAVLTree(avlTree, node2, &a, &b);
    avlTree = insertToAVLTree(avlTree, node3, &a, &b);
 
    
    return avlTree;
}

Node *makeMediumTree(int *valArray, int arrayLength){

    Node **nodeArray = (Node **)malloc(sizeof(Node *) * arrayLength);

	for (int i = 0; i < arrayLength; i++){
		nodeArray[i] = createNode(valArray[i]);
	}

    long a = 0;
    long b = 0;   
 
    Node *avlTree = NULL;

	for (int i = 0; i < arrayLength; i++){
		avlTree = insertToAVLTree(avlTree, nodeArray[i], &a, &b);
	}

    return avlTree;
}


int smallTreeTestHelper(int nodeVal1, int nodeVal2, int nodeVal3){

    Node *avlTree = makeSmallTree(nodeVal1, nodeVal2, nodeVal3);

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



int mediumTreeTestHelper(int *valArray, int arrayLength){

	Node *avlTree = makeMediumTree(valArray, arrayLength);
	
	int result = 0;

    if (!isBalanced(avlTree)) result = -1;

	freeTree(avlTree);

    return result;   
}


int deleteRightNodeInSmallTreeHelper(int nodeVal1, int nodeVal2, int nodeVal3, int nodeValToDelete){
    
    Node *avlTree = makeSmallTree(nodeVal1, nodeVal2, nodeVal3);
    
    Node *nodeToDelete = createNode(nodeValToDelete);

    avlTree = deleteFromAVLTree(avlTree, nodeToDelete, 0);

	int result = 0;

    if (contains(avlTree, nodeToDelete->val)) result = -1;
    if (avlTree == NULL) result = -1;
    if (avlTree->val != 2) result = -1;
    if (avlTree->left == NULL) result = -1;
    else if (avlTree->left->val != 1) result = -1;
    if (avlTree->right != NULL) result = -1;
    if (!isBalanced(avlTree)) result = -1;
	
	freeTree(avlTree);

    return result;   
}

int deleteLeftNodeInSmallTreeHelper(int nodeVal1, int nodeVal2, int nodeVal3, int nodeValToDelete){
    
    Node *avlTree = makeSmallTree(nodeVal1, nodeVal2, nodeVal3);
    
    Node *nodeToDelete = createNode(nodeValToDelete);

    avlTree = deleteFromAVLTree(avlTree, nodeToDelete, 0);

	int result = 0;

    if (contains(avlTree, nodeToDelete->val)) result = -1;
    if (avlTree == NULL) result = -1;
    if (avlTree->val != 2) result = -1;
    if (avlTree->left != NULL) result = -1;
    if (avlTree->right == NULL) result = -1;
    else if (avlTree->right->val != 3) result = -1;
    if (!isBalanced(avlTree)) result = -1;
	
	freeTree(avlTree);

    return result;   
}

int deleteMidNodeInSmallTreeHelper(int nodeVal1, int nodeVal2, int nodeVal3, int nodeValToDelete){
    
    Node *avlTree = makeSmallTree(nodeVal1, nodeVal2, nodeVal3);
    
    Node *nodeToDelete = createNode(nodeValToDelete);

    avlTree = deleteFromAVLTree(avlTree, nodeToDelete, 0);

	int result = 0;

    if (contains(avlTree, nodeToDelete->val)) result = -1;
    if (avlTree == NULL) result = -1;
    if (avlTree->val != 3) result = -1;
    if (avlTree->right != NULL) result = -1;
    if (avlTree->left == NULL) result = -1;
    else if (avlTree->left->val != 1) result = -1;
    if (!isBalanced(avlTree)) result = -1;
	
	freeTree(avlTree);

    return result;   
}

int deleteNodeInMediumTreeHelper(int *valArray, int arrayLength, int nodeValToDelete){

	Node *avlTree = makeMediumTree(valArray, arrayLength);

    Node *nodeToDelete = createNode(nodeValToDelete);

    avlTree = deleteFromAVLTree(avlTree, nodeToDelete, 0);
	
	int result = 0;

    if (!isBalanced(avlTree)) result = -1;
    if (contains(avlTree, nodeToDelete->val)) result = -1;

	freeTree(avlTree);

    return result;   
}

int deleteMidNodeInMediumTreeHelper(int *valArray, int arrayLength){

	Node *avlTree = makeMediumTree(valArray, arrayLength);

    long a = 0;

    int deletedNodeVal = avlTree->val;
    avlTree = deleteFromAVLTree(avlTree, avlTree, &a);
	
	int result = 0;

    if (!isBalanced(avlTree)) result = -1;
    if (contains(avlTree, deletedNodeVal)) result = -1;

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

int deleteRightNodeInSmallTree(){
    return deleteRightNodeInSmallTreeHelper(1, 2, 3, 3);
}

int deleteLeftNodeInSmallTree(){
    return deleteLeftNodeInSmallTreeHelper(1, 2, 3, 1);
}

int deleteMidNodeInSmallTree(){
    return deleteMidNodeInSmallTreeHelper(1, 2, 3, 2);
}

int deleteLeftNodeInMedTree(){
    return deleteNodeInMediumTreeHelper((int []){1, 2, 3, 4, 5, 6, 7, 8, 9}, mediumArrayLength, 8);
}

int deleteRightNodeInMedTree(){
    return deleteNodeInMediumTreeHelper((int []){1, 2, 3, 4, 5, 6, 7, 8, 9}, mediumArrayLength, 2);
}

int deleteMidNodeInMedTree(){
    return deleteMidNodeInMediumTreeHelper((int []){1, 2, 3, 4, 5, 6, 7, 8, 9}, mediumArrayLength);
}

int testFindNodeInSmallTree(){
    Node *avlTree = makeSmallTree(1, 2, 3);

    int result = 0;

    Node *nodeToFind = createNode(1);
    Node *foundNode = findNode(avlTree, nodeToFind);
    if (foundNode == NULL) result = -1;
    else if (foundNode->val != 1) result = -1;

    nodeToFind = createNode(2);
    foundNode = findNode(avlTree, nodeToFind);
    if (foundNode == NULL) result = -1;
    else if (foundNode->val != 2) result = -1;

    nodeToFind = createNode(3);
    foundNode = findNode(avlTree, nodeToFind);
    if (foundNode == NULL) result = -1;
    else if (foundNode->val != 3) result = -1;

    nodeToFind = createNode(4);
    foundNode = findNode(avlTree, nodeToFind);
    if (foundNode != NULL) result = -1;

    return result;
}

int testFindNodeInMedTree(){
    
    Node *avlTree = makeMediumTree((int []){1, 2, 3, 4, 5, 6, 7, 8, 9}, mediumArrayLength);

    int result = 0;

    Node *nodeToFind = createNode(7);
    Node *foundNode = findNode(avlTree, nodeToFind);
    if (foundNode == NULL) result = -1;
    else if (foundNode->val != 7) result = -1;

    nodeToFind = createNode(2);
    foundNode = findNode(avlTree, nodeToFind);
    if (foundNode == NULL) result = -1;
    else if (foundNode->val != 2) result = -1;

    nodeToFind = createNode(5);
    foundNode = findNode(avlTree, nodeToFind);
    if (foundNode == NULL) result = -1;
    else if (foundNode->val != 5) result = -1;

    nodeToFind = createNode(10);
    foundNode = findNode(avlTree, nodeToFind);
    if (foundNode != NULL) result = -1;

    return result;
}



int(*testFunctions[])(void) = {
    testLLbalancingOnSmallTree,
    testRRbalancingOnSmallTree,
    testLRbalancingOnSmallTree,
    testRLbalancingOnSmallTree,
	testRRBalancingOnMediumTree,
    testLLBalancingOnMediumTree,
    testRLBalancingOnMediumTree,
    testLRBalancingOnMediumTree,
    deleteLeftNodeInSmallTree,
    deleteRightNodeInSmallTree,
    deleteMidNodeInSmallTree,
    deleteLeftNodeInMedTree,
    deleteRightNodeInMedTree,
    deleteMidNodeInMedTree,
    testFindNodeInSmallTree,
    testFindNodeInMedTree
};

char *testFunctionNames[] = {
    "testLLbalancingOnSmallTree",
    "testRRbalancingOnSmallTree",
    "testLRbalancingOnSmallTree",
    "testRLbalancingOnSmallTree",
	"testRRBalancingOnMediumTree",
    "testLLBalancingOnMediumTree",
    "testRLBalancingOnMediumTree",
    "testLRBalancingOnMediumTree",
    "deleteLeftNodeInSmallTree",
    "deleteRightNodeInSmallTree",
    "deleteMidNodeInSmallTree",
    "deleteLeftNodeInMedTree",
    "deleteRightNodeInMedTree",
    "deleteMidNodeInMedTree",
    "testFindNodeInSmallTree",
    "testFindNodeInMedTree"
};



int main(int argc, char *argv[]){

    int numOfTests = (sizeof(testFunctions) / sizeof(testFunctions[0]));

    for (int i = 0; i < numOfTests; i++){
        
        int result = testFunctions[i]();
        if (result == -1) printf("Test %s failed\n", testFunctionNames[i]);
        else if (result == 0) printf("Test %s passed\n", testFunctionNames[i]);
    }
    return 1;

}