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

PATIENT > PARTICULATE FILTER > WATER TRAP > HIDROPHOBIC FILTER > SENSOR > PUMP

#### Mask
[Oxigen mask](https://tienda.fisaude.com/mascarilla-adulto-con-siete-concentraciones-p-40206.html) is used for testing.

#### Tubes
We mainly use 6mm ID tube for all breath line, and 8mm ID tube to adapt to filter and pump inlets and outlets.

#### Water trap
A water trap is needed for remove as much of water vapour as posible because it will affect the correct functioning of the sensor. We don´t find a easy to buy water trap in Spain. If you know let us know! We think about make a DIY one with a glass jar.

#### Particulate & hidrophobic filter
Seems that first is needed a particulate filter of 150 micron and after the water trap a hidrophobic filter of 0.22 micron.
For this prototype we don't found a particulate filter, but we found this 1 micron EPTFE hidrophobic membrane [filter](https://tienda.fisaude.com/filtro-antibacteriano-hidrofobico-para-aspiradores-secreciones-conector-8mm-p-37398.html) [(specs)](http://www.medicalfiltrationsolutions.com/wp-content/uploads/2015/09/MFS-TDS-0033_M03.1.003.pdf). With the first test without water trap we found that almost all water vapor was removed by the filter but better filtration may be necessary.

#### CO2 sensor
SprintIR-R-20 is the sensor used. More info at [CO2 sensors documentation](HW_co2sensors.md).

#### PUMP
It's recomended a suction air pump with 500ml/min flow, but we only found the [ROB-10398 Sparkfun air pump](https://www.tme.eu/es/details/sf-rob-10398/motores-de-cc/sparkfun-electronics-inc/rob-10398/) as fast shipping alternative to aliexpress cheap micro pumps. It has 12-15l/min but we use lower than nominal voltage to use less flow.
