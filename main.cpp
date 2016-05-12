#include <iostream>
#include <stdio.h>
#include <unistd.h> //used for fork(), execvp()
#include <sys/types.h> //used for wait
#include <sys/wait.h> //used for wait
#include <string.h>
#include <cstdlib>
using namespace std;

/*void execute(string command) {
	
	pid_t pid = fork(); //creates child process
	int status = 0;
	if (pid == -1) {
		perror("fork");
	}
	cout << "String command is: " << command << endl;
	if (pid == 0) {
		//char* path = "/bin/";
		cout << "Child: " << pid << endl;
		//convert string to char* to pass into exec()
		char* cmd = new char[command.length() + 1];
		strcpy(cmd, command.c_str());
		if(execvp(cmd,path) == -1) { //calls execvp WHILE checking to see if it = -1
			perror("exec");
			exit(-1);
		}
	}
	else { //Otherwise, the process is a parent
		cout << "This is a parent process" << endl;
		waitpid(pid, &status, 0); //wait for the child process to finish
		cout << "Process returned" << WEXITSTATUS(status) << endl;
	}
	
	if (pid > 0) {
		if (wait(0) == -1) {//waits for child to finish
			perror("wait");
		}
		cout << "Parent: " << pid << endl;
	}
}*/

void execute(char** commandArr) {
	
	/*if(line == "exit") {
		exit(0);
	}*/

	int status = 0;	
	char fullpath[20] = "/bin/"; //full file path	
	strcat(fullpath, commandArr[0]); //add the first command to the file path
	int pid = fork();
	if(pid==0) { //if the process is a child
		execvp(fullpath,commandArr);
	}
	else { //Otherwise, the process is a parent
		wait(NULL);
		//waitpid(pid, &status, 0); //wait for the child process to finish
	}

}

void parse_string(string &commandLine, char** cmdArray) { 
	char* token; //split command into separate strings
	char* cmd = new char[commandLine.length() + 1];
	strcpy(cmd, commandLine.c_str());
	token = strtok(cmd, " ");
	int i = 0;
	for (; token != NULL; i++) {
		cmdArray[i] = token;
		token = strtok(NULL, " ");
	}
	cmdArray[i] = NULL;
	
} 
void printPrompt() {
	char* user = getlogin();
	char host[BUFSIZ]; //creates a host name with buffer size
	int hostID = gethostname(host, 1024);
	if (user == NULL) { //could not find the username
		cout << "$ ";
	}
	else {
		cout << user << '@' << host << "$ ";
	}
}

int main () {
		char* cmdArr[100]; //will hold an array of parsed commands
		printPrompt();
		string cmdLine = "";
		getline(cin, cmdLine);
		//cout << cmdLine << endl;
		//cout << "First parsed string is: " << cmdArr[0] << endl;
		parse_string(cmdLine, cmdArr);
		execute(cmdArr); //execute the list of commands
		return 0;
}
