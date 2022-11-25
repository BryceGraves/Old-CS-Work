require 'io/console'

class RockPaperScissors
  def initialize
    @beats = {
      "rock" => "scissors",
      "scissors" => "paper",
      "paper" => "rock"
    }
    @player_input = []
  end

  def play
    gather_player_input until valid_input?
    outcome = calculate_winner(@player_input.first, @player_input.last)
    print_outcome(outcome)
  end

  private

  def calculate_winner(first, second)
    @beats[first] == second ? {"winner" => first, "loser" => second} : {"winner" => second, "loser" => first}
  end

  def gather_player_input
    @player_input = []

    puts "Player One: input your choice"
    @player_input << STDIN.noecho(&:gets).strip.downcase

    puts "Player Two: input your choice"
    @player_input << STDIN.noecho(&:gets).strip.downcase
  end

  def print_outcome(outcome)
    puts "Player One Chose: #{@player_input.first}\n" +
    "Player Two Chose: #{@player_input.last}\n" +
    outcome["winner"].capitalize + " beats " + outcome["loser"] + "!"
  end

  def valid_input?
    @beats.keys.include?(@player_input.first) && @beats.keys.include?(@player_input.last)
  end

end

RockPaperScissors.new.play
