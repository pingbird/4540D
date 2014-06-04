int autonColor=0;
int autonSide=0;
int autonMode=0;

int autonMenu=0;
int autonSel=1;

// returns bitmap of controller buttons
int ctrlButtons() {
	return (vexRT[Btn8R]<<2)|((vexRT[Btn8D]|vexRT[Btn8U])<<1)|vexRT[Btn8L];
}

int lastBt=0;

int getLCDButton() {
	int curBt=0;
	curBt=nLCDButtons|ctrlButtons(); // bOR controller and LCD buttons so they can both be used
	// while buttons are in their last state
	while (curBt==lastBt) {
		curBt=nLCDButtons|ctrlButtons();
		wait1Msec(50); // give time to other threads
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

void autonSelect() {
	bLCDBacklight=true;
	while (true) {
		char top[16];
		char selFmt[19];
		// Skills | Red | Blue menu
		if (autonMenu==0) {
			if (autonColor==2) {
				strcpy(top,"Skills");
			} else {
				// show battery info if the selected auton isnt skills
				char battery[16];
				sprintf(battery,"4540D  %i.%iV",nImmediateBatteryLevel/1000,(nImmediateBatteryLevel%1000)/10);
				strcpy(top,battery);
			}
			snprintf(selFmt,16,"%%sSkills%%sRed%%sBlue");
		}
		if (autonMenu>0) {
			// add color to top
			strcpy(top,autonColor==0?"Red ":"Blue ");
		}
		if (autonMenu==1) {
			// Back | Left | Right menu
			snprintf(selFmt,16,"%%sBack%%sLeft%%sRight");
		} else if (autonMenu==2) {
			// Back | 1 | 2 menu
			strcat(top,autonSide==0?"Left":"Right");
			strcat(top,autonMode==0?" 1":" 2");
			snprintf(selFmt,16,"%%sBack%%s1%%s2");
		}
		// display top
		clearLCDLine(0);
		displayLCDCenteredString(0,top);
		char bottom[16];
		strcpy(bottom,"                ");
		while (true) {
			// display bottom
			snprintf(bottom,16,selFmt,
				autonSel==0?"\xF6":" ",
				autonSel==1?"\xF6":" ",
				autonSel==2?"\xF6":" ",
			);
			clearLCDLine(1);
			displayLCDCenteredString(1,bottom);
			int button=getLCDButton();
			if (button==1) {
				// left
				// mod makes the selection wrap around
				autonSel=mod(autonSel-1,3);
			} else if (button==2) {
				// middle
				break;
			} else if (button==3) {
				// right
				autonSel=mod(autonSel+1,3);
			}
		}
		int lastMenu=autonMenu;
		switch (autonMenu) {
		case 0:
			// Skills | Red | Blue menu
			autonColor=mod(autonSel-1,3);
			if (autonSel==0) {
				autonMenu=1;
			}
			break;
		case 1:
			// Back | Left | Right menu
			if (autonSel>0) {
				autonSide=autonSel-1;
			}
			break;
		case 2:
			// Back | 1 | 2 menu
			if (autonSel>0) {
				autonMode=autonSel-1;
				autonMenu=1;
			}
			break;
		}
		if (autonSel==0) {
			autonMenu=autonMenu-1;
		} else {
			autonMenu=autonMenu+1;
		}
		if (autonMenu!=lastMenu) {
			autonSel=1;
		}
	}
}
