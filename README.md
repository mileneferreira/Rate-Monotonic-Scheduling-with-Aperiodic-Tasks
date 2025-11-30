# Rate Monotonic Scheduling (Automatic RM + Aperiodic Tasks)
This project implements a system that plays two Super Mario Bros songs using a PWM-driven buzzer on the ESP32.  It includes button input, interrupts, periodic and aperiodic tasks, custom GPIO and PWM abstractions, and a custom-configurable thread management system.

Projeto – Sistema de Música com PWM, GPIO e Gerenciamento de Tarefas (ESP32 + ESP-IDF + C++)

Este projeto implementa um sistema em C++ utilizando ESP-IDF com:

Geração de áudio por PWM (buzzer)

Leitura de botões via GPIO com interrupção

Tarefas periódicas para tocar músicas

Tarefas aperiódicas acionadas por interrupções

Infraestrutura própria de configuração de threads e consultas ao estado de tarefas

Biblioteca de notas musicais com frequência em Hz

O sistema permite tocar diferentes melodias quando botões são pressionados, utilizando PWM para gerar as frequências correspondentes às notas musicais.

📁 Organização por Arquivos
1. /main/main.cpp
Função do arquivo

Ponto de entrada do aplicativo. Configura GPIOs, PWM, tarefas e executa o loop principal.

Principais elementos

Tipo Buzzer

using Buzzer = Peripherals::PWM<23, TIMER_0, CHANNEL_0>;


Usa pino 23 para saída PWM do buzzer.

Tarefas periódicas para tocar música
Uma task periodic lê a música atual e envia frequência ao buzzer.

Ação por botões

Botão 1 – GPIO 18 → Seleciona música "Regular"

Botão 2 – GPIO 19 → Seleciona música "Underworld"

MusicChoice enum controla qual música será tocada.

Loop principal apenas mantém o programa ativo:

while (true) std::this_thread::sleep_for(1s);

2. Biblioteca Music (/inc/music/Song.h)
Função

Define:

Tipo Song (span de frequências)

Conjunto completo de notas musicais de B0 até B7

Músicas prontas: Regular Theme e Underworld Theme

Métricas utilizadas

Notas são representadas em Hz

Exemplo:

static constexpr auto A4 = 440_Hz;

Conversão importante

Frequency -> std::chrono::milliseconds
→ Determina o período da nota para controlar duração.

3. Peripherals
3.1 GPIO.hpp
Função

Abstração de entradas e saídas digitais.

Principais recursos

GPIO::Output<pin> – simples write HIGH/LOW

GPIO::Input<pin, edge, pull> – configuração de:

pino

borda (RISING / FALLING)

resistor (UP / DOWN)

Interrupções

register_interrupt(isr_handler, arg)

unregister_interrupt()

Uso no projeto

Botão 1 → GPIO 18

Botão 2 → GPIO 19

Ambos configurados com borda de descida (FALLING) e Pull-up.

3.2 PWM.hpp
Função

Gera frequências usando LEDC (hardware PWM do ESP32).

Template PWM<pin, timer, channel>

Parâmetros usados no projeto:

Recurso	Valor
pino	23
timer	TIMER_0
canal	CHANNEL_0
frequência base	4000 Hz
resolução	8 bits (0–255 duty)
Principais funções
start()

Inicializa canal PWM.

stop()

Desliga PWM (duty = 0).

set_frequency(Frequency freq)

Altera frequência do timer.

set_duty(Percentage duty)

Define razão cíclica (0.0 a 1.0).

4. Task System

O projeto implementa um framework próprio para manipulação de tarefas com std::thread + ESP-IDF pthread extensions.

4.1 task/Config.h & Config.cpp
Função

Define parâmetros ao criar threads usando std::thread, mas aplicando configurações do ESP-IDF:

nome da thread

prioridade

core destino

tamanho de stack

herança de configuração

Exemplo de uso
Task::Config()
  .with_name("Music Task")
  .with_priority(3)
  .pinned_to_core(0)
  .with_stack_size(8*1024);

4.2 task/Query.h & Query.cpp
Função

Consultar informações da thread atual ou da configuração pthread.

this_thread API

name()

core()

priority()

free_stack()

pthread API

name()

core()

priority()

stack_size()

4.3 task/Aperiodic.hpp
Função

Permite criar uma tarefa que roda somente quando uma interrupção ocorre.

Como funciona

Usa um semáforo (trigger_sem)

A ISR libera o semáforo

A thread associada executa o callback

Uso no projeto

Cada botão cria uma tarefa aperiódica:

auto button1_handler = Task::Aperiodic<Button1>([](){ music_chosen = REGULAR; });

4.4 task/Periodic.hpp
Função

Cria uma tarefa periódica que roda a cada intervalo fornecido.

Exemplo
Task::Periodic(200ms, [](){ tocar_nota(); });


No projeto:

Uma tarefa periódica lê a música atual

Envia a frequência ao buzzer via PWM

Avança para a próxima nota

5. Utils
5.1 Frequency.h
Função

Representa uma frequência em Hz.

Conversões

para uint32_t

para std::chrono::milliseconds (período = 1000/freq)

5.2 Percentage.h
Função

Representa valores decimais de duty-cycle.

Suporta literal:

50_percent  // vira 0.50

5.3 print.hpp
Função

Imprime texto colorido no terminal usando std::print().

🔌 Pinos Utilizados no Projeto
Função	Pino	Modo
Buzzer PWM	GPIO 23	Saída PWM
Botão 1	GPIO 18	Entrada, pull-up, FALLING
Botão 2	GPIO 19	Entrada, pull-up, FALLING
🎵 Funcionamento Geral do Código

Inicializa o PWM no pino 23 para controlar o buzzer.

Carrega músicas definidas em Song.h.

Cria uma tarefa periódica que:

lê a música selecionada

atualiza o PWM para tocar cada nota

Cria duas tarefas aperiódicas ligadas a interrupções:

Botão 1 → troca para música Regular

Botão 2 → troca para música Underworld

O sistema permanece em execução no loop infinito.
