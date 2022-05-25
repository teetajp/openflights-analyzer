import csv

filename = "Processed_Data.csv"

# Read data from file into Python
f = open(filename, "r")

source_airports = []
dest_airports = []

for entry in f:
  source_airports.append(entry[1: 4])
  dest_airports.append(entry[4: 7])

airports = []

for i in range(len(source_airports)):
  if source_airports[i] not in airports:
    airports.append(source_airports[i])
  if dest_airports[i] not in airports:
    airports.append(dest_airports[i])

airports.sort()

with open("airports.txt", "w") as output:
  for airport in airports:
    output.write(airport + '\n')