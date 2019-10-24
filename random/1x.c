#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>

int handle_child_process_output(char buffer[], ssize_t count) {
	int max;
	for(int i=1; i<count; i++) {
		if(buffer[i-1]=='\n') {
			max=0;	
			for(int j=i; j<count; j++) {
				if(buffer[j]==':') break;
				max=max*10+(buffer[j]-'0');
			}
		}
	}
	return max;
}

int crshrand() {
	//system("./1"); //
	//http://www.microhowto.info/howto/capture_the_output_of_a_child_process_in_c.html
	int filedes[2];
	if (pipe(filedes) == -1) {
	  perror("pipe");
	  exit(1);
	}

	pid_t pid = fork();
	if (pid == -1) {
	  perror("fork");
	  exit(1);
	} else if (pid == 0) {
	  while ((dup2(filedes[1], STDOUT_FILENO) == -1) && (errno == EINTR)) {}
	  close(filedes[1]);
	  close(filedes[0]);
	  execl("./1", "1", (char*)0);
	  perror("execl");
	  _exit(1);
	}
	close(filedes[1]);

	char buffer[4096];
	int max=0;
	while (1) {
	  ssize_t count = read(filedes[0], buffer, sizeof(buffer));
	  if (count == -1) {
		if (errno == EINTR) {
		  continue;
		} else {
		  perror("read");
		  exit(1);
		}
	  } else if (count == 0) {
		break;
	  } else {
		max=handle_child_process_output(buffer, count);
	  }
	}
	close(filedes[0]);
	wait(0);
	return max;
}

