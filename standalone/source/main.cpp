#include <airportsim/airportsim.h>
#include <airportsim/version.h>

#include <cxxopts.hpp>
#include <iostream>
#include <string>
#include <unordered_map>

auto main(int argc, char** argv) -> int {
  const std::unordered_map<std::string, int> examples{
      {"cxxopts", 1},
      {"fmt", 2},
      {"spdlog", 3},
  };

  const std::unordered_map<std::string, airportsim::LanguageCode> languages{
      {"en", airportsim::LanguageCode::EN},
      {"de", airportsim::LanguageCode::DE},
      {"es", airportsim::LanguageCode::ES},
      {"fr", airportsim::LanguageCode::FR},
  };

  cxxopts::Options options(*argv, "A program to welcome the world!");

  std::string language;
  std::string name;

  // clang-format off
  options.add_options()
    ("h,help", "Show help")
    ("v,version", "Print the current version number")
    ("n,name", "Name to greet", cxxopts::value(name)->default_value("World"))
    ("l,lang", "Language code to use", cxxopts::value(language)->default_value("en"))
  ;
  // clang-format on

  auto result = options.parse(argc, argv);

  if (result["help"].as<bool>()) {
    std::cout << options.help() << std::endl;
    return 0;
  }

  if (result["version"].as<bool>()) {
    std::cout << "AirportSim, version " << AIRPORTSIM_VERSION << std::endl;
    return 0;
  }

  auto langIt = languages.find(language);
  if (langIt == languages.end()) {
    std::cerr << "unknown language code: " << language << std::endl;
    return 1;
  }

  airportsim::AirportSim airportsim(name);
  std::cout << airportsim.greet(langIt->second) << std::endl;

  return 0;
}
