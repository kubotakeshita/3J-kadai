#include <stdio.h>
#include <stdlib.h>

#define	HASHSIZE	9			/* ハッシュ表のサイズ */
#define	Hash( key )	( key % HASHSIZE )
								/* ハッシュ関数 */

typedef struct _Student {		/* 学生を表す構造体 */
	int		no ;				/* 番号 */
	char	name[16] ;			/* 名前 */
	struct _Student	*next ;		/* 次の学生データのアドレス */
} Student ;

Student	*HashTable[ HASHSIZE ] ;	/* ハッシュ表 */

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
 *	ハッシュ表の内容を表示する
 */
void PrintTable( void )
{
	int		i = 0 ;
	Student	*s ;

	for( i = 0 ; i < HASHSIZE ; i++ ) {
		printf( "[%d]-", i ) ;
		s = HashTable[i] ;
		while(s != NULL){
			printf("[%d|%s]-",s->no,s->name);
			s = s->next;
		}

		printf( "\n" ) ;
	}
}

/*
 *	データの追加
 */
void Add( void )
{
	Student	*p, *q ;
	int		key, i ;

	p = (Student*)malloc( sizeof(Student) ) ;

	if( p == NULL ) {
		fprintf( stderr, "memory allocation error\n" ) ;
		PrintTable( ) ;
		return ;
	}

	printf( "No= " ) ;
	p->no = GetNum( ) ;

	printf( "Name= " ) ;
	fgets( p->name, 16, stdin ) ;

	for( i = 0 ; p->name[i] != '\n' && i != 15 ; i++ ) ;
	p->name[i] = '\0' ;

	p->next = NULL ;

	key = Hash(p->no) ;

	if(HashTable[key] == NULL){
		HashTable[key] = p;
	}else {
		q = HashTable[key];
		while(q->next != NULL){
			q = q->next;
		}
		q->next = p;
	}
	

	PrintTable( ) ;
}

/*
 *	データの削除
 */
void Del( void )
{
	Student	*head, *target, *prev, *tmp ;
	int		no, key ;

	PrintTable( ) ;

	printf( "No= " ) ;
	no = GetNum( ) ;

	key = Hash( no ) ;
	head = HashTable[key] ;
	target = head ;

	while(target != NULL){
		if(target->no == no){
			if(target == head){
				HashTable[key] = HashTable[key]->next;
				free(target);
				PrintTable();
				return;
			}else {
				prev = head;
				while(prev->next != target) prev = prev->next;
				prev->next = target->next;
				free(target);
				PrintTable();
				return;
			}
		}
		target = target->next;
	}
	printf("Not found\n");
	return;

}

/*
 *	データの検索
 */
int Search( void )
{
	Student	*s ;
	int		no, key ;

	printf( "No= " ) ;
	no = GetNum( ) ;
	key = Hash( no ) ;
	s = HashTable[key] ;

	while(s != NULL){
		if(s->no == no){
			printf("%d -> %s\n",s->no,s->name);
		}
		s = s->next;
	}
	printf("Not found");
	return -1;

}

/*
 *	メニューの表示
 */
int Menu( void )
{
	int		c ;

	while( 1 ) {
		printf( "1:表示,2:追加,3:削除,4:探索,5:終了 ==> " ) ;

		c = GetNum( ) ;

		if( 1 <= c && c <= 5 )
			break ;
		else
			printf( "1から5までの数字を入力してください．\n" ) ;
	}

	switch( c ) {
		case 1:	PrintTable( ) ;	break ;
		case 2:	Add( ) ;		break ;
		case 3:	Del( ) ;		break ;
		case 4:	Search( ) ;		break ;
		case 5:	return 1 ;
	}
	return 0 ;
}

/*
 *	メイン関数
 */
int main( void )
{
	int i, end = 0 ;

	for( i = 0 ; i < HASHSIZE ; i++ ) {
		HashTable[i] = NULL ;
	}

	while( !end ) {
		end = Menu( ) ;
	}
	return 0 ;
}


/* 実行結果

>hash.exe
1:表・2:追加,3:削除,4:探索,5:終了 ==> 1
[0]-
[1]-
[2]-
[3]-
[4]-
[5]-
[6]-
[7]-
[8]-
1:表・2:追加,3:削除,4:探索,5:終了 ==> 2
No= 17
Name= Hazamaru Taro
[0]-
[1]-
[2]-
[3]-
[4]-
[5]-
[6]-
[7]-
[8]-[17|Hazamaru Taro]-
1:表・2:追加,3:削除,4:探索,5:終了 ==> 2
No= 35
Name= Kosen Hanako
[0]-
[1]-
[2]-
[3]-
[4]-
[5]-
[6]-
[7]-
[8]-[17|Hazamaru Taro]-[35|Kosen Hanako]-
1:表・2:追加,3:削除,4:探索,5:終了 ==> 2
No= 53
Name= Tokyo Jiro
[0]-
[1]-
[2]-
[3]-
[4]-
[5]-
[6]-
[7]-
[8]-[17|Hazamaru Taro]-[35|Kosen Hanako]-[53|Tokyo Jiro]-
1:表・2:追加,3:削除,4:探索,5:終了 ==> 2
No= 13
Name= Joho Saburo
[0]-
[1]-
[2]-
[3]-
[4]-[13|Joho Saburo]-
[5]-
[6]-
[7]-
[8]-[17|Hazamaru Taro]-[35|Kosen Hanako]-[53|Tokyo Jiro]-
1:表・2:追加,3:削除,4:探索,5:終了 ==> 4
No= 35
35 -> Kosen Hanako
Not found1:表・2:追加,3:削除,4:探索,5:終了 ==> 3
[0]-
[1]-
[2]-
[3]-
[4]-[13|Joho Saburo]-
[5]-
[6]-
[7]-
[8]-[17|Hazamaru Taro]-[35|Kosen Hanako]-[53|Tokyo Jiro]-
No= 17
[0]-
[1]-
[2]-
[3]-
[4]-[13|Joho Saburo]-
[5]-
[6]-
[7]-
[8]-[35|Kosen Hanako]-[53|Tokyo Jiro]-
1:表・2:追加,3:削除,4:探索,5:終了 ==> 5

Pushing any key leads the exit.

*/