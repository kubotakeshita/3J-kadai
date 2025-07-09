#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define	NAMELEN	16	/* �w���̍ő啶�����D�w���̓A���t�@�x�b�g�\�L�Ƃ��� */

/*
 *	�w����\���\����
 */
typedef struct _Station {
	char	name[NAMELEN] ;		/* �w�� */
	int		time ;				/* ��(���X�g��1�O�̗v�f)����̏��v���� */
	struct _Station *next ;		/* ���̉w�̃f�[�^�ւ̃|�C���^ */
} Station ;

Station	*head ;					/* �w���Ɋւ�����`���X�g�̐擪�A�h���X */
int		StationNum = 0 ;		/* ���`���X�g�ɓo�^����Ă���w�̐� */


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
 *	�t�@�C�����珉���̃��X�g�f�[�^��ǂݍ���
 *	*head��擪�Ƃ�����`���X�g���\������D
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
 *	���`���X�g��\������
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
 *	�����œn���ꂽ�w�������X�g(*head)�ɑ��݂��邩�m�F����
 *	���݂���΂��̃f�[�^�̃|�C���^���C���݂��Ȃ����NULL��Ԃ��D
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
 *	�f�[�^�̒ǉ�
 *	�L�[�{�[�h����w���C���v���ԁC�ǉ��ʒu����͂��Ă��炢�C
 *	���X�g(*head)�ɒǉ�����D
 */
void Add( void )
{
	Station *s, *ns ;
	char	name[NAMELEN] ;
	int		i ;

	ns = (Station*)malloc(sizeof(Station));
	printf("�w�������->");
	gets(ns->name);
	printf("���v���Ԃ����->");
	ns->time = GetNum();
	
	PrintList( ) ;

	do {
		printf( "�ǂ̉w�̌�ɒǉ����܂����H\n" ) ;
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
 *	�f�[�^�̍폜
 */
void Del( void )
{
	Station *cur, *prev ;
	char	name[NAMELEN] ;
	int		i ;

	PrintList( ) ;

	do {
		printf( "�ǂ̉w���폜���܂����H\n" ) ;
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
 *	���p���Ԃ̌v�Z
 */
void Calc( void )
{
	Station *from, *to ;
	char	name[NAMELEN] ;
	int		sum = 0 ;
	int		i ;

	PrintList( ) ;

	do {
		printf( "�ǂ̉w����ǂ̉w�܂ł̏��v���Ԃ��v�Z���܂����H\n" ) ;
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

	printf( "%s����%s�܂ł̏��v���Ԃ�", from->name, to->name ) ;

	while(from!=to){
		from = from->next;
		sum += from->time;
	}
	
	printf( "%d���ł�\n", sum ) ;
}

/*
 *	���j���[�̕\��
 */
int Menu( void )
{
	int		c ;

	while( 1 ) {
		printf( "1:�\��,2:�ǉ�,3:�폜,4:���v����,5:�I�� ==> " ) ;

		c = GetNum( ) ;

		if( 1 <= c && c <= 5 )
			break ;
		else
			printf( "1����5�܂ł̐�������͂��Ă�������\n" ) ;
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
 *	���C���֐�
 */
int main( int argc, char *argv[] )
{
	int end ;

	if( argc == 2 ) {
		end = ReadInitData( argv[1] ) ;
	} else {
		fprintf( stderr, "�����f�[�^�t�@�C�����w�肵�Ă��������D\n" ) ;
		return -1 ;
	}

	while( !end ) {
		end = Menu( ) ;
	}
	return 0 ;
}
