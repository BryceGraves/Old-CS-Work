from getpass import getpass

player_input = []
beats = {
  "rock": "scissors",
  "scissors": "paper",
  "paper": "rock"
}

player_input.append(getpass("Player One Input Your choice: "))
player_input.append(getpass("Player Two Input Your choice: "))

outcome = {"winner": player_input[0], "loser": player_input[1]} if beats[player_input[0]] == player_input[1] else {"winner": player_input[1], "loser": player_input[0]}
print(outcome["winner"].capitalize() + " beats " + outcome["loser"] + "!")
