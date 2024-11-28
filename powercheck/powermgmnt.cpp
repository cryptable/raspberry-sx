/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "pico/binary_info.h"
#include "powerdisplay.hpp"

#define  WAIT_UNTIL_POWERDOWN_IN_MS 10000
#define  POWERDOWN_PIN              14
#define  POWERDOWN_BUTTON_PIN       2
#define  POWERDOWN_PI_PIN           3

#define  INA3221_SDA                0
#define  INA3221_SCL                1

#define  INA3221_CRIT               11
#define  INA3221_WARN               10
#define  INA3221_PV                 12


// Powerdown to stop RP2040
bool done = false;
Powerdisplay *p_display = NULL;
int timer = WAIT_UNTIL_POWERDOWN_IN_MS / 1000;

int64_t alarm_powerdown(alarm_id_t id, void *user_data);

void gpio_irq_powerdown(uint gpio, uint32_t event_mask);

// I2C reserves some addresses for special purposes. We exclude these from the scan.
// These are any addresses of the form 000 0xxx or 111 1xxx
bool reserved_addr(uint8_t addr) {
    return (addr & 0x78) == 0 || (addr & 0x78) == 0x78;
}

int main() {
    i2c_init(i2c_default, 100 * 1000);
    gpio_set_function(INA3221_SDA, GPIO_FUNC_I2C);
    gpio_set_function(INA3221_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(INA3221_SDA);
    gpio_pull_up(INA3221_SCL);

    gpio_init(POWERDOWN_PIN);
    gpio_set_dir(POWERDOWN_PIN, GPIO_OUT);
//    gpio_pull_up(POWERDOWN_PIN);
    gpio_put(POWERDOWN_PIN,1);


    gpio_init(INA3221_PV);
    gpio_set_dir(INA3221_PV, GPIO_IN);
    gpio_pull_up(INA3221_PV);

    gpio_init(INA3221_CRIT);
    gpio_set_dir(INA3221_CRIT, GPIO_IN);
    gpio_pull_up(INA3221_CRIT);

    gpio_init(INA3221_WARN);
    gpio_set_dir(INA3221_WARN, GPIO_IN);
    gpio_pull_up(INA3221_WARN);

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
    p_display->powerdata(12.5, 2.45, 5.02, 4.44);
    while (!done) {
 //       tight_loop_contents();

    // BEGIN : I2C scan
    // Enable UART so we can print status output
    stdio_init_all();
    // Make the I2C pins available to picotool
    bi_decl(bi_2pins_with_func(PICO_DEFAULT_I2C_SDA_PIN, PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C));
    
    printf("\nI2C Bus Scan\n");
    printf("   0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F\n");

    for (int addr = 0; addr < (1 << 7); ++addr) {
        if (addr % 16 == 0) {
            printf("%02x ", addr);
        }

        // Perform a 1-byte dummy read from the probe address. If a slave
        // acknowledges this address, the function returns the number of bytes
        // transferred. If the address byte is ignored, the function returns
        // -1.

        // Skip over any reserved addresses.
        int ret;
        uint8_t rxdata;
        if (reserved_addr(addr))
            ret = PICO_ERROR_GENERIC;
        else
            ret = i2c_read_blocking(i2c_default, addr, &rxdata, 1, false);

        printf(ret < 0 ? "." : "@");
        printf(addr % 16 == 15 ? "\n" : "  ");
    }
    printf("Done.\n");
    // END I2C scan

    sleep_ms(1000);
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

