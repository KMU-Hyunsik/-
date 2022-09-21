#define PIN_LED 7
unsigned int count, toggle;

void setup() {
  pinMode(PIN_LED, OUTPUT);
  Serial.begin(115200);
  while (!Serial) {
    ; //
  }
  Serial.println("Hello World!");
  count = toggle =0;
  digitalWrite(PIN_LED, toggle); //
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(++count);
  toggle = toggle_state(count); // toggle LED value.
  digitalWrite(PIN_LED, toggle); //
  delay(1000); //
  if(count == 12) {
    while(1)  {}
  }

}

int toggle_state(int a)  {
  if(a % 2 == 1)  {
    return 0;
  }
  if(a % 2 == 0)  {
    return 1;
  }
}