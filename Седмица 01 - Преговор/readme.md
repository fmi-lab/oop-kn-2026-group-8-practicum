# Седмица 01 - Преговор

## Задача 01 - Най-голям общ делител
```c++
unsigned gcd(unsigned a, unsigned b);
```

Напишете рекурсивна функция, която намира най-големия общ делител на две цели неотрицателни числа.

### Пример:
```c++
std::cout << gcd(24, 60) << '\n'; // -> 12
std::cout << gcd(13, 17) << '\n'; // -> 1
```

## Задача 02 - Търсене на подниз
```c++
char* find_word(char* str, const char* substr);
```
Напишете функция, която връща указател към първата буква на конкретен подниз в даден низ. Ако този подниз не е част от низа, функцията да връща `nullptr`.

### Пример:
```c++
char str[] = "I am the best programmer ever";
std::cout << find_word(str, "programmer") << '\n'; // -> programmer ever
```

## Задача 03 - Премахване на подниз
```c++
void remove_word(char* str, const char* word);
```
Напишете функция, която премахва всички срещания на подниз от низ.

### Пример:
```c++
char str[] = "I am the best programmer ever";
remove_word(str, "mer");
std::cout << str << '\n'; // -> I am the best program ever
```

## Задача 04 - Четни числа
```c++
std::size_t extract_evens(const char* source, int destination[]);
```
Напишете функция, която обхожда символен низ, намира всички четни положителни числа в него и ги записва в масив от цели числа. Функцията да връща броя записани елементи. Приемете, че в низа не се срещат отрицателни числа.

### Пример:
```c++
int arr[255]{};
std::size_t size = extract_evens("458sade21asd4asd42a7sd8", arr);
print(arr, arr + size); // -> 458 4 42 8
```

### Бонус:
Променете функцията, така че да работи и за отрицателни числа.

## Задача 05 - Еднакви масиви
```c++
bool equal(const int* first_begin, const int* first_end, const int* second_begin, const int* second_end);
```
Напишете функция, която проверява дали елементите на два масиви съвпадат.

### Пример:
```c++
const int arr[]{1, 2, 1, 3};
const int arr2[]{1, 2};

std::cout << std::boolalpha << equal(std::cbegin(arr), std::cbegin(arr) + 2, std::cbegin(arr2), std::cend(arr2)) << '\n'; // -> true
std::cout << std::boolalpha << equal(std::cbegin(arr), std::cend(arr), std::cbegin(arr2), std::cend(arr2)) << '\n'; // -> false
```

## Задача 06 - Разделяне
```c++
const int* partition(int* begin, int* end, int element);
```
Напишете функция, която по подаден масив и естествено число пренарежда масива, така че в началото му да са всички елементи, по-малки от подаденото число, а в края - всички по-големи или равни. Функцията да връща указател към началото на втората група. Редът на елементите в двете групи няма значение.

### Пример:
```c++
int arr[]{4, 7, 1, 3, 2, 6, 5, 9, 0};
const int *mid = partition(std::begin(arr), std::end(arr), 5);

print(std::begin(arr), mid); // -> 4 0 1 3 2
print(mid, std::cend(arr)); // -> 5 9 6 7
```

## Задача 07 - Кръстословица
```c++
unsigned find_words_in_crossword(char matrix[][255], std::size_t rows, std::size_t cols, char words[][255], std::size_t n);
```
Напишете функция, която приема кръстословица, представена като матрица от букви, както и списък от думи, и намира броя на думите от списъка, които се срещат в кръстословицата. Една дума се съдържа в кръстословицата, ако всяка буква от думата се намира в съседна клетка на предишната буква. Ако буква в дадена клетка е използвана, тя не може да се ползва втори път.

### Пример:
```c++
char matrix[][255] = {{'c', 'a', 't'},
                      {'w', 'h', 'o'},
                      {'w', 'i', 'n'}};
char words[][255] = {"cat", "hello", "what", "caca"};
std::cout << find_words_in_crossword(matrix, 3, 3, words, 4) << '\n'; // -> 2
// -> cat, what
```