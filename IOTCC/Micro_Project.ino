int sensor_pin = A0;     
int pump_pin = 9;         
int output_value = 0;
int moisture_level = 0;   

void setup() {
  pinMode(pump_pin, OUTPUT);
  Serial.begin(9600);
  Serial.println("Reading from the Moisture sensor...");
  delay(2000);
}

void loop() {
  output_value = analogRead(sensor_pin);  

  // Convert raw sensor value to moisture percentage
  // Assuming 1023 = completely dry (0% moisture), 0 = fully wet (100% moisture)
  moisture_level = map(output_value, 1023, 0, 0, 100);
  moisture_level = constrain(moisture_level, 0, 100);  // Keep within 0-100%

  // Print raw value and moisture percentage for calibration
  Serial.print("Raw Sensor Value: ");
  Serial.print(output_value);
  Serial.print("  |  Moisture Level: ");
  Serial.print(moisture_level);
  Serial.println("%");

  // You can calibrate these thresholds based on your soil:
  // Dry ~> 550-1023, Wet ~< 300-500 (depends on your sensor and soil)
  if (output_value > 550) {
    // Soil is dry – start watering
    digitalWrite(pump_pin, LOW);  // Assuming LOW activates pump
    Serial.println("Soil is dry – Watering ON");
  } else {
    // Soil is wet – stop watering
    digitalWrite(pump_pin, HIGH); // Assuming HIGH deactivates pump
    Serial.println("Soil is wet – Watering OFF");
  }

  delay(1000);  // Delay between readings
}
