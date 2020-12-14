#pragma once
#include<math.h>
#include<vector>
#include "ObjLoader.h"
#include "Texture.h"
#include "Car�ontrolSystem.h"
#include "MyOGL.h"
#include "DrawBezierAndHermit.h"

using namespace std;

extern Texture HauseTex, UnderTex, Hause2Tex;
extern ObjFile HauseObj, UnderObj, Hause2Obj, Under2Obj;

//�����
extern Texture LandTex;
extern ObjFile LandObj, StartObj;

extern Car�ontrolSystem Car;

Vector3 HausePosition(10, 10, 0);
Vector3 Hause2Position(-15, 10, 0);
vector<Point> Start = { Point(0, 0, 0), Point(0, 0, 0), Point(0, 0, 5), Point(0, 0, 5) };

const double Hause_x_max = 6;
const double Hause_x_min = -6;
const double Hause_y_max = 6.9;
const double Hause_y_min = -6.9;
const double Hause_R = 9.5;
const double Hause2_R = 9;

double Hause_x_maxNow;
double Hause_x_minNow;
double Hause_y_maxNow;
double Hause_y_minNow;

void UpdatePointHause() {
	Hause_x_maxNow = Hause_x_max - HausePosition.X();
	Hause_x_minNow = Hause_x_min - HausePosition.X();
	Hause_y_maxNow = Hause_y_max - HausePosition.Y();
	Hause_y_minNow = Hause_y_min - HausePosition.Y();
}

double MoveZ() {
	double matrix[3][3] = {
		{cos(Car.AngleZ * PI / 180), -1 * sin(Car.AngleZ * PI / 180), 0},
		{sin(Car.AngleZ * PI / 180), cos(Car.AngleZ * PI / 180), 0},
		{0, 0, 1}
	};
	return  SearchDeterminantMatrix3(matrix);
}

void StopCarHause() {
	double CD = sqrt(pow(Car.CarPosition.X() - HausePosition.X(), 2) + pow(Car.CarPosition.Y() - HausePosition.Y(), 2)) - Car.R - Hause_R;
	double CD2 = sqrt(pow(Car.CarPosition.X() - Hause2Position.X(), 2) + pow(Car.CarPosition.Y() - Hause2Position.Y(), 2)) - Car.R - Hause2_R;
	if (CD == 0 || CD2 == 0) {
		Car.KeyDuration_W = 0;
	}
	else {
		Car.Stop = false;
	}
	if (CD < 0 || CD2 < 0) {
		Car.Stop = true;
		Car.CarPosition = Car.CarPosition_back;
	}
	else {
		Car.Stop = false;
	}
}

vector<Point> PlanePoint = { Point(50, 50, 10), Point(-100, -100, 3), Point(50, 50, 14), Point(-100, 100, 4) };
//������ ��� ����� � ������� � ��������
extern Texture PlaneTex, FlapsTex, HeliceTex, RearFlapTex, WheelsTex;
extern ObjFile PlaneObj, FlapsObj, HeliceObj, RearFlapObj, WheelsObj;

void DrawPlane() {
	static double t_max = 0;
	static double t_max_next = 0;
	static bool flag_tmax = true;

	//��������� �������
	double delta_time = Search_delta_time();
	double go = delta_time / 5; //t_max ���������� = 1 �� 5 ������
	//t_max ���� �� ���� ���������� �� 0 �� 1 ���������� �� ����� � �����
	if (flag_tmax) {
		t_max += go;
		t_max_next = t_max + go;
		if (t_max > 1) {
			t_max = 1;
			flag_tmax = false;
		}
		if (t_max_next > 1) {
			t_max_next = 1;
		}
	}
	else {
		t_max -= go;
		t_max_next = t_max - go;
		if (t_max < 0) {
			t_max = 0;
			flag_tmax = true;
		}
		if (t_max_next < 0) {
			t_max_next = 0;
		}
	}

	glPushMatrix();

	Point point = BezierCurve3(PlanePoint[0], PlanePoint[1], PlanePoint[2], PlanePoint[3], t_max);
	Point next_point = BezierCurve3(PlanePoint[0], PlanePoint[1], PlanePoint[2], PlanePoint[3], t_max_next);
	point.Translated();
	glRotated(-90, 0, 0, 1);
	MoveAxis(point, next_point);
	PlaneTex.bindTexture();
	PlaneObj.DrawObj();

	glPopMatrix();
}
//��������� �����
void MovePovStart() {
	static double t_max = 0;
	static double t_max_next = 0;
	static bool flag_tmax = true;

	//��������� �������
	double delta_time = Search_delta_time();
	double go = delta_time / 5; //t_max ���������� = 1 �� 5 ������
	//t_max ���� �� ���� ���������� �� 0 �� 1 ���������� �� ����� � �����
	if (flag_tmax) {
		t_max += go;
		t_max_next = t_max + go;
		if (t_max > 1) {
			t_max = 1;
			flag_tmax = false;
		}
		if (t_max_next > 1) {
			t_max_next = 1;
		}
	}
	else {
		t_max -= go;
		t_max_next = t_max - go;
		if (t_max < 0) {
			t_max = 0;
			flag_tmax = true;
		}
		if (t_max_next < 0) {
			t_max_next = 0;
		}
	}

	//��������� ������� ������
	//��������� ����
	glDisable(GL_LIGHTING);
	//��������� ��������
	glDisable(GL_TEXTURE_2D);
	//�������� ����� ����������
	glEnable(GL_BLEND);
	////������ ����� ��� ������������� ��������� � ���������
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor3d(0.5, 0.2, 0.4);
	glColor4d(0.4, 0.6, 0.4, 0.6);

	glPushMatrix();

	Point point = BezierCurve3(Start[0], Start[1], Start[2], Start[3], t_max);
	Point next_point = BezierCurve3(Start[0], Start[1], Start[2], Start[3], t_max_next);
	point.Translated();
	glRotated(90, 0, 0, 1);
	StartObj.DrawObj();
	glPopMatrix();

	//��������� ����� ����������
	glDisable(GL_BLEND);
	//�������� ����
	glEnable(GL_LIGHTING);
	//�������� ��������
	glEnable(GL_TEXTURE_2D);
}

void WorkLand() {

	//������ �����
	glPushMatrix();
	glTranslated(HausePosition.X(), HausePosition.Y(), HausePosition.Z());
	glRotated(180, 0, 0, 1);
	//�����
	UnderTex.bindTexture();
	UnderObj.DrawObj();
	//���
	HauseTex.bindTexture();
	HauseObj.DrawObj();
	glPopMatrix();

	glPushMatrix();
	glTranslated(Hause2Position.X(), Hause2Position.Y(), Hause2Position.Z());
	glRotated(180, 0, 0, 1);
	//�����
	UnderTex.bindTexture();
	Under2Obj.DrawObj();


	//���2
	Hause2Tex.bindTexture();
	Hause2Obj.DrawObj();
	glPopMatrix();

	//������ �����
	glDisable(GL_TEXTURE_2D);
	glPushMatrix();
	glColor3d(.0, .0, .0);
	LandObj.DrawObj();
	glPopMatrix();

	glEnable(GL_TEXTURE_2D);
	//�������� �� �����
	StopCarHause();

	DrawPlane();

	//��������� ������� ������
	MovePovStart();
}
