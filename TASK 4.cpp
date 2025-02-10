#include <iostream>
#include <vector>
#include <algorithm>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

int main() {
    setlocale(LC_ALL, "ru");
    while (true) {
        // All rules
        cpr::Response response1 = cpr::Get(cpr::Url{ "https://www.dnd5eapi.co/api/rules" });
        if (response1.status_code != 200) {
            std::cout << response1.error.message << '\n';
            return -1;
        }
        nlohmann::json response_json1 = nlohmann::json::parse(response1.text);

        std::cout << "Rules";
        std::cout << "\n------------------\n";
        int count1 = 1;
        for (auto& i : response_json1["results"]) {
            std::cout << count1++ << ") " << i["name"] << '\n';
        }

        // The Rule
        std::string input2;
        std::cout << "\nВведите название правила: ";
        std::cin >> input2;

        cpr::Response response2 = cpr::Get(cpr::Url{ "https://www.dnd5eapi.co/api/rules/" + input2 });
        if (response2.status_code != 200) {
            std::cout << response2.error.message << '\n';
            return -1;
        }
        nlohmann::json response_json2 = nlohmann::json::parse(response2.text);

        std::cout << "\n" << input2;
        std::cout << "\n------------------\n";
        int count2 = 1;
        for (auto& i : response_json2["subsections"]) {
            std::cout << count2++ << ") " << i["name"] << '\n';
        }

        // Subsections
        std::string input3;
        std::cout << "\nВведите название подраздела через '-' между словами: ";
        std::cin >> input3;

        cpr::Response response3 = cpr::Get(cpr::Url{ "https://www.dnd5eapi.co/api/rule-sections/" + input3 });
        if (response3.status_code != 200) {
            std::cout << response3.error.message << '\n';
            return -1;
        }
        nlohmann::json response_json3 = nlohmann::json::parse(response3.text);

        std::cout << "\n" << input3;
        std::cout << "\n------------------\n";
        std::cout << response_json3["desc"].get<std::string>() << "\n\n";
    }
}
