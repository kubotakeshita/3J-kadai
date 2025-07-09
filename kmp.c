#include	<stdio.h>
#include	<string.h>

#define		TEXTLEN		64	/* テキストの最大文字数 */
#define		PTNLEN		16	/* パターンの最大文字数 */

int	next[ PTNLEN ] ;		/* ずらし表 */

/*
 *	ずらし表の作成
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
 *	力まかせ法
 *	テキストtext[]からパターンptn[]を検索し，最初に見つかった位置を返す．
 *	位置はtex[]のインデックスとする．(つまり先頭に見つかったら0）
 *	パターンが見つからない場合は-1を返す．
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
 *	KMP法
 *	テキストtext[]からパターンptn[]を検索し，最初に見つかった位置を返す．
 *	位置はtex[]のインデックスとする．(つまり先頭に見つかったら0）
 *	パターンが見つからない場合は-1を返す．
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
 *	メイン関数
 */
int main(void)
{
	char	text[ TEXTLEN ] ;
	char	ptn[ PTNLEN ] ;
	int		i,pos,len;

	/*《実験Ａ》*/
	strcpy( text, "xxxtartartaya" ) ;
	strcpy( ptn, "tartay" ) ;

	/*《実験Ｂ》*/
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
