#include <stdio.h>
#include <stdlib.h>

#define IMAX 1000000 /* ∞を表す便宜的な値 */

int *data;	 /* データ列 */
int datanum; /* 実際のデータ数 */
int leafnum; /* 完全二進木のleafの数 */

/*
 *	【PrintData】（デバッグ用）
 *	対象データを表示する．
 */
void PrintData()
{
	int i;

	for (i = 0; i < 2 * leafnum - 1; i++)
	{
		printf("[PrintData](%d)(%d) %d\n", i, i - (leafnum - 1), *(data + i));
	}
}

/*
 *	データをファイルから読み込んでセグメント木を作成し，
 *	その先頭アドレスを返す．
 */
int *ReadFile(char *fn)
{
	FILE *fp;
	int i, tmp;

	/*
	 *	ファイルのオープン
	 */
	if ((fp = fopen(fn, "r")) == NULL)
	{
		fprintf(stderr, "cannot open %s\n", fn);
		return NULL;
	}

	/*
	 *	ファイル内のデータ数を数えdatanumに代入する．
	 */
	datanum = 0;
	while (fscanf(fp, "%d", &tmp) != EOF)
		datanum++;
	rewind(fp);

	for (i = 2; i < datanum; i *= 2)
		;
	leafnum = i;
	data = (int *)malloc((2 * leafnum - 1) * sizeof(int));
	i = leafnum - 1;
	while (fscanf(fp, "%d", &tmp) != EOF)
	{
		data[i] = tmp;
		i++;
	}
	while (i < 2 * leafnum - 1)
	{
		data[i] = IMAX;
		i++;
	}
	for (i = leafnum - 2; i >= 0; i++)
	{
		if (data[2 * i + 1] < data[2 * i + 2])
		{
			data[i] = data[2 * i + 1];
		}
		else
			data[i] = data[2 * i + 2];
	}

	return data;
}

/*
 *	【数値の入力】数値は5桁までとする．
 */
int GetNum(void)
{
	int i, d = 0, c = 0;

	rewind(stdin);

	for (i = 0; i < 5 && c != '\n'; i++)
	{
		c = getchar();
		if (c == '\n')
			break;
		d = d * 10 + c - '0';
	}
	rewind(stdin);

	return d;
}

/*
 *	【最小値の探索】
 *	pos	現在注目しているノードの番号(ルートノードの番号は0)
 *	[left,right]	pos番のノードが管理する区間
 *	[start, end]	探索区間
 */
int SearchMin(int pos, int left, int right, int start, int end)
{
	int vleft, vright;

	if (start < left && end < left || start > right && end > right)
		return IMAX;
	if (start >= left && end <= right && start <= right && end >= left)
		return data[pos];
	else
	{
		vleft = SearchMin(2 * pos + 1, left, (left + right) / 2, start, end);
		vright = SearchMin(2 * pos + 2, (left + right) / 2 + 1, right, start, end);
		if (vleft < vright)
			return vleft;
		else
			return vright;
	}
}

/*
 *	【指定された区間の最小値の計算】
 */
void Search()
{
	int start, end;

	/*
	 *	探索区間の左端および右端をキーボードから入力する．
	 */
	printf("開始位置(0-%d)：", datanum);
	start = GetNum();

	printf("終了位置(0-%d)：", datanum);
	end = GetNum();

	/*
	 *	関数SearchMin()を用いて最小値を計算し，結果を出力する．
	 */
	printf("最小値：%d\n", SearchMin(0, 0, datanum - 1, start, end));
}

/*
 *	データを変更し，完全二進木を更新する．
 */
void Change()
{
	int pos, val, j;

	/*
	 *	変更するデータの場所と，新しい値をキーボードから入力し，
	 *	しかるべき位置に新しい値を代入する．
	 */
	printf("何個目のデータを変更しますか(0-%d)：", datanum);
	pos = GetNum();

	printf("新しい値を入力してください：");
	val = GetNum();

	j = leafnum - 1 + pos;
	data[j] = val;
	while (j != 0)
	{
		j = (j - 1) / 2;
		if (data[2 * j + 1] < data[2 * j + 2])
			data[j] = data[2 * j + 1];
		else
			data[j] = data[2 * j + 2];
	}
}

/*
 *	【メイン関数】
 */
int main(int argc, char *argv[])
{
	/*
	 *	argcはコマンドラインで指定された文字列の数が代入されている．
	 *	argv[]はコマンドラインで指定された文字列が代入されている．
	 *
	 *	【例】
	 *	C\:> ./kadai.exe sample.txt
	 *
	 *	この場合，プログラムを実行したときにargcには予め2が代入されている．
	 *	argv[0]には「./kadai.exe」が，argv[1]には「sample.txt」が代入されている．
	 */
	/*
	 *	プログラムの引数としてデータファイルが1つ指定されているかどうかをチェックする．
	 */
	if (argc != 2)
	{
		fprintf(stderr, "USAGE : %s datafile\n", argv[0]);
		return 0;
	}

	/*
	 *	コマンドラインで指定されたファイルの内容を読み込む．
	 */
	if (ReadFile(argv[1]) == NULL)
	{
		fprintf(stderr, "cannot read %s\n", argv[1]);
		return 0;
	}

	/*
	 *	キーボードからコマンドを受け付け，対応する処理を行う．
	 */
	while (1)
	{
		printf("1:search, 2:change, 0:finish\n");
		switch (GetNum())
		{
		case 0:
			return 0; /* プログラムの終了 */
		case 1:
			Search();
			break; /* データの検索 */
		case 2:
			Change();
			break; /* データの変更 */
		}
	}
}
