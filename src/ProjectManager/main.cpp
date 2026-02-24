#include "GArgs/GArgs.hpp"
#include "GArgs/Version.hpp"
#include "ProjectManager/Templates.hpp"
#include <cstdlib>
#include <filesystem>
#include <iostream>

static const std::string APPLICATION_NAME_STRING = PROJECT_MANAGER_APPLICATION_NAME;
static const GArgs::Version<size_t> APPLICATION_VERSION_OBJ = {
  PROJECT_MANAGER_MAJOR_VERSION,
  PROJECT_MANAGER_MINOR_VERSION,
  PROJECT_MANAGER_PATCH_VERSION,
};

static const std::filesystem::path APPLICATION_DATA_DIRECTORY = PROJECT_MANAGER_DATA_DIR;

static const std::string HELP_FLAG = "--help";

static const std::string LIST_TEMPLATES_COMMAND = "list-templates";
static const std::string ADD_TEMPLATE_COMMAND = "add-template";
static const std::string REMOVE_TEMPLATE_COMMAND = "remove-template";
static const std::string CREATE_COMMAND = "create";
static const std::string DELETE_COMMAND = "delete";

static const std::string WILDCARD_PATH = "*";

int main(int argc, char *argv[]) {
  GArgs::Parser parser(APPLICATION_NAME_STRING, APPLICATION_VERSION_OBJ);
  GArgs::ArgumentSlot flags("flags", "Program flags.", "-", 0, 0);
  GArgs::ArgumentSlot command("command", "Program action.", "", 1, 1);
  GArgs::ArgumentSlot path("path", "Path to apply command on.", "", 0, 1);

  flags.AddKey(GArgs::ArgumentKey(HELP_FLAG));
  command.AddKey(GArgs::ArgumentKey(LIST_TEMPLATES_COMMAND));
  command.AddKey(GArgs::ArgumentKey(ADD_TEMPLATE_COMMAND));
  command.AddKey(GArgs::ArgumentKey(REMOVE_TEMPLATE_COMMAND));
  command.AddKey(GArgs::ArgumentKey(CREATE_COMMAND));
  command.AddKey(GArgs::ArgumentKey(DELETE_COMMAND));
  path.AddKey(GArgs::ArgumentKey(WILDCARD_PATH));

  parser.AddSlot(flags);
  parser.AddSlot(command);
  parser.AddSlot(path);

  try {
    parser.Parse(argc, argv);
  }
  catch (const std::exception&) {
    if (parser["flags"].Has("--help")) {
      std::cout << parser.Help();
      return 0;
    } else {
      std::cerr << "Required argument not supplied." << std::endl;
      return 1;
    }
  }

  if (parser["flags"].Has("--help")) {
    std::cout << parser.Help();
    return 0;
  }

  // Application data setup
  if (!std::filesystem::exists(APPLICATION_DATA_DIRECTORY)) {
    std::cerr << "Program data directory corrupted!" << std::endl;
    return 1;
  }

  if ((std::string)parser["command"][0] == LIST_TEMPLATES_COMMAND) {
    ProjectManager::ListTemplates(APPLICATION_DATA_DIRECTORY, std::cout);
    return 0;
  }

  if ((std::string)parser["command"][0] == ADD_TEMPLATE_COMMAND) {
    if (parser["path"].Size() == 1) {
      try {
        ProjectManager::CreateTemplate(APPLICATION_DATA_DIRECTORY, std::cout, (std::string)parser["path"][0]);
        return 0;
      }
      catch (const std::exception& e) {
        std::cerr << "Error creating template: " << e.what() << std::endl;
        return 1;
      }
    }
    else {
      std::cerr << "Path not supplied." << std::endl;
      return 1;
    }
  }

  if ((std::string)parser["command"][0] == REMOVE_TEMPLATE_COMMAND) {
    try {
      ProjectManager::DeleteTemplate(APPLICATION_DATA_DIRECTORY, std::cout, std::cin);
      return 0;
    }
    catch (const std::exception& e) {
      std::cerr << "Error deleting template: " << e.what() << std::endl;
      return 1;
    }
  }

  std::cerr << "Unknown command! Use --help flag for more information." << std::endl;
  return 1;
}
