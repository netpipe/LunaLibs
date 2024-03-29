/*
 * Copyright (c) 2021 Aidan MacDonald
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */
//#include "../../config.h"
#ifdef COMPRESS
#include "./microtar/src/microtar-stdio.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

/* exit codes */
#define E_TAR   1
#define E_FS    2
#define E_OTHER 4
#define E_ARGS  8

enum {
    OP_LIST,
    OP_CREATE,
    OP_EXTRACT,
};

void die(int err, const char* msg, ...)
{
    fprintf(stderr, "mtar: ");

    va_list ap;
    va_start(ap, msg);
    vfprintf(stderr, msg, ap);
    va_end(ap);

    fprintf(stderr, "\n");
    exit(err);
}

int list_foreach_cb(mtar_t* tar, const mtar_header_t* h, void* arg)
{
    (void)tar;
    (void)arg;
    printf("%s\n", h->name);
    return 0;
}

void list_files(mtar_t* tar)
{
    int err = mtar_foreach(tar, list_foreach_cb, NULL);
    if(err)
        die(E_TAR, "listing failed: %s", mtar_strerror(err));
}

struct extract_args {
    char** names;
    int count;
};

int dir_exists(const char* name)
{
    struct stat sb;
    if (stat(name, &sb) == 0 && (sb.st_mode& S_IFDIR) == S_IFDIR) 
    {
        return 1;
    }
    else {
        return 0;
    }
}

int make_dir_recursive(const char* name, int mode)
{
    mode=ACCESSPERMS;
    int result = 1;
    char* copy_name = strdup(name);
    char* last_slash = strrchr(copy_name, '/');
    if (last_slash)
    {
        *last_slash = 0;
        if (!make_dir_recursive(copy_name, mode))
            result = 0;    
    }

    if (result)
    {
#ifdef WIN32
        if (!dir_exists(name))
            if (mkdir(name) != 0)
                result = 0;
#else
        if (!dir_exists(name))
            if (mkdir(name, mode) != 0)
                result = 0;
#endif // WIN32
    }
    return result;
}

int extract_foreach_cb(mtar_t* tar, const mtar_header_t* h, void* arg)
{
    struct extract_args* args = (struct extract_args*)arg;
    (void)args; /* TODO */
    
    if(h->type == MTAR_TDIR) {
        if (!make_dir_recursive(h->name, h->mode))
            die(E_FS, "cannot create directory \"%s\"", h->name);
        return 0;
    }
    

    if(h->type != MTAR_TREG) {
        fprintf(stderr, "warning: not extracting unsupported type \"%s\"", h->name);
        return 0;
    }

    char* copy_name = strdup(h->name);
    char* last_slash = strrchr(copy_name, '/');
    if (last_slash)
    {
        *last_slash = 0;
        if (!make_dir_recursive(copy_name, h->mode))
            die(E_FS, "cannot create directory \"%s\"", h->name);
    }
    free(copy_name);

    int fd = open(h->name, O_CREAT|O_WRONLY|O_TRUNC, h->mode);
    if(fd < 0)
        die(E_FS, "extracting \"%s\" failed: %s", h->name, strerror(errno));

    char iobuf[1024];
    while(!mtar_eof_data(tar)) {
        int rcount = mtar_read_data(tar, iobuf, sizeof(iobuf));
        if(rcount < 0)
            die(E_TAR, "extracting \"%s\" failed: %s", h->name, mtar_strerror(rcount));

        int wcount = write(fd, iobuf, rcount);
        if(wcount != rcount)
            die(E_FS, "extracting \"%s\" failed: %s", h->name, strerror(errno));
    }

    close(fd);
    return 0;
}

//void extract_files(mtar_t* tar, char** files, int num_files)
//{
//    struct extract_args args;
//    args.names = files;
//    args.count = num_files;
//
//    int err = mtar_foreach(tar, extract_foreach_cb, &args);
//    if(err)
//        die(E_TAR, "extraction failed: %s", mtar_strerror(err));
//}

void extract_files2(mtar_t* tar, char* files, int num_files)
{
    struct extract_args args;
    args.names = &files;
    args.count = num_files;

    int err = mtar_foreach(tar, extract_foreach_cb, &args);
    if(err)
        die(E_TAR, "extraction failed: %s", mtar_strerror(err));
}


void add_files(mtar_t* tar, char** files, int num_files)
{
    for(int i = 0; i < num_files; ++i) {
        int fd = open(files[i], O_RDONLY);
        if(fd < 0)
            die(E_FS, "adding \"%s\" failed: %s", files[i], strerror(errno));

        off_t off = lseek(fd, 0, SEEK_END);
        if(off < 0)
            die(E_FS, "adding \"%s\" failed: %s", files[i], strerror(errno));

        unsigned filesize = off;
        lseek(fd, 0, SEEK_SET);

        int err = mtar_write_file_header(tar, files[i], filesize);
        if(err)
            die(E_TAR, "adding \"%s\" failed: %s", files[i], mtar_strerror(err));

        char iobuf[1024];
        while(1) {
            int rcount = read(fd, iobuf, sizeof(iobuf));
            if(rcount < 0)
                die(E_FS, "adding \"%s\" failed: %s", files[i], strerror(errno));
            if(rcount == 0)
                break;

            int wcount = mtar_write_data(tar, iobuf, rcount);
            if(wcount < 0)
                die(E_TAR, "adding \"%s\" failed: %s", files[i], mtar_strerror(wcount));
            if(wcount != rcount)
                die(E_TAR, "adding \"%s\" failed: write too short %d/%d", files[i], wcount, rcount);
        }

        close(fd);

        err = mtar_end_data(tar);
        if(err)
            die(E_TAR, "adding \"%s\" failed: %s", files[i], mtar_strerror(err));
    }
}

#include <stdlib.h>
#include <stdio.h>
#include <string>

extern bool extractTar(char * tarfile){
//string test=tarfile;
    mtar_t tar;
        const char* mode = "rb";
//    if(op == OP_CREATE)
  //      mode = "wb";
    int err = mtar_open(&tar, tarfile, mode);
    if(err)
        die(E_TAR, "can't open archive: %s", mtar_strerror(err));

        #if defined(WIN64) || defined(WIN32)
       // if (_wmkdir(filename.c_str(), mode) != 0)
//        _wmkdir((wchar_t*)"\\media") ;
//        _wmkdir((wchar_t*)"\\media\lib") ;
//        _wmkdir((wchar_t*)"../media/lib/python2.7") ;
//        _wmkdir((wchar_t*)"../media/lib/python2.7/compiler") ;
//        _wmkdir((wchar_t*)"../media/lib/python2.7/encodings") ;
//        _wmkdir((wchar_t*)"../media/lib/python2.7/importlib") ;
//        _wmkdir((wchar_t*)"../media/lib/python2.7/json");
//        _wmkdir((wchar_t*)"../media/lib/python2.7/logging");
//        _wmkdir((wchar_t*)"../media/lib/python2.7/plat-emscripten") ;
//        _wmkdir((wchar_t*)"../media/lib/python2.7/xml") ;
//        _wmkdir((wchar_t*)"../media/lib/python2.7/xml/sax") ;
//        _wmkdir((wchar_t*)"../media/lib/python2.7/xml/parsers") ;
//        _wmkdir((wchar_t*)"../media/lib/python2.7/xml/etree" ) ;
//        _wmkdir((wchar_t*)"../media/lib/python2.7/xml/dom" ) ;

//        _mkdir("../media") ;
        mkdir( "../media/lib") ;
        mkdir("../media/lib/python2.7") ;
        mkdir("../media/lib/python2.7/compiler") ;
        mkdir("../media/lib/python2.7/encodings") ;
        mkdir("../media/lib/python2.7/importlib") ;
        mkdir("../media/lib/python2.7/json");
        mkdir("../media/lib/python2.7/logging");
        mkdir("../media/lib/python2.7/plat-emscripten") ;
        mkdir("../media/lib/python2.7/xml") ;
        mkdir("../media/lib/python2.7/xml/sax") ;
        mkdir("../media/lib/python2.7/xml/parsers") ;
        mkdir("../media/lib/python2.7/xml/etree" ) ;
        mkdir("../media/lib/python2.7/xml/dom" ) ;
// _mkdir( "testtmp" );
        #else
        // if (mkdir(filename.c_str(), (u16)mode) != 0)
//        mkdir("../media/lib", 0775) ;
//        mkdir("../media/lib/python2.7", 0775) ;
//        mkdir("../media/lib/python2.7/compiler", 0775) ;
//        mkdir("../media/lib/python2.7/encodings", 0775) ;
//        mkdir("../media/lib/python2.7/importlib", 0775) ;
//        mkdir("../media/lib/python2.7/json", 0775);
//        mkdir("../media/lib/python2.7/logging", 0775);
//        mkdir("../media/lib/python2.7/plat-emscripten", 0775) ;
//        mkdir("../media/lib/python2.7/xml", 0775) ;
//        mkdir("../media/lib/python2.7/xml/sax", 0775) ;
//        mkdir("../media/lib/python2.7/xml/parsers", 0775) ;
//        mkdir("../media/lib/python2.7/xml/etree", 0775) ;
//        mkdir("../media/lib/python2.7/xml/dom", 0775) ;
        #endif

  extract_files2(&tar, tarfile, 1);

      err = mtar_close(&tar);
    if(err)
        die(E_TAR, "failed to close archive: %s", mtar_strerror(err));

}
//
//int main-non(int argc, char* argv[])
//{
//    ++argv, --argc;
//    if(argc == 0)
//        die(E_ARGS, "no input files");
//
//    if(!strcmp(*argv, "--help")) {
//        printf(
//"usage:\n"
//"  mtar list tar-file\n"
//"    List the members of the given tar archive, one filename per line.\n"
//"\n"
//"  mtar create tar-file members//    const char* mode = "rb";
//    if(op == OP_CREATE)
//        mode = "wb";...\n"
//"  mtar add tar-file members...\n"
//"    Create a new tar archive from the files listed on the command line.\n"
//"    WARNING: Any existing file at tar-file will be overwritten!\n"
//"\n"
//"  mtar extract tar-file [members...]\n"
//"    Extract the contents of the tar archive to the current directory.\n"
//"    If filenames are given, only the named members will be extracted.\n"
//"\n");
//        exit(E_ARGS);
//    }
//
//    int op;
//    if(!strcmp(*argv, "list"))
//        op = OP_LIST;
//    else if(!strcmp(*argv, "create"))
//        op = OP_CREATE;
//    else if(!strcmp(*argv, "extract"))
//        op = OP_EXTRACT;
//    else
//        die(E_ARGS, "invalid operation \"%s\"", *argv);
//    ++argv, --argc;
//
//    if(argc == 0)
//        die(E_ARGS, "missing archive name");
//    const char* archive_name = *argv;
//    ++argv, --argc;
//
//    if(op == OP_LIST && argc != 0)
//        die(E_ARGS, "excess arguments on command line");
//
//    const char* mode = "rb";
//    if(op == OP_CREATE)
//        mode = "wb";
//
//    mtar_t tar;
//    int err = mtar_open(&tar, archive_name, mode);
//    if(err)
//        die(E_TAR, "can't open archive: %s", mtar_strerror(err));
//
//    switch(op) {
//    case OP_LIST:
//        list_files(&tar);
//        break;
//
//    case OP_EXTRACT:
//        extract_files(&tar, argv, argc);
//        break;
//
//    case OP_CREATE:
//        add_files(&tar, argv, argc);
//        err = mtar_finalize(&tar);
//        if(err)
//            die(E_TAR, "failed to finalize archive: %s", mtar_strerror(err));
//        break;
//
//    default:
//        die(E_OTHER, "not implemented");
//        break;
//    }
//
//    err = mtar_close(&tar);
//    if(err)
//        die(E_TAR, "failed to close archive: %s", mtar_strerror(err));
//
//    return 0;
//}
#endif
