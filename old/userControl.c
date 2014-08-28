int mode=0;
int lastl=0;
void setMode(int md) {
	mode=md;
	char line[16];
	snprintf(line,16,"Mode: %d",mode);
	displayLCDCenteredString(1,line);
}
#define getBtns(a,b) ((vexRT[a]*-127)+(vexRT[b]*127))
float clawslow=1;
task usercontrol() {
	clearLCDLine(1);
	displayLCDCenteredString(0,"User control");
	setMode(0);
	while (true) {
		if ((!lastl)&&vexRT[Btn7R]!=lastl) {
			setMode(!mode);
		}
		lastl=vexRT[Btn7R];
		motor[arm_left]=getBtns(Btn5D,Btn5U);
		motor[arm_right]=getBtns(Btn5D,Btn5U);
		if (getBtns(Btn6D,Btn6U)==0) {
			clawslow=1;
		} else {
			clawslow=max(clawslow-0.05,0);
		}
		motor[claw_grab]=getBtns(Btn6D,Btn6U)*clawslow;
		motor[claw_tilt]=getBtns(Btn8D,Btn8U);
		motor[claw_slide]=getBtns(Btn7D,Btn7U);
		switch (mode) {
			case 0: // normal tank controls
				motor[bottom_left]=vexRT[Ch3];
				motor[top_left]=vexRT[Ch3];
				motor[bottom_right]=vexRT[Ch2];
				motor[top_right]=vexRT[Ch2];
				#ifdef side_wheel
				motor[side_wheel]=getBtns(Btn8L,Btn8R);
				#endif
			break;
			case 1: // left stick moves robot in four directions and right stick turns
				#ifdef side_wheel
				motor[side_wheel]=vexRT[Ch4];
				#endif
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
