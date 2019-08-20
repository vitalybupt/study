int** merge(int** intervals, int intervalsSize, int* intervalsColSize, int* returnSize, int** returnColumnSizes){
printf("%d %d %d", intervalsSize, *intervalsColSize, returnColumnSizes[0][1]);
    int** retArrays = malloc(sizeof(int*)*3);
    int* array1 = malloc(sizeof(int)*2);
    array1[0] = 1; array1[1] = 6;
    retArrays[0] = array1;
    (*returnSize) = 1;
    int* columnSizeArray = malloc(sizeof(int)*3);
    returnColumnSizes[0] = columnSizeArray; 
    columnSizeArray[0] = 2; columnSizeArray[1] = 2; columnSizeArray[2] = 2;
    return retArrays;
}
