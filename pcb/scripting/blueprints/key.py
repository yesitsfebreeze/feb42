from core import *

from .hall_sensor import HallSensorBlueprint
from .led import LEDBlueprint


class KeyBlueprint(BluePrint):
  def set_key_data(self, units, row, col):
    self.units = units
    self.row = row
    self.col = col

  def is_even(self):
    return self.row % 2 == 0

  def define(self):
    self.group.SetName(f"KEY{self.index}")

    fp = create_footprint(f"HE_Switch_{self.units}U", f"Key{self.index}")
    move_to(fp, self.position)
    self.add(fp)

    hall_sensor = HallSensorBlueprint(self.index)
    hall_sensor.move_to(self.position)
    self.add_blueprint(hall_sensor)

    led = LEDBlueprint(self.index)
    led.move_to(self.position)
    self.add_blueprint(led)
    if self.is_even():
      led.rotate(180)
