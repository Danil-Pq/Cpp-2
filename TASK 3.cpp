#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <functional>

using namespace std;

// Операции с двумя числами
double add(double a, double b) {
    return a + b;
}

double subtract(double a, double b) {
    return a - b;
}

double multiply(double a, double b) {
    return a * b;
}

double divide(double a, double b) {
    return b != 0 ? a / b : 0; // Проверка деления на 0
}

// Функция для работы с вектором
void process_vector(vector<int>& v, function<void(int&)> func) {
    for (auto& elem : v) {
        func(elem);
    }
}

// Программа
int main() {
    // 1. Массив указателей на функции
    typedef double (*Operation)(double, double);
    Operation operations[] = {add, subtract, multiply, divide};

    double a, b;
    int choice;

    cout << "Введите два числа: ";
    cin >> a >> b;
    cout << "Выберите операцию (0-сложение, 1-вычитание, 2-умножение, 3-деление): ";
    cin >> choice;

    if (choice >= 0 && choice < 4) {
        cout << "Результат: " << operations[choice](a, b) << '\n';
    } else {
        cout << "Неверный выбор операции" << '\n';
    }

    // 2. Удвоить значения элементов массива
    vector<int> vec = {1, 2, 3, 4};
    process_vector(vec, [](int& n) { n *= 2; });
    cout << "Удвоенные значения: ";
    for (const auto& v : vec) cout << v << " "; // 2 4 6 8
    cout << '\n';

    // 3. Возвести значения элементов массива в квадрат
    process_vector(vec, [](int& n) { n *= n; });
    cout << "Значения в квадрате: ";
    for (const auto& v : vec) cout << v << " "; // 4 16 36 64
    cout << '\n';

    // 4. Увеличение каждого элемента на 5
    vector<int> nums = {1, 2, 3, 4};
    std::for_each(nums.begin(), nums.end(), [](int& n) { n += 5; });
    cout << "Увеличенные значения: ";
    for (const auto& n : nums) cout << n << " "; // 6 7 8 9
    cout << '\n';

    // 5. Вывод только четных элементов
    cout << "Четные элементы: ";
    std::for_each(nums.begin(), nums.end(), [](int n) {
        if (n % 2 == 0) cout << n << " "; // 6
    });
    cout << '\n';

    // 6. Сортировка вектора строк по длине и в лексикографическом порядке в обратном направлении
    vector<string> strings = {"apple", "banana", "kiwi", "cherry", "berry"};
    
    // Сортировка по длине строк
    std::sort(strings.begin(), strings.end(), [](const string& a, const string& b) {
        return a.length() < b.length();
    });
    cout << "Сортировка по длине: ";
    for (const auto& s : strings) cout << s << " "; // apple berry kiwi banana cherry
    cout << '\n';

    // Сортировка по лексикографическому порядку в обратном направлении
    std::sort(strings.begin(), strings.end(), [](const string& a, const string& b) {
        return a > b;
    });
    cout << "Сортировка в обратном порядке: ";
    for (const auto& s : strings) cout << s << " "; // cherry banana kiwi berry apple
    cout << '\n';

    // 7. Пример использования std::function
    std::function<double(double, double)> func = [](double x, double y) {
        return x + y; // простая функция сложения
    };
    cout << "Использование std::function: 5 + 3 = " << func(5, 3) << '\n'; // 8

    return 0;
}
