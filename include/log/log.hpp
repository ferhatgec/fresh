// MIT License
//
// Copyright (c) 2024 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
#pragma once

#include <colorized.hh>
#include <chrono>
#include <source_location>
#include <format>

// TODO: in the future, we may add write logs to log file synchronously as a feature.
namespace fresh {
using namespace std::literals;

enum class LogType {
  Info,
  Warning,
  Error,
  Stdout
};

static constexpr std::uint8_t MaxFunctionSize = 10; // to improve readability

static constexpr auto info_color = colorized::Foreground::FgBrBlack;
static constexpr auto warning_color = colorized::Foreground::FgYellow;
static constexpr auto error_color = colorized::Foreground::FgBrRed;

template<typename... Args>
static void print(std::string_view fmt_str, Args&&... args) noexcept {
  std::cout << std::vformat(fmt_str, std::make_format_args(args...));
}

template<typename... Args>
static void println(std::string_view fmt_str, Args&&... args) noexcept {
  std::cout << std::vformat(fmt_str, std::make_format_args(args...)) << '\n';
}

template<typename... Args>
static constexpr void log(const std::source_location& location, LogType log_type, std::string_view ctx, Args&&... format_args) noexcept {
  using namespace colorized;
  print_formats_recursive(
    Pack{Style::Standard,
      Foreground::FgWhite, Background::BgDefault,
      std::cout,
      "{:%T} [file: {}({}:{}) from {}]: ",
      std::chrono::floor<std::chrono::seconds>(std::chrono::system_clock::now()), // hh:mm:ss
      location.file_name(),
      location.line(),
      location.column(),
      std::strlen(location.function_name()) /* what about unicode huh? */ > MaxFunctionSize ? "@" : location.function_name()}
  );
  switch(log_type) {
  case LogType::Info: {
    print_formats_recursive(
      Pack{Style::Standard, Foreground::FgWhite, Background::BgDefault, std::cout, ctx, std::move(format_args)...}, // f*ck perfect forwarding, all my homies use std::move! /s
      Pack{Style::Standard, info_color, Background::BgDefault, std::cout, "info: "}
      );
    print_cout_reset();
    break;
  }
  case LogType::Warning: {
    print_formats_recursive(
    Pack{Style::Standard, Foreground::FgWhite, Background::BgDefault, std::cout, ctx, std::move(format_args)...},
    Pack{Style::Standard, warning_color, Background::BgDefault, std::cout, "warning: "}
      );
    print_cout_reset();
    break;
  }
  case LogType::Error: {
    print_formats_recursive(
    Pack{Style::Standard, Foreground::FgBrWhite, Background::BgDefault, std::cerr, ctx, std::move(format_args)...},
    Pack{Style::Bold, error_color, Background::BgDefault, std::cout, "error: "}
      );
    print_cout_reset();
    std::exit(1);
    // Engine::get_instance()->set_engine_running(false);  // better way than forcing to std::exit.
                                                        // TODO: use custom exception to stop fresh running.
    break;
  }
  case LogType::Stdout: {
    // directly prints, fancy wrapper for std::cout << std::format.
    print_formats_recursive(
      Pack{Style::Standard, Foreground::FgBrWhite, Background::BgDefault, std::cout, ctx, std::move(format_args)...}
      );
    break;
  }
  }
  std::cout << '\n';
}

template<typename... Args>
static constexpr void log_info(const std::source_location& location, std::string_view ctx, Args&&... format_args) noexcept {
  log(location, LogType::Info, ctx, std::forward<Args>(format_args)...);
}

template<typename... Args>
static constexpr void log_warning(const std::source_location& location, std::string_view ctx, Args&&... format_args) noexcept {
  log(location, LogType::Warning, ctx, std::forward<Args>(format_args)...);
}

template<typename... Args>
static constexpr void log_error(const std::source_location& location, std::string_view ctx, Args&&... format_args) noexcept {
  log(location, LogType::Error, ctx, std::forward<Args>(format_args)...);
}

template<typename... Args>
static constexpr void log_stdout(const std::source_location& location, std::string_view ctx, Args&&... format_args) noexcept {
  log(location, LogType::Stdout, ctx, std::forward<Args>(format_args)...);
}

[[nodiscard]]
static constexpr std::source_location src(const std::source_location& location = std::source_location::current()) noexcept {
  return location;
}
} // namespace fresh