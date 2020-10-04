#include <Motor.h>

/* ========== Private =========== */

/** @brief Adjust Steps */
void MotorClass::adjustSteps() {
  if (stepCount > MOTOR_STEP_REV) {
    stepCount += (-1 * MOTOR_STEP_REV);
  } else if (stepCount < (-1 * MOTOR_STEP_REV)) {
    stepCount += MOTOR_STEP_REV;
  }
}

/** @brief            Move the Motor
 *  @param[in] state  Number of Steps
 */
void MotorClass::step(int steps) {
  /* Prevent the motor from turning more than a revolution per command */
  if (steps > MOTOR_STEP_REV) {
    Debug.warn("Motor is trying to move more than a rev per time!");
    /* Defines Step as 1 Revolution */
    steps = MOTOR_STEP_REV;
    /* Moves a full Revolution */
    stepperMotor.step(steps);
    return;
  } else if (steps < (-1 * MOTOR_STEP_REV)) {
    Debug.warn("Motor is trying to move more than a rev per time!");
    steps = (-1 * MOTOR_STEP_REV);
    stepperMotor.step(steps);
  }

  /* Moves */
  stepperMotor.step(steps);
  /* Updates StepCount */
  stepCount += steps;
  /* Adjust Step Count */
  adjustSteps();
}

/** @brief Gets back to rest position */
void MotorClass::backToRest(){
  step(-1 * stepCount);
}

/** @brief Place motor in card position */
void MotorClass::cardPosition() {
  step(MOTOR_STEP_REV / 4);
}

/* ============ Public ========== */

/** @brief Set Motor Speed */
void MotorClass::setup() {
  /* Set Motor Speed */
  stepperMotor.setSpeed(MOTOR_SPEED);
}

/** @brief spits a card */
void MotorClass::spitCard() {
  /* Spits a perfume card */
  cardPosition();
  delay(2000);
  backToRest();
}

MotorClass Motor;