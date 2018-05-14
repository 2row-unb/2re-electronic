### 2RE - Relay

O subsistema 2RE-Relay era o responsável por controlar as cargas de resistência do gerador inicialmente, porém após mudanças para adequação do freio eletromagnético o subsistema passou a fazer o controle do número de bobinas acionadas em cada vez.

O freio eletromagnético conta com 2 bobinas, sendo cada uma delas seccionada em 4 sub-bobinas, isso para que haja 4 módulos de força diferentes para freiar o disco durante o movimento de remada do atleta, portanto para controlar as 8 bobinas individuias escolheu-se o módulo relé com 4 canais cada um, portanto 2 módulos conseguem chavear 8 bobinas individualmente.

Quando o atleta vai começar o movimento, ele deve apertar o botão 1 para que o sistema seja iniciado ou reiniciado caso algum outro indivíduo estivesse utilizando o equipamento anteriomente. Após ter apertado o primeiro botão o indivíduo então tem que escolher a carga de força para execução da remada, ela vai de 1 a 4, sendo o peso 1 o mais fraco e aumenta proporcionalmente conforme o atleta aperta o botão 2, o botão 3 serve para diminuir a carga de 4 até 1 caso o atleta queira voltar a realizar o movimento com uma carga menor. É importante frisar que o atleta deve para o movimento antes de mudar a carga, pois as estatísticas estarão sendo contabilizadas a partir da carga escolhida, também é importante presar pela segurança do atleta e como o controle fica na lateral do movimento, não é seguro que o mesmo tente alterar a força da remada durante a realização do esporte.

![reles^[Fonte: Do_autor]](imagens/rele.jpeg){#fig:Rele}


## Integração com 2RE-Power


A integração com energia se baseia em fazer as conexões necessárias para chavear as bobinas utilizando o circuito com relés já mencionados anteriormente, testes já foram feitos para o acionamento de cada bobina separadamente e eles se mostraram nem executados.

![reles^[Fonte: Do_autor]](imagens/reles.png){#fig:Reles}
