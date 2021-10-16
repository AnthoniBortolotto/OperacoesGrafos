#pragma once

#include <vector>
#include <iostream>
#include "string.h"

using namespace std;

class Aresta
{
public:

    Aresta(int peso, int origem, int destino);
    ~Aresta();
    int peso;
    int origem;
    int destino;
    /*Aresta();*/

private:

};

