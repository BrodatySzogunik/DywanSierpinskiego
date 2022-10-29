// DywanSierpinskiego.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdlib.h>    
#include <time.h>       
#include <windows.h>
#include <iostream>
#include <gl/gl.h>

#include <gl/glut.h>


typedef float point2[2];

struct Colour {
	float R;
	float G;
	float B;
};


Colour randomColor() { //Funkcja tworzenia losowego koloru

	Colour colour;
	colour.R = ((float)rand()) / RAND_MAX * 2.0 - 0.5;
	colour.G = ((float)rand()) / RAND_MAX * 2.0 - 0.5;
	colour.B = ((float)rand()) / RAND_MAX * 2.0 - 0.5;

	return colour;
}

float perturbation(float levelOfDeformation) { //Funkcja losująca zmiane w punkcie w małym zakresie
	return (float)rand() / (float)(RAND_MAX / levelOfDeformation);
}

void printColorfulRectange(point2 point, float width) {

	
	float dividedWidth = width / 2;
	Colour color{ 0.0f, 0.0f, 0.0f };

	point2 a = { point[0] - dividedWidth,point[1] + dividedWidth },
		b = { point[0] - dividedWidth, point[1] - dividedWidth },
		c = { point[0] + dividedWidth, point[1] - dividedWidth },
		d = { point[0] + dividedWidth, point[1] + dividedWidth };

	glBegin(GL_POLYGON);

	color = randomColor();
	glColor3f(color.R, color.G, color.B);
	glVertex2fv(a);

	color = randomColor();
	glColor3f(color.R, color.G, color.B);
	glVertex2fv(b);

	color = randomColor();
	glColor3f(color.R, color.G, color.B);
	glVertex2fv(c);

	color = randomColor();
	glColor3f(color.R, color.G, color.B);
	glVertex2fv(d);

	glEnd();
}

void printWhiteRectange(point2 point, float width) {


	float dividedWidth = width / 2;
	Colour color{ 0.0f, 0.0f, 0.0f };

	point2 a = { point[0] - dividedWidth,point[1] + dividedWidth },
		b = { point[0] - dividedWidth, point[1] - dividedWidth },
		c = { point[0] + dividedWidth, point[1] - dividedWidth },
		d = { point[0] + dividedWidth, point[1] + dividedWidth };

	glBegin(GL_POLYGON);

	glColor3f(color.R, color.G, color.B);

	glVertex2fv(a);

	glVertex2fv(b);

	glVertex2fv(c);

	glVertex2fv(d);

	glEnd();

}

void generateCarpet(point2 point, float width, int level,int levelOfDeformation) {
	int dividedWidth = width / 3;
	// podzielona szerokość potrzebna do określenia pozycji pomniejszonych kwadratów
	//|	s1	s2	s3|
	//|	s4		s5|
	//|	s6	s7	s8|


	point[0] += perturbation(levelOfDeformation);
	point[1] += perturbation(levelOfDeformation);



	point2 s1 = { point[0] - dividedWidth, point[1] + dividedWidth },
		s2 = { point[0], point[1] + dividedWidth },
		s3 = { point[0] + dividedWidth, point[1] + dividedWidth },
		s4 = { point[0] - dividedWidth, point[1] },
		s5 = { point[0] + dividedWidth, point[1] },
		s6 = { point[0] - dividedWidth, point[1] - dividedWidth },
		s7 = { point[0] , point[1] - dividedWidth },
		s8 = { point[0] + dividedWidth, point[1] - dividedWidth };


	if (level > 0) {
		generateCarpet(s1, dividedWidth, level - 1 ,levelOfDeformation);
		generateCarpet(s2, dividedWidth, level - 1, levelOfDeformation);
		generateCarpet(s3, dividedWidth, level - 1, levelOfDeformation);
		generateCarpet(s4, dividedWidth, level - 1, levelOfDeformation);
		generateCarpet(s5, dividedWidth, level - 1, levelOfDeformation);
		generateCarpet(s6, dividedWidth, level - 1, levelOfDeformation);
		generateCarpet(s7, dividedWidth, level - 1, levelOfDeformation);
		generateCarpet(s8, dividedWidth, level - 1, levelOfDeformation);
	}
	else printColorfulRectange(point, width);

}

void cutCarpet(point2 point, float width, int level) {
	int dividedWidth = width / 3;
	// podzielona szerokość potrzebna do określenia pozycji pomniejszonych kwadratów
	//|	s1	s2	s3|
	//|	s4	s5	s6|
	//|	s7	s8	s9|

	point2 s1 = { point[0] - dividedWidth, point[1] + dividedWidth },
		s2 = { point[0], point[1] + dividedWidth },
		s3 = { point[0] + dividedWidth, point[1] + dividedWidth },
		s4 = { point[0] - dividedWidth, point[1] },
		s5 = { point[0], point[1] },
		s6 = { point[0] + dividedWidth, point[1] },
		s7 = { point[0] - dividedWidth, point[1] - dividedWidth },
		s8 = { point[0] , point[1] - dividedWidth },
		s9 = { point[0] + dividedWidth, point[1] - dividedWidth };

	


	if (level > 0) {
		cutCarpet(s1, dividedWidth, level - 1);
		cutCarpet(s2, dividedWidth, level - 1);
		cutCarpet(s3, dividedWidth, level - 1);
		cutCarpet(s4, dividedWidth, level - 1);
		cutCarpet(s6, dividedWidth, level - 1);
		cutCarpet(s7, dividedWidth, level - 1);
		cutCarpet(s8, dividedWidth, level - 1);
		cutCarpet(s9, dividedWidth, level - 1);
		printWhiteRectange(s5, dividedWidth);
	}
	else {
		return;
	}

}



void RenderScene(void) {


	point2 point = { 0,0 };



	int maximumLevelOfCarpet;
	int levelOfDeformation;

	std::cout << "podaj maksymalny poziom dywanu jaki ma zostać wyrenderowany:" << std::endl;
	std::cin >> maximumLevelOfCarpet;

	//std::cout << "podaj stopień deformacji dywanu:" << std::endl;
	//std::cin >> levelOfDeformation;

	for (int i = 0; i < maximumLevelOfCarpet; i++) {
		glClear(GL_COLOR_BUFFER_BIT);
		cutCarpet(point, 81, i);
		glFlush();
		Sleep(1000);
	}

}

void ChangeSize(GLsizei horizontal, GLsizei vertical)

// Parametry horizontal i vertical (szerokość i wysokość okna) są
// przekazywane do funkcji za każdym razem, gdy zmieni się rozmiar okna

{

	GLfloat AspectRatio;

	// Deklaracja zmiennej AspectRatio określającej proporcję wymiarów okna



	if (vertical == 0)
		// Zabezpieczenie pzred dzieleniem przez 0

		vertical = 1;


	glViewport(0, 0, horizontal, vertical);
	// Ustawienie wielkościokna okna urządzenia (Viewport)
	// W tym przypadku od (0,0) do (horizontal, vertical)


	glMatrixMode(GL_PROJECTION);
	// Określenie układu współrzędnych obserwatora

	glLoadIdentity();
	// Określenie przestrzeni ograniczającej

	AspectRatio = (GLfloat)horizontal / (GLfloat)vertical;
	// Wyznaczenie współczynnika proporcji okna

	// Gdy okno na ekranie nie jest kwadratem wymagane jest
	// określenie okna obserwatora.
	// Pozwala to zachować właściwe proporcje rysowanego obiektu
	// Do określenia okna obserwatora służy funkcja glOrtho(...)



	if (horizontal <= vertical)

		glOrtho(-100.0, 100.0, -100.0 / AspectRatio, 100.0 / AspectRatio, 1.0, -1.0);

	else

		glOrtho(-100.0 * AspectRatio, 100.0 * AspectRatio, -100.0, 100.0, 1.0, -1.0);

	glMatrixMode(GL_MODELVIEW);
	// Określenie układu współrzędnych    

	glLoadIdentity();

}


void Init(void) {
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	// ustawienie koloru czyszczenia na szary 
}



int main()
{

	srand(time(NULL));

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	// Ustawienie trybu wyświetlania
	// GLUT_SINGLE - pojedynczy bufor wyświetlania
	// GLUT_RGB - model kolorów RGB

	glutCreateWindow("Dywan Sierpinskiego");

	glutDisplayFunc(RenderScene);

	glutReshapeFunc(ChangeSize);

	Init();

	glutMainLoop();

}

