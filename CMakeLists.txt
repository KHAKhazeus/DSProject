cmake_minimum_required(VERSION 3.12)
project(DSProject)

set(CMAKE_CXX_STANDARD 14)

add_executable(DSProject test_signup_system/test_signup_system.cpp test_signup_system/ListNode.h test_signup_system/List.h)