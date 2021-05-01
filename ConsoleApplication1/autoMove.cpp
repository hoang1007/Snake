#include "Snake.hpp"
#include <vector>
#include <stack>
#include <iostream>

const int SIZE = 6;

bool map[SIZE][SIZE] = 
{
	{0, 0, 0, 0, 0, 1},			// 0 là vị trí của snake 
	{1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 1},
};

struct Coordinate
{
	int x, y;
	Coordinate() { x = y = numCode = 0; }
	Coordinate(int _x, int _y)
	{
		x = _x;
		y = _y;
		numCode = x + y * SIZE;
	}
	Coordinate(int _numCode)
	{
		numCode = _numCode;
		x = numCode % SIZE;
		y = numCode / SIZE;
	}
	Coordinate(Block pSnake)
	{
		x = pSnake.x / GRID - 2;
		y = pSnake.y / GRID - 2;
		numCode = x + y * SIZE;
	}

	bool insideMap()
	{
		return x >= 0 && x < SIZE&& y >= 0 && y < SIZE;
	}

	int toNum()
	{
		return numCode;
	}

	bool& getMapValue()
	{
		return map[y][x];
	}
private:
	int numCode;
};

struct TreeCycle
{
	struct Node;
	Node* root;
	std::vector<Node*> path;
	TreeCycle() { root = nullptr; }
	TreeCycle(int value)
	{
		root = new Node(value, 0);
	}
	void clear(Node* &node)
	{
		if (node == nullptr) return;
		clear(node->left_child);
		clear(node->right_child);
		node = nullptr;
		delete node;
	}
	~TreeCycle()
	{
		clear(root);
	}
	void build(Node*& node, const int &End, const int &path_length);
	Node* findShortestPath(int food)
	{
		Node* shortest = nullptr;
		int max = 0;
		for (int i = 0; i < path.size(); i++)
		{
			int path_length = 0;
			Node* temp = path[i];
			while (temp->data != food)
			{
				path_length++;
				temp = temp->parent;
			}
			if (max < path_length)
			{
				max = path_length;
				shortest = temp;
			}
		}
		path.clear();
		return shortest;
	}
	struct Node
	{
		int data;
		int depth;
		Node* parent;
		Node* left_child;
		Node* right_child;

		Node()
		{
			data = 0;
			depth = 0;
			parent = left_child = right_child = nullptr;
		}
		Node(int value, int _depth)
		{
			data = value;
			depth = _depth;
			parent = left_child = right_child = nullptr;
		}
	};
};

Direction Snake::autoMove(Block _food)
{
	static stack<Direction> path;
	Coordinate head = Coordinate(front());
	Coordinate tail = Coordinate(back());

	map[tail.y][tail.x] = true;
	map[head.y][head.x] = false;
	
	if (path.empty())
	{
		TreeCycle pathTree(head.toNum());
		Coordinate food = Coordinate(_food);
		pathTree.build(pathTree.root, tail.toNum(), SIZE * SIZE - size() - 1);
		TreeCycle::Node* shortest = pathTree.findShortestPath(food.toNum());
		while (shortest->parent)
		{
			Coordinate src = Coordinate(shortest->parent->data),
				dst = Coordinate(shortest->data);

			if (src.x + 1 == dst.x) path.push(RIGHT);
			else if (src.x - 1 == dst.x) path.push(LEFT);
			else if (src.y + 1 == dst.y) path.push(DOWN);
			else path.push(UP);
			shortest = shortest->parent;
		}
	}
	
	if (!path.empty())
	{
		Direction dir = path.top();
		path.pop();
		return dir;
	}
	return nextDir;
}

void TreeCycle::build(Node*& node, const int& End, const int& path_length)
{
	if (path.size() == 4) return;
	if (node == nullptr) return;
	if (node->depth == path_length && (End == node->data))
	{
		path.push_back(node);
		return;
	}

	Coordinate node_coor(node->data);
	//theo chieu up => down => left => right
	Coordinate neighbor[4];

	neighbor[UP] = Coordinate(node_coor.x, node_coor.y - 1),
	neighbor[DOWN] = Coordinate(node_coor.x, node_coor.y + 1),
	neighbor[LEFT] = Coordinate(node_coor.x - 1, node_coor.y),
	neighbor[RIGHT] = Coordinate(node_coor.x + 1, node_coor.y);

	vector<int> isLegal;
	for (int i = 0; i < 4; i++)
		if (neighbor[i].insideMap() & map[neighbor[i].y][neighbor[i].x])
			isLegal.push_back(i);

	if (isLegal.size() == 0) return;
	if (isLegal.size() == 3)
	{
		int shortest = INT_MAX;
		int shortest_e = 0;
		for (int i = 0; i < 3; i++)
		{
			int dist = abs(End - neighbor[isLegal[i]].toNum());
			if (dist < shortest)
			{
				shortest = dist;
				shortest_e = i;
			}
		}
		isLegal.erase(isLegal.begin() + shortest_e);
	}

	node->left_child = new Node(neighbor[isLegal.front()].toNum(), node->depth + 1);
	node->left_child->parent = node;
	neighbor[isLegal.front()].getMapValue() = false;
	build(node->left_child, End, path_length);
	neighbor[isLegal.front()].getMapValue() = true;

	if (isLegal.size() == 2)
	{
		node->right_child = new Node(neighbor[isLegal.back()].toNum(), node->depth + 1);
		node->right_child->parent = node;
		neighbor[isLegal.back()].getMapValue() = false;
		build(node->right_child, End, path_length);
		neighbor[isLegal.back()].getMapValue() = true;
	}
}