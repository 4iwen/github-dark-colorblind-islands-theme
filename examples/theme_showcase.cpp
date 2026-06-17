// GitHub Dark Colorblind Islands C++ theme showcase.
// Open this file in CLion to inspect comments, keywords, strings, numbers,
// functions, classes, diagnostics, preprocessor branches, and semantic tokens.

#include <algorithm>
#include <array>
#include <chrono>
#include <concepts>
#include <cstdint>
#include <exception>
#include <format>
#include <iostream>
#include <map>
#include <memory>
#include <optional>
#include <ranges>
#include <regex>
#include <stdexcept>
#include <string>
#include <string_view>
#include <tuple>
#include <variant>
#include <vector>

#define GHCB_TRACE(message) std::clog << "[trace] " << (message) << '\n'

#if defined(__clang__)
#  define GHCB_COMPILER "clang"
#elif defined(__GNUC__)
#  define GHCB_COMPILER "gcc"
#else
#  define GHCB_COMPILER "unknown"
#endif

namespace ghcb::demo {

using namespace std::chrono_literals;

constexpr std::uint32_t accent_blue = 0x58A6FF;
constexpr double warning_threshold = 0.80;
constexpr auto title = "GitHub Dark Colorblind Islands";

enum class Severity : std::uint8_t {
    info,
    warning,
    severe,
    danger,
};

struct Metrics {
    int files = 0;
    double contrast = 0.0;
    std::optional<std::string> note {};

    [[nodiscard]] bool healthy() const noexcept {
        return files > 0 && contrast >= warning_threshold;
    }
};

template <typename T>
concept Printable = requires(std::ostream& out, const T& value) {
    { out << value } -> std::same_as<std::ostream&>;
};

template <Printable T>
void print_value(std::string_view label, const T& value) {
    std::cout << std::format("{:>12}: {}\n", label, value);
}

class ThemeProbe final {
public:
    explicit ThemeProbe(std::string name)
        : name_(std::move(name)) {}

    [[nodiscard]] std::string describe(const Metrics& metrics) const {
        const auto state = metrics.healthy() ? "ready" : "needs review";
        return std::format("{} [{}] files={} contrast={:.2f}",
                           name_, state, metrics.files, metrics.contrast);
    }

    [[deprecated("Use describe(Metrics) for richer output")]]
    std::string legacy_name() const {
        return name_;
    }

private:
    std::string name_;
};

auto build_metrics() -> std::map<std::string, Metrics> {
    return {
        {"editor", {.files = 1, .contrast = 0.92, .note = "main surface #0D1117"}},
        {"toolwindow", {.files = 2, .contrast = 0.84, .note = "inset #010409"}},
        {"diff", {.files = 3, .contrast = 0.78, .note = std::nullopt}},
    };
}

std::variant<Metrics, std::string> parse_metric(std::string_view text) {
    static const std::regex pattern {R"((\w+):(\d+):([0-9]+\.[0-9]+))"};
    std::cmatch match {};

    if (!std::regex_match(text.data(), match, pattern)) {
        return std::string {"invalid metric payload"};
    }

    return Metrics {
        .files = std::stoi(match[2].str()),
        .contrast = std::stod(match[3].str()),
        .note = match[1].str(),
    };
}

void render_table(const std::map<std::string, Metrics>& rows) {
    for (const auto& [name, metrics] : rows) {
        const auto marker = metrics.healthy() ? '+' : '!';
        std::cout << marker << ' ' << name << " -> ";
        print_value("contrast", metrics.contrast);
    }
}

void demonstrate_control_flow(Severity severity) {
    switch (severity) {
        case Severity::info:
            GHCB_TRACE("info path");
            break;
        case Severity::warning:
            std::cout << "warning: attention color should be amber\n";
            break;
        case Severity::severe:
        case Severity::danger:
            throw std::runtime_error {"danger/severe path should be orange"};
    }
}

} // namespace ghcb::demo

int main() try {
    using ghcb::demo::Severity;
    using ghcb::demo::ThemeProbe;

    const ThemeProbe probe {ghcb::demo::title};
    const auto rows = ghcb::demo::build_metrics();
    const auto parsed = ghcb::demo::parse_metric("editor:42:0.95");

    std::visit([](const auto& value) {
        if constexpr (std::same_as<std::decay_t<decltype(value)>, ghcb::demo::Metrics>) {
            std::cout << "parsed metric contrast: " << value.contrast << '\n';
        } else {
            std::cerr << value << '\n';
        }
    }, parsed);

    for (const auto& [name, metrics] : rows | std::views::filter([](const auto& row) {
             return row.second.files > 0;
         })) {
        std::cout << probe.describe(metrics) << " // " << name << '\n';
    }

    ghcb::demo::render_table(rows);
    ghcb::demo::demonstrate_control_flow(Severity::warning);

    const std::string raw_json = R"json({
      "editor.background": "#0D1117",
      "editor.foreground": "#C9D1D9",
      "editorCursor.foreground": "#58A6FF"
    })json";
    std::cout << raw_json << '\n';

    // TODO: Check TODO highlighting.
    // FIXME: Check warning/error stripe highlighting.
    return 0;
} catch (const std::exception& error) {
    std::cerr << "fatal: " << error.what() << '\n';
    return 1;
}
