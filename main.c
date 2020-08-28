
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct options_tag_t options_t;
typedef struct mimeinfo_tag_t mimeinfo_t;

/* {"text.plain", "text file", "text/plain", 0, NULL, 4, "\0\1\2\3"}, */

struct mimeinfo_tag_t
{
    /* ident for this type. defaults to "application.octet_stream" */
    const char* sident;

    /* mime name. defaults to "data" */
    const char* sname;

    /* mime type. defaults to "application/octet-stream" */
    const char* smime;

    /* offset at which to start looking for $matchbytes. defaults to 0 */
    size_t mbstart;

    /* array of bytes to match. can be NULL */
    size_t mblength;
    const char* matchbytes;


    /* array of "forbidden" bytes - the opposite of $matchbytes. */
    size_t nolength;
    const char* noneofbytes;
};

struct options_tag_t
{
    const char* argv0;
    bool prefixfilename;
    bool wantmime;
    size_t headsize;
};

#include "types.h"

static void init_options(options_t* opts)
{
    opts->prefixfilename = true;
    opts->wantmime = false;
    opts->headsize = 255;
}

static void init_mime(mimeinfo_t* dest)
{
    dest->sident = "application.octet_stream";
    dest->sname = "data";
    dest->smime = "application/octet-stream";
    dest->mbstart = 0;
    dest->matchbytes = NULL;
    dest->mblength = 0;
    dest->noneofbytes = NULL;
    dest->nolength = 0;
}

static bool does_matchbytes(const char* head, size_t headsize, const mimeinfo_t* mi)
{
    size_t i;
    for(i=0; (i < mi->mblength) && (i < headsize); i++)
    {
        if(head[i] != mi->matchbytes[i])
        {
            return false;
        }
    }
    return true;
}

static mimeinfo_t* find_mime(options_t* opts, FILE* infh)
{
    int ch;
    size_t i;
    size_t headsz;
    char* head;
    mimeinfo_t* rt;
    headsz = 0;
    head = (char*)malloc(opts->headsize + 1);
    while(headsz < opts->headsize)
    {
        ch = fgetc(infh);
        if(ch == -1)
        {
            break;
        }
        head[headsz] = ch;
        headsz++;
    }
    for(i=0; (rt = &knowntypes[i])->sident != NULL; i++)
    {
        if(rt->matchbytes != NULL)
        {
            if(does_matchbytes(head, headsz, rt))
            {
                return rt;
            }
        }
    }
    return NULL;
}

static void print_results(options_t* opts, const char* file, mimeinfo_t* inf)
{
    if(opts->prefixfilename)
    {
        printf("%s: ", file);
    }
    printf("%s\n", (opts->wantmime ? inf->smime : inf->sname));
}

static bool do_file(options_t* opts, const char* file)
{
    FILE* fh;
    mimeinfo_t* rt;
    mimeinfo_t definf;
    if((fh = fopen(file, "rb")) == NULL)
    {
        fprintf(stderr, "qfile: cannot open '%s' for reading\n", file);
        return false;
    }
    init_mime(&definf);
    if((rt = find_mime(opts, fh)) != NULL)
    {
        print_results(opts, file, rt);
        return true;
    }
    print_results(opts, file, &definf);
    return false;
}

static void do_help(options_t* opts)
{
    printf(
        "usage: %s [<options>] <file ...>\n"
        "supported options:\n"
        "  -h    show this help and exit\n"
        "  -i    print mime type, instead of name\n"
        "\n"
    , opts->argv0);
}

static void do_flag(options_t* opts, const char* arg)
{
    int i;
    int flag;
    for(i=1; arg[i]!=0; i++)
    {
        flag = arg[i];
        switch(flag)
        {
            case 'h':
                do_help(opts);
                exit(0);
                break;
            case 'i':
                opts->wantmime = true;
                break;
            case 'f':
                opts->prefixfilename = false;
                break;
            default:
                fprintf(stderr, "qfile: unknown option '-%c'\n", flag);
                exit(1);
                break;
        }
    }
}

int main(int argc, char* argv[])
{
    int i;
    int rc;
    const char* arg;
    options_t opts;
    init_options(&opts);
    opts.argv0 = argv[0];
    rc = 0;
    if(argc > 1)
    {
        for(i=1; i<argc; i++)
        {
            arg = argv[i];
            if(arg[0] == '-')
            {
                do_flag(&opts, arg);
            }
            else
            {
                rc += do_file(&opts, arg);
            }
        }
    }
    else
    {
        fprintf(stderr, "qfile: too few arguments. try '%s -h'\n", opts.argv0);
        return 1;
    }
    return ((rc > 0) ? 1 : 0);
}
