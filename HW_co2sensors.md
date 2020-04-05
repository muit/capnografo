# CO2 sensors
The CO2 sensors for this project need some caracteristics to work:
* Be able to measure directly the CO2 concentration. Non dispersive infrared sensors (NDIR) works. Metal Oxide sensors (MOS) don´t work because they only "estimate" the CO2 concentration.
* Have MORE than 5% CO2 concentration measure range (MORE than 50000ppm)
* Response time less than 1s at 500ml/min air flow
* Sample time equal or less than 0.1s (10Hz)

## Sensor choice for BricoLabs prototype
For this prototype we choose the **SprintIR-R-20** for these reasons:
* Is the top of the line at sample speed (50 samples/s). Maybe slower versions (SprintIR-WF or SprintIR-6S) with 20Hz also work, but we have one shot ;)
* Has a good range for this application (20%)
* It has compact size and tube input & output
* Is digital, with serial communication

## Other valid sensors
At capnograph project many members are trying to make another prototype with Pyreos epy12231 I2C sensor. Other group are working with Pyreos PY2343 analog sensor. Both groups are developing PCBs, and air conducts. 
See the slack channels: [#sensor-epy12231](https://bit.ly/2QETJuY) and [#py2343_sensor](https://bit.ly/2QETJuY)

## Checked Sensors
At this table we show the found sensors and their caracteristics. If you know a unlisted VALID sensor please add it here!

| Model           | Range | Samples/s | Warm | Response | Accuracy | Valid? | Price | Datasheet |
| --------------- |:-----:|:---------:|:----:|:--------:|:--------:|:------:|:-----:|:---------:| 
| SprintIR-W-5    | 5%    | 0.05s     | <30s | 3s       | 70ppm+5% | NO     | ?     | [data](https://docs.rs-online.com/ece4/0900766b8168eabd.pdf) |
| SprintIR-WF-20  | 20%   | 0.05s     | <30s | 3s       | 70ppm+5% | maybe  | 270€  | [data](https://docs.rs-online.com/ece4/0900766b8168eabd.pdf) |
| SprintIR-W-20   | 20%   | 0.05s     | <30s | 3s       | 70ppm+5% | maybe  | 138€  | [data](https://docs.rs-online.com/ece4/0900766b8168eabd.pdf) |
| SprintIR-W-60   | 60%   | 0.05s     | <30s | 3s       | 70ppm+5% | maybe  | 138€  | [data](https://docs.rs-online.com/ece4/0900766b8168eabd.pdf) |
| SprintIR-W-100  | 100%  | 0.05s     | <30s | 3s       | 70ppm+5% | maybe  | 138€  | [data](https://docs.rs-online.com/ece4/0900766b8168eabd.pdf) |
| SprintIR-6S-5   | 5%    | 0.05s     | <30s | <1s      | 70ppm+5% | NO     | 231€  | [data](https://www.gassensing.co.uk/wp-content/uploads/2020/03/SprintIR-6S-Product-Flyers.pdf) |
| SprintIR-6S-20  | 20%   | 0.05s     | <30s | <1s      | 70ppm+5% | YES    | 231€  | [data](https://www.gassensing.co.uk/wp-content/uploads/2020/03/SprintIR-6S-Product-Flyers.pdf) |
| SprintIR-6S-60  | 60%   | 0.05s     | <30s | <1s      | 70ppm+5% | YES    | 231€  | [data](https://www.gassensing.co.uk/wp-content/uploads/2020/03/SprintIR-6S-Product-Flyers.pdf) |
| SprintIR-6S-100 | 100%  | 0.05s     | <30s | <1s      | 70ppm+5% | YES    | 231€  | [data](https://www.gassensing.co.uk/wp-content/uploads/2020/03/SprintIR-6S-Product-Flyers.pdf) |
| SprintIR-R-5    | 5%    | 0.02s     | ?    | <1s      | 70ppm+5% | NO     | 370€  | [data](http://co2meters.com/Documentation/Datasheets/DataSheet_GC0033_100.pdf) |
| SprintIR-R-20   | 20%   | 0.02s     | ?    | <1s      | 70ppm+5% | YES    | 370€  | [data](http://co2meters.com/Documentation/Datasheets/DataSheet_GC0033_100.pdf) |
| SprintIR-R-60   | 60%   | 0.02s     | ?    | <1s      | 70ppm+5% | YES    | 370€  | [data](http://co2meters.com/Documentation/Datasheets/DataSheet_GC0033_100.pdf) |
| SprintIR-R-100  | 100%  | 0.02s     | ?    | <1s      | 70ppm+5% | YES    | 370€  | [data](http://co2meters.com/Documentation/Datasheets/DataSheet_GC0033_100.pdf) |
| ExploIR-W-5     | 5%    | 0.5s      | <10s | 10s      | 70ppm+5% | NO     | 101€  | [data](https://docs.rs-online.com/4cdd/0900766b8168eabb.pdf) |
| ExploIR-W-20    | 20%   | 0.5s      | <10s | 10s      | 70ppm+5% | NO     | 101€  | [data](https://docs.rs-online.com/4cdd/0900766b8168eabb.pdf) |
| ExploIR-W-60    | 60%   | 0.5s      | <10s | 10s      | 70ppm+5% | NO     | 101€  | [data](https://docs.rs-online.com/4cdd/0900766b8168eabb.pdf) |
| ExploIR-W-100   | 100%  | 0.5s      | <10s | 10s      | 70ppm+5% | NO     | 101€  | [data](https://docs.rs-online.com/4cdd/0900766b8168eabb.pdf) |
| ExploIR-M-20    | 20%   | 0.5s      | <10s | 10s      | 70ppm+5% | NO     | 222€  | [data](https://www.gassensing.co.uk/wp-content/uploads/2018/10/ExplorIR-M-CO2-sensor-datasheet.pdf) |
| ePY12231        | ?     | 0.001s    | ?    | ?        | ?        | maybe? | 30€   | [data](https://www.mouser.es/datasheet/2/948/ezpyro_ir_sensor_for_gas_sensing_short_form_datash-1483387.pdf) |
| PY2343          | ?     | ?         | ?    | ?        | ?        | maybe? | 60€   | [data](https://www.mouser.es/datasheet/2/948/pyreos_ir_sensor_for_gas_sensing_-_two_channel-1483382.pdf) |
| K30             | 0.5%  | 0.5s      | 60s  | 20s      | 30ppm+3% | NO     | 79€   | [data](https://rmtplusstoragesenseair.blob.core.windows.net/docs/publicerat/PSP109.pdf) |
| MH-Z19          | 0.5%  | 5s        | 180s | <60s     | 50ppm+5% | NO     | 27€   | [data](https://www.winsen-sensor.com/d/files/PDF/Infrared%20Gas%20Sensor/NDIR%20CO2%20SENSOR/MH-Z19%20CO2%20Ver1.0.pdf) |
| MH-Z14A         | 1%    | ?         | 189s | <120s    | 10%      | NO     | 37€   | [data](https://www.winsen-sensor.com/d/files/infrared-gas-sensor/mh-z14a_co2-manual-v1_01.pdf) |
| LI-820          | 2%    | ?         | 90m  | ?        | ?        | NO     | ?     | [data](https://www.licor.com/documents/srqy9vep2nocnnei7ksb) |
| DS-CO2-20       | 0.5%  | ?         | ?    | ?        | ?        | NO     | 27€   | [data](https://datasheet.lcsc.com/szlcsc/1811151534_Beijing-Plantower-DS-CO2-20_C86424.pdf) |
| SGP-30          | MOS   | 1s        | ?    | ?        | ?        | NO     | 20€   | [data](https://www.mouser.de/datasheet/2/682/Sensirion_Gas_Sensors_SGP30_Datasheet-1511334.pdf) |
| MQ-135          | MOS   | ?         | ?    | ?        | ?        | NO     | 6€    | [data](https://www.olimex.com/Products/Components/Sensors/Gas/SNS-MQ135/resources/SNS-MQ135.pdf) |
| CCS811          | MOS   | 1s        | ?    | ?        | ?        | NO     | 21€   | [data](https://cdn.sparkfun.com/assets/learn_tutorials/1/4/3/CCS811_Datasheet-DS000459.pdf) |
| ADD!            | ?     | ?         | ?    | ?        | ?        | YES     | ?   | [data]() |

Not all sensors have tube adaptors but maybe you can 3D print one!
