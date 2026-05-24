const int GameClockRunningSwitchPin = 5;
const int HornButtonPin = 6;
const int PrecisionTimeStatusSwitchPin = 7;
const int ShotClock24SecondResetButtonPin = 8;
const int ShotClock14SecondResetButtonPin = 9;
const int ShotClockRunningSwitchPin = 10;

volatile byte state = LOW;

void setup()
{
  // Configure the relevant pins as inputs
  pinMode(GameClockRunningSwitchPin, INPUT_PULLUP);
  pinMode(HornButtonPin, INPUT_PULLUP);
  pinMode(PrecisionTimeStatusSwitchPin, INPUT_PULLUP);
  pinMode(ShotClock24SecondResetButtonPin, INPUT_PULLUP);
  pinMode(ShotClock14SecondResetButtonPin, INPUT_PULLUP);
  pinMode(ShotClockRunningSwitchPin, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(GameClockRunningSwitchPin), change, CHANGE);
  attachInterrupt(digitalPinToInterrupt(HornButtonPin), change, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PrecisionTimeStatusSwitchPin), change, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ShotClock24SecondResetButtonPin), change, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ShotClock14SecondResetButtonPin), change, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ShotClockRunningSwitchPin), change, CHANGE);

  // Configure serial send (through RX/TX)
  Serial.begin(57600);
  while (!Serial) {;}
}

void change()
{
  state = HIGH;
}

void loop()
{
  if (state == LOW)
    return;

  state = LOW;

  bool gameClockRunningSwitchState = !digitalRead(GameClockRunningSwitchPin);
  bool hornButtonState = !digitalRead(HornButtonPin);
  bool precisionTimeStatusSwitchState = !digitalRead(PrecisionTimeStatusSwitchPin);
  bool shotClock24SecondResetButtonState = !digitalRead(ShotClock24SecondResetButtonPin);
  bool shotClock14SecondResetButtonState = !digitalRead(ShotClock14SecondResetButtonPin);
  bool shotClockRunningSwitchState = !digitalRead(ShotClockRunningSwitchPin);

  Serial.write(0x0D);
  
  byte value1 = 0x30;
  if (gameClockRunningSwitchState)
    value1 += 0x01;
  if (hornButtonState)
    value1 += 0x02;
  if (precisionTimeStatusSwitchState)
    value1 += 0x04;
  Serial.write(value1);

  byte value2 = 0x40;
  if (shotClock24SecondResetButtonState)
    value2 += 0x01;
  if (shotClock14SecondResetButtonState)
    value2 += 0x02;
  if (shotClockRunningSwitchState)
    value2 += 0x04;
  Serial.write(value2);

  Serial.write(0x50);
  Serial.write(0x60);  
}