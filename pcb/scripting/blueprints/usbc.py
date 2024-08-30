from core import *


class USBCBlueprint(BluePrint):

  def define(self):
    self.group.SetName("USB-C")
    usb = create_footprint("USB_C", "USB1")
    move_to(usb, self.position)
    rotate(usb, 180)
    self.add(usb)

    gndx = 5.5
    gndy1 = 1.05
    gndy2 = -3.13

    via = create_via(0.8, 0.5)
    move_to(via, self.position + vec2(-gndx, -gndy1))
    self.add(via)
    p = vec2.from_kicad(via.GetPosition())
    track = create_track(p, p + vec2(1.25, 0), 0.8)
    self.add(track)
    track = create_track(p, p + vec2(1.25, 0), 0.8, layer=kicad.B_Cu)
    self.add(track)

    via = create_via(0.8, 0.5)
    move_to(via, self.position + vec2(-gndx, -gndy2))
    self.add(via)
    p = vec2.from_kicad(via.GetPosition())
    track = create_track(p, p + vec2(1.25, 0), 0.8)
    self.add(track)
    track = create_track(p, p + vec2(1.25, 0), 0.8, layer=kicad.B_Cu)
    self.add(track)

    via = create_via(0.8, 0.5)
    move_to(via, self.position + vec2(gndx, -gndy1))
    self.add(via)
    p = vec2.from_kicad(via.GetPosition())
    track = create_track(p, p + vec2(-1.25, 0), 0.8)
    self.add(track)
    track = create_track(p, p + vec2(-1.25, 0), 0.8, layer=kicad.B_Cu)
    self.add(track)

    via = create_via(0.8, 0.5)
    move_to(via, self.position + vec2(gndx, -gndy2))
    self.add(via)
    p = vec2.from_kicad(via.GetPosition())
    track = create_track(p, p + vec2(-1.25, 0), 0.8)
    self.add(track)
    track = create_track(p, p + vec2(-1.25, 0), 0.8, layer=kicad.B_Cu)
    self.add(track)

    shape = shape_rectangle(6.8, 8.0, .5)
    shape = move_points(shape, self.position)
    keepout = create_keepout(shape, [kicad.F_Cu, kicad.In1_Cu, kicad.In2_Cu])
    self.add(keepout)

    d1 = create_footprint("SOT-143", "USBD1")
    move_to(d1, self.position + vec2(-0.2, 10.0))
    self.add(d1)

    r1 = create_footprint("R_0402_1005Metric", "USBR1")
    move_to(r1, self.position + vec2(-2.5, 10.0))
    rotate(r1, 90)
    self.add(r1)

    r2 = create_footprint("R_0402_1005Metric", "USBR2")
    move_to(r2, self.position + vec2(2.1, 10.0))
    rotate(r2, 90)
    self.add(r2)
