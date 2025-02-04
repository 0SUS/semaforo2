#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"

// Definição dos pinos dos LEDs e botão
#define LED_RED 11
#define LED_YELLOW 12
#define LED_GREEN 13
#define BUTTON 5

//tempo de atraso
#define TIMER_DELAY_MS 3000

//estado do sistema
volatile bool is_running = false;
volatile absolute_time_t last_press_time;

//função de callback para desligar LEDs progressivamente
int led_state = 0;
bool led_callback(struct repeating_timer *t) {
    if (led_state == 1) {
        gpio_put(LED_RED, 0);
        printf("Estado 1: LED Vermelho desligado\n");
    } else if (led_state == 2) {
        gpio_put(LED_YELLOW, 0);
        printf("Estado 2: LED Amarelo desligado\n");
    } else if (led_state == 3) {
        gpio_put(LED_GREEN, 0);
        printf("Estado 3: LED Verde desligado\n");
        is_running = false;  // permite uma nova ativação do botão
    }

    led_state++;
    return false; //disparo unico entao nao repete
}

//callback do botão com debounce
void button_callback(uint gpio, uint32_t events) {
    absolute_time_t now = get_absolute_time();
    if (absolute_time_diff_us(last_press_time, now) > 200000 && !is_running) { // 200ms debounce
        last_press_time = now;
        is_running = true;
        led_state = 1;

        // liga todos os LEDs
        gpio_put(LED_RED, 1);
        gpio_put(LED_YELLOW, 1);
        gpio_put(LED_GREEN, 1);
        printf("Todos os LEDs ligados!\n");

        // configura os temporizadores 
        add_alarm_in_ms(TIMER_DELAY_MS, (alarm_callback_t)led_callback, NULL, false);
        add_alarm_in_ms(TIMER_DELAY_MS * 2, (alarm_callback_t)led_callback, NULL, false);
        add_alarm_in_ms(TIMER_DELAY_MS * 3, (alarm_callback_t)led_callback, NULL, false);
    }
}

int main() {
    stdio_init_all();

    // configuração dos LEDs
    gpio_init(LED_RED);
    gpio_set_dir(LED_RED, GPIO_OUT);
    gpio_init(LED_YELLOW);
    gpio_set_dir(LED_YELLOW, GPIO_OUT);
    gpio_init(LED_GREEN);
    gpio_set_dir(LED_GREEN, GPIO_OUT);

    // configuração do botão
    gpio_init(BUTTON);
    gpio_set_dir(BUTTON, GPIO_IN);
    gpio_pull_up(BUTTON);
    gpio_set_irq_enabled_with_callback(BUTTON, GPIO_IRQ_EDGE_FALL, true, &button_callback);

    last_press_time = get_absolute_time(); // inicializa tempo do debounce

    while (1) {
        sleep_ms(100);//pequeno atraso pra evitar sobrecarga
    }

    return 0;
}