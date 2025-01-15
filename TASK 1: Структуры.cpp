#include <iostream>
#include <string>

struct Student {
    std::string name;      
    int age;              
    float averageGrade;   
    std::string faculty;   
};

struct City {
    std::string cityName;   
    std::string countryName; 
    int population;         
};

struct University {
    std::string universityName;
};

int main() {
    Student student1 = {"Иван Иванов", 20, 4.5, "Факультет информатики"};
    City city1 = {"Москва", "Россия", 11920000};
    University university1 = {"Московский государственный университет"};

    std::cout << "Студент: " << student1.name << ", Возраст: " << student1.age 
              << ", Средний балл: " << student1.averageGrade 
              << ", Факультет: " << student1.faculty << '\n';

    std::cout << "Город: " << city1.cityName << ", Страна: " << city1.countryName 
              << ", Население: " << city1.population << '\n';

    std::cout << "Университет: " << university1.universityName << '\n';

    return 0;
}
