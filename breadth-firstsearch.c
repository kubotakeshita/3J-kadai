#include <stdio.h>
#include <string.h>

#define	TRUE	1
#define	FALSE	0
#define	MAXSIZE	11
#define	NONE	-1

char	*GraphData[] = {
	"CI",		/* A : C I */
	"DGH",		/* B : D G H */
	"ADG",		/* C : A D G */
	"BCHIJ",	/* D : B C H I J */
	"FHJ",		/* E : F H J */
	"EGK",		/* F : E G K */
	"BCF",		/* G : G C F */
	"BDEJ",		/* H : B D E J */
	"AD",		/* I : A D */
	"DEHK",		/* J : D E H K */
	"FJ"		/* K : F J */
} ;


/*
 * 隣接行列(adj)を表示する
 */
void	PrintAdjMatrix( int adj[MAXSIZE][MAXSIZE] )
{
	int	i, j ;

	printf( "[Adjacent Matrix]\n" ) ;
	for( i = 0 ; i < MAXSIZE ; i++ ) {
		for( j = 0 ; j < MAXSIZE ; j++ ) {
			printf( "%1d ", adj[i][j] ) ;
		}
		printf( "\n" ) ;
	}
	printf( "\n" ) ;
}


/*
 * グラフデータ(GraphData)から隣接行列(adj)を生成する
 */
void	InitGraph( int adj[MAXSIZE][MAXSIZE] )
{
	int i,j,k;
	for(i = 0;i < MAXSIZE;i++){
		for(j = 0;j < MAXSIZE;j++){
			adj[i][j] = 0;
		}
		k = 0;
		while(GraphData[i][k] != '\0'){
			adj[i][GraphData[i][k] - 'A'] = 1;
			k++;
		}
	}

	PrintAdjMatrix( adj ) ;
}


/*
 * キュー(q)を表示する
 */
void	PrintQueue( int *q )
{
	int		i ;

	printf( "[queue] { " ) ;
	for( i = 0 ; i < MAXSIZE ; i++ ) {
		if( q[i] != NONE ) {
			printf( "%c ", q[i]+'A' ) ;
		}
	}
	printf( "}\n" ) ;
}


/*
 * キュー(q)の中にデータ(d)が存在するかどうか確認する
 */
int	CheckQueue( int *q, int d )
{
	int		i ;

	for( i = 0 ; i < MAXSIZE ; i++ ) {
		if( q[i] == d ) return TRUE ;
	}
	return FALSE ;
}


/*
 * キュー(q)にデータ(d)を追加する
 */
void	Enqueue( int *q, int d )
{
	int		i ;
	for(i = 0;i < MAXSIZE;i++){
		if(q[i] == NONE){
			q[i] = d;
			return;
		}
	}
	printf("error!");
	return;
}


/*
 * キュー(q)からデータを取り除く
 */
int	Dequeue( int *q )
{
	int num,i;
	num = q[0];
	for(i = 0;i < MAXSIZE - 1;i++){
		q[i] = q[i+1];
	}
	q[i+1] = NONE;
	
	return num;
}


/*
 * 隣接行列(adj)を用いて，
 * 指定地点(now)からゴール(end)まで幅優先経路探索を行う
 */
void	Search( int adj[MAXSIZE][MAXSIZE], int now, int end )
{
	int visited[MAXSIZE] ;
	int queue[MAXSIZE] ;
	int i;
	
	for(i = 0;i < MAXSIZE;i++){
		queue[i] = NONE;
		visited[i] = FALSE;
	}

	Enqueue(queue,now);
	PrintQueue(queue);
	
	visited[now] = TRUE;
	
	if(queue[0] == NONE){
		printf("Found!\n");
		return;
	}
	while(now < MAXSIZE){
		now = Dequeue(queue);
		printf("[now] %c  ",'A' + now);
		for(i = 0;i < MAXSIZE;i++){
			if(adj[now][i] == 1){
				if(visited[i] == FALSE){
					visited[i] = TRUE;
					Enqueue(queue,i);
				}
			}
		}
		if(queue[0] == NONE){
			printf("Found!\n");
			return;
		}
		PrintQueue(queue);
	}
}


/*
 * メイン関数
 */
int main( void )
{
	int	adjacent[MAXSIZE][MAXSIZE] ;	/*隣接行列*/

	InitGraph( adjacent ) ;	/* 隣接行列の初期化 */
	Search( adjacent, 0, MAXSIZE-1 ) ;	/* A(0)からK(10)までの経路 */
	return 0 ;
}

/* 実行結果
>breadth-firstsearch.exe
[Adjacent Matrix]
0 0 1 0 0 0 0 0 1 0 0
0 0 0 1 0 0 1 1 0 0 0
1 0 0 1 0 0 1 0 0 0 0
0 1 1 0 0 0 0 1 1 1 0
0 0 0 0 0 1 0 1 0 1 0
0 0 0 0 1 0 1 0 0 0 1
0 1 1 0 0 1 0 0 0 0 0
0 1 0 1 1 0 0 0 0 1 0
1 0 0 1 0 0 0 0 0 0 0
0 0 0 1 1 0 0 1 0 0 1
0 0 0 0 0 1 0 0 0 1 0

[queue] { A }
[now] A  [queue] { C I }
[now] C  [queue] { I D G }
[now] I  [queue] { D G }
[now] D  [queue] { G B H J }
[now] G  [queue] { B H J F }
[now] B  [queue] { H J F }
[now] H  [queue] { J F E }
[now] J  [queue] { F E K }
[now] F  [queue] { E K }
[now] E  [queue] { K }
[now] K  Found!
*/