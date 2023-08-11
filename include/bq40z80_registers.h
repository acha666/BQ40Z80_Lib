#ifndef __BQ40Z80_REGISTERS_H
#define __BQ40Z80_REGISTERS_H

#include <esp_types.h>

typedef struct
{
    uint16_t cell_voltage_1; //!< Cell Voltage 1 (mV)
    uint16_t cell_voltage_2; //!< Cell Voltage 2 (mV)
    uint16_t cell_voltage_3; //!< Cell Voltage 3 (mV)
    uint16_t cell_voltage_4; //!< Cell Voltage 4 (mV)
    uint16_t bat_voltage;    //!< BAT Voltage. Voltage at the BAT pin. Different from Voltage() which is the sum of all cell voltages (mV)
    uint16_t pack_voltage;   //!< PACK Voltage. Voltage at the PACK+ pin. (mV)
    uint16_t cell_current_1; //!< Cell Current 1. Simultaneous current measured during Cell Voltage 1 measurement (mA)
    uint16_t cell_current_2; //!< Cell Current 2. Simultaneous current measured during Cell Voltage 2 measurement (mA)
    uint16_t cell_current_3; //!< Cell Current 3. Simultaneous current measured during Cell Voltage 3 measurement (mA)
    uint16_t cell_current_4; //!< Cell Current 4. Simultaneous current measured during Cell Voltage 4 measurement (mA)
    uint16_t cell_power_1;   //!< Cell Power 1. Calculated using Cell Voltage1 and Cell Current 1 data (cW)
    uint16_t cell_power_2;   //!< Cell Power 2. Calculated using Cell Voltage2 and Cell Current 2 data (cW)
    uint16_t cell_power_3;   //!< Cell Power 3. Calculated using Cell Voltage3 and Cell Current 3 data (cW)
    uint16_t cell_power_4;   //!< Cell Power 4. Calculated using Cell Voltage4 and Cell Current 4 data (cW)
    uint16_t power;          //!< Power calculated by Voltage() × Current() (cW)
    uint16_t average_power;  //!< Average Power (cW)
} DA_STATUS_1;

typedef struct
{
    uint16_t int_temperature;     //!< Int Temperature (0.1 K)
    uint16_t ts1_temperature;     //!< TS1 Temperature (0.1 K)
    uint16_t ts2_temperature;     //!< TS2 Temperature (0.1 K)
    uint16_t ts3_temperature;     //!< TS3 Temperature (0.1 K)
    uint16_t ts4_temperature;     //!< TS4 Temperature (0.1 K)
    uint16_t cell_temperature;    //!< Cell Temperature (0.1 K)
    uint16_t fet_temperature;     //!< FET Temperature (0.1 K)
    uint16_t gauging_temperature; //!< Gauging Temperature (0.1 K)
} DA_STATUS_2;

typedef struct
{
    uint16_t cell_voltage_5; //!< Cell Voltage 5 (mV)
    uint16_t cell_voltage_6; //!< Cell Voltage 6 (mV)
    uint16_t cell_voltage_7; //!< Cell Voltage 7 (mV)
    uint16_t cell_current_5; //!< Cell Current 5. Simultaneous current measured during Cell Voltage 5 measurement (mA)
    uint16_t cell_current_6; //!< Cell Current 6. Simultaneous current measured during Cell Voltage 6 measurement (mA)
    uint16_t cell_current_7; //!< Cell Current 7. (mA)
    uint16_t cell_power_5;   //!< Cell Power 5. Calculated using Cell Voltage 5 and Cell Current 5 data (cW)
    uint16_t cell_power_6;   //!< Cell Power 6. Calculated using Cell Voltage 6 and Cell Current 6 data (cW)
    uint16_t cell_power_7;   //!< Cell Power 7. Calculated using Cell Voltage 7 and Cell Current 7 data (cW)
} DA_STATUS_3;

#endif