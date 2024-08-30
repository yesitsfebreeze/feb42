from core import *


class MCUBlueprint(BluePrint):

  def define(self):
    self.group.SetName("MCU")

    mcu = create_footprint("LQFP-48_7x7mm_P0.5mm", "MCU1")
    move_to(mcu, self.position)
    rotate(mcu, 90)
    self.add(mcu)

    # caps = [
    #     create_footprint("C_0402_1005Metric", "C10"),  # 0
    #     create_footprint("C_0402_1005Metric", "C11"),  # 1
    #     create_footprint("C_0402_1005Metric", "C12"),  # 2
    #     create_footprint("C_0402_1005Metric", "C13"),  # 3
    #     create_footprint("C_0402_1005Metric", "C14"),  # 4
    #     create_footprint("C_0402_1005Metric", "C15"),  # 5
    #     create_footprint("C_0402_1005Metric", "C16"),  # 6
    #     create_footprint("C_0402_1005Metric", "C17"),  # 7
    # ]

    # for i, cap in enumerate(caps):
    #   self.add(cap)
    #   move_to(cap, self.position)

    # cap = caps[0]
    # move(cap, vec2(-3.35, -6.0))
    # via = create_via(0.6, 0.3)
    # move_to(via, pad_pos(cap, 2) + vec2(-0.5, 0.6))
    # self.add(via)
    # track = connect(cap, 2, via, width=0.5)
    # self.add(track)
    # tracks = create_tracks([
    #     vec2(-3.9, -6.0),
    #     vec2(-3.9, -3.85),
    #     vec2(-3.5425, -3.5625),
    #     vec2(-2.875, -3.5625)
    # ], width=0.2)
    # for track in tracks:
    #   move_to(track, self.position)
    # self.add(tracks)

    # tracks = create_tracks([
    #     vec2(-2.375, -3.5625),
    #     vec2(-2.375, -4.255),
    #     vec2(-2.87, -6.0)
    # ], width=0.2)
    # for track in tracks:
    #   move_to(track, self.position)
    # self.add(tracks)

    # cap = caps[1]
    # move(cap, vec2(4.5, -2.9))
    # rotate(cap, -90)
    # via = create_via(0.6, 0.3)
    # move_to(via, pad_pos(cap, 2) + vec2(0.6, 0.0))
    # self.add(via)
    # track = connect(cap, 2, via, width=0.5)
    # self.add(track)
    # track = connect(cap, 1, mcu, 24, width=0.2)
    # self.add(track)
    # track = connect(cap, 2, mcu, 23, width=0.2)
    # self.add(track)

    # cap = caps[2]
    # move(cap, vec2(1.7, 4.5))
    # track = connect(cap, 1, mcu, 9, width=0.2)
    # self.add(track)
    # via = create_via(0.6, 0.3)
    # move_to(via, pad_pos(cap, 2) + vec2(0.0, 0.6))
    # self.add(via)
    # track = connect(cap, 2, via, width=0.5)
    # self.add(track)

    # cap = caps[3]
    # move(cap, vec2(-4.7, 2.6))
    # rotate(cap, -90)
    # track = connect(cap, 1, mcu, 47, width=0.2)
    # self.add(track)
    # via = create_via(0.6, 0.3)
    # move_to(via, pad_pos(cap, 2) + vec2(-0.6, 0))
    # self.add(via)
    # track = connect(cap, 2, via, width=0.5)
    # self.add(track)

    # cap = caps[7]
    # move(cap, vec2(4.5, -1.0))
    # rotate(cap, -90)
    # via = create_via(0.6, 0.3)
    # move_to(via, pad_pos(cap, 2) + vec2(0.6, 0.0))
    # self.add(via)
    # track = connect(cap, 2, via, width=0.5)
    # self.add(track)
    # track = connect(cap, 1, mcu, 22, width=0.2)
    # self.add(track)
