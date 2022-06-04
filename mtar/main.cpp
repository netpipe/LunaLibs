#define COMPRESS

#include "./mtar.h"

extern "C"{
bool extractTar(char);

}

int main(){

extractTar("./pydata.tar");


system("pause");
}
