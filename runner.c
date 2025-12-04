
#include <stdio.h>
#include "avl.h"

char *dataCsv = "data.csv";

void logToCSV(const char* fileName, int(*getVal)(int)){

    FILE *data = fopen(fileName, "w");
    if (data == NULL) {
        printf("Error opening file with w!\n");
        return; 
    }

    fprintf(data, "");

    fclose(data);

    data = fopen(fileName, "a");
    if (data == NULL) {
        printf("Error opening file with a!\n");
        return; 
    }

    long totalSearchOps = 0;
    long totalBalanceOps = 0;

    Node *avlTree = NULL;


    fprintf(data, "N, Search Ops, Balance Ops\n");

    for (int i = 1; i <= 1000; i++){

        int currVal = getVal(i);

        long searchOps = 0;
        long balanceOps = 0;
        
        avlTree = insertToAVLTree(avlTree, createNode(currVal), &searchOps, &balanceOps);

        totalSearchOps += searchOps;
        totalBalanceOps += balanceOps;

        fprintf(data, "%d, ", i);
        fprintf(data, "%ld, ", totalSearchOps);
        fprintf(data, "%ld", totalBalanceOps);
        fprintf(data, "\n");

        searchOps = 0;
        balanceOps = 0;
    }

    

    fclose(data);
}

int getSameNum(int i){
    return i;
}

int getDifference(int i){
    return 1000 - i;
}

int getRandomNum(int i){
    return (rand() % 1000) + 1;
}


int main(int argc, char *argv[]){

    logToCSV("ascendingNodeValues.csv", getSameNum);
    logToCSV("descendingNodeValues.csv", getDifference);
    logToCSV("randomNodeValues.csv", getRandomNum);

}