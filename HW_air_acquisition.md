# Air acquisition
There are two methods to access to the breath of the patient to measure the CO2 concentration:
* Main-stream
* Side-sream

## Main stream
In this method de CO2 sensor is located between the patient and the breathing circuit. 
The sensor "sees" trough some transparent windows in a special airwave adapter the light of an infrared emiter located in the other side.
To prevent water condensation the air is heated slighty above of the body temperature.  

Advantages  
* No obstruction
* Don´t make pressure drop
* Normally dont have problems with sterilization because the sensor don't have contact with the breath
* No pollution
* No delay in the graph
* Suitable for children  

Disadvantages  
* Sensor windows can clog with secretions
* Dificult to use in unusual positions like prone
* Some one piece units are heavy
* Only can be used with intubated patients
* **Hard to DIY the airwave adapter and windows**

### Prototype epy12231
Some capnograph project members are trying to use this method with epy12231 and py2343 sensors.  
See the slack channels: [#sensor-epy12231](https://bit.ly/2QETJuY) and [#py2343_sensor](https://bit.ly/2QETJuY)


## Side stream
This method uses a sampling tube connected to a T-piece. The CO2 sensor is located at the main unit and a small pump aspirates a small gas sample to measure.
If the patient has a disease that can be spread by breathing like COVID-19 or has anesthesic gases, the exhausted gas from the capnograph unit must be returned to the patients breathing system or be routed to a gas scavenger.  

Advantages  
* Easy to connect
* Can be used in awake and no-intubed patients
* Easy to use whith unusual patient positions like prone  

Disadvantages  
* Sampling tube obstruction
* Water vapor may change CO2 readings if gets to the sensor
* Some delay in the graph due gass transportation

### "BricoLabs" prototype
This prototype uses the side stream method to measure the CO2 concentration.

PATIENT > TUBE > WATER TRAP > TUBE > PARTICULATE FILTER > TUBE > SENSOR > TUBE > PUMP

#### Mask
[Oxigen mask](https://tienda.fisaude.com/mascarilla-adulto-con-siete-concentraciones-p-40206.html) is used for testing.

#### Tubes
We mainly use 6mm ID tube for all breath line, and 8mm ID tube to adapt to filter and pump inlets and outlets.

#### Water trap
We don´t find a easy to buy water trap in Spain. If you know let us know! We think about make a DIY one with a glass jar.

#### Particulate filter

#### CO2 sensor

#### PUMP


