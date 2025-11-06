cmake_minimum_required(VERSION 4.0)
project(cpp_datastructures)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(cpp_datastructures main.cpp
        tree/bst/SinarySearchTree.cpp
        tree/bst/SinarySearchTree.h
        tree/string/StringTest.cpp
        tree/vector/VectorTest.cpp
        heap/HeapTest.cpp
        cache/LruCacheLinkedList.cpp
        cache/LruCacheLinkedList.h
        nullsafety/OptionalExample.cpp
        greedy/GasStation.cpp
        namespaces/NamespaceAliasesExample.cpp
        graph/cycle_detection/DFSCycleDetection.cpp
        graph/cycle_detection/DFSCycleDetection.h
        set/disjoint_set/DisjointSetCycleDetection.cpp
        deque/SlidingWindowMaximum.cpp
        deque/SlidingWindowMedian.cpp
        heap/MedianOfRunningStream.cpp
        linkedlist/DeleteMiddle.cpp
        sorting/KthLargestElement.cpp
        graph/limits/PlayWithLimits.cpp
        tree/string/SplitAndJoin.cpp
        heap/PriorityQueueCTAD.cpp
        string/KMP.cpp
        string/FindFirstOccurenceOfCharacter.cpp
        math/geometry/linear_algebra/Vector2D.cpp
        functional_programming/MapReduceFilter.cpp
        concurrency/ConsumerProducerProblem.cpp
        concurrency/LockFreeConcurrency.cpp
        math/geometry/linear_algebra/GaussElimination.cpp
        functional_programming/Lambdas.cpp
        heap/MinimumMeetingRoomsRequired.cpp
        math/bitwise_operator/BitSet.cpp
        graph/scc/Kosaraju.cpp
        tree/trie/SearchSuggestionSystem.cpp
        math/intervals/InsertIntervals.cpp
        math/binary/AddBinary.cpp)
