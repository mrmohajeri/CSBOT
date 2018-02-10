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
#define NELEMS(x)  (sizeof(x) / sizeof((x)[0]))
#define mapX 360
#define mapY 270
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

int MS = 0;
int MN = 0;
int o = 0;
int t;
int targetX;
int targetY;
int aX;
int aY;
int fi;
int shouldDepositValue = 5;
int SOX = 0;
int SOY = 0;
int timer;
bool circularTrap = false;
bool followingDeposit = false;
bool followingSuperObject = false;
int X = 1;
int Y = 1;
int storage = 0;
int is_on_color = 0;
int NR = 0;
int NG = 0;
int NB = 0;
int defaultSpeed = 3;
int minimumDeposit = 5;
bool isOnMap2 = false;
int counter = 0;
int Matris[2][30] = { 0 };
void setMatris();
// Cordinates

// Trap
int trapX[] = { 80,275,80 };
int trapY[] = { 200,130,130 };
int trapR[] = { 25,30,30 };

// Deposit Area
int depositX[] = { 240 };
int depositY[] = { 255 };

// Middle Map
int mmX = mapX / 2;
int mmY = mapY / 2;

// Borders
int xL = 10;
int xR = 350;
int yU = 260;
int yD = 10;

// Color Values

// Point Red
int PRR = 200;
int PRG = 60;
int PRB = 60;

// Point Green
/*int PGR = 60;
int PGG = 200;
int PGB = 60;*/
int PGR = 50;
int PGG = 200;
int PGB = 200;

// Point Black
int PBR = 40;
int PBG = 40;
int PBB = 40;

// Deposit Area
int DAR = 180;
int DAG = 130;
int DAB = 60;

// SuperObject
int SOR = 190;
int SOG = 60;
int SOB = 200;

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
	sprintf(info, "Duration=%d;SuperDuration=%d;bGameEnd=%d;CurAction=%d;CurGame=%d;SuperObj_Num=%d;SuperObj_X=%d;SuperObj_Y=%d;Teleport=%d;LoadedObjects=%d;US_Front=%d;US_Left=%d;US_Right=%d;CSLeft_R=%d;CSLeft_G=%d;CSLeft_B=%d;CSRight_R=%d;CSRight_G=%d;CSRight_B=%d;PositionX=%d;PositionY=%d;TM_State=%d;Compass=%d;Time=%d;WheelLeft=%d;WheelRight=%d;LED_1=%d;MyState=%d;counter=%d;counterX=%d;counterY=%d;storage=%d;", Duration, SuperDuration, bGameEnd, CurAction, CurGame, SuperObj_Num, SuperObj_X, SuperObj_Y, Teleport, LoadedObjects, US_Front, US_Left, US_Right, CSLeft_R, CSLeft_G, CSLeft_B, CSRight_R, CSRight_G, CSRight_B, PositionX, PositionY, TM_State, Compass, Time, WheelLeft, WheelRight, LED_1, MyState, counter, Matris[0][counter], Matris[1][counter],storage);
	return info;
}

DLL_EXPORT char* GetTeamName()
{
	return "Helii programer2";
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
	if ((CSRight_R < PGR && CSRight_G > PGG && CSRight_B > PGB) ||
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
	/*if ((CSRight_R > PRR && CSRight_G < PRG && CSRight_B < PRB) ||
		(CSLeft_R > PRR && CSLeft_G < PRG && CSLeft_B < PRB))*/
	if (( (CSRight_R>225 && CSRight_R <= 255 && CSRight_G>0 && CSRight_G <= 60 && CSRight_B>0 && CSRight_B <= 60) || (CSLeft_R>225 && CSLeft_R <= 255 && CSLeft_G>0 && CSLeft_G <= 60 && CSLeft_B>0 && CSLeft_B <= 60) ))
	{
		return true;
	}
	else {
		return false;
	}
}

bool isRightWheelOnDepositMap1() {
	if (CSRight_R>190 && CSRight_R <= 245 && CSRight_G>20 && CSRight_G <= 55 && CSRight_B>=0 && CSRight_B <= 15) {
		if (storage > 0) {
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

bool isLeftWheelOnDepositMap1() {
	if (CSLeft_R>190 && CSLeft_R <= 245 && CSLeft_G>20 && CSLeft_G <= 55 && CSLeft_B>=0 && CSLeft_B <= 15) {
		if (storage > 0) {
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

bool isOnDepositMap1() {
	if (CSRight_R>190 && CSRight_R <= 245 && CSRight_G>20 && CSRight_G <= 55 && CSRight_B>=0 && CSRight_B <= 15 && CSLeft_R>190 && CSLeft_R <= 245 && CSLeft_G>20 && CSLeft_G <= 55 && CSLeft_B>=0 && CSLeft_B <= 15)
	{
		if (storage>0) {
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


bool checkUltrasonic() {
	if (US_Front >= 0 && US_Front <= 10 && !(US_Right >= 0 && US_Right<10 && US_Left >= 0 && US_Left<10))
	{
		Duration = 0;
		CurAction = 600;
		return true;
	}
	else if (US_Right >= 0 && US_Right<10 && !(US_Left >= 0 && US_Left<10 && US_Front >= 0 && US_Front<10))
	{
		Duration = 0;
		CurAction = 601;
		return true;
	}
	else if (US_Left >= 0 && US_Left <= 10 && !(US_Right >= 0 && US_Right<10 && US_Front >= 0 && US_Front<10))
	{
		Duration = 0;
		CurAction = 602;
		return true;
	}
	else if (US_Right >= 0 && US_Right<10 && US_Left >= 0 && US_Left<10)
	{
		Duration = 0;
		CurAction = 603;
		return true;
	}
	else if (US_Left >= 0 && US_Left<10 && US_Front >= 0 && US_Front<10)
	{
		Duration = 0;
		CurAction = 604;
		return true;
	}
	else if (US_Right >= 0 && US_Right<10 && US_Front >= 0 && US_Front<10)
	{
		Duration = 0;
		CurAction = 605;
		return true;
	}
	return false;
}

bool isOnSuperObject() {		
	if ((CSLeft_R > 190 && CSLeft_G <60 && CSLeft_B > 200)||
		(CSRight_R > 190 && CSRight_G <60 && CSRight_B > 200)) {
			SOX = 0;
			SOY = 0;
			return true;
	}
	else {
		return false;
	}
}

bool isOnBorder() {
	if (X < xL || xR < X || Y < yD || yU < Y) {
		return true;
	}
	else {
		return false;
	}
}

bool shouldDeposit(){
	if (( storage>=shouldDepositValue) || (storage>0 && timer<30) ) {
		return true;
	}
	else {
		return false;
	}
}

bool isSuperObjectAvailable() {
	if (SOX != 0 || SOY !=0) {
		return true;
	}
	else {
		return false;
	}
}

int subregion() {
	if (X < xL) {
		return 2;
	}
	else if (xR < X) {
		return 4;
	}
	else if (yU < Y) {
		return 1;
	}
	else if (Y < yD) {
		return 3;
	}
}

void onBorder() {
	switch (subregion()) {
	case 1:
		if (Compass >= 0 && Compass <= 90) {
			CurAction = 107;
			Duration = 0;
		}
		if (Compass <= 359 && Compass >= 270) {
			CurAction = 106;
			Duration = 0;

		}
		if ((Compass <= 270 && Compass>180) || (Compass >= 90 && Compass <= 180)) {
			CurAction = 100;
			Duration = 0;
		}
		break;
	case 2:
		if (Compass<90) {
			CurAction = 106;
			Duration = 0;
		}
		if (Compass <= 180 && Compass >= 90) {
			CurAction = 107;
			Duration = 0;

		}
		if (Compass>180) {
			CurAction = 100;
			Duration = 0;
		}
		break;
	case 3:
		if (Compass >= 180 && Compass <= 270) {
			CurAction = 107;
			Duration = 0;
		}
		if (Compass < 180 && Compass >= 90) {
			CurAction = 106;
			Duration = 0;
		}
		if (Compass < 90 || Compass > 270) {
			CurAction = 100;
			Duration = 0;
		}
		break;
	case 4:
		if (Compass >= 180 && Compass<270) {
			CurAction = 106;
			Duration = 0;
		}
		if (Compass >= 270) {
			CurAction = 107;
			Duration = 0;

		}
		if (Compass <= 180) {
			CurAction = 100;
			Duration = 0;
		}
		break;
	default:
		CurAction = 100;
		Duration = 0;
		break;
	}
}

void checkTrapCordinates() {
	if (circularTrap == true) {
		for (int i = 0; i < NELEMS(trapX); i++) {
			if (distance(trapX[i], trapY[i]) < trapR[i]) {
				Duration = 0;
				CurAction = 101;
			}
		}
	}

}

int distance(int toX, int toY) {
	return sqrt(pow((X - toX), 2) + pow((Y - toY), 2));
}

int whichDepositX() {
	int hold;
	int a[NELEMS(depositX)];
	for (int i = 0; i < NELEMS(depositX); i++) {
		a[i] = distance(depositX[i], depositY[i]);
	}
	for (int i = 0; i < NELEMS(depositX); i++) {
		for (int j = 0; j < NELEMS(depositX); j++) {
			if (a[j] > a[j + 1]) {
				hold = a[j];
				a[j] = a[j + 1];
				a[j + 1] = hold;
			}
		}
	}
	for (int i = 0; i < NELEMS(depositX); i++) {
		if (distance(depositX[i], depositY[i]) == a[0]) {
			return depositX[i];
		}
	}
}

int whichDepositY() {
	int hold;
	int a[NELEMS(depositX)];
	for (int i = 0; i < NELEMS(depositX); i++) {
		a[i] = distance(depositX[i], depositY[i]);
	}
	for (int i = 0; i < NELEMS(depositX); i++) {
		for (int j = 0; j < NELEMS(depositX); j++) {
			if (a[j] > a[j + 1]) {
				hold = a[j];
				a[j] = a[j + 1];
				a[j + 1] = hold;
			}
		}
	}
	for (int i = 0; i < NELEMS(depositX); i++) {
		if (distance(depositX[i], depositY[i]) == a[0]) {
			return depositY[i];
		}
	}
}

void fiCalculate(int baseFi , int tX,int tY) {
	if (tX > X && tY >= Y) {
		fi = baseFi + 270;
	}
	if (tX <= X && tY > Y) {
		fi = baseFi;
	}
	if (tX < X && tY <= Y) {
		fi = baseFi + 90;
	}
	if (tX >= X && tY < Y) {
		fi = baseFi + 180;
	}
}

void route(int baseFi, int tX, int tY) {

	if ((Compass < baseFi + 7) && (Compass > baseFi - 7)) {
		Duration = 0;
		CurAction = 100;
	}
	else if (Compass > baseFi) {
		Duration = 0;
		CurAction = 109;
	}
	else if (Compass < baseFi) {
		Duration = 0;
		CurAction = 108;
	}
}

void initializeRouting(int tX,int tY) {
	aX = abs(X - tX);
	aY = abs(Y - tY);
	if (aX == 0) {
		fiCalculate(0, tX, tY);
		route(fi,tX,tY);
	}
	else if (aY == 0) {
		fiCalculate(0, tX, tY);
		route(fi, tX, tY);
	}
	else {
		fi = atan(aY / aX) * (180 / M_PI);
		fiCalculate(fi, tX, tY);
		route(fi, tX, tY);
	}
}

bool isOnSwampLand() {
	if ((CSLeft_R >= 130 && CSLeft_R < 190 && CSLeft_G >= 130 && CSLeft_G < 190 && CSLeft_B >= 190 && CSLeft_B < 215) ||
		(CSRight_R >= 130 && CSRight_R < 190 && CSRight_G >= 130 && CSRight_G < 190 && CSRight_B >= 130 && CSRight_B < 190)) {
		return true;
	}
	else {
		return false;
	}
}

void avoidSwampland() {
	if (distance(245, 20) < 77)
	{
		if (o == 0)
		{
			t = Compass;
		}
		if (Compass <= t + 20 || Compass >= t - 20)
		{
			o = 1;
			Duration = 0;
			CurAction = 116;
		}
		if (Compass >= t + 21 || Compass <= t - 21)
		{
			Duration = 6;
			CurAction = 100;
			o = 0;
		}
	}

}

void Map1() {
	if (Time >= 180)
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

	else if (isOnDepositMap1()) {
		CurAction = 101;
		Duration = 50;
	}

	else if (isRightWheelOnDepositMap1()) {
		CurAction = 102;
		Duration = 0;
	}

	else if (isLeftWheelOnDepositMap1()) {
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

	else if (checkUltrasonic()) {
		int alaki = 0;
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
		WheelRight = -1;
		LED_1 = 0;
		MyState = 0;
		break;
	case 110:
		WheelLeft = -1;
		WheelRight = 1;
		LED_1 = 0;
		MyState = 0;
		break;
	case 600:
		WheelLeft = -2;
		WheelRight = 1;
		LED_1 = 0;
		MyState = 0;
		break;
	case 601:
		WheelLeft = 2;
		WheelRight = 4;
		LED_1 = 0;
		MyState = 0;
		break;
	case 602:
		WheelLeft = 4;
		WheelRight = 2;
		LED_1 = 0;
		MyState = 0;
		break;
	case 603:
		WheelLeft = -2;
		WheelRight = 1;
		LED_1 = 0;
		MyState = 0;
		break;
	case 604:
		WheelLeft = -3;
		WheelRight = 1;
		LED_1 = 0;
		MyState = 0;
		break;
	case 605:
		WheelLeft = 1;
		WheelRight = -3;
		LED_1 = 0;
		MyState = 0;
		break;
	default:
		break;
	}

}

void Map2() {
	if (isOnMap2 == false) {
		isOnMap2 = true;
		storage = 0;
		setMatris(0);
	}

	if (SuperObj_X != 0 && SuperObj_Y != 0) {
		SOX = SuperObj_X - 4;
		SOY = SuperObj_Y - 4;
		followingSuperObject = true;
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
	}

	else if (distance(SOX,SOY)<=2 && followingSuperObject==true) {
		CurAction = 105;
		Duration = 49;
		SOX = 0;
		SOY = 0;
		storage++;
		followingSuperObject = false;
	}

	else if (isOnBorder()) {
		onBorder();
	}

	/*else if (rightUltraSonic()) {
		CurAction = 113;
		Duration = 0;
	}

	else if (leftUltraSonic()) {
		CurAction = 114;
		Duration = 0;
	}

	else if (frontUltraSonic()) {
		CurAction = 115;
		Duration = 0;
	}*/

	else if (isOnTrap()) {
		CurAction = 110;
		Duration = 0;
	}

	else if (isRightWheelOnTrap()) {
		CurAction = 111;
		Duration = 0;
	}

	else if (isLeftWheelOnTrap()) {
		CurAction = 112;
		Duration = 0;
	}

	else if (isOnDeposit() || (shouldDeposit() && distance(whichDepositX(),whichDepositY())<3)) {
		Duration = 49;
		CurAction = 102;
	}

	else if (isRightWheelOnDeposit()) {
		CurAction = 103;
		Duration = 0;
	}

	else if (isLeftWheelOnDeposit()) {
		CurAction = 104;
		Duration = 0;
	}

	else if (isOnSuperObject()) {
		CurAction = 105;
		Duration = 49;
		SOX = 0;
		SOY = 0;
		storage++;
		followingSuperObject = false;
	}

	else if (isOnBlackPoint() || isOnRedPoint() || isOnGreenPoint()) {
		if (storage < 6) {
			if (isOnBlackPoint() && NB<2) {
				CurAction = 105;
				Duration = 49;
				storage++;
				NB++;
			}
			else if (isOnRedPoint() && NR<2) {
				CurAction = 105;
				Duration = 49;
				storage++;
				NR++;
			}
			else if (isOnGreenPoint() && NG < 2) {
				CurAction = 105;
				Duration = 49;
				storage++;
				NG++;
			}
		}
	}

	else if (checkUltrasonic()) {
		int alaki = 0;
	}

	else if (isSuperObjectAvailable()) {
		//initializeRouting(SOX,SOY);
		CurAction = move(SOX,SOY);
		followingSuperObject = true;
	}

	else if (shouldDeposit()) {
		//initializeRouting(whichDepositX(),whichDepositY());
		CurAction = move(whichDepositX(), whichDepositY());
		followingDeposit = true;
	}
	
	else if (isOnSwampLand() && CurAction == 100) {
		CurAction = 99;
	}

	else if (true) {
		Duration = 0;		
		if (NB > 1 && NR > 1)
		{
			if (MS != 2) {
				MS = 2;
				counter = 0;
			}
			setMatris(2);
		}else if (NB>1 && NG > 1) {
			if (MS != 1) {
				MS = 1;
				counter = 0;
			}
			setMatris(1);
		}else if (NG>1&&NR>1) {
			if (MS != 3) {
				MS = 3;
				counter = 0;
			}
			setMatris(3);
		}else{
			if (MS != 0) {
				MS = 0;
				counter = 0;
			}
			setMatris(0);

		}
		CurAction = Search();
	}

	/*if (followingSuperObject == true || followingDeposit == true) {
		avoidSwampland();
	}*/

	checkTrapCordinates();

	switch (CurAction)
	{
	case 99:
		WheelLeft = 5;
		WheelRight = 5;
		LED_1 = 0;
		MyState = 0;
		break;
	case 100:
		WheelLeft = defaultSpeed;
		WheelRight = defaultSpeed;
		if (isOnSwampLand()) {
			WheelLeft = 5;
			WheelRight = 5;
		}
		LED_1 = 0;
		MyState = 0;
		break;
	case 101:
		WheelLeft = -1;
		WheelRight = -3;
		LED_1 = 0;
		MyState = 0;
		break;
	case 102:
		WheelLeft = 0;
		WheelRight = 0;
		LED_1 = 2;
		MyState = 0;
		NR = 0;
		NG = 0;
		NB = 0;
		storage = 0;
		counter = 0;
		followingDeposit = false;
		break;
	case 103:
		WheelLeft = defaultSpeed;
		WheelRight = 0;
		LED_1 = 0;
		MyState = 0;
		break;
	case 104:
		WheelLeft = 0;
		WheelRight = defaultSpeed;
		LED_1 = 0;
		MyState = 0;
		break;
	case 105:
		WheelLeft = 0;
		WheelRight = 0;
		LED_1 = 1;
		MyState = 0;
		break;
	case 106:
		WheelLeft = 2;
		WheelRight = -1;
		LED_1 = 0;
		MyState = 0;
		break;
	case 107:
		WheelLeft = -1;
		WheelRight = 2;
		LED_1 = 0;
		MyState = 0;
		break;
	case 108:
		WheelLeft = 1;
		WheelRight = defaultSpeed;
		LED_1 = 0;
		MyState = 0;
		break;
	case 109:
		WheelLeft = defaultSpeed;
		WheelRight = 1;
		LED_1 = 0;
		MyState = 0;
		break;
	case 110:
		WheelLeft = defaultSpeed - 4;
		WheelRight = defaultSpeed - 6;
		LED_1 = 0;
		MyState = 0;
		break;
	case 111:
		WheelLeft = 1;
		WheelRight = defaultSpeed;
		LED_1 = 0;
		MyState = 0;
		break;
	case 112:
		WheelLeft = defaultSpeed;
		WheelRight = 1;
		LED_1 = 0;
		MyState = 0;
		break;
	case 113:
		WheelLeft = 1;
		WheelRight = -3;
		LED_1 = 0;
		MyState = 0;
		break;
	case 114:
		WheelLeft = -3;
		WheelRight = 1;
		LED_1 = 0;
		MyState = 0;
		break;
	case 115:
		WheelLeft = 2;
		WheelRight = 4;
		LED_1 = 0;
		MyState = 0;
		break;
	case 116:
		WheelLeft = -2;
		WheelRight = 2;
		LED_1 = 0;
		MyState = 0;
		break;
	case 117:
		WheelLeft = -1;
		WheelRight = 1;
		LED_1 = 0;
		MyState = 0;
		break;
	case 1000:
		WheelLeft = 3;
		WheelRight = -3;
		LED_1 = 0;
		MyState = 0;
		break;
	case 1001:
		WheelLeft = -3;
		WheelRight = 3;
		LED_1 = 0;
		MyState = 0;
		break;
	case 2000:
		WheelLeft = 2;
		WheelRight = -2;
		LED_1 = 0;
		MyState = 0;
		break;
	case 2001:
		WheelLeft = -2;
		WheelRight = 2;
		LED_1 = 0;
		MyState = 0;
		break;
	case 3000:
		WheelLeft = 1;
		WheelRight = -1;
		LED_1 = 0;
		MyState = 0;
		break;
	case 3001:
		WheelLeft = -1;
		WheelRight = 1;
		LED_1 = 0;
		MyState = 0;
		break;
	case 4000:
		WheelLeft = 3;
		WheelRight = 3;
		if (isOnSwampLand()) {
			WheelLeft = 5;
			WheelRight = 5;
		}
		LED_1 = 0;
		MyState = 0;
		break;
	case 600:
		WheelLeft = -2;
		WheelRight = 1;
		LED_1 = 0;
		MyState = 0;
		break;
	case 601:
		WheelLeft = 2;
		WheelRight = 4;
		LED_1 = 0;
		MyState = 0;
		break;
	case 602:
		WheelLeft = 4;
		WheelRight = 2;
		LED_1 = 0;
		MyState = 0;
		break;
	case 603:
		WheelLeft = -2;
		WheelRight = 1;
		LED_1 = 0;
		MyState = 0;
		break;
	case 604:
		WheelLeft = -3;
		WheelRight = 1;
		LED_1 = 0;
		MyState = 0;
		break;
	case 605:
		WheelLeft = 1;
		WheelRight = -3;
		LED_1 = 0;
		MyState = 0;
		break;
	default:
		break;
	}
}

DLL_EXPORT void OnTimer()
{
	timer = abs(480 - Time);
	switch (CurGame)
	{
	case 0:
		Map1();
		break;
	case 1:
		Map2();
		isOnMap2 = true;
		is_on_color = 0;
		break;
	default:
		break;
	}
}


float VirtualCompass()
{
	if (Compass <= 180)
	{
		return 180 + Compass;
	}
	else
		return Compass - 180;
	return 0;
}

int move(int Ox, int Oy)
{
	float V_angle = 0;
	float angle = 0;
	float dx = Ox - X;
	float dy = Oy - Y;
	float a = atan(abs(dy / dx));
	if (dy > 0 && dx > 0)
	{
		V_angle = 90 + a * 180 / 3.1415;
		angle = 270 + a * 180 / 3.1415;
	}
	else if (dy > 0 && dx < 0)
	{
		V_angle = 270 - a * 180 / 3.1415;
		angle = 90 - a * 180 / 3.1415;
	}
	else if (dy < 0 && dx < 0)
	{
		V_angle = 270 + a * 180 / 3.1415;
		angle = 90 + a * 180 / 3.1415;
	}
	else if (dy < 0 && dx > 0)
	{
		V_angle = 90 - a * 180 / 3.1415;
		angle = 270 - a * 180 / 3.1415;
	}
	float charkhesh = 0;
	if (angle > 330 || angle < 30)
	{
		charkhesh = (VirtualCompass() - V_angle);
	}
	else
		charkhesh = (Compass - angle);

	//***********************************
	if (abs(charkhesh) >= 180)
	{
		if (charkhesh > 0)
		{
			return 1000;
		}
		else
		{
			return 1001;
		}
	}

	else if (abs(charkhesh) >= 100)
	{
		if (charkhesh > 0)
		{
			return 1000;
		}
		else
		{
			return 1001;
		}
	}
	else if (abs(charkhesh) >= 70 && abs(charkhesh) <= 100)
	{
		if (charkhesh > 0)
		{
			return 2000;
		}
		else
		{
			return 2001;
		}

	}
	else if (abs(charkhesh) >= 20 && abs(charkhesh) <= 70)
	{
		if (charkhesh > 0)
		{
			return 3000;
		}
		else
		{
			return 3001;
		}
	}
	else if (true)
	{
		return 4000;
	}
}

void setMatris(int T) {
	switch (T)
	{
	case 0:
		Matris[0][0] = 60;//x1
		Matris[1][0] = 235;//y1
						   //2
		Matris[0][1] = 100;//x1
		Matris[1][1] = 175;//y1
						   //3
		Matris[0][2] = 125;//x1
		Matris[1][2] = 230;//y1
						   //4
		Matris[0][3] = 220;//x1
		Matris[1][3] = 200;//y1
						   //5
		Matris[0][4] = 290;//x1
		Matris[1][4] = 250;//y1
						   //6
		Matris[0][5] = 285;//x1
		Matris[1][5] = 165;//y1
						   //7
		Matris[0][6] = 210;//x1
		Matris[1][6] = 95;//y1

		Matris[0][7] = 265;//x1
		Matris[1][7] = 70;//y1

		Matris[0][8] = 165;//x1
		Matris[1][8] = 15;//y1

		Matris[0][9] = 240;//x1
		Matris[1][9] = 255;//y1
		MN = 9;
		break;
	case 1:
		Matris[0][0] = 250;//x1
		Matris[1][0] = 100;//y1
						   //2
		Matris[0][1] = 210;//x1
		Matris[1][1] = 80;//y1
						  //3
		Matris[0][2] = 275;//x1
		Matris[1][2] = 55;//y1
						  //4
		Matris[0][3] = 210;//x1
		Matris[1][3] = 65;//y1
						  //5
		Matris[0][4] = 185;//x1
		Matris[1][4] = 20;//y1
						  //6
		Matris[0][5] = 275;//x1
		Matris[1][5] = 30;//y1
						  //7
		Matris[0][6] = 200;//x1
		Matris[1][6] = 25;//y1

		Matris[0][7] = 185;//x1
		Matris[1][7] = 35;//y1

		Matris[0][8] = 230;//x1
		Matris[1][8] = 85;//y1

		Matris[0][9] = 270;//x1
		Matris[1][9] = 30;//y1

		break;
	case 2:
		Matris[0][0] = 55;//x1
		Matris[1][0] = 250;//y1
						   //2
		Matris[0][1] = 110;//x1
		Matris[1][1] = 225;//y1
						   //3
		Matris[0][2] = 150;//x1
		Matris[1][2] = 175;//y1
						   //4
		Matris[0][3] = 105;//x1
		Matris[1][3] = 220;//y1
						   //5
		Matris[0][4] = 110;//x1
		Matris[1][4] = 155;//y1
						   //6
		Matris[0][5] = 185;//x1
		Matris[1][5] = 180;//y1
						   //7
		Matris[0][6] = 165;//x1
		Matris[1][6] = 70;//y1

		Matris[0][7] = 95;//x1
		Matris[1][7] = 60;//y1

		Matris[0][8] = 140;//x1
		Matris[1][8] = 195;//y1
		MN = 8;
		break;
	case 3:

		Matris[0][0] = 330;//x1
		Matris[1][0] = 120;//y1
						   //2
		Matris[0][1] = 240;//x1
		Matris[1][1] = 140;//y1
						   //3
		Matris[0][2] = 320;//x1
		Matris[1][2] = 155;//y1
						   //4
		Matris[0][3] = 270;//x1
		Matris[1][3] = 200;//y1
						   //5
		Matris[0][4] = 330;//x1
		Matris[1][4] = 215;//y1
						   //6
		Matris[0][5] = 295;//x1
		Matris[1][5] = 255;//y1
						   //7
		Matris[0][6] = 265;//x1
		Matris[1][6] = 195;//y1

		Matris[0][7] = 340;//x1
		Matris[1][7] = 250;//y1

		Matris[0][8] = 300;//x1
		Matris[1][8] = 180;//y1



		break;
	default:
		break;
	}
}

int Search()
{
	if (abs(Matris[0][counter] - X)<5 && abs(Matris[1][counter] - Y)<5)
		counter++;

	if (counter > MN)
		counter = 0;
	//printf("%d",counter);

	return move(Matris[0][counter], Matris[1][counter]);
}
