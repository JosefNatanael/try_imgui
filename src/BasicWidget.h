#pragma once

#include <array>
#include <vector>

#include "ApplicationState.h"

namespace op {

struct TableColumnsViewState {
    bool lastTradedPrice = false;
    bool topVol = true;
    bool impliedVol = true;
    bool delta = true;
    bool gamma = true;
    bool vega = true;
    bool theta = false;
    bool rho = false;
    bool volume = true;
    bool position = true;
    bool usdValue = true;
};

void renderBasicWidget(ApplicationState& appState, ImGuiIO& io);

}  // namespace op
