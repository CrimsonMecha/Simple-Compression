#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

char * itob(int index);

typedef struct Table {
    
    char *str;
    struct Table *one;
    struct Table *zero;
    int idx;

} Table;

Table *make_table( char* s, int index ){
	Table *ptr;
	
	ptr = (Table *)malloc( sizeof(Table) );
	assert( ptr != NULL );
	ptr->str = strdup( s );
	ptr->one = NULL;
	ptr->zero = NULL;
    ptr->idx = index;

	return ptr;
}

Table *search_tree( char *input, Table *table ){
    if (strlen(input) <= 1){
        return table;
    }
    if (*input == '1'){
        if (table -> one != NULL){
            return search_tree(++input, table->one);
        } else {
            return table;
        }
    } else {
        if (table -> zero != NULL){
            return search_tree(++input, table -> zero);
        } else {
            return table;
        }
    }
}

char *binary_index(int index, int bits){
    char *str = (char*)malloc(bits * sizeof(char));
    str[0] = '\0';
    char *buf;
    
    buf = itob(index);
    
    //add in extra zeros
    int num_zeros = bits - strlen(buf);
    for(int i = 0; i<num_zeros; ++i){
        strcat(str, "0");
    }
    strcat(str, buf);
    free(buf);

    return str;
}

void jabber( FILE *ifp, FILE *ofp ){

    int bits = 0;
    int index = 0;

    Table * table = make_table("", index);

    fseek(ifp, 0L, SEEK_END);
	int size = ftell(ifp) - 1;
	fseek(ifp, 0L, SEEK_SET);
	char * input = (char *)malloc(size * sizeof(char));
	fread(input, sizeof(char), size, ifp);

    for (int i = 0; i < size;){
        printf("i: %d\nbits: %d\n", i, bits);
        Table *curr_node = search_tree(input + i, table);
        printf("curr_node->str: %s\n", curr_node->str);
        char *idx_str = binary_index(curr_node->idx, bits);
        printf("idx_str: %s\n", idx_str);
        char *jab_str = (char*)malloc((strlen(idx_str) + 1) * sizeof(char));
        char *table_str = (char*)malloc((strlen(curr_node->str) + 1) * sizeof(char));
        
        jab_str[0] = '\0';
        strcat(jab_str, idx_str);        
        if (strlen(input + i + strlen(curr_node -> str)) > 0){
            // if (!strcmp(curr_node->str, "")){
                // jab_str[strlen(idx_str)] = *(input + i);
               
            // } else {
        
                if (i + strlen(curr_node->str) + 1 < size ){
                    if (*(input + i + strlen(curr_node->str)) == '1'){
                        strcat(jab_str, "1");
                        printf("bad 1\n");
                    } else {
                        strcat(jab_str, "0");
                        printf("bad 0\n");
                    }
                } 
            // }
        }
        
        
        fprintf(ofp, "%s", jab_str);
        printf("jabber: %s\n", jab_str);
        free(jab_str);

        table_str[0] = '\0';
        strcat(table_str, curr_node->str);
        if (strlen(input + i + strlen(curr_node -> str)) > 0){
            // if (!strcmp(curr_node->str, "")){
                // table_str[0] = *(input + i);
                // printf("carry: %c\n", *(input + i));    
                // table_str[0] = *(input + i + 1);
                // table_str[1] = '\0';
            // } else {    
                printf("carry: %c\n", *(input + strlen(curr_node -> str) + i)); 
                // table_str[strlen(idx_str)] = *(input + i + strlen(curr_node->str));
                if (*(input + strlen(curr_node -> str) + i) == '1'){
                    strcat(table_str, "1");
                    printf("no 1\n");
                } else {
                    printf("no 0\n");
                    strcat(table_str, "0");
                }
               
                
            // }
            printf("table str: %s\n", table_str);
        }
        
        
        if (*(input + i + strlen(curr_node->str)) == '1'){
            curr_node -> one = make_table(table_str, ++index);
        } else {
            curr_node -> zero = make_table(table_str, ++index);
        }
        
        free(table_str);
        
        if(pow(2, bits) - 1 < index){
            bits++;
        }

        i += strlen(curr_node->str)+1;
        
        
    }
    fprintf(ofp, "\n");
}

int main(int argc, char **argv){

    if (argc != 3){
		fprintf(stderr, "usage: ./jabber <input> <output>\n");
		return -1;
	}
	FILE *ifp = fopen(argv[1], "r");
	FILE *ofp = fopen(argv[2], "w");
	jabber(ifp, ofp);

	fclose(ifp);
	fclose(ofp);

    return 0;
}

char * itob(int index){
    char *input = calloc(32, sizeof(char));
    sprintf(input, "%d", index);
    int size = strlen(input);
	for (int i = 0; i < size; ++i){
		input[i] -= '0';
    }
    char * output = (char *)malloc(size * 8 * sizeof(char));
	output[0] = '\0';

	//convert
	for (unsigned i = 0; i < size; i++){
		char tmp[9];
		tmp[0] = '\0';
		if (index > 127){
			if (input[i] > 127){
				strcat(tmp, "1");
				input[i] -= 128;
			} else {
				strcat(tmp, "0");
			}
		}

		if (index > 63){
			if (input[i] > 63){
				strcat(tmp, "1");
				input[i] -= 64;
			} else {
				strcat(tmp, "0");
			}
		}

		if (index > 31){
			if (input[i] > 31){
				strcat(tmp, "1");
				input[i] -= 32;
			} else {
				strcat(tmp, "0");
			}
		}

		if (index > 15){
			if (input[i] > 15 && index > 15){
				strcat(tmp, "1");
				input[i] -= 16;
			} else {
				strcat(tmp, "0");
			}
		}

		if (index > 7){
			if (input[i] > 7){
				strcat(tmp, "1");
				input[i] -= 8;
			} else {
				strcat(tmp, "0");
			}
		}

		if (index > 3){
			if (input[i] > 3){
				strcat(tmp, "1");
				input[i] -= 4;
			} else {
				strcat(tmp, "0");
			}
		}

		if (index > 1){
			if (input[i] > 1){
				strcat(tmp, "1");
				input[i] -= 2;
			} else {
				strcat(tmp, "0");
			}
		}

		if (index >= 1){
			if (input[i] == 1){
				strcat(tmp, "1");
			} else {
				strcat(tmp, "0");
			}
		}

		strncat(output, tmp, 8);

	}

	return output;
}
