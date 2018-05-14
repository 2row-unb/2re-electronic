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



  Portanto, analisando valores e disponibilidade rápida para entrega, conclui-se que comprar um wattímetro pronto estaria fora do orçamento do projeto uma vez que seu valor é muito alto, também analisou-se comprar um torquímetro e um encoder, mas seria uma solução relativamente complexa do ponto de vista de integração e também por aumentar o escopo do projeto, uma vez que já há demasiado trabalho a ser realizado. Por isso, optou-se por colocar 2 células de carga na base para os pés para realizar medições de força e transformá-las em potência, como será explicado adiante.  Para dimensionar a célula de carga a ser utilizada, foi nessário calcular a força de reação em que a mesma será exposta e concomitantemente a isso, o sistema do 2RBoad fez a simulação de forças para o aparato dos pés, para verificar se a estrutura suportaria a força aplicada, para o valor de potência máxima, no qual um atleta de remo pode realizar. Segundo os autores, [@maia06], a potência máxima de por ciclo de remada pode ser defina em torno de 600 W. Logo, esse será o valor máximo que o equipamento 2Row irá operar e o valor que será aplicado ao modelo matemático proposto.
  
   Tendo como embasamento que é necessário saber a força de reação, já que a célula de carga ficará inclinada, utilizou-se as equações descritas por (referencia), em que se partiu do princípio do impulso angular e do momento, os quais permitem solucionar problemas que envolvem a força, velocidade e tempo. Para realizar os cálculos foi necessário definir o sistema de coordenadas do diagrama de coprpo livre. A equação XX,diz que  os impulsos angulares que atuam em um corpo durante um certo intervalo de tempo é igual a mudança do momento nesse mesmo intervalo.
  
#### Célula de Carga Modelo S

  A Célula de carga, muito conhecido como "strain gage" é um transdutor responsável por medir a informação de peso ou alguma força a partir da colocação física do objeto a ter a massa descoberta em cima da célula de carga. O strain gage modelo S tem esse nome exatamente por ter o formato de um S, como pode ser observado na figura x, quando o objeto é colocado em cima do mesmo, o peso do objeto deforma a célula de carga, que conta com resistores internos, sendo um deles variável em relação à deformação. Então há uma saída de tensão que varia conforme a deformação da célula quando o objeto pesa sobre a mesma. Com o auxílio do conversor HX711, mostrado na figura xx, o valor de tensão que se encontra analógica é convertida para digital e nos pinos GPIO da Raspberry Pi, que atua como o 2RE-Kernel, é possível obter os valores de saída do HX711.
  
  
![carga^[Fonte: do_autor]](imagens/carga_montada.png){#fig:Testes_célula_de_carga}
 
   O princípio do impulso angular e do momento, permite solucionar problemas que envolva força, velocidade e tempo, para realizar os cálculos é necessário definir o sistema de coordenadas do diadrama de coprpo livre. A equação XX, 
+  $\sum \int_{t1}^{t2}M_{0}dt = I_{0}w_{2} - I_{0}w_{1}$
 
Por analogia, sabe-se que o Watts pode ser representado por $N\ast m/s$, ou seja, é a mesma unidade de torque por segundo, desse modo, considerou-se que a potência seria o argumento da integral do impulso. O cálculo foi realizado dessa forma, nesse momento para título de comparação com a simulação da estrutura. Como foi dito anteriormente, considerou-se a potência máxima como 600 W. A partir da equação XX, encontrou-se a velocidade angular, conforme pode ser observado no cálculo XX. O intervalo de tempo definido foi o tempo de ciclo da remada especificado em 1 segundo pelos autores (referência) para a potência descrita.
+  
+  $I_{0}w = \int_{0}^{1}600dt$
   
+  $w = 600 (N \times m/s) /(|I_{0}|(kg\times m^{2}))$


O módulo da força é dado pela equação XX, mas para isso precisou-se calcular a força referente ao eixo x e ao eixo y, as quais estão dispostas na equação XX


$|F| = \sqrt{F_{x}^{2} + F_{y}^{2}}$
  
  $\sum F_{n}= mw^{2}r_{0}$
  
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
 

  
    
#### Cógido para leitura dos valores de força

  Para realizar a leitura da força exercida nas células de carga e realizar testes para futura integração foi criado um programa em Python para que a leitura pudesse acontecer a partir da Raspberry Pi, os pinos 8 e 13 no modo BOARD, 
  

  

  
  Entre os modelos pesquisados para servir como célula de carga, o modelo S e o modelo de viga de flexão foram os que mais se adaptaram às necessidades do projeto. Pensando na alocação dos sensores no subsistema 2RE-Boat, foi escolhida então a célula de carga modelo S pois a mesma ocuparia menos espaço e tem o limite de força adequado à medição necessária. 
 
  Para realizar a medição da força a partir da célula de carga foi necessário utilizar um componente que converte as saídas analógicas a do strain gage em saídas digitais, o componente em questão é o hx711. Para realizar os testes do subsistema realizou-se a leitura na Raspberry Pi 3 em seus pinos GPIO, um programa em python foi criado e a leitura da força pôde ser realizada, o modelo de célula de carga escolhida suporta o limite de 200 kg, passando do limite estabelicido no projeto, já que uma célula de carga de 100 kg resolveria. No entanto, tendo em vista que CS200, produto do fornecedor da Balança Líder, suporta o peso máximo calculado um dos fatores para se utlilizar esse dispositivo além das especificações apresentadas foi a disponibilidade de empréstimo de 2 células de carga do modelo S por professores da FGA.


