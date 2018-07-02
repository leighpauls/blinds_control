

int UP_COMMAND_INPUT = 12;
int DOWN_COMMAND_INPUT = 13;

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
  8, 9, 0, 1, NEUTRAL_DIRECTION,
};

BlindInfo leftMiddleBlind = {
  10, 11, 2, 3, NEUTRAL_DIRECTION,
};

void setupBlind(BlindInfo* blind) {
  pinMode(blind->upMotor, OUTPUT);
  pinMode(blind->downMotor, OUTPUT);
  digitalWrite(blind->upMotor, LOW);
  digitalWrite(blind->downMotor, LOW);
  
  pinMode(blind->topSensor, INPUT);
  pinMode(blind->bottomSensor, INPUT);
}

void updateBlind(BlindInfo* blind) {

  if (digitalRead(UP_COMMAND_INPUT) == HIGH) {
    blind->desiredDirection = UP_DIRECTION;
  } else if (digitalRead(DOWN_COMMAND_INPUT) == HIGH) {
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

  pinMode(UP_COMMAND_INPUT, INPUT);
  pinMode(DOWN_COMMAND_INPUT, INPUT);

  setupBlind(&leftBlind);
  setupBlind(&leftMiddleBlind);
}

void loop() {
  updateBlind(&leftBlind);
  updateBlind(&leftMiddleBlind);
}

