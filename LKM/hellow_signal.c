#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

void sighup_handler() {
	int pid = getpid();

	signal(SIGHUP, SIG_IGN); /* reset signal */
	printf("\n\n From signal handler with PID=%d I have received a SIGHUP signal \n", pid);
}

void sigint_handler() {
	int pid = getpid();

	signal(SIGINT, SIGN_IGN); /*reset signal */
	printf("\n\n From signal handler with PID=%d I have received a SIGINT signal \n", pid);
}

void sigquit_handler() {
	int pid = getpid();

	//signal(SIGINT, SIGN_IGN); /*reset signal */
	printf("\n\n From signal handler with PID=%d I have received a SIGQUIT signal \n", pid);
}

main() {
	int pid0;
	int pid = getpid();

	/* setup signal handler */
	printf("\nParent: Setting up SIGHUP handler with pid = %d \n\n", pid);
	signal(SIGHUP, sighup_handler); /*set function call*/

	printf("\nParent: Setting up SIGINT handler with pid = %d \n\n", pid);
	signal(SIGINT, sigint_handler); /*set function call*/

	printf("\nParent: Setting up SIGQUIT handler with pid = %d \n\n", pid);
	signal(SIGQUIT, sigquit_handler); /*set function call*/

	/* set the child process */
	if (pid0 == fork() < 0) {
		perror("fork");
		exit(1);
	}

	if (pid0 == 0) {
		/*child */
		pid = getpid();
		printf("\nChild process invoked with PID = %d \n\n", pid);

		/* setup the signal handler */
		printf("\nChild: Setting up SIGHUP handler with pid = %d \n\n", pid);
		signal(SIGHUP, sighup_handler); /*set function call*/

		printf("\nChild: Setting up SIGINT handler with pid = %d \n\n", pid);
		signal(SIGINT, sigint_handler); /*set function call*/

		printf("\nChild: Setting up SIGQUIT handler with pid = %d \n\n", pid);
		signal(SIGQUIT, sigquit_handler); /*set function call*/

		loop(;;); /* loop forever*/
	} else {
		/*parent*/

		printf("\nParent: sending SIGHUP Parent pid = %d \n\n", pid);
		kill(pid, SIGHUP);
		sleep(3);

		printf("\nParent: sending SIGINT Parent pid = %d \n\n", pid);
		kill(pid, SIGINT);
		sleep(3);

		printf("\nParent: sending SIGQUIT Parent pid = %d \n\n", pid);
		kill(pid, SIGQUIT);
		sleep(3);
	}
}
