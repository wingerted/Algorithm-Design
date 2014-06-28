#include <iostream>
#include <queue>
#include <algorithm>
#include <cmath>

using namespace std;

struct Node {
	int x;
	int y;
	int f;
	int h;
	int g;
	Node *parent;
	void GetValueF() {this->f = this->g + this->h;};

	Node () {
	} 
	Node (const Node &node) {
		this->x = node.x;
		this->y = node.y;
		this->f = node.f;
		this->h = node.h;
		this->g = node.g;
		this->parent = new Node();
		if (!node.parent) {
			this->parent = NULL;
		} else {
			*(this->parent) = *(node.parent);
		}
	}
	friend bool operator< (const Node &first, const Node &second);
};

bool operator< (const Node &first, const Node &second) {
	return first.f > second.f;
}


Node* NodeNext(int map[][10], Node &parent, int x_step, int y_step, Node &end) {
	Node* current = new Node();
	current->parent = &parent;
	current->x = parent.x + x_step;
	current->y = parent.y + y_step;
	current->g = parent.g + 1;
	current->h = abs(end.x - current->x) + abs(end.y - current->y);
	current->GetValueF();

	if (current->x < 0 || current->x > 9) {
		return NULL;
	} else if (current->y < 0 || current->y > 9) {
		return NULL;
	} else if (map[current->x][current->y] != 0) {
		return NULL;
	}

	return current;
}


void A_Star_Search(int map[][10], Node &start, Node &end) {
	priority_queue<Node> node_queue_open;
	bool visited[10][10];
	for (int i=0; i<10; ++i) {
		for (int j=0; j<10; ++j) {
			visited[i][j] = false;
		}
	}

	start.parent = NULL;
	start.g = 0;
	start.h = (abs(end.x - start.x) + abs(end.y - start.y)) * 10;
	start.GetValueF();
	node_queue_open.push(start);

	while (!node_queue_open.empty()) {
		Node current = node_queue_open.top();
  		node_queue_open.pop();

		int x_step_array[4] = {1, 0, -1, 0};
		int y_step_array[4] = {0, 1, 0, -1};
		for (int i=0; i<4; ++i) {
			Node *next = NodeNext(map, current, x_step_array[i], y_step_array[i], end);
			if (next && !visited[next->x][next->y]){
				node_queue_open.push(*next);
			}
		}

		if (current.x == end.x && current.y == end.y) {
			end.parent = current.parent;
			return;
		}
		visited[current.x][current.y] = true;
	}
}


int main()
{
	int map[10][10];

	for (int i=0; i<10; ++i) {
		for (int j=0; j<10; ++j) {
			map[i][j] = 0;
		}
	}


	Node start;
	Node end;
	start.x = 0;
	start.y = 0;
	end.x = 4;
	end.y = 4;

	A_Star_Search(map, start, end);
	
	for (Node *p = &end; p; p=p->parent) {
		cout << "x: " << p->x << "  y: " << p->y << endl;
	}

	return 0;
}