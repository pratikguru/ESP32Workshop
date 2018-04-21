
void setup() {
  Serial.begin(115200);
  Serial.println("\n\n");
  Serial.println("Ready....");
}

void loop() {
  int size_ = 0;
  char payload[256];
  String string = "";
  if(size_ = Serial.available()) {
    for(int i = 0 ; i < size_; i++) {
      payload[i] = Serial.read();
      string += payload[i];
      Serial.print(payload[i]);
    }
    Serial.println();
    Serial.println("Bytes: " + String(size_));
    Serial.println("------------------------------");

    if(payload[0] == 'x') {
    Serial.println("Secret ASCII char detected");
    return;
     } 
  }
  while(!Serial.available()) {
    
  }

}

