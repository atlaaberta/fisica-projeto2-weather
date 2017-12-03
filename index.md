## Materiais

### Software

Descrição | Versão
------------ | -------------
[Arduino IDE](https://www.arduino.cc/)  |   1.8.5
[Thinkspeak](https://thingspeak.com/)   |   -
[Ionic](https://ionicframework.com/)    |   2 

#### Bibliotecas

Antes de realizar a instalação das bibliotecas é necessário adicionar um novo repositório de busca na IDE do Arduino. Isso pode ser feito adicionando o endereço `http://arduino.esp8266.com/stable/package_esp8266com_index.json` ao campo **URLs adicionais para Gerenciadores de Placas** localizado em **Arquivo > Preferências**. Dessa forma, o gerenciador de biblioteca da IDE do Arduino é capaz de localizar e instalar todas as bibliotecas necessárias para o projeto.

Para que o programa seja compilado e gravado no ESP de maneira correta é necessário realizar a instalação das seguintes bibliotecas:

Descrição | Versão
------------ | -------------
ESP8266*  |   1.0.0
DHT Sensor Library | 1.3.0

### Hardware

Qtd | Descrição | Preço Médio
------------ | ------------- | -------------
1   |   [ESP8266 nodemcu](https://www.filipeflop.com/blog/esp8266-nodemcu-como-programar/)  | R$ 28,00
1   |   Protoboard | R$ 4,00
1   |   [Sensor de temperatura e umidade DHT11](https://akizukidenshi.com/download/ds/aosong/DHT11.pdf) | R$ 7,00
1   |   Sensor de umidade do Solo YL-69 | R$ 8,00
1   |   Sensor de luminosidade LDR | R$ 4,00 (10un)

> Mais sensores podem ser adicionados e monitorados através da configuração do ESP e da adição de novos campos na API do [*Thinkspeak*](https://thingspeak.com).

#### Esquema de montagem

A imagem abaixo mostra o esquema de montagem utilizado no projeto.



