void button_handler(system_event_t event, int duration, void*) {
      if (!duration) {
          Mesh.publish("toggle-led");
          digitalWrite(D7, HIGH);
      }  else {
          digitalWrite(D7, LOW);
      }
}

void setup() {
    pinMode(D7, OUTPUT);
    
    System.on(button_status, button_handler);
}

void loop() {

}