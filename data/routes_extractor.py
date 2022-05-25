import csv

filename = "Processed_Data.csv"

# Read data from file into Python
f = open(filename, "r")

routes = []

# First three char is source airport, next three is destination airport, last char is number of stops
for entry in f:
  routes.append(entry[1:8])


with open("routes.txt", "w") as output:
  for route in routes:
    output.write(route + '\n')