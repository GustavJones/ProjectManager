#pragma once
#include "GArgs/Parser.hpp"
#include <filesystem>
#include <ostream>
#include <vector>

namespace ProjectManager {
  std::vector<std::filesystem::path> GetTemplatePaths(const std::filesystem::path &_appdataPath) noexcept;
  std::vector<std::string> GetTemplateNames(const std::filesystem::path &_appdataPath) noexcept;
  
  void ListTemplates(const std::filesystem::path &_appdataPath, std::ostream &_stream) noexcept;
  void CreateTemplate(const std::filesystem::path &_appdataPath, std::ostream &_stream, const std::filesystem::path &_path);
  void DeleteTemplate(const std::filesystem::path &_appdataPath, std::ostream &_outstream, std::istream &_instream);
}
