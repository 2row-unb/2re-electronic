

# 3.3  Solução do sistema 2RElectronic

  O sistema de eletrônica ficou responsável pelo sensoriamento, aquisição de sinais, tratamentos dos sinais e controle do acionamento das cargas. Os sinais obtidos foram das IMUs e dos botões, este último define qual a carga que deverá ser acionada. Este relatório apresenta a evolução do grupo, assim como as alterações realizadas no escopo do ponto de controle 1.
  
   
  
  ![diagrama^[Fonte:Do_autor]](imagens/diag.png){#fig:Diagrama_Geral}

## 3.3.1 2RE-Suit

  Esse subsistema continha o 2RE-Cardio e o 2RE-IMU. No entanto após a exclusão do 2RE-Cardio, que será explicado o porquê a seguir, o 2RE-Suit passou a ser a vestimenta somente com o 2RE-IMU, dessa forma a confecção ainda está em andamento e será apresentada nas próximas semanas.
  
  
  
### 2RE-Cardio

Inicialmente o 2Row contaria com um sensor para medir frequência cardíaca do atleta de remo durante o movimento, sendo o subsistema chamado de 2RE-Cardio, porém ao final do Ponto de Controle 1 foi notado juntamente com os professores que seria difícil fazer a aquisição dos sinais por alguns motivos, como: dificuldade em alocar o sensor na orelha ou nos dedos das mãos (locais apropriados para aquisição), uma vez que o atleta estará em movimento e poderia sair do lugar durante a remada, dificuldade no processamento do sinal de batimento cardíaco com as muitas interferências durante o movimento.

Portanto, após avaliar as prioridades para execução do projeto, foi decidido retirar do escopo o subsistema 2RE-Cardio, isso fez com que o escopo do 2Row ficasse mais enxuto e exequível em relação ao pouco tempo que resta para a entrega do projeto.


## Kernel

### 2R-Kernel
O kernel do projeto será um microprocessador Raspberry-Pi que será intermediador das informações trocas pelo sistema.
Para que os dados transitem e sejam trabalhados pelo dispositivo kernel, o gerenciamento de todo o processo ocorre com o uso do protocolo de comunicação MQTT. Nesse contexto a título de simplificação o Raspberry-Pi aplicado como kernel será visto dentro do protocolo MQTT, como um Broker e os dispositivos em comunicação poderão fazer publicações e leituras referentes a transmissão de dados pelo Kernel. 

## MQTT
O MQTT(Message Queuing Telemetry Transport) é um protocolo de comunicação via troca de mensagens classificado em M2M(machine to machine). Ele será aplicado ao projeto por questões de viabilidade, pois é levado em conta a sua necessidade de pouquissíma banda, a sua base em TCP/IP e por possuir um payload que carrega a mensagem menor que HTTP.

As mensagens enviadas ao Broker são publicações por parte dos clientes. Assim como o kernel, que nessa situação é o broker, vai encaminhar dados e está fazendo publicações.
Entretando a parte do Kernel funciona de maneira mais interessante pelo fato de não só publicar, mas também subscrever, isso ocorre, pois o broker do caso atua como mediador, recebendo informações e respondendo às mesmas. Em termos simples, o dispositivo que solicita a informação é nomeado de subscriber.(figura x).

### Publish/subscribe
O padrão publish/subscribe é uma alternativa ao tradicional modelo cliente-servidor, mas o cliente comunica diretamente com o endpoint. Todavia, Pub/Sub desacopla um cliente que envia uma mensagem particular(chamado publisher) de outro cliente(ou mais clientes), os quais estão recebendo a mensagem(chamado subscriber). Isso significa que tanto o publisher quanto o subscriber, não sabem da existência um do outro. O terceiro componente existente nesse protocolo é o broker(no projeto será o kernel). Já o broker é conhecido tanto pelo publisher quanto pelo subscriber. O broker é crucial pois é o responsável por filtrar todas as mensagens chegadas e distribui cada uma delas.

## Aplicação no projeto
O kernel farrá boa parte da comunicação com a parte de software. Serão enviadas informações recebidas das IMU's, também as recebidas acerca dos dados de potência. Todas essa informações vão ser passadas ao software para que a análise seja feita e a decisão seja tomada pelo kernel.
A escolha pelo MQTT foi com base na facilidade em utilizar um protocolo da camada de aplicação cuja velocidade de envio das mensagens serão sufientes em uma rede local. O projeto fica robusto ao utilizar um protocolo confiável e com uma certa mobilidade para o envio ordenado de mensagens. Além disso o protocolo MQTT possui um buffer suficiente para organizar as mensagens em termos de um tempo no kernel do projeto e transparecer a transição de dados em tempo real.  
O projeto envolve uma topogia ideal para o uso do protocolo, pois o kernel necessita julgar informações e divisão correta do envio das mensagens[@fig:Modelo_broker_MQTT], algo que um servidor poderia trazer complicações. Além da base do MQTT é ser usado para comunicação entre máquinas e não por envio à base de solicitações de clientes, como ocorre no servidor. A aplicação também é bem colocada por se tratar de clientes mandando informaçẽos de sensores, o que traz a ideia de IoT, o que não deixa de ser parte do projeto.

A taxa de envio no kernel é de 34.4kbps. Essa é uma informação tida como base a taxa de transmissão do módulo Wifi, ESP8266.

![Celula_s^[Fonte: ]](imagens/mqtt.png){#fig:Modelo_broker_MQTT}

## Integração dos sensores do projeto

Os dados gerados pelos sensores já estão chegando até o kernel, colocando a ESP como cliente e a Raspberry Pi como broker. O código que executa a tarefa inicia o cliente através de uma função padrão do protocolo MQTT, logo após isso as informações sobre a rede local e o IP do kernel são setados para realizar a conexão, também através de outra função padrão do MQTT, nessa situação uma função de reconexão garante que o existe a conexão entre o broker e o determinado cliente. Logo que todas essas etapas são estabelecidas todo o trabalho do cliente ESP8266 será realizado em relação aos dados da IMU por funções e determinadas em um setup, por fim um loop infinito vai garantir que as funções sejam devidamente invocadas para envio das mensagens ao kernel.
A imagem [@fig:Envio_IMU_ESP8266_MQTT] retrata o recebimento de dados pelo terminal da Raspberry Pi, como kernel. Os dados apresentados na imagem são de um vetor de 9 posições com a seguinte ordem dos dados da IMU: acelerômetro x, y e z, depois o giroscópio x, y e z, por fim o magnetômetro x, y , z.

![Celula_s^[Fonte: ]](imagens/teste_mqtt.png){#fig:Envio_IMU_ESP8266_MQTT}





### 2RE-IMU:

  A Unidade de Medida Inercial (IMU) é um sistema microeletromecânico (MEM), que permite identificar a posição  ou o deslocamento de um corpo rígido em um espaço tridimensional. Neste trabalho, a IMU será responsável em determinar a posição do membro inferior direito para a criação de exoesqueleto autónomo para a identificação e correção da postura do praticante de remo indoor. Desse modo, este trabalho sugere implementar uma IMU em dois centros de gravidades, pois nesses pontos a massa está distribuída de forma uniforme,  localizados no membro inferior do exoesqueleto como pode ser visto na Figura [@fig:exoesqueleto], para estimar a orientação desses pontos onde há equilíbrio de forças [@vaughan99].
  
  
  ![Celula_s^[Fonte:Adaptado de (VAUGHAN et al., 1999)]](imagens/exoesqueleto.png){#fig:exoesqueleto}
  
  A IMU é composta de três sensores principais, os quais são acelerômetro, giroscópio e magnetômetro, o que possibilita obter continuamente  a variação de velocidade, posição e direção de um corpo rígido  [@araujo13] . Esses sensores podem realizar medições nos eixos de referência x,y e z. A Tabela 1.0 apresenta uma comparação entre IMUs de baixo custo e parâmetros relevantes para a escolha da tecnologia, como: quantidade de sensores embarcados, graus de liberdade, custo.

Tabela 1.0 Tabela de comparação de parâmetros das IMUs de baixo custo.

| Parâmetros            | MPU6050 | MPU9250 | GY80 |
|--------------------   |------------|-------|------------|
| Sensor embarcado      |   Único sensor   |    Único sensor   |      Único sensor    |
| Acelerômetro          |   MPU6050        |   MPU9250 |    ADXL345       |
| Giroscópio            |   MPU6050        |    MPU9250   |     L3G4200D       |
| Magnetômetro          |      -   |    AK8963  |   HMC5883L        |
| Graus de liberdade    |      6   |   9    |     10       |
| Custo                 |   R$ 13,90   |   R$ 25,00    |       R$ 80,00     |


  Em observância com a Tabela 1.0, a IMU selecionada como solução foi a MPU9250, pois a mesma possui um custo baixo e magnetômetro, contemplando 9 graus de liberdade, três graus de liberdade a mais do que a MPU6050. A GY80 possui um custo mais alto comparado aos demais. A Figura [@fig:orientacoes] apresenta a orientação dos eixos dos sensores (a) acelerômetro, (b) giroscópio e (c) magnetômetro, esses dados são essenciais para realização do código para aquisição dos sinais (INVENSENSE, 2016). A Tabela 2.0 apresenta as características do MPU9250. Os três sensores imbutidos na MPU9250 podem obter sinais nos três eixos (x, y, z) e possuem três conversores analógico-digitais (ADCs) de 16 bits, para cada respectivo sensor.
  
![Celula_s^[Fonte:Adaptado de (INVENSENSE, 2016).]](imagens/orientacoes.png){#fig:orientacoes}
 
 
 Tabela 2.0 Características da IMU MPU9250
 
| Características             | MPU9250            |
|------------------------------|--------------------|
| Alimentação                  |       2,4 - 3,6 V  | 
| Dimensão                     |  15 x 25 mm        |    
| Graus de liberdade           |       9            |    
| Interface de comunicação     |     I2C           |   
| Corrente de operação normal  |        3,5 mA   |  
| Frequência de operação       |        400 kHz   |  

Essa corrente de operação é com o DPM habilitado. O DPM é o processador utilizado na IMU9250.

Fonte: (INVENSENSE, 2016)



 
 Foi realizado um código para calibrar as IMUs utilizadas, pois como as medidas devem ser enviadas de forma contínua, é necessário que haja uma maior precisão. 

#### Calibração

  Para que seja realizada a leitura dos dados dos sensores da IMU MPU9250 e os futuros processamentos de dados para o estudo de estimar a orientação do membro inferior direito do praticante de remo indoor, foram realizados testes para calibrar os sensores, pois como a leitura será realizada de forma contínua é necessário que os dados sejam precisos. Os testes foram realizados utilizando o microcontrolador ESP8266 Node MCU e o software Matlab. A conexão desses dispositivos está disposta no diagrama da Figura X.
  Figura das conexões.

   Para realizar a calibração dos três eixos (x,y,z), foi necessário que o sensor ficasse apoiado de forma firme, para isso foi utilizada uma plataforma, a qual foi feita para auxiliar na calibração de IMUs pelo LEIA (Laboratory of Embedded Systems and Integrated Circuits Applications). Essa plataforma foi desenvolvida em um software 3D, e serve apenas como apoio e para facilitar o manuseio  nos processos de calibração da da IMU. Para realizar a calibração foi verificado antes de iniciar que a bancada estava na posição correta  e durante o procedimento não houve movimentos bruscos. Como pode ser visto na Figura [@plataforma], observa-se que é possível manipular os três eixos da IMU manualmente. Essa bancada possui três transferidores, cada um destinado a medida de grau para cada eixo. A resolução da medida de grau da bancada é de 10 graus.
   
  ![Celula_s^[Fonte:Autor,2018).]](imagens/plataforma.jpg){#fig:plataforma}
   
  Vale ressaltar que com essa plataforma a calibração continua a ser manual, como acontece em drones, exoesqueletos [@fabian2018]. Para o desenvolvimento do software de calibração foram definidos o endereço na MPU9250 dos sensores de acelerômetro e giroscópio 0x68 e o do magnetômetro 0x0C (InvenSense, 2016). Esses endereços são os do escravos e eles são necessários para que a comunicação I2C  aconteça entre a ESP8266 e os sensores.  
  
Duas funções foram criadas como base para a calibração, a função de escrita e a de leitura. A função de escrita dos dados envia o endereço dos sensores da MPU9250 (8 bits), o endereço do registrador, onde será escrito os valores (8 bits) e o dado a ser escrito (8 bits). A função de leitura dos dados recebe o endereço dos sensores (8 bits), o valor do registrador, onde os dados têm de serem lidos (8 bits), o número de bytes e o dado que foi lido (8 bits). Os intervalos de tempo para a calibração, foram os mesmos utilizados por [@fabian18] em seu estudo, a fim de comparação. Os intervalos utilizados foram de  ±250 graus/seg, ±2g e ±4800µT (nas respectivas unidades de graus, gravidade e Tesla ) e foram utilizados para o giroscópio, acelerômetro e magnetômetro, respectivamente. O valor do magnetômetro é dado em mG e foi feita uma conversão para Tesla partindo de que, (10mG = 1uT). Entretanto, no Matlab usou-se a unidade mG, para validar com o valor real. 

  As escalas foram definidas conforme o (InvenSense, 2016) apresenta em relação ao acelerômetro e giroscópio para que a conversão analógica/digital fosse feita corretamente. A código de calibração consistiu em satisfazer os seguintes passos. Inicialmente, a MPU9250 ficou na posição inicial, como mostra a Figura XX. Observa-se que o eixo definido como z está perpendicular com o eixo horizontal da plataforma, os sensores acelerômetro e giroscópio ficaram parados e o magnetômetro foi girado de modo a fazer uma volta (360 graus), isso para obter os valores dos offsets do acelerômetro e giroscópio.  O segundo passo foi necessário para calibrar o sensor magnetômetro, o eixo y, definido como a parte externa da base da protoboard (essa está em vermelho na Figura [@plataforma]) foi posicionado em paralelo com o eixo horizontal e girou-se 360 graus, para a obtenção dos offsets do magnetômetro. Esses valores são de extrema importância, pois serão utilizados como parâmetros no código de leitura principal para adequar as leituras feitas. 
Para os cálculos de offset foram analisados 100 amostras em cada eixo para verificar quais eram os valores máximos e mínimos do deslocamento dos sensores, conforme também foi realizado no estudo de [@fabian18], em que o deslocamento foi definido pela equação 3.0. Ademais, o cálculo para o fator de escala também foi realizado, apresentado na equação 3.1.

 $offset_{x,y,z} = (valormax_{x,y,z} + valormin_{x,y,z})/2$         Equação 3.0
 
 $fatoresc_{x,y,z} = (valormax_{x,y,z} - valormin_{x,y,z})/2$       Equação 3.1

  No software Matlab foram adquiridos os dados sem o ajuste da calibração e com o ajuste da calibração (de offset e fator de escala) para que fosse analisado o resultado da calibração. A Figura [@fig:acel] mostra os valores correspondidos ao acelerômetro antes e depois da calibração, nota-se que os dois apresentam um certo ruído, entretanto, no não calibrado os valores estão um pouco abaixo dos valores reais (0g e 1g), após a calibração esses valores ficaram mais próximos dos reais devido aos ajustes realizados de offset. 
 
 ![Celula_s^[Fonte:Autor,2018).]](imagens/acel.png){#fig:acel}

  A  Figura [@giro], mostra os valores correspondidos ao giroscópio antes e depois da calibração, é possível observar que os gráficos são muito parecidos, isso pode ter acontecido, pois nesse processo em específico, o integrante pode ter refeito a calibração. p calibrado possui os valores mais próximos ao valor (0 graus/s), conforme o esperado.


![Celula_s^[Fonte:Autor,2018).]](imagens/gir.png){#fig:gir}


  Na calibração do magnetômetro é necessário enfatizar que cada eixo deve ser calibrado em relação ao mesmo campo magnético, foi por esse motivo que fez-se primeiro nos eixos x e y e depois no z. Na Figura [@mag] é possível verificar que a calibração é primordial para esse sensor, pois sem os ajustes os dados do mesmo não terá valor significativo, o valor da medida dos eixos não está disposto no ponto de referência dos três eixos (0,0,0). Cada eixo está localizado em um ponto diferente. Depois de calibrado, observa-se que os três eixos estão centralizados próximo ao ponto de referência (0,0,0), o que indica que os três eixos (x,y,z) estão calibrados em relação ao mesmo campo magnético.

 ![Celula_s^[Fonte:Autor,2018).]](imagens/mag.png){#fig:mag}


#### Protocolo de comunicação I2C

  O protocolo I2C (Inter- Intergrated Circuit) é um barramento de comunicação serial que utiliza dois fios( Serial Data- DAS e Serial Clock- SCL), ou seja sinal de dados e de clock. Ele realiza a comunicação de escrita (W) e leitura (R) entre dois ou mais dispositivos, em que se pode ocorrer entre um mestre e um ou mais escravos. Para que o mestre envie sinal para determinado escravo ele precisa saber qual o endereço do escravo. Cada escravo tem um endereço específico de identificação, composto de 7 bits [@fabian18]. Neste trabalho, o dispositivo dimensionado como mestre é o microcontrolador ESP8366 Node-MCU, e o escravo é a MPU9250. Tem-se também o escravo do escravo, o qual é o segundo MPU9250. ço do escravo a ser contactado.
  
   A Figura [@fig:i2c] apresenta um exemplo do protocolo de comunicação I2C. A comunicação é iniciada pelo mestre, o início e término da comunicação é determinada pela variação do clock do nível baixo para alto. Por outro lado, para que aconteça o envio de dados o SDA tem de mudar de nível lógico quando o SCL estiver em nível baixo, depois de ter ocorrido a transição desse, de alto para baixo (critério de início) e de baixo para alto (critério de término). Feito isso, o mestre envia 1 byte, em que o bit menos significativo representa a seleção de escrita (‘1’) ou leitura (‘0’) e os demais bits representam o endereço do escravo que ele quer se comunicar. O escravo por sua vez retorna um sinal, Acknowledge (ACK), em que nível baixo indica que ele está pronto para aceitar os dados e nível alto indica um sinal de não reconhecimento,  Not Acknowledge  (NACK). Depois da validação de reconhecimento ocorre a troca de dados pelo pino SDA, até que a condição de término seja satisfeita [@lima12][@fabian18].
  
   ![Celula_s^[Fonte:Adaptado de (INVENSENSE, 2016).]](imagens/i2c.png){#fig:i2c}
  
  Ao colocar o segundo MPU9250, segundo escravo, para que não houvesse curto-circuito nas linhas de transmissão foram colocadas resistências de pull-up de 3.3k.
  
  
  
#### Leitura dos dados das IMUs


  Para realizar as leituras foi utilizado uma ESP8266 com 2 IMUs multiplexadas, assim, com apenas um microcontrolador seria possível obter os dados das IMUs,
      
  Inicialmente foram setados todos os registradores da MPU9250, que se referem ao acelerômetro e giroscópio, e também do AK8963, que é o registrador do magnetômetro. Em seguida foram definidas as escalas de transformação para os valores práticos de graus/segundo para giroscópio, gravidade para o acelerômetro e tesla para o magnetômetro.
  Para continuar o programa foram colocadas as variáveis de offset de acordo com os dados retirados da calibração para cada IMU, assim como o fator de escala para o magnetômetro. As demais variáveis utilizadas ao longo do código foram definidas e desse modo pode se iniciar as funções: inicialização da comunicação I2C, função de escrita, função para multiplexação dos IMUs e função de leitura dos dados. Foi estudado como trabalhar melhor com a ESP266 para ler mais de uma IMU, somente os pinos D1 e D2 da ESP8266 transmitem comunicação I2C, portanto utilizou-se os pinos digitais D6 e D7 para multiplexar a partir do código e obter os dados das IMUs acopladas ao sistema. 
  É necessário frisar que a orientação do magnetômetro é diferente em relação aos demais sensores, como mostrado na imagem [@fig:orientacoes], portanto ao se criar o código, mudou-se a ordem da orientação para que não houvesse erro na futura fusão sensorial.
  
  
 
   Envio de dados via MQTT 

   Cálculo da taxa de transmissão de dados


### 2RE - Relay

O subsistema 2RE-Relay era o responsável por controlar as cargas de resistência do gerador inicialmente, porém após mudanças para adequação do freio eletromagnético construído pelo 2R-Power o subsistema passou a fazer o controle do número de bobinas acionadas em cada vez.

O freio eletromagnético conta com 2 bobinas, sendo cada uma delas seccionada em 4 sub-bobinas, isso para que haja 4 módulos de força diferentes para freiar o disco durante o movimento de remada do atleta, portanto para controlar as 8 bobinas individuias escolheu-se o módulo relé com 4 canais cada um, portanto 2 módulos conseguem chavear 8 bobinas individualmente.

Quando o atleta vai começar o movimento, ele deve apertar o botão 1 para que o sistema seja iniciado ou reiniciado caso algum outro indivíduo estivesse utilizando o equipamento anteriomente. Após ter apertado o primeiro botão o indivíduo então tem que escolher a carga de força para execução da remada, ela vai de 1 a 4, sendo o peso 1 o mais fraco e aumenta proporcionalmente conforme o atleta aperta o botão 2, o botão 3 serve para diminuir a carga de 4 até 1 caso o atleta queira voltar a realizar o movimento com uma carga menor. É importante frisar que o atleta deve para o movimento antes de mudar a carga, pois as estatísticas estarão sendo contabilizadas a partir da carga escolhida, também é importante presar pela segurança do atleta e como o controle fica na lateral do movimento, não é seguro que o mesmo tente alterar a força da remada durante a realização do esporte.

Para validar oo funcionamento dos relés, foi montado um circuito com botões e relés e este circuito foi conectado nas bobinas do freio eletromagnético, o resultado dos testes foi positivo, sendo possível controlar a ativação das bobinas 2 a cada vez, uma de cada um dos 2 freios eletromagnéticos.

![reles^[Fonte: Do_autor]](imagens/rele.jpeg){#fig:Rele}



### 2RE-UI

Para que o usuário solicite a mudança de carga e a inicialização/reset do equipamento 2Row é necessário uma interação usuário-máquina. Foram pesquisados alguns modelos de botões para inserir no sistema, em que foram observados as seguintes características: resistência, durabilidade, praticidade e tamanho suficiente para facilitar a visualização e o pressionamento do mesmo. Desse modo, foi escolhido o botão de acrílico, o qual pode ser alimentado com uma tensão de 3,3 V da própria raspberry pi 3, a Figura [@fig:botoao] mostra o botão que será utilizado,. Ademais, como ele atende as necessidades do projeto outro ponto para a escolha desse botão foi devido ao fato de um integrante do grupo possuir esse mesmo modelo, o que proporciona economia ao custo do projeto.

 ![carga^[Fonte:Autor]](imagens/botao.jpeg){#fig:botao}

 Para testar esse subsistema foi criado um código em Python e utilizou-se o microprocessador raspberry Pi 3. Foram setados os pinos 11,15 e 18 como entradas, para receber os valores do estado do botão. Foi setado resistor pull-down no código, isso para certificar que quando o botão não for pressionado, ele não será ativado. O código permite realizar a leitura dos botões acionados pelo usuário, tanto quanto, realizar um tratamento do sinal recebido, pois as chaves mecânicas possui um erro conhecido como bouncing, que pode ser entendido como uma trepidação que causa oscilações no sinal, e necessita de um algoritmo de debounce.
 O código desenvolvido possui um delay de 0.5 segundo até a próxima leitura, desprezando assim qualquer acionamento do botão que poderia ser feito dentro desse tempo. Um evento é criado sempre que o botão pressionada durante o intervalo de tempo, ou seja, há a utilização da função detecção de eventos, chamado de event_detect, em qualquer borda de descida. Esse evento é responsável por armazena o estado do botão, e coloca como prioridade, para quando se der o início do próximo loop, baseados na função callback, retornar o evento que ocorreu. Para o tratamento de bounce, podemos aproveitar o parâmetro callback e requisitar que este ignore os primeiros 100 milisegundos da leitura, usando o parâmetro bouncetime.


### 2RE-Watt

  O subsistema inicialmente denominado 2RE-Volt, que a princípio seria responsável por medir a tensão das cargas no gerador para encontrar, sabendo a carga do gerador em atuação, a potência elétrica durante a realização da remada do atleta. Após testes preliminares a solução de energia decidiu mudar o método de manter uma força contrária ao movimento do atleta e então optou-se pelo freio eletromagnético. Portanto, eletrônica teve que encontrar outra solução para medição da potência mecânica do atleta durante o movimento.

  Foram analisadas então 2 opções para medição da potência do movimento: wattímetro no eixo rotativo e células de carga (strain gage) sob os pés do atleta. então foram geradas as tabelas a seguir para determinar qual tecnologia seria aplicada. 

| Compontes do Wattímetro | Quantidade | Média de Preço (R$) | Localização do Fornecedor |
|--------------------------|------------|-------|------------|
| Torquímetro digital                    |        1   |    630,00   |      São Paulo      |
| Encoder                      |        1   |    120,00   |     São Paulo       |
| Wattímetro digital         |        1   |    2.000,00   |     São Paulo       |

**Colocar as imagens de todos os subcomponentes pensados para escolha

![Torquímetro_digital^[Fonte: https://produto.mercadolivre.com.br/MLB-703889366-torquimetro-digital-12-de-4-a-20-kgf-m-waft-_JM]](imagens/torquimetro.png){#fig:torquimetro}

![Encoder^[Fonte: https://produto.mercadolivre.com.br/MLB-882483511-encoder-incremental-rotativo-600-pulsos-eixo-6mm-5-24v--_JM]](imagens/encoder.png){#fig:encoder}

![Wattímetro^[Fonte: https://produto.mercadolivre.com.br/MLB-945963390-medidor-de-potncia-stages-bluetooth-modelo-spm1-175mm-_JM]](imagens/wattimetro.png){#fig:wattimetro}

| Compontes da Célula de Carga | Quantidade | Média de Preço (R$) | Localização do Fornecedor |
|--------------------------|------------|-------|------------|
| Strain gage modelo S                  |        2   |    200,00   |      São Paulo      |
| Strain gage modelo viga de flexão                  |        2   |    130,00   |      São Paulo      |
| HX711         |        2   |    15,00   |     Brasília       |

![Celula_s^[Fonte: ]](imagens/modelo_s.jpeg){#fig:modelo_s}

![Celula_de_carga^[Fonte: https://produto.mercadolivre.com.br/MLB-931359038-celula-de-carga-sensor-de-peso-200kg-200-kg-0296-_JM]](imagens/celula.png){#fig:celula_de_carga}


![HX711^[Fonte: https://produto.mercadolivre.com.br/MLB-930850652-modulo-conversor-hx711-para-sensor-de-peso-projeto-arduino-_JM]](imagens/hx711.png){#fig:hx711}



  Portanto, analisando valores e disponibilidade rápida para entrega, conclui-se que comprar um wattímetro pronto estaria fora do orçamento do projeto uma vez que seu valor é muito alto, também analisou-se comprar um torquímetro e um encoder, mas seria uma solução relativamente complexa do ponto de vista de integração e também por aumentar o escopo do projeto, uma vez que já há demasiado trabalho a ser realizado. Por isso, optou-se por colocar 2 células de carga na base para os pés para realizar medições de força e transformá-las em potência, como será explicado adiante.  
  
  
  #### HX711
  
  HX711 é um preciso conversor analógico-digital de 24 bits feito para converter escalas de peso de células de carga. Suas utilização é vasta pois o mesmo torna a leitura de sinais mais simples pois a saída da célula de carga é analógica e o HX711 transduz a saída para digital, podendo então o sinal ser capturado por dispositivos com entradas digitais, como realizado nesse projeto com a Raspberry Pi.
  
  
  ![HX711^[Fonte: ]](imagens/diagrama_hx711.png){#fig:diagrama_hx711}
  
  #### Célula de Carga Modelo S

  A Célula de carga, muito conhecido como "strain gage" é um transdutor responsável por medir a informação de peso ou alguma força a partir da colocação física do objeto a ter a massa descoberta em cima da célula de carga. O strain gage modelo S tem esse nome exatamente por ter o formato de um S, como pode ser observado na figura x, quando o objeto é colocado em cima do mesmo, o peso do objeto deforma a célula de carga, que conta com resistores internos, sendo um deles variável em relação à deformação. Então há uma saída de tensão que varia conforme a deformação da célula quando o objeto pesa sobre a mesma. Com o auxílio do conversor HX711, mostrado na figura xx, o valor de tensão que se encontra analógica é convertida para digital e nos pinos GPIO da Raspberry Pi, que atua como o 2RE-Kernel, é possível obter os valores de saída do HX711.
  
  
![carga^[Fonte: do_autor]](imagens/carga_montada.jpeg){#fig:Testes_célula_de_carga}
  
  
  Para dimensionar a célula de carga a ser utilizada, foi nessário calcular a força de reação em que a mesma será exposta e concomitantemente a isso, o sistema do 2RBoad fez a simulação de forças para o aparato dos pés, para verificar se a estrutura suportaria a força aplicada, para o valor de potência máxima, no qual um atleta de remo pode realizar. Segundo os autores, [@maia06] [@baptista05], a potência máxima de por ciclo de remada pode ser defina em torno de 600 W. Logo, esse será o valor máximo que o equipamento 2Row irá operar e o valor que será aplicado ao modelo matemático proposto.
  
   Tendo como embasamento que é necessário saber a força de reação, já que a célula de carga ficará inclinada, utilizou-se as equações descritas por (referencia), em que se partiu do princípio do impulso angular e do momento,em que inicialemnte pressupõe que o corpo está em repouso. A equação [@eq:principio_impulso],diz que  os impulsos angulares que atuam em um corpo durante um certo intervalo de tempo é igual a mudança do momento nesse mesmo intervalo.
  
  $$\sum \int_{t1}^{t2}M_{0}dt = I_{0}w_{2} - I_{0}w_{1}$${#eq:principio_impulso}
 
  Por analogia, sabe-se que o Watts pode ser representado por $N\ast m/s$, ou seja, é a mesma unidade de torque por segundo, desse modo, considerou-se que a potência seria o argumento da integral do impulso, tendo em vista que o corpo deixou de ficar em repouso. O cálculo foi realizado nesse momento, dessa forma, para título de comparação com a simulação da estrutura, localizada no plano de integração entre estrutura/eletrônica. Como foi dito anteriormente, considerou-se a potência máxima como 600 W. A partir da equação [@eq:velocidadeang], encontrou-se a velocidade angular para realizar o cálculo da força. O intervalo de tempo definido foi o tempo de ciclo da remada especificado em 1 segundo pelos autores para a potência descrita.
  
  $$$I_{0}w = \int_{0}^{1}600dt$$${#eq:velocidadeang}
   
  $w = 600 (N \times m/s) /(|I_{0}|(kg\times m^{2}))$


O módulo da força é dado pela equação [@eq:modulof], mas para isso precisou calcular a força referente ao eixo x e ao eixo y, as quais foram aplicadas pela equação [@eq:forca].


$$$|F| = \sqrt{F_{x}^{2} + F_{y}^{2}}$$${#eq:modulof}
  
  $$$\sum F_{n}= mw^{2}r_{0}$$${#eq:forca}
  
  $F_{x}= m(600/I_{0})\times r_{0}$
  
  Onde, $r_{0} = 34,5\times (10^{-3})$ 
        $I_{0} = 1/2 \times m r^{2}$
        
        
  Logo, a força será: 
  
  $|F| = 1697,056 N$
  
  Pela Segunda Lei de Newton sabe-se que:
  
  $F = m\times a$
  
  Desse modo, o peso máximo será de:
  
  $m = 173,169 kg$
  
  
  
 Em cada pé o peso máximo será de $m = 86,58 kg$
 
  

  
  Entre os modelos pesquisados para servir como célula de carga, o modelo S e o modelo de viga de flexão foram os que mais se adaptaram às necessidades do projeto. Pensando na alocação dos sensores no subsistema 2RE-Boat, foi escolhida então a célula de carga modelo S pois a mesma ocuparia menos espaço e tem o limite de força adequado à medição necessária. 
 
  Para realizar a medição da força a partir da célula de carga foi necessário utilizar um componente que converte as saídas analógicas a do strain gage em saídas digitais, o componente em questão é o hx711. Para realizar os testes do subsistema realizou-se a leitura na Raspberry Pi 3 em seus pinos GPIO, um programa em python foi criado e a leitura da força pôde ser realizada, o modelo de célula de carga escolhida suporta o limite de 200 kg, passando do limite estabelicido no projeto, já que uma célula de carga de 100 kg resolveria. No entanto, tendo em vista que CS200, produto do fornecedor da Balança Líder, suporta o peso máximo calculado um dos fatores para se utlilizar esse dispositivo além das especificações apresentadas foi a disponibilidade de empréstimo de 2 células de carga do modelo S por professores da FGA.



    
#### Cógido para leitura dos valores de força

  Para realizar a leitura da força exercida nas células de carga e realizar testes para futura integração foi criado um programa em Python para que a leitura pudesse acontecer usando o microprocessador Raspberry Pi, os pinos 8 e 13 foram colocados no modo BOARD,além do VCC e GND para conezão om o HX711. A leitura pode ser vista na imagem a seguir:
  
  
  ![carga^[Fonte: Autor]](imagens/monitor_carga.png){#fig:monitor_carga}








# Plano de Integração

## Integração de 2RElectronic com 2RBoat

 A integração do sistema de eletrônica  com software consiste em duas situações. A primeira trata-se da estrutura, a qual supotará as células de cargas (Estrutura de apoio aos pés), adequada para comportar o sensor e a passagem dos fios do mesmo. A segunda, trata-se do fornecimento da estrutura do case para alocar os sistemas emcados, incluindo os botões, a raspberry Pi 3 e os demais sistemas da parte de software 

## Integração de 2RElectronic com 2R-Power


A integração com energia se baseia em fazer as conexões necessárias para chavear as bobinas utilizando o circuito com relés já mencionados anteriormente, testes já foram feitos para o acionamento de cada bobina separadamente e eles se mostraram nem executados.

![reles^[Fonte: Do_autor]](imagens/reles.png){#fig:Reles}


