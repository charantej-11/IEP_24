#include <stdio.h>
#include <limits.h>

void printOptimalParenthesization(int start_index, int end_index, int optimalSplit[30][30], char *matrixName) {
    if (start_index == end_index) {
        printf("%c", (*matrixName)++);
        return;
    }
    printf("(");
    printOptimalParenthesization(start_index, optimalSplit[start_index][end_index], optimalSplit, matrixName);
    printOptimalParenthesization(optimalSplit[start_index][end_index] + 1, end_index, optimalSplit, matrixName);
    printf(")");
}
int main() {
    int numMatrices, i, j, k, chainLength;
    int dimensions[30]; 
    int minCosts[30][30];
    int optimalSplits[30][30]; 
    
    printf("Enter number of matrices: ");
    scanf("%d", &numMatrices);

    printf("Enter dimensions (p[0] p[1] ... p[n]):\n");
    for (i = 0; i <= numMatrices; i++) {
        scanf("%d", &dimensions[i]);
    }
    for (i = 1; i <= numMatrices; i++) {
        minCosts[i][i] = 0;
    }
    for (chainLength = 2; chainLength <= numMatrices; chainLength++) {
        for (i = 1; i <= numMatrices - chainLength + 1; i++) {
            j = i + chainLength - 1;
            minCosts[i][j] = INT_MAX; 

            for (k = i; k < j; k++) {
                int currentCost = minCosts[i][k] + minCosts[k + 1][j] + dimensions[i-1] * dimensions[k] * dimensions[j];
                if (currentCost < minCosts[i][j]) {
                    minCosts[i][j] = currentCost;
                    optimalSplits[i][j] = k;
                }
            }
        }
    }
    char matrixLabel = 'A';
    printf("Optimal Parenthesization: ");
    printOptimalParenthesization(1, numMatrices, optimalSplits, &matrixLabel);
    printf("\nMinimum number of multiplications: %d\n", minCosts[1][numMatrices]);
    return 0;
}
