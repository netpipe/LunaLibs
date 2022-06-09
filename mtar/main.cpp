#define COMPRESS

#include "microtar/src/microtar.h"
#include "microtar/src/microtar-stdio.h"

#include "./mtar.h"


extern "C"{
bool extractTar(char);
void list_files();
}

int main(){

extractTar("./test.tar");
//list_files("./test.tar");

system("pause");
}
