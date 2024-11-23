import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor
from esphome.const import (
    CONF_TEMPERATURE,
    CONF_ILLUMINANCE,
    CONF_MOISTURE,
    CONF_CONDUCTIVITY,
    DEVICE_CLASS_MOISTURE,
    DEVICE_CLASS_TEMPERATURE,
    DEVICE_CLASS_ILLUMINANCE,
    STATE_CLASS_MEASUREMENT,
    UNIT_CELSIUS,
    UNIT_PERCENT,
    UNIT_LUX,
    UNIT_MICROSIEMENS_PER_CENTIMETER,
    ICON_THERMOMETER,
    ICON_WATER_PERCENT,
    ICON_FLOWER
)
from .. import miot  # pylint: disable=relative-beyond-top-level

AUTO_LOAD = ["miot"]
CODEOWNERS = ["@mbronk"]

ICON_SUN = "mdi:sun-wireless-outline"

miot_miflora_ns = cg.esphome_ns.namespace("miot_miflora")
MiotPlantSensor = miot_miflora_ns.class_("MiotMiFlora", miot.MiotComponent)

CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(MiotPlantSensor),
            cv.Optional(CONF_TEMPERATURE): sensor.sensor_schema(
                unit_of_measurement=UNIT_CELSIUS,
                accuracy_decimals=1,
                device_class=DEVICE_CLASS_TEMPERATURE,
                state_class=STATE_CLASS_MEASUREMENT,
                icon=ICON_THERMOMETER,
            ),
            cv.Optional(CONF_MOISTURE): sensor.sensor_schema(
                unit_of_measurement=UNIT_PERCENT,
                accuracy_decimals=0,
                device_class=DEVICE_CLASS_MOISTURE,
                state_class=STATE_CLASS_MEASUREMENT,
                icon=ICON_WATER_PERCENT,
            ),
            cv.Optional(CONF_ILLUMINANCE): sensor.sensor_schema(
                unit_of_measurement=UNIT_LUX,
                accuracy_decimals=0,
                device_class=DEVICE_CLASS_ILLUMINANCE,
                state_class=STATE_CLASS_MEASUREMENT,
                icon=ICON_SUN,
            ),
            cv.Optional(CONF_CONDUCTIVITY): sensor.sensor_schema(
                unit_of_measurement=UNIT_MICROSIEMENS_PER_CENTIMETER,
                accuracy_decimals=0,
                state_class=STATE_CLASS_MEASUREMENT,
                icon=ICON_FLOWER,
            )
        }
    )
    .extend(miot.MIOT_BLE_DEVICE_SCHEMA)
    .extend(cv.COMPONENT_SCHEMA)
)


async def to_code(config):
    """Code generation entry point"""
    var = await miot.new_device(config)
    if CONF_TEMPERATURE in config:
        sens = await sensor.new_sensor(config[CONF_TEMPERATURE])
        cg.add(var.set_temperature(sens))
    if CONF_MOISTURE in config:
        sens = await sensor.new_sensor(config[CONF_MOISTURE])
        cg.add(var.set_moisture(sens))
    if CONF_ILLUMINANCE in config:
        sens = await sensor.new_sensor(config[CONF_ILLUMINANCE])
        cg.add(var.set_illuminance(sens))
    if CONF_CONDUCTIVITY in config:
        sens = await sensor.new_sensor(config[CONF_CONDUCTIVITY])
        cg.add(var.set_conductivity(sens))
