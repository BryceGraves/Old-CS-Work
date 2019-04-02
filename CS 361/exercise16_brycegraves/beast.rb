class Beast

  attr_accessor :name

  def initialize(name)
    @name = name
  end

  def speak
    puts "My name is #{name}, "
    puts suffix()
  end

  def suffix
    raise NoMethodError
  end
end
