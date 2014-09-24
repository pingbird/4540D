// "There's no need to modify this program." they said

void allMotorsOff();
void allTasksStop();
void pre_auton();
task autonomous();
task usercontrol();

task main()
{
	clearLCDLine(0);
	clearLCDLine(1);
	bLCDBacklight=true;
	displayLCDPos(0,0);
	displayNextLCDString("Startup");
	wait1Msec(2000);

	pre_auton();

	while (true) {
		while (bIfiRobotDisabled) {
			wait1Msec(25);
		}
		if (bIfiAutonomousMode) {
			startTask(autonomous);
			while (bIfiAutonomousMode && !bIfiRobotDisabled) {
				if (!bVEXNETActive) {
					if (nVexRCReceiveState == vrNoXmiters) {
						allMotorsOff();
					}
				}
				wait1Msec(25);
			}
			stopTask(autonomous);
			allMotorsOff();
		} else {
			startTask(usercontrol);
			while (!bIfiAutonomousMode && !bIfiRobotDisabled) {
				if (nVexRCReceiveState == vrNoXmiters) {
					allMotorsOff();
				}
				wait1Msec(25);
			}
			stopTask(usercontrol);
			allMotorsOff();
		}
	}
}


void allMotorsOff() {
	motor[port1] = 0;
	motor[port2] = 0;
	motor[port3] = 0;
	motor[port4] = 0;
	motor[port5] = 0;
	motor[port6] = 0;
	motor[port7] = 0;
	motor[port8] = 0;
#if defined(VEX2)
	motor[port9] = 0;
	motor[port10] = 0;
#endif
}

void allTasksStop() {
	stopTask(1);
	stopTask(2);
	stopTask(3);
	stopTask(4);
	#if defined(VEX2)
	stopTask(5);
	stopTask(6);
	stopTask(7);
	stopTask(8);
	stopTask(9);
	stopTask(10);
	stopTask(11);
	stopTask(12);
	stopTask(13);
	stopTask(14);
	stopTask(15);
	stopTask(16);
	stopTask(17);
	stopTask(18);
	stopTask(19);
#endif
}
