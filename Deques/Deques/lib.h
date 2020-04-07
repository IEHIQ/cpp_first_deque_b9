#pragma once
#include "pch.h"
#include <cstdlib>
#include <random>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <fstream>
#include <deque>

using namespace std;

enum OPERATION_TYPE { CYCLE, TRANSFORM, FOREACH };

fstream file_fill(int M, int N, bool use_cycle, const char* filename);

deque<int> file_to_deque(const char* filename);

void modify(deque<int> &container, OPERATION_TYPE op_type);

void modify(deque<int> &container, deque<int>::iterator begin, deque<int>::iterator end, OPERATION_TYPE op_type);

int sum(deque<int> &container);

float average(deque<int> &container);

void output(deque<int> &container);

void output(deque<int> &container, const char* filename);