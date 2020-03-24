#include <iostream>
#include <queue>
#include <stack>
using namespace std;

const int bottle1Max = 5;
const int bottle2Max = 3;
const int result = 4;

struct State
{
	int bottle1;
	int bottle2;
	State* parent;

	State(int bottle1, int bottle2) {
		this->bottle1 = bottle1;
		this->bottle2 = bottle2;
		parent = NULL;
	}
};
vector<State*> Nodes;
bool solve();
State* createState(int, int);
bool checkState(int, int);
void printResult();

int main()
{
	bool solved = solve();

	if (solved) {
		printResult();
	}
	else {
		cout << "Can not find solution";
	}
    
}

bool solve() { //BFS
	State *initial = new State(0, 0);
	queue<State*> q;
	q.push(initial);
	Nodes.push_back(initial);

	while (!q.empty()) {
		State *current = q.front();
		q.pop();

		while (true) {
			State *newState = createState(current->bottle1, current->bottle2);
			if (newState->bottle1 == -1) {
				break;
			}
			newState->parent = current;
			Nodes.push_back(newState);

			if (newState->bottle1 == result || newState->bottle2 == result) {
				return true;
			}
			q.push(newState);
		}
	}

	return false;
}

// create new Node of bottles
State* createState(int bottle1, int bottle2) {
	int newbottle1 = 0;
	int newbottle2 = 0;
	bool isUnique;
	State *newState = new State(0, 0);

	if (bottle1 != bottle1Max) {	// make first bottle full
		newbottle1 = bottle1Max;
		newbottle2 = bottle2;
		isUnique = checkState(newbottle1, newbottle2);
		if (isUnique) {
			newState->bottle1 = newbottle1;
			newState->bottle2 = newbottle2;
			return newState;
		}
		else {
			newbottle1 = 0;
			newbottle2 = 0;
		}
	}
	if (bottle2 != bottle2Max) {	// make second bottle full
		newbottle1 = bottle1;
		newbottle2 = bottle2Max;
		isUnique = checkState(newbottle1, newbottle2);
		if (isUnique) {
			newState->bottle1 = newbottle1;
			newState->bottle2 = newbottle2;
			return newState;
		}
		else {
			newbottle1 = 0;
			newbottle2 = 0;
		}
	}
	if (bottle1 != bottle1Max && bottle2 != 0) {	// pour from second bottle to first
		int addTobottle1 = bottle1Max - bottle1;
		newbottle1 = bottle1 + (bottle2 <= addTobottle1 ? bottle2 : addTobottle1);
		newbottle2 = bottle2 <= addTobottle1 ? 0 : bottle2 - addTobottle1;
		isUnique = checkState(newbottle1, newbottle2);
		if (isUnique) {
			newState->bottle1 = newbottle1;
			newState->bottle2 = newbottle2;
			return newState;
		}
		else {
			newbottle1 = 0;
			newbottle2 = 0;
		}
	}
	if (bottle2 != bottle2Max && bottle1 != 0) {	// pour from first bottle to second
		int addTobottle2 = bottle2Max - bottle2;
		newbottle2 = bottle2 + (bottle1 <= addTobottle2 ? bottle1 : addTobottle2);
		newbottle1 = bottle1 <= addTobottle2 ? 0 : bottle1 - addTobottle2;
		isUnique = checkState(newbottle1, newbottle2);
		if (isUnique) {
			newState->bottle1 = newbottle1;
			newState->bottle2 = newbottle2;
			return newState;
		}
		else {
			newbottle1 = 0;
			newbottle2 = 0;
		}
	}
	if (bottle1 != 0) {		// make first bottle empty
		newbottle1 = 0;
		newbottle2 = bottle2;
		isUnique = checkState(newbottle1, newbottle2);
		if (isUnique) {
			newState->bottle1 = newbottle1;
			newState->bottle2 = newbottle2;
			return newState;
		}
		else {
			newbottle1 = 0;
			newbottle2 = 0;
		}
	}
	if (bottle2 != 0) {		// make second bottle empty
		newbottle1 = bottle1;
		newbottle2 = 0;
		isUnique = checkState(newbottle1, newbottle2);
		if (isUnique) {
			newState->bottle1 = newbottle1;
			newState->bottle2 = newbottle2;
			return newState;
		}
		else {
			newbottle1 = 0;
			newbottle2 = 0;
		}
	}

	return new State(-1, -1);
}

// check if current Node of bottles is not copy of existing Nodes
bool checkState(int bottle1, int bottle2) {
	bool isUnique = true;

	for (int i = 0; i < Nodes.size(); i++)	{
		State *Node = Nodes[i];
		if (Node->bottle1 == bottle1 && Node->bottle2 == bottle2) {
			isUnique = false;
			break;
		}
	}

	return isUnique;
}

void printResult() {
	State *Node = Nodes.back();
	stack<State*> s;
	while (true) {
		s.push(Node);
		if (!Node->parent) {
			break;
		}
		Node = Node->parent;
	}
	cout << "bottle1max = " << bottle1Max << " bottle2max = "<< bottle2Max << endl;
	while (!s.empty()) {
		Node = s.top();
		s.pop();
		cout << Node->bottle1 << " " << Node->bottle2 << endl;
	}
}