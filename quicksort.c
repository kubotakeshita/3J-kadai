/* アルゴリズムとデータ構造I */
/* 課題9 3J13 久保隼人 */

#include <stdio.h>
#include <time.h>

void QuickSort(int data[],int left,int right){
	int p,i,j,tmp;
	i=left+1;
	j=right;
	p=left;
	if(left>=right)return;
	while(i<j){
		while(data[i]>data[p])i++;
		while(data[j]<data[p])j--;
		if(i<j){
			tmp=data[i];
			data[i]=data[j];
			data[j]=tmp;
		}
	}
	tmp=data[p];
	data[p]=data[i-1];
	data[i-1]=tmp;
	p=i-1;
	QuickSort(data,left,p-1);
	QuickSort(data,p+1,right);
}

int main(){
    int *data ;
    data = (int*)malloc(sizeof(int)*10000000 ) ;
    if( data == NULL ) {
        fprintf( stderr, "error\n" ) ;
        return -1 ;
    }
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
    QuickSort(data,0,size-1);
    end = clock();
    
    printf("ソート後\n");
    for(i=0;i<size;i++){
        printf("%d\n",data[i]);
    }
    
    //printf("交換回数=%d",count);
    printf("time=%d(ms)\n", end-start);
    
    return 0;
}
