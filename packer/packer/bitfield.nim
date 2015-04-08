import unsigned

type
  Bitfield* = distinct uint32

proc `and`*(b0 : Bitfield, b1 : Bitfield) : Bitfield = 
  Bitfield(uint32(b0) and uint32(b1))
proc `or`*(b0 : Bitfield, b1 : Bitfield) : Bitfield = 
  Bitfield(uint32(b0) or uint32(b1))
proc `xor`*(b0 : Bitfield, b1 : Bitfield) : Bitfield = 
  Bitfield(uint32(b0) xor uint32(b1))
proc `==`*(b0 : Bitfield, b1 : Bitfield) : bool = 
  uint32(b0) == uint32(b1)
proc `shl`*(b0 : Bitfield, b1 : int) : Bitfield = 
  Bitfield(uint32(b0) shl uint32(b1))
proc `shr`*(b0 : Bitfield, b1 : int) : Bitfield = 
  Bitfield(uint32(b0) shr uint32(b1))
proc get*(b0 : Bitfield, idx : int) : bool = 
  uint32((b0 shr idx) and Bitfield(1)) > uint32(0)
proc getUInt32*(b0 : Bitfield, idx : int) : uint32 = 
  uint32((b0 shr idx) and Bitfield(1))
proc flag*(b0 : Bitfield, idx : int) : Bitfield = 
  Bitfield(uint32(b0) or (uint32(1) shl uint32(idx)))
proc unflag*(b0 : Bitfield, idx : int) : Bitfield = 
  Bitfield(uint32(b0) and not (uint32(1) shl uint32(idx)))
proc invert*(b0 : Bitfield) : Bitfield {.inline.} =
  return Bitfield(not uint32(b0))
proc sequence*(b0 : Bitfield) : seq[bool] =
  result = newSeq[bool](32)
  for i0 in 0.. <32:
    result[i0] = get(b0, i0)
proc `$`*(b0 : Bitfield) : string =
  result = newString(32)
  for i0 in 0.. <32:
    if b0.get(i0):
      result[i0 .. i0] = "T"
    else:
      result[i0 .. i0] = "F"
proc flagfill*(b0 : Bitfield, start : int, len : int) : Bitfield =
  const bf = Bitfield(0).invert
  let mask0 = bf shl start
  let mask1 = bf shl (start + len)
  result = b0 or (mask0 xor mask1)
proc unflagfill*(b0 : Bitfield, start : int, len : int) : Bitfield =
  const bf = Bitfield(0).invert
  let mask0 = bf shl start
  let mask1 = bf shl (start + len)
  result = ((b0.invert) or (mask0 xor mask1)).invert
proc fill*(b0 : Bitfield, start : int, len : int, val : bool) : Bitfield =
  if val:
    return flagfill(b0, start, len)
  else:
    return unflagfill(b0, start, len)
proc rangeTrue*(b0 : Bitfield, start : int, len : int) : bool {.inline.} =
  const bf = Bitfield(0).invert
  let mask0 = bf shl start
  if (start + len >= 32): # otherwise mask1's shl overflows
    result = uint32(b0 and mask0) != uint32(0)
  else: 
    let mask1 = bf shl (start + len)
    result = uint32(b0 and (mask0 xor mask1)) != uint32(0)

when isMainModule:
  var bf = Bitfield(0)

  for i0 in 0.. <32:
    bf = bf.flag(i0)
    echo($bf)
    bf = bf.unflag(i0)

  for i0 in 0.. <32:
    bf = bf.flag(i0)
    bf = bf.flag(31-i0)
    echo($bf)
    bf = bf.unflag(i0)

  var bf2 = Bitfield(0)
  bf2 = bf2.flag(1)
  bf2 = bf2.flag(3)
  bf2 = bf2.flag(5)
  bf2 = bf2.flag(7)
  echo(bf2 and bf)
  echo(bf2 or bf)
  echo(bf2 xor bf)

  var bf3 = Bitfield(0)
  bf3 = bf3.fill(0, 1, true)
  echo(bf3)
  bf3 = Bitfield(0)
  bf3 = bf3.fill(1, 20, true)
  echo(bf3)
  bf3 = bf3.fill(2, 18, false)
  echo(bf3)
  
  assert(bf3.rangeTrue(1, 0) == false)
  assert(bf3.rangeTrue(0, 8) == true)
  assert(bf3.rangeTrue(2, 8) == false)
  assert(bf3.rangeTrue(16, 8) == true)
  assert(bf3.rangeTrue(21, 5) == false)