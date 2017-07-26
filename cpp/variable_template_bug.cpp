#include <iostream>
#include <type_traits>

template<typename T, std::enable_if_t< std::is_same_v<T, int>, std::nullptr_t> = nullptr> // std::is_same_vをやめstd::is_same<T, int>::valueにするとIntelliSenseはバグらない
constexpr inline T value(const T& v) {
	return v;
}

int main()
{
	static_assert(value(20) == 20, "");

	return 0;
}

