#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <iostream>
#include <vector>
#include <string>

#define API "https://www.dnd5eapi.co/api/rules"

class Rule {
public:
    std::string name;
    std::string url;

    Rule(const std::string& name, const std::string& url) : name(name), url(url) {}

    void displayDetails() {
        std::string full_url = "https://www.dnd5eapi.co" + url;
        cpr::Response response = cpr::Get(cpr::Url(full_url));
        if (response.status_code != 200) {
            std::cerr << "Ошибка: Невозможно получить детали правила. Код состояния: " << response.status_code << "\n";
            return;
        }
        nlohmann::json rule_json = nlohmann::json::parse(response.text);
        std::cout << "\n=== " << rule_json["name"] << " ===\n\n";
        std::cout << "Описание:\n" << rule_json["desc"] << "\n";

        if (rule_json.contains("subsections") && !rule_json["subsections"].empty()) {
            std::vector<std::string> subsection_urls;
            std::cout << "\nПодразделы:\n";
            for (size_t i = 0; i < rule_json["subsections"].size(); ++i) {
                const auto& subsection = rule_json["subsections"][i];
                std::cout << i + 1 << ". " << subsection["name"] << "\n";
                subsection_urls.push_back("https://www.dnd5eapi.co" + subsection["url"].get<std::string>());
            }
            std::cout << "0. Вернуться назад\n";

            int subsection_choice;
            std::cout << "\nВведите номер подраздела для просмотра или 0 для возврата: ";
            std::cin >> subsection_choice;

            if (subsection_choice == 0) {
                return;
            }

            if (subsection_choice < 1 || subsection_choice > subsection_urls.size()) {
                std::cerr << "Неверный выбор подраздела. Попробуйте снова.\n";
                return;
            }

            std::string subsection_url = subsection_urls[subsection_choice - 1];
            cpr::Response subsection_response = cpr::Get(cpr::Url(subsection_url));
            if (subsection_response.status_code != 200) {
                std::cerr << "Ошибка: Невозможно получить детали подраздела. Код состояния: " << subsection_response.status_code << "\n";
                return;
            }

            nlohmann::json subsection_json = nlohmann::json::parse(subsection_response.text);
            std::cout << "\n=== " << subsection_json["name"] << " ===\n\n";
            std::cout << "Описание:\n" << subsection_json["desc"].get<std::string>() << "\n";
        } else {
            std::cout << "У этого правила нет подразделов.\n";
        }
    }
};

class RuleManager {
private:
    std::vector<Rule> rules;

public:
    RuleManager() {
        loadRules();
    }

    void loadRules() {
        cpr::Response response = cpr::Get(cpr::Url(API));
        if (response.status_code != 200) {
            std::cerr << "Ошибка: Невозможно получить данные из API. Код состояния: " << response.status_code << "\n";
            return;
        }

        nlohmann::json response_json = nlohmann::json::parse(response.text);
        for (const auto& item : response_json["results"]) {
            rules.emplace_back(item["name"], item["url"]);
        }
    }

    const std::vector<Rule>& getRules() const {
        return rules;
    }

    void displayRuleDetails(int index) {
        if (index >= 0 && index < rules.size()) {
            rules[index].displayDetails();
        } else {
            std::cerr << "Неверный индекс правила.\n";
        }
    }
};

class CLI {
private:
    RuleManager& ruleManager;

public:
    CLI(RuleManager& manager) : ruleManager(manager) {}

    void displayMenu() {
        std::cout << "\n=== Доступные правила ===\n";
        const std::vector<Rule>& rules = ruleManager.getRules();
        for (size_t i = 0; i < rules.size(); ++i) {
            std::cout << i + 1 << ". " << rules[i].name << "\n";
        }
        std::cout << "0. Выйти\n";
    }

    void run() {
        bool exit_program = false;
        while (!exit_program) {
            displayMenu();
            int choice;
            std::cout << "\nВведите номер правила для просмотра или 0 для выхода: ";
            std::cin >> choice;

            if (choice == 0) {
                exit_program = true;
                continue;
            }

            if (choice < 1 || choice > ruleManager.getRules().size()) {
                std::cerr << "Неверный выбор. Попробуйте снова.\n";
                continue;
            }

            ruleManager.displayRuleDetails(choice - 1);
        }
    }
};

int main() {
    RuleManager manager;
    CLI cli(manager);
    cli.run();
    return 0;
}
