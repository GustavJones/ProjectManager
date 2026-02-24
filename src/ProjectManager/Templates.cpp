#include "ProjectManager/Templates.hpp"
#include <filesystem>
#include <stdexcept>
#include <string>
#include <vector>

namespace ProjectManager {
std::vector<std::filesystem::path> GetTemplatePaths(const std::filesystem::path &_appdataPath) noexcept {
  std::vector<std::filesystem::path> templates;

  std::filesystem::directory_iterator di(_appdataPath);
  for (const auto &folder : di) {
    if (!folder.is_directory()) {
      continue;
    }

    templates.push_back(folder.path());
  }

  return templates;
}

std::vector<std::string> GetTemplateNames(const std::filesystem::path &_appdataPath) noexcept {
  std::vector<std::string> templates;

  std::filesystem::directory_iterator di(_appdataPath);
  for (const auto &folder : di) {
    if (!folder.is_directory()) {
      continue;
    }

    templates.push_back(folder.path().filename());
  }

  return templates;
}

void ListTemplates(const std::filesystem::path &_appdataPath, std::ostream &_stream) noexcept {
  auto templates = GetTemplateNames(_appdataPath);
  _stream << "Templates: " << std::endl;
  for (const auto &templateName : templates) {
    _stream << "- " << templateName << std::endl;
  }
}

void CreateTemplate(const std::filesystem::path &_appdataPath, std::ostream &_stream, const std::filesystem::path &_path) {
  auto templateName = _path.filename();
  auto templateDataPath = _appdataPath / templateName;

  if (std::filesystem::exists(templateDataPath)) {
    throw std::runtime_error("Template already exists.");
  }

  if (!std::filesystem::exists(_path)) {
    throw std::runtime_error("Unknown path to template directory.");
  }

  std::filesystem::copy(_path, templateDataPath, std::filesystem::copy_options::recursive);
}

void DeleteTemplate(const std::filesystem::path &_appdataPath, std::ostream &_outstream, std::istream &_instream) {
  auto templateNames = GetTemplateNames(_appdataPath);

  _outstream << "Select a template: " << std::endl;
  for (size_t __templateIndex = 0; __templateIndex < templateNames.size(); __templateIndex++) {
    _outstream << __templateIndex + 1 << ": " << templateNames[__templateIndex] << std::endl;
  }

  _outstream << std::endl;
  _outstream << ": ";

  std::string templateNumberString;
  std::getline(_instream, templateNumberString);

  size_t templateNumber = 0;
  try {
    templateNumber = std::stoul(templateNumberString);
  }
  catch (const std::exception&) {
    throw std::runtime_error("Cannot parse number from input!");
  }

  if (templateNumber < 1 || templateNumber > templateNames.size()) {
    throw std::runtime_error("Out of bounds selection.");
  }

  auto templatePath = _appdataPath / templateNames[templateNumber - 1];

  if (!std::filesystem::exists(templatePath)) {
    throw std::runtime_error("Cannot find template directory.");
  }

  std::filesystem::remove_all(templatePath);
}
} // namespace ProjectManager
