#!/usr/bin/env ruby

center = []

class State
  FLOOR_NO = 4
  CHIPS_NO = 14
  private_class_method :new

  @@register = {}

  #
  # Note, chips is passed by value
  #
  def initialize(elevator, chips)
    @elevator = elevator
    @chips = chips
  end

  def ele
    @elevator
  end

  def chp
    @chips
  end

  def valid?(floor, chips)
    if floor < 1  || floor > FLOOR_NO
      return false
    end
    has_generator = (CHIPS_NO/2..CHIPS_NO-1).any? { |i| chips[i] == floor }
    may_in_danger = (0..CHIPS_NO/2-1).any? do |i|
      chips[i] == floor && chips[CHIPS_NO-i-1] != floor
    end
    return !has_generator || !may_in_danger
  end

  def self.get_id(e, chips)
    id = e.to_s
    cplx = []
    for i in (0..CHIPS_NO / 2 -1)
      cplx << Complex(chips[i], chips[CHIPS_NO-i-1])
    end
    cplx.sort! do |x, y|
      if x.real != y.real
        x.real - y.real
      else
        x.imag - y.imag
      end
    end
    cplx.each { |x| id = id + x.real.to_s + x.imag.to_s }
    # chips.each { |x| id += x.to_s }

    id
  end

  def self.find_or_create(e, chips)
    id = get_id(e, chips)
    unless @@register.has_key? id
      @@register[id] = new(e, chips)
    end
    @@register[id]
  end

  def find_neighbors
    nei = []
    ch = []
    if @elevator > 1
      for i in (0..CHIPS_NO-1)
        e = @elevator - 1
        next unless @chips[i] == @elevator
        ch = @chips.clone
        ch[i] -= 1
        nei << State.find_or_create(e, ch) if
          valid?(e, ch) && valid?(@elevator, ch)
        for j in (i+1..CHIPS_NO-1)
          next unless @chips[j] == @elevator
          ch = @chips.clone
          ch[i] -= 1
          ch[j] -= 1
          nei << State.find_or_create(e, ch) if
            valid?(e, ch) && valid?(@elevator, ch)
        end
      end
    end

    if @elevator < FLOOR_NO
      for i in (0..CHIPS_NO-1)
        e = @elevator + 1
        next unless @chips[i] == @elevator
        for j in (i+1..CHIPS_NO-1)
          next unless @chips[j] == @elevator
          ch = @chips.clone
          ch[i] += 1
          ch[j] += 1
          nei << State.find_or_create(e, ch) if
            valid?(e, ch) && valid?(@elevator, ch)
        end
        ch = @chips.clone
        ch[i] += 1
        nei << State.find_or_create(e, ch) if
          valid?(e, ch) && valid?(@elevator, ch)
      end
    end
    # print nei, "\n"
    nei
  end

  def neighbors
    if @neighbors.nil?
      @neighbors = find_neighbors
    end
    @neighbors
  end

  def estimate
    # if @estimate.nil?
    #   @estimate = (FLOOR_NO - @elevator) * 100
    #   @chips.each_with_index { |f, i| @estimate += (FLOOR_NO-f) * (i+1) }
    #   @estimate = (@estimate / 2).ceil
    # end
    # @estimate
    1
  end
end

def find_min(open, fScore)
  min = 200000
  state = nil
  open.each do |s|
    if fScore[s] < min
      min = fScore[s]
      state = s
    end
  end
  state
  #open.shift
end

def rebuild_path(came_from, goal)
  states = []
  while !goal.nil?
    states << goal
    goal = came_from[goal]
  end
  states
end

def a_star(start, goal)
  closedSet = []
  openSet = [ start ]
  fScore = { start => start.estimate }
  came_from = { start => nil }
  gScore = { start => 0 }
  while !openSet.empty?
    state = find_min(openSet, fScore)
    print state.ele, ", ", state.chp, "\n"
    if state == goal
      path = rebuild_path(came_from, goal)
      print "result\n"
      path.each  { |p| print p.ele, ", ", p.chp, "\n" }
      return path.length - 1
    end
    openSet.delete state
    if closedSet.include? state
      next
    end
    closedSet << state
    state.neighbors.each do |ng|
      next if closedSet.include?(ng)
      cur_d = gScore[state] + 1
      openSet.push ng unless openSet.include?(ng)

      if !gScore.has_key?(ng) || gScore[ng] > cur_d
        gScore[ng] = cur_d
        came_from[ng] = state
        fScore[ng] = ng.estimate + cur_d
      end
    end
  end
  -1
end

start = State.find_or_create(1, [1,1,1,3,3,3,3,2,2,2,2,1,1,1])
goal = State.find_or_create(4, [4,4,4,4,4,4,4,4,4,4,4,4,4,4])
a = { start => 0}
#print a[s2], " test\n"
print a_star(start, goal), "\n"
