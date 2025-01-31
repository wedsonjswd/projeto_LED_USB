#include <stdio.h>
#include "pico/stdlib.h"

#define LED_PIN 12  // Definição do pino do LED

int controle_getchar()
{
     int c = getchar();  // Bloqueia a execução até o usuário digitar algo

        if (c == '1') {
            gpio_put(LED_PIN, 1);
            printf("LED Ligado!\n");
        } else if (c == '0') {
            gpio_put(LED_PIN, 0);
            printf("LED Desligado!\n");
        } else {
            printf("Entrada inválida! Digite '1' ou '0'.\n");
        }
}

int controle_getchar_timeout()
{
    if (stdio_usb_connected()) 
        {  
            // Verifica se o USB está conectado
            
            int c = getchar_timeout_us(1000000); // Aguarda entrada do usuário
            /*
                Diferente de getchar(), que bloqueia a execução até que o usuário insira um caractere, 
                getchar_timeout_us() permite que o código continue rodando se nada for digitado.
            */
            if (c != PICO_ERROR_TIMEOUT) 
            {
                printf("Caractere recebido: %c\n", c);
                if (c == '1') 
                {
                    gpio_put(LED_PIN, 1);
                    printf("LED Ligado!\n");
                } 
            
                else if (c == '0') 
                {
                    gpio_put(LED_PIN, 0);
                    printf("LED Desligado!\n");
                }
            } 
            else 
            {
                printf("Nenhuma entrada recebida em 1 segundo.\n");
            }
        }
}


int main() 
{
    stdio_init_all();  // Inicializa a comunicação serial
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    printf("Sistema iniciado. Digite '1' para ligar o LED e '0' para desligar.\n");


    while (true) 
    {
            //controle_getchar();
            controle_getchar_timeout();
    }
}
