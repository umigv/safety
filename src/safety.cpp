/*
 * IGV Safety Microprocessor
 * Authored by Chris Marsh, UMIGV
 * Based off of a template by Andrew Kramer
 * http://andrewjkramer.net/motor-encoders-arduino/
 */
 
// pins for the encoder inputs
#define RIGHT_FRONT_ENCODER_A 2
#define RIGHT_FRONT_ENCODER_B 3

#define LEFT_FRONT_ENCODER_A 4
#define LEFT_FRONT_ENCODER_B 5

#define MOTOR_ENABLE 6;
#define STOPPED_SIGNAL 7;

// variables to store the number of encoder pulses
// for each motor
volatile unsigned long rightFrontCount = 0;
volatile unsigned long leftFrontCount = 0;
 
void setup() {
	//Inputs of the encoders
	pinMode(RIGHT_FRONT_ENCODER_A, INPUT);
	pinMode(RIGHT_FRONT_ENCODER_B, INPUT);
	pinMode(LEFT_FRONT_ENCODER_A, INPUT);
	pinMode(LEFT_FRONT_ENCODER_B, INPUT);

	//Pin enabling the relays
	pinMode(MOTOR_ENABLE, OUTPUT);

	//Output pin to send a simple signal to the NUC indicating status
	pinMode(STOPPED_SIGNAL);
	
	// initialize hardware interrupts
	attachInterrupt(digitalPinToInterrupt(RIGHT_FRONT_ENCODER_A), leftEncoderEvent, CHANGE);
	attachInterrupt(digitalPinToInterrupt(LEFT_FRONT_ENCODER_A), rightEncoderEvent, CHANGE);
	digitalWrite(MOTOR_ENABLE, HIGH);
	digitalWrite(STOPPED_SIGNAL, LOW);
	
	Serial.begin(9600);
}
 
void loop() {
	Serial.print("Right Front Count: ");
	Serial.println(rightFrontCount);
	Serial.print("Left Front Count: ");
	Serial.println(leftFrontCount);
	Serial.println();//Line spacing

	float scaler = 1;//Number to be calculated mapping encoder ticks to miles/hour  
	//Yes I do know it's spelled 'scalar', but this is something that scales, so, 'scaler' :-P
	float leftSpeed = (float)leftFrontCount / scaler;
	float rightSpeed = (float)rightFrontCount / scaler;
	float totalSpeed = (leftSpeed + rightSpeed) / 2.0;

	//Detect max speed, shut down
	if(totalSpeed >= 5.0){
		digitalWrite(MOTOR_ENABLE, LOW);
		digitalWrite(STOPPED_SIGNAL, HIGH);
		//Infinite loop for now, probably to change later
		while(1){
			serial.println('Motor Speed Limit Tripped');
			delay(2000);
		}
	}

	//Reset the counts
	rightFrontCount = 0;
	leftFrontCount = 0;

	//Interrupts can be triggered during this time in particular
	delay(500);
}

//These below functions have not been modified much. Testing is needed to see if they work
 
// encoder event for the interrupt call
void rightFrontEncoderEvent() {
	if(digitalRead(RIGHT_FRONT_ENCODER_A) == HIGH){
		if(digitalRead(RIGHT_FRONT_ENCODER_B) == LOW){
			rightCount++;
		}else {
			rightCount--;
		}
	}else {
		if(digitalRead(RIGHT_FRONT_ENCODER_B) == LOW){
			rightCount--;
		}else{
			rightCount++;
		}
	}
}

// encoder event for the interrupt call
void leftFrontEncoderEvent() {
	if(digitalRead(LEFT_FRONT_ENCODER_A) == HIGH){
		if(digitalRead(LEFT_FRONT_ENCODER_B) == LOW){
			leftCount++;
		}else {
			leftCount--;
		}
	}else{
		if(digitalRead(LEFT_FRONT_ENCODER_B) == LOW){
			leftCount--;
		}else{
			leftCount++;
		}
	}
}
 
