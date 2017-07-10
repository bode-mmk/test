#include <iostream>
#include <utility>
#include <tuple>

template<typename T>
constexpr bool is_even_number_impl_impl(const T& v) {
	return (v % 2 == 0);
}

template<typename T, typename... Ts>
constexpr bool is_even_number_impl_impl(const T& v, const Ts&... vs) {
	return is_even_number_impl_impl(v)
		&& is_even_number_impl_impl(vs...);
}

template<typename T, typename Tuple, std::size_t... I>
constexpr bool is_even_number_impl(const Tuple& t, std::index_sequence<I...>) {
	return is_even_number_impl_impl(std::get<I>(t)...);
}

template<typename Tuple,typename I = std::make_index_sequence< std::tuple_size<Tuple>::value >>
constexpr auto is_even_number(const Tuple& t) {
	return is_even_number_impl(t, I());
}

int main() {
	constexpr std::tuple<int, int, int, int, int> v = { 1,2,3,4,5 };
	constexpr std::tuple<int, int, int, int, int, int, int> w = { 2,4,6,8,10,12,14 };
	constexpr auto is_even = is_even_number(v);
	//constexpr auto is_even2 = is_even_number(w);

}