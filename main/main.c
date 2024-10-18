#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_adc/adc_oneshot.h"  // Include the new ADC oneshot driver
#include "esp_system.h"

// Define soil moisture sensor pin
#define SOIL_MOISTURE_PIN ADC_CHANNEL_0 // GPIO0 (D3) is connected to ADC_CHANNEL_0

void app_main(void)
{
    // ADC configuration structures
    adc_oneshot_unit_handle_t adc1_handle;
    adc_oneshot_unit_init_cfg_t init_config = {
        .unit_id = ADC_UNIT_1,
    };
    adc_oneshot_chan_cfg_t channel_config = {
        .atten = ADC_ATTEN_DB_11,
        .bitwidth = ADC_BITWIDTH_12,
    };

    // Initialize the ADC unit and configure the channel
    adc_oneshot_new_unit(&init_config, &adc1_handle);
    adc_oneshot_config_channel(adc1_handle, SOIL_MOISTURE_PIN, &channel_config);

    while (1)
    {
        int soil_moisture_value;
        // Read the soil moisture value from the ADC channel
        adc_oneshot_read(adc1_handle, SOIL_MOISTURE_PIN, &soil_moisture_value);
        
        // Print the value to the serial monitor
        printf("Soil Moisture Value: %d\n", soil_moisture_value);
        
        // Delay for 500 milliseconds
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }

    // Cleanup (unreachable in this loop, but good practice in other cases)
    adc_oneshot_del_unit(adc1_handle);
}
