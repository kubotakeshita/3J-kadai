#include	<stdio.h>
#include	<string.h>

#define		TEXTLEN		64	/* テキストの最大文字数 */
#define		PTNLEN		256	/* パターンの最大文字数 */

#define		Max(a,b)	((a)>(b)?a:b)	/* a,bのうち大きい方を返す */

typedef		unsigned char	Uchar ;	/* unsigned charの省略形定義 */

int	next[ PTNLEN ] ;		/* KMP法のずらし表 */
int	skip[ PTNLEN ] ;		/* BM法のずらし表 */

/*
 *	KMP法用のずらし表の作成
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
 *	BM法用のずらし表の作成
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
 *	力まかせ法
 *	テキストtext[]からパターンptn[]を検索し，最初に見つかった位置を返す．
 *	位置はtext[]のインデックスとする．(つまり先頭に見つかったら0）
 *	パターンが見つからない場合は-1を返す．
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
 *	KMP法
 *	テキストtext[]からパターンptn[]を検索し，最初に見つかった位置を返す．
 *	位置はtext[]のインデックスとする．(つまり先頭に見つかったら0）
 *	パターンが見つからない場合は-1を返す．
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
 *	BM法
 *	テキストtext[]からパターンptn[]を検索し，最初に見つかった位置を返す．
 *	位置はtext[]のインデックスとする．(つまり先頭に見つかったら0）
 *	パターンが見つからない場合は-1を返す．
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
 *	メイン関数
 */
int main(void)
{
	Uchar	text[ TEXTLEN ] ;
	Uchar	ptn[ PTNLEN ] ;
	int		pos ;

	/*《実験Ａ》*/
	strcpy( text, "xtataytarttartayta" ) ;
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
	pos = Kmp( text, ptn ) ;
	printf( "Position = %d\n", pos ) ;

	printf( "--- BM Search ---\n" ) ;
	InitSkip( ptn ) ;
	pos = BM( text, ptn ) ;
	printf( "Position = %d\n", pos ) ;

	return 0;
}
