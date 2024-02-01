#include "graphics.h"
#include <iostream>
#include <math.h>
#include <stdlib.h>  
#include <ctype.h>
#include "CustomGraphics.h"


using namespace std;

//dichiarazione dei prototipi delle funzioni "fun" e "sol"
double fun(double t);
double sol(double t);
double imp(double t);
int pspice(double *t, double *v);

int APIENTRY WinMain

(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//inizializzazione della schermata e dichiarazione delle variabili
	initwindow(850, 610);
	setbkcolor(15);
	setcolor(15);
	int n, i;
	bar(0, 0, 850, 610);
	double a, b, c;
	double t, x, t1, x1;
	double rx, ry;
	double h;
	double x1prec, x1suc, x2prec, x2suc;
	double tempo[800], v[800];
	/*inizializzazione degli assi cartesiani, dei coefficienti del modello
	matematico del sistema e del passo di discretizzazione*/
	rx = 0.08;
	ry = 0.05;
	a = 1;
	b = 200;
	c = 100000;
	//trac ciamento degli assi
	assi(rx, ry, 0);
	//Grafico della soluzione analitica
	t = 0;
	do
	{
		x = sol(t);
		tracciapixel(t, x, rx, ry, 3, 0);
		t = t + 0.00001;
	} while (t < rx);
	setcolor(3);
	outtextxy(650, 500, "Soluzione analitica");
	getch();
	//Grafico dell'algoritmo di Eulero esplicito
	t = 0;
	x1prec = 0;
	x2prec = 0;
	h = 0.00001;
	do
	{
		x1suc = x2prec*h + x1prec;
		x2suc = (h / a)*(fun(t) - c*x1prec - b*x2prec) + x2prec;
		//tracciapixel(t, x, rx, ry, 11, 0);
		t1 = t + h;
		tracciasegmento(t, x1prec, t1, x1suc, rx, ry, 5, 0);
		t = t1;
		x1prec = x1suc;
		x2prec = x2suc;
	} while (t < rx);
	setcolor(5);
	outtextxy(650, 530, "Eulero esplicito");
	getch();


	n = pspice(tempo, v);      //soluzione pspice
	for (i = 0; i < n; i++)
		//tracciapunto(tempo[i], v[i], rx, ry, 4, 0);
		tracciapixel(tempo[i], v[i], rx, ry, 4, 0);
	setcolor(4);
	outtextxy(650, 560, "pspice");
	getch();
	return (0);

}

//definizione della funzione "fun", contenente il segnale in ingresso
double fun(double t)
{
	double f;
	f = 10 * imp(t);
	return(f);
}

//definizione della funzione "sol", contenente la soluzione analitica del sistema
double sol(double t)
{
	double f;
	f = (1 / 30.0)*sin(300 * t)*exp(-100 * t);
	return(f);
}

double imp(double t)
{
	double e;
	if (t <0.00001)
		e = 100000;
	else
		e = 0;
	return e;
}


int pspice(double *t, double *v)
{
	FILE *fp;

	int i;
	fp = fopen("dati.txt", "r");
	i = 0;
	while (!feof(fp))
	{
		fscanf(fp, "%lf", &t[i]);
		fscanf(fp, "%lf", &v[i]);
		i++;
	}
	return(i);
}
