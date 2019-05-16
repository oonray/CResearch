 /**
 * @file crestie.ino
 * @author Alexander BjÃ¸rnsrud (alexanderbjornsrud@gmail.com)
 * @brief A tempterature controlled fan and misting system for a vivarium.
 * @version 0.1
 * @date 2019-04-04
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include <DHT.h>          //DHT Libary
#include <stdio.h>        // Standard Lib
#define DHTTYPE DHT11     // The sensor is a DHT 11S

#define TEMPERATURE 8     // The temperature sensor pin
#define MOSFET 3          // The pin of the mosfet

DHT dht(TEMPERATURE, DHTTYPE); // Init

int relay = LOW; //relay bool variable

struct DHTData{
  float temp;
  float humid;
} data{0.0,0.0}; //stores the data from the sensor


int check_data_temp(){
  /**
   * @brief returns a value between 0 and 255
   * @returns int 0-255
   * returns a value between 0 and 255 to be used with the PWM signal.
   */
    int temp_range = data.temp-25;
    if(temp_range <= 0.0){
      return 0.0;
      }
    return (255/5)*temp_range;  
}

int get_temperature(){
  /**
   * @brief Gets the temoerature and stores in a struct
   * @param dht a pointer to a DHT instance
   * @param data a pointer to a struct to store the data in 
   * 
   * queries the dht pointer and sets the data in the DHTdata struct
   */
    delay(2000);
    data.temp = dht.readTemperature();
    data.humid = dht.readHumidity();
    if(isnan(data.temp)|| isnan(data.humid)){
      Serial.println("Error Reading the data from the sensor!\n");
      return 1;
    }
    return 0;
}

void print_data(){
  /**
   * @brief Prints the data values stored in a DHTData
   * @param data a DHTData struct
   */ 
    Serial.print("Temperature: ");
    Serial.print(data.temp);
    Serial.print(" *C\n");

    Serial.print("Humidity: ");
    Serial.print(data.humid);
    Serial.print(" %\n");
}


void setup() {
  /**
   * @brief The setup function of the arduino
   * 
   * In this function we will start the sensors and the serial connection.
   */

  Serial.begin(9600); 
  Serial.println("Starting!");
  dht.begin();
  pinMode(MOSFET,OUTPUT);
}

void loop() {
  if(get_temperature()==0){
    print_data();
    int spd = check_data_temp();
    Serial.println((spd*100)/255);
    analogWrite(MOSFET,spd);
  }
  
  
  
  
}
