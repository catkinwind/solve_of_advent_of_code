#!/usr/bin/env ruby

class Tester

  DIRS = [Complex(-1), Complex(1), Complex('i'), Complex('-i')]

  def initialize(magic, dst)
    @magic = magic
    @dst = dst
  end

  def search_from(from)
    l = from
    closed = []
    open = [ l ]
    gScore = { l => 0 }
    while !open.empty?
      l = open.shift
      closed << l
      open.delete l
      if gScore[l] < 50
        DIRS.each do |dir|
          c = dir + l
          if available?(c) && is_road?(c) && !closed.include?(c)
            open << c if !open.include?(c)
            edist = gScore[l] + 1
            gScore[c] = edist
          end
        end
      end
    end
    print "result: ", gScore.length, "\n"
  end

  def available?(c)
    c.real >=0 && c.imag >= 0
  end

  def candidate(open, fScore)
    min = 2147483648
    l = nil
    open.each do |c|
      if fScore[c] < min
        min = fScore[c]
        l = c
      end
    end
    l
  end

  def estimate(l)
    (l.real - @dst.real).abs + (l.imag + @dst.imag).abs
  end

  def is_road?(l)
    x = l.real
    y = l.imag
    popcount(x * x + 3 * x + 2 * x * y + y + y * y + @magic) % 2 == 0
  end

  def popcount i
    count = 0
    while i != 0
      count += 1
      i &= i - 1
    end
    count
  end

end

t = Tester.new 1358, Complex(31, 39)
t.search_from Complex(1, 1)
