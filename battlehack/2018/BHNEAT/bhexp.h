#pragma once

#include "experiments.h"
#include "bhexp.h"
#include <cstring>
#include <vector>

#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>

#include <string>
#include <sstream>
#include <map>
#include <iomanip>
#include <chrono>
#include <thread>
#include <mutex>

//#define NO_SCREEN_OUT 

Population *bh_test (int gens);
int bh_epoch (Population *pop, int generation, char *filename, int &winnernum, int &winnergenes, int &winnernodes);

string IntToString (int i);
std::string exec (const char* cmd);
void RunBot (string loc);