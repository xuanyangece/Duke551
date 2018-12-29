#include <dirent.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

/* modified later */
bool isExit(std::string input) {
  // corner case: exit with space around - still exit
  // corner case: e\x\i\t - should not exit
  char * command = NULL;
  command = std::strtok(&input[0], " ");
  std::string compare(command);
  command = std::strtok(NULL, " ");

  if (compare == "exit" && command == NULL) {
    return true;
  }
  else {
    return false;
  }
}

bool isSpace(std::string input) {
  // loop for all characters, any nonspace found return false
  for (size_t i = 0; i < input.size(); i++) {
    if (input[i] != ' ')
      return false;
  }

  // empty input or only space, return true
  return true;
}

// prune input to detect '\' in args after command
std::string pruneInput(std::string input) {
  // answer stores the result of pruning
  std::string answer;

  // first_space mark the status of if currently on the left space of command
  // second_space mark the status of if currently on the right space of command
  /* for example "  ls  -a"
     first_space detect space on the left of "ls"
     second_space detect space between "ls" and "-a"
   */
  bool first_space = true;
  bool second_space = true;

  /* 
     Using those two space flags to detect if we are on the right of our command.
     When both of them are false, we are on the right of command.
     This is where we should ignore all '/'.
   */
  for (size_t i = 0; i < input.size(); i++) {
    if (first_space && second_space) { /* on the left of command or already pass it */
      if (input[i] != ' ') {           /* found first nonspace character */
        first_space = false;
        answer += input[i];
      }
    }
    else if (second_space) { /* on command itself or just after it */
      if (input[i] == ' ') { /* just after command, first space after command */
        second_space = false;
      }
      answer += input[i];
    }
    else { /* passed commands, safely remove all '\' */
      if (input[i] != '\\') {
        answer += input[i];
      }
    }
  }

  return answer;
}

std::string findPath(std::vector<char *> paths, char * command) {
  std::string answer = "";

  // iterate each possible path in paths
  for (std::vector<char *>::iterator it = paths.begin(); it != paths.end(); ++it) {
    // open directory
    DIR * d = opendir(*it);
    if (!d) {
      std::cerr << "invalid directory path." << std::endl;
      exit(EXIT_FAILURE);
    }

    // seperate command's name itself and directory name
    std::string command_name(command);
    std::string dirname(*it);
    dirname += "/";

    // search file
    struct dirent * entry;
    while ((entry = readdir(d)) != NULL) {
      std::string filename(entry->d_name);

      // handle . and ..
      if (filename == "." || filename == "..")
        continue;

      // command matches!
      if (command_name == filename) {
        answer += dirname + filename;
        return answer;
      }
    }
  }

  // no matches, return empty string
  return answer;
}

void executePath(std::string & path_found, std::vector<char *> & args, std::vector<char *> & envs) {
  if (path_found == "") { /* no match with command */
    std::cout << "Command " << args[0] << " not found" << std::endl;
    _exit(atoi(args[0]));
  }
  else { /* command found in environment path */
    // update command with full path
    args[0] = &path_found[0];

    execve(args[0], &args[0], &envs[0]);
  }
}

int main(int argc, char ** argv, char ** envp) {
  // input - stores input command every time user types
  // path_found - stores the full path of command, which will be used when searching command path
  std::string input;
  std::string path_found;

  std::cout << "myShell$ ";

  // gets all environment variables & stores them in vector
  std::vector<char *> envs;
  for (char ** env = envp; *env != NULL; ++env) {
    envs.push_back(*env);
  }
  envs.push_back(NULL);

  // gets environment variable PATH & stores it in value
  const char * path = "PATH";
  char * value = getenv(path);

  // read from stdin
  while (std::getline(std::cin, input)) {
    // if input is only white space, then continue without and fork()
    if (isSpace(input)) {
      std::cout << "myShell$ ";
      continue;
    }

    // if input is exit, then exit
    if (isExit(input))
      break;

    input = pruneInput(input);

    // define current pid as cpid, wait pid as w
    // wait status = wstatus
    pid_t cpid, w;
    int wstatus;

    cpid = fork();

    // child process error
    if (cpid == -1) {
      std::cerr << "fork";
      exit(EXIT_FAILURE);
    }

    if (cpid == 0) { /* code excuted by child */
      /* parse input line to new argv and new envp */

      // use vector to parse command line arg and its length
      std::vector<char *> args;

      // delimiter = " ", cut original string into pieces
      char * p = std::strtok(&input[0], " ");
      while (p != NULL) {
        args.push_back(p);
        p = std::strtok(NULL, " ");
      }
      p = NULL;
      args.push_back(p);

      // args.size() > 1 means input is not space or empty
      if (args.size() > 1) {
        // find whether '/' exists in command name
        std::string first(args[0]);
        std::size_t found = first.find("/");

        if (found != std::string::npos) { /* path provided, search in specific path */
          // use loop to let pos point at the last occurence of '/', which aims to find directory
          size_t pos = 0;
          for (size_t i = first.size() - 1; i >= 0; i--) {
            if (first[i] == '/') {
              pos = i;
              break;
            }
          }

          // if '/' appears at last, command is purely a directory, which is incorrect
          if (pos == first.size() - 1) {
            std::cerr << "Invalid command: not a directory!" << std::endl;
            _exit(atoi(args[0]));
          }
          else {
            std::string command_dir = first.substr(0, pos + 1);
            std::string command_name = first.substr(pos + 1);

            std::vector<char *> paths;
            paths.push_back(&command_dir[0]);

            // find the path use function findPath() & execute it
            path_found = findPath(paths, &command_name[0]);
            executePath(path_found, args, envs);
          }
        }
        else { /* no path provided, search it */
          // store all paths in vector
          std::vector<char *> paths;
          char * curt_path = std::strtok(value, ":");
          while (curt_path != NULL) {
            paths.push_back(curt_path);
            curt_path = std::strtok(NULL, ":");
          }

          // find the path use function findPath() & execute it
          path_found = findPath(paths, args[0]);
          executePath(path_found, args, envs);
        }
      }
      // don't expect return unless error
      _exit(atoi(args[0]));
    }
    else { /* code executed by parent */
      do {
        w = waitpid(cpid, &wstatus, WUNTRACED | WCONTINUED);
        if (w == -1) {
          std::cerr << "waitpid";
          exit(EXIT_FAILURE);
        }

        if (WIFSIGNALED(wstatus)) {
          std::cout << "Program was killed by signal " << WTERMSIG(wstatus) << std::endl;
        }
        else if (WIFEXITED(wstatus)) {
          std::cout << "Program exited with status " << WEXITSTATUS(wstatus) << std::endl;
        }
      } while (!WIFEXITED(wstatus) &&
               !WIFSIGNALED(
                   wstatus)); /* exit unnormally && no signal raised to cause exit, then loop again 
SOMETHING TO TEST: WHAT IF ERROR */
    }

    std::cout << "myShell$ ";
  }

  // print information before exit
  std::cout << "Program exited with status " << EXIT_SUCCESS << std::endl;

  return EXIT_SUCCESS;
}
