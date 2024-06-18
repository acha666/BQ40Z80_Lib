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

typedef struct
{
    bool iata_cterm; //!< IATA charge control: 1 = Active, 0 = Inactive
    bool rsvd_30;    //!< Reserved. Do not use.
    bool emshut;     //!< Emergency FET shutdown: 1 = Active, 0 = Inactive
    bool cb;         //!< Cell balancing status: 1 = Active, 0 = Inactive
    bool slpcc;      //!< CC measurement in SLEEP mode: 1 = Active, 0 = Inactive
    bool slpad;      //!< ADC measurement in SLEEP mode: 1 = Active, 0 = Inactive
    bool smblcal;    //!< Auto CC calibration
    bool init;       //!< Initialization after full reset: 1 = Active, 0 = Inactive
    bool sleepm;     //!< SLEEP mode triggered via command: 1 = Active, 0 = Inactive
    bool xl;         //!< 400-kHz SMBus mode: 1 = Active, 0 = Inactive
    bool cal_offset; //!< Calibration output (raw CC offset data)
    bool cal;        //!< Calibration output (raw ADC and CC data)
    bool autocalm;   //!< Auto CC Offset calibration by the MAC AutoCCOffset(): 1 = Calibration ongoing, 0 = Calibration completed
    bool auth;       //!< Authentication in progress: 1 = Active, 0 = Inactive
    bool led;        //!< LED Display: 1 = Display on, 0 = Display off
    bool sdm;        //!< Shutdown triggered via command: 1 = Active, 0 = Inactive
    bool sleep;      //!< SLEEP mode conditions met: 1 = Active, 0 = Inactive
    bool xchg;       //!< Charging disabled: 1 = Active, 0 = Inactive
    bool xdsg;       //!< Discharging disabled: 1 = Active, 0 = Inactive
    bool pf;         //!< PERMANENT FAILURE mode status: 1 = Active, 0 = Inactive
    bool ss;         //!< SAFETY status: 1 = Active, 0 = Inactive
    bool sdv;        //!< Shutdown triggered via low battery stack voltage: 1 = Active, 0 = Inactive
    bool sec1;       //!< SECURITY mode bit 1
    bool sec0;       //!< SECURITY mode bit 0
    bool btp_int;    //!< Battery trip point interrupt: 1 = Active, 0 = Inactive
    bool rsvd_6;     //!< Reserved. Do not use.
    bool fuse;       //!< Fuse status: 1 = Active, 0 = Inactive
    bool pdsg;       //!< Pre-discharge FET status: 1 = Active, 0 = Inactive
    bool pchg;       //!< Precharge FET status: 1 = Active, 0 = Inactive
    bool chg;        //!< CHG FET status: 1 = Active, 0 = Inactive
    bool dsg;        //!< DSG FET status: 1 = Active, 0 = Inactive
    bool pres;       //!< System present low: 1 = Active, 0 = Inactive
} OPERATION_STATUS;

typedef struct
{
    // Charging Status Flags (Bits 23–8)
    bool rsvd_23; //!< Reserved. Do not use.
    bool rsvd_22; //!< Reserved. Do not use.
    bool rsvd_21; //!< Reserved. Do not use.
    bool rsvd_20; //!< Reserved. Do not use.
    bool nct;     //!< Near charge termination: 1 = Active, 0 = Inactive
    bool ccc;     //!< Charging loss compensation: 1 = Active, 0 = Inactive
    bool cvr;     //!< Charging voltage rate of change: 1 = Active, 0 = Inactive
    bool ccr;     //!< Charging current rate of change: 1 = Active, 0 = Inactive
    bool vct;     //!< Charge termination: 1 = Active, 0 = Inactive
    bool mchg;    //!< Maintenance charge: 1 = Active, 0 = Inactive
    bool su;      //!< Suspend charge: 1 = Active, 0 = Inactive
    bool in;      //!< Charge inhibit: 1 = Active, 0 = Inactive
    bool hv;      //!< High voltage region: 1 = Active, 0 = Inactive
    bool mv;      //!< Mid voltage region: 1 = Active, 0 = Inactive
    bool lv;      //!< Low voltage region: 1 = Active, 0 = Inactive
    bool pv;      //!< Precharge voltage region: 1 = Active, 0 = Inactive

    // Temperature Range Flags (Bits 7–0)
    bool rsvd_7; //!< Reserved. Do not use.
    bool ot;     //!< Overtemperature region: 1 = Active, 0 = Inactive
    bool ht;     //!< High temperature region: 1 = Active, 0 = Inactive
    bool sth;    //!< Standard temperature high region: 1 = Active, 0 = Inactive
    bool rt;     //!< Recommended temperature region: 1 = Active, 0 = Inactive
    bool stl;    //!< Standard temperature low region: 1 = Active, 0 = Inactive
    bool lt;     //!< Low temperature region: 1 = Active, 0 = Inactive
    bool ut;     //!< Undertemperature region: 1 = Active, 0 = Inactive
} CHARGING_STATUS;

#endif