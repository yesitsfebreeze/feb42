from core import *


class CrystalBlueprint(BluePrint):

  def define(self):
    self.group.SetName("Crystal")

    crystal = create_footprint("Crystal_SMD_3225-4Pin_3.2x2.5mm", "CR1")
    move_to(crystal, self.position)
    rotate(crystal, -90)
    self.add(crystal)

    offset = 0.5
    c1 = create_footprint("C_0402_1005Metric", "CR_C1")
    move_to(c1, self.position + vec2(-1.0 + offset, 2.7))
    rotate(c1, 180)
    self.add(c1)

    c2 = create_footprint("C_0402_1005Metric", "CR_C2")
    move_to(c2, self.position + vec2(1.0 + offset, 2.7))
    rotate(c2, 180)
    self.add(c2)

    r1 = create_footprint("R_0402_1005Metric", "CR_R1")
    rotate(r1, 180)
    move_to(r1, self.position + vec2(1.0 + offset, 3.7))
    self.add(r1)

    track = create_track(pad_pos(c1, 1), pad_pos(crystal, 2), width=0.5)
    self.add(track)

    via = create_via(0.8, 0.4)
    move_to(via, pad_pos(c1, 1) + vec2(0, 1.0))
    self.add(via)
    track = connect(c1, 1, via, width=0.5)
    self.add(track)

    track = create_track(pad_pos(c2, 2), pad_pos(crystal, 3), width=0.25)
    self.add(track)
    track = create_track(pad_pos(c2, 2), pad_pos(r1, 2), width=0.25)
    self.add(track)

    via = create_via(0.8, 0.4)
    move_to(via, self.position + vec2(1.98, 0))
    self.add(via)
    track = connect(c2, 1, via, width=0.5)
    self.add(track)
    track = connect(crystal, 4, via, width=0.5)
    self.add(track)
