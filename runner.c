/**
*  AVL Tree 'Data To CSV Runner' Implementation.
 *
 * @author: Aliya Salmanova
 * @class: CS 5008
 * @term: Fall 2025
 */

#include <stdio.h>
#include <stdlib.h>
#include "avl.h"



void logToCSV(const char* fileName, int(*getVal)(int)){

    //open file in write mode to delete everything from it
    FILE *data = fopen(fileName, "w");

    //edge case
    if (data == NULL) {
        printf("Error opening file with w!\n");
        return; 
    }
    //overwrite with empty string and close
    fprintf(data, "");
    fclose(data);

    //now open sale file in append mode
    data = fopen(fileName, "a");
    //edge case
    if (data == NULL) {
        printf("Error opening file with a!\n");
        return; 
    }

    //set longs for total operations counts
    long totalSearchOps = 0;
    long totalBalanceOps = 0;

    Node *avlTree = NULL;

    //header for csv files
    fprintf(data, "N, Search Ops, Balance Ops\n");

    for (int i = 1; i <= 1000; i++){
        
        //get value by calling passed in function
        int currVal = getVal(i);

        //set variables for search operations
        long searchOps = 0;
        long balanceOps = 0;
        
        //insert node to tree
        avlTree = insertToAVLTree(avlTree, createNode(currVal), &searchOps, &balanceOps);

        //add operations counts to totals
        totalSearchOps += searchOps;
        totalBalanceOps += balanceOps;

        //log operations into file, separated by comments and go to next line at the end
        fprintf(data, "%d, ", i);
        fprintf(data, "%ld, ", totalSearchOps);
        fprintf(data, "%ld", totalBalanceOps);
        fprintf(data, "\n");

        //reset just in case, though we don't necessarily need this as we reinstantiate operations every iteration
        searchOps = 0;
        balanceOps = 0;
    }

    //free memory!
    freeTree(avlTree);

    //close file to avoid leaks
    fclose(data);
}

//callback functions:

//ascending will return just i
int getSameNum(int i){
    return i;
}

//descending will return 1000 - i
int getDifference(int i){
    return 1000 - i;
}

//random, not related to i but needs same parameter type as other callback funcs
int getRandomNum(int i){
    return (rand() % 1000) + 1;
}


int main(int argc, char *argv[]){

    //run logToCSV function passing in file with corresponding callback function for our 3 variations
    logToCSV("ascendingNodeValues.csv", getSameNum);
    logToCSV("descendingNodeValues.csv", getDifference);
    logToCSV("randomNodeValues.csv", getRandomNum);

    return 0;
}