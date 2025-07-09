#include	<stdio.h>
#include	<string.h>

#define		TEXTLEN		64	/* �e�L�X�g�̍ő啶���� */
#define		PTNLEN		256	/* �p�^�[���̍ő啶���� */

#define		Max(a,b)	((a)>(b)?a:b)	/* a,b�̂����傫������Ԃ� */

typedef		unsigned char	Uchar ;	/* unsigned char�̏ȗ��`��` */

int	next[ PTNLEN ] ;		/* KMP�@�̂��炵�\ */
int	skip[ PTNLEN ] ;		/* BM�@�̂��炵�\ */

/*
 *	KMP�@�p�̂��炵�\�̍쐬
 */
void InitNext( Uchar ptn[] )
{
	int m,s,p,len=strlen(ptn);
	
	next[0]=1;
	next[1]=1;
	
	for(m=2;m<len;m++){
		for(s=1;s<m;s++){
			for(p=s;p<m;p++){
				if(ptn[p]!=ptn[p-s])break;
			}
			if(p==m){
				next[m]=s;
				break;
			}else next[m]=m;
		}
	}
}

/*
 *	BM�@�p�̂��炵�\�̍쐬
 */
void InitSkip( Uchar ptn[] )
{
	int i,ptnlen=strlen(ptn);
	for(i=0;i<PTNLEN;i++){
		skip[i]=ptnlen;	
	}
	
	for(i=0;i<ptnlen;i++){
		skip[ptn[i]]=(ptnlen-1)-i;
	}
}

/*
 *	�͂܂����@
 *	�e�L�X�gtext[]����p�^�[��ptn[]���������C�ŏ��Ɍ��������ʒu��Ԃ��D
 *	�ʒu��text[]�̃C���f�b�N�X�Ƃ���D(�܂�擪�Ɍ���������0�j
 *	�p�^�[����������Ȃ��ꍇ��-1��Ԃ��D
 */
int BruteForce( Uchar text[], Uchar ptn[] )
{
	int idx,i,k;
	int texlen=strlen(text);
	int ptnlen=strlen(ptn);
	printf("%s\n",text);
	for(idx=0;idx<texlen-ptnlen;idx++){
		for(i=0;i<ptnlen;i++){
			printf("%c",ptn[i]);
			if(text[idx+i]!=ptn[i]){
				printf("...Failure\n");
				break;
			}
		}
		if(i==ptnlen){
			printf("...Success!\n");
			return idx;
		}
		printf(" ");
		for(k=0;k<idx;k++)printf(" ");
	}
	return -1;
}

/*
 *	KMP�@
 *	�e�L�X�gtext[]����p�^�[��ptn[]���������C�ŏ��Ɍ��������ʒu��Ԃ��D
 *	�ʒu��text[]�̃C���f�b�N�X�Ƃ���D(�܂�擪�Ɍ���������0�j
 *	�p�^�[����������Ȃ��ꍇ��-1��Ԃ��D
 */
int Kmp( Uchar text[], Uchar ptn[] )
{
	int idx,i,k;
	int texlen=strlen(text);
	int ptnlen=strlen(ptn);
	printf("%s\n",text);
	for(idx=0;idx<texlen-ptnlen;idx++){
		for(i=0;i<ptnlen;i++){
			printf("%c",ptn[i]);
			if(text[idx+i]!=ptn[i]){
				printf("...Failure\n");
				break;
			}
		}
		if(i==ptnlen){
		 printf("...Success!\n");
			return idx;
		}
		idx+=next[i]-1;
		printf(" ");
		for(k=0;k<idx;k++)printf(" ");
	}
	return -1;
}

/*
 *	BM�@
 *	�e�L�X�gtext[]����p�^�[��ptn[]���������C�ŏ��Ɍ��������ʒu��Ԃ��D
 *	�ʒu��text[]�̃C���f�b�N�X�Ƃ���D(�܂�擪�Ɍ���������0�j
 *	�p�^�[����������Ȃ��ꍇ��-1��Ԃ��D
 */
int BM( Uchar text[], Uchar ptn[] )
{
	int i=0,j,ptnlen=strlen(ptn),txtlen=strlen(text);
	while(i<txtlen){
		for(j=ptnlen-1;j<=0;j--){
			if(text[i+j]==ptn[j]){
				if(j==0)return i;
			}else {
				if(skip[text[j]]<i){
					i+=1;
				}else i+=skip[text[j]];
			}
		}
	}
}

/*
 *	���C���֐�
 */
int main(void)
{
	Uchar	text[ TEXTLEN ] ;
	Uchar	ptn[ PTNLEN ] ;
	int		pos ;

	/*�s�����`�t*/
	strcpy( text, "xtataytarttartayta" ) ;
	strcpy( ptn, "tartay" ) ;

	/*�s�����a�t*/
	/*
	strcpy( text, "pyokopyokomipyokopyokomepyokopyokopyokopyokomupyokopyoko" ) ;
	strcpy( ptn, "pyokopyokomu" ) ;
	*/

	printf( "--- Brute Force Search ---\n" ) ;
	pos = BruteForce( text, ptn ) ;
	printf( "Position = %d\n", pos ) ;

	printf( "--- KMP Search ---\n" ) ;
	InitNext( ptn ) ;
	pos = Kmp( text, ptn ) ;
	printf( "Position = %d\n", pos ) ;

	printf( "--- BM Search ---\n" ) ;
	InitSkip( ptn ) ;
	pos = BM( text, ptn ) ;
	printf( "Position = %d\n", pos ) ;

	return 0;
}
