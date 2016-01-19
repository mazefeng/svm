
#include <svm_common.h>
#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <fstream>

using std::string;	
using std::vector;
using std::ifstream;
	
int main(int argc, char **argv)
{
 	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
/**
 * @brief 
**/
class test_split_suite : public ::testing::Test{
    protected:
        test_split_suite(){};
        virtual ~test_split_suite(){};
        virtual void SetUp() {
            //Called befor every TEST_F(test_split_suite, *)
        };
        virtual void TearDown() {
            //Called after every TEST_F(test_split_suite, *)
        };
};
 
/**
 * @brief 
 * @begin_version 
**/
TEST_F(test_split_suite, case_split)
{
    string s = "this is a test string";
    vector<string> v;
    
    split(s, ' ', v);
    
    ASSERT_EQ(5, (int)v.size());
    
    ASSERT_EQ(0, v[0].compare("this"));
    ASSERT_EQ(0, v[1].compare("is"));
    ASSERT_EQ(0, v[2].compare("a"));
    ASSERT_EQ(0, v[3].compare("test"));
    ASSERT_EQ(0, v[4].compare("string"));
}
 
/**
 * @brief 
**/
class test_cmp_suite : public ::testing::Test{
    protected:
        test_cmp_suite(){};
        virtual ~test_cmp_suite(){};
        virtual void SetUp() {
            //Called befor every TEST_F(test_cmp_suite, *)
        };
        virtual void TearDown() {
            //Called after every TEST_F(test_cmp_suite, *)
        };
};
 
/**
 * @brief 
 * @begin_version 
**/
TEST_F(test_cmp_suite, case_cmp)
{
    TVectorDim p1, p2;

    p1.second = 0.0;
    p2.second = 0.0;

    p1.first = 0;
    p2.first = 1;

    ASSERT_TRUE(cmp(p1, p2));
    ASSERT_FALSE(cmp(p2, p1));

}
 
/**
 * @brief 
**/
class test_read_sample_suite : public ::testing::Test{
    protected:
        test_read_sample_suite(){};
        virtual ~test_read_sample_suite(){};
        virtual void SetUp() {
            //Called befor every TEST_F(test_read_sample_suite, *)
        };
        virtual void TearDown() {
            //Called after every TEST_F(test_read_sample_suite, *)
        };
};
 
/**
 * @brief 
 * @begin_version 
**/
TEST_F(test_read_sample_suite, case_read_sample)
{
    TString s = "1.0 2:2.0 0:0.0 1:1.0";
    TVector x;
    float y;
    
    int ret = read_sample(s, x, y);
    
    ASSERT_EQ(0, ret);
    ASSERT_EQ(1.0, y);
    ASSERT_EQ(3, (int)x.size());
    
    ASSERT_TRUE(x[0].first == 0);
    ASSERT_TRUE(x[0].second == 0.0);
    
    ASSERT_TRUE(x[1].first == 1);
    ASSERT_TRUE(x[1].second == 1.0);
    
    ASSERT_TRUE(x[2].first == 2);
    ASSERT_TRUE(x[2].second == 2.0);
}
 
/**
 * @brief 
**/
class test_write_sample_suite : public ::testing::Test{
    protected:
        test_write_sample_suite(){};
        virtual ~test_write_sample_suite(){};
        virtual void SetUp() {
            //Called befor every TEST_F(test_write_sample_suite, *)
        };
        virtual void TearDown() {
            //Called after every TEST_F(test_write_sample_suite, *)
        };
};
 
/**
 * @brief 
 * @begin_version 
**/
TEST_F(test_write_sample_suite, case_write_sample)
{
	//TODO
    TString s;
    TVector x;
    float y;

    x.push_back(TVectorDim(2, 2.1));
    x.push_back(TVectorDim(0, 0.1));
    x.push_back(TVectorDim(1, 1.1));
    y = 1.1;

    int ret = write_sample(s, x, y);
 
    ASSERT_EQ(0, ret);
    ASSERT_EQ(0, s.compare("1.1 2:2.1 0:0.1 1:1.1"));
}
 
/**
 * @brief 
**/
class test_batch_read_sample_suite : public ::testing::Test{
    protected:
        test_batch_read_sample_suite(){};
        virtual ~test_batch_read_sample_suite(){};
        virtual void SetUp() {
            //Called befor every TEST_F(test_batch_read_sample_suite, *)
        };
        virtual void TearDown() {
            //Called after every TEST_F(test_batch_read_sample_suite, *)
        };
};
 
/**
 * @brief 
 * @begin_version 
**/
TEST_F(test_batch_read_sample_suite, case_batch_read_sample)
{
	//TODO
    TVectorArray X;
    TFloatArray Y;
    int n;

    string fname = "data/test_batch_read_sample.dat";
    ifstream is(fname.c_str());
    int ret = batch_read_sample(is, X, Y, n);
    
    ASSERT_EQ(0, ret);
    ASSERT_EQ(4, n);

    ASSERT_EQ(4, (int)X.size());
    ASSERT_EQ(4, (int)Y.size());

}
 
/**
 * @brief 
**/
class test_batch_write_sample_suite : public ::testing::Test{
    protected:
        test_batch_write_sample_suite(){};
        virtual ~test_batch_write_sample_suite(){};
        virtual void SetUp() {
            //Called befor every TEST_F(test_batch_write_sample_suite, *)
        };
        virtual void TearDown() {
            //Called after every TEST_F(test_batch_write_sample_suite, *)
        };
};
 
/**
 * @brief 
 * @begin_version 
**/
TEST_F(test_batch_write_sample_suite, case_batch_write_sample)
{
	//TODO
}
 
/**
 * @brief 
**/
class test_print_vector_suite : public ::testing::Test{
    protected:
        test_print_vector_suite(){};
        virtual ~test_print_vector_suite(){};
        virtual void SetUp() {
            //Called befor every TEST_F(test_print_vector_suite, *)
        };
        virtual void TearDown() {
            //Called after every TEST_F(test_print_vector_suite, *)
        };
};
 
/**
 * @brief 
 * @begin_version 
**/
TEST_F(test_print_vector_suite, case_name1)
{
	//TODO
}
 
/**
 * @brief 
**/
class test_dot_product_suite : public ::testing::Test{
    protected:
        test_dot_product_suite(){};
        virtual ~test_dot_product_suite(){};
        virtual void SetUp() {
            //Called befor every TEST_F(test_dot_product_suite, *)
        };
        virtual void TearDown() {
            //Called after every TEST_F(test_dot_product_suite, *)
        };
};
 
/**
 * @brief 
 * @begin_version 
**/
TEST_F(test_dot_product_suite, case_dot_product)
{
    TVector v1;
    TVector v2;
    
    v1.push_back(TVectorDim(0, 1.0));
    v1.push_back(TVectorDim(1, 2.0));
    v1.push_back(TVectorDim(3, 4.0));

    v2.push_back(TVectorDim(0, 2.0));
    v2.push_back(TVectorDim(2, 4.0));
    v2.push_back(TVectorDim(3, 8.0));

    float dot = dot_product(v1, v2);
    
    ASSERT_EQ(34.0, dot);
    
}
 
/**
 * @brief 
**/
class test_operator_multiplies_suite : public ::testing::Test{
    protected:
        test_operator_multiplies_suite(){};
        virtual ~test_operator_multiplies_suite(){};
        virtual void SetUp() {
            //Called befor every TEST_F(test_operator_multiplies_suite, *)
        };
        virtual void TearDown() {
            //Called after every TEST_F(test_operator_multiplies_suite, *)
        };
};
 
/**
 * @brief 
 * @begin_version 
**/
TEST_F(test_operator_multiplies_suite, case_left_multiplies)
{
	TVector v;
    float f;

    v.push_back(TVectorDim(0, 1.0));
    v.push_back(TVectorDim(1, 2.0));
    v.push_back(TVectorDim(2, 4.0));

    f = 4.0;

    TVector fv = f * v;
    ASSERT_EQ(3, (int)fv.size());
    
    ASSERT_EQ(0, fv[0].first);
    ASSERT_EQ(4.0, fv[0].second);
    
    ASSERT_EQ(1, fv[1].first);
    ASSERT_EQ(8.0, fv[1].second);

    ASSERT_EQ(2, fv[2].first);
    ASSERT_EQ(16.0, fv[2].second);

}
 
/**
 * @brief 
 * @begin_version 
**/
TEST_F(test_operator_multiplies_suite, case_right_multiplies)
{
	//TODO
	TVector v;
    float f;

    v.push_back(TVectorDim(0, 1.0));
    v.push_back(TVectorDim(1, 2.0));
    v.push_back(TVectorDim(2, 4.0));

    f = 2.0;

    TVector vf = v * f;
    ASSERT_EQ(3, (int)vf.size());
    
    ASSERT_EQ(0, vf[0].first);
    ASSERT_EQ(2.0, vf[0].second);
    
    ASSERT_EQ(1, vf[1].first);
    ASSERT_EQ(4.0, vf[1].second);

    ASSERT_EQ(2, vf[2].first);
    ASSERT_EQ(8.0, vf[2].second);
}
 
/**
 * @brief 
**/
class test_operator_plus_suite : public ::testing::Test{
    protected:
        test_operator_plus_suite(){};
        virtual ~test_operator_plus_suite(){};
        virtual void SetUp() {
            //Called befor every TEST_F(test_operator_plus_suite, *)
        };
        virtual void TearDown() {
            //Called after every TEST_F(test_operator_plus_suite, *)
        };
};
 
/**
 * @brief 
 * @begin_version 
**/
TEST_F(test_operator_plus_suite, case_plus)
{
    TVector v1;
    TVector v2;
    
    v1.push_back(TVectorDim(0, 1.0));
    v1.push_back(TVectorDim(1, 2.0));
    v1.push_back(TVectorDim(3, 4.0));

    v2.push_back(TVectorDim(0, 2.0));
    v2.push_back(TVectorDim(2, 4.0));
    v2.push_back(TVectorDim(3, 8.0));
    
    TVector v12 = v1 + v2;

    ASSERT_EQ(4, (int)v12.size());
    
    ASSERT_EQ(0, v12[0].first);
    ASSERT_EQ(3.0, v12[0].second);
    
    ASSERT_EQ(1, v12[1].first);
    ASSERT_EQ(2.0, v12[1].second);

    ASSERT_EQ(2, v12[2].first);
    ASSERT_EQ(4.0, v12[2].second);
    
    ASSERT_EQ(3, v12[3].first);
    ASSERT_EQ(12.0, v12[3].second);

}
 
