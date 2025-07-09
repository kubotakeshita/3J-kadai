/* アルゴリズムとデータ構造I */
/* 課題3 3J13 久保隼人 */

#include <stdio.h>
#include <time.h>

#define NUM 1000000

int data[NUM];

void InsertSort(int data[], int size) {
    int i,j,tmp,num,pos;
    if(data[0]<data[1]){
        tmp=data[0];
        data[0]=data[1];
        data[1]=tmp;
    }
    for(i=2;i<size;i++){
        pos=i;
        for(j=i-1;j>=0;j--){
            if(data[j]<data[i]){
                pos=j;
            }
        }
        tmp=data[i];
        for(j=i;j>pos;j--){
            data[j]=data[j-1];
        }
        data[pos]=tmp;
    }
}

int main(){
    clock_t start, end;
    FILE *fp;
    char filename[256];
    int i,size;
    
    printf("ファイル名を入力→");                            //ファイルを開く
    gets(filename);                                          //1-サンプルデータ100万件.txt
    fp = fopen(filename,"r");
    if (fp==NULL) {
        printf("can't open a file\n");
        exit (1);
    }
    printf("読み込むデータ量を入力→");                      //読み込むデータ量を決める
    scanf("%d",&size);
    for(i=0;i<size;i++){
        fscanf(fp,"%d",&data[i]);
    }
    fclose(fp);       
    
    printf("ソート前\n");
    for(i=0;i<size;i++){
        printf("%d\n",data[i]);
    }
    printf("\n");
    
    start = clock();
    InsertSort(data, size);
    end = clock();
    
    printf("ソート後\n");
    for(i=0;i<size;i++){
        printf("%d\n",data[i]);
    }
    
    printf("time=%d(ms)\n", end-start);
    
    return 0;
}
