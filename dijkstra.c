#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

#define	SIZE	13		/* �m�[�h�� */
#define	FIXED	1		/* �m�[�h�ɑ΂���ŒZ�o�H������� */
#define UNFIXED	0		/* �m�[�h�ɑ΂���ŒZ�o�H������ */
#define	UNDEF	-1		/* ����`�m�[�h�D�m�[�h����`����Ă��Ȃ���Ԃ�\�� */
#define IMAX	INT_MAX	/* int�^�f�[�^�̍ő�l */

/* �אڍs�� */
int Adjacent[SIZE][SIZE] = {
	/* A    B    C    D    E    F    G    H    I    J    K    L    M */
	{   0,  30,IMAX,  40,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX},	// A: ����
	{  30,   0,  90,  60, 140,  80,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX},	// B: ���
	{IMAX,  90,   0,IMAX,IMAX, 110, 330, 240,IMAX,IMAX,IMAX,IMAX,IMAX},	// C: �Q�n
	{  40,  60,IMAX,   0, 130,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX},	// D: ��t
	{IMAX, 140,IMAX, 130,   0, 100, 260,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX},	// E: ���
	{IMAX,  80, 110,IMAX, 100,   0, 170,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX},	// F: �Ȗ�
	{IMAX,IMAX, 330,IMAX, 260, 170,   0, 550,  80,  90,IMAX,IMAX,IMAX},	// G: ����
	{IMAX,IMAX, 240,IMAX,IMAX,IMAX, 550,   0, 630,IMAX,IMAX,IMAX,IMAX},	// H: �V��
	{IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,  80, 630,   0,  60, 190,IMAX,IMAX},	// I: �R�`
	{IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,  90,IMAX,  60,   0, 290, 180,IMAX},	// J: �{��
	{IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX, 190, 290,   0, 110, 300},	// K: �H�c
	{IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX, 180, 110,   0, 190},	// L: ���
	{IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX,IMAX, 300, 190,   0}	// M: �X
} ;

char *GraphData[] = {	/* �m�[�h���D��L�אڍs���0�`12�Ԗڂ̊e�v�f�ɑΉ� */
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

int	Cost[SIZE] ;	/* �e�m�[�h�܂ł̍ŒZ�o�H�̃R�X�g */
int Fixed[SIZE] ;	/* �e�m�[�h�ɑ΂���ŒZ�o�H�����肵�Ă��邩�ǂ�����\�� */
int	Prev[SIZE] ;	/* �ŒZ�o�H�ɂ�����P�O�̃m�[�h */

/*
 *	�e�m�[�h�ɂ��āC�ŒZ�o�H�ɂ����钼�O�̃m�[�h�ƃR�X�g��\��
 */
void PrintCost( void )
{
	int i;
	for(i = 0; i < SIZE; i++){
		printf("�m�[�h %s ���O�̃m�[�h %s �R�X�g %d\n", GraphData[i], GraphData[Prev[i]], Cost[i]);
	}
}


/*
 *	Dijkstra�@
 */
void Dijkstra( int start )
{
	int i, min = IMAX, num = -1;

	for(i = 0; i < SIZE; i++){
		if(Adjacent[start][i] != IMAX){						//�אڂ��Ă���
			if(Fixed[i] == UNFIXED){						//�ŒZ�o�H���m�肵�Ă��Ȃ�
				if(Cost[i] > Cost[start] + Adjacent[start][i]){	//�R�X�g���r
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
 *	start����goal�܂ł̌o�H�ƍŏ��R�X�g���o�͂���
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
 *	���C���֐�
 */
int main( void )
{
	int		start ;			/* �o���n�_ */
	int		goal ;			/* �����n�_ */
	int		i ;

	/*
	 *	�s�����̕\��
	 */
	for( i = 0 ; i < SIZE ; i++ ) {
		printf( "%2d: %s\n", i, GraphData[i] ) ;
	}

	/*
	 *	�o���n�_�y�ѓ����n�_�̓���
	 */
	printf( "�o���n�_����͂��Ă��������F" ) ;
	scanf( "%d", &start ) ;
	printf( "�����n�_����͂��Ă��������F" ) ;
	scanf( "%d", &goal ) ;

	/*
	 *	Dijkstra�@�ɂ��o�H�T��
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
	 *	�e�m�[�h�ɂ��āC�ŒZ�o�H�ɂ�����1�O�̃m�[�h�ƍŒZ�o�H�R�X�g��\��
	 */
	PrintCost( ) ;

	/*
	 *	start����goal�܂ł̍ŒZ�o�H�ƁC���̃R�X�g��\��
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
�o���n�_����͂��Ă��������F1
�����n�_����͂��Ă��������F10
�m�[�h Tokyo ���O�̃m�[�h Saitama �R�X�g 30
�m�[�h Saitama ���O�̃m�[�h Saitama �R�X�g 0
�m�[�h Gunma ���O�̃m�[�h Saitama �R�X�g 90
�m�[�h Chiba ���O�̃m�[�h Saitama �R�X�g 60
�m�[�h Ibaraki ���O�̃m�[�h Saitama �R�X�g 140
�m�[�h Tochigi ���O�̃m�[�h Saitama �R�X�g 80
�m�[�h Fukushima ���O�̃m�[�h Tochigi �R�X�g 250
�m�[�h Niigata ���O�̃m�[�h Gunma �R�X�g 330
�m�[�h Yamagata ���O�̃m�[�h Fukushima �R�X�g 330
�m�[�h Miyagi ���O�̃m�[�h Fukushima �R�X�g 340
�m�[�h Akita ���O�̃m�[�h Yamagata �R�X�g 520
�m�[�h Iwate ���O�̃m�[�h Miyagi �R�X�g 520
�m�[�h Aomori ���O�̃m�[�h Iwate �R�X�g 710
[Saitama]->[Tochigi]->[Fukushima]->[Yamagata]->[Akita]: Cost=520

*/