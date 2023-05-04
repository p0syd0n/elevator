// Include the V5 Library
#include "vex.h"
  
// Allows for easier use of the VEX Library
using namespace vex;

bool bottom = false;
int level = 0;

void go_up() {
  Motor1.spinFor(reverse, 9, turns, false);
  Motor2.spinFor(forward, 9, turns, false);
}

void up_a_floor() {
  switch (level) {
    case 0:
      Motor1.spinFor(reverse, 4, turns, false);
      Motor2.spinFor(forward, 4, turns, false);
  }
  Motor1.spinFor(reverse, 4, turns, false);
  Motor2.spinFor(forward, 4, turns, false);
}

void go_to_floor(int destination) {
    Motor1.spinFor(reverse, 4*destination, turns, false);
    Motor2.spinFor(forward, 4*destination, turns, false);
}

void up_a_floor1() {
    Motor1.spinFor(reverse, 4, turns, false);
    Motor2.spinFor(forward, 4, turns, false);
}

void go_bottom() {
  Motor1.spinFor(forward, 10, turns, false);
  Motor2.spinFor(reverse, 10, turns, false);
  while (true) {
    Brain.Screen.print(bottom);
    if (bottom == 1) {
      Motor1.stop();
      Motor2.stop();
      break;
    }
  }
}

void bottom_switch_callback() {
  bottom = true;
}

void bottom_switch_callback_release() {
  bottom = false;
}

void up_a_turn() {
  Motor1.spinFor(reverse, 1, turns, false);
  Motor2.spinFor(forward, 1, turns, false);
}

void test_floor() {
  go_to_floor(2);
}

void down_a_turn() {
  Motor1.spinFor(forward, 1, turns, false);
  Motor2.spinFor(reverse, 1, turns, false);
}

//1 turn  = 5/8 inch
//c: bottom
//b: up 1
int main() {
  LimitSwitch_Bottom_A.pressed(bottom_switch_callback);
  LimitSwitch_Bottom_A.released(bottom_switch_callback_release);
  Bumper_up1_B.pressed(up_a_floor1);
  Bumper_AllDown_C.pressed(go_bottom);
  Motor1.setVelocity(70, percent);
  Motor2.setVelocity(70, percent);
}
