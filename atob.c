#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void atob(FILE *ifp, FILE * ofp){
	fseek(ifp, 0L, SEEK_END);
	unsigned size = ftell(ifp);
	fseek(ifp, 0L, SEEK_SET);
	char * input = (char *)malloc(size * sizeof(char));
	fread(input, sizeof(char), size, ifp);
	char * output = (char *)malloc(size * 8 * sizeof(char));
	output[0] = '\0';

	//convert
	for (unsigned i = 0; i < size; i++){
		char tmp[9];
		tmp[0] = '\0';
		if (input[i] > 127){
			strcat(tmp, "1");
			input[i] -= 128;
		} else {
			strcat(tmp, "0");
		}

		if (input[i] > 63){
			strcat(tmp, "1");
			input[i] -= 64;
		} else {
			strcat(tmp, "0");
		}

		if (input[i] > 31){
			strcat(tmp, "1");
			input[i] -= 32;
		} else {
			strcat(tmp, "0");
		}

		if (input[i] > 15){
			strcat(tmp, "1");
			input[i] -= 16;
		} else {
			strcat(tmp, "0");
		}

		if (input[i] > 7){
			strcat(tmp, "1");
			input[i] -= 8;
		} else {
			strcat(tmp, "0");
		}

		if (input[i] > 3){
			strcat(tmp, "1");
			input[i] -= 4;
		} else {
			strcat(tmp, "0");
		}

		if (input[i] > 1){
			strcat(tmp, "1");
			input[i] -= 2;
		} else {
			strcat(tmp, "0");
		}
		if (input[i] == 1){
			strcat(tmp, "1");
		} else {
			strcat(tmp, "0");
		}

		strncat(output, tmp, 8);

	}

	fprintf(ofp, "%s", output);
}



int main(int argc, char ** argv){
	if (argc != 3){
		fprintf(stderr, "usage: ./atob <input> <output>\n");
		return -1;
	}
	FILE *ifp = fopen(argv[1], "r");
	FILE *ofp = fopen(argv[2], "w");
	atob(ifp, ofp);

	fclose(ifp);
	fclose(ofp);

	return 0;
}
