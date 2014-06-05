int mode=0;
int lastl=0;
int lastr=0;
void setMode(int md) {
	mode=md;
	char line[16];
	snprintf(line,16,"Mode: %d",mode);
	displayLCDCenteredString(1,line);
}
task usercontrol() {
	clearLCDLine(1);
	displayLCDCenteredString(0,"User control");
	setMode(0);
	while (true) {
		if ((!lastl)&&vexRT[Btn7D]!=lastl) {
			if (mode==1) {
				setMode(0);
			} else {
				setMode(1);
			}
		} else if ((!lastr)&&vexRT[Btn8D]!=lastr) {
			if (mode==2) {
				setMode(0);
			} else {
				setMode(2);
			}
		}
		lastl=vexRT[Btn7D];
		lastr=vexRT[Btn8D];
		switch (mode) {
			case 0: // normal tank controls
				motor[bottom_left]=vexRT[Ch3];
				motor[top_left]=vexRT[Ch3];
				motor[bottom_right]=vexRT[Ch2];
				motor[top_right]=vexRT[Ch2];
				motor[side_wheel]=(vexRT[Btn8L]*-127)|(vexRT[Btn8R]*127);
			break;
			case 1: // robot moves in four directions without turning
				motor[side_wheel]=vexRT[Ch4]|vexRT[Ch1];
				forwardDirect(vexRT[Ch3]|vexRT[Ch2]);
			break;
			case 2: // one stick for turning and moving forward/backward
				int fwd=vexRT[Ch3]|vexRT[Ch2];
				int turn=vexRT[Ch4]|vexRT[Ch1];
				motor[bottom_left]=fwd+turn;
				motor[top_left]=fwd+turn;
				motor[bottom_right]=fwd-turn;
				motor[top_right]=fwd-turn;
			break;
		}
		wait1Msec(50);
	}
}

