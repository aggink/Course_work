#pragma once
#include<vector>
#include <math.h>
#include"MyShaders.h"
#include "Plane�ontrolSystem.h"
#include "MyOGL.h"
#include "CustomCamera.h"
#include "Texture.h"
#include "ObjLoader.h"
#include <ctime>
using namespace std;

//������ ��� ����� � ������� � ��������
extern Texture PlaneTex, FlapsTex, HeliceTex, RearFlapTex, WheelsTex;
extern ObjFile PlaneObj, FlapsObj, HeliceObj, RearFlapObj, WheelsObj;



//���������� ��� ������ � ��������� ��������
extern Plane�ontrolSystem Plane;

//��������� ����� ������
extern bool freeCamera;

//������� ������ ������
extern CustomCamera  camera;

//����� ���������� �����
extern double TimeLastFrame;

//������� ����� �����
void NewPositionPlane() {
	if (Plane.KeyDuration_W > 15) {
		Plane.KeyDuration_W = 15;
	}
	Plane.PlanePosition.setCoord_X(Plane.PlanePosition.X() + Plane.SpeedPlane * cos(Plane.AngleY * PI / 180) * cos(Plane.AngleZ * PI / 180) * (Plane.KeyDuration_W / 5));
	Plane.PlanePosition.setCoord_Y(Plane.PlanePosition.Y() + Plane.SpeedPlane * cos(Plane.AngleY * PI / 180) * sin(Plane.AngleZ * PI / 180) * (Plane.KeyDuration_W / 5));
	Plane.PlanePosition.setCoord_Z(Plane.PlanePosition.Z() + Plane.SpeedPlane * sin(Plane.AngleY * PI / 180) * (Plane.KeyDuration_W / 5));
}

void NewPositionFlaps() {
	if (Plane.KeyDuration_W > 15) {
		Plane.KeyDuration_W = 15;
	}
	Plane.FlapsPosition.setCoord_X(Plane.FlapsPosition.X() + Plane.SpeedPlane * cos(Plane.AngleY * PI / 180) * cos(Plane.AngleZ * PI / 180) * (Plane.KeyDuration_W / 5));
	Plane.FlapsPosition.setCoord_Y(Plane.FlapsPosition.Y() + Plane.SpeedPlane * cos(Plane.AngleY * PI / 180) * sin(Plane.AngleZ * PI / 180) * (Plane.KeyDuration_W / 5));
	Plane.FlapsPosition.setCoord_Z(Plane.FlapsPosition.Z() + Plane.SpeedPlane * sin(Plane.AngleY * PI / 180) * (Plane.KeyDuration_W / 5));
}

void NewPositionRearFlap() {
	if (Plane.KeyDuration_W > 15) {
		Plane.KeyDuration_W = 15;
	}
	Plane.RearFlapPosition.setCoord_X(Plane.RearFlapPosition.X() + Plane.SpeedPlane * cos(Plane.AngleY * PI / 180) * cos(Plane.AngleZ * PI / 180) * (Plane.KeyDuration_W / 5));
	Plane.RearFlapPosition.setCoord_Y(Plane.RearFlapPosition.Y() + Plane.SpeedPlane * cos(Plane.AngleY * PI / 180) * sin(Plane.AngleZ * PI / 180) * (Plane.KeyDuration_W / 5));
	Plane.RearFlapPosition.setCoord_Z(Plane.RearFlapPosition.Z() + Plane.SpeedPlane * sin(Plane.AngleY * PI / 180) * (Plane.KeyDuration_W / 5));
}

void NewPositionWheels() {
	if (Plane.KeyDuration_W > 15) {
		Plane.KeyDuration_W = 15;
	}
	Plane.WheelsPosition.setCoord_X(Plane.WheelsPosition.X() + Plane.SpeedPlane * cos(Plane.AngleY * PI / 180) * cos(Plane.AngleZ * PI / 180) * (Plane.KeyDuration_W / 5));
	Plane.WheelsPosition.setCoord_Y(Plane.WheelsPosition.Y() + Plane.SpeedPlane * cos(Plane.AngleY * PI / 180) * sin(Plane.AngleZ * PI / 180) * (Plane.KeyDuration_W / 5));
	Plane.WheelsPosition.setCoord_Z(Plane.WheelsPosition.Z() + Plane.SpeedPlane * sin(Plane.AngleY * PI / 180) * (Plane.KeyDuration_W / 5));
}

void NewPositionHelice() {
	if (Plane.KeyDuration_W > 15) {
		Plane.KeyDuration_W = 15;
	}
	Plane.HelicePosition.setCoord_X(Plane.HelicePosition.X() + Plane.SpeedPlane * cos(Plane.AngleY * PI / 180) * cos(Plane.AngleZ * PI / 180) * (Plane.KeyDuration_W / 5));
	Plane.HelicePosition.setCoord_Y(Plane.HelicePosition.Y() + Plane.SpeedPlane * cos(Plane.AngleY * PI / 180) * sin(Plane.AngleZ * PI / 180) * (Plane.KeyDuration_W / 5));
	Plane.HelicePosition.setCoord_Z(Plane.HelicePosition.Z() + Plane.SpeedPlane * sin(Plane.AngleY * PI / 180) * (Plane.KeyDuration_W / 5));
}
//������ ������ ��������� ������
void NewPositionCamera() {

	Vector3 tmp{
		Plane.PlanePosition.X() - Plane.DistanceFromPlane * cos(Plane.AngleY * PI / 180),
		Plane.PlanePosition.Y() - Plane.DistanceFromPlane * cos(Plane.AngleY * PI / 180),
		Plane.PlanePosition.Z() + Plane.HeightFromPlane * sin(Plane.AngleY * PI / 180)
	};
	camera.pos = tmp;
	camera.camDist = 30;
	camera.SetLookPoint(Plane.PlanePosition);
}

//����������� ��������� � ������� ������ ��� ����������
void ObjectDeceleration_Key_W() {
	//���� ����� ������� ��������
	NewPositionPlane();
	if (!freeCamera) {
		NewPositionCamera();
	}
}

//���������� ������� ������ ��� ��������
void UpdateParameters() {
	//�������� ������� �����
	double end = clock();

	//����� �����
	double TimeFrame = (end - TimeLastFrame) / CLOCKS_PER_SEC;

	if (TimeFrame > 2) {
		return;
	}

	//���������� ������� ��� �������� ������, ���� �� ������ ������� W � S
	if (!OpenGL::isKeyPressed('W') && !OpenGL::isKeyPressed('S') && Plane.KeyDuration_W > 0) {
		//���������, ���� ����� ������� W �� ���� � �����
		if (Plane.KeyDuration_W - TimeFrame < 0) {
			Plane.KeyDuration_W = 0;
		}
		else
		{
			Plane.KeyDuration_W -= TimeFrame;
			//������� ����� ���������� �������, � ����� ������ ����� ��������� ������
			ObjectDeceleration_Key_W();
		}
		//������������� ���� �� ������ ����� ����������
		Plane.FlagAccAfterDec = true;
	}

	//������� ���������� ��� �������� �����
	if (!OpenGL::isKeyPressed('S') && !OpenGL::isKeyPressed('W') && Plane.KeyDuration_W < 0)
	{
		if (Plane.KeyDuration_W + TimeFrame > 0)
			Plane.KeyDuration_W = 0;
		else
		{
			Plane.KeyDuration_W += TimeFrame;
			//������� ����� ���������� �������, � ����� ������ ����� ��������� ������
			ObjectDeceleration_Key_W();
		}
	}

	//���������� ��� �������� ������, ������ ������ S
	if (OpenGL::isKeyPressed('S') && !OpenGL::isKeyPressed('W') && Plane.KeyDuration_W > 0)
	{
		if (Plane.KeyDuration_W - Plane.SpeedSlow < 0)
			Plane.KeyDuration_W = 0;
		else
		{
			Plane.KeyDuration_W -= Plane.SpeedSlow;
			ObjectDeceleration_Key_W();
		}

	}

	//���������� ��� �������� �����
	if (OpenGL::isKeyPressed('W') && !OpenGL::isKeyPressed('S') && Plane.KeyDuration_W < 0)
	{
		if (Plane.KeyDuration_W + Plane.SpeedSlow > 0)
			Plane.KeyDuration_W = 0;
		else
		{
			Plane.KeyDuration_W += Plane.SpeedSlow;
			ObjectDeceleration_Key_W();
		}
	}

	//�������� ������, ������ ������ W
	if (OpenGL::isKeyPressed('W') && !OpenGL::isKeyPressed('S') && Plane.KeyDuration_W >= 0)
	{
		//���������, ���� �� ������ ������
		if (!Plane.FlagAcceleration)
		{
			Plane.FlagAcceleration = true;
		}
		else
		{
			//���� ����� ������� ��������
			NewPositionPlane();
			if (!freeCamera)
			{
				NewPositionCamera();
			}

			//����������
			Plane.KeyDuration_W += TimeFrame;
		}
	}

	//�������� �����, ������ ������ S
	if (OpenGL::isKeyPressed('S') && !OpenGL::isKeyPressed('W') && Plane.KeyDuration_W <= 0)
	{
		if (!Plane.FlagDeceleration)
		{
			Plane.FlagDeceleration = true;
		}
		else
		{
			NewPositionPlane();
			if (!freeCamera)
			{
				NewPositionCamera();
			}
			//�����������
			Plane.KeyDuration_W -= TimeFrame;
		}
	}

	//������� ����� 38
	//������� ���� 40
	//������� ������ 39
	//������� ����� 37

	//������������ ������ �������� ������
	if (OpenGL::isKeyPressed(39)) {
		if (Plane.AngleRearFlap + Plane.SpeedRearFlap > Plane.MaxAnglRearFlap + Plane.AngleZ) {
			Plane.AngleRearFlap = Plane.MaxAnglRearFlap + Plane.AngleZ;
		}
		else
		{
			Plane.AngleRearFlap += Plane.SpeedRearFlap;
		}

		//����������� ������ ��������
		if (Plane.KeyDuration_W != 0) {
			Plane.AngleZ += Plane.SpeedRearFlap / 10;
		}
	}

	//������������ ������ �������� �����
	if (OpenGL::isKeyPressed(37)) {
		if (Plane.AngleRearFlap - Plane.SpeedRearFlap < -1 * Plane.MaxAnglRearFlap + Plane.AngleZ) {
			Plane.AngleRearFlap = -1 * Plane.MaxAnglRearFlap + Plane.AngleZ;
		}
		else
		{
			Plane.AngleRearFlap -= Plane.SpeedRearFlap;
		}

		//����������� ������ ��������
		if (Plane.KeyDuration_W != 0) {
			Plane.AngleZ -= Plane.SpeedRearFlap / 10;
		}
	}

	//���������� ���������� ������ �������� ����� 
	if (!OpenGL::isKeyPressed(37) && !OpenGL::isKeyPressed(39) && Plane.AngleRearFlap < Plane.AngleZ) 
	{
		if (Plane.AngleRearFlap + Plane.SpeedRearFlapReverse > Plane.AngleZ)
		{
			Plane.AngleRearFlap = Plane.AngleZ;
		}
		else
		{
			Plane.AngleRearFlap += Plane.SpeedRearFlapReverse;
		}
	}

	//���������� ���������� ������ �������� ����� 
	if (!OpenGL::isKeyPressed(37) && !OpenGL::isKeyPressed(39) && Plane.AngleRearFlap > Plane.AngleZ) 
	{
		if (Plane.AngleRearFlap - Plane.SpeedRearFlapReverse < Plane.AngleZ)
		{
			Plane.AngleRearFlap = Plane.AngleZ;
		}
		else
		{
			Plane.AngleRearFlap -= Plane.SpeedRearFlapReverse;
		}
	}

	//������ �����
	if (OpenGL::isKeyPressed(38)) {
		if (Plane.AngleFlaps + Plane.SpeedFlaps > Plane.MaxAngleFlaps + Plane.AngleY) {
			Plane.AngleFlaps = Plane.MaxAngleFlaps + Plane.AngleY;
		}
		else
		{
			Plane.AngleFlaps += Plane.SpeedFlaps;
		}

		//����������� ������ ��������
		if (Plane.KeyDuration_W != 0) {
			Plane.AngleY += Plane.SpeedFlaps / 10;
		}
	}

	//������ ����
	if (OpenGL::isKeyPressed(40)) {
		if (Plane.AngleFlaps - Plane.SpeedFlaps < -1 * Plane.MaxAngleFlaps + Plane.AngleY) {
			Plane.AngleFlaps = -1 * Plane.MaxAngleFlaps + Plane.AngleY;
		}
		else
		{
			Plane.AngleFlaps -= Plane.SpeedFlaps;
		}

		//����������� ������ ��������
		if (Plane.KeyDuration_W != 0) {
			Plane.AngleY -= Plane.SpeedFlaps / 10;
		}
	}

	//���������� ���������� �������� ����� 
	if (!OpenGL::isKeyPressed(38) && !OpenGL::isKeyPressed(40) && Plane.AngleFlaps < Plane.AngleY) 
	{
		if (Plane.AngleFlaps + Plane.SpeedFlapsReverse > Plane.AngleY)
		{
			Plane.AngleFlaps = Plane.AngleY;
		}
		else
		{
			Plane.AngleFlaps += Plane.SpeedFlapsReverse;
		}
	}

	//���������� ���������� �������� ����� 
	if (!OpenGL::isKeyPressed(38) && !OpenGL::isKeyPressed(40) && Plane.AngleFlaps > Plane.AngleY)
	{
		if (Plane.AngleFlaps - Plane.SpeedFlapsReverse < Plane.AngleY)
		{
			Plane.AngleFlaps = Plane.AngleY;
		}
		else
		{
			Plane.AngleFlaps -= Plane.SpeedFlapsReverse;
		}
	}

	//P - ������� � �������� ���������
	if (OpenGL::isKeyPressed('P')) {
		Plane = Plane�ontrolSystem();
	}
}


void WorkPlane() {

	
}