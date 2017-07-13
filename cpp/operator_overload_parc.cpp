#include <iostream>
#include <utility>
#include <cassert>

namespace k {

	template<typename T, typename... Ts>
	struct match_value_holder
		: match_value_holder<Ts...>
	{
	public:
		constexpr
			match_value_holder(T v, Ts... ts) :
			match_value_holder<Ts...>(ts...),
			value_(v) {}

		constexpr inline bool
			match(const T& v) const {
			return (value_ == v) || (match_value_holder<Ts...>::match(v));
		}

	private:
		T value_;
	};

	template<typename T>
	struct match_value_holder<T> {
		constexpr
			match_value_holder(T v) :
			value_(v) {}

		constexpr inline bool
			match(const T& v) const {
			return (v == value_);
		}

	private:
		T value_;
	};

	template<typename... Ts>
	constexpr inline
		match_value_holder<Ts...> match_any(Ts&&... ts) {
		return match_value_holder<Ts...>(ts...);
	}

	template<typename T, typename... Ts>
	constexpr inline bool operator |(T&& t, match_value_holder<Ts...>&& ts) {
		return ts.match(t);
	}
}

int main() {
	constexpr bool b = 4 | k::match_any(4, 5, 6 ,7);
	constexpr bool c = 12 | k:: match_any(10, 11, 13, 4);

	constexpr int hogehoge = 233;
	constexpr bool hogesame = hogehoge | k::match_any(1, 2, 3, 233, 5);
}