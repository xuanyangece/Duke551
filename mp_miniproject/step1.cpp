#include <sys/wait.h>
#include <unistd.h>

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char ** argv) {
  std::string input;
  std::cout << "myShell$ ";

  // read from stdin
  while (std::getline(std::cin, input)) {
    // if input is exit, then exit
    if (input == "exit")
      break;

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
      char * cstr = new char[input.length() + 1];
      std::strcpy(cstr, input.c_str());
      std::vector<char *> vec;

      // delimiter = " ", cut original string into pieces
      char * p = std::strtok(cstr, " ");
      while (p != NULL) {
        vec.push_back(p);
        p = std::strtok(NULL, " ");
      }

      // convert vector to newargv
      char ** newargv = new char *[vec.size() + 1];
      newargv[vec.size()] = NULL;
      for (size_t i = 0; i < vec.size(); i++) {
        newargv[i] = vec[i];
      }

      // envp set to {NULL}
      char * envp[] = {NULL};

      execve(newargv[0], newargv, envp);

      // expect no return unless error
      // CORNER CASE: no input or invalid input, then new shell directly or print message and new shell
      if (vec.size() > 0)
        std::cerr << "Command line " << newargv[0] << " not found." << std::endl;
      _exit(atoi(argv[0]));
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
