# semaforo2
# README - Controle de LEDs com Temporizador no Raspberry Pi Pico

## Descrição
Este programa controla três LEDs (vermelho, amarelo e verde) conectados ao Raspberry Pi Pico. Quando o botão é pressionado, todos os LEDs acendem simultaneamente e, após intervalos de 3 segundos, eles se apagam progressivamente até que todos estejam desligados. Durante o ciclo de desligamento, novas ativações do botão são bloqueadas.

## Requisitos
- Placa **Raspberry Pi Pico**
- Três LEDs conectados às GPIOs:
  - **LED Vermelho** → GPIO 11
  - **LED Amarelo** → GPIO 12
  - **LED Verde** → GPIO 13
- Um botão de pressão (pushbutton) conectado à **GPIO 5** com resistor pull-up interno ativado
- Ferramenta de desenvolvimento **BitDogLab** (opcional)
- SDK do Raspberry Pi Pico instalado

## Como Compilar e Executar
1. Clone ou copie este repositório para seu ambiente de desenvolvimento.
2. Compile o código utilizando o **SDK do Pico** e gere o arquivo UF2.
3. Conecte o Raspberry Pi Pico ao computador em **modo bootloader**.
4. Arraste e solte o arquivo UF2 no dispositivo **RPI-RP2**.
5. O código será executado automaticamente após o upload.

## Funcionamento
1. O programa inicia com todos os LEDs apagados.
2. Quando o botão (GPIO 5) é pressionado:
   - Todos os LEDs acendem.
   - Após 3 segundos, o **LED vermelho** apaga.
   - Após mais 3 segundos, o **LED amarelo** apaga.
   - Após mais 3 segundos, o **LED verde** apaga.
3. O botão só pode ser pressionado novamente após o último LED ser desligado.
4. A saída serial exibe mensagens indicando o estado atual do sistema.

## Observações
- **Debounce via software** foi implementado para evitar leituras falsas do botão.
- O temporizador de um disparo (`add_alarm_in_ms`) é utilizado para controlar a sequência de desligamento dos LEDs.
- A execução do programa pode ser monitorada por um terminal serial via `printf()`.

## Licença
Este código é fornecido sem garantia e pode ser utilizado para fins educacionais e experimentação no Raspberry Pi Pico.

