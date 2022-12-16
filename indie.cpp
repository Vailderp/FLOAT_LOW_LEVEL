// indie2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

#define DEFINE_OPERATOR_S32LL(_OP, S32LLBTYPE, S32LLBPATH) \
__s32ll operator _OP (__s32ll s32lla, S32LLBTYPE s32llb) \
{ \
    return __s32ll(s32lla.float_value _OP S32LLBPATH); \
} \

// unsigned int 32 bit
using __u32 = uint32_t;

// unsigned int 16 bit
using __u16 = uint16_t;

// unsigned int 8 bit
using __u8 = uint8_t;

// mask for getting a bit at the end of a 32 bit number
constexpr __u32 u32_mask = static_cast<__u32>(0b1u);

// IEEE754 single precision floating point 32 bit low-level -> struct (size = 32 bit)
// si - sign bit - 1 bit
// ex - exponent - 8 bit
// ma - mantissa - 23 bit
struct __s32p
{
    __u32 ma : 23;
    __u32 ex : 8;
    __u32 si : 1;
};

// single precision floating point 32 bit low-level -> union (size = 32 bit)
union __s32ll 
{
    __s32p s32p;
    float float_value;
    __u32 u32_value;
    __s32ll(float src) : float_value(src) {}
    __s32ll(__u32 src) : u32_value(src) {}
    __s32ll& operator= (float src) 
    {
        float_value = src;
    }
    __s32ll& operator=(__u32 src)
    {
        u32_value = src;
    }
};

DEFINE_OPERATOR_S32LL(+, __s32ll, s32llb.float_value)
DEFINE_OPERATOR_S32LL(-, __s32ll, s32llb.float_value)
DEFINE_OPERATOR_S32LL(*, __s32ll, s32llb.float_value)
DEFINE_OPERATOR_S32LL(/, __s32ll, s32llb.float_value)

DEFINE_OPERATOR_S32LL(+, float, s32llb)
DEFINE_OPERATOR_S32LL(-, float, s32llb)
DEFINE_OPERATOR_S32LL(*, float, s32llb)
DEFINE_OPERATOR_S32LL(/, float, s32llb)


__s32ll operator-(__s32ll s32lla)
{
    return __s32ll(-s32lla.float_value);
}

inline std::string to_string(__u32 u32, __u8 end, __u8 begin = __u8(0))
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

inline void get_info(__s32ll s32ll)
{
    std::cout << "1) " << s32ll.float_value << "f = " << s32ll << '\n';
    if (s32ll.s32p.si == 1)
        std::cout << "2) Is a negative number\n";
    else
        std::cout << "2) Is a positive number\n";
    std::cout << "3) Exponent = " << s32ll.s32p.ex << '\n';
}

int main()
{
    //__s32ll a = 0b1'01111110'10111111000001111100000;
    __s32ll a = 1.5f;
    __s32ll b = -5.0f;
    __s32ll a_add_b = a + 1.5f;

    get_info(a);
    std::cout << std::endl;
    get_info(-b);
    std::cout << std::endl;
    get_info(b);
    std::cout << std::endl;
    get_info(a_add_b);
}
