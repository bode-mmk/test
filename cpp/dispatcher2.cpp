#include <iostream>
#include <functional>
#include <unordered_map>
#include <tuple>
#include <type_traits>

enum struct key_bind : int {
	ctrl,
	shift
};

struct has_mouse_event_impl {
	template<typename F, typename... Params>
    static constexpr auto check(F f)->decltype( f.mouse_event( std::declval<Params>()... ), std::true_type{} );

	//static constexpr auto check(F f)->decltype( f.mouse_event(std::declval<int>(), std::declval<int>(), std::declval<key_bind>()), std::true_type{} );

	template<typename F, typename...>
	static constexpr auto check(...)->std::false_type;
};

template<typename F, typename... Params>
class has_mouse_event :
	public decltype(has_mouse_event_impl::check<F, Params...>(std::declval<F>())){};

template<typename T>
struct explicit_type{
    template<typename U>
    explicit_type(U&&) = delete;

    explicit_type(T&& v) noexcept :
    v_(v){}

    ~explicit_type() noexcept = default;

    operator T(){
        return v_;
    }
private:
    T v_;
};

struct event_class{
	void mouse_event(explicit_type<int> x, explicit_type<int> y, explicit_type<key_bind> /* k */) {
		std::cout << "this is event_class::mouse_event " << "x" << x << "y" << y << "key" /* << static_cast<int>(k)*/ << std::endl;
	}
};

int main(void) {
    static_assert( has_mouse_event<event_class, int, int, key_bind>::value == true );
    static_assert( has_mouse_event<event_class, int, key_bind>::value == false);
    static_assert( has_mouse_event<event_class, int ,double, key_bind>::value == false); // OK

	return 0;
}
