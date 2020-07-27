# frozen_string_literal: true

data = ''
output = "threads,node count,performance\n"
thread_tests = [1, 2, 3, 4, 5, 6, 7, 8]
node_tests = [4**1, 4**2, 4**3, 4**4, 4**5, 4**6, 4**7, 4**8]

`make`

thread_tests.each do |i|
  puts "Running trials with #{i} threads"

  node_tests.each do |j|
    data += `./project-2 -v -t #{i} -n #{j}`
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

output += ",#{node_tests.join(' nodes,')} nodes\n"

thread_tests.each do |i|
  current_selection = data.select { |line| line.first == i.to_s }

  output += "#{i} threads," + current_selection.map(&:last).join(',') + "\n"
end

output += "\n"

output += ",#{thread_tests.join(' threads,')} threads\n"

node_tests.each do |i|
  current_selection = data.select { |line| line[1] == i.to_s }

  output += "#{i} nodes," + current_selection.map(&:last).join(',') + "\n"
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
