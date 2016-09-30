#include <cartographie.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>
#include <libopencm3/stm32/timer.h>

#include <libopencm3/stm32/flash.h>
#include <libopencm3/stm32/exti.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/cm3/systick.h>
#include "cartographie.h"
#include <debug.h>

int x_actuel = 300;
int y_actuel = 1000;
void new_xy_absolu(int x, int y);

float float_get_x_actuel(){
    return x_actuel;
}
float float_get_y_actuel(){
    return y_actuel;

}
int get_theta_actuel(){
    return 0;
}

void set_trajectoire_xy_absolu(int x, int y) {
    new_xy_absolu(x, y);
}
void new_xy_absolu(int x, int y) {

    // On appelle le pathfinding et on regarde si il y a un chemin
    int longueur_chemin_trouve = pathfinding(x_actuel, y_actuel, x, y);

    if (longueur_chemin_trouve > 0) {
        debug(1, "Chemin trouvé de %d points\n", longueur_chemin_trouve);
        // On récupère le chemin lui-même
        int chemin_trouve[longueur_chemin_trouve][2];
        return_path_found(chemin_trouve);

        // On l'affiche
        gpio_set  (GPIOG, GPIO14);
        for (int i = 0; i < longueur_chemin_trouve; ++i) {
            //debug(1, "%d -- %d\n", chemin_trouve[i][0], chemin_trouve[i][1]);
            // gpio_set  (GPIOG, GPIO13);
            // for (int i = 0; i < 5000000; i++);
            // gpio_clear(GPIOG, GPIO13);
            // for (int i = 0; i < 5000000; i++);
        }
        gpio_clear(GPIOG, GPIO14);

        // Et on l'exécute !
        x_actuel = x;
        y_actuel = y;
    } else {
        debug(1, "Pas de chemin trouvé\n");
    }
    for (int i = 0; i < 500000; i++);
}




int main_blink(void) {
    rcc_clock_setup_hse_3v3(&rcc_hse_8mhz_3v3[RCC_CLOCK_3V3_168MHZ]);

    rcc_periph_clock_enable(RCC_GPIOA);
    rcc_periph_clock_enable(RCC_GPIOG);


    gpio_mode_setup(GPIOA, GPIO_MODE_INPUT, GPIO_PUPD_PULLDOWN, GPIO0); // Bouton User

    gpio_mode_setup(GPIOG, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,
        GPIO13 | GPIO14);

    pathfinding_init();

    nouvel_obstacle_rond(1500, 1200, 200);
    //while(1) {
        gpio_toggle(GPIOG, GPIO13);
        new_xy_absolu(2700,1600);
    //}
    // new_xy_absolu(300,1600);
    // new_xy_absolu(2700,1600);


    while (1) {
        if (gpio_get(GPIOA, GPIO0)) {
            gpio_set  (GPIOG,  GPIO14);
        } else {
            gpio_clear(GPIOG,  GPIO14);

        }

    }
}


int main() {
    main_mandel();
}
