import pandas as pandas
from os import listdir
from tabulate import tabulate

#---------------------------Start-Of-Sad-Variables---------------------------#
#Files is a list of files in the data folder
files = listdir("./data")

#Some variables for later
picked_file = None
picked_column = None
list_of_headers = []
#----------------------------End-Of-Sad-Variables----------------------------#

#Iterate through the files and print out the "index" of the file
index = 1
for file in files:
    print(str(index) + ": " + file)
    index += 1

#A loop to check to see if the file chosen is within the bounds of the files available
while picked_file is None:
    picked_file = input("Pick a file to examine: ") - 1

    if picked_file > len(files) - 1 or picked_file < 0:
        picked_file = None
        print("Please pick a number within the bounds of the list.")
        continue

#Read the CSV file selected
print("You selected: " + files[picked_file])
df = pandas.read_csv("./data/" + files[picked_file])

for i in df:
    print(df[i].dtype)
