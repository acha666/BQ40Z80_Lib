#ifdef __cplusplus
extern "C"
{
#endif

#include "bq40z80.h"

    BQ40Z80::BQ40Z80(uint8_t i2c_scl_io, uint8_t i2c_sda_io, i2c_port_t i2c_master_num, uint8_t device_address)
    {
        this->DEVICE_ADDRESS = device_address;
        this->I2C_MASTER_NUM = i2c_master_num;

        i2c_config_t conf;
        conf.mode = I2C_MODE_MASTER;
        conf.sda_io_num = i2c_sda_io;
        conf.scl_io_num = i2c_scl_io;
        conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
        conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
        conf.master.clk_speed = I2C_MASTER_FREQ_HZ;
        conf.clk_flags = I2C_SCLK_SRC_FLAG_FOR_NOMAL;

        ESP_ERROR_CHECK(i2c_param_config(i2c_master_num, &conf));

        ESP_ERROR_CHECK(i2c_driver_install(i2c_master_num, conf.mode, I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0));
    }

    BQ40Z80::~BQ40Z80()
    {
        i2c_driver_delete(this->I2C_MASTER_NUM);
    }

    /***************************** Public Functions *****************************/
    uint16_t BQ40Z80::get_battery_mode()
    {
        uint16_t buf;
        ESP_ERROR_CHECK(this->smbus_read_word(BQ40Z80_SBS_BatteryMode, &buf));
        return buf;
    }

    void BQ40Z80::set_battery_mode(u_int16_t val)
    {
        ESP_ERROR_CHECK(this->smbus_write_word(BQ40Z80_SBS_BatteryMode, val));
        // this->update_basic_info();
    }

    uint16_t BQ40Z80::get_temperature()
    {
        uint16_t buf;
        ESP_ERROR_CHECK(this->smbus_read_word(BQ40Z80_SBS_Current, &buf));
        return buf - 2732; // raw data unit: 0.1 Kelvin
    }

    uint16_t BQ40Z80::get_voltage()
    {
        uint16_t buf;
        ESP_ERROR_CHECK(this->smbus_read_word(BQ40Z80_SBS_Voltage, &buf));
        return buf;
    }

    uint16_t BQ40Z80::get_current()
    {
        uint16_t buf;
        ESP_ERROR_CHECK(this->smbus_read_word(BQ40Z80_SBS_Current, &buf));
        return buf;
    }

    uint8_t BQ40Z80::get_rsoc()
    {
        uint16_t buf;
        ESP_ERROR_CHECK(this->smbus_read_word(BQ40Z80_SBS_RelativeStateOfCharge, &buf));
        return buf;
    }

    uint16_t BQ40Z80::get_remaining_capacity()
    {
        uint16_t buf;
        ESP_ERROR_CHECK(this->smbus_read_word(BQ40Z80_SBS_RemainingCapacity, &buf));
        return buf;
    }

    uint16_t BQ40Z80::get_full_charge_capacity()
    {
        uint16_t buf;
        ESP_ERROR_CHECK(this->smbus_read_word(BQ40Z80_SBS_FullChargeCapacity, &buf));
        return buf;
    }

    uint16_t BQ40Z80::get_average_time_to_empty()
    {
        uint16_t buf;
        ESP_ERROR_CHECK(this->smbus_read_word(BQ40Z80_SBS_AverageTimeToEmpty, &buf));
        return buf;
    }

    uint16_t BQ40Z80::get_average_time_to_full()
    {
        uint16_t buf;
        ESP_ERROR_CHECK(this->smbus_read_word(BQ40Z80_SBS_AverageTimeToFull, &buf));
        return buf;
    }

    uint16_t BQ40Z80::get_cycle_count()
    {
        uint16_t buf;
        ESP_ERROR_CHECK(this->smbus_read_word(BQ40Z80_SBS_CycleCount, &buf));
        return buf;
    }

    uint16_t BQ40Z80::get_design_capacity()
    {
        uint16_t buf;
        ESP_ERROR_CHECK(this->smbus_read_word(BQ40Z80_SBS_DesignCapacity, &buf));
        return buf;
    }

    uint16_t BQ40Z80::get_design_voltage()
    {
        uint16_t buf;
        ESP_ERROR_CHECK(this->smbus_read_word(BQ40Z80_SBS_DesignVoltage, &buf));
        return buf;
    }

    uint16_t BQ40Z80::get_cell_voltage(uint8_t cell)
    {
        assert(1 <= cell && cell <= 7); //!< range check

        if (cell <= 4)
        {
            DA_STATUS_1 da_status_1_data;
            this->read_da_status_1(&da_status_1_data);
            switch (cell)
            {
            case 1:
                return da_status_1_data.cell_voltage_1;
                break;
            case 2:
                return da_status_1_data.cell_voltage_2;
                break;
            case 3:
                return da_status_1_data.cell_voltage_3;
                break;
            case 4:
                return da_status_1_data.cell_voltage_4;
            default:
                break;
            }
        }
        else
        {
            DA_STATUS_3 da_status_3_data;
            this->read_da_status_3(&da_status_3_data);
            switch (cell)
            {
            case 5:
                return da_status_3_data.cell_voltage_5;
                break;
            case 6:
                return da_status_3_data.cell_voltage_6;
                break;
            case 7:
                return da_status_3_data.cell_voltage_7;
                break;
            default:
                break;
            }
        }
        return 0;
    }

    void BQ40Z80::set_capm(bool val)
    {
        uint16_t buf = this->get_battery_mode();
        if (val)
            buf |= 0x8000;
        else
            buf &= 0x7fff;
        this->set_battery_mode(buf);
    }

    void BQ40Z80::read_da_status_1(DA_STATUS_1 *data)
    {
        uint8_t buf[32];

        ESP_ERROR_CHECK(this->mfa_read_block(BQ40Z80_MFA_DA_STATUS_1, buf, 32));

        data->cell_voltage_1 = (buf[1] << 8) | buf[0];
        data->cell_voltage_2 = (buf[3] << 8) | buf[2];
        data->cell_voltage_3 = (buf[5] << 8) | buf[4];
        data->cell_voltage_4 = (buf[7] << 8) | buf[6];
        data->bat_voltage = (buf[9] << 8) | buf[8];
        data->pack_voltage = (buf[11] << 8) | buf[10];
        data->cell_current_1 = (buf[13] << 8) | buf[12];
        data->cell_current_2 = (buf[15] << 8) | buf[14];
        data->cell_current_3 = (buf[17] << 8) | buf[16];
        data->cell_current_4 = (buf[19] << 8) | buf[18];
        data->cell_power_1 = (buf[21] << 8) | buf[20];
        data->cell_power_2 = (buf[23] << 8) | buf[22];
        data->cell_power_3 = (buf[25] << 8) | buf[24];
        data->cell_power_4 = (buf[27] << 8) | buf[26];
        data->power = (buf[29] << 8) | buf[28];
        data->average_power = (buf[31] << 8) | buf[30];

        return;
    }

    void BQ40Z80::read_da_status_3(DA_STATUS_3 *data)
    {
        uint8_t buf[18];

        ESP_ERROR_CHECK(this->mfa_read_block(BQ40Z80_MFA_DA_STATUS_3, buf, 18));

        data->cell_voltage_5 = (buf[1] << 8) | buf[0];
        data->cell_current_5 = (buf[3] << 8) | buf[2];
        data->cell_power_5 = (buf[5] << 8) | buf[4];
        data->cell_voltage_6 = (buf[7] << 8) | buf[6];
        data->cell_current_6 = (buf[9] << 8) | buf[8];
        data->cell_power_6 = (buf[11] << 8) | buf[10];
        data->cell_voltage_7 = (buf[13] << 8) | buf[12];
        data->cell_current_7 = (buf[15] << 8) | buf[14];
        data->cell_power_7 = (buf[17] << 8) | buf[16];

        return;
    }

    /***************************** Private Functions *****************************/

    esp_err_t BQ40Z80::smbus_read_word(uint8_t reg_addr, uint16_t *data)
    {
        esp_err_t err;
        uint8_t buf[2];

        err = i2c_master_write_read_device(this->I2C_MASTER_NUM, this->DEVICE_ADDRESS, &reg_addr, 1, buf, 2, I2C_MASTER_TIMEOUT_TICK);

        *data = (buf[1] << 8) | buf[0];

        return err;
    }

    esp_err_t BQ40Z80::smbus_write_word(uint8_t reg_addr, uint16_t data)
    {
        esp_err_t err;
        uint8_t buf[2];
        buf[0] = data & 0x00FF;
        buf[1] = data >> 8;

        i2c_cmd_handle_t cmd = i2c_cmd_link_create();
        i2c_master_start(cmd);
        i2c_master_write_byte(cmd, (this->DEVICE_ADDRESS << 1) | I2C_MASTER_WRITE, true);
        i2c_master_write_byte(cmd, reg_addr, true);
        i2c_master_write(cmd, buf, 2, true);
        i2c_master_stop(cmd);

        err = i2c_master_cmd_begin(this->I2C_MASTER_NUM, cmd, I2C_MASTER_TIMEOUT_TICK);
        i2c_cmd_link_delete(cmd);

        return err;
    }

    esp_err_t BQ40Z80::smbus_read_block(uint8_t reg_addr, uint8_t *data, uint8_t len)
    {
        esp_err_t err;
        uint8_t slave_len = 0;

        i2c_cmd_handle_t cmd = i2c_cmd_link_create();
        i2c_master_start(cmd);
        i2c_master_write_byte(cmd, this->DEVICE_ADDRESS << 1 | I2C_MASTER_WRITE, true);
        i2c_master_write_byte(cmd, reg_addr, true);
        i2c_master_start(cmd);
        i2c_master_write_byte(cmd, this->DEVICE_ADDRESS << 1 | I2C_MASTER_READ, true);
        i2c_master_read_byte(cmd, &slave_len, I2C_MASTER_ACK);
        err = i2c_master_cmd_begin(this->I2C_MASTER_NUM, cmd, I2C_MASTER_TIMEOUT_TICK);
        i2c_cmd_link_delete(cmd);

        if (len < slave_len)
        {
            ESP_LOGE("SMBus", "slave data length(%d) exceeds provided data length(%d)", slave_len, len);
            return ESP_ERR_INVALID_SIZE;
        }
        if (len > slave_len)
            ESP_LOGW("SMBus", "slave data length(%d) dosen't match provided data length(%d)", slave_len, len);

        if (err != ESP_OK)
            return err;

        cmd = i2c_cmd_link_create();
        i2c_master_read(cmd, data, slave_len, I2C_MASTER_LAST_NACK);
        i2c_master_stop(cmd);
        err = i2c_master_cmd_begin(this->I2C_MASTER_NUM, cmd, I2C_MASTER_TIMEOUT_TICK);
        i2c_cmd_link_delete(cmd);

        return err;
    }

    esp_err_t BQ40Z80::smbus_write_block(uint8_t reg_addr, uint8_t *data, uint8_t len)
    {
        esp_err_t err;

        i2c_cmd_handle_t cmd = i2c_cmd_link_create();
        i2c_master_start(cmd);
        i2c_master_write_byte(cmd, (this->DEVICE_ADDRESS << 1) | I2C_MASTER_WRITE, true);
        i2c_master_write_byte(cmd, reg_addr, true);
        i2c_master_write_byte(cmd, len, true);
        i2c_master_write(cmd, data, len, true);
        i2c_master_stop(cmd);

        err = i2c_master_cmd_begin(this->I2C_MASTER_NUM, cmd, I2C_MASTER_TIMEOUT_TICK);
        i2c_cmd_link_delete(cmd);

        return err;
    }

    esp_err_t BQ40Z80::mfa_read_block(uint16_t mfa_command, uint8_t *data, uint8_t len)
    {
        esp_err_t err;
        uint8_t command[2];
        command[0] = mfa_command & 0x00ff;
        command[1] = mfa_command >> 8;

        err = this->smbus_write_block(BQ40Z80_SBS_ManufacturerBlockAccess, command, 2);
        if (err != ESP_OK)
            return err;

        err = this->smbus_read_block(BQ40Z80_SBS_ManufacturerData, data, len);
        return err;
    }

#ifdef __cplusplus
}
#endif