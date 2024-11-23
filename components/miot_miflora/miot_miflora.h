#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "../miot/miot.h"

namespace esphome
{
  namespace miot_miflora
  {

    class MiotMiFlora : public miot::MiotComponent
    {
    public:
      void dump_config() override;

      void set_temperature(sensor::Sensor *temperature) { temperature_ = temperature; }
      void set_moisture(sensor::Sensor *moisture) { moisture_ = moisture; }
      void set_conductivity(sensor::Sensor *conductivity) { conductivity_ = conductivity; }
      void set_illuminance(sensor::Sensor *illuminance) { illuminance_ = illuminance; }

    protected:
      sensor::Sensor *temperature_{nullptr};
      sensor::Sensor *moisture_{nullptr};
      sensor::Sensor *conductivity_{nullptr};
      sensor::Sensor *illuminance_{nullptr};

      bool process_object_(const miot::BLEObject &obj) override;

      void process_temperature_(const miot::BLEObject &obj);
      void process_moisture_(const miot::BLEObject &obj);
      void process_conductivity_(const miot::BLEObject &obj);
      void process_illuminance_(const miot::BLEObject &obj);
    };

  } // namespace miot_miflora
} // namespace esphome
