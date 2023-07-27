#pragma once

#include <cstdint>

// https://github.com/ocornut/imgui/wiki/Implementing-Power-Save,-aka-Idling-outside-of-ImGui

namespace op {

static constexpr int32_t FPS_IDLE = 5;
static constexpr double WAIT_TIMEOUT_MS = 200.0;

void idleBySleeping();

}  // namespace op
