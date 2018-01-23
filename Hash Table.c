//Just for easy..
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct words{
    char word[10];
    char context[100];
}wordTable;

int num = 0;
unsigned int hashArray[0xffff] = {0,};                              //for file read/write

unsigned int HashEncrypt(char* word){
    int length = strlen(word);
    unsigned int hashNum = 0;
    for(unsigned int i = 0;i < length;i++){
        if(i % 2 == 0){
            hashNum ^= ((word[i] - 'A') << 8) ^ i;
        }else{
            hashNum ^= (word[i] - 'A') ^ i;
        }
    }
    return hashNum;
}

int FromFileInputWords(wordTable* words){
    wordTable subData = {"\0","\0"};
    int size = sizeof(wordTable);
    FILE *Textfp = NULL;
    FILE *Hashfp = NULL;
    Textfp = fopen("E:\\workspace\\wordtable.txt","rb");
    Hashfp = fopen("E:\\workspace\\hash.txt","r");
    if(Textfp == NULL || Hashfp == NULL){
        return 0;
    }
    while(getc(Textfp) != EOF){
        fseek(Textfp,-1,1);
        fread(&subData,size,1,Textfp);
        fscanf(Hashfp,"%d",&hashArray[num]);
        fgetc(Hashfp);
        if(num < 0xffff){
            memcpy((words + hashArray[num++]),&subData,size);
        }else{
            printf("The Array is full!!\n");
        }
    }
    fclose(Textfp);
    fclose(Hashfp);
    return 1;
}

void FillTable(wordTable* words){
    int choice,subHash;
    wordTable subData;
    int size = sizeof(wordTable);
    while(1){
        if(num >= 0xffff){
            printf("This Array is full!\n");
            return;
        }
        printf("Please input the word:\n");
        fgets(subData.word,10,stdin);
        if(subData.word[strlen(subData.word) - 1] == '\n'){
            subData.word[strlen(subData.word) - 1] = '\0';
        }
        subHash = HashEncrypt(subData.word);
        if(words[subHash].word[0] != '\0'){
            printf("Conflicting!!\n");
            return;
        }
        printf("Now please input the context of this word:\n");
        fgets(subData.context,100,stdin);
        if(subData.context[strlen(subData.context) - 1] == '\n'){
            subData.context[strlen(subData.context) - 1] = '\0';
        }
        memcpy(words + subHash,&subData,size);
        hashArray[num++] = subHash;
        printf("1.Continue       2.Break\n");
        if(scanf("%d",&choice),choice == 2){                    //No judge.Easy Best!
            getchar();
            break;
        }
        getchar();
    }
}

void SearchTable(wordTable* words){
    char word[10];
    int loc = 0;
    printf("Please input the word which you want to search:\n");
    fgets(word,10,stdin);
    if(word[strlen(word) - 1] == '\n'){
        word[strlen(word) - 1] = '\0';
    }
    if(loc = HashEncrypt(word),*(words[loc].word) != '\0'){
        printf("This word's meaning is %s\n",words[loc].context);
    }else{
        printf("No this word here.\n");
    }
}

void PutWordsIntoFile(const wordTable* words){
    int size = sizeof(wordTable);
    FILE *Textfp = NULL;
    FILE *Hashfp = NULL;
    Textfp = fopen("E:\\workspace\\wordtable.txt","wb+");
    Hashfp = fopen("E:\\workspace\\hash.txt","wt+");
    if(Textfp == NULL || Hashfp == NULL){
        return;
    }
    for(int i = 0;i < num;i++){
        fwrite(words + hashArray[i],size,1,Textfp);
        fprintf(Hashfp,"%d",hashArray[i]);
        fputc('\n',Hashfp);
    }
    fclose(Textfp);
    fclose(Hashfp);
}

int main(){
    int choice;
    wordTable* words = (wordTable*)malloc(sizeof(wordTable) * 0xffff);
    memset(words,0,sizeof(wordTable) * 0xffff);
    if(!FromFileInputWords(words)){
        printf("Load File failed!!!\n");
        return 0;
    }
    while(1){
        printf("Welcome to the dic!\n");
        printf("Please choose the fuc which you would like to use:\n");
        printf("1.Fill the dic             2.Search\n");
        printf("3.Exit\n");
retry:
        scanf("%d",&choice);
        getchar();
        switch(choice){
            case 1:
                FillTable(words);
                break;
            case 2:
                SearchTable(words);
                break;
            case 3:
                printf("Looking forward to the next time\n");
                goto end;
            default:
                printf("Please input the right num\n");
                goto retry;
        }
    }
end:
    PutWordsIntoFile(words);
    system("pause");
    return 0;
}