#include <Motor.h>
#include <Eugenio.h>
#include <DataSet.h>

DebugClass DebugStaticMotor("All The Motors");

/* ========== Static ============ */

void MotorClass::setupAll() {
  MotorFirst.setup();
  MotorSecond.setup();
  MotorThird.setup();
}

void MotorClass::selectPerfume(int motorNumber) {
  DebugStaticMotor.warn("MotorNumber -> %d", motorNumber);
  switch (motorNumber) {
    case 0:
      DebugStaticMotor.print("Motor One Selected");
      MotorFirst.spitCard();
      sendToEugenio();
      break;

    case 1:
      DebugStaticMotor.print("Motor Two Selected");
      MotorSecond.spitCard();
      sendToEugenio();
      break;
    case 2:
      DebugStaticMotor.print("Motor Three Selected");
      MotorThird.spitCard();
      sendToEugenio();
      break;

    default:
      DebugStaticMotor.print("Invalid Motor");
      break;
  }
}

void MotorClass::update() {
  EugenioData.perfume_one = MotorFirst.cardAmount;
  EugenioData.perfume_two = MotorSecond.cardAmount;
  EugenioData.perfume_three = MotorThird.cardAmount;
}

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
void MotorClass::backToRest() {
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
  cardAmount--;
  MotorClass::update();
}

MotorClass MotorFirst(MOTOR_PIN_ONE, CARD_AMOUNT);
MotorClass MotorSecond(MOTOR_PIN_TWO, CARD_AMOUNT);
MotorClass MotorThird(MOTOR_PIN_THREE, CARD_AMOUNT);