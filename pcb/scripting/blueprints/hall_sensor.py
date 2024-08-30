from core import *


class HallSensorBlueprint(BluePrint):

  def define(self):
    self.group.SetName(f"HallSensor{self.index}")

    he = create_footprint("SOT-23", f"HE{self.index}")
    move_to(he, self.position)
    rotate(he, -90.0)
    self.add(he)

    c1 = create_footprint("C_0402_1005Metric", f"HEC{self.index}")
    move_to(c1, pad_pos(he, 1) + vec2(1.5, 0))
    rotate(c1, -90)
    self.add(c1)

    r1 = create_footprint("R_0402_1005Metric", f"HER{self.index}")
    move_to(r1, pad_pos(he, 2) + vec2(-1.5, 0.0))
    rotate(r1, 90)
    self.add(r1)

    c2 = create_footprint("C_0402_1005Metric", f"HECC{self.index}")
    move_to(c2, pad_pos(he, 2) + vec2(-2.5, 0.0))
    rotate(c2, -90)
    self.add(c2)

    he_ko_shape = shape_circle(5.0)
    he_ko_shape = move_points(he_ko_shape, self.position)
    he_keepout = create_keepout(he_ko_shape, [kicad.F_Cu, kicad.In1_Cu, kicad.In2_Cu, kicad.B_Cu])
    self.add(he_keepout)

    v3_ko_shape = shape_circle(1.5)
    v3_ko_shape = move_points(v3_ko_shape, pad_pos(c1, "1"))
    v3_keepout = create_keepout(v3_ko_shape)
    self.add(v3_keepout)

    track = connect(c2, 1, r1, 2, width=0.4)
    self.add(track)

    pos = pad_pos(r1, 1)
    track = create_track(pos, pos + vec2(1.25, 0), 0.4)
    self.add(track)

    via = create_via(0.6, 0.3)
    self.add(via)
    move_to(via, pad_pos(c2, 1) + vec2(0.0, -1.0))
    track = connect(c2, 1, via, width=0.4)
    self.add(track)

    via = create_via(0.6, 0.3)
    self.add(via)
    move_to(via, pad_pos(c1, 2) + vec2(0.0, 1.0))
    track = connect(c1, 2, via, width=0.4)
    self.add(track)

    pos = pad_pos(c1, 1)
    track = create_track(pos, pos + vec2(-1.5, 0.0), 0.5)
    self.add(track)

    pos = pad_pos(c1, 1)
    track = create_track(pos, pos + vec2(0, -0.75), 0.5)
    self.add(track)

    pos = pad_pos(c1, 1)
    track = create_track(pos, pos + vec2(0.75, 0), 0.5)
    self.add(track)

    via = create_via(0.6, 0.3)
    self.add(via)
    move_to(via, pad_pos(c2, 2) + vec2(0.0, 1.0))
    track = connect(c2, 2, via, width=0.4)
    self.add(track)

    via = create_via(0.6, 0.3)
    self.add(via)
    move_to(via, pad_pos(he, 3) + vec2(0.0, 1.5))
    track = connect(he, 3, via, width=0.4)
    self.add(track)
