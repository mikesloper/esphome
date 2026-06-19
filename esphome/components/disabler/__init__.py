import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.const import CONF_ID
from esphome.core import coroutine_with_priority

CODEOWNERS = ["@esphome/core"]

preferences_ns = cg.esphome_ns.namespace("disabler")
Disabler = preferences_ns.class_("Disabler", cg.Component)

#CONF_FLASH_WRITE_INTERVAL = "flash_write_interval"
CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(Disabler),
        #cv.Optional(CONF_FLASH_WRITE_INTERVAL, default="60s"): cv.update_interval,
    }
).extend(cv.COMPONENT_SCHEMA)

@coroutine_with_priority(100.0)
async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    #cg.add(var.set_write_interval(config[CONF_FLASH_WRITE_INTERVAL]))
    await cg.register_component(var, config)
