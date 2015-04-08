import unsigned
import bitfield

type
  Bitarray = seq[Bitfield]

const FieldSize = 2 shl sizeof(Bitfield)

proc `==`*(b0 : Bitarray, b1 : Bitarray):bool=
  if seq[uint32](b0).len != seq[uint32](b0).len:
    return false
  else:
    for i0 in 0.. seq[uint32](b0).high:
      if b0[i0] != b1[i0]:
        return false
    return true
proc len*(b0 : Bitarray):int= seq[uint32](b0).len * FieldSize
proc high*(b0 : Bitarray):int= <(seq[uint32](b0).len * FieldSize)
proc get*(b0 : Bitarray, idx : int) : bool =
  b0[idx shr (sizeof(Bitfield) + 1)].get(idx and <FieldSize)
proc getUInt32*(b0 : Bitarray, idx : int) : uint32 =
  b0[idx shr (sizeof(Bitfield) + 1)].getUInt32(idx and <FieldSize)
proc flag*(b0 : var Bitarray, idx : int) = 
  let big = idx shr (sizeof(Bitfield) + 1)
  let small = idx and <FieldSize
  b0[big] = b0[big].flag(small)
proc unflag*(b0 : var Bitarray, idx : int) = 
  let big = idx shr (sizeof(Bitfield) + 1)
  let small = idx and <FieldSize
  b0[big] = b0[big].unflag(small)
proc invert*(b0 : var Bitarray)=
  for i0 in 0.. seq[uint32](b0).high:
    b0[i0] = b0[i0].invert
proc fill*(b0 : var Bitarray, start : int, len : int, val : bool) =
  let big0 = start shr (sizeof(Bitfield) + 1)
  let small0 = start and <FieldSize
  let big1 = (start + len) shr (sizeof(Bitfield) + 1)
  let small1 = (start + len) and <FieldSize
  # case 1. fill is size zero
  if len < 1:
    return
  # case 2. fill size is less or equal bitfield size
  elif big0 == big1:
    b0[big0] = b0[big0].fill(small0, small1 - small0, val)
  # case 3. fill size greater bitfield size
  else:
    b0[big0] = b0[big0].fill(small0, FieldSize - small0, val)
    b0[big1] = b0[big1].fill(0, small1, val)
    # case 3.1. fill size occupies more than two bigs
    if big1 - big0 > 1:
      var fillv = Bitfield(0)
      if val:
        fillv = fillv.invert
      for i0 in (big0+1)..(<big1):
        b0[i0] = fillv
proc rangeTrue*(b0 : var Bitarray, start : int, len : int) : bool =
  let big0 = start shr (sizeof(Bitfield) + 1)
  let small0 = start and <FieldSize
  let big1 = (start + len) shr (sizeof(Bitfield) + 1)
  let small1 = (start + len) and <FieldSize
  # case 1. range is size zero
  if len < 1:
    return false
  # case 2. range is less or equal bitfield size
  elif big0 == big1:
    return b0[big0].rangeTrue(small0, small1 - small0)
  # case 3. range greater bitfield size
  else:
    if b0[big0].rangeTrue(small0, FieldSize - small0) or
       b0[big1].rangeTrue(0, small1):
      return true
    # case 3.1. range occupies more than two bigs
    elif big1 - big0 > 1:
      for i0 in (big0+1)..(<big1):
        if uint32(b0[i0]) != uint32(0):
          return true
    return false  

proc sequence*(b0 : Bitarray) : seq[bool] =
  result = newSeq[bool](b0.len)
  for i0 in 0.. <(b0.len):
    result[i0] = get(b0, i0)
proc `$`*(b0 : Bitarray) : string =
  result = newString(b0.len)
  for i0 in 0.. <(b0.len):
    if b0.get(i0):
      result[i0 .. i0] = "T"
    else:
      result[i0 .. i0] = "F"
proc newBitarray*(len : int):Bitarray=
  let shrlen = len shr (sizeof(Bitfield) + 1)
  let remlen = len and (<FieldSize)
  if remlen > 0:
    result = Bitarray(newSeq[Bitfield](shrlen + 1))
  else:
    result = Bitarray(newSeq[Bitfield](shrlen))

when isMainModule:
  var ba : Bitarray
  var ba2 : Bitarray
  var bf = Bitfield(0)
  bf = bf.flag(0)
  bf = bf.flag(1)
  bf = bf.flag(2)
  echo(bf)
  ba = newBitarray(0)
  echo(ba)
  ba = newBitarray(1)
  ba[0] = bf
  echo(ba)
  ba = newBitarray(32)
  ba.flag(31)
  echo(ba)
  ba = newBitarray(33)
  ba[1] = bf
  echo(ba)
  ba = newBitarray(32)
  ba2 = newBitarray(32); ba2.invert
  ba.fill(0, 31, true)
  ba2.fill(0, 31, false)
  echo(ba)
  ba2.invert; 
  echo(ba2 == ba)
  ba = newBitarray(64)
  ba2 = newBitarray(64); ba2.invert
  ba.fill(31, 2, true)
  ba2.fill(31, 2, false)
  echo(ba)
  ba2.invert; echo(ba2 ==ba)
  ba = newBitarray(96)
  ba2 = newBitarray(96); ba2.invert
  ba.fill(1, 64, true)
  ba2.fill(1, 64, false)
  echo(ba)
  ba2.invert; echo(ba2 == ba)

  echo(ba.rangeTrue(0,1))
  echo(ba.rangeTrue(0,2))
  echo(ba.rangeTrue(65,2))
  echo(ba.rangeTrue(3,32))