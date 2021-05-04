
/*
* Mỗi khi bắt đầu game hoặc rắn ăn thức ăn ta đi tìm một chu trình khép kín từ đầu tới đuôi của rắn
* đi qua tất cả các ô vuông trên bản đồ mỗi ô một lần (chu trình Hamilton)
*
* Vì con rắn luôn đi theo chu trình trên nên lúc nào cũng tồn tại ít nhất một con đường sao cho
* rắn không bao giờ tự đâm vào chính nó trừ khi chiều dài của nó vượt quá số ô vuông trên bản đồ
*
* Sử dụng cây nhị phân vét cạn mọi đường đi có thể để tìm ra chu trình Hamilton
* từ đó ta tìm ra con đường ngắn nhất từ đầu rắn tới thức ăn và đi theo nó
*
* Vì độ phức tạp là O(2^n) nên bản đồ chỉ giới hạn ở kích thước 6x6 để không bị time limit
*/


#include "Snake.hpp"
#include "Food.hpp"
#include <iostream>
#include <vector>
#include <stack>

const int SIZE = 6;	// mặc định kích thước bản đồ là 6x6 

// bản đồ mô tả vị trí của rắn để có thể xét va chạm với O(1)
// với mỗi nước đi của rắn ta cập nhật lại bản đồ (đầu mới thêm là 0 và đuôi xóa đi là 1)

bool map[SIZE][SIZE] =
{
	{0, 0, 0, 0, 0, 1},			// 0 là vị trí của snake 
	{1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 1},
};

// Tọa độ trên map với serial là số thứ tự của các ô vuông trên map
// map trên khi chuyển sang serial
/*
* 00 01 02 03 04 05
* 06 07 08 09 10 11
* 12 13 14 15 16 17
* 18 19 20 21 22 23
* 24 25 26 27 28 29
* 30 31 32 33 34 35
*/

struct Coordinate
{
	int x, y;
	Coordinate() { x = y = serial = 0; }
	// chuyển tọa độ thành serial 
	Coordinate(int _x, int _y)
	{
		x = _x;
		y = _y;
		serial = x + y * SIZE;
	}
	// chuyển serial thành tọa độ
	Coordinate(int _serial)
	{
		serial = _serial;
		x = serial % SIZE;
		y = serial / SIZE;
	}
	// nhận tọa độ trên bản đồ thật trên game và chuyển về tọa độ tương ứng với map bool
	Coordinate(Block pSnake)
	{
		x = pSnake.x / GRID - 2;
		y = pSnake.y / GRID - 2;
		serial = x + y * SIZE;
	}

	// kiểm tra xem tọa độ có phù hợp hay không 
	bool insideMap()
	{
		return x >= 0 && x < SIZE&& y >= 0 && y < SIZE;
	}

	// trả về serial 
	int toNum()
	{
		return serial;
	}

	// lấy giá trị của map bool 
	bool& mapValue()
	{
		return map[y][x];
	}
private:
	int serial;
};

// Cây nhị phân tìm đường 
struct TreeCycle
{
	// Node của cây
	struct Node;

	Node* root;
	vector<Node*> destination;	// lưu lại node cuối của mỗi chu trình để truy ra cả chu trình 
	TreeCycle() { root = nullptr; }
	TreeCycle(int value)
	{
		root = new Node(value, 0);
	}
	// Thu hồi vùng nhớ khi hoàn thành 
	void clear(Node*& node)
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

	// tìm tất cả các chu trình Hamilton 
	void build(Node*& node, const int& End, const int& path_length);

	// tìm đường đi xa nhất từ đuôi rắn đến thức ăn
	// tức là gần nhất từ đầu tới thức ăn 
	Node* findShortestPath(int food)
	{
		Node* shortest = nullptr;
		int max = INT_MIN;

		for (int i = 0; i < destination.size(); i++)
		{
			int path_length = 0;
			// duyệt từ phía cuối chu trình lên đầu
			// lưu lại số node phải đi và so sánh với các chu trình khác 
			for (; destination[i]->data != food; destination[i] = destination[i]->parent, path_length++);

			if (max < path_length)	// nếu tìm thấy chu trình nào có thức ăn xa hơn đuôi thì cập nhật shortest 
			{
				max = path_length;
				shortest = destination[i];
			}
		}
		destination.clear();	// xóa tất cả các chu trình cũ để tìm các chu trình mới 
		return shortest;
	}

	struct Node
	{
		int data;	// giá trị của node <=> serial trong Coordinate 
		int depth;	// độ sâu của node 
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
	// tọa độ của head và tail trên bitmap
	Coordinate head = Coordinate(front());
	Coordinate tail = Coordinate(back());

	// cập nhật vị trí của rắn trên bitmap 
	map[tail.y][tail.x] = true;
	map[head.y][head.x] = false;
	// global variable
	static ReverseQueue<Direction> path;	// lưu lại hướng đi khi truy ngược
	if (path.empty())
	{
		cerr << "path finding...\n";;
		TreeCycle pathTree(head.toNum());
		Coordinate food = Coordinate(_food);

		pathTree.build(pathTree.root, tail.toNum(), 31); // 31 la chieu dai cua chu trinh Halminton

		TreeCycle::Node* shortest = pathTree.findShortestPath(food.toNum());

		if (shortest)
		{
			while (shortest->parent)
			{
				// truy ngược node cuối 
				// từ độ chênh lệch tọa độ giữa node cha và con ta tính ra các hướng đi 
				Coordinate src = Coordinate(shortest->parent->data),
					dst = Coordinate(shortest->data);

				if (src.x + 1 == dst.x) path.push_back(RIGHT);
				else if (src.x - 1 == dst.x) path.push_back(LEFT);
				else if (src.y + 1 == dst.y) path.push_back(DOWN);
				else path.push_back(UP);
				shortest = shortest->parent;
			}
		}
		else return nextDir;
	}

	if (!path.empty())	// mỗi lượt đi trả về các hướng đi 
	{
		return path.pop();
	}
	return nextDir;	// nếu có lỗi trả về hướng đi hiện tại 
}

void TreeCycle::build(Node*& node, const int& End, const int& path_length)
{
	if (destination.size() == 8) return;	// giới hạn số chu trình tìm được để tiết kiệm thời gian 
	if (node == nullptr) return;

	// vì chu trình đi qua tất cả các ô trên map trừ rắn 
	// nên node cuối cùng phải có độ sâu bằng số ô trống trên map (path_length)

	if (End == node->data)
	{
		if (node->depth == path_length)
			destination.push_back(node);
		return;
	}

	Coordinate node_coor(node->data);	// chuyển node thành tọa độ trên map bool để xét các ô xung quanh 

	// với mỗi node tìm các hướng đi có thể di chuyển 
	Coordinate neighbor[4];

	neighbor[UP] = Coordinate(node_coor.x, node_coor.y - 1),
	neighbor[DOWN] = Coordinate(node_coor.x, node_coor.y + 1),
	neighbor[LEFT] = Coordinate(node_coor.x - 1, node_coor.y),
	neighbor[RIGHT] = Coordinate(node_coor.x + 1, node_coor.y);

	// xét các ô xung quanh nếu ở trong map và có thể đi thì đẩy vào vector isLegal 
	vector<int> isLegal;
	for (int i = 0; i < 4; i++)
		if (neighbor[i].insideMap() && neighbor[i].mapValue())
			isLegal.push_back(i);

	if (isLegal.size() == 0) return;	// nếu không có hướng đi nào thì thoát 

	// nếu cả 3 hướng đi đều có thể đi thì loại hướng đi chia map thành 2 nửa 
	// hoặc hướng đi tiến gần tới điểm cuối cùng nhất để có thể cài đặt cây nhị phân 
	if (isLegal.size() == 3)
	{
		// loại hướng đi mà ngăn cách map (sát với tường)
		int need_erase = INT_MAX;
		for (int i = 0; i < 3; i++)
		{
			if (neighbor[isLegal[i]].x == 0 || neighbor[isLegal[i]].x == SIZE - 1 ||
				neighbor[isLegal[i]].y == 0 || neighbor[isLegal[i]].y == SIZE - 1)
				need_erase = i;
		}
		if (need_erase == INT_MAX)
		{
			int shortest = INT_MAX;
			for (int i = 0; i < 3; i++)
			{
				int dist = abs(End - neighbor[isLegal[i]].toNum());
				if (dist < shortest)
				{
					shortest = dist;
					need_erase = i;
				}
			}
		}
		isLegal.erase(isLegal.begin() + need_erase);
	}

	// đệ quy tìm các hướng đi tiếp theo với mỗi node trái phải của node cha 
	node->left_child = new Node(neighbor[isLegal.front()].toNum(), node->depth + 1);
	node->left_child->parent = node;
	neighbor[isLegal.front()].mapValue() = false;	// gán cho node hiện tại không truy cập được 
	build(node->left_child, End, path_length);
	neighbor[isLegal.front()].mapValue() = true;// sau khi tìm xong gán lại giá trị ban đầu để tiếp tục với những nhánh khác 

	if (isLegal.size() == 2)
	{
		node->right_child = new Node(neighbor[isLegal.back()].toNum(), node->depth + 1);
		node->right_child->parent = node;
		neighbor[isLegal.back()].mapValue() = false;
		build(node->right_child, End, path_length);
		neighbor[isLegal.back()].mapValue() = true;
	}
}


// cải tiến hàm spawn food bằng cách random trên map bool

void Food::spawn()
{
	do
	{
		x = rand() % SIZE;
		y = rand() % SIZE;
	} while (!map[y][x]);

	x = (x + 2) * GRID;
	y = (y + 2) * GRID;
}