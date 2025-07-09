/* アルゴリズムとデータ構造I */
/* 課題14 3J13 久保隼人 */
#include <stdio.h>
#include <time.h>

int BinSearch(int data[],int key,int left,int right){
	int mid;
	if(left==right){
		if(key==data[left])return left;
		else return -1;
	}
	mid=(left+right)/2;
	if(key==data[mid])return mid;
	if(key<data[mid]){
		right=mid-1;
	}else{
		left=mid+1;
	}
	BinSearch(data,key,left,right);
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
    int i,size,key,count,pos;
    size=10000000;
    printf("ファイル名を入力→");                            //ファイルを開く
    gets(filename);                                          //4-ソート済データ1000万件.txt
    fp = fopen(filename,"r");
    if (fp==NULL) {
        printf("can't open a file\n");
        exit (1);
    }
    for(i=0;i<size;i++){
        fscanf(fp,"%d",&data[i]);
    }
    printf("keyを入力→");                      //読み込むデータ量を決める
    scanf("%d",&key);
    fclose(fp);       
    
    /*printf("ソート前\n");
    for(i=0;i<size;i++){
        printf("%d\n",data[i]);
    }
    printf("\n");*/
    
    start = clock();
    pos=BinSearch(data,key,0,size-1);
    end = clock();
    
    /*printf("ソート後\n");
    for(i=0;i<size;i++){
        printf("%d\n",data[i]);
    }*/
    
    //printf("交換回数=%d",count);
    printf("keyの位置=%d\n",pos);
    //printf("time=%d(ms)\n", end-start);
    
    return 0;
}

/* 
	実行結果
	key=409210707 pos=3812863
	key=616950060 pos=-1
	key=878820736 pos=8184373
*/