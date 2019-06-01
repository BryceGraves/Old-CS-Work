#! /usr/bin/env ruby
# Bryce Graves
# Exercise 5: Decorator Pattern

# Do not modify this class. Pretend it is from a library that is "closed."
class HyperCar

  def initialize(sound)
    @sound = sound
  end

  def go
    3.times { puts @sound }
  end

end

# Do not modify this class. Pretend it is from a library that is "closed."
class CarService

  def initialize(car)
    @car = car
  end

  def execute
    @car.go
  end
end

class CarDecorator
  attr_accessor :car

  def initialize(car)
    @car = car
  end

  def begin_startup
    puts "Awooga!"
  end

  def excited_running_noises
    puts "waka waka waka!"
  end

  def execute
    begin_startup
    go
    excited_running_noises
  end

  def go
    car.go
  end

end

hyper_car = HyperCar.new("bzzzz")
service = CarDecorator.new(hyper_car)
service.execute

# This `execute` call should print:
# > awooga!
# > bzzzz
# > bzzzz
# > bzzzz
# > waka waka waka!
