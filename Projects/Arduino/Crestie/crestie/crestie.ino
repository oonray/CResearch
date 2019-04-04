/**
 * @file crestie.ino
 * @author Alexander Bjørnsrud (alexanderbjornsrud@gmail.com)
 * @brief A tempterature controlled fan and misting system for a vivarium.
 * @version 0.1
 * @date 2019-04-04
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include <DHT.h>          //DHT Libary
#define DHTTYPE DHT11     // The sensor is a DHT 11

#define TEMPERATURE 8     // The temperature sensor pin
#define RELE 7            // The Relay pin
#define MOSFET 3          // The pin of the mosfet

DHT dht(DHTPIN, DHTTYPE); // Init

struct DHTData{
  float temp;
  float humid;
} data;

int get_temperature(DHT *dht, struct DHTData *data){
  /**
   * @brief Gets the temoerature and stores in a struct
   * @param dht a pointer to a DHT instance
   * @param data a pointer to a struct to store the data in 
   * 
   * queries the dht pointer and sets the data in the DHTdata struct
   */
    data->temp = dht->readTemperature();
    data->humid = dht->readHumidity();
    if(isnan(data->temp)|| isnan(data->humid)){
      Serial.println("Error Reading the data from the sensor!");
      return 1;
    }
    return 0;
}

void setup() {
  /**
   * @brief The setup function of the arduino
   * 
   * In this function we will start the sensors and the serial connection.
   */

  Serial.begin(9600); 
  Serial.print("Starting!\n");
  dht.begin();
  data = malloc(sizeof(struct DHTData));
}

void loop() {
  delay(2000);
  get_temperature(data);


}
