### Kernel

## 2R-Kernel
O kernel do projeto será um microprocessador Raspberry-Pi que será intermediador das informações trocas pelo sistema.
Para que os dados transitem e sejam trabalhados pelo dispositivo kernel, o gerenciamento de todo o processo ocorre com o uso do protocolo de comunicação MQTT. Nesse contexto a título de simplificação o Raspberry-Pi aplicado como kernel será visto dentro do protocolo MQTT, como um Broker e os dispositivos em comunicação poderão fazer publicações e leituras referentes a transmissão de dados pelo Kernel. 

## MQTT
O MQTT(Message Queuing Telemetry Transport) é um protocolo de comunicação via troca de mensagens classificado em M2M(machine to machine). Ele será aplicado ao projeto por questões de viabilidade, pois é levado em conta a sua necessidade de pouquissíma banda, a sua base em TCP/IP e por possuir um payload que carrega a mensagem menor que HTTP.

As mensagens enviadas ao Broker são publicações por parte dos clientes. Assim como o kernel, que nessa situação é o broker, vai encaminhar dados e está fazendo publicações.
Entretando a parte do Kernel funciona de maneira mais interessante pelo fato de não só publicar, mas também subscrever, isso ocorre, pois o broker do caso atua como mediador, recebendo informações e respondendo às mesmas. Em termos simples, o dispositivo que solicita a informação é nomeado de subscriber.(figura x).

# Publish/subscribe
O padrão publish/subscribe é uma alternativa ao tradicional modelo cliente-servidor, mas o cliente comunica diretamente com o endpoint. Todavia, Pub/Sub desacopla um cliente que envia uma mensagem particular(chamado publisher) de outro cliente(ou mais clientes), os quais estão recebendo a mensagem(chamado subscriber). Isso significa que tanto o publisher quanto o subscriber, não sabem da existência um do outro. O terceiro componente existente nesse protocolo é o broker(no projeto será o kernel). Já o broker é conhecido tanto pelo publisher quanto pelo subscriber. O broker é crucial pois é o responsável por filtrar todas as mensagens chegadas e distribui cada uma delas.

## Aplicação no projeto
O kernel farrá boa parte da comunicação com a parte de software. Serão enviadas informações recebidas das IMU's, também as recebidas acerca dos dados de potência. Todas essa informações vão ser passadas ao software para que a análise seja feita e a decisão seja tomada pelo kernel.
A escolha pelo MQTT foi com base na facilidade em utilizar um protocolo da camada de aplicação cuja velocidade de envio das mensagens serão sufientes em uma rede local. O projeto fica robusto ao utilizar um protocolo confiável e com uma certa mobilidade para o envio ordenado de mensagens. Além disso o protocolo MQTT possui um buffer suficiente para organizar as mensagens em termos de um tempo no kernel do projeto e transparecer a transição de dados em tempo real.  

A taxa de envio no kernel é de 34.4kbps. Essa é uma informação tida como base a taxa de transmissão do módulo Wifi, ESP8266.

![Celula_s^[Fonte: ]](imagens/mqtt.png){#fig:Modelo broker MQTT}

![Celula_s^[Fonte: ]](imagens/teste_mqtt.png){#fig:Envio de dados da IMU pela ESP8266 por MQTT}

