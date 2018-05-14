### 2RE-UI

Para que o usuário solicite a mudança de carga e a inicialização/reset do equipamento 2Row é necessário uma interação usuário-máquina. Foram pesquisados alguns modelos de botões para inserir no sistema, em que foram observados as seguintes características: resistência, durabilidade, praticidade e tamanho suficiente para facilitar a visualização e o pressionamento do mesmo. Desse modo, foi escolhido o botão de acrílico, o qual pode ser alimentado com uma tensão de 3,3 V da própria raspberry pi 3, a Figura [@fig:botoao] mostra o botão que será utilizado.

 ![carga^[Fonte: Autor]](imagens/botao.jpeg){#fig:botao}

O botão utilizado funciona como chave comum. O seguinte esquema abaixo foi montado em protoboard com o  Raspberry Pi 3 para testar uma chave, substituta temporária do botão que seria utilizado. Um resistor pull-down é ativadodentro do código. 
 O código testado em Python foi chamado no terminal do Raspberry.
 Pela recepção e tratamento de dados do teclado: realizar a leitura dos botões acionados pelo usuário, tanto quanto, realizar um tratamento do sinal recebido, pois em chaves mecânicas há um erro conhecido como bouncing, que é uma “trepidação” que causa 
oscilações no sinal, e necessita de um algoritmo de debounce.

O código desenvolvido possui um delay de 1 segundo até a próxima leitura, desprezando assim qualquer acionamento da tecla que
poderia ser feito dentro desse tempo. Para resolução deste problema, um evento é criado sempre que a tecla é pressionada durante o intervalo de tempo, ou seja, há a utilização da função detecção de eventos (event_detect) em qualquer borda de descida, que já faz parte do RPi.GPIO. Esse sistema é responsável por “guardar” o acionamento da tecla, e coloca como prioridade, para quando se der o início do próximo loop, baseados na função callback, retornar o evento
que ocorreu, sendo um segundo processo ou thread. 



