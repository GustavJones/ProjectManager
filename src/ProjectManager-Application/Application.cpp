#include "ProjectManager-Application/Application.hpp"
#include <filesystem>
#include <iostream>
#include <string>

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
