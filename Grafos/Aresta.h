#pragma once

#include <vector>
#include <iostream>
#include "string.h"

using namespace std;

class Aresta
{
public:

    Aresta(int peso, string origem, string destino);
    ~Aresta();
    int peso;
    string origem;
    string destino;
    /*Aresta();*/

private:

};

