#pragma once
#include "MyVector3d.h"
class Plane�ontrolSystem {
public:
	//������������ ���� �������� ���������
	double MaxAngleFlaps = 75;

	//������������ ���� �������� ������� ��������
	double MaxAnglRearFlap = 75;
	
	//���� �������� ������� ������������ ��� Z
	double AngleZ = 0;

	//���� �������� ������� ������������ ��� Y
	double AngleY = 0;

	//���� �������� ���������
	double AngleFlaps = 0;

	//���� �������� ������� ��������
	double AngleRearFlap = 0;

	//�������� 
	double SpeedPlane = 0.1;

	//�������� �������� ���������
	double SpeedRearFlap = 4;
	
	//�������� �������� ���������
	double SpeedFlaps = 4;

	//������� ������ ������������ ����� ���
	double AngleWheel = 0;

	//�������� ����������� ��������� � ������ ���������
	double SpeedFlapsReverse = 0.5;

	//�������� ����������� ������� �������� � ������ ���������
	double SpeedRearFlapReverse = 0.5;

	//������������ ������ �� �������vm
	double DistanceFromPlane = 10;

	//������ ������ ��� ��������
	double HeightFromPlane = 10;

	//�������� ����������w
	double SpeedSlow = 0.1;

	//����� ������ ������� W
	double KeyTimeDown_W = 0;

	//������ ������� W
	double KeyDuration_W = 0;

	//���������� �� ������ ����������
	bool FlagDeceleration = false;

	//���������� �� ������ ������
	bool FlagAcceleration = false;

	//������ ����� ����������
	bool FlagAccAfterDec = false;

	//������� �������
	Vector3 PlanePosition;

	Vector3 FlapsPosition;

	Vector3 RearFlapPosition;

	Vector3 WheelsPosition;

	Vector3 HelicePosition;

	Plane�ontrolSystem() {
		PlanePosition = Vector3(0, 0, 0);
		FlapsPosition = Vector3(0, 0, 0);
		RearFlapPosition = Vector3(0, 0, 0);
		WheelsPosition = Vector3(0, 0, 0);
		HelicePosition = Vector3(0, 0, 0);
	}
};