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

#define CsBot_AI_H//DO NOT delete this line
#ifndef CSBOT_REAL
#include <windows.h>
#include <stdio.h>
#include <math.h>
#define DLL_EXPORT extern __declspec(dllexport)
#define false 0
#define true 1
#endif//The robot ID : It must be two char, such as '00','kl' or 'Cr'.
char AI_MyID[2] = {'0','2'};

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
int anbar = 0;
int N_R = 0;
int N_G = 0;
int N_B = 0;
int K = 0;
int H = 0;
int X = 0;
int Y = 0;
int m = 0;
int Compass1 = 0;
int X_SO =0 ;
int Y_SO =0 ;
int G = 0;
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
    sprintf(info, "Duration=%d;SuperDuration=%d;bGameEnd=%d;CurAction=%d;CurGame=%d;SuperObj_Num=%d;SuperObj_X=%d;SuperObj_Y=%d;Teleport=%d;LoadedObjects=%d;US_Front=%d;US_Left=%d;US_Right=%d;CSLeft_R=%d;CSLeft_G=%d;CSLeft_B=%d;CSRight_R=%d;CSRight_G=%d;CSRight_B=%d;PositionX=%d;PositionY=%d;TM_State=%d;Compass=%d;Time=%d;WheelLeft=%d;WheelRight=%d;LED_1=%d;MyState=%d;",Duration,SuperDuration,bGameEnd,CurAction,CurGame,SuperObj_Num,SuperObj_X,SuperObj_Y,Teleport,LoadedObjects,US_Front,US_Left,US_Right,CSLeft_R,CSLeft_G,CSLeft_B,CSRight_R,CSRight_G,CSRight_B,PositionX,PositionY,TM_State,Compass,Time,WheelLeft,WheelRight,LED_1,MyState);
    return info;
}
 
DLL_EXPORT char* GetTeamName()
{
     return " ";
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
void Game0()
{

    if(SuperDuration>0)
    {
        SuperDuration--;
    }
    else if(Duration>0)
    {
        Duration--;
    }
	////teleport
	else if(Time>180)
	{
		Teleport=1;
		anbar=0;
		N_R=0;
		N_G=0;
		N_B=0;
	}
	/////////............
	else if (H==1 && Time>=K+4)
	{ 
		H=0;
		Duration = 0;
        CurAction =21;
	}
	///////anbar
	 else if(CSRight_R>=200 && CSRight_R<=255 && CSRight_G>=70 && CSRight_G<=130 && CSRight_B>=0 && CSRight_B<=40 && CSLeft_R>=200 && CSLeft_R<=255 && CSLeft_G>=70 && CSLeft_G<=130 && CSLeft_B>=0 && CSLeft_B<=40 && anbar>=2)
    {
        Duration = 49;
        CurAction =1;
		anbar=0;
		
    }
	////////////////Follow_anbar_Left
	else if(CSLeft_R>=200 && CSLeft_R<=255 && CSLeft_G>=70 && CSLeft_G<=130 && CSLeft_B>=0 && CSLeft_B<=30 && CSRight_R>=200 && CSRight_R<=255 && CSRight_G>=210 && CSRight_G<=255 && CSRight_B>=250 && CSRight_B<=255 && anbar>=2)
    {
        Duration = 0;
        CurAction =9;
    }
	////////////////Follow_anbar_Right
	else if(CSRight_R>=200 && CSRight_R<=255 && CSRight_G>=70 && CSRight_G<=130 && CSRight_B>=0 && CSRight_B<=40 && CSLeft_R>=200 && CSLeft_R<=255 && CSLeft_G>=210 && CSLeft_G<=255 && CSLeft_B>=250 && CSLeft_B<=255 && anbar>=2)
    {
        Duration = 0;
        CurAction =10;
    }
	
	////trap2
	else if(CSLeft_R>=200 && CSLeft_R<=255 && CSLeft_G>=170 && CSLeft_G<=255 && CSLeft_B>=0 && CSLeft_B<=70 && CSRight_R>=200 && CSRight_R<=255 && CSRight_G>=170 && CSRight_G<=255 && CSRight_B>=0 && CSRight_B<=70)
    {
        Duration = 1;
        CurAction =2;
    }
	////trap-r
    else if(CSRight_R>=200 && CSRight_R<=255 && CSRight_G>=170 && CSRight_G<=255 && CSRight_B>=0 && CSRight_B<=70)
    {
        Duration = 1;
        CurAction =3;
    }
	////trap-l
    else if(CSLeft_R>=200 && CSLeft_R<=255 && CSLeft_G>=170 && CSLeft_G<=255 && CSLeft_B>=0 && CSLeft_B<=70)
    {
        Duration = 1;
        CurAction =4;
    }
	////////////////Red
    else if((CSLeft_R>=200 && CSLeft_R<=255 && CSLeft_G>=0 && CSLeft_G<=55 && CSLeft_B>=0 && CSLeft_B<=55 && anbar<=5 && H==0) || (H==0 &&  CSRight_R>=200 && CSRight_R<=255 && CSRight_G>=0 && CSRight_G<=55 && CSRight_B>=0 && CSRight_B<=55 && anbar<=5))
    {
        Duration = 49;
        CurAction =206;
	anbar++;
	K=Time;
	H=1;
    }
	////////////////Black
	 else if((CSLeft_R>=15 && CSLeft_R<=55 && CSLeft_G>=15 && CSLeft_G<=55 && CSLeft_B>=15 && CSLeft_B<=55 && anbar<=5 && H==0)||(H==0 &&CSRight_R>=15 && CSRight_R<=55 && CSRight_G>=15 && CSRight_G<=55 && CSRight_B>=15 && CSRight_B<=55 && anbar<=5))
    {
        Duration = 46;
        CurAction =206;
	anbar++;
	K=Time;
	H=1;
    }
	////////////////Green
	else if((CSLeft_R>=0 && CSLeft_R<=55 && CSLeft_G>=230 && CSLeft_G<=255 && CSLeft_B>=0 && CSLeft_B<=55 && anbar<=5 && H==0) || (H==0 && CSRight_R>=0 && CSRight_R<=55 && CSRight_G>=230 && CSRight_G<=255 && CSRight_B>=0 && CSRight_B<=55  && anbar<=5))
    {
        Duration = 49;
        CurAction =206;
        anbar++;
		K=Time;
		H=1;
    }
	////////move

    else if(US_Front>=0 && US_Front<=10)
    {
        Duration = 0;
        CurAction =6;
    }
    else if(US_Left>=0 && US_Left<=10)
    {
        Duration = 0;
        CurAction =7;
    }
    else if(US_Right>=0 && US_Right<=10)
    {
        Duration = 0;
        CurAction =8;
    }
    else if(true)
    {
        Duration = 0;
        CurAction =11;
    }
    
       
    

    switch(CurAction)
    {
		 case 1:
            WheelLeft=0;
            WheelRight=0;
            LED_1=2;
            MyState=0;
            break;
		case 2:
            WheelLeft=-1;
            WheelRight=-3;
            LED_1=0;
            MyState=0;
            break;
        case 3:
            WheelLeft=-3;
            WheelRight=-1;
            LED_1=0;
            MyState=0;
            break;
        case 4:
            WheelLeft=-1;
            WheelRight=-3;
            LED_1=0;
            MyState=0;
            break;
        case 4:
            WheelLeft=1;
            WheelRight=-2;
            LED_1=0;
            MyState=0;
            break;

		case 5:
            WheelLeft=0;
            WheelRight=0;
            LED_1=1;
            MyState=0;
            break;

        case 6:
            WheelLeft=0;
            WheelRight=-2;
            LED_1=0;
            MyState=0;
            break;
        case 7:
            WheelLeft=4;
            WheelRight=2;
            LED_1=0;
            MyState=0;
            break;
        case 8:
            WheelLeft=2;
            WheelRight=4;
            LED_1=0;
            MyState=0;
            break;
		case 9:
            WheelLeft=-1;
            WheelRight=1;
            LED_1=0;
            MyState=0;
            break;
		case 10:
            WheelLeft=1;
            WheelRight=-1;
            LED_1=0;
            MyState=0;
            break;
        case 11:
            WheelLeft=2;
            WheelRight=2;
            LED_1=0;
            MyState=0;
            break;
			case 206:
            WheelLeft=0;
            WheelRight=0;
            LED_1=1;
            MyState=0;
            break;
        default:
            break;

    }
}

void Game1()
{
if (PositionX != 0)
{
	X=PositionX;
}
if (PositionY != 0)
{
	Y=PositionY;
}
    if(SuperDuration>0)
    {
        SuperDuration--;
    }
    else if(Duration>0)
    {
        Duration--;
		
    }
	
	///////anbar
	 else if(CSRight_R>=200 && CSRight_R<=255 && CSRight_G>=70 && CSRight_G<=130 && CSRight_B>=0 && CSRight_B<=40 && CSLeft_R>=200 && CSLeft_R<=255 && CSLeft_G>=70 && CSLeft_G<=130 && CSLeft_B>=0 && CSLeft_B<=40 && anbar>=2)
    {
        Duration = 49;
        CurAction =1;
		anbar=0;
		X_SO=0;
		Y_SO=0;
		N_R = 0;
        N_G = 0;
        N_B = 0;
    }
	////////////////Follow_anbar_Left
	else if(CSLeft_R>=200 && CSLeft_R<=255 && CSLeft_G>=70 && CSLeft_G<=130 && CSLeft_B>=0 && CSLeft_B<=30 && CSRight_R>=200 && CSRight_R<=255 && CSRight_G>=210 && CSRight_G<=255 && CSRight_B>=250 && CSRight_B<=255 && anbar>=2)
    {
        Duration = 0;
        CurAction =9;
    }
	////////////////Follow_anbar_Right
	else if(CSRight_R>=200 && CSRight_R<=255 && CSRight_G>=70 && CSRight_G<=130 && CSRight_B>=0 && CSRight_B<=40 && CSLeft_R>=200 && CSLeft_R<=255 && CSLeft_G>=210 && CSLeft_G<=255 && CSLeft_B>=250 && CSLeft_B<=255 && anbar>=2)
    {
        Duration = 0;
        CurAction =10;
    }



else if(((sqrt(( X - X_SO)^2))<=2) && ((sqrt(( Y - Y_SO)^2))<=2) && G==1)
	{
        Duration = 49;
        CurAction =206;
		anbar++;
    }
///////////SuperObj
    else if(CSLeft_R>=210 && CSLeft_R<=230 && CSLeft_G>=20 && CSLeft_G<=60 && CSLeft_B>=250 && CSLeft_B<=255 )
	{
        Duration = 49;
        CurAction =206;
		anbar++;
    }
	///////////SuperObj
    else if(CSRight_R>=210 && CSRight_R<=230 && CSRight_G>=20 && CSRight_G<=60 && CSRight_B>=250 && CSRight_B<=255 )
    {
        Duration = 49;
        CurAction =206;
		anbar++;
    }

	////////////SuperObj
	else if(SuperObj_X != 0 || SuperObj_Y != 0)
	{
		X_SO=SuperObj_X;
		Y_SO=SuperObj_Y;
		G=1;
	}
	else if(X_SO!=0 || Y_SO!=0)
	{
		//////////N_1
		if(X_SO>X && Y_SO>Y)
		{
		m =atan((Y_SO-Y)/(X_SO-X))*(180/3.14);
		Compass1= m + 270;

		if(Compass>(Compass1 + 2))
				{
					
					Duration=0;
					CurAction=70;
				}
				if(Compass<(Compass1 - 2))
				{
					Duration=0;
					CurAction=80;
				}
				if((Compass1 + 2)>Compass>(Compass1 - 2))
				{
					Duration=0;
					CurAction=21;
				}
		}
	    ////////////N_2
		if(X_SO<X && Y_SO>Y)
		{
		m =atan((Y-Y_SO)/(X_SO-X))*(180/3.14);
		Compass1= m;

		if(Compass>(Compass1 + 2))
				{
					
					Duration=0;
					CurAction=70;
				}
				if(Compass<(Compass1 - 2))
				{
					Duration=0;
					CurAction=80;
				}
				if((Compass1 + 2)>Compass>(Compass1 - 2))
				{
					Duration=0;
					CurAction=21;
				}
		
		}
		///////////N_3
		if(X_SO<X && Y_SO<Y)
		{
		m =atan((Y-Y_SO)/(X-X_SO))*(180/3.14);
		Compass1 = m + 90;
		
		if(Compass>(Compass1 + 2))
				{
					Duration=0;
					CurAction=70;
				}
				if(Compass<(Compass1 - 2))
				{
					Duration=0;
					CurAction=80;
				}
				if((Compass1 + 2)>Compass>(Compass1 - 2))
				{
					Duration=0;
					CurAction=21;
				}
		}
		/////////////N_4
		if(X_SO>X && Y_SO<Y)
		{
		m =atan((Y_SO-Y)/(X-X_SO))*(180/3.14);
		Compass1= m + 180;

		if(Compass>(Compass1 + 2))
				{
					
					Duration=0;
					CurAction=70;
				}
				if(Compass<(Compass1 - 2))
				{
					Duration=0;
					CurAction=80;
				}
				if((Compass1 + 2)>Compass>(Compass1 - 2))
				{
					Duration=0;
					CurAction=21;
				}
		}
	}
	
	////////////////Slower
   else if((CSRight_R>=125 && CSRight_R<=160 && CSRight_G>=130 && CSRight_G<=170 && CSRight_B>=180 && CSRight_B<=215) || (CSLeft_R>=125 && CSLeft_R<=160 && CSLeft_G>=130 && CSLeft_G<=170 && CSLeft_B>=180 && CSLeft_B<=215))
    {
    if((X>=135 && Y<=130) || (X<135))
		{

		////n3
		if(X>=160 && Y<=130)
		{
		m =atan((130-Y)/(X-160))*(180/3.14);
		Compass1= m;

		if(Compass>(Compass1 + 5))
				{
					
					Duration=0;
					CurAction=70;
				}
				if(Compass<(Compass1 - 5))
				{
					Duration=0;
					CurAction=80;
				}
				if((Compass1 + 5)>Compass>(Compass1 - 5))
				{
					Duration=0;
					CurAction=21;
				}
		}
	    ////////////n4
		if(X<160 )
		{
		m =atan((130-Y)/(X-175))*(180/3.14);
		Compass1= m + 180;

		if(Compass>(Compass1 + 5))
				{
					
					Duration=0;
					CurAction=70;
				}
				if(Compass<(Compass1 - 5))
				{
					Duration=0;
					CurAction=80;
				}
				if((Compass1 + 5)>Compass>(Compass1 - 5))
				{
					Duration=0;
					CurAction=21;
				}
		}
	    
	}
	}
	
	
	
	////trap2
	else if(CSLeft_R>=200 && CSLeft_R<=255 && CSLeft_G>=170 && CSLeft_G<=255 && CSLeft_B>=0 && CSLeft_B<=70 && CSRight_R>=200 && CSRight_R<=255 && CSRight_G>=170 && CSRight_G<=255 && CSRight_B>=0 && CSRight_B<=70)
    {
        Duration = 1;
        CurAction =2;
    }
	////trap-r
    else if(CSRight_R>=200 && CSRight_R<=255 && CSRight_G>=170 && CSRight_G<=255 && CSRight_B>=0 && CSRight_B<=70)
    {
        Duration = 1;
        CurAction =3;
    }
	////trap-l
    else if(CSLeft_R>=200 && CSLeft_R<=255 && CSLeft_G>=170 && CSLeft_G<=255 && CSLeft_B>=0 && CSLeft_B<=70)
    {
        Duration = 1;
        CurAction =4;
    }
	////////////////Red
    else if((CSLeft_R>=200 && CSLeft_R<=255 && CSLeft_G>=0 && CSLeft_G<=55 && CSLeft_B>=0 && CSLeft_B<=55 && anbar<=5 && N_R<2) || (N_R<2 &&  CSRight_R>=200 && CSRight_R<=255 && CSRight_G>=0 && CSRight_G<=55 && CSRight_B>=0 && CSRight_B<=55 && anbar<=5))
    {
        Duration = 49;
        CurAction =206;
	    anbar++;
	    N_R++;
    }
	////////////////Black
	 else if((CSLeft_R>=15 && CSLeft_R<=55 && CSLeft_G>=15 && CSLeft_G<=55 && CSLeft_B>=15 && CSLeft_B<=55 && anbar<=5 && N_B<2)||(N_B<2 && CSRight_R>=15 && CSRight_R<=55 && CSRight_G>=15 && CSRight_G<=55 && CSRight_B>=15 && CSRight_B<=55 && anbar<=5))
    {
        Duration = 46;
        CurAction =206;
	    anbar++;
	    N_B++;
    }
	////////////////Green
	else if((CSLeft_R>=0 && CSLeft_R<=55 && CSLeft_G>=230 && CSLeft_G<=255 && CSLeft_B>=0 && CSLeft_B<=55 && anbar<=5 && N_G<2) || (N_G<2 && CSRight_R>=0 && CSRight_R<=55 && CSRight_G>=230 && CSRight_G<=255 && CSRight_B>=0 && CSRight_B<=55  && anbar<=5))
    {
        Duration = 49;
        CurAction =206;
        anbar++;
		N_G++;
    }
	 else if(anbar>=5)
	{
		
		if(X<=180 && Y<=140)
		{
		m =atan(Y/X)*(180/3.14);
		Compass1= m + 90;

		

		if(Compass>=(Compass1 + 2))
				{
					
					Duration=0;
					CurAction=70;
				}
				if(Compass<=(Compass1 - 2))
				{
				    Duration=0;
					CurAction=80;
				}
				if((Compass1 + 2)>Compass>(Compass1 - 2))
				{
					Duration=0;
					CurAction=21;
				}
		
		}
	
	
	
		if(X>180 || Y>140)
		{
		m =atan((260-Y)/(360-X))*(180/3.14);
		Compass1= m + 270;
		
		if(Compass>=(Compass1 + 2))
				{
					
					Duration=0;
					CurAction=70;
				}
				if(Compass<=(Compass1 - 2) )
				{
				    Duration=0;
					CurAction=80;
				}
				if((Compass1 + 2)>Compass>(Compass1 - 2))
				{
					Duration=0;
					CurAction=21;
				}
		
		}
	
	}
	

	 ////////////Position
	 else if(X<=10 || X>=345 || Y<=10 || Y>=250)
	 { 
		////n3
		 if(X<=175 && Y<=130)
		{
		m =atan((130-Y)/(175-X))*(180/3.14);
		Compass1= m + 270;

		 if(Compass>(Compass1 + 5))
				{
					
					Duration=0;
					CurAction=6;
				}
				 if(Compass<(Compass1 - 5))
				{
					Duration=0;
					CurAction=9;
				}
				 if((Compass1 + 5)>Compass>(Compass1 - 5))
				{
					Duration=0;
					CurAction=21;
				}
		 }
	    ////////////n4
		if(X>=175 && Y<=130)
		{
		m =atan((130-Y)/(X-175))*(180/3.14);
		Compass1= 90 -m;

		if(Compass>(Compass1 + 5))
				{
					
					Duration=0;
					CurAction=6;
				}
				if(Compass<(Compass1 - 5))
				{
					Duration=0;
					CurAction=9;
				}
				if((Compass1 + 5)>Compass>(Compass1 - 5))
				{
					Duration=0;
					CurAction=21;
				}
		}
		///////////n1
		if(X>=175 && Y>=130)
		{
		m =atan((Y-130)/(X-175))*(180/3.14);
		Compass1= m + 90;

		if(Compass>(Compass1 + 5))
				{
					
					Duration=0;
					CurAction=6;
				}
				if(Compass<(Compass1 - 5))
				{
					Duration=0;
					CurAction=9;
				}
				if((Compass1 + 5)>Compass>(Compass1 - 5))
				{
					Duration=0;
					CurAction=21;
				}
		}
		/////////////n2
		if(X<=175 && Y>=130)
		{
		m =atan((Y-130)/(175-X))*(180/3.14);
		Compass1= 270 - m;

		if(Compass>(Compass1 + 5))
				{
					
					Duration=0;
					CurAction=6;
				}
				if(Compass<(Compass1 - 5))
				{
					Duration=0;
					CurAction=9;
				}
				if((Compass1 + 5)>Compass>(Compass1 - 5))
				{
					Duration=0;
					CurAction=21;
				}
		}
	}
	
    
    
		
	////////move

    else if(US_Front>=0 && US_Front<=10)
    {
        Duration = 0;
        CurAction =6;
    }
    else if(US_Left>=0 && US_Left<=10)
    {
        Duration = 0;
        CurAction =7;
    }
    else if(US_Right>=0 && US_Right<=10)
    {
        Duration = 0;
        CurAction =8;
    }
    else if(true)
    {
        Duration = 0;
        CurAction =21;
	}

    switch(CurAction)
    {
		case 21:
            WheelLeft=3;
            WheelRight=3;
            LED_1=0;
            MyState=0;
            break;
		 case 1:
            WheelLeft=0;
            WheelRight=0;
            LED_1=2;
            MyState=0;
            break;
		case 2:
            WheelLeft=-1;
            WheelRight=-3;
            LED_1=0;
            MyState=0;
            break;
        case 3:
            WheelLeft=-3;
            WheelRight=-1;
            LED_1=0;
            MyState=0;
            break;
        case 4:
            WheelLeft=-1;
            WheelRight=-3;
            LED_1=0;
            MyState=0;
            break;
        case 4:
            WheelLeft=1;
            WheelRight=-2;
            LED_1=0;
            MyState=0;
            break;

		case 5:
            WheelLeft=0;
            WheelRight=0;
            LED_1=1;
            MyState=0;
            break;

        case 6:
            WheelLeft=1;
            WheelRight=-1;
            LED_1=0;
            MyState=0;
            break;
        case 7:
            WheelLeft=4;
            WheelRight=2;
            LED_1=0;
            MyState=0;
            break;
        case 8:
            WheelLeft=2;
            WheelRight=4;
            LED_1=0;
            MyState=0;
            break;
		case 9:
            WheelLeft=-1;
            WheelRight=1;
            LED_1=0;
            MyState=0;
            break;
		case 10:
            WheelLeft=1;
            WheelRight=-1;
            LED_1=0;
            MyState=0;
            break;
        case 11:
            WheelLeft=2;
            WheelRight=2;
            LED_1=0;
            MyState=0;
            break;
			case 206:
            WheelLeft=0;
            WheelRight=0;
            LED_1=1;
            MyState=0;
            break;
			case 70:
            WheelLeft=3;
            WheelRight=1;
            LED_1=0;
            MyState=0;
            break;
        case 80:
            WheelLeft=1;
            WheelRight=3;
            LED_1=0;
            MyState=0;
            break;
			
        default:
            break;

    }
}


DLL_EXPORT void OnTimer()
{
    switch (CurGame)
    {
        case 9:
            break;
        case 10:
            WheelLeft=0;
            WheelRight=0;
            LED_1=0;
            MyState=0;
            break;
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













