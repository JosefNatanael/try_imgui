#include "PowerSave.h"

#include <GLFW/glfw3.h>  // Will drag system OpenGL headers

#include <chrono>

namespace op {

void idleBySleeping() {
    using clock = std::chrono::system_clock;
    using fractional_ms = std::chrono::duration<double, std::milli>;

    static clock::time_point a = clock::now();
    static clock::time_point b = clock::now();
    fractional_ms work_time = a - b;

    if (work_time.count() < WAIT_TIMEOUT_MS) {
        auto delta = fractional_ms(WAIT_TIMEOUT_MS - work_time.count());
        glfwWaitEventsTimeout(delta.count());
    }
    b = clock::now();
}

}  // namespace op
