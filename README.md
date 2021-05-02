# Game Snake
## Thuật toán tự chơi
* Sử dụng chu trình Halmiton
* Coi bản đồ như một đồ thị lưới
* Dùng cây nhị phân để tìm tất cả các đường có thể đi từ đầu rắn đến đuôi trên đồ thị (chu trình Hamilton)
* Từ các chu trình Halmiton tìm được tìm đường đi ngắn nhất từ đầu rắn tới thức ăn
* Mỗi khi ăn tiếp tục tìm đường mới có thể
* Snake luôn thắng vì luôn luôn tồn tại một chu trình Hamilton (đường ban đầu) mỗi khi ăn thức ăn
