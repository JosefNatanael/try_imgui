#pragma once

#ifdef __cplusplus
#if __cplusplus >= 201402L
#define CPP14_SUPPORTED
#endif
#endif

#include <future>

namespace op {

#ifdef CPP14_SUPPORTED
template <typename F, typename... Ts>
inline auto reallyAsync(F&& f, Ts&&... params) {
    return std::async(std::launch::async, std::forward<F>(f), std::forward<Ts>(params)...);
}
#else
template <typename F, typename... Ts>
inline std::future<typename std::result_of<F(Ts...)>::type> reallyAsync(F&& f, Ts&&... params) {
    return std::async(std::launch::async, std::forward<F>(f), std::forward<Ts>(params)...);
}
#endif

};  // namespace op
