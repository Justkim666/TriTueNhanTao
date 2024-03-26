# a = int(input('Enter tankcapacity X : '))
# b = int(input('Enter tankcapacity Y: '))
# t = int(input('Enter goal: '))
# a, b = min(a, b), max(a, b)  
a, b, t = 9, 4, 6

def is_solved(state):
        return t in state


def get_neighbors(state):
        a_to_b = min(state[0], b - state[1])
        b_to_a = min(state[1], a - state[0])
        return [
                ((a, state[1]), f'Pour Water Full X({a})'),
                ((state[0], b), f'Pour Water Full Y({b})'),
                ((0, state[1]), f'pour Water Empty X({a})'),
                ((state[0], 0), f'pour Water Empty Y({b})'),
                ((state[0] - a_to_b, state[1] + a_to_b),
                  f'pour Water X({a}) to Y({b})'),
                ((state[0] + b_to_a, state[1] - b_to_a),
                  f'Pour Water Y({b}) to X({a})')
        ]



state = (0, 0)
q = [state]
visited = {state}
prev = {state: None}
action = {}
i = 1
while len(q) and i > 0:
		curr_state = q.pop(0)
		if is_solved(curr_state):
			prev[neighbor] = curr_state
			break

		for neighbor, action_description in get_neighbors(curr_state):
				if neighbor not in visited:
					prev[neighbor] = curr_state
					action[neighbor] = action_description
					visited.add(neighbor)
					q.append(neighbor)

if not is_solved(curr_state):
        print('No solution...')
else:
        instructions = []
        path = []
        while prev[curr_state] is not None:
                instructions.insert(0, action[curr_state])
                path.insert(0, curr_state)
                curr_state = prev[curr_state]
        print('Action 0: First State')
        print(state)
        for i in range(0, len(instructions)):
	        print(f'Action {i+1}: ' + instructions[i])
	        print(path[i])
