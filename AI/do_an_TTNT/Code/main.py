import GeneticAlgorithm as GA
import Chromosome as Ch
import numpy as np
import matplotlib.pyplot as plt


# number of generations
number_of_generations = 200
# number of indivitual in population
population_size = 100
# what percent mutation ?
mut_rate = 0.2
# data
dataset = Ch.dataset

# genetic_algorithm
def genetic_algorithm(number_of_generations, pop_size, mutation_rate, data_list):
	new_gen = GA.initialization(data_list, pop_size)
	draw_graph = []
	# main loop
	for i in range(0, number_of_generations):
		new_gen = GA.create_new_generations(new_gen, mutation_rate)
		# show significant change 
		print(str(i) + ". generation --> " + "cost --> " + str(new_gen[0].cost))
		draw_graph.append(GA.find_best(new_gen).cost)
		# show final path
		if i == number_of_generations - 1:
			for i in range(0, len(data_list)):
				if i != len(data_list)-1:
					print(str(new_gen[0].chr_representation[i]) + " -> ", end='')
				else:
					print(str(new_gen[0].chr_representation[i]) + " -> " + str(new_gen[0].chr_representation[0]))
	return new_gen, draw_graph

def draw_cost_generation(y_list):
	x_list = np.arange(1, len(y_list)+1) # np.arange(start,stop,step) => ndarray
	plt.plot(x_list, y_list) # plt.plot(x-axis, y-axis)
	plt.title("Route Cost through Generation")
	plt.xlabel("Generation")
	plt.ylabel("Cost")
	plt.show()

def draw_path(solution):
	x_list = []
	y_list = []

	for m in range(0, len(solution.chromosome)):
		x_list.append(solution.chromosome[m].x)
		y_list.append(solution.chromosome[m].y)

	fig, ax = plt.subplots(1,1) # plt.subplots(nrows, ncol)
	plt.scatter(x_list, y_list, color='r') # plt.scatter(list_x, list_y, color)

	ax.plot(x_list, y_list, '--', lw=2,color='black')
	ax.set_xlim(0, 1700)
	ax.set_ylim(0, 1300)
	plt.show()

last_generation, y_axis = genetic_algorithm(
	number_of_generations=number_of_generations, pop_size=population_size, mutation_rate = mut_rate,
	data_list = dataset)
best_solution = GA.find_best(last_generation)
draw_cost_generation(y_axis)
draw_path(best_solution)