# Materiais

### Software

Descrição | Versão
------------ | -------------
[Arduino IDE](https://www.arduino.cc/)  |   1.8.5
[Thinkspeak](https://thingspeak.com/)   |   -
[Ionic](https://ionicframework.com/)    |   2 

#### Bibliotecas

Antes de relizar a instalação das bibliotecas é necessário adicionar um novo repositório de busca na IDE do Arduino. Isso pode ser feito adicionando o endereço `http://arduino.esp8266.com/stable/package_esp8266com_index.json` ao campo **URLs adicionais para Gerenciadores de Placas**. Dessa forma, o gerenciador de biblioteca da IDE do Arduino é capaz de localizar e instalar todas as bibliotecas necessárias para o projeto.

Para que o pograma seja compilado e gravado no ESP de maneira correta é necessária realizar a instalão das bibliotecas:

Descrição | Versão
------------ | -------------
ESP8266*  |   1.0.0
DHT Sensor Library | 1.3.0

### Hardware

Qtd | Descrição
------------ | -------------
1   |   [Arduino UNO](https://www.arduino.cc/)
1   |   [Protoboard](https://www.google.com.br/)
1   |   [Sensor de temperatura e umidade DHT22](https://www.sparkfun.com/datasheets/Sensors/Temperature/DHT22.pdf)
1   |   [Sensor de umidade do Solo](http://www.google.com.br/)
1   |   [Sensor de luminosidade](http://www.google.com.br/)

> Mais sensores podem ser adicionados e monitorados através da configuração do arduino e da adição de novos campos na API do Thinkspeak


