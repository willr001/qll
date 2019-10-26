#include "unity.h"
#include "qll.h"
#include <stdlib.h>
#include <string.h>

typedef struct TestStruct TestStruct;

struct TestStruct {
    TestStruct *other;
};

static TestStruct test_struct = { .other = NULL };
static TestStruct test_struct2 = { .other = &test_struct };
static TestStruct test_struct3 = { .other = &test_struct2 };
static TestStruct test_struct_a;
static TestStruct test_struct_b;
static TestStruct test_struct_c;
static TestStruct *returned_value;
static TestStruct *arg;
static TestStruct *head_thing;

void setUp(void)
{
    head_thing = NULL;
    returned_value = ((TestStruct*)1);
    arg = NULL;
    memset(&test_struct_a,0,sizeof(test_struct_a));
    memset(&test_struct_b,0,sizeof(test_struct_a));
    memset(&test_struct_c,0,sizeof(test_struct_a));
    test_struct.other = NULL;
    test_struct2.other = &test_struct;
    test_struct3.other = &test_struct2;
}

void tearDown(void)
{
}

void test_QLL_GET_TAIL_null_returns_null(void)
{
    TEST_ASSERT_EQUAL(NULL,QLL_GET_TAIL(returned_value,head_thing,other));
    TEST_ASSERT_EQUAL(NULL,returned_value);
}

void test_QLL_GET_TAIL_one_returns_self(void)
{
    head_thing = &test_struct;
    TEST_ASSERT_EQUAL(&test_struct,QLL_GET_TAIL(returned_value,head_thing,other));
    TEST_ASSERT_EQUAL(&test_struct,returned_value);
}

void test_QLL_GET_TAIL_one_returns_self_a_different_way(void)
{
    head_thing = &test_struct;
    TestStruct *rval;
    rval = QLL_GET_TAIL(returned_value,head_thing,other);
    TEST_ASSERT_EQUAL(&test_struct,rval);
}

void test_QLL_GET_TAIL_two_returns_second(void)
{
    head_thing = &test_struct2;
    TEST_ASSERT_EQUAL(&test_struct,QLL_GET_TAIL(returned_value,head_thing,other));
}

void test_QLL_FIND_null_head_returns_null(void)
{
    returned_value = (TestStruct*)1;
    TestStruct *find_this = returned_value;
    TEST_ASSERT_EQUAL(NULL,QLL_FIND(returned_value,find_this,head_thing,other));
    TEST_ASSERT_EQUAL(NULL,returned_value);
}

void test_QLL_FIND_null_find_returns_null(void)
{
    TestStruct *returned_value = (TestStruct*)1;
    TestStruct *find_this = NULL;
    head_thing = returned_value;
    TEST_ASSERT_EQUAL(NULL,QLL_FIND(returned_value,find_this,head_thing,other));
    TEST_ASSERT_EQUAL(NULL,returned_value);
}

void test_QLL_FIND_match_works(void)
{
    TestStruct *returned_value = NULL;
    TestStruct *find_this = head_thing = (TestStruct*)1;
    TEST_ASSERT_EQUAL(find_this,QLL_FIND(returned_value,find_this,head_thing,other));
    TEST_ASSERT_EQUAL(find_this,returned_value);
}

void test_QLL_FIND_next_works(void)
{
    TestStruct test_struct = { .other = NULL };
    TestStruct test_struct2 = { .other = &test_struct };
    TestStruct *find_this = &test_struct;
    TestStruct *returned_value = NULL;
    head_thing = &test_struct2;
    TEST_ASSERT_EQUAL(find_this,QLL_FIND(returned_value,find_this,head_thing,other));
    TEST_ASSERT_EQUAL(find_this,returned_value);
}

void test_QLL_FIND_mismatch_fails(void)
{
    TestStruct test_struct = { .other = NULL };
    TestStruct *find_this = (TestStruct*)1;
    TestStruct *returned_value = find_this;
    head_thing = &test_struct;
    TEST_ASSERT_EQUAL(NULL,QLL_FIND(returned_value,find_this,head_thing,other));
    TEST_ASSERT_EQUAL(NULL,returned_value);
}

void test_QLL_FIND_two_returns_second(void)
{
    TestStruct test_struct = { .other = NULL };
    TestStruct test_struct2 = { .other = &test_struct };
    TestStruct *find_this = &test_struct;
    TestStruct *returned_value = NULL;
    head_thing = &test_struct2;
    TEST_ASSERT_EQUAL(find_this,QLL_FIND(returned_value,find_this,head_thing,other));
}

void test_QLL_FIND_three_returns_third(void)
{
    TestStruct test_struct = { .other = NULL };
    TestStruct test_struct2 = { .other = &test_struct };
    TestStruct test_struct3 = { .other = &test_struct2 };
    TestStruct *find_this = &test_struct;
    TestStruct *returned_value = NULL;
    head_thing = &test_struct3;
    TEST_ASSERT_EQUAL(find_this,QLL_FIND(returned_value,find_this,head_thing,other));
}

void test_QLL_FIND_three_fail(void)
{
    TestStruct test_struct = { .other = NULL };
    TestStruct test_struct2 = { .other = &test_struct };
    TestStruct test_struct3 = { .other = &test_struct2 };
    TestStruct *find_this = (TestStruct*)1;
    TestStruct *returned_value = find_this;
    head_thing = &test_struct3;
    TEST_ASSERT_EQUAL(NULL,QLL_FIND(returned_value,find_this,head_thing,other));
    TEST_ASSERT_EQUAL(NULL,returned_value);
}

void test_QLL_REMOVE_remove_null(void)
{
    TestStruct *temp;
    head_thing = &test_struct;
    QLL_REMOVE(temp, arg, head_thing, other);
    TEST_ASSERT_EQUAL(&test_struct, head_thing);
}

void test_QLL_REMOVE_head_null(void)
{
    TestStruct *temp;
    arg = &test_struct2;
    QLL_REMOVE(temp, arg, head_thing, other);
    TEST_ASSERT_EQUAL(arg->other, &test_struct);
}

void test_QLL_REMOVE_head_equals_remove(void)
{
    TestStruct *temp;
    head_thing = &test_struct3;
    QLL_REMOVE(temp, &test_struct3, head_thing, other);
    TEST_ASSERT_EQUAL(&test_struct2, head_thing);
}

void test_QLL_REMOVE_head_contains_remove(void)
{
    TestStruct *temp;
    head_thing = &test_struct3;
    QLL_REMOVE(temp, &test_struct2, head_thing, other);
    TEST_ASSERT_EQUAL(test_struct3.other, &test_struct);
}

void test_QLL_REMOVE_head_doesnt_contain_remove(void)
{
    TestStruct *temp;
    head_thing = &test_struct3;
    QLL_REMOVE(temp, &test_struct_a, head_thing, other);
    TEST_ASSERT_EQUAL(test_struct3.other, &test_struct2);
    TEST_ASSERT_EQUAL(test_struct2.other, &test_struct);
    TEST_ASSERT_EQUAL(test_struct.other, NULL);
    TEST_ASSERT_EQUAL(head_thing, &test_struct3);
}

void test_qll_NeedToImplement(void)
{
    // add
    TEST_IGNORE_MESSAGE("Need to Implement qll");
}
