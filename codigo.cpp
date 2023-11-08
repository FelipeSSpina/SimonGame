#include <Arduino.h> // biblioteca Arduino para usar suas funções

// define as constantes para os pinos dos LEDs
const int Led1 = 16; // LED 1 está conectado ao pino 16
const int Led2 = 17; // LED 2 está conectado ao pino 17
const int Led3 = 21; // LED 3 está conectado ao pino 21
const int Led4 = 22; // LED 4 está conectado ao pino 22

// define as constantes para os pinos dos botões
const int Botao1 = 27; // Botão 1 está conectado ao pino 27
const int Botao2 = 26; // Botão 2 está conectado ao pino 26
const int Botao3 = 25; // Botão 3 está conectado ao pino 25
const int Botao4 = 33; // Botão 4 está conectado ao pino 33
const int BotaoRESET = 35; // Botão de reset está conectado ao pino 35

// define o nível máximo do jogo
const int MAX_LEVEL = 5; // O jogo tem 5 níveis

// define os arrays para os pinos dos LEDs e botões
int leds[4] = {Led1, Led2, Led3, Led4}; // Array para armazenar os pinos dos LEDs
int botoes[4] = {Botao1, Botao2, Botao3, Botao4}; // Array para armazenar os pinos dos botões

// define as sequências do jogo e do jogador
int sequencia[MAX_LEVEL]; // array para armazenar a sequência gerada pelo jogo
int player_sequence[MAX_LEVEL]; // array para armazenar a sequência inserida pelo jogador

// define o nível inicial e a velocidade do jogo
int nivel = 0; // inicia o jogo no nível 0
int velocidade = 1000; // define a velocidade inicial do jogo

// configura os pinos dos LEDs e botões como saída ou entrada
void configurarPinos() {
  for (int i = 0; i < 4; i++) {
    pinMode(leds[i], OUTPUT); // configura o pino do LED como saída
    pinMode(botoes[i], INPUT_PULLUP); // configura o pino do botão como entrada com resistor de pull-up
  }
  pinMode(BOTAORESET, INPUT_PULLUP); // configura o pino do botão de reset como entrada com resistor de pull-up
}

// inicia o jogo
void iniciarJogo() {
  nivel = 1; // define o nível inicial como 1
  randomSeed(analogRead(0)); // inicializa o gerador de números aleatórios
  for (int i = 0; i < MAX_LEVEL; i++) {
    sequencia[i] = random(0, 4); // gera uma sequência aleatória para o jogo
  }
  delay(1000); // aguarda 1 segundo antes de iniciar o jogo
}

// mostra a sequência do jogo
void mostrarSequencia() {
  for (int i = 0; i < nivel; i++) {
    int led_a_acender = sequencia[i]; // seleciona o LED a acender de acordo com a sequência do jogo
    digitalWrite(leds[led_a_acender], HIGH); // acende o LED selecionado
    delay(velocidade); // aguarda o tempo definido pela velocidade do jogo
    digitalWrite(leds[led_a_acender], LOW); // apaga o LED selecionado
    delay(200); // aguarda 200 milissegundos antes de acender o próximo LED
  }
  delay(500); // aguarda 500 milissegundos antes de iniciar a próxima rodada
}

// obtém a sequência inserida pelo jogador
void obterSequenciaJogador() {
  int indice_jogador = 0; // inicia o índice do jogador

  while (indice_jogador < nivel) { // enquanto o índice do jogador for menor que o nível do jogo
    for (int i = 0; i < 4; i++) { // para cada botão
      if (digitalRead(botoes[i]) == LOW) { // se o botão foi pressionado
        player_sequence[indice_jogador] = i; // armazena o índice do botão pressionado na sequência do jogador
        digitalWrite(leds[i], HIGH); // acende o LED correspondente ao botão pressionado
        delay(200); // aguarda 200 milissegundos
        digitalWrite(leds[i], LOW); // apaga o LED correspondente ao botão pressionado
        indice_jogador++; // incrementa o índice do jogador
        delay(200); // aguarda 200 milissegundos antes de ler o próximo botão
      }
    }
  }

  verificarSequenciaJogador(); // verifica se a sequência inserida pelo jogador está correta
}

// verifica se a sequência inserida pelo jogador está correta
void verificarSequenciaJogador() {
  for (int i = 0; i < nivel; i++) { // para cada nível do jogo
    if (player_sequence[i] != sequencia[i]) { // se a sequência inserida pelo jogador for diferente da sequência do jogo
      nivel = 0; // reinicia o jogo
      return; // retorna para a função principal
    }
  }
  nivel++; // incrementa o nível do jogo
  delay(500); // aguarda 500 milissegundos antes de iniciar a próxima rodada
}

// reinicia o jogo
void reiniciarJogo() {
  nivel = 0; // define o nível do jogo como 0
}

// configura os pinos dos LEDs e botões
void setup() {    
  configurarPinos(); // chama a função para configurar os pinos dos LEDs e botões
}

// loop principal do jogo
void loop() {
  if (nivel == 0) { // se o nível do jogo for 0
    if (digitalRead(BOTAORESET) == LOW) { // se o botão de reset for pressionado
      iniciarJogo(); // Inicia o jogo
    }
  } else if (nivel <= MAX_LEVEL) { // se o nível do jogo for menor ou igual ao nível máximo
    mostrarSequencia(); // mostra a sequência do jogo
    obterSequenciaJogador(); // obtém a sequência inserida pelo jogador
  } else { // se o nível do jogo for maior que o nível máximo
    reiniciarJogo(); // reinicia o jogo
  }
}
