*singlepso.h:
Pso_single: một lớp gói một particle đơn.
data member của lớp, bao gồm các particles:
không gian tọa độ: in_dim, coordinate, adaptation value, upper and lower limits of position,
upper and lower limits of speed và inertia coefficient
thông số tốc độ global, thông số tốc độ local, upper and lower speed limits, thông số vùng tốc độ, giai pháp tối ưu cục bao
giai pháp tối ưu toàn cục,
- Methods: sự khởi tạo ngẫu nhiên, giá trị fitness tính toán, cập nhật tối ưu toàn cụ, cập nhật tối ưu cục bộ
&&class pso single:
private:
+ không gian tọa độ: in_dims: int
+ chặn trên, chặn dưới của vị tris: *in_max, *int_min: float
+ chặn trên, chặn dưới của tốc độl: *v_max, *v_min: float
+ hệ số gia tốc, thông số tốc độ cục bộ, toàn cục: w, c1, c2: float
public:
+ tốc độ: *v: float
+ fitness: fitness_: ____
+ tọa độ của particals: *in_: ___
+ giá trị tối ưu cục bộ fitness_pbest:
+ tọa độ giá trị tối ưu cục bộ: *in_pbest
+ giá trị tối ựu toan cục: fitness_gbest:
+ tọa độ vị trí tối ưu toàn cục: *in_gbest:
- init: khởi tạo
- get_fitness: lấy giá trị tối ưu
- init_pbest: cài giá trị khởi tạo tối ưu cụ bộ
- updata_pbest: cập nhật giá trị tối ưu cục bộ
- get_gbest: câp nhật giá trị tối ưu cục bộ
- updata_v: cập nhật tốc độ
- updata_in: cập nhật tọa đọ