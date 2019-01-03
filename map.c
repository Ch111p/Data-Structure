#include <stdio.h>
#include <stdlib.h>
#include "map.h"

int main(){
    int edge[][3] = {
        {0,2,1},
        {1,3,2},
        {2,1,3},
        {0,4,3}
    };
    char* name[] = {"a","b","c","d"};
    char* infor[] = {"a","b","c","d"};
    pForm form = fillForm(name,infor,edge,4,4);
    char** road = findMin(form,0,3);
    showMatrix(form);
    printf("%s\n",road[3]);
    getRoads(0,3,form,0,0);
    return 0;
}