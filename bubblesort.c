/* アルゴリズムとデータ構造I */
/* 課題1 3J13 久保隼人 */

#include <stdio.h>
#include <time.h>

#define NUM 1000000

int data[NUM];

int BubbleSort(int data[], int size) {
    int i,j,tmp,count=0;
    for(i=size-1;i>0;i--){
        for(j=0;j<i;j++){                                  
            if(data[j] < data[j+1]){                            
                tmp = data[j];
                data[j] = data[j+1];
                data[j+1] = tmp;
                count++;
            }
        }
    }
    return count;
} 

int main(){
    // Your code here!
    clock_t start, end;
    FILE *fp;
    char filename[256];
    int i,size,count;
    
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
    count = BubbleSort(data, size);
    end = clock();
    
    printf("ソート後\n");
    for(i=0;i<size;i++){
        printf("%d\n",data[i]);
    }
    
    printf("交換回数=%d",count);
    printf("time=%d(ms)\n", end-start);
    
    return 0;
}
