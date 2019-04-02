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

#Strip whitespace of files that match string type object type
df = df.apply(lambda value: value.str.strip() if value.dtype == "object" else value)


print("What would you like to sort by? Here are your options:")

#List of available headers and add them to a list as we do
index = 1
for header in df:
    print(str(index) + ": " + header)
    list_of_headers.append(header);
    index += 1

#A loop to check to see if the column chosen is within the bounds of the columns available
while picked_column is None:
    picked_column = input("I want to sort by (input the number): ") - 1
    if picked_column > len(list_of_headers) - 1 or picked_column < 0:
        picked_column = None
        print("Please pick a number within the bounds of the list.")
        continue

#Print the dataframe to show the user that is sorted based on selection
print(tabulate(df.sort_values(list_of_headers[picked_column]), headers='keys', tablefmt='psql', showindex=False))

#Convert object type of Price column to numeric type for mean calculations
df['Price'] = df['Price'].apply(pandas.to_numeric)

#Counting the number of Amandas in the data and the average of the price column
name_count = df['Name'].str.contains('amanda', case=False, regex=False).sum()
average_price = df['Price'].mean()

print("\nNumber of Amandas in dataset: " + str(name_count))
print("Average price: " + str(average_price))

#Replace United States with USA and print the number of changes that are mad
record_changes = df['Country'].str.contains('United States', case=False, regex=False).sum()
df['Country'] = df['Country'].replace('United States', 'USA')

print("Number of record changes: " + str(record_changes))

#Exporting the newly cleaned data to a separate cleaned data folder
df.to_csv("./clean_data/" + files[picked_file], index=False)
