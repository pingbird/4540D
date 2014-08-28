void autonTest() {
	turnRight(180);
	turnLeft(180);
}

task autonomous() {
	printAutonMode();
	autonTest();
}