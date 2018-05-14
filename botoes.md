### 2RE-UI

Para que o usuário solicite a mudança de carga e a inicialização/reset do equipamento 2Row é necessário uma interação usuário-máquina. Foram pesquisados alguns modelos de botões para inserir no sistema, em que foram observados as seguintes características: resistência, durabilidade, praticidade e tamanho suficiente para facilitar a visualização e o pressionamento do mesmo. Desse modo, foi escolhido o botão de acrílico, o qual pode ser alimentado com uma tensão de 3,3 V da própria raspberry pi 3, a Figura [@fig:botoao] mostra o botão que será utilizado,. Ademais, como ele atende as necessidades do projeto outro ponto para a escolha desse botão foi devido ao fato de um integrante do grupo possuir esse mesmo modelo, o que proporciona economia ao custo do projeto.

 ![carga^[Fonte:Autor]](imagens/botao.jpeg){#fig:botao}

 Para testar esse subsistema foi criado um código em Python e utilizou-se o microprocessador raspberry Pi 3. Foram setados os pinos 11,15 e 18 como entradas, para receber os valores do estado do botão. Foi setado resistor pull-down no código, isso para certificar que quando o botão não for pressionado, ele não será ativado. O código permite realizar a leitura dos botões acionados pelo usuário, tanto quanto, realizar um tratamento do sinal recebido, pois as chaves mecânicas possui um erro conhecido como bouncing, que pode ser entendido como uma trepidação que causa oscilações no sinal, e necessita de um algoritmo de debounce.
 O código desenvolvido possui um delay de 0.5 segundo até a próxima leitura, desprezando assim qualquer acionamento do botão que poderia ser feito dentro desse tempo. Um evento é criado sempre que o botão pressionada durante o intervalo de tempo, ou seja, há a utilização da função detecção de eventos, chamado de event_detect, em qualquer borda de descida. Esse evento é responsável por armazena o estado do botão, e coloca como prioridade, para quando se der o início do próximo loop, baseados na função callback, retornar o evento que ocorreu. Para o tratamento de bounce, podemos aproveitar o parâmetro callback e requisitar que este ignore os primeiros 100 milisegundos da leitura, usando o parâmetro bouncetime.



