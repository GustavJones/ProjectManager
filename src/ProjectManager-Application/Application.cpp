#include "ProjectManager-Application/Application.hpp"
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

namespace ProjectManager {
Application::Application(const std::string &_template_dir,
                         const GArgs::Parser &_parser)
    : templateDir(_template_dir), parser(_parser) {}

Application::~Application() {}

bool Application::SetupTemplateDir() {
  if (std::filesystem::exists(templateDir)) {
    return true;
  } else {
    std::cout << "Template Directory doesn't exist. Creating now!" << std::endl;
    return std::filesystem::create_directory(templateDir);
  }
}

bool Application::RemoveDir(const std::string &_path) {
  if (!std::filesystem::exists(_path)) {
    return false;
  } else {
    return std::filesystem::remove_all(_path);
  }
}

bool Application::CreateDir(const std::string &_path) {
  return std::filesystem::create_directory(_path);
}

std::vector<std::string> Application::ListDir(const std::string &_path) {
  std::vector<std::string> out;

  for (const auto &dir : std::filesystem::directory_iterator(_path)) {
    out.push_back(dir.path().filename());
  }

  return out;
}

bool Application::CopyDir(const std::string &_destination,
                          const std::string &_source) {

  if (!Exists(_source)) {
    return false;
  } else {
    CreateDir(_destination);

    std::filesystem::copy(
        _source, _destination,
        std::filesystem::copy_options::recursive |
            std::filesystem::copy_options::overwrite_existing);
    return true;
  }
}

bool Application::Exists(const std::string &_path) {
  return std::filesystem::exists(_path);
}

} // namespace ProjectManager
