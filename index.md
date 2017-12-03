## Objetivo

O objetivo desse trabalho é apresentar um sistema de monitoramento de variáveis de ambiente utilizando dipositivos e plataformas com suporte a IoT.

### Motivação

O monitoramento de variáveis de ambiente é algo presente em diversas áreas, desde ao monitoramento para automação até a um controle mais preciso prar fins de pesquisa científica.

Com a disseminação do IoT agora é possivel que exista um monitoramento e tomada de decisões em um tempo bem menor ou até mesmo em tempo real. 

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

#### Preparação da API Thinkspeak

Para o armazenamento e comunicação com os dispositivos, foi utilizado o serviço ***ThinkSpeak***, uma plataforma aberta para IoT, que permite a criação de API para comunicação entre dispositivos através da nuvem. Para fazer uso da plataforma ***ThinkSpeak*** é necessário registrar-se no [link](https://thingspeak.com).

Após realizado o cadastro no ***ThinkSpeak*** são necessários os seguintes passos para criação de uma API para sua aplicação:

1. Crie uma nova aplicação do tipo **ThingHTTP** nesse [link](https://thingspeak.com/apps), para criação de POST ou GET personalizados para o seu webservice.
2. Crie um novo canal nesse [link](https://thingspeak.com/channels), para configurar e habilitar os campos existentes nas suas requisições.
3. Teste as requisições de acordo com o formato indicado após a criação do canal.

### Hardware

Qtd | Descrição | Preço Médio
------------ | ------------- | -------------
1   |   [ESP8266 nodemcu](https://www.filipeflop.com/blog/esp8266-nodemcu-como-programar/)  | R$ 28,00
1   |   Protoboard | R$ 4,00
1   |   [Sensor de temperatura e umidade DHT11](https://akizukidenshi.com/download/ds/aosong/DHT11.pdf) | R$ 7,00
1   |   Sensor de umidade do Solo YL-69 + YL-38| R$ 8,00
1   |   Sensor de luminosidade LDR | R$ 4,00 (10un)
1   |   Resistor de 10k ohms       | R$ 0,50
2   |   Diodos (?)                 | R$ 0,70

> Mais sensores podem ser adicionados e monitorados através da configuração do ESP e da adição de novos campos na API do [*Thinkspeak*](https://thingspeak.com).

#### Esquema de montagem

A imagem abaixo mostra o esquema de montagem utilizado no projeto.

![Esquema de montagem](documentacao/res/montagem_fritz_bb.png)

## Passos para Execução

Uma vez instalado o programa, juntamente com as depencias de bibliotecas, basta clicar em **Comilar e executar** para que o código seja compilado e inserido no **NodeMCU**.

## Passos para Adição de outros sensores


## Problemas e Soluções

#### Problemas com protocolo HTTPS?

#### Problemas com precisão dos sensores?

