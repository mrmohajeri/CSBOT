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

#ifndef __cplusplus
typedef unsigned char bool;
static const bool False = 0;
static const bool True = 1;
#endif

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
int is_on_color = 0;
int N_R = 0;
int N_G = 0;
int N_B = 0;
int defaultSpeed = 3;
int minimumDeposit = 2;

// Color Values

// Point Red
int PRR = 200;
int PRG = 60;
int PRB = 60;

// Point Green
int PGR = 60;
int PGG = 200;
int PGB = 60;

// Point Black
int PBR = 40;
int PBG = 40;
int PBB = 40;

// Deposit Area
int DAR = 200;
int DAG = 80;
int DAB = 41;

// Trap
int TR = 200;
int TG = 170;
int TB = 70;

//


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
	sprintf(info, "Duration=%d;SuperDuration=%d;bGameEnd=%d;CurAction=%d;CurGame=%d;SuperObj_Num=%d;SuperObj_X=%d;SuperObj_Y=%d;Teleport=%d;LoadedObjects=%d;US_Front=%d;US_Left=%d;US_Right=%d;CSLeft_R=%d;CSLeft_G=%d;CSLeft_B=%d;CSRight_R=%d;CSRight_G=%d;CSRight_B=%d;PositionX=%d;PositionY=%d;TM_State=%d;Compass=%d;Time=%d;WheelLeft=%d;WheelRight=%d;LED_1=%d;MyState=%d;", Duration, SuperDuration, bGameEnd, CurAction, CurGame, SuperObj_Num, SuperObj_X, SuperObj_Y, Teleport, LoadedObjects, US_Front, US_Left, US_Right, CSLeft_R, CSLeft_G, CSLeft_B, CSRight_R, CSRight_G, CSRight_B, PositionX, PositionY, TM_State, Compass, Time, WheelLeft, WheelRight, LED_1, MyState);

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

bool isOnGreenPoint() {
	if ((CSRight_R < PGR && CSRight_G > PGG && CSRight_B < PGB) ||
		(CSLeft_R < PGR && CSLeft_G > PGG && CSLeft_B < PGB))
	{
		return true;
	}
	else {
		return false;
	}
}

bool isOnBlackPoint() {
	if ((CSRight_R < PBR && CSRight_G < PBG && CSRight_B < PBB) ||
		(CSLeft_R < PBR && CSLeft_G < PBG && CSLeft_B < PBB))
	{
		return true;
	}
	else {
		return false;
	}
}

bool isOnRedPoint() {
	if ((CSRight_R > PRR && CSRight_G < PRG && CSRight_B < PRB) ||
		(CSLeft_R > PRR && CSLeft_G < PRG && CSLeft_B < PRB))
	{
		return true;
	}
	else {
		return false;
	}
}

bool isRightWheelOnDeposit() {
	if (CSRight_B < DAB && CSRight_G > DAG && CSRight_R > DAR) {
		if (storage >= minimumDeposit) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

bool isLeftWheelOnDeposit() {
	if (CSLeft_B < DAB && CSLeft_G > DAG && CSLeft_R > DAR) {
		if (storage >= minimumDeposit) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

bool isOnDeposit() {
	if ((CSLeft_B < DAB && CSLeft_G > DAG && CSLeft_R > DAR) &&
		(CSRight_B < DAB && CSRight_G > DAG && CSRight_R > DAR))
	{
		if (storage>=minimumDeposit) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

bool isOnTrap() {
	if ((CSLeft_R >= TR && CSLeft_G >= TG && CSLeft_B <= TB) &&
		(CSRight_R >= TR && CSRight_G >= TG && CSRight_B <= TB)) {
		return true;
	}
	else {
		return false;
	}
}

bool isRightWheelOnTrap() {
	if (CSRight_R >= TR && CSRight_G >= TG && CSRight_B <= TB) {
		return true;
	}
	else {
		return false;
	}
}

bool isLeftWheelOnTrap() {
	if (CSLeft_R >= TR && CSLeft_G >= TG && CSLeft_B <= TB) {
		return true;
	}
	else {
		return false;
	}
}

bool frontUltraSonic() {
	if (US_Front >= 0 && US_Front <= 5){
		return true;
	}
	else {
		return false;
	}
}

bool leftUltraSonic() {
	if (US_Left >= 0 && US_Left <= 10) {
		return true;
	}
	else {
		return false;
	}
}

bool rightUltraSonic() {
	if (US_Right >= 0 && US_Right <= 10) {
		return true;
	}
	else {
		return false;
	}
}

void Map1() {
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

	else if (isOnTrap()) {
		CurAction = 105;
		Duration = 0;
	}

	else if (isRightWheelOnTrap()) {
		CurAction = 106;
		Duration = 0;
	}

	else if (isLeftWheelOnTrap()) {
		CurAction = 107;
		Duration = 0;
	}

	else if (isOnDeposit()) {
		CurAction = 101;
		Duration = 50;
	}

	else if (isRightWheelOnDeposit()) {
		CurAction = 102;
		Duration = 0;
	}

	else if (isLeftWheelOnDeposit()) {
		CurAction = 103;
		Duration = 0;
	}

	else if (isOnBlackPoint() || isOnRedPoint() || isOnGreenPoint()) {
		if (storage < 6) {
			if (is_on_color == 0) {
				CurAction = 104;
				Duration = 49;
				is_on_color = 1;
				storage++;
			}
			else {
				CurAction = 99;
				Duration = 0;
				is_on_color = 0;
			}
		}
	}

	else if (frontUltraSonic()) {
		CurAction = 108;
		Duration = 0;
	}

	else if (leftUltraSonic()) {
		CurAction = 109;
		Duration = 0;
	}

	else if (rightUltraSonic()) {
		CurAction = 110;
		Duration = 0;
	}

	else if (true) {
		Duration = 0;
		CurAction = 100;
	}

	switch (CurAction) {
	case 99:
		WheelLeft = 5;
		WheelRight = 5;
		LED_1 = 0;
		MyState = 0;
		break;
	case 100:
		WheelLeft = defaultSpeed;
		WheelRight = defaultSpeed;
		LED_1 = 0;
		MyState = 0;
		break;
	case 101:
		WheelLeft = 0;
		WheelRight = 0;
		LED_1 = 2;
		MyState = 0;
		storage = 0;
		break;
	case 102:
		WheelLeft = defaultSpeed;
		WheelRight = 0;
		LED_1 = 0;
		MyState = 0;
		break;
	case 103:
		WheelLeft = 0;
		WheelRight = defaultSpeed;
		LED_1 = 0;
		MyState = 0;
		break;
	case 104:
		WheelLeft = 0;
		WheelRight = 0;
		LED_1 = 1;
		MyState = 0;
		break;
	case 105:
		WheelLeft = defaultSpeed - 4;
		WheelRight = defaultSpeed - 6;
		LED_1 = 0;
		MyState = 0;
		break;	
	case 106:
		WheelLeft = 1;
		WheelRight = defaultSpeed;
		LED_1 = 0;
		MyState = 0;
		break;
	case 107:
		WheelLeft = defaultSpeed;
		WheelRight = 1;
		LED_1 = 0;
		MyState = 0;
		break;
	case 108:
		WheelLeft = -3;
		WheelRight = -2;
		LED_1 = 0;
		MyState = 0;
		break;
	case 109:
		WheelLeft = 1;
		WheelRight = - 1;
		LED_1 = 0;
		MyState = 0;
		break;
	case 110:
		WheelLeft = -1;
		WheelRight = 1;
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
		Map1();
		break;
	default:
		break;
	}
}