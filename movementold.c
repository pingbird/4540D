void stopDirect() {
	motor[bottom_left]=0;
	motor[top_left]=0;
	motor[bottom_right]=0;
	motor[top_right]=0;
}

void forwardDirect(int pow) {
	motor[bottom_left]=pow;
	motor[top_left]=pow;
	motor[bottom_right]=pow;
	motor[top_right]=pow;
}

void backDirect(int pow) {
	motor[bottom_left]=-pow;
	motor[top_left]=-pow;
	motor[bottom_right]=-pow;
	motor[top_right]=-pow;
}

#define backwardDirect(pow) backDirect(pow)

void rightDirect(int pow) {
	motor[bottom_left]=pow;
	motor[top_left]=pow;
	motor[bottom_right]=-pow;
	motor[top_right]=-pow;
}

void leftDirect(int pow) {
	motor[bottom_left]=-pow;
	motor[top_left]=-pow;
	motor[bottom_right]=pow;
	motor[top_right]=pow;
}

void right(float time) {
	rightDirect(127*(-reversed));
	wait1Msec(time*1000);
	stopDirect();
	wait1Msec(100);
}

void left(float time) {
	leftDirect(127*(-reversed));
	wait1Msec(time*1000);
	stopDirect();
	wait1Msec(100);
}

#define dtr(name,f) void name(float time) {f(127); wait1Msec(time*1000); stopDirect(); wait1Msec(100);}

dtr(forward,forwardDirect)
dtr(back,backDirect)

#define backward(time) back(time)

#define turnRight(time) right(time)

#define turnLeft(time) left(time)