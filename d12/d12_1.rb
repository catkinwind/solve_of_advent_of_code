#!/usr/bin/env ruby

class Tester
  INSTRUCTIONS = [
    "cpy 1 a",
    "cpy 1 b",
    "cpy 26 d",
    "jnz c 2",
    "jnz 1 5",
    "cpy 7 c",
    "inc d",
    "dec c",
    "jnz c -2",
    "cpy a c",
    "inc a",
    "dec b",
    "jnz b -2",
    "cpy c b",
    "dec d",
    "jnz d -6",
    "cpy 13 c",
    "cpy 14 d",
    "inc a",
    "dec d",
    "jnz d -2",
    "dec c",
    "jnz c -5"
  ]

  REGISTERS = { 'a' => 0, 'b' => 0, 'c' => 1, 'd' => 0}

  def initialize
    @p = 0
  end

  def jnz(from, offset)
    if evaluate(from) != 0
      @p += evaluate(offset)
    else
      @p += 1
    end
  end

  def cpy(from, to)
    REGISTERS[to] = evaluate(from)
    @p += 1
  end

  def inc(reg)
    REGISTERS[reg] += 1
    @p += 1
  end

  def dec(reg)
    REGISTERS[reg] -= 1
    @p += 1
  end

  def evaluate(str)
    if REGISTERS.has_key? str
      REGISTERS[str]
    else
      str.to_i
    end
  end

  def run
    while @p < INSTRUCTIONS.length
      seg = INSTRUCTIONS[@p].split
      if seg[0] == 'jnz'
        jnz seg[1], seg[2]
      elsif seg[0] == 'cpy'
        cpy seg[1], seg[2]
      elsif seg[0] == 'inc'
        inc seg[1]
      elsif seg[0] == 'dec'
        dec seg[1]
      else
        print "error\n"
        exit 1
      end
    end
    print REGISTERS['a'], "\n"
  end
end

t = Tester.new
t.run
