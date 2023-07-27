#pragma once

#include <array>
#include <mutex>
#include <vector>

#include "imgui.h"

namespace op {

// One row is one strike price for a call or a put
struct TableRowData {
    float lastTradedPrice = 0.0f;
    float bidSize = 0.0f;
    float bidVol = 0.0f;
    float bidPrice = 0.0f;
    float askSize = 0.0f;
    float askVol = 0.0f;
    float askPrice = 0.0f;
    float openInterest = 0.0f;
    float delta = 0.0f;
    float gamma = 0.0f;
    float vega = 0.0f;
    float theta = 0.0f;
    float rho = 0.0f;
    float volume = 0.0f;
    float position = 0.0f;
};

struct TableStateByExpiry {
    std::vector<float> strikes;
    std::vector<TableRowData> callRowData;
    std::vector<TableRowData> putRowData;
};

struct WrappedTableStateByExpiry {
    TableStateByExpiry tsbe;
    std::mutex mutex;
    bool processed = true;
};

static constexpr std::array<const char*, 15> TABLE_COLUMN_NAMES = {"Last",   "BidSize", "BidVol", "Bid",    "Ask",
                                                                   "AskVol", "AskSize", "Open",   "Delta",  "Gamma",
                                                                   "Vega",   "Theta",   "Rho",    "Volume", "Position"};

struct ApplicationState {
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    bool enable_power_save = true;
    bool show_demo_window = true;
    bool show_another_window = false;

    WrappedTableStateByExpiry wrappedTableData;
};

};  // namespace op
