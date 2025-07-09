#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define	TRUE	1	/* ノードが訪問済の場合のvisited[]の値 */
#define	FALSE	0	/* ノードが未訪問の場合のvisited[]の値 */
#define	MAXSIZE	11	/* ノードの数(最大数) */

/*
 *	隣接リストを構成するためのセル構造体
 */
typedef struct _Cell {
	int				no ;	/* ノードの固有番号 名前A～Kが0～10に対応 */
	char			name ;	/* ノードの名前(アルファベット1文字) */
	struct _Cell	*next ;	/* 次のノードへのポインタ */
} Cell ;

char *GraphData[] = {
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

Cell	*adjacent[MAXSIZE] ;	/* 隣接リスト */
int		visited[MAXSIZE] ;		/* 訪問済フラグ */
int		path[MAXSIZE] ;			/* 経路．スタックとして利用 */

/*
 *	隣接リストを表示
 */
void PrintAdjList( void )
{
	int		i ;
	Cell	*c ;

	printf( "隣接リスト\n" ) ;

	for(i = 0;i < MAXSIZE;i++){
		c = adjacent[i];
		printf("[%c]",'A' + i);
		while(c != NULL){
			printf(" -> %c",c->name);
			c = c->next;
		}
		printf("\n");
	}
}


/*
 *	データの追加：parent番のノードの隣接先としてchildを追加
 */
void Add( int parent, int child )
{
	Cell *p, *q ;

	p = (Cell*)malloc( sizeof(Cell) ) ;
	p->no = child ;
	p->name = 'A' + child ;
	p->next = NULL ;

	if( adjacent[parent] == NULL ) {
		adjacent[parent] = p ;
		return ;
	}

	q = adjacent[parent] ;
	while( q->next != NULL ) {
		q = q->next ;
	}
	q->next = p ;
}


/*
 *	グラフの初期化：GraphDataをadjacent[]に代入する
 */
void InitGraph( void )
{
	int	i, j, tmp;

	for(i = 0;i < MAXSIZE;i++){
		j = 0;
		while(GraphData[i][j] != '\0'){
			int tmp = GraphData[i][j] - 'A';
			Add(i,tmp);
			j++;
		}
	}
	

	PrintAdjList( ) ;
}


/*
 *	スタックpath[]の初期化
 */
void InitStack( )
{
	int i ;

	for( i = 0 ; i < MAXSIZE ; i++ ) {
		path[i] = -1 ;
	}
}


/*
 *	path[]にデータをプッシュ
 */
void PushPath( int no )
{
	int i = 0 ;

	while( path[i] != -1 ) i++ ;

	if( i >= MAXSIZE ) {
		printf( "Stack Oerflow\n" ) ;
		return ;
	}
	path[i] = no ;
}


/*
 *	path[]のデータをポップ
 */
int PopPath( )
{
	int i = 0, no ;

	while( path[i] != -1 && i < MAXSIZE ) i++ ;

	no = path[--i] ;
	path[i] = -1 ;

	return no ;
}


/*
 *	探索した経路を表示
 */
void PrintPath( )
{
	int	i = 0 ;

	printf("[PATH] A");
	while(path[i] > -1 && i < MAXSIZE){
		printf(" %c", path[i] + 'A');
		i++;
	}
	printf("\n");
}


/*
 *	経路探索 現在の注目ノード(now)からゴール(end)までの経路を探索
 */
void Search( int now, int end )
{
	Cell	*p ;

	visited[now] = TRUE;
	if(now != 0)PushPath(now);
	if(now == end)PrintPath();
	else{
		p = adjacent[now];
		while(p != NULL){
			if(visited[p->no] != TRUE)Search(p->no,end);
			p = p->next;
		}
	}
	PopPath();
	visited[now] = FALSE;
}


/*
 *	メイン関数
 */
int main( void )
{
	InitStack( ) ;
	InitGraph( ) ;
	printf( "探索結果\n" ) ;
	Search( 0, 10 ) ;	/* AからK(0から10)への経路 */
	return 0 ;
}

/*実行結果
>backtrack.exe
隣接リスト
[A] -> C -> I
[B] -> D -> G -> H
[C] -> A -> D -> G
[D] -> B -> C -> H -> I -> J
[E] -> F -> H -> J
[F] -> E -> G -> K
[G] -> B -> C -> F
[H] -> B -> D -> E -> J
[I] -> A -> D
[J] -> D -> E -> H -> K
[K] -> F -> J
探索結果
[PATH] A C D B G F E H J K
[PATH] A C D B G F E J K
[PATH] A C D B G F K
[PATH] A C D B H E F K
[PATH] A C D B H E J K
[PATH] A C D B H J E F K
[PATH] A C D B H J K
[PATH] A C D H B G F E J K
[PATH] A C D H B G F K
[PATH] A C D H E F K
[PATH] A C D H E J K
[PATH] A C D H J E F K
[PATH] A C D H J K
[PATH] A C D J E F K
[PATH] A C D J E H B G F K
[PATH] A C D J H B G F K
[PATH] A C D J H E F K
[PATH] A C D J K
[PATH] A C G B D H E F K
[PATH] A C G B D H E J K
[PATH] A C G B D H J E F K
[PATH] A C G B D H J K
[PATH] A C G B D J E F K
[PATH] A C G B D J H E F K
[PATH] A C G B D J K
[PATH] A C G B H D J E F K
[PATH] A C G B H D J K
[PATH] A C G B H E F K
[PATH] A C G B H E J K
[PATH] A C G B H J E F K
[PATH] A C G B H J K
[PATH] A C G F E H B D J K
[PATH] A C G F E H D J K
[PATH] A C G F E H J K
[PATH] A C G F E J K
[PATH] A C G F K
[PATH] A I D B G F E H J K
[PATH] A I D B G F E J K
[PATH] A I D B G F K
[PATH] A I D B H E F K
[PATH] A I D B H E J K
[PATH] A I D B H J E F K
[PATH] A I D B H J K
[PATH] A I D C G B H E F K
[PATH] A I D C G B H E J K
[PATH] A I D C G B H J E F K
[PATH] A I D C G B H J K
[PATH] A I D C G F E H J K
[PATH] A I D C G F E J K
[PATH] A I D C G F K
[PATH] A I D H B G F E J K
[PATH] A I D H B G F K
[PATH] A I D H E F K
[PATH] A I D H E J K
[PATH] A I D H J E F K
[PATH] A I D H J K
[PATH] A I D J E F K
[PATH] A I D J E H B G F K
[PATH] A I D J H B G F K
[PATH] A I D J H E F K
[PATH] A I D J K
*/