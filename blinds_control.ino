

int UP_COMMAND_INPUT = A1;
int DOWN_COMMAND_INPUT = A0;
int BLINK_OUTPUT = 13;

int NEUTRAL_DIRECTION = 0;
int UP_DIRECTION = 1;
int DOWN_DIRECTION = 2;

typedef struct BlindInfo {
  int upMotor;
  int downMotor;
  int topSensor;
  int bottomSensor;

  int desiredDirection;
} BlindInfo;

void setupBlind(BlindInfo* blind);
void updateBlind(BlindInfo* blind);

BlindInfo leftBlind = {
  1, 0, 4, 5, NEUTRAL_DIRECTION,
};

BlindInfo leftMiddleBlind = {
  3, 2, 6, 7, NEUTRAL_DIRECTION,
};

BlindInfo rightMiddleBlind = {
  A3, A2, 8, 9, NEUTRAL_DIRECTION,
};

BlindInfo rightBlind = {
  A5, A4, 10, 11, NEUTRAL_DIRECTION,
};

void setupBlind(BlindInfo* blind) {
  pinMode(blind->upMotor, OUTPUT);
  pinMode(blind->downMotor, OUTPUT);
  digitalWrite(blind->upMotor, LOW);
  digitalWrite(blind->downMotor, LOW);
  
  pinMode(blind->topSensor, INPUT_PULLUP);
  pinMode(blind->bottomSensor, INPUT_PULLUP);
}

void updateBlind(BlindInfo* blind) {
  if (digitalRead(UP_COMMAND_INPUT) == LOW) {
    blind->desiredDirection = UP_DIRECTION;
  } else if (digitalRead(DOWN_COMMAND_INPUT) == LOW) {
    blind->desiredDirection = DOWN_DIRECTION;
  }

  int newDirection;
  if (blind->desiredDirection == UP_DIRECTION) {
    if (digitalRead(blind->topSensor) == LOW) {
      blind->desiredDirection = NEUTRAL_DIRECTION;
    } else {
      newDirection = UP_DIRECTION;
    }
  } else if (blind->desiredDirection == DOWN_DIRECTION) {
    if (digitalRead(blind->bottomSensor) == LOW) {
      blind->desiredDirection = NEUTRAL_DIRECTION;
    } else {
      newDirection = DOWN_DIRECTION;
    }
  }
  // Fall-through from the above cases
  if (blind->desiredDirection == NEUTRAL_DIRECTION) {
    newDirection = NEUTRAL_DIRECTION;
  }

  digitalWrite(
    blind->upMotor,
    (newDirection == UP_DIRECTION) ? HIGH : LOW);
  digitalWrite(
    blind->downMotor,
    (newDirection == DOWN_DIRECTION) ? HIGH : LOW);
}

void setup() {
  delay(1000);
  pinMode(UP_COMMAND_INPUT, INPUT_PULLUP);
  pinMode(DOWN_COMMAND_INPUT, INPUT_PULLUP);
  pinMode(BLINK_OUTPUT, OUTPUT);

  setupBlind(&leftBlind);
  setupBlind(&leftMiddleBlind);
  setupBlind(&rightBlind);
  setupBlind(&rightMiddleBlind);
}

void loop() {
  updateBlind(&leftBlind);
  updateBlind(&leftMiddleBlind);
  updateBlind(&rightBlind);
  updateBlind(&rightMiddleBlind);
  digitalWrite(BLINK_OUTPUT, ((millis()/500) % 2) ? LOW : HIGH);
  delay(20);
}

