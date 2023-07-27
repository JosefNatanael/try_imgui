#include "FakeData.h"

#include <chrono>
#include <random>
#include <thread>

#include "BasicWidget.h"

namespace op::fake {

static TableRowData generateRandomTableRowData() {
    std::random_device rd;
    std::mt19937 gen(rd());

    float lower = 0.0f;
    float upper = 100.0f;
    std::uniform_real_distribution<float> dis(lower, upper);

    TableRowData trd = {
        dis(gen), dis(gen), dis(gen), dis(gen), dis(gen), dis(gen), dis(gen), dis(gen),
        dis(gen), dis(gen), dis(gen), dis(gen), dis(gen), dis(gen), dis(gen),
    };
    return trd;
}

TableStateByExpiry getFakeDataForTable() noexcept {
    using fractional_ms = std::chrono::duration<float, std::milli>;

    float lower = 40.0f;
    float upper = 60.0f;
    // Create a random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(lower, upper);

    // Generate a random number between a and b
    float randomNum = dis(gen);
    std::this_thread::sleep_for(fractional_ms(randomNum));

    TableStateByExpiry tableData;
    tableData.strikes = {26000.0f, 27000.0f, 28000.0f, 29000.0f, 30000.0f, 31000.0f, 32000.0f, 33000.0f};
    tableData.callRowData = {};
    tableData.putRowData = {};

    auto lenStrikes = tableData.strikes.size();

    tableData.callRowData.reserve(lenStrikes);
    for (std::size_t i = 0; i < lenStrikes; ++i) {
        tableData.callRowData.push_back(generateRandomTableRowData());
    }
    tableData.putRowData.reserve(lenStrikes);
    for (std::size_t i = 0; i < lenStrikes; ++i) {
        tableData.putRowData.push_back(generateRandomTableRowData());
    }
    return tableData;
}

}  // namespace op::fake
