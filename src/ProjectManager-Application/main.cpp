#include "GArgs.hpp"
#include "ProjectManager-Application/Application.hpp"
#include <iostream>

int main(int argc, char *argv[]) {
  ProjectManager::Application app(
      "/opt/ProjectManager", GArgs::Parser("ProjectManager", "V1.0", true));

  app.parser.AddStructure(
      "[flags:value_amount=0,argument_filter=--,help=Flag "
      "Values;command:help=Run Command;name:help=The "
      "Name of the Project to apply command;directory:help=Path to directory]");

  app.parser.AddKey(GArgs::Key("flags", "--help", "Display's this message"));
  app.parser.AddKey(
      GArgs::Key("flags", "--template_dir", "Sets template directory"));
  app.parser.AddKey(
      GArgs::Key("command", "list_templates", "List available templates"));
  app.parser.AddKey(GArgs::Key("command", "create", "Creates a new Project"));
  app.parser.AddKey(
      GArgs::Key("command", "delete", "Deletes an existing Project"));
  app.parser.AddKey(GArgs::Key("command", "rename",
                               "Rename a Project created with the tool"));
  app.parser.AddKey(GArgs::Key("command", "add_template",
                               "Adds a new Project template to generate"));
  app.parser.AddKey(GArgs::Key("command", "remove_template",
                               "Removes an existing Project template"));
  app.parser.AddKey(GArgs::Key("name", "*", "Template Name"));
  app.parser.AddKey(GArgs::Key("directory", "*", "Directory path"));

  app.parser.ParseArgs(argc, argv);

  // Print help if help arg is present
  if (app.parser.Contains("flags", "--help")) {
    app.parser.DisplayHelp();
    return 0;
  }

  // Set Template Directory from argument
  const std::string templateDirStr = "--template_dir";
  if (app.parser.Contains("flags", templateDirStr)) {
    int startIndex =
        app.parser["flags"].find(templateDirStr) + templateDirStr.length() + 1;
    int endIndex = app.parser["flags"].find(' ', startIndex);
    app.templateDir =
        app.parser["flags"].substr(startIndex, endIndex - startIndex);
  }

  app.SetupTemplateDir();

  // Remove template
  if (app.parser.Contains("command", "remove_template")) {
    if (app.parser["name"] == "") {
      std::cerr << "Template name not given" << std::endl;
      return 1;
    } else {
      const std::string templatePath =
          app.templateDir + "/" + app.parser["name"];

      if (!app.Exists(templatePath)) {
        std::cout << "Template doesn't exist" << std::endl;
        return 1;
      } else {
        if (app.RemoveDir(templatePath)) {
          std::cout << "Removed template" << std::endl;
          return 0;
        } else {
          std::cout << "Failed to remove template" << std::endl;
          return 1;
        }
      }
    }
  }

  // Create Template
  if (app.parser.Contains("command", "add_template")) {
    if (app.parser["directory"] == "") {
      std::cerr << "No directory given for source" << std::endl;
      return 1;
    }

    if (app.parser["name"] == "") {
      std::cerr << "Template name not given" << std::endl;
      return 1;
    } else {
      const std::string templatePath =
          app.templateDir + '/' + app.parser["name"];

      const std::string copyPath = app.parser["directory"];

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
  }

  // List Templates
  if (app.parser.Contains("command", "list_templates")) {
    std::cout << "Template projects: " << std::endl;

    for (const auto &dir : app.ListDir(app.templateDir)) {
      std::cout << dir << std::endl;
    }

    return 0;
  }

  // Delete Project
  if (app.parser.Contains("command", "delete")) {
    if (app.parser["directory"] == "") {
      std::cerr << "No directory given for source" << std::endl;
      return 1;
    }

    if (app.parser["name"] == "") {
      std::cerr << "Project name not given" << std::endl;
      return 1;
    } else {
      const std::string projectPath =
          app.parser["directory"] + '/' + app.parser["name"];

      if (app.RemoveDir(projectPath)) {
        std::cout << "Deleted project " << app.parser["name"] << std::endl;
        return 0;
      } else {
        std::cerr << "Failed to delete project" << std::endl;
        return 1;
      }
    }
  }

  // Create Project
  if (app.parser.Contains("command", "create")) {
    if (app.parser["directory"] == "") {
      std::cerr << "No directory given for source" << std::endl;
      return 1;
    }

    if (app.parser["name"] == "") {
      std::cerr << "Project template not given" << std::endl;
      return 1;
    } else {
      const std::string projectPath =
          app.parser["directory"] + '/' + app.parser["name"];

      if (app.CopyDir(projectPath,
                      app.templateDir + '/' + app.parser["name"])) {
        std::cout << "Project created from " << app.parser["name"] << std::endl;
        return 0;
      } else {
        std::cerr << "Failed to create project" << std::endl;
        return 1;
      }
    }
  }

  if (app.parser.Contains("command", "rename")) {
    if (app.parser["directory"] == "") {
      std::cerr << "No directory given for source" << std::endl;
      return 1;
    }

    if (app.parser["name"] == "") {
      std::cerr << "New Project name not given" << std::endl;
      return 1;
    } else {
      const std::string projectPathOld = app.AbsPath(app.parser["directory"]);
      const std::string projectPathNew =
          app.GetContainingDir(projectPathOld) + '/' + app.parser["name"];

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
  }

  std::cerr << "Please add the correct arguments. Use --help for a list of "
               "available arguments"
            << std::endl;

  return 0;
}
