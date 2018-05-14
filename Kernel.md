### Kernel

## 2R-Kernel
O kernel do projeto será um microprocessador Raspberry-Pi que será intermediador das informações trocas pelo sistema.
Para que os dados transitem e sejam trabalhados pelo dispositivo kernel, o gerenciamento de todo o processo ocorre com o uso do protocolo de comunicação MQTT. Nesse contexto a título de simplificação o Raspberry-Pi aplicado como kernel será visto dentro do protocolo MQTT, como um Broker e os dispositivos em comunicação poderão fazer publicações e leituras referentes a transmissão de dados pelo Kernel. 

## MQTT
O MQTT(Message Queuing Telemetry Transport) é um protocolo de comunicação via troca de mensagens classificado em M2M(machine to machine). Ele será aplicado ao projeto por questões de viabilidade, pois é levado em conta a sua necessidade de pouquissíma banda, a sua base em TCP/IP e por possuir um payload que carrega a mensagem menor que HTTP.

As mensagens enviadas ao Broker são publicações por parte dos clientes. Assim como o kernel, que nessa situação é o broker, vai encaminhar dados e está fazendo publicações.
Entretando a parte do Kernel funciona de maneira mais interessante pelo fato de não só publicar, mas também subscrever, isso ocorre, pois o broker do caso atua como mediador, recebendo informações e respondendo às mesmas. Em termos simples, o dispositivo que solicita a informação é nomeado de subscriber.(figura x).

## Aplicação no projeto
O kernel farrá boa parte da comunicação com a parte de software. Serão enviadas informações recebidas das IMU's, também as recebidas acerca dos dados de potência. Todas essa informações vão ser passadas ao software para que a análise seja feita e a decisão seja tomada pelo kernel.

A taxa de envio no kernel é de 34.4kbps. Essa é uma informação tida como base a taxa de transmissão do módulo Wifi, ESP8266.
