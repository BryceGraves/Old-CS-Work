# frozen_string_literal: true

TOTAL_RUNS = 20

data = ''
output = "threads,trials,probability,performance\n"
six_zeros = '000000'
tread_header = ",1 thread,2 threads,3 threads,4 threads\n"
trial_header = ",1M,2M,4M,8M,16M\n"

`make`

(1..4).each do |i|
  puts "Running trials with #{i} threads"

  data += `./project-1 -t #{i} -c 1`
  data += `./project-1 -t #{i} -c 2`
  data += `./project-1 -t #{i} -c 4`
  data += `./project-1 -t #{i} -c 8`
  data += `./project-1 -t #{i} -c 16`
end

`make clean`

output += data += "\n"

puts "Results!\n" + output

puts "\nCleaning data for export"

data = data.lines

data.each_with_index do |line, index|
  data[index] = line.split(',').map(&:chomp)
end

output += trial_header

(1..4).each do |i|
  current_selection = data.select { |line| line.first == i.to_s }

  output += "#{i} threads," + current_selection.map(&:last).join(',') + "\n"
end

output += "\n"

output += tread_header

[1, 2, 4, 8, 16].each do |i|
  current_selection = data.select { |line| line[1] == i.to_s + six_zeros }

  output += "#{i}M," + current_selection.map(&:last).join(',') + "\n"
end

output += "\n"

puts "\nData clean. Exporting to csv..."

File.open('output.csv', 'a+') do |file|
  file << output
end

puts "\nData exported."
puts 'Calculating average probability from all tests'

total = 0.0

data.each do |line|
  total += line[2].to_f
end

puts "Average probability for entire test set: #{total / TOTAL_RUNS}"

puts "\nCalculating FP..."

one_thread_max = data.select do |line|
  line.first == '1'
end.map(&:last).map(&:to_f).max

four_thread_max = data.select do |line|
  line.first == '4'
end.map(&:last).map(&:to_f).max

puts "FP: #{((4.0 / 3.0) * (1.0 - (1.0 / (four_thread_max / one_thread_max))))}"
