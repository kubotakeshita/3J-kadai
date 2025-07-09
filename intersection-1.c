#include <stdio.h>

#define	LINENUM	8

typedef struct {	/* �_�̍��W */
	double	x ;
	double	y ;
} Axis ;

typedef struct {	/* ���� */
	Axis	s ;		/* ���[�_(start) */
	Axis	e ;		/* �E�[�_(end) */
} Line ;



/*
 *	2�̐������������邩�ǂ����𔻒f���C
 *	��������ꍇ�́C���̌�_��\������D
 */
Axis* InterSection( Line f, Line g )
{
	double a,b,c,d,s,t,u,v;
	a = f.s.x;
	b = f.s.y;
	c = f.e.x;
	d = f.e.y;
	s = g.s.x;
	t = g.s.y;
	u = g.e.x;
	v = g.e.y;
	
	if((c - a)*(t - b) <= (d - b)*(s - a))return NULL;
	if((c - a)*(v - b) >= (d - b)*(u - a))return NULL;
	if((u - s)*(d - t) <= (v - t)*(c - s))return NULL;
	if((u - s)*(b - t) >= (v - t)*(a - s))return NULL;
	
	Axis* ans;
	ans = (Axis*)malloc(sizeof(Axis));
	ans->x = ((a*(d - b)*(u - s)) - (s*(c - a)*(v - t)) + (c - a)*(u - s)*(t - b)) /
			 ((d - b)*(u - s) - (c - a)*(v - t));
	ans->y = (((d - b)*(ans->x - a))/(c - a)) + b;
	
	return ans;
}



int main( )
{
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

	int	i, j ;
	Axis* p;
	p = (Axis*)malloc(sizeof(Axis));

	for( i = 0 ; i < LINENUM ; i++ ) {
		for( j = 0 ; j < LINENUM ; j++ ) {
			p = InterSection( lines[i], lines[j] ) ;
			if(p != NULL) printf("��_�̍��W( %f , %f )\n",p->x,p->y);
		}
	}
}

/* ���s����
��_�̍��W( 14.991055 , 18.640429 )
��_�̍��W( 42.051437 , 34.989410 )
��_�̍��W( 32.583691 , 10.643777 )
��_�̍��W( 39.052632 , 27.278195 )
��_�̍��W( 42.815287 , 17.987261 )
*/