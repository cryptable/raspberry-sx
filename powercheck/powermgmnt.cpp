/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "pico/stdlib.h"
#include "powerdisplay.hpp"

#define  WAIT_UNTIL_POWERDOWN_IN_MS 10000
#define  POWERDOWN_PIN              2
#define  POWERDOWN_BUTTON_PIN       3
#define  POWERDOWN_PI_PIN           4

// Powerdown to stop RP2040
bool done = false;
Powerdisplay *p_display = NULL;
int timer = WAIT_UNTIL_POWERDOWN_IN_MS / 1000;

int64_t alarm_powerdown(alarm_id_t id, void *user_data);

void gpio_irq_powerdown(uint gpio, uint32_t event_mask);

int main() {
    gpio_init(POWERDOWN_PIN);
    gpio_set_dir(POWERDOWN_PIN, GPIO_OUT);
    gpio_put(POWERDOWN_PIN, 1);

    gpio_init(POWERDOWN_BUTTON_PIN);
    gpio_set_dir(POWERDOWN_BUTTON_PIN, GPIO_IN);
    gpio_set_pulls(POWERDOWN_BUTTON_PIN, true, false);
    gpio_set_irq_enabled_with_callback(POWERDOWN_BUTTON_PIN, GPIO_IRQ_EDGE_FALL, true, gpio_irq_powerdown);

    gpio_init(POWERDOWN_PI_PIN);
    gpio_set_dir(POWERDOWN_PI_PIN, GPIO_OUT);
    gpio_put(POWERDOWN_PI_PIN, 0);

    // Display
    auto display = Powerdisplay();
    p_display = &display;

    while (!done) {
        tight_loop_contents();
    }

    return 0;
}

int64_t alarm_powerdown(alarm_id_t id, void *user_data) {
    if (timer < 0) {
        gpio_put(POWERDOWN_PIN, 0);
        done = true;
        return 0;
    }

    char text[3]={0x00};
    sprintf(text,"%d",timer);
    p_display->countdown(text);
    timer--;
    add_alarm_in_ms(1000, alarm_powerdown, NULL, false);

    return 0;
}

void gpio_irq_powerdown(uint gpio, uint32_t event_mask) {
    add_alarm_in_ms(1000, alarm_powerdown, NULL, false);
    gpio_put(POWERDOWN_PI_PIN, 1);
}

