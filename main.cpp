#pragma region VEXcode Generated Robot Configuration
// Make sure all required headers are included.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>


#include "vex.h"

using namespace vex;

// Brain should be defined by default
brain Brain;


// START V5 MACROS
#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)
// END V5 MACROS


// Robot configuration code.
motor Motor1 = motor(PORT1, ratio36_1, false);

motor Motor2 = motor(PORT2, ratio36_1, false);

limit LimitSwitch_Bottom_A = limit(Brain.ThreeWirePort.A);
bumper Bumper_up1_H = bumper(Brain.ThreeWirePort.H);
bumper Bumper_AllDown_B = bumper(Brain.ThreeWirePort.B);
bumper Bumper_Floor3_C = bumper(Brain.ThreeWirePort.C);
#pragma endregion VEXcode Generated Robot Configuration

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       {author}                                                  */
/*    Created:      {date}                                                    */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

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

// void up_a_level() {
//   switch (level) {
//     case 0:
//       Motor1.spinFor(reverse, 4, turns, false);
//       Motor2.spinFor(forward, 4, turns, false);
//   }
//   Motor1.spinFor(reverse, 4, turns, false);
//   Motor2.spinFor(forward, 4, turns, false);
// }
void up_a_level() {
    Motor1.spinFor(reverse, 4, turns, false);
    Motor2.spinFor(forward, 4, turns, false);
    level+=1;
}

void down_a_level() {
    Motor1.spinFor(forward, 4, turns, false);
    Motor2.spinFor(reverse, 4, turns, false);
    level+=1;
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

void go_to_level(int destination) {
    if (destination == 0) {
      go_bottom();
    } else if (destination == 1) {
      if (level == 0) {
        up_a_level();
      } else if (level == 2) {
        down_a_level();
      }
    } else if (destination == 2) {
      if (level == 1) {
        up_a_level();
      } else if (level == 0) {
        for (int i = 0; i<2; i++) {
          up_a_level();
        }
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
  go_to_level(2);
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
  Bumper_up1_H.pressed(up_a_level);
  Bumper_AllDown_B.pressed(go_bottom);
  //Bumper_Floor3_C.pressed(go_to_level(2))
  Motor1.setVelocity(70, percent);
  Motor2.setVelocity(70, percent);
  go_bottom();
}
