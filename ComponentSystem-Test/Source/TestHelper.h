#pragma once
#include <CppUnitTest.h>

// ベンチマーク属性を指定する 
// value: Default/DebugOnly/ReleaseOnly/RTTI
#define EGL_TEST_MRTHOD_BENCHMARK(methodName,value) BEGIN_TEST_METHOD_ATTRIBUTE(methodName)\
TEST_METHOD_ATTRIBUTE(L"Benchmark",##value)\
END_TEST_METHOD_ATTRIBUTE()\
TEST_METHOD(methodName)

// テストが未実装であることを示す
#define EGL_TEST_MRTHOD_NOT_IMPLEMENT(methodName) BEGIN_TEST_METHOD_ATTRIBUTE(methodName)\
TEST_METHOD_ATTRIBUTE(L"Test Not Implement",L" ")\
END_TEST_METHOD_ATTRIBUTE()\
TEST_METHOD(methodName)