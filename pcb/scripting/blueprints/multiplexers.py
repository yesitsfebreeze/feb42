from core import *

from .multiplexer import MultiplexerBlueprint


class MultiplexersBlueprint(BluePrint):

  def define(self):
    for i in range(3):
      i += 1
      mp = MultiplexerBlueprint(i)
      if i == 1:
        mp.move_to(vec2(39.25, 42.5))
      if i == 2:
        mp.move_to(vec2(109, 39.5))
      if i == 3:
        mp.move_to(vec2(185, 39.5))
      self.add_blueprint(mp)
