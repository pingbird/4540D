// gets the maximum value of two
float max(float a,float b) {
	if (a>b) {
		return a;
		} else {
		return b;
	}
}

// gets the minimum value of two
float min(float a,float b) {
	if (a<b) {
		return a;
		} else {
		return b;
	}
}

// makes sure a value is within a range
float range(float n,float mn,float mx) {
	return max(min(n,mx),mn);
}

int mod(int n,int d) {
	const int result=n%d;
	return result>=0?result:result+d;
}

#include "movement.c"
#include "autonSelect.c"
#include "auton.c"
#include "userControl.c"

void pre_auton() {
	/*while (true) {
		motor[side_wheel]=vexRT[AccelX];
		forwardDirect(-vexRT[AccelY]);
	}*/
	bLCDBacklight=true;
	while (true) {
		startTask(autonSelect);
		wait1Msec(500);
		while (!(vexRT[Btn7L] && vexRT[Btn7R])) {
			if (vexRT[Btn8U]) {
				startTask(autonomous);
			}
			wait1Msec(100);
		}
		stopTask(autonomous);
		stopDirect();
		motor[side_wheel]=0;
		stopTask(autonSelect);
		startTask(usercontrol);
		wait1Msec(500);
		while (!(vexRT[Btn7L] && vexRT[Btn7R])) {
			wait1Msec(100);
		}
		stopTask(usercontrol);
	}
}

