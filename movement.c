float smooth=2; // degrees off to ajustment ratio
float l;
float r;
float cm_ratio=1; // cm to encoder value ratio, havent measured yet

void encoderStart(float sl,float sr) {
	l=sl*cm_ratio;
	r=sr*cm_ratio;
	resetMotorEncoder(bottom_left);
	resetMotorEncoder(bottom_right);
}

void encoderRun(float mult) {
	// difference between left and right motors
	int dif=smooth*((getMotorEncoder(bottom_left)/l)-(getMotorEncoder(bottom_right)/r));

	int left=range((127-dif)*l,-127,127)*mult; // left power
	int right=range((127+dif)*r,-127,127)*mult; // right power

	motor[bottom_left]=left;
	motor[top_left]=left;
	motor[bottom_right]=right;
	motor[top_right]=right;
}

void encoderStop() {
	// reverse wheels to stop momentum
	motor[bottom_left]=l*-64;
	motor[top_left]=l*-64;
	motor[bottom_right]=r*-64;
	motor[top_right]=r*-64;
	wait1Msec(40);
	motor[bottom_left]=0;
	motor[top_left]=0;
	motor[bottom_right]=0;
	motor[top_right]=0;
	wait1Msec(300);
}

int encoderMaxOff=0;

void encoder(float dist,int sl,int sr) {
	if (dist<0) {
		dist=-dist;
		sl=-sl;
		sr=-sr;
	}
	encoderStart(sl,sr);
	float rdist=0;
	while (rdist<dist) {
		rdist=((getMotorEncoder(bottom_left)/l)+(getMotorEncoder(bottom_right)/r))/2;
		encoderRun(range((dist-rdist)/500,0.2,1)); // slow when it is close to stopping
	}
	encoderStop();
	// see how much it was off, should not be greater than -/+20 for turns
	encoderMaxOff=max(dist-(((getMotorEncoder(bottom_left)/l)+(getMotorEncoder(bottom_right)/r))/2),encoderMaxOff);
	char line[16];
	snprintf(line,16,"Off: %d",encoderMaxOff);
	clearLCDLine(1);
	displayLCDCenteredString(1,line);
}

void forwardDirect(int pow) {
	motor[bottom_left]=pow;
	motor[top_left]=pow;
	motor[bottom_right]=pow;
	motor[top_right]=pow;
}

void backwardDirect(int pow) {
	motor[bottom_left]=pow;
	motor[top_left]=pow;
	motor[bottom_right]=pow;
	motor[top_right]=pow;
}

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

void stopDirect() {
	motor[bottom_left]=0;
	motor[top_left]=0;
	motor[bottom_right]=0;
	motor[top_right]=0;
}

void forward(float dist) {
	encoder(dist,1,1);
}

void backward(float dist) {
	encoder(dist,-1,-1);
}

void turnRight(float deg) {
	encoder(3.55*deg,1,-1);
}

void turnLeft(float deg) {
	encoder(3.55*deg,-1,1);
}