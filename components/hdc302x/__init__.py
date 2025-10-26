import esphome.codegen as cg
import esphome.config_validation as cv

# Define a namespace for our component
hdc3022_ns = cg.esphome_ns.namespace("hdc3022")

# Define the C++ component class
HDC3022Component = hdc3022_ns.class_("HDC3022Component", cg.PollingComponent, cg.Component)

