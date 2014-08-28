#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!

// returns bitmap of controller buttons
int ctrlButtons() {
	return (vexRT[Btn7R]<<2)|((vexRT[Btn7D]|vexRT[Btn7U])<<1)|vexRT[Btn7L];
}

int lastBt=0;

int getLCDButton() {
	int curBt=0;
	curBt=nLCDButtons|ctrlButtons(); // bOR controller and LCD buttons so they can both be used
	// while buttons are in their last state
	while (curBt==lastBt) {
		curBt=nLCDButtons|ctrlButtons();
		wait1Msec(50);
	}
	lastBt=curBt;
	switch (curBt) {
		case 1:
			return 1; // left pressed
		case 2:
			return 2; // middle pressed
		case 4:
			return 3; // right pressed
		default:
			return 0; // none or multiple pressed
	}
}

int mod(int n,int d) {
	const int result=n%d;
	return result>=0?result:result+d;
}

float max(float a,float b) {
	if (a>b) {
		return a;
		} else {
		return b;
	}
}

float min(float a,float b) {
	if (a<b) {
		return a;
		} else {
		return b;
	}
}

float range(float n,float mn,float mx) {
	return max(min(n,mx),mn);
}

int mode=0;
int cport=0;
float cspeed=0;

char top[16];
char bottom[16];

void render() {
	clearLCDLine(0);
	clearLCDLine(1);
	snprintf(top,16,"%s port: %d",mode==0?" ":"\xF6",cport+1);
	snprintf(bottom,16,"%s speed: %d",mode==1?" ":"\xF6",cspeed);
	displayLCDString(0,0,top);
	displayLCDString(1,0,bottom);
}

void motortest() {
	bLCDBacklight=true;
	render();
	while (true) {
		int bt=getLCDButton();
		if (bt==2) {
			mode=!mode;
			render();
		} else if (bt!=0) {
			if (mode==1) {
				motor[cport]=0;
				cport=mod(cport+(bt==1?-1:1),10);
				render();
			} else {
				cspeed=range(cspeed+(bt==1?-63.5:63.5),-127,127);
				render();
			}
			motor[cport]=cspeed;
		}
	}
}

void pre_auton()
{
	motortest();
	bStopTasksBetweenModes = true;
}

task autonomous()
{
	motortest();
}

task usercontrol()
{
	motortest();
}
