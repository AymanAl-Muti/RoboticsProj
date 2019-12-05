#include "main.h"
#include "okapi/api.hpp"
using namespace std;

void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");

	pros::lcd::register_btn1_cb(on_center_button);
}
int gyro(){
	pros::ADIAnalogIn sensor (1);
	while (true){
		cout << "distance" << sensor.get_value();
	}
}



void disabled() {}

void competition_initialize() {

}

/*using namespace okapi;

const int LFT_FRNT = 1;
const int LFT_BCK = 2;
const int RIGHT_FRNT = 3;
const int RIGHT_BCK = 4;

const double liftkP = 0.001;
const double liftkI = 0.0001;
const double liftkD = 0.0001;
const int LIFT_MTR1 = 7;
const int LIFT_MTR2 = 8;

const auto WHEEL_DIAMETER = 4_in;
const auto CHASSIS_WIDTH = 12.5_in;
auto lift = AsyncControllerFactory:: posPID(LIFT_MTR1, LIFT_MTR2,liftkP, liftkI,
liftkD);
auto drive = ChassisControllerFactory::create(
  LFT_FRNT, LFT_BCK, RIGHT_FRNT, RIGHT_BCK,
  AbstractMotor::gearset::green,
  {WHEEL_DIAMETER, CHASSIS_WIDTH}
);*/
pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::Motor left_mtr_frnt(1);
pros::Motor left_mtr_bck(2);
pros::Motor right_mtr_frnt(3);
pros::Motor right_mtr_bck(4);
pros::Motor claw_mtr(6);
pros::Motor lift1(7);
pros::Motor lift2(8);
int distanceCalc(float numb){
	return (numb/12.6)*900;
}

//distance inch
//speed velocity
void straight(float distance, int speed){
	int tick_distance = distanceCalc(distance);
	left_mtr_frnt.move_absolute(tick_distance, speed);
	left_mtr_bck.move_absolute(tick_distance, speed);
	right_mtr_frnt.move_absolute(tick_distance, speed);
	right_mtr_bck.move_absolute(tick_distance, speed);
	while (left_mtr_bck.get_position() < tick_distance && right_mtr_bck.get_position() < tick_distance){
		pros::delay(10);
	}
}
void turn(int degrees){

}

void autonomous() {
	lift1.move(100);
	lift2.move(-100);
	straight(84, 100);
	lift1.move(-100);
	lift2.move(100);
	straight(-89, 100);


}

void opcontrol() {
	const int startPosition = 10;

	#define Peto_Port 1







	while (true) {
		pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
		                 (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
		                 (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);
		int liftu = master.get_digital(DIGITAL_L1);
		int liftd = master.get_digital(DIGITAL_L2);
		int fwd = master.get_analog(ANALOG_LEFT_Y);
		int right = master.get_analog(ANALOG_RIGHT_X);
		int right2 = master.get_analog(ANALOG_RIGHT_X)*-1;
		int x = lift1.get_voltage();
		if (x == lift1.get_voltage()){
			lift2 = lift1.get_voltage()*-1;
		}

		if (master.get_digital(DIGITAL_R1) == 1)
		{
			claw_mtr.move(36);
		}
if (liftu == 1) {
	lift1 = 100;
	lift2 = -100;

}


if (liftd == 1){
	lift2 = 100;
	lift1 = -100;
}
		left_mtr_bck = fwd;
		right_mtr_frnt = fwd;
		right_mtr_bck = fwd;
		if (right >= 1){
			left_mtr_bck = right;
			left_mtr_frnt = right;
			right_mtr_frnt = right2;
			right_mtr_bck = right2;
		}
		if (right2 >= 1){
			left_mtr_bck = right;
			left_mtr_frnt = right;
			right_mtr_frnt = right2;
			right_mtr_bck = right2;
		}
 		}
	pros::delay(10);
}
