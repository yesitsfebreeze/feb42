import pcbnew as kicad
import os
import math


UNIT = 19.05
NAME = "BOARD"
VERSION = "1.0"
NETS = {}
BOARD_SIZE = None


def get_logfile():
  path = os.path.abspath(os.path.dirname(__file__))
  return os.path.join(path, 'log')


def log(*args):
  logfile = get_logfile()
  with open(logfile, 'a') as file:
    file.write(' '.join(map(str, args)) + '\n')


def clear_log():
  logfile = get_logfile()
  with open(logfile, 'w') as file:
    file.write('')

# logger end


# vec2
class vec2():
  x: float
  y: float

  def __init__(self, x: float = 0.0, y: float = 0.0):
    self.x = x
    self.y = y

  def to_kicad(self) -> kicad.VECTOR2I:
    return kicad.VECTOR2I(kicad.FromMM(self.x), kicad.FromMM(self.y))

  def from_kicad(vec: kicad.VECTOR2I):
    return vec2(kicad.ToMM(vec.x), kicad.ToMM(vec.y))

  def __add__(self, other):
    return vec2(self.x + other.x, self.y + other.y)

  def __sub__(self, other):
    return vec2(self.x - other.x, self.y - other.y)

  def __mul__(self, other):
    return vec2(self.x * other, self.y * other)

  def __truediv__(self, other):
    return vec2(self.x / other, self.y / other)

  def __repr__(self):
    return f"vec2({self.x}, {self.y})"

# vec2 end

# board


def remove_recursive(el):
  board = kicad.GetBoard()
  board.Remove(el)
  if isinstance(el, kicad.PCB_GROUP):
    for child in el.GetItems():
      remove_recursive(child)


def clear_board():
  kicad.Refresh()
  board = kicad.GetBoard()
  for g in board.Groups():
    if g.GetName() == "__auto_generated__":
      remove_recursive(g)
  kicad.Refresh()


def clear_designators():
  board = kicad.GetBoard()
  for item in board.GetFootprints():
    fp = item.Value().GetText()
    item.Reference().SetVisible(False)
    item.Value().SetVisible(False)


sheet_size = None

sheet_sizes = {
    "A4": vec2(297, 210),
    "A3": vec2(420, 297),
    "A2": vec2(594, 420),
    "A1": vec2(841, 594),
    "A0": vec2(1189, 841),
    "A": vec2(1189, 841),
    "B": vec2(1414, 1000),
    "C": vec2(1297, 917),
    "D": vec2(1752, 1219),
    "E": vec2(1580, 1118),
    "USLetter": vec2(279, 216),
    "USLegal": vec2(356, 216),
    "USLedger": vec2(432, 279),
}


def get_sheet_size():
  board = kicad.GetBoard()
  board_file = board.GetFileName()
  sheet_size = sheet_sizes["A4"]
  with open(board_file, 'r') as file:
    for line in file:
      line = line.strip()
      line = line.strip('(')
      line = line.strip(')')
      if line.startswith('paper '):
        line = line.replace('paper ', '')
        line = line.replace('"', '')
        sheet_size = sheet_sizes[line]
        break
  return sheet_size

# board end


class BluePrint:
  index: int
  i: list
  o: list
  position: vec2
  rotation: float
  children: list
  group: None

  def __init__(self, index: int = 0):
    board = kicad.GetBoard()
    self.index = index
    self.i = []
    self.o = []
    self.position = vec2(0, 0)
    self.anchor = vec2(0, 0)
    self.rotation = 0
    self.children = []
    self.parent = None
    self.group = kicad.PCB_GROUP(board)
    self.group.SetName("__auto_generated__")
    board.Add(self.group)

  def set_anchor(self, *args):
    if len(args) == 1 and isinstance(args[0], vec2):
      self.anchor = args[0]
    elif len(args) == 2 and all(isinstance(arg, (int, float)) for arg in args):
      self.anchor = vec2(args[0], args[1])
    else:
      raise TypeError(
          "Invalid arguments for set_anchor. Expected either (vec2) or (float, float).")

  def rotate(self, deg: float):
    self.rotation = self.rotation + deg

  def set_rotation(self, deg: float):
    self.rotation = deg

  def move(self, pos: vec2):
    move(self.group, pos)

  def move_to(self, *args):
    if len(args) == 1 and isinstance(args[0], vec2):
      self.position = args[0]
    elif len(args) == 2 and all(isinstance(arg, (int, float)) for arg in args):
      self.position = vec2(args[0], args[1])
    else:
      raise TypeError(
          "Invalid arguments for set_position. Expected either (vec2) or (float, float).")

  def is_of(self, type) -> bool:
    return self.type == type

  def add(self, *args):
    if len(args) == 1 and isinstance(args[0], list):
      for item in args[0]:
        self.group.AddItem(item)
    else:
      for item in args:
        self.group.AddItem(item)

  def add_blueprint(self, blueprint):
    self.children.append(blueprint)
    blueprint.parent = self
    return blueprint

  def define(self):
    pass

  def __get_center_offset(self) -> vec2:
    sheet_size = get_sheet_size()
    sheet_half = sheet_size / 2
    return sheet_half - (BOARD_SIZE / 2)

  def generate(self, center=True):
    self.define()
    rotate_around(self.group, self.anchor, self.rotation)
    for child in self.children:
      child.generate()
      self.add(child.group)

    # root blueprint
    if self.parent is None:
      offset = vec2(0, 0)
      if center:
        offset = self.__get_center_offset()
        self.move(offset)
      self.__create_fill_zones(center)

  def __create_fill_zones(self, center=True):
    size = BOARD_SIZE + vec2(10, 10)
    sheet_size = get_sheet_size()

    shape = shape_rectangle(size.x, size.y, .5)
    if center:
      shape = move_points(shape, sheet_size/2)

    for layer, settings in NETS.items():
      net = settings[0]
      clearance = settings[1]
      zone = create_zone(shape, [layer], net)
      zone.HatchBorder()
      zone.SetFillMode(kicad.ZONE_FILL_MODE_POLYGONS)
      zone.SetLocalClearance(kicad.FromMM(clearance))
      self.add(zone)

# helpers start


def set_nets(nets):
  for layer, settings in nets.items():
    NETS[layer] = settings


def set_version(major: int, minor: int):
  global VERSION
  VERSION = f"{major}.{minor}"


def get_version():
  return VERSION


def set_name(string: str):
  global NAME
  NAME = string


def get_name():
  return NAME


def set_board_size(size: vec2):
  global BOARD_SIZE
  BOARD_SIZE = size


def from_mm(mm: float) -> int:
  return kicad.FromMM(mm)


def to_mm(nm: int) -> float:
  return kicad.ToMM(nm)


def move_to(el, *args):
  pos = vec2(0, 0)

  if len(args) == 1 and isinstance(args[0], vec2):
    pos = args[0]
  elif len(args) == 2 and all(isinstance(arg, (int, float)) for arg in args):
    pos = vec2(args[0], args[1])
  if isinstance(el, kicad.PCB_TRACK) and not isinstance(el, kicad.PCB_VIA):
    el.Move(pos.to_kicad())
  else:
    el.SetPosition(pos.to_kicad())


def move(el, *args):
  pos = vec2(0, 0)
  if len(args) == 1 and isinstance(args[0], vec2):
    pos = args[0]
  elif len(args) == 2 and all(isinstance(arg, (int, float)) for arg in args):
    pos = vec2(args[0], args[1])
  move_to(el, vec2.from_kicad(el.GetPosition()) + pos)


def rotate_around(el, pos: vec2, deg: float):
  el.Rotate(pos.to_kicad(), kicad.EDA_ANGLE(deg))


def rotate(el, deg: float):
  el.Rotate(el.GetPosition(), kicad.EDA_ANGLE(deg))


def move_points(points, *args):
  pos = vec2(0, 0)
  if len(args) == 1 and isinstance(args[0], vec2):
    pos = args[0]
  elif len(args) == 2 and all(isinstance(arg, (int, float)) for arg in args):
    pos = vec2(args[0], args[1])
  return [p + pos for p in points]


def find_pad(el, search):
  if isinstance(search, int):
    return el.FindPadByNumber(search)
  if isinstance(search, str):
    for pad in el.Pads():
      if pad.GetPadName() == search:
        return pad
  return None


def pad_pos(el, search):
  pad = find_pad(el, search)
  if pad is None:
    return None
  return vec2.from_kicad(pad.GetPosition())

# helpers end


# shapes

def shape_circle(diameter: float = 1.0, num_points=64):
  radius = diameter * 0.5

  points = []
  for i in range(num_points):
    angle = 2 * math.pi * i / num_points
    x = radius * math.cos(angle)
    y = radius * math.sin(angle)
    p = vec2(x, y)
    points.append(p)
  points.append(points[0])
  return points


def shape_arc(center, start_angle, end_angle, radius, num_points):
  points = []
  for i in range(num_points + 1):
    angle = start_angle + (end_angle - start_angle) * i / num_points
    x = center.x + radius * math.cos(angle)
    y = center.y + radius * math.sin(angle)
    points.append(vec2(x, y))
  return points


def shape_rectangle(width: float, height: float, radius: float = 0.5, num_points=32):
  points = []

  center = vec2(width - radius, radius)
  points += shape_arc(center, -math.pi / 2, 0, radius, num_points)

  center = vec2(width - radius, height - radius)
  points += shape_arc(center, 0, math.pi / 2, radius, num_points)

  center = vec2(radius, height - radius)
  points += shape_arc(center, math.pi / 2, math.pi, radius, num_points)

  center = vec2(radius, radius)
  points += shape_arc(center, math.pi, 3 * math.pi / 2, radius, num_points)

  points.append(points[0])

  points = move_points(points, vec2(-width*0.5, -height*0.5))

  return points

# shapes end


# creation

def create_footprint(name, ref):
  board = kicad.GetBoard()
  boardfile = board.GetFileName()
  board_path = os.path.abspath(boardfile)
  board_dir = os.path.dirname(board_path)
  lib = os.path.join(board_dir, "project.pretty")
  fp = kicad.FootprintLoad(lib, name)
  fp.SetReference(ref)
  board.Add(fp)
  return fp


def create_text(string, size: float = 2.5, layer=kicad.F_SilkS, knockout=False, bold=True):
  board = kicad.GetBoard()
  text = kicad.PCB_TEXT(board)
  text.SetLayer(layer)
  text.SetHorizJustify(kicad.GR_TEXT_H_ALIGN_LEFT)
  text.SetVertJustify(kicad.GR_TEXT_V_ALIGN_BOTTOM)
  text.SetText(string)
  text.SetTextSize(vec2(size, size).to_kicad())
  if bold:
    text.SetTextThickness(from_mm(size * 0.2))
  else:
    text.SetTextThickness(from_mm(size * 0.1))
  if knockout:
    text.SetIsKnockout(True)
  board.Add(text)
  return text


def create_via(size, drill):
  board = kicad.GetBoard()
  via = kicad.PCB_VIA(board)
  via.SetWidth(from_mm(size))
  via.SetDrill(from_mm(drill))
  board.Add(via)
  return via


def create_or_find_net(name):
  board = kicad.GetBoard()
  net = board.FindNet(name)
  if net is None:
    net = kicad.NETINFO_ITEM(board, name)
    board.Add(net)
  return net


def create_zone(points, layers=[kicad.F_Cu], net: str = None):
  board = kicad.GetBoard()
  chain = kicad.SHAPE_LINE_CHAIN()
  for p in points:
    if not isinstance(p, kicad.VECTOR2I):
      chain.Append(p.to_kicad())
    else:
      chain.Append(p)

  zone = kicad.ZONE(board)
  if net is not None:
    zone.SetNet(create_or_find_net(net))

  if len(layers) > 1:
    layer_set = kicad.LSET()
    for l in layers:
      layer_set.AddLayer(l)
    zone.SetLayerSet(layer_set)
  else:
    zone.SetLayer(layers[0])

  zone.AddPolygon(chain)
  board.Add(zone)
  return zone


def create_keepout(points, layers=[kicad.F_Cu, ]):
  zone = create_zone(points, layers)

  zone.SetIsRuleArea(True)
  zone.SetDoNotAllowCopperPour(True)
  zone.SetDoNotAllowFootprints(False)
  zone.SetDoNotAllowPads(False)
  zone.SetDoNotAllowTracks(False)
  zone.SetDoNotAllowVias(False)

  return zone


def create_segments(points, layer, width: float = 0.25):
  board = kicad.GetBoard()
  segments = []
  for start, end in zip(points, points[1:]):
    if not isinstance(start, kicad.VECTOR2I):
      start = start.to_kicad()
    if not isinstance(end, kicad.VECTOR2I):
      end = end.to_kicad()
    segment = kicad.PCB_SHAPE(board)
    segment.SetShape(kicad.SHAPE_T_SEGMENT)
    segment.SetLayer(layer)
    segment.SetStart(kicad.VECTOR2I(start.x, start.y))
    segment.SetEnd(kicad.VECTOR2I(end.x, end.y))
    segment.SetWidth(from_mm(width))
    segments.append(segment)
    board.Add(segment)
  return segments


def create_track(start, end, width: float = 0.25, layer=kicad.F_Cu):
  board = kicad.GetBoard()
  track = kicad.PCB_TRACK(board)
  track.SetStart(start.to_kicad())
  track.SetEnd(end.to_kicad())
  track.SetWidth(from_mm(width))
  track.SetLayer(layer)
  board.Add(track)
  return track


def create_tracks(points, width: float = 0.25, layer=kicad.F_Cu):
  tracks = []
  # points are defining the a and b points of the track
  # so it has to connect from point[0] to points[1] and from points[1] to points[2] and so on
  for start, end in zip(points, points[1:]):
    track = create_track(start, end, width, layer)
    tracks.append(track)
  return tracks


def create_tracks_from_points(points, width: float = 0.25, layer=kicad.F_Cu):
  for start, end in zip(points, points[1:]):
    create_track(start, end, width, layer)


def connect(el1, pad1, el2, pad2=0, width: float = 0.25, layer=kicad.F_Cu, offset1=vec2(0, 0), offset2=vec2(0, 0)):
  p1 = vec2(0, 0)
  p2 = vec2(0, 0)
  if isinstance(el1, kicad.PCB_VIA):
    p1 = vec2.from_kicad(el1.GetPosition())
  else:
    p1 = pad_pos(el1, pad1)
  if isinstance(el2, kicad.PCB_VIA):
    p2 = vec2.from_kicad(el2.GetPosition())
  else:
    p2 = pad_pos(el2, pad2)

  return create_track(p1 + offset1, p2 + offset2, width, layer)

# creation end
