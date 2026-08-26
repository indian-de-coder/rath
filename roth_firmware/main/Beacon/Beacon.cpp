#include "Beacon.hpp"

#include "driver/gpio.h"

#define BEACON_LED GPIO_NUM_2

Beacon::Beacon()
{
    gpio_reset_pin(BEACON_LED);
    gpio_set_direction(BEACON_LED, GPIO_MODE_OUTPUT);

    off();
}

void Beacon::on()
{
    gpio_set_level(BEACON_LED, 1);
}

void Beacon::off()
{
    gpio_set_level(BEACON_LED, 0);
}

