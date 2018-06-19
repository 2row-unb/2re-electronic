//.............................................................................................................................................................................................
//                                                                      PROGRAMA DE CALIBRACAO DA IMU9250 (MPU6500+AK8963)
//.............................................................................................................................................................................................
// Autor: Fabián Barrera Prieto
// Curso: Mestrado em Sistemas Mecatrônicos
// Instituicao: Universidade de Brasília
// Data: 17/04/2017
//.............................................................................................................................................................................................

//----------------------------------------------------------------------------
//                                BIBLIOTECAS
//----------------------------------------------------------------------------

#include <Wire.h> // Biblioteca para permitir a comunicação com dispositivos I2C/TWI
#include <ESP8266WiFi.h> // biblioteca para usar as funções de Wifi do módulo ESP8266
#include <ArduinoJson.h>  COLOCAR SEM AS BIBLIOTECAS PARA VER SE PARA DE DAR PROBLEMA NOS PINOS DIGITAIS
#include <stdlib.h>

//----------------------------------------------------------------------------
//  FUNCAO ESCRITA DADOS [Endereco(8bits) | Regitrador(8bits) | Dado(8bits)]
//----------------------------------------------------------------------------
//Address = 0x68 (Endereco da MPU9250 "acel e giro") ou 0x0C (Endereco do Magnetômetro)
//Register = 0x1C ou 0x1B (Endereco do registrador a acessar na MPU9250 "acel e giro") ou 0x (Endereco do Magnetômetro)
//Data = Nome_Data (Dado que vai ser configurado)

void void_write(uint8_t Address, uint8_t Register, uint8_t Data){
  Wire.beginTransmission(Address); //Inicia comunicação com o endereço I2C do sensor   
  Wire.write(Register); //Define o endereço inicial
  Wire.write(Data); //Escreve o dado a configurar
  Wire.endTransmission(); //Deixa aberta a comunicação com o endereço I2C do sensor
}
//----------------------------------------------------------------------------
//  FUNCAO LEITURA DADOS [Endereco(8bits) | Regitrador(8bits) | N°Bytes(#) | Dado(8bits)]
//----------------------------------------------------------------------------
//Address = 0x68 (Endereco da MPU9250 "acel e giro") ou 0x0C (Endereco do Magnetômetro)
//Register = 0x3B (Endereco do registrador a acessar na MPU9250 "acel e giro") ou 0x03 (Endereco do Magnetômetro)
//Nbytes = 6 para acelerômetro + 2 termometro + 6 girôscopio ou 6 magnetometro (Numero de bytes a transportar)
//Data = Buffer (Nome da variavel onde vai ser salvados os bytes transportados)

void void_read(uint8_t Address, uint8_t Register, uint8_t Nbytes, uint8_t* Data){
  Wire.beginTransmission(Address); //Inicia comunicação com o endereço I2C do sensor   
  Wire.write(Register); //Define o endereço inicial
  Wire.endTransmission(); //Deixa aberta a comunicação com o endereço I2C do sensor

  // Read Nbytes
  Wire.requestFrom(Address, Nbytes); //Solicita os dados de 14 endereços de 8 bits do sensor (6 do Acelerômetro, 2 do Termometro e 6 do Girôscopio))
  uint8_t index = 0; // Índice do vetor, o qual chegará até Nbytes
  while (Wire.available()) //Enquanto fique disponível a conexao com os sensores
    Data[index++] = Wire.read(); //Vetor onde vai armazenar os dados dos sensores
}

//----------------------------------------------------------------------------
//                       DEFINICOES DO DATASHEET DA MPU9250
//----------------------------------------------------------------------------

// Enderecos dos escravos
#define    MPU6500_address            0x68 // Endereço da MPU6500 (giroscópio e acelerômetro)
#define    AK8963_address             0x0C // Endereço do magnetômetro AK8963

// Escalas do girôscopio
#define    GYRO_FULL_SCALE_250_DPS    0x00 // SCALE_250 (°/s) = 0 (0x00 = 000|00|000)
#define    GYRO_FULL_SCALE_500_DPS    0x08 // SCALE_500 (°/s) = 1 (0x08 = 000|01|000)
#define    GYRO_FULL_SCALE_1000_DPS   0x10 // SCALE_1000 (°/s) = 2 (0x10 = 000|10|000)
#define    GYRO_FULL_SCALE_2000_DPS   0x18 // SCALE_2000 (°/s) = 3 (0x18 = 000|11|000)

// Escalas do acelerômetro
#define    ACC_FULL_SCALE_2_G        0x00 // SCALE_2_G (g) = 0 (0x00 = 000|00|000)
#define    ACC_FULL_SCALE_4_G        0x08 // SCALE_4_G (g) = 1 (0x08 = 000|01|000)
#define    ACC_FULL_SCALE_8_G        0x10 // SCALE_8_G (g) = 2 (0x10 = 000|10|000)
#define    ACC_FULL_SCALE_16_G       0x18 // SCALE_16_G (g) = 3 (0x18 = 000|11|000)

// Escalas de conversao (As taxas de conversão são especificadas na documentação)
#define SENSITIVITY_ACCEL     2.0/32768.0             // Valor de conversão do Acelerômetro (g/LSB) para 2g e 16 bits de comprimento da palavra
#define SENSITIVITY_GYRO      250.0/32768.0           // Valor de conversão do Girôscopio ((°/s)/LSB) para 250 °/s e 16 bits de comprimento da palavra
#define SENSITIVITY_TEMP      333.87                  // Valor de sensitividade do Termometro (Datasheet: MPU-9250 Product Specification, pag. 12)
#define TEMP_OFFSET           21                      // Valor de offset do Termometro (Datasheet: MPU-9250 Product Specification, pag. 12)
#define SENSITIVITY_MAGN      (10.0*4800.0)/32768.0   // Valor de conversão do Magnetômetro (mG/LSB) para 4800uT, 16 bits de comprimento da palavra e conversao a Gauss (10mG = 1uT)


//----------------------------------------------------------------------------
//                           DECLARACAO DE VARIAVEIS
//----------------------------------------------------------------------------
bool newMagData = false;

// Offsets de calibração
int i = 0, offset_samples = 100;
double offset_accelx = 0.0, offset_accely = 0.0, offset_accelz = 0.0;
double offset_gyrox = 0.0, offset_gyroy = 0.0, offset_gyroz = 0.0;
double offset_magnx = 0.0, offset_magny = 0.0, offset_magnz = 0.0;
double scale_magnx = 0.0, scale_magny = 0.0, scale_magnz = 0.0, avg_scale = 0.0;

// Máximos e mínimos para os offsets
double max_accelx = -32768.0, min_accelx = 32767.0, max_accely = -32768.0, min_accely = 32767.0, max_accelz = -32768.0, min_accelz = 32767.0;
double max_gyrox = -32768.0, min_gyrox = 32767.0, max_gyroy = -32768.0, min_gyroy = 32767.0, max_gyroz = -32768.0, min_gyroz = 32767.0;
double max_magnx = -32768.0 , min_magnx = 32767.0, max_magny = -32768.0, min_magny= 32767.0, max_magnz = -32768.0, min_magnz = 32767.0;


// Valores "RAW" de tipo inteiro
int16_t raw_accelx, raw_accely, raw_accelz;
int16_t raw_gyrox, raw_gyroy, raw_gyroz;
int16_t raw_temp;
int16_t raw_magnx, raw_magny, raw_magnz;

// Valores "RAW" de tipo double
double Raw_accelx, Raw_accely, Raw_accelz;
double Raw_gyrox, Raw_gyroy, Raw_gyroz;
double Raw_temp;
double Raw_magnx, Raw_magny, Raw_magnz;

// Bytes
uint8_t data[1];
uint8_t GirAcel[14];
uint8_t Mag[7];

// Tempos
unsigned long t_ini_config, t_fim_config, t_ini1_cal, t_fim1_cal, t_ini2_cal, t_fim2_cal, t_ini3_cal, t_fim3_cal, t_ini, t_fim, t;
//                                                                ----------------------------------------------------------------------------
//                                                                                           INICIO DA FUNCAO 'SETUP'
//                                                                ----------------------------------------------------------------------------
void setup() {
t_ini_config = millis();
//.....................................................................
//                        Inicializacao I2C
//.....................................................................
Wire.begin(); //Inicializando comunicacao I2C   
Serial.begin(115200); // Abrindo o canal de comunicação serial a 115200 baudios/segundo
delay(100);
Serial.println("INICIALIZANDO A COMUNICACAO I2C");
Serial.println();

// Desativa modo de hibernação do MPU9250
void_write(MPU6500_address, 0x6B, 0x00); //PWR_MGMT_1 0x6B e CLK_SEL_PWR_MGMT_1 0x00 (// Desativa modo de hibernação da MPU9250, habilitando a opcao (Internal 20MHz oscillator))

Serial.println("TESTE DE CONEXAO PARA O GIROSCOPIO E O ACELEROMETRO");
Serial.println();
//.....................................................................
//        Quem sou eu para a MPU6500 (giroscópio e acelerômetro)
//.....................................................................
Serial.println("1. Teste de conexao da MPU6500..."); // Verifica a conexao
void_read(MPU6500_address, 0x75, 1, data); //WHO_AM_I_MPU6500 0x75
if (data[0] != 0x71) { // DEFAULT_REGISTER_WHO_AM_I_MPU6500 0x71
  Serial.println(F("Erro de conexao com a MPU6500"));
  Serial.print(F("Opaaa. Eu nao sou a MPU6500, Quem sou eu? :S. I am "));
  Serial.println(data[0],HEX);
  Serial.println("");
  while (1);
}else 
  Serial.println(F("Conexao bem sucedida com a MPU6500"));
  Serial.println(F("Oi, tudo joia?... Eu sou a MPU6500 XD"));
  Serial.println("");

delay(100);  

//.....................................................................
//        Configuracao dos sensores giroscópio e acelerômetro
//.....................................................................

// Configura o Girôscopio (Full Scale Gyro Range  = 250 deg/s)
void_write(MPU6500_address, 0x1B, GYRO_FULL_SCALE_250_DPS); //GYRO_CONFIG 0x1B //Registrador de configuracao do Girôscopio
// Configura o Acelerômetro (Full Scale Accelerometer Range  = 2g)
void_write(MPU6500_address, 0x1C, ACC_FULL_SCALE_2_G); // ACCEL_CONFIG 0x1C //Registrador de configuracao do Acelerômetro

//.....................................................................
//                Configuracao do sensor magnetômetro
//.....................................................................

// Desativa modo de hibernação do AK8963 (Habilita o Magnetômetro)
void_write(MPU6500_address, 0x37, 0x02); //INT_PIN_CFG 0x37 e BYPASS_EN 0x02 (0x02 = 000000|1|0) Habilita o enable para acessar ao Magnetômetro
// Configura o Magnetometro para alta resolucao (16 bits) e leituras continuas (8Hz)
void_write(AK8963_address, 0x0A, 0x16); //MAGN_CNTL 0x0A e BITS_OUTPUT_and_CONTINUOUS_MEASUREMENT_MODE_1 0x11 // "(0001|0010) = 0x12" : (16 bits output | continuous measurement mode 1 para 8Hz para velocidade das amostras)
delay(10);

Serial.println("TESTE DE CONEXAO PARA O MAGNETOMETRO ");
Serial.println();
//.....................................................................
//                Quem sou eu para o magnetômetro (AK8963)
//.....................................................................
Serial.println("2. Teste de conexao do AK8963..."); // Verifica a conexao
void_read(AK8963_address, 0x00, 1, data); // AK8963_address 0x0C e WHO_AM_I_AK8963 0x00
if (data[0] != 0x48) { // DEFAULT_REGISTER_WHO_AM_I_AK8963 0x48
  Serial.println(F("Erro de conexao com o AK8963"));
  Serial.print(F("Opaaa. Eu nao sou o AK8963, Quem sou eu? :S. I am "));
  Serial.println(data[0],HEX);
  Serial.println("");
  while (1);
}else 
  Serial.println(F("Conexao bem sucedida com o AK8963"));
  Serial.println(F("E ai, blz?... Eu sou o AK8963 XD"));
  Serial.println("");
        
delay(100);

t_fim_config = millis() - t_ini_config;
Serial.print("Tempo de inicializacao e configuracao dos sensores (giroscopio, acelerometro e magnetometro): "); 
Serial.print(t_fim_config); Serial.println(" ms");
Serial.println();

}

//                                                                ----------------------------------------------------------------------------
//                                                                                            FIM DA FUNCAO 'SETUP'
//                                                                ----------------------------------------------------------------------------

//                                                                ----------------------------------------------------------------------------
//                                                                                           INICIO DA FUNCAO 'LOOP'
//                                                                ----------------------------------------------------------------------------
void loop() {
t_ini1_cal = millis();
//  .....................................................................
//                 Calibração do Giroscopio e do Acelerometro
//  .....................................................................
Serial.println("CALIBRACAO DO GIROSCOPIO E DO ACELEROMETRO");
Serial.println();
Serial.println(F("Nao mexa neles ate que voce leia a mensagem 'calibracao finalizada'"));
delay(2000);
Serial.println(F("Coloque a IMU em posicao horizontal com as letras viradas para cima "));
delay(2000);

Serial.println(F("Lendo os sensores pela primeira vez...")); //Leitura de dados (primeiras 100 amostras dos sensores descartadas)
for (i=0; i < offset_samples; i++){ 
  void_read(MPU6500_address, 0x3B, 14, GirAcel); // 0x3B é o endereco do ACCEL_XOUT_H
  raw_accelx = (GirAcel[0] << 8 | GirAcel[1]);
  raw_accely = (GirAcel[2] << 8 | GirAcel[3]);
  raw_accelz = GirAcel[4] << 8 | GirAcel[5];
  raw_temp = (GirAcel[6] << 8 | GirAcel[7]);
  raw_gyrox = (GirAcel[8] << 8 | GirAcel[9]);
  raw_gyroy = (GirAcel[10] << 8 | GirAcel[11]);
  raw_gyroz = GirAcel[12] << 8 | GirAcel[13];
  
  delay(10);
}

Serial.println(F("Lendo os sensores e calculando os offsets..."));
for (i=0; i < offset_samples; i++){// 100 amostras dos sensores
  void_read(MPU6500_address, 0x3B, 14, GirAcel);//  0x3B é o endereco do ACCEL_XOUT_H
  raw_accelx = (GirAcel[0] << 8 | GirAcel[1]);
  raw_accely = (GirAcel[2] << 8 | GirAcel[3]);
  raw_accelz = (GirAcel[4] << 8 | GirAcel[5]);
  raw_temp = (GirAcel[6] << 8 | GirAcel[7]);
  raw_gyrox = (GirAcel[8] << 8 | GirAcel[9]);
  raw_gyroy = (GirAcel[10] << 8 | GirAcel[11]);
  raw_gyroz = GirAcel[12] << 8 | GirAcel[13];

  // Valores RAW de inteiros a double
  Raw_accelx = raw_accelx; Raw_accely = raw_accely; Raw_accelz = raw_accelz; 
  Raw_gyrox = raw_gyrox; Raw_gyroy = raw_gyroy; Raw_gyroz = raw_gyroz;
  // Serial.print("raw / RAW : "); Serial.print(raw_gyrox); Serial.print(" / ");Serial.print(Raw_gyrox); Serial.print(" gyro max / min : "); Serial.print(max_gyrox); Serial.print(" / "); Serial.println(min_gyrox);

  // Máximos e mínimos para o acelerômetro em cada um dos seus eixos (X,Y e Z)
  //Eixo X
  if (Raw_accelx >= max_accelx){
    max_accelx = Raw_accelx;
  }
  if (Raw_accelx <= min_accelx){
    min_accelx = Raw_accelx;
  }
  //Eixo Y
  if (Raw_accely >= max_accely){
    max_accely = Raw_accely;
  }
  if (Raw_accely <= min_accely){
    min_accely = Raw_accely;
  }
  //Eixo Z
  if (Raw_accelz >= max_accelz){
    max_accelz = Raw_accelz;
  }
  if (Raw_accelz <= min_accelz){
    min_accelz = Raw_accelz;
  }
        
  //Maximos e minimos para o Giroscopio em cada um dos seus eixos (X,Y e Z)
  //Eixo X
  if (Raw_gyrox >= max_gyrox){
    max_gyrox = Raw_gyrox;
  }
  if (Raw_gyrox <= min_gyrox){
    min_gyrox = Raw_gyrox;
  }
  //Eixo Y
  if (Raw_gyroy >= max_gyroy){
    max_gyroy = Raw_gyroy;
  }
  if (Raw_gyroy <= min_gyroy){
    min_gyroy = Raw_gyroy;
  }
  //Eixo Z
  if (Raw_gyroz >= max_gyroz){
    max_gyroz = Raw_gyroz;
  }
  if (Raw_gyroz <= min_gyroz){
    min_gyroz = Raw_gyroz;
  }
  
  delay(10);
} //for (i=0; i < offset_samples; i++)

//Calculando offset (bias) de calibração
//Giroscópio
offset_gyrox = (max_gyrox + min_gyrox) / 2;
offset_gyroy = (max_gyroy + min_gyroy) / 2;
offset_gyroz = (max_gyroz + min_gyroz) / 2;
//Acelerômetro
offset_accelx = (max_accelx + min_accelx) / 2;
offset_accely = (max_accely + min_accely) / 2;
offset_accelz = (max_accelz + min_accelz) / 2;

Serial.println("Calibracao finalizada do acelerometro e do giroscopio");
Serial.println();
t_fim1_cal = millis() - t_ini1_cal;
Serial.print("Tempo da calibracao do acelerometro e do giroscopio: "); 
Serial.print(t_fim1_cal); Serial.println(" ms");
Serial.println();
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

t_ini2_cal = millis(); 
t_ini3_cal = millis();
Serial.println("CALIBRACAO DO MAGNETOMETRO");
Serial.println();
Serial.println(F("1. Calibracao dos eixos X e Y"));
Serial.println(F("Coloque a IMU com o eixo Z perpendicular ao plano horizontal e aguarde"));
delay(2000);
Serial.println(F("A calibracao dos eixos X e Y, consiste em girar (completar 360 graus) o magnetometro em torno ao eixo Z por 20 segundos"));
delay(5000);
Serial.println(F("Calculando os offsets do Magnetometro dos eixos X e Y..."));
Serial.println(F("'Agora gira o Magnetometro 360 graus'"));
delay(1000);

t_fim = 20000; t_ini = millis(); t = 0;
while (t < t_fim){//amostras do sensor por 20 segundos
  //void_write(AK8963_address, 0x0A, 0x11); //MAGN_CNTL 0x0A e BITS_OUTPUT_and_SINGLE_MEASUREMENT_MODE 0x11 // "(0001|0001) = 0x11" : (16 bits output | single measurement mode)
  //delay(10);
  void_read(AK8963_address, 0x02, 1, data); // ST1=0x02
  newMagData = data[0]& 0x01;
  if(newMagData == true) { // Aguarda o bit 'ready' do magnetômetro para configurar
    void_read(AK8963_address, 0x03, 7, Mag); // MAGN_XOUT_L = 0x03
    uint8_t c = Mag[6]; // End data read by reading ST2 register
    if(!(c & 0x08)) { // Check if magnetic sensor overflow set, if not then report data
      raw_magnx = (Mag[3] << 8 | Mag[2]); 
      raw_magny = (Mag[1] << 8 | Mag[0]); 
      raw_magnz = -(Mag[5] << 8 | Mag[4]);
    }
  }

  // Valores RAW de inteiros a double
  Raw_magnx = raw_magnx;
  Raw_magny = raw_magny;

  //Maximos e minimos para o Magnetometro em cada um dos seus eixos (X,Y e Z)
  //Eixo X
  if (Raw_magnx >= max_magnx){
    max_magnx = Raw_magnx;
  }
  if (Raw_magnx <= min_magnx){
    min_magnx = Raw_magnx;
  }     
  //Eixo Y
  if (Raw_magny >= max_magny){
    max_magny = Raw_magny;
  }
  if (Raw_magny <= min_magny){
    min_magny = Raw_magny;
  }     

  t = millis() - t_ini;
    
}//while (t < t_fin){//amostras do sensor por 20 segundos

// Offsets e escalas do magnetômetro no eixo Z
offset_magnx = (max_magnx + min_magnx) / 2;
offset_magny = (max_magny + min_magny) / 2;
 
scale_magnx = (max_magnx - min_magnx) / 2;
scale_magny = (max_magny - min_magny) / 2;

Serial.println(F("Calibracao finalizada dos eixos X e Y do magnetometro"));
t_fim2_cal = millis() - t_ini2_cal;
Serial.print("Tempo da calibracao dos eixos X e Y do magnetometro: "); 
Serial.print(t_fim2_cal); Serial.println(" ms");

Serial.println();
//.................

t_ini2_cal = millis();
Serial.println(F("2. Calibracao do eixo Z"));
Serial.println(F("Coloque a IMU com o eixo Y perpendicular ao plano horizontal e aguarde"));
delay(2000);
Serial.println(F("A calibracao do eixo Z, consiste em girar (completar 360 graus) o Magnetometro em torno ao eixo Y por 20 segundos"));
delay(5000);
Serial.println(F("Calculando os offsets do Magnetometro do eixo Z..."));
Serial.println(F("'Agora gira o Magnetometro 360 graus'"));
delay(1000);

t_fim = 20000; t_ini = millis(); t = 0;
while (t < t_fim){//amostras do sensor por 20 segundos
  //void_write(AK8963_address, 0x0A, 0x11); //MAGN_CNTL 0x0A e BITS_OUTPUT_and_SINGLE_MEASUREMENT_MODE 0x11 // "(0001|0001) = 0x11" : (16 bits output | single measurement mode)
  //delay(10);
  void_read(AK8963_address, 0x02, 1, data);
  newMagData = data[0]& 0x01;
  if(newMagData == true) { // wait for magnetometer data ready bit to be set
    void_read(AK8963_address, 0x03, 7, Mag); // MAGN_XOUT_L = 0x03
    uint8_t c = Mag[6]; // End data read by reading ST2 register
    if(!(c & 0x08)) { // Check if magnetic sensor overflow set, if not then report data
      raw_magnx = (Mag[3] << 8 | Mag[2]); 
      raw_magny = (Mag[1] << 8 | Mag[0]); 
      raw_magnz = -(Mag[5] << 8 | Mag[4]);
    }
  }
      
  // Valores RAW de inteiros a double
  Raw_magnz = raw_magnz;

  //Maximos e minimos para o Magnetometro em cada um dos seus eixos (X,Y e Z)
  //Eixo Z
  if (Raw_magnz >= max_magnz){
    max_magnz = Raw_magnz;
  }
  if (Raw_magnz <= min_magnz){
    min_magnz = Raw_magnz;
  }    
      
  t = millis() - t_ini;
    
}//while (t < t_fin){//amostras do sensor por 20 segundos

// Offset e escala do magnetometro no eixo Y
offset_magnz = (max_magnz + min_magnz) / 2;

scale_magnz = (max_magnz - min_magnz) / 2;

Serial.println(F("Calibracao finalizada do eixo Z do magnetometro"));
t_fim2_cal = millis() - t_ini2_cal;
Serial.println();
Serial.print("Tempo da calibracao do eixo Z do magnetometro: "); 
Serial.print(t_fim2_cal); Serial.println(" ms");
Serial.println();
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

avg_scale = (scale_magnx + scale_magny + scale_magnz) / 3;

scale_magnx = avg_scale / scale_magnx;
scale_magny = avg_scale / scale_magny;
scale_magnz = avg_scale / scale_magnz;

//  .....................................................................
//                           Imprimir valores
//  .....................................................................
#if 1  
  // Offsets do acelerômetro
  Serial.print("Offset acelX: "); Serial.println(offset_accelx);
  Serial.print("Offset acelY: "); Serial.println(offset_accely);
  Serial.print("Offset acelZ: "); Serial.println(offset_accelz);
            
  // Offsets do giroscópio
  Serial.print("Offset giroX: "); Serial.println(offset_gyrox);
  Serial.print("Offset giroY: "); Serial.println(offset_gyroy);
  Serial.print("Offset giroZ: "); Serial.println(offset_gyroz);
                       
  // Offsets do magnetômetro
  Serial.print("Offset magnX: "); Serial.println(offset_magnx);
  Serial.print("Offset magnY: "); Serial.println(offset_magny);
  Serial.print("Offset magnZ: "); Serial.println(offset_magnz);

  // Escalas do magnetômetro
  Serial.print("Escala magnX: "); Serial.println(scale_magnx);
  Serial.print("Escala magnY: "); Serial.println(scale_magny);
  Serial.print("Escala magnZ: "); Serial.println(scale_magnz);
#endif

t_fim3_cal = millis() - t_ini3_cal;
Serial.println();
Serial.print("Tempo de calibracao dos sensores (giroscopio, acelerometro e magnetometro) : "); 
Serial.print(t_fim3_cal); Serial.println(" ms");
Serial.println();

Serial.println(F("CALIBRACAO ENCERRADA"));
Serial.println();

Serial.println(F("Posiciona a IMU na posicao inicial"));
delay(100000); // Pause infinito
}

//                                                                ----------------------------------------------------------------------------
//                                                                                            FIM DA FUNCAO 'LOOP'
//                                                                ----------------------------------------------------------------------------
