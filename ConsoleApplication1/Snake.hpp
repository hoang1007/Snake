/*
* Sử dụng vector để tạo rắn
* Rắn di chuyển bằng cách liên tục thêm một Block vào đầu và bỏ một Block ở đuôi
*/

#pragma once

#include "Block.hpp"
#include "Queue.hpp"
#include <vector>
#include <stack>
using namespace std;

// liệt kê các bộ phận của rắn
const int TOTALS_PARTS = 5;
enum { HEAD, TAIL, CRASH, BODY, CORNER };

class Snake : public ReverseQueue<Block>
{
	Block* temp;	// lưu lại phần đuôi thừa của rắn khi di chuyển
	//kiểm tra xem Block mới thêm vào đầu của snake có hợp lệ hay không
	bool isSuitable(Block newBlock);
	//thay đổi hướng đi của rắn
	Direction changeDir();
public:
	bool isEatFood;
	bool alive;
	Direction nextDir;	// lưu lại hướng đi nhận từ bàn phím
	vector<SDL_Rect> src;	//lưu lại vị trí, kích thước của các bộ phận rắn từ file nguồn
	Snake();
	Snake(int length);
	~Snake();
	/*
	* Vẽ rắn với grassColor dùng để vẽ lại bản đồ với màu cỏ so le nhau
	*/
	void paint(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Color grassColor[]);
	void move();
	Direction autoMove(Block food);
};