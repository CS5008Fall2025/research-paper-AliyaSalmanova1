/**
*  AVL Tree Tests Implementation.
 *
 * @author: Aliya Salmanova
 * @class: CS 5008
 * @term: Fall 2025
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "avl.h"


const int mediumArrayLength = 9;

/* helper function that recursively checks if all branches of tree are balanced */
bool isBalanced(Node *tree){
    //base case
	if (tree == NULL) return true;
    
    //if tree isn't balanced, return false
	int balance = getBalance(tree);
	if (balance < -1 || balance > 1) return false;

    //to return true, left and right side have to be balanced - recursing downward
	return (isBalanced(tree->left) && isBalanced(tree->right));
}

/* helper function that returns whether val was found in tree or not */
bool contains(Node *tree, int val){
    //edge case - if we have traversed the whole branch without finding, return false
    if (tree == NULL) return false;
    //if found
    if (tree->val == val) return true;
    //return whether any branch return true
    return (contains(tree->left, val) || contains(tree->right, val));
}

/* helper function to dynamically create tree of 3 nodes */
Node *makeSmallTree(int nodeVal1, int nodeVal2, int nodeVal3){

    //create nodes based on vals passed into function
    Node *node1 = createNode(nodeVal1);
    Node *node2 = createNode(nodeVal2);
    Node *node3 = createNode(nodeVal3);

    //arguments required in insertToAVLTree function as it counts search and balanace operations 
    long a = 0;
    long b = 0;    
    
    Node *avlTree = NULL;

    //add all nodes to avl tree
    avlTree = insertToAVLTree(avlTree, node1, &a, &b);
    avlTree = insertToAVLTree(avlTree, node2, &a, &b);
    avlTree = insertToAVLTree(avlTree, node3, &a, &b);
    
    return avlTree;
}


/* helper function to dynamically create bigger tree from array of node values */
Node *makeMediumTree(int *valArray, int arrayLength){

    Node *avlTree = NULL;

    //arguments required for counting operations
    long a = 0;
    long b = 0;   

    //looop through val array
	for (int i = 0; i < arrayLength; i++){
        //for each val, create node and insert to tree
		Node *nodeToInsert = createNode(valArray[i]);
	    avlTree = insertToAVLTree(avlTree, nodeToInsert, &a, &b);

        //reset integers for accuracy, though this doesn't matter for our tests 
	    a = 0;
	    b = 0;
	}
    return avlTree;
}


/* helper function to test insert function for small trees given 3 vals - 1, 2, 3 in any order */
int smallTreeTestHelper(int nodeVal1, int nodeVal2, int nodeVal3){

    //create tree
    Node *avlTree = makeSmallTree(nodeVal1, nodeVal2, nodeVal3);

	int result = 0;

   //2 has to be centered, 1 on the left and 3 on the right
    if (avlTree->val != 2) result = -1;
    if (avlTree->left == NULL) result = -1;
    if (avlTree->left->val != 1) result = -1;
    if (avlTree->right == NULL) result = -1;
    if (avlTree->right->val != 3) result = -1;

    //check heights
	if (avlTree->left->height != 1) result = -1;
	if (avlTree->right->height != 1) result = -1;
	if (avlTree->height != 2) result = -1;
	
    //free memory!
	freeTree(avlTree);

    return result;   
}


/* helper function to test insert function for medium trees */
int mediumTreeTestHelper(int *valArray, int arrayLength){

    //make tree
	Node *avlTree = makeMediumTree(valArray, arrayLength);
	
	int result = 0;

    //check if tree is balanced 
    if (!isBalanced(avlTree)) result = -1;

    //free memory!
	freeTree(avlTree);

    return result;   
}

/* helper function to test deleting right node from tree of 1, 2, and 3 */
int deleteRightNodeInSmallTreeHelper(int nodeVal1, int nodeVal2, int nodeVal3, int nodeValToDelete){
    
    //make tree
    Node *avlTree = makeSmallTree(nodeVal1, nodeVal2, nodeVal3);
    
    //delete node
    Node *nodeToDelete = createNode(nodeValToDelete);
    avlTree = deleteFromAVLTree(avlTree, nodeToDelete, 0);

	int result = 0;

    //if val is still in tree, test has to fail!
    if (contains(avlTree, nodeToDelete->val)) result = -1;

    //center val has to be 2 - make sure it is not null before checking
    if (avlTree == NULL) result = -1;
    if (avlTree->val != 2) result = -1;
    //left val has to be 1 - make sure it is not null before checking
    if (avlTree->left == NULL) result = -1;
    else if (avlTree->left->val != 1) result = -1;
    //right has to be null
    if (avlTree->right != NULL) result = -1;
    
    //tree must be balanced
    if (!isBalanced(avlTree)) result = -1;
	
    //free memory!
	freeTree(avlTree);

    return result;   
}

/* helper function to test deleting left node from tree of 1, 2, and 3 */
int deleteLeftNodeInSmallTreeHelper(int nodeVal1, int nodeVal2, int nodeVal3, int nodeValToDelete){
    
    //make tree
    Node *avlTree = makeSmallTree(nodeVal1, nodeVal2, nodeVal3);
    
    //delete node
    Node *nodeToDelete = createNode(nodeValToDelete);
    avlTree = deleteFromAVLTree(avlTree, nodeToDelete, 0);

	int result = 0;

    //if val is still in tree, test has to fail!
    if (contains(avlTree, nodeToDelete->val)) result = -1;

    //center val has to be 2 - make sure it is not null before checking
    if (avlTree == NULL) result = -1;
    if (avlTree->val != 2) result = -1;
    //right val has to be 3 - make sure it is not null before checking
    if (avlTree->right == NULL) result = -1;
    else if (avlTree->right->val != 3) result = -1;
    //left val must be null
    if (avlTree->left != NULL) result = -1;

    //tree must be balanced - this checks for correct heights
    if (!isBalanced(avlTree)) result = -1;
	
    //free memory!
	freeTree(avlTree);

    return result;   
}

/* helper function to test deleting center node from tree of 1, 2, and 3 */
int deleteMidNodeInSmallTreeHelper(int nodeVal1, int nodeVal2, int nodeVal3, int nodeValToDelete){
    
    //make tree
    Node *avlTree = makeSmallTree(nodeVal1, nodeVal2, nodeVal3);
    

    //delete node
    long a = 0; // for operations
    Node *nodeToDelete = createNode(nodeValToDelete);
    avlTree = deleteFromAVLTree(avlTree, nodeToDelete, &a);

	int result = 0;
    
    if (contains(avlTree, nodeToDelete->val)) result = -1;
    //center val has to be 3 - make sure it is not null before checking
    if (avlTree == NULL) result = -1;
    if (avlTree->val != 3) result = -1;
    //left val has to be 1 - make sure it is not null before checking
    if (avlTree->left == NULL) result = -1;
    else if (avlTree->left->val != 1) result = -1;
    //right node must be null
    if (avlTree->right != NULL) result = -1;
    if (!isBalanced(avlTree)) result = -1;
	
    //free memory!
	freeTree(avlTree);

    return result;   
}

/* helper function to test deleting node from medium tree given array */
int deleteNodeInMediumTreeHelper(int *valArray, int arrayLength, int nodeValToDelete){

    //make tree
	Node *avlTree = makeMediumTree(valArray, arrayLength);

    //delete node
    long a = 0; //for ops count
    Node *nodeToDelete = createNode(nodeValToDelete);
    avlTree = deleteFromAVLTree(avlTree, nodeToDelete, &a);
	
	int result = 0;

    //check if tree is balanced 
    if (!isBalanced(avlTree)) result = -1;
    //tree should node contain deleted value
    if (contains(avlTree, nodeToDelete->val)) result = -1;

    //free memory!
	freeTree(avlTree);

    return result;   
}

/* helper function to test deleting center node from medium tree given array */
int deleteMidNodeInMediumTreeHelper(int *valArray, int arrayLength){

    //make tree
	Node *avlTree = makeMediumTree(valArray, arrayLength);

    //delete root node
    long a = 0; //for ops count
    int deletedNodeVal = avlTree->val;
    avlTree = deleteFromAVLTree(avlTree, avlTree, &a);
	
	int result = 0;

    //check if tree is balanced 
    if (!isBalanced(avlTree)) result = -1;
    //tree should node contain deleted value
    if (contains(avlTree, deletedNodeVal)) result = -1;

    //free memory!
	freeTree(avlTree);

    return result;   
}

//call small tree helper passing in ascending 1,2,3
int testRRbalancingOnSmallTree(){
    return smallTreeTestHelper(1, 2, 3);
}

//call small tree helper passing in descending 3,2,1
int testLLbalancingOnSmallTree(){
    return smallTreeTestHelper(3, 2, 1);
}

//call small tree helper passing in ascending 1,3 then descend to 2
int testRLbalancingOnSmallTree(){
    return smallTreeTestHelper(1, 3, 2);
}

//call small tree helper passing in descending 3,1 then ascend to 2
int testLRbalancingOnSmallTree(){
    return smallTreeTestHelper(3, 1, 2);
}

//call medium tree test helper passing in ascending 1-9
int testRRBalancingOnMediumTree(){
    return mediumTreeTestHelper((int []){1, 2, 3, 4, 5, 6, 7, 8, 9}, mediumArrayLength);
}

//call medium tree test helper passing in descending 9-1
int testLLBalancingOnMediumTree(){
    return mediumTreeTestHelper((int []){9, 8, 7, 6, 5, 4, 3, 2, 1}, mediumArrayLength);
}

//call medium tree test helper passing ascending numbers and then descending numbers
int testRLBalancingOnMediumTree(){
    return mediumTreeTestHelper((int []){1, 3, 5, 7, 9, 8, 6, 4, 2}, mediumArrayLength);
}

//call medium tree test helper passing descending numbers and then ascending numbers
int testLRBalancingOnMediumTree(){
    return mediumTreeTestHelper((int []){9, 8, 6, 4, 2, 1, 3, 5, 7}, mediumArrayLength);
}

//call deleteRightNodeInSmallTreeHelper and delete 3, which would be on the right
int deleteRightNodeInSmallTree(){
    return deleteRightNodeInSmallTreeHelper(1, 2, 3, 3);
}

//call deleteRightNodeInSmallTreeHelper and delete 1, which would be on the left
int deleteLeftNodeInSmallTree(){
    return deleteLeftNodeInSmallTreeHelper(1, 2, 3, 1);
}

//call deleteRightNodeInSmallTreeHelper and delete 2, which would be centered
int deleteMidNodeInSmallTree(){
    return deleteMidNodeInSmallTreeHelper(1, 2, 3, 2);
}

//delete a node on the right of medium tree
int deleteRightNodeInMedTree(){
    return deleteNodeInMediumTreeHelper((int []){1, 2, 3, 4, 5, 6, 7, 8, 9}, mediumArrayLength, 8);
}

//delete a node on the left of medium tree
int deleteLeftNodeInMedTree(){
    return deleteNodeInMediumTreeHelper((int []){1, 2, 3, 4, 5, 6, 7, 8, 9}, mediumArrayLength, 2);
}

//call deleteMidNodeInMediumTreeHelper
int deleteMidNodeInMedTree(){
    return deleteMidNodeInMediumTreeHelper((int []){1, 2, 3, 4, 5, 6, 7, 8, 9}, mediumArrayLength);
}

//test find function using a small tree
int testFindNodeInSmallTree(){
    //mkae tree
    Node *avlTree = makeSmallTree(1, 2, 3);

    int result = 0;

    //find 1 
    Node *nodeToFind = createNode(1);
    Node *foundNode = findNode(avlTree, nodeToFind);
    //should be found and not null
    if (foundNode == NULL) result = -1;
    else if (foundNode->val != 1) result = -1;

    //find 2
    nodeToFind = createNode(2);
    foundNode = findNode(avlTree, nodeToFind);
    //should be found and not null
    if (foundNode == NULL) result = -1;
    else if (foundNode->val != 2) result = -1;

    //find 3
    nodeToFind = createNode(3);
    foundNode = findNode(avlTree, nodeToFind);
    //should be found and not null
    if (foundNode == NULL) result = -1;
    else if (foundNode->val != 3) result = -1;

    //find 4 which doesn't exist in tree
    nodeToFind = createNode(4);
    foundNode = findNode(avlTree, nodeToFind);
    //should be null!
    if (foundNode != NULL) result = -1;

    //free memory!
    freeTree(avlTree);

    return result;
}

//test find function using a medium tree
int testFindNodeInMedTree(){
    
    //make tree
    Node *avlTree = makeMediumTree((int []){1, 2, 3, 4, 5, 6, 7, 8, 9}, mediumArrayLength);

    int result = 0;

    //find 7
    Node *nodeToFind = createNode(7);
    Node *foundNode = findNode(avlTree, nodeToFind);
    //should be found and not null
    if (foundNode == NULL) result = -1;
    else if (foundNode->val != 7) result = -1;

    //find 2
    nodeToFind = createNode(2);
    foundNode = findNode(avlTree, nodeToFind);
    //should be found and not null
    if (foundNode == NULL) result = -1;
    else if (foundNode->val != 2) result = -1;

    //find 5
    nodeToFind = createNode(5);
    foundNode = findNode(avlTree, nodeToFind);
    //should be found and not null
    if (foundNode == NULL) result = -1;
    else if (foundNode->val != 5) result = -1;

    //find 4 which doesn't exist in tree
    nodeToFind = createNode(10);
    foundNode = findNode(avlTree, nodeToFind);
    //should be null!
    if (foundNode != NULL) result = -1;

    //free memory!
    freeTree(avlTree);

    return result;
}


//array of function definitions
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

//array of names of the test functions
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

    //find number of tests by dividing sixe of testFunctions array by size of a function
    int numOfTests = (sizeof(testFunctions) / sizeof(testFunctions[0]));

    //loop through tests
    for (int i = 0; i < numOfTests; i++){
        
        //if result of test is -1, print that test failed, if 0, it passed
        int result = testFunctions[i]();
        if (result == -1) printf("Test %s failed\n", testFunctionNames[i]);
        else if (result == 0) printf("Test %s passed\n", testFunctionNames[i]);
    }
    return 1;

}