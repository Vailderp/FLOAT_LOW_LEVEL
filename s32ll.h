#include <iostream>
#include <sstream>
#include <type_traits>

#define S32LL_INTERNAL_OPERATOR(S32LL_OPERATOR) \
template <typename _Type>\
__s32ll& operator S32LL_OPERATOR (_Type value) \
{ \
    if constexpr (std::is_same_v<_Type, __s32ll>)\
        float_value S32LL_OPERATOR value.float_value;\
    else if constexpr (std::is_same_v<_Type, uint32_t> || std::is_same_v<_Type, int32_t> || std::is_same_v<_Type, unsigned long long int>) \
        u32_value S32LL_OPERATOR value;\
    else\
        float_value S32LL_OPERATOR value;\
    return *this;\
} \

#define S32LL_EXTERNAL_OPERATOR(S32LL_OPERATOR) \
template <typename _Type1, typename _Type2>\
__s32ll operator S32LL_OPERATOR (_Type1 value1, _Type2 value2)\
{\
    static_assert(\
        std::is_same_v<_Type1, __s32ll> || std::is_same_v<_Type2, __s32ll>,\
        "One of arguments must be __s32ll"\
        );\
    __s32ll s32ll_ret;\
    s32ll_ret = __s32ll(value1).float_value S32LL_OPERATOR __s32ll(value2).float_value;\
    return s32ll_ret;\
}

// mask for getting a bit at the end of a 32 bit number
constexpr uint32_t u32_mask = static_cast<uint32_t>(0b1u);

// IEEE754 single precision floating point 32 bit
// si - sign bit - 1 bit
// ex - exponent - 8 bit
// ma - mantissa - 23 bit
struct __s32p
{
    uint32_t ma : 23;
    uint32_t ex : 8;
    uint32_t si : 1;
};


// union-impl 32 bit 
union __s32ll
{
    __s32p s32p;
    float float_value;
    uint32_t u32_value;

    __s32ll() : float_value(0.0f) {}

    template <typename _Type>
    __s32ll(const __s32ll& value) : float_value(value.float_value) {}

    template <typename _Type>
    __s32ll(typename _Type value)
    {
        if constexpr (std::is_same_v<_Type, uint32_t> || std::is_same_v<_Type, int32_t> || std::is_same_v<_Type, unsigned long long int>)
            u32_value = static_cast<uint32_t>(value);
        else
            float_value = static_cast<float>(value);
    }

    template <typename _Type>
    operator _Type ()
    {
        if constexpr (std::is_same_v<_Type, __s32ll>)
			return *this;
        else if constexpr (std::is_same_v<_Type, uint32_t> || std::is_same_v<_Type, int32_t> || std::is_same_v<_Type, unsigned long long int>)
            return static_cast<_Type>(u32_value);
        else 
            return static_cast<_Type>(float_value);
    } 

	S32LL_INTERNAL_OPERATOR(=)
	S32LL_INTERNAL_OPERATOR(+=)
	S32LL_INTERNAL_OPERATOR(-=)
	S32LL_INTERNAL_OPERATOR(*=)
	S32LL_INTERNAL_OPERATOR(/=)
};

S32LL_EXTERNAL_OPERATOR(+)
S32LL_EXTERNAL_OPERATOR(-)
S32LL_EXTERNAL_OPERATOR(/)
S32LL_EXTERNAL_OPERATOR(*)

__s32ll operator-(__s32ll s32lla)
{
    return __s32ll(-s32lla.float_value);
}

__s32ll operator+(__s32ll s32lla)
{
    return __s32ll(+s32lla.float_value);
}

__s32ll operator"" _s32ll(long double value)
{
    return __s32ll(value);
}

__s32ll operator"" _s32ll(unsigned long long int value)
{
    return __s32ll(value);
}

inline std::string to_string(uint32_t u32, uint8_t end, uint8_t begin = uint8_t(0))
{
    std::string str;

    for (int i = end - 1; i >= begin; i--)
        str += (u32_mask & (u32 >> i)) >= 1 ? '1' : '0';
    return str;
}

inline std::string to_string(__s32p s32p)
{
    std::string str;
    str.reserve(32 + 2);
    (str += s32p.si + '0') += ' ';
    (str += to_string(s32p.ex, 8)) += ' ';
    (str += to_string(s32p.ma, 23)) += ' ';
    return str;
}

inline std::ostream& operator<<(std::ostream& os, __s32ll s32ll)
{
    return os << to_string(s32ll.s32p);
}

inline std::string get_info(__s32ll s32ll)
{
	std::stringstream ss;
    ss << "1) " << s32ll.float_value << "f = " << s32ll << '\n';
    if (s32ll.s32p.si == 1)
        ss << "2) Is a negative number\n";
    else
        ss << "2) Is a positive number\n";
    ss << "3) Exponent = " << s32ll.s32p.ex << '\n';
	return ss.str();
}
