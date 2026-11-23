#include "driver_power.h"
#include "bsp_adc.h"
#include "bsp_core.h"

/* =========================================
 * 驱动核心函数
 * ========================================= */

bool Driver_Power_Init(void)
{
    // ADC 硬件 (ADC1 扫描 + DMA) 由 bsp_adc_init_default() 在 main 硬件初始化阶段统一完成，
    // 本驱动只负责电压/电流的读取与换算
    return true;
}

float Driver_Power_GetVoltage(void)
{
    // 满量程 4096 对应 3.3V 内部基准，分压系数为 11
    uint16_t raw = bsp_adc_read_raw(BSP_ADC_VOLTAGE);

    return (((float)raw / 4096.0f) * 3.3f * 11.667f + 0.2);
}

float Driver_Power_GetCurrent(void)
{
    // 满量程 4096 对应 3.3V 内部基准
    uint16_t raw = bsp_adc_read_raw(BSP_ADC_CURRENT);
    float voltage_i = ((float)raw / 4096.0f) * 3.3f;

    // 电流解算公式：10 * (测量电压 - 2.5V 偏移)
    return 25.0f * (voltage_i - 0.124f);
}
