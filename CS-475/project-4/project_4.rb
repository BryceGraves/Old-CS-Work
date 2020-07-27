# frozen_string_literal: true

project = 'project_4'
data = ''
output = "Thread,Array Size,Speedup\n"
thread_tests = [1, 2, 4, 8]
array_size_tests = [
  1000 * 1,
  1000 * 10,
  1000 * 100,
  1000 * 1000,
  1000 * 10_000,
  1000 * 100_000,
  1000 * 1_000_000
]

`make`

thread_tests.each do |i|
  puts "Running trials with #{i} threads"

  array_size_tests.each do |j|
    data += `./#{project} -t #{i} -s #{j}`
  end
end

`make clean`

output += data += "\n"

puts "Results!\n" + output

puts "\nCleaning data for export"

data = data.lines

data.each_with_index do |line, index|
  data[index] = line.split(',').map(&:chomp)
end

output += ",#{array_size_tests.join(',')}\n"

thread_tests.each do |i|
  current_selection = data.select { |line| line.first == i.to_s }

  output += "#{i}," + current_selection.map(&:last).join(',') + "\n"
end

output += "\n"

output += ",#{thread_tests.join(',')} \n"

array_size_tests.each do |i|
  current_selection = data.select { |line| line[1] == i.to_s }

  output += "#{i}," + current_selection.map(&:last).join(',') + "\n"
end

output += "\n"

puts "\nData clean. Exporting to csv..."

File.open('output.csv', 'a+') do |file|
  file << output
end

puts "\nData exported."

puts "\nCalculating FP..."

one_thread_max = data.select do |line|
  line.first == '1'
end.map(&:last).map(&:to_f).max

four_thread_max = data.select do |line|
  line.first == '4'
end.map(&:last).map(&:to_f).max

puts "FP: #{((4.0 / 3.0) * (1.0 - (1.0 / (four_thread_max / one_thread_max))))}"
