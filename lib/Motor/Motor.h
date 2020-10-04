#ifndef PUMP_H
#define PUMP_H

#include <Arduino.h>
#include <Debug.h>
#include <Stepper.h>

#define MOTOR_PIN_ONE 1
#define MOTOR_PIN_TWO 2
#define MOTOR_PIN_THREE 3
#define MOTOR_PIN_FOUR 4

#ifndef MOTOR_STEP_REV
#define MOTOR_STEP_REV 200
#endif

#ifndef MOTOR_SPEED
#define MOTOR_SPEED 60
#endif

class MotorClass {
 private:
  /* Instances */
  Stepper stepperMotor;
  DebugClass Debug;

  /* Varaibles */
  int stepCount;

  /* Methods */
  /** @brief            Move the Motor
   *  @param[in] state  Number of Steps
   */
  void step(int steps);

  /** @brief Adjust Steps */
  void adjustSteps();

  /** @brief Gets back to rest position */
  void backToRest();

  /** @brief Place motor in card position */
  void cardPosition();

 public:
  /* Initializer  */
  MotorClass() : stepperMotor(MOTOR_STEP_REV,
                              MOTOR_PIN_FOUR,
                              MOTOR_PIN_THREE,
                              MOTOR_PIN_TWO,
                              MOTOR_PIN_ONE),
                 Debug("Motor"),
                 stepCount(0){};

  /** @brief Set Motor Speed */
  void setup();

  /** @brief spits a card */
  void spitCard();

  /** @brief    Get Pimp State
   *  @returns  Pump State
   */
  bool getState() const {return stepCount;}
};

extern MotorClass Motor;

#endif