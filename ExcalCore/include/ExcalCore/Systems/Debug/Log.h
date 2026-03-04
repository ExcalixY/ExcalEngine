//
// Created by arch-excalixy on 3/2/26.
//

#pragma once

#include <format>
#include <iostream>
#include <string>

namespace Debug {
    namespace _internal {
        inline void _log_impl(std::string_view prefix, std::string_view fmt, std::format_args args) {
            std::cerr << prefix << std::vformat(fmt, args) << std::endl;
        }
    }

    template<typename... Args>
    void LogInfo(std::format_string<Args...> fmt, Args&&... args) {
        _internal::_log_impl("[INFO]    | ", fmt.get(), std::make_format_args(args...));
    }

    template<typename... Args>
    void LogWarning(std::format_string<Args...> fmt, Args&&... args) {
        _internal::_log_impl("[WARNING] | ", fmt.get(), std::make_format_args(args...));
    }

    template<typename... Args>
    void LogError(std::format_string<Args...> fmt, Args&&... args) {
        _internal::_log_impl("[ERROR]   | ", fmt.get(), std::make_format_args(args...));
    }

    template<typename... Args>
    void Log(std::format_string<Args...> fmt, Args&&... args) {
        _internal::_log_impl("[DEBUG]   | ", fmt.get(), std::make_format_args(args...));
    }
}