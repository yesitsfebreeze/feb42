import json

from core import *
from blueprints.key import KeyBlueprint
from blueprints.usbc import USBCBlueprint
from blueprints.multiplexers import MultiplexersBlueprint
from blueprints.power import PowerBlueprint
from blueprints.labels import LabelsBlueprint
from blueprints.mcu import MCUBlueprint
from blueprints.crystal import CrystalBlueprint


def read_layout():
  with open("layout.json", "r") as file:
    return json.load(file)


def make_keys(layout):
  keys = []
  index = 0
  for row in range(len(layout)):
    offset_x = 0
    keys_in_row = len(layout[row])
    for col in range(keys_in_row):
      index += 1
      col = keys_in_row - col - 1
      key = layout[row][col]
      units = key[0]
      x = offset_x + ((units / 2) * UNIT)
      y = (row + 0.5) * UNIT
      keys.append((index, units, x, y, row, col))
      offset_x += (units + key[1]) * UNIT
  return keys


def main():
  clear_log()
  clear_board()
  layout = read_layout()
  keys = make_keys(layout)
  keyboard = BluePrint()

  set_nets({
      kicad.F_Cu: ("+3V3", 0.225),
      kicad.In1_Cu: ("GND", 0.225),
      kicad.In2_Cu: ("GND", 0.225),
      kicad.B_Cu: ("+5V", 0.225),
  })
  set_version(1, 0)
  set_name("FEB42")
  set_board_size(vec2(228.6, 76.2))

  labels = LabelsBlueprint()
  labels.move_to(vec2(5, 60.5))
  keyboard.add_blueprint(labels)

  esd_logo = create_footprint("esd", "esd_logo")
  move(esd_logo, vec2(13, 21))
  keyboard.add(esd_logo)

  for index, units, x, y, row, col in keys:
    key = KeyBlueprint(index)
    key.set_key_data(units, row, col)
    key.move_to(vec2(x, y))
    keyboard.add_blueprint(key)

  usb = USBCBlueprint()
  usb.move_to(vec2(UNIT, 2.0))
  keyboard.add_blueprint(usb)

  power = PowerBlueprint()
  power.move_to(vec2(UNIT + 9.0, 3.0))
  keyboard.add_blueprint(power)

  keyboard.add_blueprint(MultiplexersBlueprint())

  mcu = MCUBlueprint()
  mcu.move_to(vec2(63.0, 63.0))
  keyboard.add_blueprint(mcu)

  crystal = CrystalBlueprint()
  crystal.move_to(vec2(56.0, 71))
  crystal.set_anchor(crystal.position)
  crystal.rotate(90)
  keyboard.add_blueprint(crystal)

  outline = create_footprint("Outline", "Outline")
  keyboard.add(outline)

  keyboard.generate()
  clear_designators()
  kicad.Refresh()
