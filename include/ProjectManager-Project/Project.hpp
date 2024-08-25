#pragma once

#include <string>

namespace ProjectManager {
class Project {
public:
  Project();
  Project(Project &&) = default;
  Project(const Project &) = default;
  Project &operator=(Project &&) = default;
  Project &operator=(const Project &) = default;
  ~Project();

  std::string name;
};
} // namespace ProjectManager
