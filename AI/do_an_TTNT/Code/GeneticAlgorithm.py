import random
import Chromosome as ch

# random list
def create_random_list(city_list):
	# start depend on data
	start = city_list[0]
	temp = city_list[1:]
	temp = random.sample(temp, len(temp))
	temp.insert(0, start)
	temp.append(start)
	return temp

# initialize population
def initialization(data, pop_size):
	initial_population = []
	for i in range(0, pop_size):
		temp = create_random_list(data)
		new_ch = ch.Chromosome(temp)
		initial_population.append(new_ch)
	return initial_population

# selection
def selection(population):
	pos_ADN1, pos_ADN2, pos_ADN3, pos_ADN4 = random.sample(range(0, 99), 4)

	ADN1 = population[pos_ADN1]
	ADN2 = population[pos_ADN2]
	ADN3 = population[pos_ADN3]
	ADN4 = population[pos_ADN4]

	if ADN1.fitness > ADN2.fitness:
		winner = ADN1
	else:
		winner = ADN2
	if ADN3.fitness > winner.fitness:
		winner = ADN3
	if ADN4.fitness > winner.fitness:
		winner = ADN4
	return winner


def crossover(p1, p2):
	t1, t2 = random.sample(range(1, len(p1.chromosome)-1), 2)
	begin = min(t1, t2)
	end = max(t1, t2)
	child1 = p1.chromosome[begin:end+1]
	child2 = p2.chromosome[begin:end+1]

	child1_ = [x for x in p2.chromosome[1:-1] if x not in child1]
	child2_ = [x for x in p1.chromosome[1:-1] if x not in child2]

	child1 += child1_
	child2 += child2_

	child1.insert(0, p1.chromosome[0])
	child1.append(p1.chromosome[0])

	child2.insert(0, p2.chromosome[0])
	child2.append(p2.chromosome[0])
	return child1, child2

# mutation
def mutation(chromosome):
	d1, d2 = random.sample(range(1,19), 2)
	chromosome[d1], chromosome[d2] = chromosome[d2], chromosome[d1]
	return chromosome

# find_best
def find_best(generation):
	best = generation[0]
	for x in range(1, len(generation)):
		if generation[x].cost < best.cost:
			best = generation[x]
	return best

# major function : create_new_generation
def create_new_generations(previous_generation, mutation_rate):
	new_generation = [find_best(previous_generation)]
	for x in range(0, int(len(previous_generation)/2)):
		parent1 = selection(previous_generation)
		parent2 = selection(previous_generation)
		# crossover
		child1, child2 = crossover(parent1, parent2)
		# convert to chromosome
		child1 = ch.Chromosome(child1)
		child2 = ch.Chromosome(child2)
		if random.random() < mutation_rate:
			mutated1 = mutation(child1.chromosome)
			child1 = ch.Chromosome(mutated1)

		new_generation.append(child1)
		new_generation.append(child2)
	return new_generation


