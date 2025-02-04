#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"

#define LED_VERDE 11
#define LED_AZUL 12
#define LED_VERMELHO 13
#define BOTAO 5

volatile bool ciclo_em_andamento = false;

int64_t desligar_led_azul(alarm_id_t id, void *user_data);
int64_t desligar_led_vermelho(alarm_id_t id, void *user_data);
int64_t desligar_led_verde(alarm_id_t id, void *user_data);

// Callback para iniciar a sequência de LEDs
void iniciar_sequencia() {
    if (!ciclo_em_andamento) {
        ciclo_em_andamento = true;
        printf("Temporizador Iniciado\n");  // Mensagem indicando que o temporizador foi iniciado
        gpio_put(LED_VERDE, 1);
        gpio_put(LED_AZUL, 1);
        gpio_put(LED_VERMELHO, 1);
        add_alarm_in_ms(3000, desligar_led_azul, NULL, false);
    }
}

// Callbacks para desligar LEDs em sequência
int64_t desligar_led_azul(alarm_id_t id, void *user_data) {
    gpio_put(LED_AZUL, 0);
    add_alarm_in_ms(3000, desligar_led_vermelho, NULL, false);
    return 0;
}

int64_t desligar_led_vermelho(alarm_id_t id, void *user_data) {
    gpio_put(LED_VERMELHO, 0);
    add_alarm_in_ms(3000, desligar_led_verde, NULL, false);
    return 0;
}

int64_t desligar_led_verde(alarm_id_t id, void *user_data) {
    gpio_put(LED_VERDE, 0);
    ciclo_em_andamento = false;
    printf("Temporizador Finalizado\n");  // Mensagem indicando que o temporizador foi finalizado
    return 0;
}

// Função de debounce do botão
bool debounce_botao() {
    static uint32_t ultimo_tempo = 0;
    uint32_t tempo_atual = to_ms_since_boot(get_absolute_time());
    if (tempo_atual - ultimo_tempo > 200) {  // 200ms de debounce
        ultimo_tempo = tempo_atual;
        return true;
    }
    return false;
}

// Interrupção do botão
void botao_callback(uint gpio, uint32_t events) {
    if (debounce_botao()) {
        iniciar_sequencia();
    }
}

int main() {
    stdio_init_all();
    
    gpio_init(LED_VERDE);
    gpio_set_dir(LED_VERDE, GPIO_OUT);
    gpio_init(LED_AZUL);
    gpio_set_dir(LED_AZUL, GPIO_OUT);
    gpio_init(LED_VERMELHO);
    gpio_set_dir(LED_VERMELHO, GPIO_OUT);
    
    gpio_init(BOTAO);
    gpio_set_dir(BOTAO, GPIO_IN);
    gpio_pull_up(BOTAO);
    gpio_set_irq_enabled_with_callback(BOTAO, GPIO_IRQ_EDGE_RISE, true, &botao_callback);
    
    while (1) {
        sleep_ms(100);
    }
}