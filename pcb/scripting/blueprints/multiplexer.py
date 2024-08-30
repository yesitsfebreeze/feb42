from core import *


class MultiplexerBlueprint(BluePrint):

  def define(self):
    self.group.SetName("Multiplexer")

    mpex = create_footprint("SSOP-24_5.3x8.2mm_P0.65mm", f"MP{self.index}")
    move_to(mpex, self.position)
    rotate(mpex, 90)
    self.add(mpex)

    c1 = create_footprint("C_0402_1005Metric", f"MPc{self.index}")
    move_to(c1, self.position + vec2(-5.55, -3.0))
    rotate(c1, -90)
    self.add(c1)

    inset = 1.95
    spread = 0.15
    alternate = 0.125

    signal = list(range(2, 9 + 1)) + list(range(16, 23 + 1))

    for i in range(0, 8):
      odd = i % 2 == 1

      a = signal[i]
      b = signal[i + 8]
      s = spread * a - spread * 5
      via = create_via(0.6, 0.3)
      move_to(via, pad_pos(mpex, a) + vec2(s, -inset))
      if odd:
        move(via, vec2(0, -alternate))
      else:
        move(via, vec2(0, alternate))
      self.add(via)
      track = connect(mpex, a, via, width=0.23, offset1=vec2(0, -0.8))

      self.add(track)

      via = create_via(0.6, 0.3)
      move_to(via, pad_pos(mpex, b) + vec2(-s, inset))
      if odd:
        move(via, vec2(0, alternate))
      else:
        move(via, vec2(0, -alternate))
      self.add(via)
      track = connect(mpex, b, via, width=0.23, offset1=vec2(0, 0.8))
      self.add(track)

    # gnd
    dist = 1.15
    via = create_via(0.6, 0.3)
    p_12 = pad_pos(mpex, 12)
    move_to(via, p_12 + vec2(dist, -dist))
    self.add(via)
    track = create_track(p_12 + vec2(0.25, 0), p_12 + vec2(dist, 0), 0.5)
    self.add(track)
    track = create_track(p_12 + vec2(dist, 0), p_12 + vec2(dist, -dist), 0.5)
    self.add(track)

    track = create_track(pad_pos(c1, 1), pad_pos(mpex, 24) + vec2(-0.15, 0), width=0.5)
    self.add(track)

    via = create_via(0.6, 0.3)
    move_to(via, pad_pos(c1, 2) + vec2(0, 0.75))
    self.add(via)
    track = connect(c1, 2, via, width=0.5)
    self.add(track)

    # via = create_via(0.6, 0.3)
    # move_to(via, pad_pos(mpex, 14) + vec2(0.5, 1.7))
    # self.add(via)

    # via = create_via(0.6, 0.3)
    # move_to(via, pad_pos(mpex, 10))
    # self.add(via)

    # via = create_via(0.6, 0.3)
    # move_to(via, pad_pos(mpex, 11))
    # self.add(via)
