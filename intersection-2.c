#include <stdio.h>
#include <stdlib.h>

#define	LINENUM	8
#define	INTSECNUM	(LINENUM*LINENUM)
#define	EVENTNUM	(LINENUM+INTSECNUM)

#define	EVENTSTART	1	/* �����̍��[(start) */
#define	EVENTEND	2	/* �����̉E�[(end) */
#define	EVENTINTSCT	3	/* 2�̐����̌�_ */

typedef struct {	/* �_�̍��W */
	double	x ;
	double	y ;
} Axis ;

typedef struct {	/* ���� */
	Axis	s ;		/* ���[�_(start) */
	Axis	e ;		/* �E�[�_(end) */
} Line ;

typedef struct _Event {
	int		id ;				/* identifier */
	int		attr ;				/* 1:���_�C2:��_�C3:�E�_ */
	Line	line ;				/* ���� */
	double	x ;					/* ���[�_�E�E�[�_�E��_��x���W */
	double	y ;					/* ���[�_�E�E�[�_�E��_��x���W */
	struct _Event	*prev ;		/* �O�̃C�x���g */
	struct _Event	*next ;		/* ���̃C�x���g */
	struct _Event	*cline1 ;	/* �����������(1) */
	struct _Event	*cline2 ;	/* �����������(2) */
} Event ;

int	id = 1 ;	/* �C�x���g�̎��ʔԍ� */




/*
 *	Event�\���̂̃��X�g��\������D
 *	�����̃|�C���^�͕K���������X�g�̐擪���w���Ƃ͌���Ȃ����C
 *	�����ł͗^����ꂽ�|�C���^�����X�g�̐擪�Ƃ݂Ȃ��ĕ\������D
 */
void PrintEvents( Event *e )
{
	while( e != NULL ){
		printf( "attr:%d x = %f y = %f\n",e->attr, e->x, e->y );
		e = e->next;
	}
}



/*
 *	2�̃C�x���g�\���̂̃f�[�^���݂��Ɍ�������D
 *	�|�C���^�͕ύX���Ȃ��D
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
 *	�C�x���g�\���̂̐��`���X�g��x�����W�̒l�ŏ����Ƀ\�[�g���C
 *	���̐擪�A�h���X��Ԃ��D
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
 *	�C�x���g���X�g�����������C���̐��`���X�g�̐擪�A�h���X��Ԃ��D
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
 *	�C�x���g���X�gevent�ɐV�����C�x���gne��ǉ�����D
 *	�C�x���g��x�����W�Ɋւ��ď����ɐ��񂷂�悤�ɒǉ�����D
 *	event�̓C�x���g���X�g�̐擪�Ƃ͌���Ȃ��D
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
 *	2�̒������������邩�ǂ����𔻒f���C��������ꍇ�́C
 *	���̌�_��\���C�x���g��V���ɍ쐬����D
 *	��������ꍇ�͐V���ɍ쐻�����C�x���g���C
 *	�����łȂ��ꍇ��NULL��Ԃ��D
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
		printf("��_:(%f,%f)\n", inserted->x, inserted->y);
		return inserted;
	}
	return NULL;
}



/*
 *	2�̃C�x���g�\���̂Ɋ܂܂��������������ǂ����𔻒f����D

int	IsSameLine( Event *e1, Event *e2 )
{

	if(e1->line == e2->line)return 1;
	else return 0;
}
*/


/*
 *	�^����ꂽ�����ɑ΂��āC�^����ꂽ�_����������ɂ����1���C
 *	������艺�ɂ����-1���C������ɂ����0��Ԃ��D
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
 *	�������X�g�ɐV����������ǉ�����D
 *	�������X�g�́C�����̎n�_��y���W�Ɋւ��ď����ɐ��񂷂�D
 *	�������X�g��list[idx]�ɒǉ�����Ƃ��C
 *	���̊֐��̓��X�g�ɐ�����ǉ������ʒu��Ԃ����C
 *	�ǉ��Ɏ��s�����ꍇ��-1��Ԃ��D
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
 *	�������X�g����w�肳�ꂽ�������폜����D
 *	�폜���������Event�\���̂�list�����o�[�ŗ^������D
 *	�������X�g�́C�����̎n�_��y���W�Ɋւ��ď����ɐ��񂳂�Ă���D
 *	�������X�g��list[idx]���폜����Ƃ��C�Ԃ�l��idx�ł���D
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
 *	list[]���ׂ̗荇������e1��e2�̏��Ԃ����ւ���D
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
 *	���ʑ������s���D
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
	Event	*event ;		/* �C�x���g���X�g */

	Line lines[LINENUM] = {	/* �������X�g */
		 4, 12, 52, 41,	/* ���_(x,y),�E�_(x,y)�̏� */
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
��_:(14.991055,18.640429)
��_:(32.583691,10.643777)
��_:(39.052632,27.278195)
��_:(42.051437,34.989410)
��_:(42.815287,17.987261)
*/