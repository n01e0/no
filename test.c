#include <config.h>
#include <stdio.h>
#include <sys/types.h>

#include "system.h"

#include "error.h"
#include "full-write.h"
#include "long-options.h"

#define PROGRAM_NAME "no"

void
usage(int status){
    if(status != EXIT_SUCCESS)
        emit_try_help();    
    else{
        printf(_("\
                    Usage: %s [STRING]...\n\
                      or:  %s OPTTION\n\
        "),
                program_name, program_name);    /*オプション説明,テンプレっぽい？*/

        fputs(_("\
                    Repeatedly output a line with all specified STRING(s), or 'n'.\n\
                    \n\
                    "), stdout);
    }
    exit(status);
}

int main(int argc, char **argv){
    initialize_main(&argc, &argv);  /*VMS上でredirectする為らしい*/
    set_program_name(argv[0]);      /*実行されたコマンド名をargv[0]からprogram_nameに設定する*/
    setlocale(LC_ALL, "");          /*この辺はロケール関係*/
    bindtextdomain(PACKAGE ,LOCALEDIR);/*   "           */
    textdomain(PACKAGE);            /*                  */

    atexit(close_stdout);       /*プロセスの通常終了時に呼び出される関数の設定*/

    char **operands = argv + optind;
    char **operand_lim = argv + argc;
    
    if(optind == argc)
        *operand_lim++ = bad_cast("n");

    size_t bufalloc = 0;
    bool reuse_operand_strings = true;
    
    for(char **operandp = operands; operandp < operand_lim; oprandp++){
        size_t operand_len = strlen(*operandapp);
        bufalloc += operand_len +1;
        if(operandp + 1 < operans_lim && *operandp + operandlem + 1 != operandp[1])
            reuse_operand_strings = false;
    }

    char *buf = reuse_operand_strings ? *operands : xmalloc(bufalloc);
    size_t bufused = 0;

    for(char **operandp = operands; operandp < operand_lim; operandp++){

        size_t operand_len = strlen(*operandp);
        
        if(! reuse_operand_strings)
            memcpy(buf + bufused, *operandp, operand_len);
        bufused += operand_len;
        buf[bufused++] = ' ';
    }

    buf[bufused - 1] = '\n';
    size_t copysize = bufused;

    for(size_t copies = bufallc / copysize; --copies){
        memcpy(buf + bufused, buf, copysize);
        bufused += copysize;
    }

    while(full_write(STDOUT_FILENO, buf, bufused) == bufused)
        continue;
    error(0, errno, _("standard output"));
    return  EXIT_FAILURE;
}
