/*
  Based on: https://github.com/wmbusmeters/wmbusmeters
  Copyright (C) 2021-2024 Fredrik Öhrström (gpl-3.0-or-later)
*/

#pragma once

#include "driver.h"

#include <vector>
#include <string>

struct LseWaterMeter : Driver
{
    LseWaterMeter(std::string key = "") : Driver(std::string("lse_07_17"), key) {};

    virtual esphome::optional<std::map<std::string, double>> get_values(std::vector<unsigned char> &telegram) override {
        std::map<std::string, double> ret_val{};

        // Fügen Sie die spezifischen Methoden hinzu, um die Werte zu extrahieren
        add_to_map(ret_val, "total_m3", this->get_total(telegram));
        add_to_map(ret_val, "due_date_m3", this->get_due_date_volume(telegram));
        add_to_map(ret_val, "due_date", this->get_due_date(telegram));
        add_to_map(ret_val, "error_code", this->get_error_code(telegram));
        add_to_map(ret_val, "error_date", this->get_error_date(telegram));
        add_to_map(ret_val, "device_date_time", this->get_device_date_time(telegram));
        add_to_map(ret_val, "timestamp", this->get_timestamp(telegram));

        if (ret_val.size() > 0) {
            return ret_val;
        } else {
            return {};
        }
    };
