# Game Snake
## Em tự đánh giá game của em nhận được 9 điểm


* Sử dụng nhiều class, tách file, kế thừa
* Code snake sử dụng class template hàng đợi được viết bằng danh sách liên kết
* Vẽ đầu, đuôi theo hướng đi của rắn, bo góc rắn khi chuyển hướng
* Sử dụng nạp chồng toán tử
* Tự thiết kế tài nguyên game
* Tự thiết kế âm thanh di chuyển từ [https://musiclab.chromeexperiments.com/]
* Tham khảo cách cài đặt iterator từ [https://www.geeksforgeeks.org/implementing-iterator-pattern-of-a-single-linked-list/
* Có thể lưu lại điểm cao nhất sau mỗi lần chơi
## Thuật toán tự chơi
* Sử dụng chu trình Halmiton
* Coi bản đồ như một đồ thị lưới
* Dùng cây nhị phân để tìm tất cả các đường đi có thể từ mỗi điểm trên đồ thị
* Từ các chu trình Halmiton tìm được tìm đường đi ngắn nhất từ đầu rắn tới thức ăn
* Mỗi khi ăn tiếp tục tìm đường mới có thể
* Snake luôn thắng vì luôn luôn tồn tại một chu trình Hamilton mỗi khi ăn thức ăn
