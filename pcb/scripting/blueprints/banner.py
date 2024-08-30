from core import *
from datetime import datetime


class BannerBlueprint(BluePrint):

  def define(self):
    self.group.SetName("Labels")
    shape = shape_rectangle(100, 10, 0.5)
    shape = move_points(shape, self.position)
    self.add(create_pol)

    # name = create_text(get_name(), knockout=True, size=2)
    # move_to(name, self.position)
    # self.add(name)

    # version = create_text(f"REV{get_version()}", size=2)
    # move_to(version, self.position + vec2(10.0, 0))
    # self.add(version)

    # now = datetime.now()
    # date = create_text(now.strftime("%d-%m-%Y %H:%M:%S"), size=1.1)
    # move_to(date, self.position + vec2(0, 2.25))
    # self.add(date)
