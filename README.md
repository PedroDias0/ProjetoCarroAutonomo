Veículo de Condução Autónoma com ESP32

Projeto desenvolvido no âmbito das unidades curriculares Project Factory e Computação Física e IoT da Licenciatura em Engenharia Informática (IADE).

O objetivo deste projeto foi desenvolver um veículo autónomo capaz de navegar num percurso de forma inteligente, evitando obstáculos e respeitando os limites da pista através da utilização de sensores e de um microcontrolador ESP32.

📌 Funcionalidades
Deteção de obstáculos através de sensores ultrassónicos
Desvio automático de obstáculos
Correção de trajetória com base na distância às paredes
Deteção dos limites da pista através de sensores infravermelhos
Controlo diferencial de tração
Comunicação Bluetooth via ESP32
Telemetria em tempo real através da porta série
Navegação totalmente autónoma
🛠 Tecnologias Utilizadas
Hardware
ESP32
3x Sensores Ultrassónicos HC-SR04
2x Sensores Infravermelhos de Linha
2x Drivers L298N
4x Motores DC com Redução
Bateria LiPo 11.1V (3S)
Conversor Buck DC-DC 5V
Software
Arduino IDE
Linguagem C++
Bluetooth Serial (SPP)
PWM para controlo de velocidade dos motores
🏗 Arquitetura do Sistema

O sistema está dividido em três subsistemas principais:

Alimentação

Uma bateria LiPo fornece energia aos motores através dos drivers L298N. Um conversor Buck reduz a tensão para alimentar o ESP32 e os sensores.

Sensorização

O veículo utiliza:

3 sensores ultrassónicos para deteção de obstáculos e paredes;
2 sensores infravermelhos para deteção das linhas da pista.
Tração

Os quatro motores são controlados através de dois drivers L298N, permitindo movimentos para a frente, trás, esquerda, direita e rotação sobre o próprio eixo.

🤖 Lógica de Navegação

O firmware executa continuamente uma rotina autónoma que:

Lê os sensores ultrassónicos e infravermelhos.
Verifica a existência de obstáculos.
Corrige a posição quando está demasiado próximo de uma parede.
Evita ultrapassar os limites da pista.
Decide a melhor manobra para continuar o percurso.


🚀 Como Executar
Abrir o projeto na Arduino IDE.
Instalar as bibliotecas necessárias para ESP32.
Selecionar a placa ESP32 correta.
Compilar e carregar o firmware.
Ligar a alimentação do veículo.
Colocar o veículo no percurso para iniciar a navegação autónoma.

Equipa

Pedro Dias	
Leonardo Nguyên	
Silésio Virigal	

O projeto resultou num protótipo funcional capaz de percorrer o circuito autonomamente, evitando obstáculos e mantendo-se dentro dos limites definidos pela pista.


Este projeto foi desenvolvido para fins académicos no âmbito da Licenciatura em Engenharia Informática do IADE.
