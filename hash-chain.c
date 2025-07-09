#include <stdio.h>
#include <stdlib.h>

#define	HASHSIZE	9			/* �n�b�V���\�̃T�C�Y */
#define	Hash( key )	( key % HASHSIZE )
								/* �n�b�V���֐� */

typedef struct _Student {		/* �w����\���\���� */
	int		no ;				/* �ԍ� */
	char	name[16] ;			/* ���O */
	struct _Student	*next ;		/* ���̊w���f�[�^�̃A�h���X */
} Student ;

Student	*HashTable[ HASHSIZE ] ;	/* �n�b�V���\ */

/*
 *	�L�[�{�[�h������͂��ꂽ�ԍ���ǂݎ��D
 *	�ǂݎ�鐔�l��0�ȏ�̐���5���܂łƂ���D
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
 *	�n�b�V���\�̓��e��\������
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
 *	�f�[�^�̒ǉ�
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
 *	�f�[�^�̍폜
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
 *	�f�[�^�̌���
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
 *	���j���[�̕\��
 */
int Menu( void )
{
	int		c ;

	while( 1 ) {
		printf( "1:�\��,2:�ǉ�,3:�폜,4:�T��,5:�I�� ==> " ) ;

		c = GetNum( ) ;

		if( 1 <= c && c <= 5 )
			break ;
		else
			printf( "1����5�܂ł̐�������͂��Ă��������D\n" ) ;
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
 *	���C���֐�
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


/* ���s����

>hash.exe
1:�\�E2:�ǉ�,3:�폜,4:�T��,5:�I�� ==> 1
[0]-
[1]-
[2]-
[3]-
[4]-
[5]-
[6]-
[7]-
[8]-
1:�\�E2:�ǉ�,3:�폜,4:�T��,5:�I�� ==> 2
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
1:�\�E2:�ǉ�,3:�폜,4:�T��,5:�I�� ==> 2
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
1:�\�E2:�ǉ�,3:�폜,4:�T��,5:�I�� ==> 2
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
1:�\�E2:�ǉ�,3:�폜,4:�T��,5:�I�� ==> 2
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
1:�\�E2:�ǉ�,3:�폜,4:�T��,5:�I�� ==> 4
No= 35
35 -> Kosen Hanako
Not found1:�\�E2:�ǉ�,3:�폜,4:�T��,5:�I�� ==> 3
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
1:�\�E2:�ǉ�,3:�폜,4:�T��,5:�I�� ==> 5

Pushing any key leads the exit.

*/