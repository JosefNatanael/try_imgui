#pragma once

#include "imgui.h"

struct ApplicationState {
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    bool enable_power_save = true;
    bool show_demo_window = true;
    bool show_another_window = false;
};
