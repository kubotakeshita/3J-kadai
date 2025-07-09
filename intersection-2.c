#include <stdio.h>
#include <stdlib.h>

#define	LINENUM	8
#define	INTSECNUM	(LINENUM*LINENUM)
#define	EVENTNUM	(LINENUM+INTSECNUM)

#define	EVENTSTART	1	/* 線分の左端(start) */
#define	EVENTEND	2	/* 線分の右端(end) */
#define	EVENTINTSCT	3	/* 2つの線分の交点 */

typedef struct {	/* 点の座標 */
	double	x ;
	double	y ;
} Axis ;

typedef struct {	/* 線分 */
	Axis	s ;		/* 左端点(start) */
	Axis	e ;		/* 右端点(end) */
} Line ;

typedef struct _Event {
	int		id ;				/* identifier */
	int		attr ;				/* 1:左点，2:交点，3:右点 */
	Line	line ;				/* 線分 */
	double	x ;					/* 左端点・右端点・交点のx座標 */
	double	y ;					/* 左端点・右端点・交点のx座標 */
	struct _Event	*prev ;		/* 前のイベント */
	struct _Event	*next ;		/* 次のイベント */
	struct _Event	*cline1 ;	/* 交差する線分(1) */
	struct _Event	*cline2 ;	/* 交差する線分(2) */
} Event ;

int	id = 1 ;	/* イベントの識別番号 */




/*
 *	Event構造体のリストを表示する．
 *	引数のポインタは必ずしもリストの先頭を指すとは限らないが，
 *	ここでは与えられたポインタをリストの先頭とみなして表示する．
 */
void PrintEvents( Event *e )
{
	while( e != NULL ){
		printf( "attr:%d x = %f y = %f\n",e->attr, e->x, e->y );
		e = e->next;
	}
}



/*
 *	2つのイベント構造体のデータを互いに交換する．
 *	ポインタは変更しない．
 */
void ExchangeEvents( Event *e1, Event *e2 )
{
	Event tmp, *p;
	
	tmp = *e1;
	*e1 = *e2;
	*e2 =tmp;
	
	p = e1->next;
	e1->next = e2->next;
	e2->next = p;
	
}


/*
 *	イベント構造体の線形リストをx軸座標の値で昇順にソートし，
 *	その先頭アドレスを返す．
 */
void SortEventByX( Event *e )
{
	Event* p = e;
	int i = 0, tmp;
	while (e != NULL) {
		i++;
		e = e->next;
	}

	for (int j = 0; j < i - 1; j++) {
		e = p;
		for (int k = 0; k < i - j - 1; k++) {
			if (e->x > e->next->x) {
				ExchangeEvents(e, e->next);
			}
			e = e->next;
		}
	}
}



/*
 *	イベントリストを初期化し，その線形リストの先頭アドレスを返す．
 */
Event* InitEvents( Line lines[] )
{
	Event *head = NULL, *e = NULL;
	
	for(int i=0; i<LINENUM; i++){
		Event *p = (Event*)malloc(sizeof(Event));
		
		if(head == NULL){
			head = p;
		}else {
			e->next = p;
		}
		e = p;
		e->next = NULL;
		e->id = id++;
		e->attr = 1;
		e->line = lines[i];
		e->x = lines[i].s.x;
		e->y = lines[i].s.y;
		
		p = (Event*)malloc(sizeof(Event));
		if(head == NULL){
			head = p;
		}else {
			e->next = p;
		}
		e = p;
		e->next = NULL;
		e->id = id++;
		e->attr = 3;
		e->line = lines[i];
		e->x = lines[i].e.x;
		e->y = lines[i].e.y;
	}

	SortEventByX( head ) ;
	return head;
}


/*
 *	イベントリストeventに新しいイベントneを追加する．
 *	イベントはx軸座標に関して昇順に整列するように追加する．
 *	eventはイベントリストの先頭とは限らない．
 */
void AddEvent( Event *event, Event *ne )
{
	int num = 0;
	while (event->next->x < ne->x) {

		event = event->next;
		if (event->next == NULL) {
			break;
		}
	}
	ne->next = event->next;
	event->next = ne;
}



/*
 *	2つの直線が交差するかどうかを判断し，交差する場合は，
 *	その交点を表すイベントを新たに作成する．
 *	交差する場合は新たに作製したイベントを，
 *	そうでない場合はNULLを返す．
 */
Event* InterSection( Event *e1, Event *e2 )
{
	if (e1 == NULL || e2 == NULL)return NULL;
	if(
		((e2->line.e.x - e2->line.s.x) * (e1->line.s.y - e2->line.s.y) - (e2->line.e.y - e2->line.s.y) * (e1->line.s.x - e2->line.s.x)) *
		((e2->line.e.x - e2->line.s.x) * (e1->line.e.y - e2->line.s.y) - (e2->line.e.y - e2->line.s.y) * (e1->line.e.x - e2->line.s.x)) < 0 &&
		((e1->line.e.x - e1->line.s.x) * (e2->line.e.y - e1->line.s.y) - (e1->line.e.y - e1->line.s.y) * (e2->line.e.x - e1->line.s.x)) *
		((e1->line.e.x - e1->line.s.x) * (e2->line.s.y - e1->line.s.y) - (e1->line.e.y - e1->line.s.y) * (e2->line.s.x - e1->line.s.x)) < 0
	){
		Event* inserted = (Event*)malloc(sizeof(Event));
		inserted->id = id++;

		inserted->attr = 2;
		double dx1, dx2, dy1, dy2;
		dx1 = e1->line.e.x - e1->line.s.x;
		dx2 = e2->line.e.x - e2->line.s.x;
		dy1 = e1->line.e.y - e1->line.s.y;
		dy2 = e2->line.e.y - e2->line.s.y;

		inserted->x = (e2->line.s.x * (e2->line.e.y - e2->line.s.y) * (e1->line.e.x - e1->line.s.x) - e1->line.s.x * (e2->line.e.x - e2->line.s.x) * (e1->line.e.y - e1->line.s.y) + (e2->line.e.x - e2->line.s.x) * (e1->line.e.x - e1->line.s.x) * (e1->line.s.y - e2->line.s.y)) / ((e2->line.e.y - e2->line.s.y) * (e1->line.e.x - e1->line.s.x) - (e2->line.e.x - e2->line.s.x) * (e1->line.e.y - e1->line.s.y));
		inserted->y = e2->line.s.y + (e2->line.e.y - e2->line.s.y) * (inserted->x - e2->line.s.x) / (e2->line.e.x - e2->line.s.x);

		inserted->next = NULL;
		inserted->cline1 = e1;
		inserted->cline2 = e2;

		AddEvent(e1, inserted);
		printf("交点:(%f,%f)\n", inserted->x, inserted->y);
		return inserted;
	}
	return NULL;
}



/*
 *	2つのイベント構造体に含まれる線分が同じかどうかを判断する．

int	IsSameLine( Event *e1, Event *e2 )
{

	if(e1->line == e2->line)return 1;
	else return 0;
}
*/


/*
 *	与えられた直線に対して，与えられた点が直線より上にあれば1を，
 *	直線より下にあれば-1を，直線上にあれば0を返す．
 */
int LinePosRelation( Line line, Axis point )
{

	if((line.e.x - line.s.x) * (point.y - line.s.y) - (line.e.y - line.s.y) * (point.x - line.s.x) > 0){
		return 1;
	}else if ((line.e.x - line.s.x) * (point.y - line.s.y) - (line.e.y - line.s.y) * (point.x - line.s.x) == 0){
		return 0;
	}else return -1;

}



/*
 *	線分リストに新しい線分を追加する．
 *	線分リストは，線分の始点のy座標に関して昇順に整列する．
 *	線分リストのlist[idx]に追加するとき，
 *	この関数はリストに線分を追加した位置を返すが，
 *	追加に失敗した場合は-1を返す．
 */
int	AddLine( Event *list[], Event *e )
{
	int i, pos = 0;
	for(i = LINENUM - 2; i >= 0; i--){
		if(list[i] == NULL || LinePosRelation(list[i]->line,e->line.s) == -1){
			list[i + 1] = list[i];
			list[i] = e;
		}else {
			pos = i + 1;
			break;
		}
	}
	
	if(pos + 1 < LINENUM)InterSection(list[pos + 1],list[pos]);
	if(pos - 1 >= 0)InterSection(list[pos - 1],list[pos]);
	return pos;
}



/*
 *	線分リストから指定された線分を削除する．
 *	削除する線分はEvent構造体のlistメンバーで与えられる．
 *	線分リストは，線分の始点のy座標に関して昇順に整列されている．
 *	線分リストのlist[idx]を削除するとき，返り値はidxである．
 */
int	DelLine( Event *list[], Event *e )
{
	int i, j;
	for(i = 0; i < LINENUM; i++){
		if(list[i]->line.s.x == e->line.s.x && list[i]->line.s.y){
			for(j = i; j < LINENUM - 2; j++){
				list[j] = list[j + 1];
			}
			list[LINENUM - 1] = NULL;
			if(i - 1 >= 0)InterSection(list[i],list[i - 1]);
			return i;
		}
	}
	return -1;
}



/*
 *	list[]中の隣り合う線分e1とe2の順番を入れ替える．
 */
int	ExchangeLine( Event *list[], Event *e1, Event *e2 )
{
	int a = -1, b = -1;
	for (int i = 0; i < LINENUM; i++) {
		if (list[i] == e1)a = i;
		if (list[i] == e2)b = i;
	}
	if (a == -1 || b == -1)return 0;
	Event* tmp;
	tmp = list[a];
	list[a] = list[b];
	list[b] = tmp;
	int TMP;
	if (b > a) {
		TMP = a;
		a = b;
		b = TMP;
	}


	if (a + 1 < LINENUM)InterSection(list[a], list[a + 1]);
	if (b - 1 >= 0)InterSection(list[b], list[b - 1]);
	return 1;
}



/*
 *	平面走査を行う．
 */
void Scan( Event *event )
{
	Event* LineList[LINENUM];
	for (int i = 0; i < LINENUM; i++) {
		LineList[i] = NULL;
	}
	while (event != NULL) {
		if (event->attr == 1) {
			AddLine(LineList, event);
		}
		else if (event->attr == 2) {
			ExchangeLine(LineList, event->cline1, event->cline2);
		}
		else DelLine(LineList, event);
		event = event->next;
	}

}



int main( )
{
	Event	*event ;		/* イベントリスト */

	Line lines[LINENUM] = {	/* 線分リスト */
		 4, 12, 52, 41,	/* 左点(x,y),右点(x,y)の順 */
		12, 20, 45,  5,
		24, 23, 36, 24,
		30,  4, 44, 40,
		34, 28, 48, 26,
		38, 22, 50, 12,
		40, 16, 57, 28,
		46, 32, 54, 29,
	} ;
	event = InitEvents( lines ) ;
	PrintEvents( event ) ;
	Scan( event ) ;
}

/*
attr:1 x = 4.000000 y = 12.000000
attr:1 x = 12.000000 y = 20.000000
attr:1 x = 24.000000 y = 23.000000
attr:1 x = 30.000000 y = 4.000000
attr:1 x = 34.000000 y = 28.000000
attr:3 x = 36.000000 y = 24.000000
attr:1 x = 38.000000 y = 22.000000
attr:1 x = 40.000000 y = 16.000000
attr:3 x = 44.000000 y = 40.000000
attr:3 x = 45.000000 y = 5.000000
attr:1 x = 46.000000 y = 32.000000
attr:3 x = 48.000000 y = 26.000000
attr:3 x = 50.000000 y = 12.000000
attr:3 x = 52.000000 y = 41.000000
attr:3 x = 54.000000 y = 29.000000
attr:3 x = 57.000000 y = 28.000000
交点:(14.991055,18.640429)
交点:(32.583691,10.643777)
交点:(39.052632,27.278195)
交点:(42.051437,34.989410)
交点:(42.815287,17.987261)
*/