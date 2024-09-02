from core import *


class LEDBlueprint(BluePrint):

  def define(self):
    self.group.SetName(f"LED{self.index}")

    self.set_anchor(self.position + vec2(0.0, 5.08))

    led = create_footprint("SK6812-MINI-E", f"LED{self.index}")
    log(dir(led))
    led.SetPosition(self.anchor.to_kicad())

    self.add(led)

    c1 = create_footprint("C_0402_1005Metric", f"LEDC{self.index}")
    c1.SetPosition(pad_pos(led, 3).to_kicad())
    move(c1, -1.5, 0.5)
    rotate(c1, 90)
    self.add(c1)

    via = create_via(0.6, 0.3)
    move_to(via, pad_pos(c1, 1) + vec2(-1.0, 0.0))
    self.add(via)
    track = connect(c1, 1, via, width=0.5)
    self.add(track)

    via = create_via(0.6, 0.3)
    move_to(via, pad_pos(c1, 2) + vec2(-1.0, 0.0))
    self.add(via)
    track = connect(c1, 2, via, width=0.5)
    self.add(track)

    track = connect(c1, 2, led, 3, width=0.5)
    self.add(track)

    via = create_via(0.6, 0.3)
    move_to(via, pad_pos(led, 1) + vec2(1.0, 0.0))
    self.add(via)
    track = connect(led, 1, via, width=0.5)
    self.add(track)
