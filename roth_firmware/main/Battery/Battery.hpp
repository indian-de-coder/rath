#pragma once

#include "esp_adc/adc_oneshot.h"
#include "esp_adc/adc_cali.h"

class Battery
{
public:
    Battery();

    float getVoltage();
    float getPercentage();

private:
    adc_oneshot_unit_handle_t adc_handle;
    adc_cali_handle_t adc_cali_handle;
};