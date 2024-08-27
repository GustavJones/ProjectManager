#pragma once
#include "GArgs.hpp"

#include <string>
#include <vector>

namespace ProjectManager {
class Application {
public:
  Application(const std::string &_template_dir, const GArgs::Parser &_parser);
  Application(Application &&) = default;
  Application(const Application &) = default;
  Application &operator=(Application &&) = default;
  Application &operator=(const Application &) = default;
  ~Application();

  bool SetupTemplateDir();
  bool RemoveDir(const std::string &_path);
  bool CreateDir(const std::string &_path);
  std::vector<std::string> ListDir(const std::string &_path);
  std::string AbsPath(const std::string &_path);
  std::string GetContainingDir(const std::string &_path);
  bool CopyDir(const std::string &_destination, const std::string &_source);
  bool Exists(const std::string &_path);

  std::string templateDir;
  GArgs::Parser parser;
};

} // namespace ProjectManager
