/* アルゴリズムとデータ構造I */
/* 課題9 3J13 久保隼人 */

#include <stdio.h>
#include <time.h>

#define NUM 1000000

int data[NUM];
int L[NUM/2],R[NUM/2];

void Merge(int data[],int left,int right){
	int m,i,j,k;
	m=(left+right)/2;
	for(i=0;i<m+1;i++){
		L[i]=data[left+i];
	}
	for(j=0;j<right-m;j++){
		R[j]=data[m+1+j];
	}
	i=0,j=0;
	for(k=left;k<right+1;k++){
		if(L[i]>R[j] && i<m+1){
			data[k]=L[i++];
		}else {
			data[k]=R[j++];
		}
	}
}

void MergeSort(int data[],int left,int right){
	int m,i;
	if(left==right) return;
	m=(left+right)/2;
	MergeSort(data,left,m);
	MergeSort(data,m+1,right);
	Merge(data,left,right);
}

int main(){
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
    MergeSort(data,0,size-1);
    end = clock();
    
    printf("ソート後\n");
    for(i=0;i<size;i++){
        printf("%d\n",data[i]);
    }
    
    //printf("交換回数=%d",count);
    printf("time=%d(ms)\n", end-start);
    
    return 0;
}
