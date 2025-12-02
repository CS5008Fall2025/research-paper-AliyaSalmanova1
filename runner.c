
#include <stdio.h>
#include "avl.h"

char *dataCsv = "data.csv";

void logToCSV(){
    FILE *data = fopen(dataCsv, "w");
    if (data == NULL) {
        printf("Error opening file with w!\n");
        return; 
    }

    fprintf(data, "");

    fclose(data);


    data = fopen(dataCsv, "a");
    if (data == NULL) {
        printf("Error opening file with a!\n");
        return; 
    }

    long totalSearchOps = 0;
    long totalBalanceOps = 0;

    Node *avlTree = NULL;


    fprintf(data, "N, Search Ops, Balance Ops\n");

    for (int i = 1; i <= 1000; i++){
        long searchOps = 0;
        long balanceOps = 0;
        
        avlTree = insertToAVLTree(avlTree, createNode(i), &searchOps, &balanceOps);

        totalSearchOps += searchOps;
        totalBalanceOps += balanceOps;

        fprintf(data, "%d", i);
        fprintf(data, " ");
        fprintf(data, "%ld", totalSearchOps);
        fprintf(data, " ");
        fprintf(data, "%ld", totalBalanceOps);
        fprintf(data, "\n");

        searchOps = 0;
        balanceOps = 0;
    }

    fclose(data);
}

int main(int argc, char *argv[]){
    logToCSV();
    //logToCSV("ascendingNodeValues.csv");
    //logToCSV("descendingNodeValues.csv");
    //logToCSV("randomNodeValues.csv");
}