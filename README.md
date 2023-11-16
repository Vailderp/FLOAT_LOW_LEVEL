# FLOAT_LOW_LEVEL
Дополнительное индивидуальное задание по численным методам ТТИТ

#Example 1. Из бит в число
```cpp
int main()
{
  // Знак = 0
  // Мантисса = 01111111
  // Экспонента = 10000000000000000000000u
  __s32ll a = 0b0'01111111'10000000000000000000000u;

  // Вывод информации о числе
  std::cout << get_info(a) << std::endl;
}
// Консоль:
// 1) 1.5f = 0 01111111 10000000000000000000000
// 2) Is a positive number
// 3) Exponent = 127
```
#Example 2. Из числа в биты
```cpp
int main()
{
  // Присваиваем значение float обычным способом
  __s32ll a = -5.0f;

  // Вывод информации о числе
  std::cout << get_info(a) << std::endl;
}
// Консоль:
// 1) -5f = 1 10000001 01000000000000000000000
// 2) Is a negative number
// 3) Exponent = 129
```

#Example 3. Тернарные ооператоры
```cpp
int main()
{
  std::cout << 0b0'01111111'10000000000000000000000_s32ll << std::endl;
}
// Консоль:
// 0 01111111 10000000000000000000000

int main()
{
  std::cout << 1.5_s32ll << std::endl;
}
// Консоль:
// 0 01111111 10000000000000000000000
```

#Example 4. Математические выражения
```cpp
int main()
{
  auto a = 0b0'01111111'10000000000000000000000_s32ll;
  auto b = -5._s32ll;
  auto c = 10. + a * b / 0b0'01111111'10000000000000000000000 - 0.2_s32ll;
  std::cout << get_info(c) << std::endl;
}
// Консоль:
// 1) 4.8f = 0 10000001 00110011001100110011010
// 2) Is a positive number
// 3) Exponent = 129
```
