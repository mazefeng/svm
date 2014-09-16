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
#include <iomanip>

using namespace std;

#ifndef __VC_SVM_SMO__
#define __VC_SVM_SMO__

typedef vector<pair<int, float> > sparse_vector;

class svm_option{
public:
    svm_option();
public:
    float C;
    float tol;
    float eps;
    float sigma;
    bool is_linear_kernel;
    const char *train_path;
    const char *test_path;
    const char *model_path;
    const char *output_path;
};

class SMO{
public:
    SMO(svm_option *opt);
    int train();
    int predict();

protected:

    float error_rate();

    int load_model(ifstream& is);
    int dump_model(ofstream& os);
    
    float kernel(int i1, int i2);
    float learned_func(int k);

    int examine_example(int i1);
    int take_step(int i1, int i2);

protected:

    // input options
    float C;
    float tol;
    float eps;
    float sigma;
    bool is_linear_kernel;
    const char *train_path;
    const char *test_path;
    const char *model_path;
    const char *output_path; 
    
    // internal options 
    int n, n_sv;
    vector<sparse_vector> X;
    vector<float> Y;
    sparse_vector w;

    vector<float> alpha;
    vector<float> D;
    vector<float> error_cache;
    float b, delta_b;
    
};


#endif
