
#include <svm_option.h>
#include "svm_common.h"
#include <gtest/gtest.h>
	
	
int main(int argc, char **argv)
{
 	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
/**
 * @brief 
**/
class test_SVMOption_SVMOption_suite : public ::testing::Test{
    protected:
        test_SVMOption_SVMOption_suite(){};
        virtual ~test_SVMOption_SVMOption_suite(){};
        virtual void SetUp() {
            //Called befor every TEST_F(test_SVMOption_SVMOption_suite, *)
            option = new SVMOption();
        };
        virtual void TearDown() {
            //Called after every TEST_F(test_SVMOption_SVMOption_suite, *)
            delete option;
        };
        SVMOption *option;
};
 
/**
 * @brief 
 * @begin_version 
**/
TEST_F(test_SVMOption_SVMOption_suite, case_svm_option)
{
    ASSERT_TRUE(fabs(SVM_OPTION_C - option->_c) < 1e-6);  
    ASSERT_TRUE(fabs(SVM_OPTION_EPSILON - option->_eps) < 1e-6);
    ASSERT_TRUE(fabs(SVM_OPTION_SIGMA - option->_sig) < 1e-6); 
    ASSERT_TRUE(false == option->_is_linear_kernel);
    ASSERT_EQ(0, (int)strlen(option->_fname_train)); 
    ASSERT_EQ(0, (int)strlen(option->_fname_valid)); 
    ASSERT_EQ(0, (int)strlen(option->_fname_model)); 
}

/**
 * @brief 
**/
class test_SVMOption_parse_command_line_suite : public ::testing::Test{
    protected:
        test_SVMOption_parse_command_line_suite(){};
        virtual ~test_SVMOption_parse_command_line_suite(){};
        virtual void SetUp() {
            //Called befor every TEST_F(test_SVMOption_parse_command_line_suite, *)
            option = new SVMOption();
        };
        virtual void TearDown() {
            //Called after every TEST_F(test_SVMOption_parse_command_line_suite, *)
            delete option;
        };
        SVMOption *option;
};
 
/**
 * @brief 
 * @begin_version 
**/
TEST_F(test_SVMOption_parse_command_line_suite, case_parse_command_line)
{
    const int argc = 15;
    char arr[argc][128] = {"xxx.xxx", "-train", "ftrain", "-model", "fmodel", 
                           "-validate", "fvalid", "-linear_kernel", "-c", "0.01", 
                           "-epsilon", "0.001", "-sigma", "0.0001", "-help"};

    char *argv[] = {arr[0], arr[1], arr[2], arr[3], arr[4], 
                    arr[5], arr[6], arr[7], arr[8], arr[9], 
                    arr[10], arr[11], arr[12], arr[13], arr[14]};

    int ret = option->parse_command_line(argc, argv);

    ASSERT_EQ(0, ret);
    
    ASSERT_EQ(0, strcmp(arr[2], option->_fname_train)); 
    ASSERT_EQ(0, strcmp(arr[4], option->_fname_model)); 
    ASSERT_EQ(0, strcmp(arr[6], option->_fname_valid)); 
    
    ASSERT_EQ(true, option->_is_linear_kernel);
    
    ASSERT_TRUE(fabs(atof(arr[9]) - option->_c) < 1e-6);  
    ASSERT_TRUE(fabs(atof(arr[11]) - option->_eps) < 1e-6);
    ASSERT_TRUE(fabs(atof(arr[13]) - option->_sig) < 1e-6); 
}
 
/**
 * @brief 
**/
class test_SVMOption_print_suite : public ::testing::Test{
    protected:
        test_SVMOption_print_suite(){};
        virtual ~test_SVMOption_print_suite(){};
        virtual void SetUp() {
            //Called befor every TEST_F(test_SVMOption_print_suite, *)
        };
        virtual void TearDown() {
            //Called after every TEST_F(test_SVMOption_print_suite, *)
        };
};
 
/**
 * @brief 
 * @begin_version 
**/
TEST_F(test_SVMOption_print_suite, case_name1)
{
	//TODO
}
 
