#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <fstream>


void Usage(char *filename) {
	printf("Usage: %s <file> <string>\n", filename);
}



int Search_in_File(char *fname) {
	char temp[1024 * 1024];

	std::ifstream in(fname, std::ios::in | std::ios::binary);

        int buffer_size = 1;
        char buffer[buffer_size];
	int i = 0;
        while(in)
        {
                in.read (buffer, buffer_size);
                if(in)
                {
                       // printf("%s", buffer);
			if (buffer[0] != 0)
				temp[i++] = buffer[0];
			else
				temp[i++] = ' ';
                }
        }
        in.close();
	//printf("\n%s\n", temp);

	if((strstr(temp, "UPX!")) != NULL)
	{
		printf("UPX Found in binary\n");
	}
	else
	{
		printf("UPX not found in binary\n");
	}
	if((strstr(temp, "rsrc")) != NULL)
        {
	        printf("rsrc Found in binary\n");
	}
	printf("finished searching file\n");
	//printf("\n%s\n", temp);
	return 0;
}

int main(int argc, char *argv[]) {
	int result, errno;

	if(argc < 2 || argc > 2) {
		Usage(argv[0]);
		exit(1);
	}

	system("clear");

	result = Search_in_File(argv[1]);
	if(result == -1) {
		perror("Error");
		printf("Error number = %d\n", errno);
		exit(1);
	}
	return(0);
}
