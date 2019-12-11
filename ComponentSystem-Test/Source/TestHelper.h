#pragma once
#include <CppUnitTest.h>

// �x���`�}�[�N�������w�肷�� 
// value: Default/DebugOnly/ReleaseOnly/RTTI
#define EGL_TEST_MRTHOD_BENCHMARK(methodName,value) BEGIN_TEST_METHOD_ATTRIBUTE(methodName)\
TEST_METHOD_ATTRIBUTE(L"Benchmark",##value)\
END_TEST_METHOD_ATTRIBUTE()\
TEST_METHOD(methodName)

// �e�X�g���������ł��邱�Ƃ�����
#define EGL_TEST_MRTHOD_NOT_IMPLEMENT(methodName) BEGIN_TEST_METHOD_ATTRIBUTE(methodName)\
TEST_METHOD_ATTRIBUTE(L"Test Not Implement",L" ")\
END_TEST_METHOD_ATTRIBUTE()\
TEST_METHOD(methodName)