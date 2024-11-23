#include "esphome/core/log.h"
#include "miot_miflora.h"

#if ESPHOME_LOG_LEVEL >= ESPHOME_LOG_LEVEL_DEBUG
#define CHECK_MIID_LOCAL(miid)                                                        \
  if (obj.id != miid)                                                                 \
  {                                                                                   \
    ESP_LOGW(TAG, "BLEObject.id %04X does not match %04X (" #miid ")", obj.id, miid); \
    return;                                                                           \
  }
#else
#define CHECK_MIID_LOCAL(miid)
#endif

namespace esphome
{
  namespace miot_miflora
  {

    static const char *const TAG = "miot_miflora";

    void MiotMiFlora::dump_config()
    {
      this->dump_config_(TAG, "TH");
      LOG_SENSOR("  ", "Temperature", this->temperature_);
      LOG_SENSOR("  ", "Moisture", this->moisture_);
      LOG_SENSOR("  ", "Conductivity", this->conductivity_);
      LOG_SENSOR("  ", "Illuminance", this->illuminance_);
    }

    void MiotMiFlora::process_temperature_(const miot::BLEObject &obj)
    {
      if (this->temperature_ != nullptr)
      {
        const auto temperature = obj.get_temperature();
        if (temperature.has_value())
        {
          this->temperature_->publish_state(*temperature);
        }
      }
    }

    void MiotMiFlora::process_moisture_(const miot::BLEObject &obj)
    {
      if (this->moisture_ != nullptr)
      {
        CHECK_MIID_LOCAL(miot::MIID_SOIL_MOISTURE);
        const auto moisture = obj.get_uint8();
        if (moisture.has_value())
        {
          ESP_LOGD(TAG, "Soil Moisture %" PRIu8 " %%", *moisture);
          this->moisture_->publish_state(*moisture);
        }
      }
    }

    void MiotMiFlora::process_conductivity_(const miot::BLEObject &obj)
    {
      if (this->conductivity_ != nullptr)
      {
        CHECK_MIID_LOCAL(miot::MIID_CONDUCTIVITY);
        const auto conductivity = obj.get_uint16();
        if (conductivity.has_value())
        {
          ESP_LOGD(TAG, "Soil Conductivity %" PRIu16 " µS/cm", *conductivity);
          this->conductivity_->publish_state(*conductivity);
        }
      }
    }

    void MiotMiFlora::process_illuminance_(const miot::BLEObject &obj)
    {
      if (this->illuminance_ != nullptr)
      {
        const auto illuminance = obj.get_illuminance();
        if (illuminance.has_value())
        {
          this->illuminance_->publish_state(*illuminance);
        }
      }
    }

    bool MiotMiFlora::process_object_(const miot::BLEObject &obj)
    {
      switch (obj.id)
      {
      case miot::MIID_TEMPERATURE:
        this->process_temperature_(obj);
        break;

      case miot::MIID_SOIL_MOISTURE:
        this->process_moisture_(obj);
        break;

      case miot::MIID_CONDUCTIVITY:
        this->process_conductivity_(obj);
        break;

      case miot::MIID_ILLUMINANCE:
        this->process_illuminance_(obj);
        break;

      default:
        return this->process_default_(obj);
      }
      return true;
    }

  } // namespace miot_miflora
} // namespace esphome
