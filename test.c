#include <stdio.h>
#include <string.h>

#define PROGRAM_NAME "no"

void
usage(int status){
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
    extern const char *program_name;
    //extern void set_program_name (const char *argv0);

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

    if(bufalloc <= BUFSIZ / 2){
        bufalloc = BUFSIZ;
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
