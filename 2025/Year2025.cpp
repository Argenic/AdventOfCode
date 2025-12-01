#include "2025/Year2025.h"
#include "2025/Days2025.h"

namespace Year2025 {

Year2025::Year2025() {
    initializeDays();
}

int Year2025::getYearNumber() const {
    return 2025;
}

std::shared_ptr<Day> Year2025::getDay(int dayNumber) {
    auto it = days_.find(dayNumber);
    if (it != days_.end()) {
        return it->second;
    }
    return nullptr;
}

std::vector<int> Year2025::getAvailableDays() const {
    std::vector<int> available;
    for (const auto& pair : days_) {
        available.push_back(pair.first);
    }
    return available;
}

bool Year2025::hasDay(int dayNumber) const {
    return days_.find(dayNumber) != days_.end();
}

void Year2025::initializeDays() {
    days_[1] = std::make_shared<Day1>();
    days_[2] = std::make_shared<Day2>();
    days_[3] = std::make_shared<Day3>();
    days_[4] = std::make_shared<Day4>();
    days_[5] = std::make_shared<Day5>();
    days_[6] = std::make_shared<Day6>();
    days_[7] = std::make_shared<Day7>();
    days_[8] = std::make_shared<Day8>();
    days_[9] = std::make_shared<Day9>();
    days_[10] = std::make_shared<Day10>();
    days_[11] = std::make_shared<Day11>();
    days_[12] = std::make_shared<Day12>();
}

} // namespace Year2025

