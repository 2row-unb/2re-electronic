## Bateria
### Cálculos para bateria utilizada para suprir a ESP8266 com a IMU9250
Para os cálculos foram considerados o uso momenâneo com bateria recarregavel para o projeto. 
Isso é suficiente pois a IMU escolhida é considerada de consumo super baixo e a ESP8266 também.

Segundo informações do Datasheet da IMU, o consumo por sensor embutido é:
3,2mA para o giroscópio
450uA para o acelerômetro
280uA para o magnetômetro
totalizando 3,93mA de consumo

A ESP8266 consome, com o WIFI ligado e clock máximo 215mA

O total de consumo para envio das mensagens usando MQTT por UDP é de:
215mA+3,93mA, totalizando 219mAh. Portanto a bateria escolhida de 5V e 5Ah era suficiente para o projeto.
A alta capacidade da bateria que ficou alocada em bolsão nas costas do atleta possibilitou vários testes até o correto funcionamento do aparelho por tempo suficiente para validação.
