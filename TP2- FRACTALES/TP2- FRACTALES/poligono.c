#include "poligono.h"
#include <math.h>
#include <stdio.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5\allegro_color.h>

#define LINE_THICKNESS	5.0

#define PI		acos(-1.0)	//3.14159265358979323846

typedef struct {
	float x;
	float y;
} coordinates_t;


void draw_poligon(float l, float centreX, float centreY, int numPoints);


//===================================================================================================================================
//		poligon
//
//	Funcion recursiva que crea un fractal poligonal.
//	Este fractal presenta la siguiente din�mica:
//		-Se empieza con un poligono (N vertices) de longitud de lado l = lStart ubicado en (x, y).
//		-Se dibujan N poligonos, en cada uno de sus v�rtices de lado l� igual a l
//		 multiplicado por una constante = lConstant.
//		-La recursi�n termina cuando l es inferior a cierto valor lEnd.
//===================================================================================================================================


int poligon(float lStart,float lEnd, float lConstant, float centreX, float centreY, int numPoints)
{
	coordinates_t v;
	double angle = 2 * PI / numPoints;
	double radius = lStart / (2 * sin(PI / numPoints));		//radio del centro del poligono a sus vertices
	
	if (lStart < lEnd)
	{
		draw_poligon(lStart, centreX, centreY, numPoints);	//Como estoy en la longitud final, dibujo el ultimo poligono y vuelvo.
		return 0;
	}
		
	else
	{
		draw_poligon(lStart, centreX, centreY, numPoints);
		for (int k = 0; k <= numPoints; k++)
		{
			v.x = centreX + radius * sin(k * angle);	//Coordenadas (x,y) de un vertice
			v.y = centreY + radius * cos(k * angle);
			poligon(lStart*lConstant, lEnd, lConstant, v.x, v.y, numPoints);
		}

	}
	return 0;
}

//===================================================================================================================================
//		draw_poligon
//	Dibuja un poligono de N (numPoints) cantidad de vertices, con los lados de longitud l, con el centro del poligono
//	en las coordenadas (centreX, centreY).
//	Cada vez que se llama a la funcion dibuja el poligono de un color aleatorio.
//
//===================================================================================================================================



void draw_poligon(float l, float centreX, float centreY, int numPoints)
{
	double angle = 2 * PI / numPoints;		
	double radius = l / (2 * sin(PI / numPoints));		//radio del centro del poligono a sus vertices

	coordinates_t v1, v2;			
	ALLEGRO_COLOR color = al_map_rgb(rand() % 255, rand() % 255, rand() % 255);	//Color Aleatorio
	
	for (int i = 0, j = 1; i <= numPoints && j <= numPoints; i++, j++)
	{
		v1.x = centreX + radius * sin(i * angle);	//Coordenadas x, y de un vertice
		v1.y = centreY + radius * cos(i * angle);

		v2.x = centreX + radius * sin(j * angle);	////Coordenadas x, y de otro vertice
		v2.y = centreY + radius * cos(j * angle);

		al_draw_line(v1.x, v1.y, v2.x, v2.y, color, LINE_THICKNESS);
		al_flip_display();
	}
}