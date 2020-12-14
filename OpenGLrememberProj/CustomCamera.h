#pragma once
#include "Camera.h"
#include "Light.h"
#include "Plane�ontrolSystem.h"
#include "Car�ontrolSystem.h"

extern Plane�ontrolSystem Plane;
extern Car�ontrolSystem Car;

//����� ��� ��������� ������
class CustomCamera : public Camera
{
public:
	//��������� ������
	double camDist;
	//���� �������� ������
	double fi1, fi2;


	//������� ������ �� ���������
	CustomCamera()
	{
		camDist = 15;
		fi1 = 1;
		fi2 = 1;
	}


	//������� ������� ������, ������ �� ����� ��������, ���������� �������
	virtual void SetUpCamera()
	{

		//lookPoint.setCoords(0, 0, 0);
		//
		//pos.setCoords(camDist * cos(fi2) * cos(fi1),
		//	camDist * cos(fi2) * sin(fi1),
		//	camDist * sin(fi2));
		//
		//if (cos(fi2) <= 0)
		//	normal.setCoords(0, 0, -1);
		//else
		//	normal.setCoords(0, 0, 1);
		//
		//LookAt();

		//�������� �� ������� ������ ������
		lookPoint.setCoords(Car.CarPosition.X(), Car.CarPosition.Y(), Car.CarPosition.Z());

		if (cos(fi2) <= 0)
			normal.setCoords(0, 0, -1);
		else
			normal.setCoords(0, 0, 1);

		LookAt();
	}

	void CustomCamera::LookAt()
	{
		gluLookAt(pos.X(), pos.Y(), pos.Z(), lookPoint.X(), lookPoint.Y(), lookPoint.Z(), normal.X(), normal.Y(), normal.Z());
	}

	void SetLookPoint(double x, double y, double z)
	{
		lookPoint.setCoords(x, y, z);
	}

	void SetLookPoint(Vector3 vec)
	{
		lookPoint = vec;
	}

};