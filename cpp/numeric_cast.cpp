#include <iostream>
#include <optional>

using char_ = const char*;
using wchar_ = const wchar_t*;

template<typename>
struct numeric_cast_format_string {};

template<>
struct numeric_cast_format_string<int> {
	static char_ format_str() { return "%d"; }
	static wchar_ format_wstr() { return L"%d"; }
};

template<>
struct numeric_cast_format_string<short> {
	static char_ format_str() { return "%hd"; }
	static wchar_ format_wstr() { return L"%hd"; }
};

template<>
struct numeric_cast_format_string<unsigned int> {
	static char_ format_str() { return "%u"; }
	static wchar_ format_wstr() { return L"%u"; }
};

template<>
struct numeric_cast_format_string<unsigned short> {
	static char_ format_str() { return "%hu"; }
	static wchar_ format_wstr() { return L"%hu"; }
};

template<>
struct numeric_cast_format_string<long> {
	static char_ format_str() { return "%ld"; }
	static wchar_ format_wstr() { return L"%ld"; }
};

template<>
struct numeric_cast_format_string<unsigned long> {
	static char_ format_str() { return "%lu"; }
	static wchar_ format_wstr() { return L"%lu"; }
};

template<>
struct numeric_cast_format_string<float> {
	static char_ format_str() { return "%f"; }
	static wchar_ format_wstr() { return L"%f"; }
};

template<>
struct numeric_cast_format_string<double> {
	static char_ format_str() { return "%lf"; }
	static wchar_ format_wstr() { return L"%lf"; }
};

template<typename T>
class is_char_type :
	public std::false_type {};

template<>
class is_char_type<char*> :
	public std::true_type {};

template<>
class is_char_type<const char*> :
	public std::true_type {};

template<typename T>
class is_wchar_type :
	public std::false_type {};

template<>
class is_wchar_type<wchar_t*> :
	public std::true_type {};

template<>
class is_wchar_type<const wchar_t*> :
	public std::true_type {};

#ifdef _MSC_VER
#define SSCANF ::sscanf_s
#define WSCANF ::swscanf_s
#else
#define SSCANF ::sscanf
#define WSCANF ::swscanf
#endif

template<typename Target, typename Source>
inline
std::enable_if_t<is_char_type<Source>::value, std::optional<Target>>
numeric_cast(Source src) {
	Target x;
	if (SSCANF(src, numeric_cast_format_string<Target>::format_str(), &x) != 1) {
		return std::nullopt;
	}

	return std::make_optional(x);
}

template<typename Target, typename Source>
inline
std::enable_if_t<is_wchar_type<Source>::value, std::optional<Target>>
numeric_cast(Source src) {
	Target x;
	if (WSCANF(src, numeric_cast_format_string<Target>::format_wstr(), &x) != 1) {
		return std::nullopt;
	}

  return std::make_optional(x);
}

#undef SSCANF

int main(void){
    auto s1 = numeric_cast<int>("123");
    auto s2 = numeric_cast<int>(L"1223");
    std::cout << *s1 << std::endl;
    std::cout << *s2 << std::endl;

    return 0;
}
