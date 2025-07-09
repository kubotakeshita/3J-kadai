#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define	NAMELEN	16	/* 駅名の最大文字数．駅名はアルファベット表記とする */

/*
 *	駅情報を表す構造体
 */
typedef struct _Station {
	char	name[NAMELEN] ;		/* 駅名 */
	int		time ;				/* 隣(リストの1つ前の要素)からの所要時間 */
	struct _Station *next ;		/* 次の駅のデータへのポインタ */
} Station ;

Station	*head ;					/* 駅情報に関する線形リストの先頭アドレス */
int		StationNum = 0 ;		/* 線形リストに登録されている駅の数 */


/*
 *	キーボードから入力された番号を読み取る．
 *	読み取る数値は0以上の整数5桁までとする．
 */
int GetNum( void )
{
	int c=0, d=0, i ;

	rewind( stdin ) ;

	for( i = 0 ; i < 5 && c != '\n' ; i++ ) {
		c = getchar( ) ;
		if( c == '\n' ) break ;
		d = d * 10 + c - '0' ;
	}

	rewind( stdin ) ;
	return d ;
}

/*
 *	ファイルから初期のリストデータを読み込み
 *	*headを先頭とする線形リストを構成する．
 */
int ReadInitData( char *fn )
{
	FILE	*fp ;
	Station	*s, *tmp ;
	char	name[NAMELEN] ;
	int		time ;

	fp = fopen(fn,"r");
	if(fp==NULL){
		printf("can't open file\n");
		return -1;
	}
	head = (Station*)malloc(sizeof(Station));
	fscanf(fp,"%s\t%d",name,&time);
	strcpy(head->name,name);
	head->time = time;
	tmp = head;
	StationNum++;
	
	while(fscanf(fp,"%s\t%d",name,&time) != 0){
		tmp->next = (Station*)malloc(sizeof(Station));
		tmp = tmp->next;
		strcpy(head->name,name);
		head->time = time;
		StationNum++;
	}
	tmp->next=NULL;
	
	fclose( fp ) ;
	return 0 ;
}

/*
 *	線形リストを表示する
 */
void PrintList( void )
{
	Station	*s = head ;

	while( 1 ) {
		printf( "\t[name] %s, [time] %d, ", s->name, s->time ) ;
		printf( "[addr] %p, ", s ) ;
		if( s->next != NULL ) {
			printf( "[next] %s\n", s->next->name ) ;
		} else {
			printf( "[next] (null)\n" ) ;
			break ;
		}
		s = s->next ;
	}
}

/*
 *	引数で渡された駅名がリスト(*head)に存在するか確認する
 *	存在すればそのデータのポインタを，存在しなければNULLを返す．
 */
Station *ChkStation( char *target )
{
	Station *s = head ;

	while(s->next!=NULL){
		if(s->name==target)return s;
		s = s->next;
	}
	if(s->name==target)return s;
	return NULL;
}

/*
 *	データの追加
 *	キーボードから駅名，所要時間，追加位置を入力してもらい，
 *	リスト(*head)に追加する．
 */
void Add( void )
{
	Station *s, *ns ;
	char	name[NAMELEN] ;
	int		i ;

	ns = (Station*)malloc(sizeof(Station));
	printf("駅名を入力->");
	gets(ns->name);
	printf("所要時間を入力->");
	ns->time = GetNum();
	
	PrintList( ) ;

	do {
		printf( "どの駅の後に追加しますか？\n" ) ;
		printf( "NAME = " ) ;
		fgets( name, NAMELEN, stdin ) ;
		for( i = 0 ; name[i] != '\n' && i < NAMELEN - 1 ; i++ ) ;
		name[i] = '\0' ;
	} while( ( s = ChkStation( name ) ) == NULL ) ;

	ns->next =s->next;
	s->next = ns;
	StationNum++;

	PrintList( ) ;
}

/*
 *	データの削除
 */
void Del( void )
{
	Station *cur, *prev ;
	char	name[NAMELEN] ;
	int		i ;

	PrintList( ) ;

	do {
		printf( "どの駅を削除しますか？\n" ) ;
		printf( "NAME = " ) ;
		fgets( name, NAMELEN, stdin ) ;
		for( i = 0 ; name[i] != '\n' && i < NAMELEN - 1 ; i++ ) ;
		name[i] = '\0' ;
	} while( ( cur = ChkStation( name ) ) == NULL ) ;

	prev = head;
	while(prev!=head){
		prev=prev->next;
	}
	if(StationNum>1){
		prev->next=cur->next;
	}
	free(cur);

	PrintList( ) ;
}

/*
 *	所用時間の計算
 */
void Calc( void )
{
	Station *from, *to ;
	char	name[NAMELEN] ;
	int		sum = 0 ;
	int		i ;

	PrintList( ) ;

	do {
		printf( "どの駅からどの駅までの所要時間を計算しますか？\n" ) ;
		printf( "FROM = " ) ;
		fgets( name, NAMELEN, stdin ) ;
		for( i = 0 ; name[i] != '\n' && i < NAMELEN - 1 ; i++ ) ;
		name[i] = '\0' ;
	} while( ( from = ChkStation( name ) ) == NULL ) ;
	do {
		printf( "TO = " ) ;
		fgets( name, NAMELEN, stdin ) ;
		for( i = 0 ; name[i] != '\n' && i < NAMELEN - 1 ; i++ ) ;
		name[i] = '\0' ;
	} while( ( to = ChkStation( name ) ) == NULL ) ;

	printf( "%sから%sまでの所要時間は", from->name, to->name ) ;

	while(from!=to){
		from = from->next;
		sum += from->time;
	}
	
	printf( "%d分です\n", sum ) ;
}

/*
 *	メニューの表示
 */
int Menu( void )
{
	int		c ;

	while( 1 ) {
		printf( "1:表示,2:追加,3:削除,4:所要時間,5:終了 ==> " ) ;

		c = GetNum( ) ;

		if( 1 <= c && c <= 5 )
			break ;
		else
			printf( "1から5までの数字を入力してください\n" ) ;
	}

	switch( c ) {
		case 1:	PrintList( ) ;	break ;
		case 2:	Add( ) ;		break ;
		case 3:	Del( ) ;		break ;
		case 4:	Calc( ) ;		break ;
		case 5:	return 1 ;
	}
	return 0 ;
}

/*
 *	メイン関数
 */
int main( int argc, char *argv[] )
{
	int end ;

	if( argc == 2 ) {
		end = ReadInitData( argv[1] ) ;
	} else {
		fprintf( stderr, "初期データファイルを指定してください．\n" ) ;
		return -1 ;
	}

	while( !end ) {
		end = Menu( ) ;
	}
	return 0 ;
}
