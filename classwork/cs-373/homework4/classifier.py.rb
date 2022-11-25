require 'json'

# README: to run this program

# Run this program through your local ruby version. I used 2.6.5 but I have confirmed that it works through 2.5.1.
# The script will ask you which json file contained within the folder you want to run. Input the number and hit enter.
# It will then ask if it's the training set. input "y" or "n" depending on the json you selected from the previous step.
# The program will run and output the results in a file called results.txt

# Classifier offsets
LIKELY_MALICIOUS = 10
VERY_LIKELY_MALICIOUS = 20
MOST_LIKELY_MALICIOUS = 30
CONFIRMED_MALICIOUS = 1000

LIKELY_NOT_MALICIOUS = -10
VERY_LIKELY_NOT_MALICIOUS = -20
MOST_LIKELY_NOT_MALICIOUS = -30
CONFIRMED_NOT_MALICIOUS = -1000

# Known Malicious Constants
DANGEROUS_FILE_EXTENSIONS = ["gif", "de", "eu", "zip", "uk", "rar", "jpg", "it"]

# Helper Methods
def calculate_weight(record)
    weight = 50

    # Host Length
    weight += LIKELY_MALICIOUS if record['host_len'] > 65

    # URL Length
    weight += LIKELY_MALICIOUS if record['url_len'] > 573

    # Alexa Rank Weight Calculations
    alexa_rank = record["alexa_rank"].to_i

    weight += VERY_LIKELY_MALICIOUS if alexa_rank == 0 || alexa_rank > 92922

    # Domain Age Weight Calculations
    domain_age_days = record["domain_age_days"].to_i

    if domain_age_days < 0
      weight += MOST_LIKELY_MALICIOUS
    elsif domain_age_days < 62
      weight += VERY_LIKELY_MALICIOUS
    elsif domain_age_days < 365
      weight += LIKELY_MALICIOUS
    elsif domain_age_days < 1504
      weight += LIKELY_NOT_MALICIOUS
    elsif domain_age_days < 16198
      weight += VERY_LIKELY_NOT_MALICIOUS
    elsif domain_age_days > 16198
      weight += MOST_LIKELY_NOT_MALICIOUS
    end

    # File Extension Weight Calculation
    weight += CONFIRMED_MALICIOUS if DANGEROUS_FILE_EXTENSIONS.include? record["file_extension"]

    weight
end

def classify_data(data, training)
  correct = count = current_result = incorrect = weight = 0
  results = []

  data.each do |record|
    weight = calculate_weight(record)
    current_result = malicious?(weight)
    
    if training
      results << "#{record["url"]}: #{current_result}:#{record["malicious_url"]}"
      current_result == record["malicious_url"] ? correct += 1 : incorrect += 1
    else
      results << "#{record["url"]}: #{current_result}"
    end
  end

  return_payload = {
    "results" => results,
    "accuracy" => [correct, incorrect]
  }
end

def fetch_and_process_user_selected_file_data
  valid_json_files = Dir["*.json"]

  selection = gets.chomp.to_i
  JSON.parse(File.read(valid_json_files[selection]))
end

def malicious?(weight)
  weight >= 50 ? 1 : 0
end

def output_results(results)
  file = File.open("results.txt", "w")

  results.each { |outcome| file << outcome + "\n" }

  file.close
end

def print_file_options
  valid_json_files = Dir["*.json"]

  puts "Select the file JSON file you wish to classify:"
  valid_json_files.each_with_index { |name, i| puts "(#{i}): #{name}" }

  valid_json_files
end

def print_accuracy(accuracy)
  correct, incorrect = accuracy
  puts "Correct: #{correct}, Incorrect: #{incorrect}"
end

def training?
  puts "Is this a training set? y/n"
  input = gets.chomp
  input == "y"
end

# Main Program
print_file_options

file_data = fetch_and_process_user_selected_file_data
training = training?

outcome = classify_data(file_data, training)

output_results(outcome["results"])
print_accuracy(outcome["accuracy"]) if training
