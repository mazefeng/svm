
#include <svm_solver.h>
#include <gtest/gtest.h>
	
	
int main(int argc, char **argv)
{
 	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
/**
 * @brief 
**/
class test_SVMSolver_SVMSolver_suite : public ::testing::Test{
    protected:
        test_SVMSolver_SVMSolver_suite(){};
        virtual ~test_SVMSolver_SVMSolver_suite(){};
        virtual void SetUp() {
            //Called befor every TEST_F(test_SVMSolver_SVMSolver_suite, *)
        };
        virtual void TearDown() {
            //Called after every TEST_F(test_SVMSolver_SVMSolver_suite, *)
        };
};
 
/**
 * @brief 
 * @begin_version 
**/
TEST_F(test_SVMSolver_SVMSolver_suite, case_name1)
{
	//TODO
}
 
/**
 * @brief 
**/
class test_SVMSolver_train_suite : public ::testing::Test{
    protected:
        test_SVMSolver_train_suite(){};
        virtual ~test_SVMSolver_train_suite(){};
        virtual void SetUp() {
            //Called befor every TEST_F(test_SVMSolver_train_suite, *)
        };
        virtual void TearDown() {
            //Called after every TEST_F(test_SVMSolver_train_suite, *)
        };
        SVMOption *option;
        SVMSolver *solver;
};
 
/**
 * @brief 
 * @begin_version 
**/
TEST_F(test_SVMSolver_train_suite, case_train)
{
    option = new SVMOption();
    strcpy(option->_fname_train, "data/heart_scale.train");
    strcpy(option->_fname_model, "data/heart_scale.model.unittest");
    solver = new SVMSolver(option);
    int ret = solver->train();
    ASSERT_EQ(0, ret);
    delete solver;
    delete option;
    
}
 
/**
 * @brief 
**/
class test_SVMSolver_predict_suite : public ::testing::Test{
    protected:
        test_SVMSolver_predict_suite(){};
        virtual ~test_SVMSolver_predict_suite(){};
        virtual void SetUp() {
            //Called befor every TEST_F(test_SVMSolver_predict_suite, *)
        };
        virtual void TearDown() {
            //Called after every TEST_F(test_SVMSolver_predict_suite, *)
        };
        SVMOption *option;
        SVMSolver *solver;
};
 
/**
 * @brief 
 * @begin_version 
**/
TEST_F(test_SVMSolver_predict_suite, case_name1)
{
    option = new SVMOption();
    strcpy(option->_fname_valid, "data/heart_scale.test");
    strcpy(option->_fname_model, "data/heart_scale.model");
    solver = new SVMSolver(option);
    int ret = solver->predict();
    ASSERT_EQ(0, ret);
    delete solver;
    delete option;
}
 
