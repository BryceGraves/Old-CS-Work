# frozen_string_literal: true

output = "Month,Height (CM),Deer Count,Precipitation,Temperature (Celsius),Wolf Count\n"
project = 'project_3'

puts 'Starting simlualtion'

`make`

output += `./#{project} #{Random.rand(1..2_147_483_647)}`

`make clean`

File.open('output.csv', 'a+') do |file|
  file << output += "\n"
end
