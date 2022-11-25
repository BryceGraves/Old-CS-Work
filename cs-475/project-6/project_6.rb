# frozen_string_literal: true

project = 'project_6'
data = ''
output = "Method,Global Size,Local Work Group Size,Speedup\n"
methods = ['ArrayMult', 'ArrayMultAdd', 'ArrayMultReduce'] # rubocop:disable Style/WordArray

array_size_tests = [32_768, 65_536, 131_072, 262_144, 524_288, 1_048_576, 2_097_152, 4_194_304, 8_388_608]
local_work_group_tests = [32, 64, 128, 256]

`make`

methods.each do |method|
  local_work_group_tests.each do |i|
    puts "Running work group test with size: #{i}"
    array_size_tests.each do |j|
      puts "Running with array size: #{j}"
      data += `./#{project} -l #{i} -s #{j} -m '#{method}'`
    end
  end
end

`make clean`

output += data += "\n"

puts "Results!\n" + output

puts "\nCleaning data for export"

data = data.lines.map(&:chomp).map { |i| i.split(',') }

data = methods.map do |method|
  data.select { |line| line.first == method }.map { |i| i.drop(1) }
end

methods.each_with_index do |method, index|
  output += "\n#{method}\n,#{local_work_group_tests.join(',')}\n"

  array_size_tests.each do |current|
    current_selection = data[index].select { |line| line.first == current.to_s }

    output += "#{current}," + current_selection.map(&:last).join(',') + "\n"
  end

  output += "\n,#{array_size_tests.join(',')}\n"

  local_work_group_tests.each do |current|
    current_selection = data[index].select { |line| line[1] == current.to_s }

    output += "#{current}," + current_selection.map(&:last).join(',') + "\n"
  end
end

output += "\n"

puts "\nData clean. Exporting to csv..."

File.open('output.csv', 'a+') do |file|
  file << output
end

puts "\nData exported."
