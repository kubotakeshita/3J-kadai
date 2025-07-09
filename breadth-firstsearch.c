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
 * �אڍs��(adj)��\������
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
 * �O���t�f�[�^(GraphData)����אڍs��(adj)�𐶐�����
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
 * �L���[(q)��\������
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
 * �L���[(q)�̒��Ƀf�[�^(d)�����݂��邩�ǂ����m�F����
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
 * �L���[(q)�Ƀf�[�^(d)��ǉ�����
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
 * �L���[(q)����f�[�^����菜��
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
 * �אڍs��(adj)��p���āC
 * �w��n�_(now)����S�[��(end)�܂ŕ��D��o�H�T�����s��
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
 * ���C���֐�
 */
int main( void )
{
	int	adjacent[MAXSIZE][MAXSIZE] ;	/*�אڍs��*/

	InitGraph( adjacent ) ;	/* �אڍs��̏����� */
	Search( adjacent, 0, MAXSIZE-1 ) ;	/* A(0)����K(10)�܂ł̌o�H */
	return 0 ;
}

/* ���s����
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