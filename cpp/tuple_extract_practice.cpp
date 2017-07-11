#include <iostream>
#include <initializer_list>
#include <tuple>
#include <type_traits>
#include <utility>

template<typename Tuple, std::size_t... Indices>
constexpr bool is_even_number_impl(Tuple&& tup, std::index_sequence<Indices...>) {
	bool result = true;
	using swallow = std::initializer_list<int>;
	(void)swallow { ( void(result &= (std::get<Indices>(tup) % 2 == 0)), 0)... };
	return result;
}

template<typename Tuple>
constexpr bool is_even_number(Tuple&& tup) {
	return is_even_number_impl(
		std::forward<Tuple>(tup),
		std::make_index_sequence<std::tuple_size<std::decay_t<Tuple>>::value> {}
	);
}

int main() {
	constexpr std::tuple<int, int, int> v = { 1, 2, 3 };
	constexpr std::tuple<int, int, int, int, int> w = { 2, 4, 6, 8, 10 };

	constexpr bool is_even1 = is_even_number(v);
	static_assert(!is_even1, "");

	constexpr bool is_even2 = is_even_number(w);
	static_assert(is_even2, "");
}
