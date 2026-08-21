//gtest简单实用

//1.包含头文件
#include <gtest/gtest.h>
#include <iostream>
#include <unordered_map>
//2.定义测试用例
TEST(unordered_map,insert){
    std::unordered_map<int,int> map;
    map.insert(std::make_pair(1,1));
    map.insert(std::make_pair(2,2));
    map.insert(std::make_pair(3,3));
    ASSERT_EQ(map.size(),3);
}
TEST(unordered_map_test,find){
    std::unordered_map<int,int> map;
    map.insert(std::make_pair(1,114514));
    map.insert(std::make_pair(2,2));
    map.insert(std::make_pair(3,3));
    ASSERT_NE(map.find(1),map.end());
    ASSERT_EQ(map.find(1)->second,1);
}

int main(int argc, char* argv[]){
    //3.初始化测试环境
    testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}
//4.执行测试用例