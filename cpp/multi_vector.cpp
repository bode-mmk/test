#include <iostream>
#include <vector>
#include <type_traits>

//第三引数は0次元以下のvectorの生成を抑制している
template<int N, typename T, class = std::enable_if_t<(N > 0)>>
struct multi_vector {
	using type = typename multi_vector<N - 1, std::vector<T>>::type;
};

template<typename T>
struct multi_vector<1, T> {
	using type = std::vector<T>;
};

template<int N, typename T>
using multi_vector_t = typename multi_vector<N, T>::type;

int main(void) {
	multi_vector_t<2, int> v
		= { {1,2,3}, {10,9,8} };

	for (const auto& e : v) {
		for (const auto& a : e) {
			std::cout << a;
		}
		std::cout << std::endl;
	}

	//抑制効果により、これはコンパイルエラーになる
	//multi_vector_t<0, int> w;
	//multi_vector_t<-2, int> w;
}
