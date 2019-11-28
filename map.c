#include <stdio.h>
#include <stdlib.h>
#include "map.h"

int main(){
    int edge[][3] = {
        {0,12,1},
        {0,16,5},
        {0,14,6},
        {1,10,2},
        {1,7,5},
        {2,3,3},
        {2,5,4},
        {2,6,5},
        {3,4,4},
        {4,2,5},
        {4,8,6},
        {5,9,6}};
    char * name[] = {"a", "b", "c", "d", "e", "f", "g"};
    char * infor[] = {"a", "b", "c", "d", "e", "f", "g"};
    pForm form = fillForm(name, infor, edge, 7, 12);
    char** road = findMin(form,3,0);
    showMatrix(form);
    printf("%s\n",road[0]);
    getRoads(3,0,form,0,0);
    return 0;
}