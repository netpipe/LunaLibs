#define COMPRESS

#include "microtar/src/microtar.h"
#include "microtar/src/microtar-stdio.h"

#include "./mtar.h"


extern "C"{
bool extractTar(char);

}

int main(){

extractTar("./microtar2.tar");


system("pause");
}
