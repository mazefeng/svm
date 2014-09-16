#include <iostream>
#include <fstream>
#include <strstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <cmath>
#include <cstdlib>
#include <unistd.h>
#include <string.h>
#include "smo.h"

using namespace std;

#ifndef __VC_SVM_COMMON__
#define __VC_SVM_COMMON__

int split(const string& s, char c, vector<string>& v);
bool cmp(const pair<int, float>& p1, const pair<int, float>& p2);

int read_sample(string& s, sparse_vector& x, float& y);
int write_sample(string& s, sparse_vector& x, float& y);
int batch_read_sample(ifstream& is, vector<sparse_vector>& X, vector<float>& Y, int& n);
int batch_write_sample(ofstream& os, vector<sparse_vector>& X, vector<float>& Y, int& n);

float dot_product(const sparse_vector& v1, const sparse_vector& v2);
sparse_vector operator*(const sparse_vector& v, float f);
sparse_vector operator*(float f, const sparse_vector& v);
sparse_vector operator+(const sparse_vector& v1, const sparse_vector& v2);
void print_sparse_vector(const sparse_vector& v);

#endif
