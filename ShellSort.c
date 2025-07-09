/* アルゴリズムとデータ構造I */
/* 課題3 3J13 久保隼人 */

#include <stdio.h>
#include <time.h>

#define NUM 1000000

int data[NUM];

int makeh(int size){
    int h=1;
    while(h<size){
        h = h*3+1;
    }
    h = (h-1)/3;
    return h;
}

unsigned int ShellSort(int data[], int size) {
    int i,j,k,h,tmp,num,pos;
    unsigned int count=0;
    h = makeh(size);
    while(h>=1){
        for(i=0;i<h;i++){
            if(data[i]<data[i+h]){
                tmp=data[i];
                data[i]=data[i+h];
                data[i+h]=tmp;
                count+=3;
            }
            for(j=2;j<=size/h;j++){
                pos=(h*j)+i;
                num=j;
                for(k=j-1;k>=0;k--){
                    if(data[(h*k)+i]<data[(h*j)+i]){
                        pos=(h*k)+i;
                        num=k;
                    }
                }
                tmp=data[(h*j)+i];
                for(k=j;k>num;k--){
                    data[(h*k)+i]=data[(h*(k-1))+i];
                    count++;
                }
                data[pos]=tmp;
                count+=2;
            }
        }
        h = (h-1)/3;
    }
    return count;
}

int main(){
    clock_t start, end;
    FILE *fp;
    char filename[256];
    int i,size;
    unsigned int count;
    
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
    count = ShellSort(data, size);
    end = clock();
    
    printf("ソート後\n");
    for(i=0;i<size;i++){
        printf("%d\n",data[i]);
    }
    
    printf("time=%d(ms)\n", end-start);
    printf("移動回数=%u\n",count);
    
    return 0;
}
