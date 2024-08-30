from core import *
from datetime import datetime


class LabelsBlueprint(BluePrint):

  def define(self):
    self.group.SetName("Labels")

    name = create_text(get_name(), knockout=True, size=2)
    move_to(name, self.position)
    self.add(name)

    version = create_text(f"REV{get_version()}", size=2)
    move_to(version, self.position + vec2(10.0, 0))
    self.add(version)

    now = datetime.now()
    date = create_text(now.strftime("%d-%m-%Y %H:%M:%S"), size=1.1)
    move_to(date, self.position + vec2(0, 2.25))
    self.add(date)
