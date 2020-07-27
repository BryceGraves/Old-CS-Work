# frozen_string_literal: true

blocksize = [16, 32, 64, 128]
number_of_trials = [16 * 1024, 32 * 1024, 64 * 1024, 128 * 1024]
data = "16,16384,533.3333\n16,32768,986.5125\n16,65536,1858.4392\n16,131072,3002.9325\n32,16384,571.4286\n32,32768,947.2711\n32,65536,1941.2322\n32,131072,3631.2058\n64,16384,571.4286\n64,32768,1084.7457\n64,65536,2151.2606\n64,131072,3953.6681\n128,16384,615.3846\n128,32768,1135.2550\n128,65536,2160.3376\n128,131072,4141.5573\n\n"
output = "Blocksize,Number of Trials,Mega Trials Per Second\n"

output += data

puts "Results!\n" + output

puts "\nCleaning data for export"

data = data.lines

data.each_with_index do |line, index|
  data[index] = line.split(',').map(&:chomp)
end

output += ",#{number_of_trials.join(',')}\n"

blocksize.each do |i|
  current_selection = data.select { |line| line.first == i.to_s }

  output += "#{i}," + current_selection.map(&:last).join(',') + "\n"
end

output += "\n"

output += ",#{blocksize.join(',')} \n"

number_of_trials.each do |i|
  current_selection = data.select { |line| line[1] == i.to_s }

  output += "#{i}," + current_selection.map(&:last).join(',') + "\n"
end

output += "\n"

puts "\nData clean. Exporting to csv..."

File.open('output.csv', 'a+') do |file|
  file << output
end

puts "\nData exported."
