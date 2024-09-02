from core import *


class PowerBlueprint(BluePrint):

  def define(self):
    self.group.SetName("Power")
    fuse = create_footprint("Fuse_1206_3216Metric", "PWRF1")
    move_to(fuse, self.position)
    self.add(fuse)

    c1 = create_footprint("C_0805_2012Metric", "PWRC1")
    move_to(c1, self.position + vec2(4.9, 0.6))
    rotate(c1, -90)
    self.add(c1)

    stepdown = create_footprint("TSOT-23-5", "SD1")
    move_to(stepdown, self.position + vec2(8.0, 0.6))
    self.add(stepdown)

    l1 = create_footprint("L_1210_3225Metric", "PWRL1")
    move_to(l1, self.position + vec2(12.0, 0.6))
    rotate(l1, 90)
    self.add(l1)

    c2 = create_footprint("C_0805_2012Metric", "PWRC2")
    move_to(c2, self.position + vec2(15.0, 0.6))
    rotate(c2, -90)
    self.add(c2)

    shape = shape_rectangle(28.0, 6.0, 0.75)
    shape = move_points(shape, self.position + vec2(3.0, 0.5))
    keepout = create_keepout(shape, [kicad.F_Cu])
    self.add(keepout)
