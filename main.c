#include <stdio.h>
#include <stdlib.h>

void error(char *s) {
		fprintf(stderr, "%s", s);
		exit(1);
}
char * readfile(FILE *f) {
	fseek(f, 0L, SEEK_END);
	int size = ftell(f);
	fseek(f, 0L, SEEK_SET);
	char *ret = malloc(size);
	fread(ret, 1, size, f);
	return ret;
}

void write(FILE *f, size_t j, char operator) {
	switch(operator) {
		case '>':
			fprintf(f, "i+=%zu;", j);
		break;
		case '<':
			fprintf(f, "i-=%zu;", j);
		break;
		case '+':
			fprintf(f, "arr[i]+=%zu;", j);
		break;
		case '-':
			fprintf(f, "arr[i]-=%zu;", j);
		break;
		case '.':
			for(size_t i = 0; i < j; i++)
				fprintf(f, "putchar(arr[i]);");
		break;
		case ',':
			for(size_t i = 0; i < j; i++)
				fprintf(f, "arr[i] = getchar();");
		break;
		case '[':
			for(size_t i = 0; i < j; i++)
				fprintf(f, "while(arr[i]) {");
		break;
		case ']':
			for(size_t i = 0; i < j; i++)
				fprintf(f, "}");
	}
}

void run(char *s, FILE *f) {
		size_t i = 0;
		char operator = '\0';

		size_t j = 0;

		while(s[i]) {
			if(s[i] != operator) {
				write(f, j, operator);

				j = 0;

				//i++;
			}

			operator = s[i];

			i++;
			j++;
		}
}

int main(int argc, char *argv[]) {
		if(argc < 3) {
			printf("usage: %s <brainfuck source> <output file>\n", argv[0]);

			exit(1);
		}

		FILE *f = fopen(argv[1], "r");
		if(!f) error("no such file");
		FILE *ef = fopen(argv[2], "w");
		char *code = readfile(f);

		fputs("#include <stdio.h>\n#include <string.h>\nint main(){int i = 0;char arr[30000];memset(arr, 0, sizeof(arr));", ef);
		run(code, ef);
		fputs("return 0;}", ef);

		free(code);
		fclose(f);
		fclose(ef);
		return 0;
}
