#include "GArgs/GArgs.hpp"
#include "ProjectManager-Application/Application.hpp"
#include <cstdlib>
#include <filesystem>
#include <iostream>

int main(int argc, char *argv[]) {
  #if __linux__
    const std::filesystem::path USER_DIRECTORY = std::getenv("HOME");
  #elif _WIN32
    const std::filesystem::path USER_DIRECTORY = (std::string)std::getenv("HOMEDRIVE") + std::getenv("HOMEPATH");
  #endif

  const std::string TEMPLATE_DIR_STRING = "--template-dir";
  const std::string LIST_TEMPLATES_STRING = "list-templates";
  const std::string ADD_TEMPLATE_STRING = "add-template";
  const std::string REMOVE_TEMPLATE_STRING = "remove-template";
  const std::string CREATE_STRING = "create";
  const std::string DELETE_STRING = "delete";
  const std::string RENAME_STRING = "rename";

  ProjectManager::Application app(
      (USER_DIRECTORY / APPLICATION_NAME).string(), GArgs::Parser(APPLICATION_NAME, "V1.0", true));

  app.parser.AddStructure(
      "[flags:value_amount=0,argument_filter=-,help=Flag "
      "Values;command:help=Run Command;name:help=The "
      "Name of the Project to apply command;directory:help=Path to directory]");

  app.parser.AddKey(
      GArgs::Key("flags", "-h | --help", "Display's this message"));
  app.parser.AddKey(
      GArgs::Key("flags", TEMPLATE_DIR_STRING, "Sets template directory"));
  app.parser.AddKey(
      GArgs::Key("command", LIST_TEMPLATES_STRING, "List available templates"));
  app.parser.AddKey(
      GArgs::Key("command", CREATE_STRING, "Creates a new Project"));
  app.parser.AddKey(
      GArgs::Key("command", DELETE_STRING, "Deletes an existing Project"));
  app.parser.AddKey(GArgs::Key("command", RENAME_STRING,
                               "Rename a Project created with the tool"));
  app.parser.AddKey(GArgs::Key("command", ADD_TEMPLATE_STRING,
                               "Adds a new Project template to generate"));
  app.parser.AddKey(GArgs::Key("command", REMOVE_TEMPLATE_STRING,
                               "Removes an existing Project template"));
  app.parser.AddKey(GArgs::Key("name", "*", "Template Name"));
  app.parser.AddKey(GArgs::Key("directory", "*", "Directory path"));

  app.parser.ParseArgs(argc, argv);

  // Print help if help arg is present
  if (app.parser.Contains("flags", "-h")) {
    app.parser.DisplayHelp();
    return 0;
  }

  // Set Template Directory from argument
  if (app.parser.Contains("flags", TEMPLATE_DIR_STRING)) {
    for (auto flag : app.parser["flags"]) {
      unsigned long index = flag.find(TEMPLATE_DIR_STRING);
      if (index != flag.npos) {
        flag.erase(index, TEMPLATE_DIR_STRING.length() + 1);
        app.templateDir = flag;
      }
    }
  }

  app.SetupTemplateDir();

  // Remove template
  if (app.parser.Contains("command", REMOVE_TEMPLATE_STRING)) {
    if (app.parser["name"].size() == 0) {
      std::cerr << "Template name not given" << std::endl;
      return 1;
    }
    const std::string templatePath =
        ((std::filesystem::path)app.templateDir / app.parser["name"][0]).string();

    if (!app.Exists(templatePath)) {
      std::cout << "Template doesn't exist" << std::endl;
      return 1;
    }
    if (app.RemoveDir(templatePath)) {
      std::cout << "Removed template" << std::endl;
      return 0;
    } else {
      std::cout << "Failed to remove template" << std::endl;
      return 1;
    }
  }

  // Create Template
  if (app.parser.Contains("command", ADD_TEMPLATE_STRING)) {
    if (app.parser["name"].size() == 0) {
      std::cerr << "Template name not given" << std::endl;
      return 1;
    }

    if (app.parser["directory"].size() == 0) {
      std::cerr << "No directory given for source" << std::endl;
      return 1;
    }

    const std::string templatePath =
        ((std::filesystem::path)app.templateDir / app.parser["name"][0]).string();

    const std::string copyPath = app.parser["directory"][0];

    if (app.Exists(templatePath)) {
      std::cout << "Template already exists" << std::endl;
      return 1;
    } else {
      if (app.CopyDir(templatePath, copyPath)) {
        std::cout << "Created template" << std::endl;
        return 0;
      } else {
        std::cout << "Failed to create template" << std::endl;
        return 1;
      }
    }
  }

  // List Templates
  if (app.parser.Contains("command", LIST_TEMPLATES_STRING)) {
    std::cout << "Template projects: " << std::endl;

    for (const auto &dir : app.ListDir(app.templateDir)) {
      std::cout << dir << std::endl;
    }

    return 0;
  }

  // Delete Project
  if (app.parser.Contains("command", DELETE_STRING)) {
    if (app.parser["name"].size() == 0) {
      std::cerr << "Project name not given" << std::endl;
      return 1;
    }

    if (app.parser["directory"].size() == 0) {
      std::cerr << "No directory given for source" << std::endl;
      return 1;
    }

    const std::string projectPath =
        ((std::filesystem::path)app.parser["directory"][0] / app.parser["name"][0]).string();

    if (app.RemoveDir(projectPath)) {
      std::cout << "Deleted project " << app.parser["name"][0] << std::endl;
      return 0;
    } else {
      std::cerr << "Failed to delete project" << std::endl;
      return 1;
    }
  }

  // Create Project
  if (app.parser.Contains("command", CREATE_STRING)) {
    if (app.parser["name"].size() == 0) {
      std::cerr << "Project template not given" << std::endl;
      return 1;
    }

    if (app.parser["directory"].size() == 0) {
      std::cerr << "No directory given for source" << std::endl;
      return 1;
    }

    const std::string projectPath =
        ((std::filesystem::path)app.parser["directory"][0] / app.parser["name"][0]).string();

    if (app.CopyDir(projectPath,
                    ((std::filesystem::path)app.templateDir / app.parser["name"][0]).string())) {
      std::cout << "Project created from " << app.parser["name"][0]
                << std::endl;
      return 0;
    } else {
      std::cerr << "Failed to create project" << std::endl;
      return 1;
    }
  }

  if (app.parser.Contains("command", RENAME_STRING)) {
    if (app.parser["name"].size() == 0) {
      std::cerr << "Project name not given" << std::endl;
      return 1;
    }

    if (app.parser["directory"].size() == 0) {
      std::cerr << "No directory given for source" << std::endl;
      return 1;
    }

    const std::string projectNameOld = app.parser["name"][0];
    const std::string projectPathOld =
        app.AbsPath(((std::filesystem::path)app.parser["directory"][0] /
                    projectNameOld).string());

    std::string projectPathNew = app.AbsPath(app.parser["directory"][0]);
    std::string projectNameNew;

    std::cout << "Please enter a new project name to replace old: " << '(' << projectNameOld << ") -> ";

    char c = '\0';
    while (c != '\n') {
      std::cin.get(c);
      if (c != '\n') {
        projectNameNew += c;
      }
    }

    projectPathNew = ((std::filesystem::path)projectPathNew / projectNameNew).string();

    if (app.CopyDir(projectPathNew, projectPathOld)) {
      if (app.RemoveDir(projectPathOld)) {
        std::cout << "Successfully renamed project" << std::endl;
        return 0;
      } else {
        std::cerr << "Failed to remove old directory" << std::endl;
        return 1;
      }
    } else {
      std::cerr << "Failed to copy project content" << std::endl;
      return 1;
    }
  }

  std::cerr << "Please add the correct arguments. Use --help for a list of "
               "available arguments"
            << std::endl;

  return 0;
}
