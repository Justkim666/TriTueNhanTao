import math

class City:
	def __init__(self, id, x, y):
		self.x = float(x)
		self.y = float(y)
		self.id = int(id)

# read file
file_name = "training_dataset"
dataset = []

with open(file_name, "r") as f:
	for line in f:
		new_line = line.strip()
		new_line = new_line.split(" ")
		id, x, y = new_line[0], new_line[1], new_line[2]
		dataset.append(City(id=id, x=x, y=y))

# declare number of city
N =  20

# 2D matrix - calculate
def calculate_distance(city_list):
	matrix2D = [[0 for x in range(N)] for x in range(N)]
	for i in range(0, len(matrix2D)-1):
		for j in range(0, len(matrix2D)-1):
			matrix2D[city_list[i].id][city_list[j].id] = math.sqrt(
				pow((city_list[i].x - city_list[j].x), 2) + pow((city_list[i].y - city_list[j].y), 2))
	return matrix2D

# calculate
matrix = calculate_distance(dataset)

class Chromosome:
	def __init__(self, city_list):
		self.chromosome = city_list
		chr_representation = []
		for i in range(0, len(city_list)-1):
			chr_representation.append(self.chromosome[i].id)
		self.chr_representation = chr_representation
		distance = 0 
		for j in range(1, len(self.chr_representation)-1):
			distance += matrix[self.chr_representation[j]-1][self.chr_representation[j+1]-1]
		self.cost = distance
		self.fitness = 1 / self.cost

