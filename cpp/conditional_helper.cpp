#include <iostream>

namespace conditional_helpers {
	template<typename T, T... N>
	struct t{};

	template<typename T, T N>
	struct t<T, N> {
		static constexpr T v = N;
	};

	template<typename T,T N>
	inline constexpr bool operator|(const T& lhs, const t<T,N>& rhs) {
		return (lhs == rhs.v);
	}

	template<typename T,T N,T... Ns>
	inline constexpr auto operator|(const T& lhs, const t<T,N,Ns...>& rhs){
		if (lhs == t<T,N>().v) {
			return true;
		}

		return lhs | t<T, Ns...>();
	}

	template<int ... Ns>
	constexpr auto is_same_of = t<int, Ns...>();
}

int main(void){
	using namespace conditional_helpers;

	static_assert((20 | is_same_of<20, 30, 40>) == true);
	static_assert((20 | is_same_of<30, 40, 70>) == false);

	// intだけじゃなくて全てのタイプに対応するためには……

	return 0;
}
