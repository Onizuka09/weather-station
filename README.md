# weather station 

This is a system that takes temperture and humidty readings from a DHT22 sesnor and then sends the data to a web server to diplay it a chart over WiFi.

the system is consists of 3 phases:
- Data aquision (STM32). 
- Data transfer (ESP8266).
- Displaying data (server).  
![image](images/pic1.jpg)
## 1- Data aquisition: 
In this pahse I used an ```STM32F4-nucleo board``` to get the readings from DHT22 sensor. 

Then transfroms the data to json-format
 sends and sends it to ```ESP8266``` over ```UART```. 
 
![image](images/pic2.jpg)
## 2- Data transfer:
The ESP8266 gets the data from ```STM32``` over ```UART```. 
 After some data processing (deseriallization) the ```ESP8266``` formats the data to json and then sends it via ```WiFi``` using ```socketIO``` protocole to a local ```Flask-socketIO``` server hosted on my laptop.   
 
![image](images/pic3.jpg) 
## 3- Displaying data:
the server recieves the data and then forword it using ```socketIO``` to a web_page to display the data using ```chartJS``` .

![image](images/pic4.png) 
![image](images/pic5.png)
# List of materials 
- STM32F401RE NUCLEO  
- ESP8266 
- DHT22 sensor


# Installation 
- Clone the repository 
```bash 
git clone https://github.com/Onizuka09/weather-station.git
``` 

- To run the python server you can:
 1- Activate the virtual environment (Linux)
```bash 
 $source env/bin/activate     
```    
 2- There is a requirements file you can install the python packages manually.     
