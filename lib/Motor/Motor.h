#ifndef PUMP_H
#define PUMP_H

#include <Arduino.h>
#include <Debug.h>
#include <Stepper.h>
#include <DataSet.h>

#define MOTOR_PIN_ONE 1
#define MOTOR_PIN_TWO 2
#define MOTOR_PIN_THREE 3

#ifndef CARD_AMOUNT
#define CARD_AMOUNT 100
#endif

#ifndef MOTOR_STEP_REV
#define MOTOR_STEP_REV 200
#endif

#ifndef MOTOR_SPEED
#define MOTOR_SPEED 60
#endif

extern eugenio_info_t EugenioData;

class MotorClass {
 public:
  static void update();
  static void selectPerfume(int motorNumber);
  static void setupAll();

 private:
  /* Instances */
  Stepper stepperMotor;
  DebugClass Debug;

  /* Varaibles */
  int stepCount;
  int cardAmount;

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
  MotorClass(int motorPin, int cardAmount) : stepperMotor(MOTOR_STEP_REV, 0, motorPin),
                                             Debug("Motor"),
                                             stepCount(0),
                                             cardAmount(cardAmount){};

  /** @brief Set Motor Speed */
  void setup();

  /** @brief spits a card */
  void spitCard();

  /** @brief    Get Pimp State
   *  @returns  Pump State
   */
  bool getState() const { return stepCount; }
};

extern MotorClass MotorFirst;
extern MotorClass MotorSecond;
extern MotorClass MotorThird;

#endif