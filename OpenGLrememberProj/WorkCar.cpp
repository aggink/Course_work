#pragma once
#include<vector>
#include <math.h>
#include"MyShaders.h"
#include "Car�ontrolSystem.h"
#include "MyOGL.h"
#include "CustomCamera.h"
#include "Texture.h"
#include "ObjLoader.h"
#include <ctime>
using namespace std;

//������ ��� ����� � ������� � ��������
extern ObjFile CarObj, CarWheelObj, CarPlayLObj, CarPlayRObj, CarStopLObj, CarStopLPovObj, CarStopRObj, CarStopRPovObj;
extern Texture CarTex, CarWheelTex, CarPlay1Tex, CarStop1Tex, CarStop2Tex;
//������ ��� �������� (������ ����� ���������� � ������������ ��������
extern vector<Shader> shader;
//���������� ��� ������ � ��������� 
extern Car�ontrolSystem Car;
//��������� ����� ������
extern bool freeCamera;
//���������� ���������� �� ������ � �������
extern CustomCamera camera;
//����� ���������� �����
extern double TimeLastFrame;


//������� ����� �����
void NewPositionCar() {
	if (Car.KeyDuration_W > 10) {
		Car.KeyDuration_W = 10;
	}
	if (!Car.Stop) {
		Car.CarPosition_back = Car.CarPosition;
	}
	Car.CarPosition.setCoord_X(Car.CarPosition.X() + Car.Speed * cos(Car.AngleZ * PI / 180) * (Car.KeyDuration_W / 5));
	Car.CarPosition.setCoord_Y(Car.CarPosition.Y() + Car.Speed * sin(Car.AngleZ * PI / 180) * (Car.KeyDuration_W / 5));

	Car.Car_x_maxNow = Car.Car_x_maxNow + Car.Speed * cos(Car.AngleZ * PI / 180) * (Car.KeyDuration_W / 5);
	Car.Car_x_minNow = Car.Car_x_minNow + Car.Speed * cos(Car.AngleZ * PI / 180) * (Car.KeyDuration_W / 5);
	Car.Car_y_maxNow = Car.Car_y_maxNow + Car.Speed * sin(Car.AngleZ * PI / 180) * (Car.KeyDuration_W / 5);
	Car.Car_y_minNow = Car.Car_y_minNow + Car.Speed * sin(Car.AngleZ * PI / 180) * (Car.KeyDuration_W / 5);
}

//������ ������ ��������� ������
void NewPositionCamera_Car() {

	Vector3 tmp{
		Car.CarPosition.X() - Car.Distance * cos(Car.AngleZ * PI / 180),
		Car.CarPosition.Y() - Car.Distance * sin(Car.AngleZ * PI / 180),
		Car.CarPosition.Z() + Car.Height
	};
	camera.pos = tmp;
	camera.camDist = 30;
	camera.SetLookPoint(Car.CarPosition);
}

//����������� ��������� � ������� ������ ��� ����������
void ObjectDeceleration_Key_W_Car() {
	//���� ����� ������� ��������
	NewPositionCar();
	if (!freeCamera) {
		NewPositionCamera_Car();
	}
}

//���������� ������� ������ 
void UpdateParameters_Car() {
	//�������� ������� �����
	double end = clock();

	//����� �����
	double TimeFrame = (end - TimeLastFrame) / CLOCKS_PER_SEC;

	if (TimeFrame > 2) {
		return;
	}

	//���������� ������� ��� �������� ������, ���� �� ������ ������� W � S
	if (!OpenGL::isKeyPressed('W') && !OpenGL::isKeyPressed('S') && Car.KeyDuration_W > 0) {
		//���������, ���� ����� ������� W �� ���� � �����
		if (Car.KeyDuration_W - TimeFrame < 0) {
			Car.KeyDuration_W = 0;
		}
		else
		{
			Car.KeyDuration_W -= TimeFrame;
			//������� ����� ���������� �������, � ����� ������ ����� ��������� ������
			ObjectDeceleration_Key_W_Car();
		}
		//������������� ���� �� ������ ����� ����������
	    Car.FlagAccAfterDec = true;
	}

	//������� ���������� ��� �������� �����
	if (!OpenGL::isKeyPressed('W') && !OpenGL::isKeyPressed('S') && Car.KeyDuration_W < 0)
	{
		if (Car.KeyDuration_W + TimeFrame > 0)
			Car.KeyDuration_W = 0;
		else
		{
			Car.KeyDuration_W += TimeFrame;
			//������� ����� ���������� �������, � ����� ������ ����� ��������� ������
			ObjectDeceleration_Key_W_Car();
		}
	}

	//���������� ��� �������� ������, ������ ������ S
	if (OpenGL::isKeyPressed('S') && !OpenGL::isKeyPressed('W') && Car.KeyDuration_W > 0)
	{
		if (Car.KeyDuration_W - Car.SpeedSlow < 0)
			Car.KeyDuration_W = 0;
		else
		{
			Car.KeyDuration_W -= Car.SpeedSlow;
			ObjectDeceleration_Key_W_Car();
		}

	}

	//���������� ��� �������� �����
	if (OpenGL::isKeyPressed('W') && !OpenGL::isKeyPressed('S') && Car.KeyDuration_W < 0)
	{
		if (Car.KeyDuration_W + Car.SpeedSlow < 0)
			Car.KeyDuration_W = 0;
		else
		{
			Car.KeyDuration_W += Car.SpeedSlow;
			ObjectDeceleration_Key_W_Car();
		}
	}

	//�������� ������, ������ ������ W
	if (OpenGL::isKeyPressed('W') && !OpenGL::isKeyPressed('S') && Car.KeyDuration_W >= 0)
	{
		//���������, ���� �� ������ ������
		if (!Car.FlagAcceleration)
		{
			Car.FlagAcceleration = true;
		}
		else
		{
			//���� ����� ������� ��������
			NewPositionCar();
			if (!freeCamera)
			{
				NewPositionCamera_Car();
			}

			//����������
			Car.KeyDuration_W += TimeFrame;
		}
	}

	//�������� �����, ������ ������ S
	if (OpenGL::isKeyPressed('S') && !OpenGL::isKeyPressed('W') && Car.KeyDuration_W <= 0)
	{
		if (!Car.FlagDeceleration)
		{
			Car.FlagDeceleration = true;
		}
		else
		{
			NewPositionCar();
			if (!freeCamera)
			{
				NewPositionCamera_Car();
			}
			//�����������
			Car.KeyDuration_W -= TimeFrame;
		}
	}

	//������������ ������
	if (OpenGL::isKeyPressed('D')) {
		if (Car.AngleWheel - Car.SpeedWheel < -1 * Car.MaxAngleWheel + Car.AngleZ) {
			Car.AngleWheel = -1 * Car.MaxAngleWheel + Car.AngleZ;
		}
		else
		{
			Car.AngleWheel -= Car.SpeedWheel;
		}

		//����������� ������ ��������
		if (OpenGL::isKeyPressed('W')) {
			Car.AngleZ -= Car.SpeedWheel / 10;
		}
		if (OpenGL::isKeyPressed('S')) {
			Car.AngleZ += Car.SpeedWheel / 10;
		}
	}

	//������������ �����
	if (OpenGL::isKeyPressed('A')) {
		if (Car.AngleWheel + Car.SpeedWheel > Car.MaxAngleWheel + Car.AngleZ) {
			Car.AngleWheel = Car.MaxAngleWheel + Car.AngleZ;
		}
		else
		{
			Car.AngleWheel += Car.SpeedWheel;
		}

		//����������� ������ ��������
		if (OpenGL::isKeyPressed('W')) {
			Car.AngleZ += Car.SpeedWheel / 10;
		}
		if (OpenGL::isKeyPressed('S')) {
			Car.AngleZ -= Car.SpeedWheel / 10;
		}
	}

	//���������� ���������� ����� 
	if (!OpenGL::isKeyPressed('A') && !OpenGL::isKeyPressed('D') && Car.AngleWheel < Car.AngleZ)
	{
		if (Car.AngleWheel + Car.SpeedWheelReverse > Car.AngleZ)
		{
			Car.AngleWheel = Car.AngleZ;
		}
		else
		{
			Car.AngleWheel += Car.SpeedWheelReverse;
		}
	}

	//���������� ���������� ����� 
	if (!OpenGL::isKeyPressed('A') && !OpenGL::isKeyPressed('D') && Car.AngleWheel > Car.AngleZ)
	{
		if (Car.AngleWheel - Car.SpeedWheelReverse < Car.AngleZ)
		{
			Car.AngleWheel = Car.AngleZ;
		}
		else
		{
			Car.AngleWheel -= Car.SpeedWheelReverse;
		}
	}
	//P - ������� � �������� ���������
	if (OpenGL::isKeyPressed('P')) {
		Car = Car�ontrolSystem();
	}
	//������ ����
	if (OpenGL::isKeyPressed(32)) {
		Car.KeyDuration_W = 0;
	}
}

//������� �����
void PositionWheels(int i) {

	//x +
	double a = 1.08;
	//y
	double b = 0.65;
	//x -
	double c = 1.03;
	//������
	double d = 0.27;

	Vector3 p;
	switch (i) {
	case 1:
		//�����
		p = Vector3(
			Car.CarPosition.X() + a * cos(Car.AngleZ * PI / 180) - b * sin(Car.AngleZ * PI / 180),
			Car.CarPosition.Y() + b * cos(Car.AngleZ * PI / 180) + a * sin(Car.AngleZ * PI / 180),
			Car.CarPosition.Z() + d);
		break;
	case 2:
		//������
		p = Vector3(
			Car.CarPosition.X() + a * cos(Car.AngleZ * PI / 180) + b * sin(Car.AngleZ * PI / 180),
			Car.CarPosition.Y() - b * cos(Car.AngleZ * PI / 180) + a * sin(Car.AngleZ * PI / 180),
			Car.CarPosition.Z() + d);
		break;
	case 3:
		//����� ������
		p = Vector3(
			Car.CarPosition.X() - c * cos(Car.AngleZ * PI / 180) - b * sin(Car.AngleZ * PI / 180),
			Car.CarPosition.Y() + b * cos(Car.AngleZ * PI / 180) - c * sin(Car.AngleZ * PI / 180),
			Car.CarPosition.Z() + d);
		break;
	case 4:
		//������ ������
		 p = Vector3(
			Car.CarPosition.X() - c * cos(Car.AngleZ * PI / 180) + b * sin(Car.AngleZ * PI / 180),
			Car.CarPosition.Y() - b * cos(Car.AngleZ * PI / 180) - c * sin(Car.AngleZ * PI / 180),
			Car.CarPosition.Z() + d);
		break;
	}
	glTranslated(p.X(), p.Y(), p.Z());
}

void WorkCar() {
	//���������� ���������� 
	UpdateParameters_Car();

	//���������� ������� ���������� �����
	TimeLastFrame = clock();
	
	int l = 0;
     
	//������
	glPushMatrix();
	glTranslated(Car.CarPosition.X(), Car.CarPosition.Y(), Car.CarPosition.Z());
	glRotated(180, 0, 0, 1);
	glRotated(Car.AngleZ, 0, 0, 1);

	//������
	CarTex.bindTexture();
	CarObj.DrawObj();

	//�������� ����

	//�����
	if (OpenGL::isKeyPressed('A')) {
		CarPlay1Tex.bindTexture();
	}
	else {
		CarStop2Tex.bindTexture();
	}
	CarPlayLObj.DrawObj();

	//������
	if (OpenGL::isKeyPressed('D')) {
		CarPlay1Tex.bindTexture();
	}
	else {
		CarStop2Tex.bindTexture();
	}
	CarPlayRObj.DrawObj();

	//������ ����
	if (OpenGL::isKeyPressed('S')) {
		CarStop2Tex.bindTexture();
	}
	else {
		CarStop1Tex.bindTexture();
	}
	CarStopLObj.DrawObj();
	CarStopRObj.DrawObj();

	//�����������
	if (OpenGL::isKeyPressed('A')) {
		CarPlay1Tex.bindTexture();
	}
	else {
		if (OpenGL::isKeyPressed('S')) {
			CarStop2Tex.bindTexture();
		}
		else {
			CarStop1Tex.bindTexture();
		}
	}
	CarStopLPovObj.DrawObj();

	if (OpenGL::isKeyPressed('D')) {
		CarPlay1Tex.bindTexture();
	}
	else {
		if (OpenGL::isKeyPressed('S')) {
			CarStop2Tex.bindTexture();
		}
		else {
			CarStop1Tex.bindTexture();
		}
	}
	CarStopRPovObj.DrawObj();

	glPopMatrix();


	Car.Wheel_angle += Car.KeyDuration_W * Car.Speed * 40;
	if (((long long)Car.Wheel_angle % 360 > -1 || (long long)Car.Wheel_angle % 360 < 1) && (Car.Wheel_angle > 2160 || Car.Wheel_angle < -2160))
		Car.Wheel_angle = 0;

	//������ ��� �����

	//�����
	glPushMatrix();
	PositionWheels(1);
	glRotated(180, 0, 0, 1);
	glRotated(Car.AngleWheel, 0, 0, 1);
	glRotated(Car.Wheel_angle, 0, 1, 0);
	CarWheelTex.bindTexture();
	CarWheelObj.DrawObj();
	glPopMatrix();
	
	//������
	glPushMatrix();
	PositionWheels(2);
	glRotated(360, 0, 0, 1);
	glRotated(Car.AngleWheel, 0, 0, 1);
	glRotated(Car.Wheel_angle, 0, 1, 0);
	CarWheelTex.bindTexture();
	CarWheelObj.DrawObj();
	glPopMatrix();

	//������ ��� �����

	//�����
	glPushMatrix();
	PositionWheels(3);
	glRotated(180, 0, 0, 1);
	glRotated(Car.AngleZ, 0, 0, 1);
	glRotated(Car.Wheel_angle, 0, 1, 0);
	CarWheelTex.bindTexture();
	CarWheelObj.DrawObj();
	glPopMatrix();

	//������
	glPushMatrix();
	PositionWheels(4);
	glRotated(360, 0, 0, 1);
	glRotated(Car.AngleZ, 0, 0, 1);
	glRotated(Car.Wheel_angle, 0, 1, 0);
	CarWheelTex.bindTexture();
	CarWheelObj.DrawObj();
	glPopMatrix();

}