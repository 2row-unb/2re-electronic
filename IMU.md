

# 3.3  Solução do sistema 2RElectronic

  O sistema de eletrônica ficou responsável pelo sensoriamento, aquisição de sinais, tratamentos dos sinais e controle do acionamento das cargas. Os sinais obtidos foram das IMUs e dos botões, este último define qual a carga que deverá ser acionada. Este relatório apresenta a evolução do grupo, assim como as alterações realizadas no escopo do ponto de controle 1.
  
   
  
  ![diagrama^[Fonte:Do_autor]](imagens/diagrama.png){#fig:Diagrama_Geral}

## 3.3.1 2RE-Suit

  Esse subsistema continha o 2RE-Cardio e o 2RE-IMU. No entanto após a exclusão do 2RE-Cardio, que será explicado o porquê a seguir, o 2RE-Suit passou a ser a vestimenta somente com o 2RE-IMU, dessa forma a confecção ainda está em andamento e será apresentada nas próximas semanas.
  
  
  
### 2RE-Cardio

Inicialmente o 2Row contaria com um sensor para medir frequência cardíaca do atleta de remo durante o movimento, sendo o subsistema chamado de 2RE-Cardio, porém ao final do Ponto de Controle 1 foi notado juntamente com os professores que seria difícil fazer a aquisição dos sinais por alguns motivos, como: dificuldade em alocar o sensor na orelha ou nos dedos das mãos (locais apropriados para aquisição), uma vez que o atleta estará em movimento e poderia sair do lugar durante a remada, dificuldade no processamento do sinal de batimento cardíaco com as muitas interferências durante o movimento.

Portanto, após avaliar as prioridades para execução do projeto, foi decidido retirar do escopo o subsistema 2RE-Cardio, isso fez com que o escopo do 2Row ficasse mais enxuto e exequível em relação ao pouco tempo que resta para a entrega do projeto.

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



# Plano de Integração



## Integração de 2R-Electronic com 2R-Power


A integração com energia se baseia em fazer as conexões necessárias para chavear as bobinas utilizando o circuito com relés já mencionados anteriormente, testes já foram feitos para o acionamento de cada bobina separadamente e eles se mostraram nem executados.

![reles^[Fonte: Do_autor]](imagens/reles.png){#fig:Reles}


