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

void pre_auton() {
	autonSelect();
}

task usercontrol() {
	while (true) {
		motor[bottom_left]=vexRT[Ch3];
		motor[top_left]=vexRT[Ch3];
		motor[bottom_right]=vexRT[Ch2];
		motor[top_right]=vexRT[Ch2];
		motor[side_wheel]=(vexRT[Btn8L]*127)|(vexRT[Btn8R]*-127);
	}
}

