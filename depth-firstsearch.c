#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define	TRUE	1	/* �m�[�h���K��ς̏ꍇ��visited[]�̒l */
#define	FALSE	0	/* �m�[�h�����K��̏ꍇ��visited[]�̒l */
#define	MAXSIZE	11	/* �m�[�h�̐�(�ő吔) */

/*
 *	�אڃ��X�g���\�����邽�߂̃Z���\����
 */
typedef struct _Cell {
	int				no ;	/* �m�[�h�̌ŗL�ԍ� ���OA�`K��0�`10�ɑΉ� */
	char			name ;	/* �m�[�h�̖��O(�A���t�@�x�b�g1����) */
	struct _Cell	*next ;	/* ���̃m�[�h�ւ̃|�C���^ */
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

Cell	*adjacent[MAXSIZE] ;	/* �אڃ��X�g */
int		visited[MAXSIZE] ;		/* �K��σt���O */
int		path[MAXSIZE] ;			/* �o�H�D�X�^�b�N�Ƃ��ė��p */

/*
 *	�אڃ��X�g��\��
 */
void PrintAdjList( void )
{
	int		i ;
	Cell	*c ;

	printf( "�אڃ��X�g\n" ) ;

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
 *	�f�[�^�̒ǉ��Fparent�Ԃ̃m�[�h�̗אڐ�Ƃ���child��ǉ�
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
 *	�O���t�̏������FGraphData��adjacent[]�ɑ������
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
 *	�X�^�b�Npath[]�̏�����
 */
void InitStack( )
{
	int i ;

	for( i = 0 ; i < MAXSIZE ; i++ ) {
		path[i] = -1 ;
	}
}


/*
 *	path[]�Ƀf�[�^���v�b�V��
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
 *	path[]�̃f�[�^���|�b�v
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
 *	�T�������o�H��\��
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
 *	�o�H�T�� ���݂̒��ڃm�[�h(now)����S�[��(end)�܂ł̌o�H��T��
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
 *	���C���֐�
 */
int main( void )
{
	InitStack( ) ;
	InitGraph( ) ;
	printf( "�T������\n" ) ;
	Search( 0, 10 ) ;	/* A����K(0����10)�ւ̌o�H */
	return 0 ;
}

/*���s����
>backtrack.exe
�אڃ��X�g
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
�T������
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