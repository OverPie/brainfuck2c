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

void run(char *s, FILE *f) {
		int i = 0;
		while(s[i]) {
				if(s[i] == '>') {
						fputs("i++;", f);
				} else if(s[i] == '<') {
						fputs("i--;", f);
				} else if(s[i] == '+') {
						fputs("arr[i]++;", f);
				} else if(s[i] == '-') {
						fputs("arr[i]--;", f);
				} else if(s[i] == '.') {
						fputs("putchar(arr[i]);", f);
				} else if(s[i] == ',') {
						fputs("arr[i] = getchar();", f);
				} else if(s[i] == '[') {
						fputs("while(arr[i]) {", f);
				} else if(s[i] == ']') {
						fputs("}", f);
				}

				i++;
		}
}

int main(int argc, char *argv[]) {
		if(argc == 1) error("filename missing");
		FILE *f = fopen(argv[1], "r");
		if(!f) error("no such file");
		FILE *ef = fopen("tmp.c", "w");
		char *code = readfile(f);

		fputs("#include <stdio.h>\n#include <string.h>\nint main(){int i = 0;char arr[30000];memset(arr, 0, sizeof(arr));", ef);
		run(code, ef);
		fputs("return 0;}", ef);

		free(code);
		fclose(f);
		fclose(ef);
		system("gcc tmp.c -o bf");
		remove("tmp.c");
		return 0;
}
