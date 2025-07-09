#include <stdio.h>
#include <stdlib.h>

#define TYPES 6			/* 荷物の種類 */
#define MAXCAPACITY 200 /* ナップザックの大きさの上限 */

int Size[] = {2, 3, 5, 7, 9, 15};	 /* 荷物の大きさ */
int Value[] = {2, 4, 7, 11, 14, 24}; /* 荷物の価値 */
/*
 *	【注】同じ添え字どうしが対応している．
 *	例：荷物1の大きさはSize[1]=3,荷物1の価値はValue[1]=4
 */

/*
 *	価値の合計total[]，最後に選んだ荷物choice[]を表示する
 */
void PrintList(int total[], int choice[], int capacity, int step)
{
	int i;
	printf("step = %d\n", step);
	printf("size   =");
	for (i = 0; i < capacity + 1; i++)
	{
		printf(" %2d", i);
	}
	printf("\ntotal  =");
	for (i = 0; i < capacity + 1; i++)
	{
		printf(" %2d", total[i]);
	}
	printf("\nchoice =");
	for (i = 0; i < capacity + 1; i++)
	{
		printf(" %2d", choice[i]);
	}
	printf("\n\n\n");
	return;
}

void DP(int capacity, int Size[], int Value[])
{

	int i, j;
	int total[MAXCAPACITY];	 /* 現時点でナップザックに詰め込んだ荷物の価値の合計 */
	int choice[MAXCAPACITY]; /* 最後に選んだ荷物 */
	int totalsize;			 /* ナップザックに詰め込んだ荷物の大きさの合計 */
	int item[TYPES] = {0};
	/*
	 *	配列のクリア
	 */
	for (i = 0; i < MAXCAPACITY; i++)
	{
		total[i] = 0;
		choice[i] = -1;
	}

	for (i = 0; i < MAXCAPACITY; i++)
	{
		total[i] = (i / Value[0]) * Value[0];
		if (i >= Size[0])
			choice[i] = 0;
	}

	PrintList(total, choice, capacity, 0);

	/*
	 *	大きさがSize[i]の荷物を大きさjのナップザックに詰め込む
	 *	価値合計が同じか小さくなる場合は大きさjの荷物は詰め込まない．
	 */

	for (i = 1; i < TYPES; i++)
	{
		for (j = 0; j < MAXCAPACITY; j++)
		{
			if (j >= Size[i])
			{
				if (total[j - Size[i]] + Value[i] >= total[j])
				{
					total[j] = total[j - Size[i]] + Value[i];
					choice[j] = i;
				}
			}
		}
		PrintList(total, choice, capacity, i);
	}

	i = capacity;
	printf("大きさ%dのナップザックの荷物の最大価値：%d\n", capacity, total[capacity]);
	while (i != 0)
	{
		item[choice[i]]++;
		i -= Size[choice[i]];
	}
	for (i = 0; i < TYPES; i++)
	{
		if (item[i] != 0)
		{
			printf("荷物%d(大きさ%d,価値%d):%d個\n", i, Size[i], Value[i], item[i]);
		}
	}
	printf("\n");
	return;
}

int main(int argc, char *argv[])
{

	int capacity; /* ナップザックの大きさ */

	if (argc != 2 || atoi(argv[1]) <= 0 || atoi(argv[1]) > MAXCAPACITY)
	{
		fprintf(stderr, "usage: %s capacity\n", argv[0]);
		fprintf(stderr, "(0<capacity<=%d)\n", MAXCAPACITY);
		exit(0);
	}

	/*
	 *	コマンドラインで指定された引数をcapacityに代入する．
	 */
	capacity = atoi(argv[1]);
	printf("Capacity of knapsack is %d\n", capacity);

	/*
	 *	動的計画法を実行
	 */
	DP(capacity, Size, Value);

	return 0;
}

/*　実行結果（荷物の内容のみ）

大きさ26のナップザックの荷物の最大価値：40
荷物0(大きさ2,価値2):1個
荷物4(大きさ9,価値14):1個
荷物5(大きさ15,価値24):1個

大きさ98のナップザックの荷物の最大価値：156
荷物3(大きさ7,価値11):2個
荷物4(大きさ9,価値14):1個
荷物5(大きさ15,価値24):5個

大きさ184のナップザックの荷物の最大価値：293
荷物1(大きさ3,価値4):1個
荷物3(大きさ7,価値11):1個
荷物4(大きさ9,価値14):1個
荷物5(大きさ15,価値24):11個

*/