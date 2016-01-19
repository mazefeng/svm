/**
 *******************************************************************************
 *
 * Copyright (c) 2015 Baidu.com, Inc. All Rights Reserved
 *
 *******************************************************************************
 * 
 * @file: main.cpp
 * @author: mazefeng(mazefeng01@baidu.com)
 * @date: 2015/06/30 11:10:00
 *
 */

#include "svm_common.h"
#include "svm_option.h"
#include "svm_solver.h"

const int RET_OK = 0;
const int RET_SVM_OPTION_ERR = 1;
const int RET_SVM_SOLVER_ERR = 2;

using std::cerr;
using std::endl;

void help(){
    cerr << "Usage: light-svm -train ${train} -model ${model} " 
         << "-valid ${valid} [-linear_kernel] [-C ${cost}] " 
         << "[-epsilon ${eps}] [-sigma ${sig}] [-help]"
    << endl;
}

int main(int argc, char *argv[]){

    int ret = RET_OK;

    SVMOption *option = new SVMOption();
    ret = option->parse_command_line(argc, argv);
    if (ret != 0){
        help();
        return RET_SVM_OPTION_ERR;
    }

    option->print();
    
    SVMSolver *solver = new SVMSolver(option);
    
    solver->train();
    solver->predict();
}

