#include <cstdlib>
#include <filesystem>

#include <fmt/core.h>
#include <fmt/color.h>
#include <git2/global.h>
#include <git2/repository.h>


int main(int argc, char *argv[]) {
    git_libgit2_init();

    fmt::print(fg(fmt::color::dark_red) | fmt::emphasis::bold, "Hello from pankage!\n\n");

    if (argc != 2) {
        fmt::print("You need to provide exactly one argument:\n"
                   "    {} FOLDER"                          "\n", argv[0]);

        return EXIT_FAILURE;
    }

    std::string target_path = std::filesystem::absolute(argv[1]);
	git_repository *repo = nullptr;

    int error_code = 0;
    if ((error_code = git_repository_init(&repo, target_path.c_str(), /* is bare: */ false)) != 0) {
        fmt::print("Error, couldn't create a repository in {}!\n"
                   "Error code: {}"                          "\n", target_path, error_code);

        return EXIT_FAILURE;
    }

    fmt::print("Create new git repository in '{}'!\n", target_path);

    git_libgit2_shutdown();
}
