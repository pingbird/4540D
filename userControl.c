int mode=0;
int lastl=0;
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
		}
		lastl=vexRT[Btn7D];
		switch (mode) {
			case 0: // normal tank controls
				motor[bottom_left]=vexRT[Ch3];
				motor[top_left]=vexRT[Ch3];
				motor[bottom_right]=vexRT[Ch2];
				motor[top_right]=vexRT[Ch2];
				motor[side_wheel]=(vexRT[Btn8L]*-127)|(vexRT[Btn8R]*127);
			break;
			case 1: // left stick moves robot in four directions and right stick turns
				motor[side_wheel]=vexRT[Ch4];
				int turn=vexRT[Ch1];
				int fwd=vexRT[Ch3];
				motor[bottom_left]=fwd+turn;
				motor[top_left]=fwd+turn;
				motor[bottom_right]=fwd-turn;
				motor[top_right]=fwd-turn;
			break;
		}
		wait1Msec(50);
	}
}
