/**
 * Small program that copies a file. 
 * Comments are interspersed to comply with assignment.
 * Superfluous comments are interspersed because I was taught with Java
 * 	and have to remind myself of C semantics
 */
//contains printf
#include <stdio.h>
//contains open
#include <fcntl.h>
//contains the system-maintained errno integer, along with EXXXX consts
#include <errno.h>
//contains read,write
#include <unistd.h>
//contains stat
#include <sys/stat.h>
//contains string helper functions and NULL
#include <string.h>
//wowwie C doesn't have booleans by default
#include <stdbool.h>
//includes atoi
#include <stdlib.h>
int main( int argc, const char* argv[] )
{
	if(argc < 3 || argc > 4) {
		//wraps a syscall (writing to /dev/stdout)
		printf("Invalid usage. Supported options: \n\
				-n do Not overwrite existing file\n\
				-p Prompt before overwriting. Trumps -n.\n");
		return -1;
	}
	int names_begin_index = 1;
	bool overwrite = true;
	bool prompt = false;
	if(argc == 4) {
		// 1'st argument is options
		names_begin_index = 2;
		const char* options = argv[1];
		char* loc_of_n = strchr(options, 'n');
		if(loc_of_n != NULL)
			overwrite = false;
		char* loc_of_p = strchr(options, 'p');
		if(loc_of_p != NULL)
			prompt = true;

	}
	// SYSCALL: open a file by path for reading.
	// returns a file descriptor known to the kernel and related to file
	// third parameter is a OR'd list of parameters. We want read-only.
	int src_file_desc = open(argv[names_begin_index], O_RDONLY);
	// in case of error, errno has been set.
	if(errno!=0) {
		if(errno==ENOENT)
			printf("File does not exist\n");
		else if(errno==EACCES)
			printf("Permission denied\n");
		return -1;
	}
	// Must copy over file permissions (so that the user can read the file he just copied)
	// first declare a struct. Its data is random bytes.
	struct stat st;
	// SYSCALL: gets file info. fstat uses the file descriptor. Normal stat could use the path.
	// & can be read as "address of" and changes a TYPE to *TYPE (a pointer to that type).
	// fstat needs this pointer and will dereference it and write to that memory.
	// (that's why we declared st above and did not care what memory it had.)
	// fstat returns the status of the operation. 
	// I don't care about it because if there would be an error, we've already encountered it.
	fstat(src_file_desc, &st);
	// Test for file existence to prompt user
	if(prompt) {
		const char* filename = argv[names_begin_index+1];
		int exists = access(filename, F_OK);
		if(exists==0) {
			printf("%s exists. Overwrite? ", filename);
			char choice;
			// SYSCALL: shorthand for reading from the file /dev/stdin.
			// Read the file (/dev/stdin), parse for format string, and put the things in the memory specified by remaining parameters.
			scanf("%c", &choice);
			if(choice=='y')
				overwrite = true;
			else if (choice=='n')
				overwrite = false;
		}
	}
	// Construct flag for next open command. These flags are declared in fcntl.h.
	int oflag;
	if(overwrite) oflag = O_WRONLY | O_CREAT;
	else oflag = O_WRONLY | O_CREAT | O_EXCL;
	// SYSCALL: open the output file. now using the write-only flag and optionally ok-to-create flags.
	// In the case that we're making a new file, open uses the third parameter to create the
	// 	file access permissions.
	// Note that the type declared is mode_t, and st is a struct of type stat. 
	// stat contains a member value st_mode of type mode_t. 
	// . will access the member of that struct (semantically similar to Java's object property access)
	// Contrast with C/C++'s -> operator (dereference and access member), which is the proper analog of Java's object property access.
	int dest_file_desc = open(argv[names_begin_index+1], oflag, st.st_mode);
	// handle errors
	if(errno!=0) {
		if(errno==EACCES)
			printf("Permission denied\n");
		if(errno==EEXIST) 
			printf("Output file already exists and not overwriting. Aborting\n");
		return -1;
	}
	// we're ok, start copying
	// need a block of memory as a buffer. Call it a char because char is 1 byte.
	// Technically buff is a pointer to the memory that represents the array.
	// This pointer's type is *char.
	char buff[20];
	int num_read;
	int tot_read=0;
	int cursor_index = 0;
	int total_size = st.st_size;
	// prepare progress bar
	// 20 ~
	printf("[~~~~~~~~~~~~~~~~~~~~]");
	// move cursor to start
	printf("\r");
	// move cursor right, past [
	fflush(stdout);
	printf("\033[C");
	do {
		// SYSCALL: copies 3rd param bytes from file referenced by descriptor into memory described by buff
		// Remember that buff is a pointer, and the type of the second parameter here is void*. 
		// A void pointer means the method doesn't care what type of pointer it is.
		// The method would have to cast the pointer before dereferencing it.
		// However, the method likely never dereferences it because it only cares where the memory is (which is literally what a pointer is: an address of memory).
		num_read = read(src_file_desc, buff, sizeof(buff));
		// ^ SYSCALL: copies 3rd param bytes from memory pointed to by buff and into file described by 1st param.
		tot_read += num_read;
		double frac_read = (double) tot_read / total_size;
		if((frac_read*20)>cursor_index) {
			printf("#");
			fflush(stdout);
			cursor_index++;
		}
		write(dest_file_desc, buff, num_read);
		
		// Note that read() does not read past EOF, and does not advace past EOF. 
		// So a read further than EOF will result in 0 bytes read.
	} while (num_read != 0);
	printf("\033[D\n");
	// SYSCALL: closes files
	close(src_file_desc);
	close(dest_file_desc);
	return 0;
}
