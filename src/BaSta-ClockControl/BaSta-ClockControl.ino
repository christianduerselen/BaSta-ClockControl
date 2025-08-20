const int GameClockRunningSwitchPin = 5;
const int HornButtonPin = 6;
const int PrecisionTimeStatusSwitchPin = 7;
const int ShotClock24SecondResetButtonPin = 8;
const int ShotClock14SecondResetButtonPin = 9;
const int ShotClockRunningSwitchPin = 10;

const int Baudrate = 57600;

void setup()
{
  // Configure the relevant pins as inputs
  pinMode(GameClockRunningSwitchPin, INPUT);
  pinMode(HornButtonPin, INPUT);
  pinMode(PrecisionTimeStatusSwitchPin, INPUT);
  pinMode(ShotClock24SecondResetButtonPin, INPUT);
  pinMode(ShotClock14SecondResetButtonPin, INPUT);
  pinMode(ShotClockRunningSwitchPin, INPUT);

  // Configure serial send (through RX/TX)
  Serial.begin(Baudrate);
}

void loop()
{
  bool gameClockRunningSwitchState = digitalRead(GameClockRunningSwitchPin);
  bool hornButtonState = digitalRead(HornButtonPin);
  bool precisionTimeStatusSwitchState = digitalRead(PrecisionTimeStatusSwitchPin);
  bool shotClock24SecondResetButtonState = digitalRead(ShotClock24SecondResetButtonPin);
  bool shotClock14SecondResetButtonState = digitalRead(ShotClock14SecondResetButtonPin);
  bool shotClockRunningSwitchState = digitalRead(ShotClockRunningSwitchPin);

  Serial.write(0x0D);
  Serial.write(0x30 + gameClockRunningSwitchState ? 0x01 : 0x00 + hornButtonState ? 0x02 : 0x00 + precisionTimeStatusSwitchState ? 0x04 : 0x00);
  Serial.write(0x40 + shotClock24SecondResetButtonState ? 0x01 : 0x00 + shotClock14SecondResetButtonState ? 0x02 : 0x00 + shotClockRunningSwitchState ? 0x04 : 0x00);
  Serial.write(0x50);
  Serial.write(0x60);
}