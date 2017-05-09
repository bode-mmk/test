#include <iostream>
#include <functional>
#include <unordered_map>
#include <type_traits>

enum struct key_bind : int {
	ctrl,
	shift
};

struct has_mouse_event_impl {
	template<typename F>
	static constexpr auto check(F f)->decltype( f.mouse_event(std::declval<int>(), std::declval<int>(), std::declval<key_bind>()), std::true_type{} );

	template<typename F>
	static constexpr auto check(...)->std::false_type;
};

template<typename F>
class has_mouse_event :
	public decltype(has_mouse_event_impl::check<F>(std::declval<F>())){};

struct dispatcher {
	using function_type = std::function< void(int, int, key_bind)>;
	using hash_type = unsigned short;

	dispatcher() noexcept :
	unique_index_(0) {}

	~dispatcher() noexcept = default;

	template<typename F, class = std::enable_if_t< has_mouse_event<F>::value >>
	hash_type push(F&& f) {
		functor_[unique_index_] = [&](int x, int y, key_bind k) {return f.mouse_event(x, y, k); };
		return unique_index_++;
	}

	hash_type push(function_type&& functor) {
		functor_[ unique_index_ ] = functor;
		return unique_index_++;
	}

	void remove(const hash_type& index) {
		functor_.erase(index);
	}

	void visit(const int& x, const int& y, const key_bind& kind) noexcept {
		for (auto&& f : functor_) {
			f.second(x, y, kind);
		}
	}

private:
	//std::vector< function_type > functor_;
	std::unordered_map< hash_type, function_type > functor_;
	hash_type unique_index_;
};

static dispatcher dispatch;

void sample_event(int x, int y, key_bind k) {
	std::cout << "this is sample_event " << "x" << x << "y" << y << "key" << static_cast<int>(k) << std::endl;
}

void sample_event2(int x, int y, key_bind k) {
	std::cout << "this is sample_event2 " << "x" << x << "y" << y << "key" << static_cast<int>(k) << std::endl;
}

struct event_class{
	void mouse_event(int x, int y, key_bind k) {
		std::cout << "this is event_class::mouse_event " << "x" << x << "y" << y << "key" << static_cast<int>(k) << std::endl;
	}
};

int main(void) {
	//1.initialize
	auto hoge = dispatch.push(&sample_event);
	auto hoge2 = dispatch.push(&sample_event2);

	event_class e;

	auto hoge3 = dispatch.push(e);

	//2.visit
	dispatch.visit(10, 20, key_bind::shift);

	//3.clear
	dispatch.remove(hoge);

	//4.re-visit
	dispatch.visit(30, 40, key_bind::ctrl);

	return 0;
}
