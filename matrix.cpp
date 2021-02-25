#include <type_traits>
#include <array>
#include <iostream>
template <size_t row_count, size_t column_count, typename T>
class matrix {
	using matrix_t = matrix<row_count, column_count, T>;
	using row_t = std::array<T, column_count>;
	std::array<row_t, row_count> arr;

public:

	matrix() : arr{} {

	}


	using iterator = decltype(arr.begin());

	using const_iterator = decltype(arr.cbegin());

	iterator begin() {
		return arr.begin();
	}

	iterator end() {
		return arr.end();
	}

	const_iterator begin() const {
		return arr.cbegin();
	}

	const_iterator end() const {
		return arr.cend();
	}

	static constexpr size_t rows = row_count;

	static constexpr size_t cols = column_count;

	matrix(matrix_t& other) {
		for (size_t i{}; i < row_count; i++) {
			arr[i] = other.arr[i];
		}
	}

	matrix(matrix_t&& other) noexcept {
		for (size_t i{}; i < row_count; i++) {
			arr[i] = std::move(other.arr[i]);
		}
	}
	template <typename... Ts>
	requires std::conjunction_v<std::is_same<row_t, Ts>...> and (sizeof...(Ts) == row_count)
		matrix(Ts... row_values) : arr{ row_values... } {
	}


	//вектор 1xN
	template <typename... Ts>
	requires std::conjunction_v<std::is_convertible<T, Ts>...> and (row_count == 1) and (sizeof...(Ts) == column_count)
		matrix(Ts... row_values) : arr{ std::array<T, column_count>{row_values ...} } {
	}


	//вектор Nx1
	template <typename... Ts>
	requires std::conjunction_v<std::is_convertible<T, Ts>...> and (column_count == 1) and (sizeof...(Ts) == row_count)
		matrix(Ts... row_values) : arr{ std::array<T, 1>{row_values} ... } {
	}


	row_t& operator[](size_t index) {
		return arr[index];
	}

	const row_t& operator[](size_t index) const {
		return arr[index];
	}


	template <size_t row_count1, size_t column_count1, typename T1> 
	requires (column_count == row_count1)
	auto operator * (matrix<row_count1, column_count1, T1> matrix1) {
		matrix<row_count, column_count1, std::common_type_t<T, T1>> ret;
		for (size_t i{}; i < row_count; i++) {
			for (size_t j{}; j < column_count1; j++) {
				for (size_t k{}; k < column_count; k++) {
					ret[i][j] += operator[](i)[k] * matrix1[k][j];
				}
					
			}
		}
		return ret;

	}

	matrix_t operator-() {
		matrix_t ret;
		for (size_t i{}; i < row_count; i++) {
			for (size_t j{}; j < column_count; j++) {
				ret[i][j] = -operator[](i)[j];
			}
		}
		return ret;
	}


	matrix_t operator-(matrix_t matrix1) {
		matrix_t ret;
		for (size_t i{}; i < row_count; i++) {
			for (size_t j{}; j < column_count; j++) {
				ret[i][j] = operator[](i)[j] - matrix1[i][j];
			}
		}
		return ret;
	}

	matrix_t operator+(matrix_t matrix1) {
		matrix_t ret;
		for (size_t i{}; i < row_count; i++) {
			for (size_t j{}; j < column_count; j++) {
				ret[i][j] = operator[](i)[j] + matrix1[i][j];
			}
		}
		return ret;
	}

	auto transpose() {
		matrix<column_count, row_count, T> ret;
		for (size_t i{}; i < row_count; i++) {
			for (size_t j{}; j < column_count; j++) {
				ret[j][i] = operator[](i)[j];
			}
		}
		return ret;

	}

	friend std::ostream& operator<<(std::ostream& os, const matrix_t& matrix) {
		for (const row_t& row : matrix) {
		 
			os << "{";
			for (size_t j{}; j < row.max_size(); j++) {
				os << row[j];
				if (j != row.max_size() - 1) {
					os << ", ";
				}

			}
			os << "}" << std::endl;
			
			
		}
		return os;
	}



};




int main() {

	
	matrix<2, 3, int> A = { std::array{1, 2, 1}, std::array{0, 1, 2} };
	matrix<3, 2, int> B = { std::array{1, 0}, std::array{0, 1}, std::array{1, 1} };

	std::cout << A * B << std::endl;
	std::cout << B * A << std::endl;

	std::cout << A.transpose().transpose().transpose() << std::endl;
 
	matrix<1, 3, int> V = { 1, 2, 3 };
	matrix<3, 1, int> V1 = { 1, 2, 3 };

	std::cout << V << std::endl;
	std::cout << V1 << std::endl;


	for (auto& row : A) {
		for (auto& el : row) {
			std::cout << el << ' ';
		}
	}

}