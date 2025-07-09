#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

#define	SIZE	13		/* ノード数 */
#define	FIXED	1		/* ノードに対する最短経路が決定済 */
#define UNFIXED	0		/* ノードに対する最短経路が未定 */
#define	UNDEF	-1		/* 未定義ノード．ノードが定義されていない状態を表す */
#define IMAX	INT_MAX	/* int型データの最大値 */

/* 隣接行列 */
int Adjacent[SIZE][SIZE] = {
	/* A    B    C    D    E    F    G    H    I    J    K    L    M */
	{   0,  30,IMAX,  40,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX},	// A: 東京
	{  30,   0,  90,  60, 140,  80,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX},	// B: 埼玉
	{IMAX,  90,   0,IMAX,IMAX, 110, 330, 240,IMAX,IMAX,IMAX,IMAX,IMAX},	// C: 群馬
	{  40,  60,IMAX,   0, 130,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX},	// D: 千葉
	{IMAX, 140,IMAX, 130,   0, 100, 260,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX},	// E: 茨城
	{IMAX,  80, 110,IMAX, 100,   0, 170,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX},	// F: 栃木
	{IMAX,IMAX, 330,IMAX, 260, 170,   0, 550,  80,  90,IMAX,IMAX,IMAX},	// G: 福島
	{IMAX,IMAX, 240,IMAX,IMAX,IMAX, 550,   0, 630,IMAX,IMAX,IMAX,IMAX},	// H: 新潟
	{IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,  80, 630,   0,  60, 190,IMAX,IMAX},	// I: 山形
	{IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,  90,IMAX,  60,   0, 290, 180,IMAX},	// J: 宮城
	{IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX, 190, 290,   0, 110, 300},	// K: 秋田
	{IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX, 180, 110,   0, 190},	// L: 岩手
	{IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX, 300, 190,   0}	// M: 青森
} ;

char *GraphData[] = {	/* ノード名．上記隣接行列の0～12番目の各要素に対応 */
	"Tokyo",
	"Saitama",
	"Gunma",
	"Chiba",
	"Ibaraki",
	"Tochigi",
	"Fukushima",
	"Niigata",
	"Yamagata",
	"Miyagi",
	"Akita",
	"Iwate",
	"Aomori"
} ;

int	Cost[SIZE] ;	/* 各ノードまでの最短経路のコスト */
int Fixed[SIZE] ;	/* 各ノードに対する最短経路が決定しているかどうかを表す */
int	Prev[SIZE] ;	/* 最短経路における１つ前のノード */

/*
 *	各ノードについて，最短経路における直前のノードとコストを表示
 */
void PrintCost( void )
{
	int i;
	for(i = 0; i < SIZE; i++){
		printf("ノード %s 直前のノード %s コスト %d\n", GraphData[i], GraphData[Prev[i]], Cost[i]);
	}
}


/*
 *	Dijkstra法
 */
void Dijkstra( int start )
{
	int i, min = IMAX, num = -1;

	for(i = 0; i < SIZE; i++){
		if(Adjacent[start][i] != IMAX){						//隣接している
			if(Fixed[i] == UNFIXED){						//最短経路が確定していない
				if(Cost[i] > Cost[start] + Adjacent[start][i]){	//コストを比較
					Cost[i] = Cost[start] + Adjacent[start][i];
					Prev[i] = start;
				}
			}
		}
	}
	for(i = 0; i < SIZE; i++){
		if(Fixed[i] == UNFIXED){
			if(Cost[i] < min){
				min = Cost[i];
				num = i;
			}
		}
	}

	if(num == -1) return;
	Fixed[num] = FIXED;
	
	Dijkstra(num);
}


/*
 *	startからgoalまでの経路と最小コストを出力する
 */
void PrintPath( int start, int goal )
{
	int path[SIZE], i, num;
	for(i = 0; i < SIZE; i++){
		path[i] = -1;
	}
	
	num = Prev[goal];
	i = SIZE - 1;
	while(num != start){
		path[i] = num;
		num = Prev[num];
		i--;
	}
	
	printf("[%s]->", GraphData[start]);
	for(i = 0; i < SIZE; i++){
		if(path[i] != -1){
			printf("[%s]->", GraphData[path[i]]);
		}
	}
	printf("[%s]: Cost=%d\n", GraphData[goal], Cost[goal]);
}


/*
 *	メイン関数
 */
int main( void )
{
	int		start ;			/* 出発地点 */
	int		goal ;			/* 到着地点 */
	int		i ;

	/*
	 *	都県情報の表示
	 */
	for( i = 0 ; i < SIZE ; i++ ) {
		printf( "%2d: %s\n", i, GraphData[i] ) ;
	}

	/*
	 *	出発地点及び到着地点の入力
	 */
	printf( "出発地点を入力してください：" ) ;
	scanf( "%d", &start ) ;
	printf( "到着地点を入力してください：" ) ;
	scanf( "%d", &goal ) ;

	/*
	 *	Dijkstra法による経路探索
	 */
	for(i = 0; i < SIZE; i++){
		Cost[i] = IMAX;
		Prev[i] = UNDEF;
		Fixed[i] = UNFIXED;
	}
	Cost[start] = Adjacent[start][start];
	Prev[start] = start;
	Fixed[start] = FIXED;
	Dijkstra( start );

	/*
	 *	各ノードについて，最短経路における1つ前のノードと最短経路コストを表示
	 */
	PrintCost( ) ;

	/*
	 *	startからgoalまでの最短経路と，そのコストを表示
	 */
	PrintPath( start, goal ) ;

	return 0;
}

/*
>dijkstra.exe
 0: Tokyo
 1: Saitama
 2: Gunma
 3: Chiba
 4: Ibaraki
 5: Tochigi
 6: Fukushima
 7: Niigata
 8: Yamagata
 9: Miyagi
10: Akita
11: Iwate
12: Aomori
出発地点を入力してください：1
到着地点を入力してください：10
ノード Tokyo 直前のノード Saitama コスト 30
ノード Saitama 直前のノード Saitama コスト 0
ノード Gunma 直前のノード Saitama コスト 90
ノード Chiba 直前のノード Saitama コスト 60
ノード Ibaraki 直前のノード Saitama コスト 140
ノード Tochigi 直前のノード Saitama コスト 80
ノード Fukushima 直前のノード Tochigi コスト 250
ノード Niigata 直前のノード Gunma コスト 330
ノード Yamagata 直前のノード Fukushima コスト 330
ノード Miyagi 直前のノード Fukushima コスト 340
ノード Akita 直前のノード Yamagata コスト 520
ノード Iwate 直前のノード Miyagi コスト 520
ノード Aomori 直前のノード Iwate コスト 710
[Saitama]->[Tochigi]->[Fukushima]->[Yamagata]->[Akita]: Cost=520

*/