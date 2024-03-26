#include <iostream>
#include <vector>
#include<stdlib.h>
#define BROWN_FROG 1
#define YELLOW_FROG 2
#define NO_FROG 0

typedef struct
{
    int position[7];
} State;

typedef struct Node
{
    State state;
    struct Node *parent;
} * Tree;

State initialState()
{
    State state = {{BROWN_FROG, BROWN_FROG, BROWN_FROG, NO_FROG, YELLOW_FROG, YELLOW_FROG, YELLOW_FROG}};

    return state;
}

Tree createRoot()
{
    Tree root = (Tree)malloc(sizeof(struct Node));
    root->state = initialState();
    root->parent = NULL;
    return root;
}

namespace actions
{
    State move(State parentState, int index, int steps)
    {
        if (steps < 1 || steps > 2)
            return parentState;

        switch (parentState.position[index])
        {
        case BROWN_FROG:
            if (index + steps > 6)
                break;
            if (parentState.position[index + steps] != NO_FROG)
                break;

            parentState.position[index] = 0;
            parentState.position[index + steps] = BROWN_FROG;
            break;

        case YELLOW_FROG:
            if (index + steps < 0)
                break;
            if (parentState.position[index - steps] != NO_FROG)
                break;

            parentState.position[index] = 0;
            parentState.position[index - steps] = YELLOW_FROG;
            break;

        default:
            break;
        }

        return parentState;
    }
}

Tree findChildNode(
    Tree parent,
    State(action(State parentState, int index, int steps)),
    int index,
    int steps)
{
    Tree child = createRoot();
    child->parent = parent;
    child->state = action(parent->state, index, steps);

    return child;
}

bool isEqualState(State st1, State st2)
{
    for (int i = 0; i < 7; i++)
    {
        if (st1.position[i] != st2.position[i])
        {
            return false;
        }
    }
    return true;
}

bool isExisting(const State &state, const std::vector<Tree> &queue)
{
    for (auto el = queue.begin(); el != queue.end(); el++)
    {
        if (isEqualState(state, (*el)->state))
        {
            return true;
        }
    }
    return false;
}

bool isGoal(const State &state)
{
    State goalState = {{YELLOW_FROG,
                        YELLOW_FROG,
                        YELLOW_FROG,
                        NO_FROG,
                        BROWN_FROG,
                        BROWN_FROG,
                        BROWN_FROG}};

    return isEqualState(state, goalState);
}

void printParent(const Tree &child)
{
    if (child->parent == NULL)
    {
        std::printf(
            "[%d, %d, %d, %d, %d, %d, %d]\n",
            child->state.position[0],
            child->state.position[1],
            child->state.position[2],
            child->state.position[3],
            child->state.position[4],
            child->state.position[5],
            child->state.position[6]);
        return;
    }

    printParent(child->parent);

    std::printf(
        "-> [%d, %d, %d, %d, %d, %d, %d]\n",
        child->state.position[0],
        child->state.position[1],
        child->state.position[2],
        child->state.position[3],
        child->state.position[4],
        child->state.position[5],
        child->state.position[6]);
    return;
}

void solution(Tree root)
{
    std::vector<Tree> Open, Closed;

    Open.push_back(root);

    int count = 0;

    while (!Open.empty())
    {
        Tree front = Open.front();
        Open.erase(Open.begin());
        Closed.push_back(front);
        count++;

        if (isGoal(front->state))
        {
            std::cout << count << std::endl;
            break;
        }

        for (int steps = 1; steps <= 2; steps++)
        {
            for (int i = 0; i < 7; i++)
            {
                Tree child = findChildNode(front, actions::move, i, steps);
                if (!isExisting(child->state, Open) && !isExisting(child->state, Closed))
                {
                    Open.push_back(child);
                }
            }
        }
    }
    printParent(Closed.back());
}

int main()
{
    Tree root = createRoot();
    solution(root);
    return 0;
}
