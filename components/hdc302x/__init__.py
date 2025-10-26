import esphome.codegen as cg
import esphome.config_validation as cv

# Define a namespace for our component
hdc302x_ns = cg.esphome_ns.namespace("hdc302x")

# Define the C++ component class
HDC302xComponent = hdc302x_ns.class_("HDC302xComponent", cg.PollingComponent, cg.Component)

