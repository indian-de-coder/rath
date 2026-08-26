#include "Battery.hpp"
#include "esp_adc/adc_oneshot.h"
#include "esp_adc/adc_cali.h"
#include "esp_adc/adc_cali_scheme.h"
#include "esp_err.h"
#include <stdio.h>

Battery::Battery()
{
    adc_oneshot_unit_init_cfg_t init_config = {};
    init_config.unit_id = ADC_UNIT_1;
    init_config.clk_src = ADC_RTC_CLK_SRC_DEFAULT;
    init_config.ulp_mode = ADC_ULP_MODE_DISABLE;


    esp_err_t err;

    err = adc_oneshot_new_unit(&init_config, &adc_handle);
    printf("ADC init: %s\n", esp_err_to_name(err));

    
    adc_oneshot_chan_cfg_t config = {};
    config.bitwidth = ADC_BITWIDTH_DEFAULT;
    config.atten = ADC_ATTEN_DB_12;

    err = adc_oneshot_config_channel(adc_handle, ADC_CHANNEL_6, &config);
    printf("ADC config: %s\n", esp_err_to_name(err));

    adc_cali_line_fitting_config_t cali_config = {};

    cali_config.unit_id = ADC_UNIT_1;
    cali_config.atten = ADC_ATTEN_DB_12;
    cali_config.bitwidth = ADC_BITWIDTH_DEFAULT;

    esp_err_t cali_err = adc_cali_create_scheme_line_fitting( &cali_config, &adc_cali_handle);

    printf("ADC calibration: %s\n", esp_err_to_name(cali_err));
}

float Battery::getVoltage()
{
    int raw;
    int adc_voltage_mv;

    adc_oneshot_read(adc_handle, ADC_CHANNEL_6, &raw);
    adc_cali_raw_to_voltage( adc_cali_handle, raw, &adc_voltage_mv);

    int battery_mv = adc_voltage_mv * 2;
    float battery_voltage = battery_mv / 1000.0f;
    return battery_voltage;
}

// Need Improvement
float Battery::getPercentage()
{
    float voltage = getVoltage();
    // FM5324 battery characteristics
    
    float min_voltage = 3.0f;  // Minimum voltage for 0%
    float max_voltage = 4.2f;  // Maximum voltage for 100%

    if (voltage <= min_voltage) {
        return 0.0f;
    } else if (voltage >= max_voltage) {
        return 100.0f;
    } else {
        return ((voltage - min_voltage) / (max_voltage - min_voltage)) * 100.0f;
    }
}