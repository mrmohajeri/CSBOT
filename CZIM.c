////////////////////////////////////////
//
//	File : ai.c
//	CoSpace Robot
//	Version 1.0.0
//	Jan 1 2016
//	Copyright (C) 2016 CoSpace Robot. All Rights Reserved
//
//////////////////////////////////////
//
// ONLY C Code can be compiled.
//
/////////////////////////////////////


/*

LED States:
0: Move
1: Point
2: Deposit


*/
#define CsBot_AI_H//DO NOT delete this line
#ifndef CSBOT_REAL
#include <windows.h>
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#define DLL_EXPORT extern __declspec(dllexport)
#define false 0
#define true 1
#endif//The robot ID : It must be two char, such as '00','kl' or 'Cr'.
char AI_MyID[2] = { '0','2' };

int Duration = 0;
int SuperDuration = 0;
int bGameEnd = false;
int CurAction = -1;
int CurGame = 0;
int SuperObj_Num = 0;
int SuperObj_X = 0;
int SuperObj_Y = 0;
int Teleport = 0;
int LoadedObjects = 0;
int US_Front = 0;
int US_Left = 0;
int US_Right = 0;
int CSLeft_R = 0;
int CSLeft_G = 0;
int CSLeft_B = 0;
int CSRight_R = 0;
int CSRight_G = 0;
int CSRight_B = 0;
int PositionX = 0;
int PositionY = 0;
int TM_State = 0;
int Compass = 0;
int Time = 0;
int WheelLeft = 0;
int WheelRight = 0;
int LED_1 = 0;
int MyState = 0;
int AI_SensorNum = 13;
int storage = 0;
int dx = 0;
int dy = 0;
int fi = 0;
int myc = 0; 
int dis1 = 0;
int dis2 = 0;
int is_on_color = 0;
int X = 0;
int Y = 0;
int SX = 0;
int SY = 0;
int N_R = 0;
int N_G = 0;
int N_B = 0;
int zm = 0;
#define CsBot_AI_C//DO NOT delete this line

DLL_EXPORT void SetGameID(int GameID)
{
	CurGame = GameID;
	bGameEnd = 0;
}

DLL_EXPORT int GetGameID()
{
	return CurGame;
}

//Only Used by CsBot Dance Platform
DLL_EXPORT int IsGameEnd()
{
	return bGameEnd;
}

#ifndef CSBOT_REAL

DLL_EXPORT char* GetDebugInfo()
{
	char info[1024];
	sprintf(info, "Duration=%d;SuperDuration=%d;bGameEnd=%d;CurAction=%d;CurGame=%d;SuperObj_Num=%d;SuperObj_X=%d;SuperObj_Y=%d;Teleport=%d;LoadedObjects=%d;US_Front=%d;US_Left=%d;US_Right=%d;CSLeft_R=%d;CSLeft_G=%d;CSLeft_B=%d;CSRight_R=%d;CSRight_G=%d;CSRight_B=%d;PositionX=%d;PositionY=%d;TM_State=%d;Compass=%d;Time=%d;WheelLeft=%d;WheelRight=%d;LED_1=%d;MyState=%d;dis1=%d;dis2=%d;dx=%d;dy=%d;fi=%d;myc=%d;SX=%d;SY=%d;zm=%d;", Duration, SuperDuration, bGameEnd, CurAction, CurGame, SuperObj_Num, SuperObj_X, SuperObj_Y, Teleport, LoadedObjects, US_Front, US_Left, US_Right, CSLeft_R, CSLeft_G, CSLeft_B, CSRight_R, CSRight_G, CSRight_B, PositionX, PositionY, TM_State, Compass, Time, WheelLeft, WheelRight, LED_1, MyState, dis1, dis2, dx, dy, fi, myc, SX, SY, zm);
	return info;
}

DLL_EXPORT char* GetTeamName()
{
	return "ZiM";
}

DLL_EXPORT int GetCurAction()
{
	return CurAction;
}

//Only Used by CsBot Rescue Platform
DLL_EXPORT int GetTeleport()
{
	return Teleport;
}

//Only Used by CsBot Rescue Platform
DLL_EXPORT void SetSuperObj(int X, int Y, int num)
{
	SuperObj_X = X;
	SuperObj_Y = Y;
	SuperObj_Num = num;
}
//Only Used by CsBot Rescue Platform
DLL_EXPORT void GetSuperObj(int *X, int *Y, int *num)
{
	*X = SuperObj_X;
	*Y = SuperObj_Y;
	*num = SuperObj_Num;
}

#endif CSBOT_REAL

DLL_EXPORT void SetDataAI(volatile int* packet, volatile int *AI_IN)
{

	int sum = 0;

	US_Front = AI_IN[0]; packet[0] = US_Front; sum += US_Front;
	US_Left = AI_IN[1]; packet[1] = US_Left; sum += US_Left;
	US_Right = AI_IN[2]; packet[2] = US_Right; sum += US_Right;
	CSLeft_R = AI_IN[3]; packet[3] = CSLeft_R; sum += CSLeft_R;
	CSLeft_G = AI_IN[4]; packet[4] = CSLeft_G; sum += CSLeft_G;
	CSLeft_B = AI_IN[5]; packet[5] = CSLeft_B; sum += CSLeft_B;
	CSRight_R = AI_IN[6]; packet[6] = CSRight_R; sum += CSRight_R;
	CSRight_G = AI_IN[7]; packet[7] = CSRight_G; sum += CSRight_G;
	CSRight_B = AI_IN[8]; packet[8] = CSRight_B; sum += CSRight_B;
	PositionX = AI_IN[9]; packet[9] = PositionX; sum += PositionX;
	PositionY = AI_IN[10]; packet[10] = PositionY; sum += PositionY;
	TM_State = AI_IN[11]; packet[11] = TM_State; sum += TM_State;
	Compass = AI_IN[12]; packet[12] = Compass; sum += Compass;
	Time = AI_IN[13]; packet[13] = Time; sum += Time;
	packet[14] = sum;

}
DLL_EXPORT void GetCommand(int *AI_OUT)
{
	AI_OUT[0] = WheelLeft;
	AI_OUT[1] = WheelRight;
	AI_OUT[2] = LED_1;
	AI_OUT[3] = MyState;
}
void Game0() {
	if (Time == 180)
	{
		Teleport = 1;
	}
	if (SuperDuration>0)
	{
		SuperDuration--;
	}
	else if (Duration>0)
	{
		Duration--;
	}
	//trap
	else if (CSLeft_R >= 200 && CSLeft_R <= 255 && CSLeft_G >= 170 && CSLeft_G <= 255 && CSLeft_B >= 0 && CSLeft_B <= 70 && CSRight_R >= 200 && CSRight_R <= 255 && CSRight_G >= 170 && CSRight_G <= 255 && CSRight_B >= 0 && CSRight_B <= 70)
	{
		Duration = 0;
		CurAction = 801;
	}
	//left border
	else if (CSLeft_R >= 200 && CSLeft_R <= 255 &&
		CSLeft_G >= 170 && CSLeft_G <= 255 &&
		CSLeft_B >= 0 && CSLeft_B <= 80)
	{
		CurAction = 802;
		Duration = 0;
	}
	//right border
	else if (CSRight_R >= 200 && CSRight_R <= 255 &&
		CSRight_G >= 170 && CSRight_G <= 255 &&
		CSRight_B >= 0 && CSRight_B <= 80)
	{
		CurAction = 803;
		Duration = 0;
	}
	//left
	else if (US_Right >= 0 && US_Right <= 10)
	{
		Duration = 0;
		CurAction = 805;
	}
	//right
	else if (US_Left >= 0 && US_Left <= 10)
	{
		Duration = 0;
		CurAction = 806;
	}
	//front
	else if (US_Front >= 0 && US_Front <= 5)
	{
		Duration = 0;
		CurAction = 807;
	}
	else if (CSRight_B < 41 && CSRight_G > 80 &&
		CSRight_R > 200 && CSLeft_B < 41 &&
		CSLeft_G > 80 && CSLeft_R > 200 && storage > 0)
	{
		// Deposit
		CurAction = 106;
		Duration = 49;
		storage = 0;

	}
	else if (CSRight_B < 41 && CSRight_G > 80 && CSRight_R > 200 && storage > 0)
	{
		// Go to Deposit From Left
		CurAction = 107;
		Duration = 0;
	}
	else if (CSLeft_B < 41 && CSLeft_G > 80 && CSLeft_R > 200 && storage > 0)
	{
		// Go to Deposit From Right
		CurAction = 108;
		Duration = 0;

	}
	else if (CSRight_R < 60 && CSRight_G > 200 && CSRight_B < 60) {
		// Green Point From Right
		if (storage < 6) {

			if (is_on_color == 0) {
				CurAction = 109;
				Duration = 49;
				is_on_color = 1;
				storage++;
			}
			else {
				CurAction = 1000;
				Duration = 0;
				is_on_color = 0;
			}
		}

	}
	else if (CSLeft_R < 60 && CSLeft_G > 200 && CSLeft_B < 60) {
		// Green Point From Left
		if (storage < 6) {
			if (is_on_color == 0) {
				CurAction = 109;
				Duration = 49;
				is_on_color = 1;
				storage++;
			}
			else {
				CurAction = 1000;
				Duration = 0;
				is_on_color = 0;
			}
		}

	}
	else if (CSRight_R < 40 && CSRight_G < 40 && CSRight_B < 40) {
		// Black Point From Right
		if (storage < 6) {

			if (is_on_color == 0) {
				CurAction = 109;
				Duration = 49;
				is_on_color = 1;
				storage++;
			}
			else {
				CurAction = 1000;
				Duration = 0;
				is_on_color = 0;
			}
		}

	}
	else if (CSLeft_R < 40 && CSLeft_G < 40 && CSLeft_B < 40) {
		// Black Point From Left
		if (storage < 6) {

			if (is_on_color == 0) {
				CurAction = 109;
				Duration = 49;
				is_on_color = 1;
				storage++;
			}
			else {
				CurAction = 1000;
				Duration = 0;
				is_on_color = 0;
			}
		}

	}
	else if (CSRight_R > 200 && CSRight_G < 60 && CSRight_B < 60) {
		// Red Point From Right
		if (storage < 6) {

			if (is_on_color == 0) {
				CurAction = 109;
				Duration = 49;
				is_on_color = 1;
				storage++;
			}
			else {
				CurAction = 1000;
				Duration = 0;
				is_on_color = 0;
			}
		}

	}
	else if (CSLeft_R > 200 && CSLeft_G < 60 && CSLeft_B < 60) {
		// Red Point From Left
		if (storage < 6) {

			if (is_on_color == 0) {
				CurAction = 109;
				Duration = 49;
				is_on_color = 1;
				storage++;
			}
			else {
				CurAction = 1000;
				Duration = 0;
				is_on_color = 0;
			}
		}

	}
	else if (true)
	{
		Duration = 0;
		CurAction = 808;
	}
	switch (CurAction)
	{
	case 1000:
		// Move
		WheelLeft = 2;
		WheelRight = 2;
		LED_1 = 0;
		MyState = 0;
		break;
	case 100:
		WheelLeft = 2;
		WheelRight = 1;
		LED_1 = 0;
		MyState = 0;
		break;
	case 101:
		WheelLeft = -2;
		WheelRight = 3;
		LED_1 = 0;
		MyState = 0;
		break;
	case 106:
		WheelLeft = 0;
		WheelRight = 0;
		LED_1 = 2;
		MyState = 0;
		break;
	case 107:
		WheelLeft = 3;
		WheelRight = 0;
		LED_1 = 0;
		MyState = 0;
		break;
	case 108:
		WheelLeft = 0;
		WheelRight = 3;
		LED_1 = 0;
		MyState = 0;
		break;
	case 109:
		WheelLeft = 0;
		WheelRight = 0;
		LED_1 = 1;
		MyState = 0;
		break;
	case 170:
		WheelLeft = 4;
		WheelRight = 2;
		LED_1 = 0;
		MyState = 0;
		break;
	case 180:
		WheelLeft = 2;
		WheelRight = 4;
		LED_1 = 0;
		MyState = 0;
		break;
	case 801:
		WheelLeft = -1;
		WheelRight = -3;
		LED_1 = 0;
		MyState = 0;
		break;
	case 802:
		WheelLeft = 2;
		WheelRight = 1;
		LED_1 = 0;
		MyState = 0;
		break;
	case 803:
		WheelLeft = 1;
		WheelRight = 2;
		LED_1 = 0;
		MyState = 0;
		break;
	case 805:
		WheelLeft = -1;
		WheelRight = 1;
		LED_1 = 0;
		MyState = 0;
		break;

	case 806:
		WheelLeft = 1;
		WheelRight = -1;
		LED_1 = 0;
		MyState = 0;
		break;
	case 807:
		WheelLeft = -3;
		WheelRight = -2;
		LED_1 = 0;
		MyState = 0;
		break;
	case 808:
		WheelLeft = 2;
		WheelRight = 2;
		LED_1 = 0;
		MyState = 0;
		break;
	default:
		break;
	}
}
void Game1()
{		
	if (SuperObj_X != 0 || SuperObj_Y != 0)  {
		SX = SuperObj_X;
		SY = SuperObj_Y;
	}
	if (PositionX != 0)
	{
		X = PositionX;
	}
	if (PositionY != 0)
	{
		Y = PositionY;
	}
	if (SuperDuration > 0)
	{
		SuperDuration--;
	}
	else if (Duration > 0)
	{
		Duration--;
	}	//khakestari bala
	else if ((sqrt(pow((X - 80), 2) + pow((Y - 200), 2)) < 28) || (sqrt(pow((X - 275), 2) + pow((Y - 130), 2)) < 30) || (sqrt(pow((X - 80), 2) + pow((Y - 130), 2)) < 30))	
	{
		Duration = 0;
		CurAction = 800;
	}

	//map
	else if (X<5 || 345<X || Y<5 || 260<Y)
	{
		Duration = 0;
		CurAction = 801;
	}
	//left
	else if (US_Right >= 0 && US_Right <= 10)
	{
		Duration = 0;
		CurAction = 805;
	}
	//right
	else if (US_Left >= 0 && US_Left <= 10)
	{
		Duration = 0;
		CurAction = 806;
	}
	//front
	else if (US_Front >= 0 && US_Front <= 5)
	{
		Duration = 0;
		CurAction = 807;
	}
	else if (CSRight_B < 41 && CSRight_G > 80 &&
		CSRight_R > 200 && CSLeft_B < 41 &&
		CSLeft_G > 80 && CSLeft_R > 200 && storage > 0)
	{
		// Deposit
		CurAction = 106;
		Duration = 51;
		storage = 0;
		N_R = 0;
		N_B = 0;
		N_G = 0;
	}
	else if (CSRight_B < 41 && CSRight_G > 80 && CSRight_R > 200 && storage > 0)
	{
		// Go to Deposit From Left
		CurAction = 107;
		Duration = 0;
	}
	else if (CSLeft_B < 41 && CSLeft_G > 80 && CSLeft_R > 200 && storage > 0)
	{
		// Go to Deposit From Right
		CurAction = 108;
		Duration = 0;

	}
	else if( (CSLeft_R > 190 && CSLeft_G <60 && CSLeft_B > 200)
		||
		(CSRight_R > 190 &&  CSRight_G <60 && CSRight_B > 200)){
		// Super Object
		CurAction = 109;
		Duration = 49;
		SX = 0;
		SY = 0;
	}
	else if (CSRight_R < 60 && CSRight_G > 200 && CSRight_B < 60 && N_G<2) {
		// Green Point From Right
		if (storage < 6) {

			if (is_on_color == 0) {
				CurAction = 109;
				Duration = 49;
				is_on_color = 1;
				storage++;
				N_G++;
			}
			else {
				CurAction = 1000;
				Duration = 0;
				is_on_color = 0;
			}
		}

	}
	else if (CSLeft_R < 60 && CSLeft_G > 200 && CSLeft_B < 60 && N_G<2) {
		// Green Point From Left
		if (storage < 6) {
			if (is_on_color == 0) {
				CurAction = 109;
				Duration = 49;
				is_on_color = 1;
				storage++;
				N_G++;

			}
			else {
				CurAction = 1000;
				Duration = 0;
				is_on_color = 0;
			}
		}

	}
	else if (CSRight_R < 40 && CSRight_G < 40 && CSRight_B < 40 && N_B<2) {
		// Black Point From Right
		if (storage < 6) {

			if (is_on_color == 0) {
				CurAction = 109;
				Duration = 49;
				is_on_color = 1;
				storage++;
				N_B++;
			}
			else {
				CurAction = 1000;
				Duration = 0;
				is_on_color = 0;
			}
		}

	}
	else if (CSLeft_R < 40 && CSLeft_G < 40 && CSLeft_B < 40 && N_B<2) {
		// Black Point From Left
		if (storage < 6) {

			if (is_on_color == 0) {
				CurAction = 109;
				Duration = 49;
				is_on_color = 1;
				storage++;
				N_B++;

			}
			else {
				CurAction = 1000;
				Duration = 0;
				is_on_color = 0;
			}
		}

	}
	else if (CSRight_R > 200 && CSRight_G < 60 && CSRight_B < 60 && N_R<2) {
		// Red Point From Right
		if (storage < 6) {

			if (is_on_color == 0) {
				CurAction = 109;
				Duration = 49;
				is_on_color = 1;
				storage++;
				N_R++;

			}
			else {
				CurAction = 1000;
				Duration = 0;
				is_on_color = 0;
			}
		}

	}
	else if (CSLeft_R > 200 && CSLeft_G < 60 && CSLeft_B < 60 && N_R<2) {
		// Red Point From Left
		if (storage < 6) {

			if (is_on_color == 0) {
				CurAction = 109;
				Duration = 49;
				is_on_color = 1;
				storage++;
				N_R++;

			}
			else {
				CurAction = 1000;
				Duration = 0;
				is_on_color = 0;
			}
		}

	}
	else if ((CSLeft_R >= 130 && CSLeft_R < 215 && CSLeft_G >= 130 && CSLeft_G < 215 && CSLeft_B >= 130 && CSLeft_B < 215) || (CSRight_R >= 130 && CSRight_R < 215 && CSRight_G >= 130 && CSRight_G < 215 && CSRight_B >= 130 && CSRight_B < 215)) {
		Duration = 0;
		CurAction = 1000;
	}
	else if (SX != 0 || SY != 0) {
		fi = atan((Y - SY  )/ ((X - SX))+1) *(180 / M_PI);
		if (SY> Y && SX > X) {
			myc = fi + 270;
			if (Compass>(myc))
			{
				Duration = 0;
				CurAction = 170;
			}
			if (Compass<(myc))
			{
				Duration = 0;
				CurAction = 180;
			}
		}
		if (SY< Y && SX < X) {
			myc = fi + 90;
			if (Compass>(myc))
			{
				Duration = 0;
				CurAction = 170;
			}
			if (Compass<(myc))
			{
				Duration = 0;
				CurAction = 180;
			}
		}
		if (SY> Y && SX < X) {
			myc = fi + 0;
			if (Compass>(myc))
			{
				Duration = 0;
				CurAction = 170;
			}
			if (Compass<(myc))
			{
				Duration = 0;
				CurAction = 180;
			}
		}
		if (SY< Y && SX > X) {
			myc = fi + 180;
			if (Compass>(myc))
			{
				Duration = 0;
				CurAction = 170;
			}
			if (Compass<(myc))
			{
				Duration = 0;
				CurAction = 180;
			}
		}


	}
	else if (storage >= 3) {
		if (sqrt((X - 355) ^ 2 + (Y - 260) ^ 2)>(sqrt(X ^ 2 + Y ^ 2)))
		{
			fi = atan(Y / ((X)+1))*(180 / M_PI);
			myc = fi + 90;

			if (Compass>(myc)) 
			{
				Duration = 0;
				CurAction = 1700;
			}
			if (Compass<(myc))
			{
				Duration = 0;
				CurAction = 1800;
			}
		}
		if (sqrt((X - 355) ^ 2 + (Y - 260) ^ 2)<(sqrt(X ^ 2 + Y ^ 2)))
		{
			
			fi = atan((260 - Y) / (355 - X))*(180 / M_PI);
			myc = fi + 270;

			if (Compass>(myc))
			{
				Duration = 0;
				CurAction = 1700;
			}
			if (Compass<(myc))
			{
				Duration = 0;
				CurAction = 1800;
			}
		}

	}
	else if (true)
	{
		// Move
		Duration = 0;
		CurAction = 1000;
	}
	switch (CurAction)
	{
	case 800:

		WheelLeft = -1;
		WheelRight = -3;
		LED_1 = 0;
		MyState = 0;
		break;
	case 1000:
		WheelLeft = 2;
		WheelRight = 2;
		if ((CSLeft_R >= 130 && CSLeft_R <215 && CSLeft_G >= 130 && CSLeft_G < 215 && CSLeft_B >= 130 && CSLeft_B < 215) || (CSRight_R >= 130 && CSRight_R < 215 && CSRight_G >= 130 && CSRight_G < 215 && CSRight_B >= 130 && CSRight_B < 215) ) {
			WheelLeft = 5;
			WheelRight = 5;
		}
		LED_1 = 0;
		MyState = 0;	
		break;
	case 100:
		WheelLeft = 2;
		WheelRight = 1;
		LED_1 = 0;
		MyState = 0;
		break;
	case 101:
		WheelLeft = -2;
		WheelRight = 3;
		LED_1 = 0;
		MyState = 0;
		break;
	case 106:
		WheelLeft = 0;
		WheelRight = 0;
		LED_1 = 2;
		MyState = 0;
		break;
	case 107:
		WheelLeft = 3;
		WheelRight = 0;
		LED_1 = 0;
		MyState = 0;
		break;
	case 108:
		WheelLeft = 0;
		WheelRight = 3;
		LED_1 = 0;
		MyState = 0;
		break;
	case 109:
		WheelLeft = 0;
		WheelRight = 0;
		LED_1 = 1;
		MyState = 0;
		break;
	case 170:
		WheelLeft = 4;
		WheelRight = 2;
		zm = sqrt(((X - SX) ^ 2) + ((Y - SY) ^ 2));
		if (sqrt(((X - SX) ^ 2) + ((Y - SY) ^ 2)) < 100) {
			WheelLeft = 2;
			WheelRight = 1;
		}
		LED_1 = 0;
		MyState = 0;
		break;
	case 180:
		WheelLeft = 2;
		WheelRight = 4;
		zm = sqrt(((X - SX) ^ 2) + ((Y - SY) ^ 2));
		if (sqrt(((X - SX) ^ 2) + ((Y - SY) ^ 2)) < 100) {
			WheelLeft = 1;
			WheelRight = 2;
		}
		LED_1 = 0;
		MyState = 0;
		break;
	case 1700:
		WheelLeft = 4;
		WheelRight = 2;
		LED_1 = 0;
		MyState = 0;
		break;
	case 1800:
		WheelLeft = 2;
		WheelRight = 4;
		LED_1 = 0;
		MyState = 0;
		break;
	case 171:
		WheelLeft = 2;
		WheelRight = 4;
		LED_1 = 0;
		MyState = 0;
		break;
	case 172:
		WheelLeft = 2;
		WheelRight = 4;
		LED_1 = 0;
		MyState = 0;
		break;


		// -------------------- 
	case 801:
		LED_1 = 0;
		MyState = 0;

		if (X<5) {
			if (Compass<90) {
				WheelLeft = 2;
				WheelRight = -1;
			}
			if (Compass<=180 && Compass>=90) {
				WheelLeft = -1;
				WheelRight = 2;

			}
			if (Compass>180) {
				WheelLeft = 2;
				WheelRight = 2;
			}
		}

		if (345<X) {
			if (Compass>=180 && Compass<270) {
				WheelLeft = 2;
				WheelRight = -1;
			}
			if (Compass>=270) {
				WheelLeft = -1;
				WheelRight = 2;

			}
			if (Compass<=180) {
				WheelLeft = 2;
				WheelRight = 2;
			}
		}

		if (Y<5) {
			if (Compass >= 180 && Compass<=270) {
				WheelLeft = -1;
				WheelRight = 2;
				if ((CSLeft_R >= 130 && CSLeft_R <215 && CSLeft_G >= 130 && CSLeft_G < 215 && CSLeft_B >= 130 && CSLeft_B < 215) || (CSRight_R >= 130 && CSRight_R < 215 && CSRight_G >= 130 && CSRight_G < 215 && CSRight_B >= 130 && CSRight_B < 215)) {
					Duration = 12;
					WheelLeft = -3;
					WheelRight = 5;
				}
			}
			if (Compass <= 180 && Compass>=90) {
				WheelLeft = 2;
				WheelRight = -1;
				if ((CSLeft_R >= 130 && CSLeft_R <215 && CSLeft_G >= 130 && CSLeft_G < 215 && CSLeft_B >= 130 && CSLeft_B < 215) || (CSRight_R >= 130 && CSRight_R < 215 && CSRight_G >= 130 && CSRight_G < 215 && CSRight_B >= 130 && CSRight_B < 215)) {
					Duration = 12;
					WheelLeft = 5;
					WheelRight = -3;
				}

			}
			if (Compass <= 90 || Compass >=270) {
				WheelLeft = 2;
				WheelRight = 2;
				if ((CSLeft_R >= 130 && CSLeft_R <215 && CSLeft_G >= 130 && CSLeft_G < 215 && CSLeft_B >= 130 && CSLeft_B < 215) || (CSRight_R >= 130 && CSRight_R < 215 && CSRight_G >= 130 && CSRight_G < 215 && CSRight_B >= 130 && CSRight_B < 215)) {
					Duration = 12;
					WheelLeft = 5;
					WheelRight = 5;
				}
			}
		}

		if (260<Y) {
			if (Compass >= 0 && Compass <= 90) {
				WheelLeft = -1;
				WheelRight = 2;
			}
			if (Compass <= 359 && Compass >= 270) {
				WheelLeft = 2;
				WheelRight = -1;

			}
			if ((Compass <= 270 && Compass>180) || (Compass >= 90 && Compass<=180)) {
				WheelLeft = 2;
				WheelRight = 2;
			}
		}







		break;
	case 805:
		WheelLeft = -1;
		WheelRight = 1;
		if ((CSLeft_R >= 130 && CSLeft_R < 215 && CSLeft_G >= 130 && CSLeft_G < 215 && CSLeft_B >= 130 && CSLeft_B < 215) || (CSRight_R >= 130 && CSRight_R < 215 && CSRight_G >= 130 && CSRight_G < 215 && CSRight_B >= 130 && CSRight_B < 215)) {
			WheelLeft = -5;
			WheelRight = 5;
			Duration = 2;
		}
		LED_1 = 0;
		MyState = 0;
		break;
	case 806:
		WheelLeft = 1;
		WheelRight = -1;
		if ((CSLeft_R >= 130 && CSLeft_R < 215 && CSLeft_G >= 130 && CSLeft_G < 215 && CSLeft_B >= 130 && CSLeft_B < 215) || (CSRight_R >= 130 && CSRight_R < 215 && CSRight_G >= 130 && CSRight_G < 215 && CSRight_B >= 130 && CSRight_B < 215)) {
			WheelLeft = 5;
			WheelRight = -5;
			Duration = 2;
		}
		LED_1 = 0;
		MyState = 0;
		break;
	case 807:
		WheelLeft = -1;
		WheelRight = -3;
		if ((CSLeft_R >= 130 && CSLeft_R < 215 && CSLeft_G >= 130 && CSLeft_G < 215 && CSLeft_B >= 130 && CSLeft_B < 215) || (CSRight_R >= 130 && CSRight_R < 215 && CSRight_G >= 130 && CSRight_G < 215 && CSRight_B >= 130 && CSRight_B < 215)) {
			WheelLeft = -5;
			WheelRight = -3;
			Duration = 2;
		}
		LED_1 = 0;
		MyState = 0;
		break;
	case 808:
		WheelLeft = 3;
		WheelRight = 3;
		LED_1 = 0;
		MyState = 0;
		break;
	default:
		break;
		
	}
}


DLL_EXPORT void OnTimer()
{
	switch (CurGame)
	{
	case 0:
		Game0();
		break;
	case 1:
		Game1();
		break;
	default:
		break;
	}
}

