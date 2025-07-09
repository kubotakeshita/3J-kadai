#include	<stdio.h>
#include	<string.h>

#define		TEXTLEN		64	/* �e�L�X�g�̍ő啶���� */
#define		PTNLEN		16	/* �p�^�[���̍ő啶���� */

int	next[ PTNLEN ] ;		/* ���炵�\ */

/*
 *	���炵�\�̍쐬
 */
void InitNext( char ptn[] )
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
//tartay,1,1,2,3,3,3
/*
 *	�͂܂����@
 *	�e�L�X�gtext[]����p�^�[��ptn[]���������C�ŏ��Ɍ��������ʒu��Ԃ��D
 *	�ʒu��tex[]�̃C���f�b�N�X�Ƃ���D(�܂�擪�Ɍ���������0�j
 *	�p�^�[����������Ȃ��ꍇ��-1��Ԃ��D
 */
int BruteForce( char text[], char ptn[] )
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
 *	�ʒu��tex[]�̃C���f�b�N�X�Ƃ���D(�܂�擪�Ɍ���������0�j
 *	�p�^�[����������Ȃ��ꍇ��-1��Ԃ��D
 */
int Kmp( char text[], char ptn[] )
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
 *	���C���֐�
 */
int main(void)
{
	char	text[ TEXTLEN ] ;
	char	ptn[ PTNLEN ] ;
	int		i,pos,len;

	/*�s�����`�t*/
	strcpy( text, "xxxtartartaya" ) ;
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
	len=strlen(ptn);
	for(i=0;i<len;i++){
		printf("next[%d]=%d\n",i,next[i]);
	}
	pos = Kmp( text, ptn ) ;
	printf( "Position = %d\n", pos ) ;

	return 0;
}

/*
>kadai1.exe
--- Brute Force Search ---
xxxtartartaya
t...Failure
 t...Failure
  t...Failure
   tartay...Failure
    t...Failure
     t...Failure
      tartay...Success!
Position = 6
--- KMP Search ---
next[0]=1
next[1]=1
next[2]=2
next[3]=3
next[4]=3
next[5]=3
xxxtartartaya
t...Failure
 t...Failure
  t...Failure
   tartay...Failure
      tartay...Success!
Position = 6
*/
