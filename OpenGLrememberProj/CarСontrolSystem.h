#pragma once
#pragma once
#include "MyVector3d.h"
class Car�ontrolSystem {
public:
	//������������ ���� �������� 
	double MaxAngleWheel = 27;

	//���� �������� ������� ������������ ��� Z
	double AngleZ = 0;

	//���� �������� 
	double AngleWheel = 0;

	//���� �������� ������������ ������ ���
	double Wheel_angle = 0;

	//�������� 
	double Speed = 0.1;

	//�������� �������� 
	double SpeedWheel = 4;

	//�������� ����������� ��������� � ������ ���������
	double SpeedWheelReverse = 0.5;

	//������������ ������ �� �������vm
	double Distance = 10;

	//������ ������ ��� ��������
	double Height = 5;

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
	
	//���������� ����� ��� ��������� ������� ������
	double Car_x_maxNow = 0.7;
	double Car_x_minNow = -1.7;
	double Car_y_maxNow = 0.74;
	double Car_y_minNow = -0.74;

	double R = 1.75;
	//������� �������
	Vector3 CarPosition;
	Vector3 CarPosition_back;

	bool Stop = false;

	Car�ontrolSystem() {
		CarPosition = Vector3(0, 0, 0);
		CarPosition_back = Vector3(0, 0, 0);
	}
};