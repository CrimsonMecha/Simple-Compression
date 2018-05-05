#include<stdlib.h>
#include<stdio.h>
#include<string.h>

void btoa(FILE *ifp, FILE *ofp){
	fseek(ifp, 0L, SEEK_END);
    unsigned size = ftell(ifp);
    fseek(ifp, 0L, SEEK_SET);
    char * input = (char *)malloc(size * sizeof(char));
    fread(input, sizeof(char), size, ifp);
	char * output = (char *)malloc((size/8)+1 * sizeof(char));
	output[0] = '\0';

	//manufacture a character
	for (unsigned i = 0; i < size; i += 8){
		char tmp;
		int newChar = 0;
		if (input[i] == '1'){
			newChar += 128;
		} 
		if (input[i+1] == '1'){
			newChar += 64;
		}
		if (input[i+2] == '1'){
			newChar += 32;
		}
		if (input[i+3] == '1'){
			newChar += 16;
		}
		if (input[i+4] == '1'){
			newChar += 8;
		}
		if (input[i+5] == '1'){
			newChar += 4;
		}
		if (input[i+6] == '1'){
			newChar += 2;
		}
		if (input[i+7] == '1'){
			newChar += 1;
		}
		strcat(output, (char*)&newChar);
			
	}
	fprintf(ofp, "%s", output);


}


int main(int argc, char **argv){
	if (argc != 3){
		fprintf(stderr, "Usage: ./btoa <input> <output>\n");
		return -1;
	}
	FILE *ifp = fopen(argv[1], "r");
	FILE *ofp = fopen(argv[2], "w");

	btoa(ifp, ofp);

	fclose(ifp);
	fclose(ofp);


	return 0;
}
