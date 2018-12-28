cmake_minimum_required(VERSION 3.12)
project(DSProject)

set(CMAKE_CXX_STANDARD 14)



add_executable(test_signup_system
        test_signup_system/test_signup_system.cpp
        test_signup_system/ListNode.h
        test_signup_system/List.h)
add_executable(intersection_of_chains
        intersection_of_chains/intersection_of_chains.cpp
        intersection_of_chains/ListNode.h
        intersection_of_chains/NonDecreaseList.h)
add_executable(maze
        maze/maze.cpp
        maze/ListNode.h
        maze/Stack.h)
add_executable(expression_transform
        expression_transform/expression_transform.cpp
        expression_transform/ListNode.h
        expression_transform/Stack.h)
add_executable(bank_queue
        bank_queue/bank_queue.cpp
        bank_queue/Queue.h
        bank_queue/ListNode.h)
add_executable(family_tree_system
        family_tree_system/family_tree_system.cpp family_tree_system/Tree.h family_tree_system/TreeNode.h)