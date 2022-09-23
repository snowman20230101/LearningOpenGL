//
// Created by windy on 2022/3/17.
//

#include <ostream>
#include <iostream>
#include "TestClass.h"

// 读取 yaml 文件解析库
#include <yaml-cpp/yaml.h>
#include "CommonInclude.h"
#include <fstream>

using namespace YAML;
using namespace std;

TestClass::TestClass() {
    std::cout << "TestClass TestClass()" << std::endl;
    wchar_t str[] = L"abcdefga";
    std::cout << sizeof(str) << std::endl;
    std::cout << sizeof(str[0]) << std::endl;
}

TestClass::~TestClass() {
    std::cout << "TestClass ~TestClass()" << std::endl;
}

void TestClass::exampleYaml() {
    string configPath = std::string(ROOT_DIR) + "resources/config.yaml";
    Node config = YAML::LoadFile(configPath);
    cout << "name:" << config["name"].as<string>() << endl;
    cout << "sex:" << config["sex"].as<string>() << endl;
    cout << "age:" << config["age"].as<int>() << endl;

    cout << "skills c++:" << config["skills"]["c++"].as<int>() << endl;
    cout << "skills java:" << config["skills"]["java"].as<int>() << endl;
    cout << "skills android:" << config["skills"]["android"].as<int>() << endl;
    cout << "skills python:" << config["skills"]["python"].as<int>() << endl;

    // 迭代器迭代
    for (YAML::const_iterator it = config["skills"].begin(); it != config["skills"].end(); ++it) {
        cout << it->first.as<string>() << ":" << it->second.as<int>() << endl;
    }

    // 分别对应 Sequence、Scalar、Map。
    YAML::Node test1 = YAML::Load("[1,2,3,4]");
    cout << " Type: " << test1.Type() << endl;

    YAML::Node test2 = YAML::Load("1");
    cout << " Type: " << test2.Type() << endl;

    YAML::Node test3 = YAML::Load("{'id':1,'degree':'senior'}");
    cout << " Type: " << test3.Type() << endl;

    //
    ofstream fout(configPath.c_str());
    config["score"] = 99;
    fout << config;
    fout.close();
}