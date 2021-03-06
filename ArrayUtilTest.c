#include "expr_assert.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ArrayUtil.h"

void test_areEqual_gives_0_if_arrayUtil_are_not_same(){
	int first_array[]={1,2,3,4,5};
	int second_array[]={1,2,3,4,5,6};
	ArrayUtil array1 = {first_array,sizeof(int),5};
	ArrayUtil array2 = {second_array,sizeof(int),6};
    assertEqual(areEqual(array1, array2),0);
};

void test_for_the_length_of_two_array_are_equal2(){
	int first_array[]={1,2,3,4};
	int second_array[]={1,2,3,4};
	ArrayUtil array1 = {first_array,sizeof(int),4};
	ArrayUtil array2 = {second_array,sizeof(int),4};
    assertEqual(areEqual(array1, array2),1);
};

void test_of_ArrayUtil_for_the_float_are_equall(){
	float first_array[]={1.0,2.6,3.2,4.1};
	float second_array[]={1.0,2.6,3.2,4.1};
	ArrayUtil array1 = {first_array,sizeof(float),4};
	ArrayUtil array2 = {second_array,sizeof(float),4};
    assertEqual(areEqual(array1, array2),1);
};

void test_for_the_ArrayUtil_for_float_are_not_equall(){
	float first_array[]={1.0,2.6,3.2,4.1};
	float second_array[]={1.0,2.9,3.2,4.1};
	ArrayUtil array1 = {first_array,sizeof(float),4};
	ArrayUtil array2 = {second_array,sizeof(float),4};
    assertEqual(areEqual(array1, array2),0);
};

void test_for_the_ArrayUtil_for_charecter_and_int_are_not_equal(){
	char first_array[]={'c','d','e','f'};
	int second_array[]={2,5,8,4};
	ArrayUtil array1 = {first_array,sizeof(char),4};
	ArrayUtil array2 = {second_array,sizeof(int),4};
    assertEqual(areEqual(array1, array2),0);
};

void test_for_create_new_array_of_integertype(){
	ArrayUtil newArray;
	newArray = create(sizeof(int),5);
    assertEqual(newArray.typeSize,4);
    assertEqual(newArray.length,5);
}

void test_for_create_new_array_of_charectertype(){
	ArrayUtil array;
	array = create(sizeof(char),6);
    assertEqual(array.typeSize,1);
    assertEqual(array.length,6);
};

void test_for_create_new_array_of_StringType(){
	ArrayUtil array;
	array = create(sizeof(char*),6);
    assertEqual(array.typeSize,4);
    assertEqual(array.length,6);
};
void test_resize_an_existing_array_to_resize_decrease_its_length(){
	int *resArray;
	ArrayUtil array,resizeArray;
	array = create(sizeof(int),5);
	((int*)array.base)[0]=90;
	((int*)array.base)[1]=40;
	((int*)array.base)[2]=550;
	((int*)array.base)[3]=550;
	((int*)array.base)[4]=40;
	resizeArray=resize(array,4);
	resArray = resizeArray.base;
	assertEqual(resArray[2],550);
	assertEqual(areEqual(resizeArray,array),0);
};

void test_resize_an_existing_array_to_resize_increase_its_length(){
	ArrayUtil array = create(sizeof(int),3),resultArray;
	((int*)array.base)[0]=90;
	((int*)array.base)[1]=40;
	((int*)array.base)[2]=550;
	resultArray = resize(array,5);
	assertEqual(((int *)resultArray.base)[0],90);
	assertEqual(((int *)resultArray.base)[1],40);
	assertEqual(((int *)resultArray.base)[2],550);
	assertEqual(((int *)resultArray.base)[3],0);
	assertEqual(((int *)resultArray.base)[4],0);
};

void test_findIndex_return_the_index_of_existing_element_in_the_array(){
	int x=3;
	int arr[] = {2,4,3,7};
	ArrayUtil array = {arr, sizeof(int) , 4};
	assertEqual(findIndex(array, &x),2);
};

void test_findIndex_retruns_the_index_of_an_element_in_an_char_array(){
	char array[]= {'a','b','c','d'};
	char element ='c';
	ArrayUtil util = {array,sizeof(char),4};
	assertEqual(findIndex(util,&element),2);
};

void test_findIndex_retruns_the_index_of_an_element_in_an_string_array(){
	char array[]= {"heloo"};
	char element ='o';
	ArrayUtil util = {array,sizeof(char),4};
	assertEqual(findIndex(util,&element),3);
};


void test_findIndex_return_first_index_of_multiple_existing_element_in_the_array(){
	int x=7;
	int arr[] = {2,4,3,7,5,7,7,7};
	ArrayUtil array={arr, sizeof(int), 8};
	assertEqual(findIndex(array, &x),3);
};

void test_ArrayUtil_to_find_indexOf_float_type_value_it_gives_1(){
	float x=4.3;
	int y=3,index;
	float arr[] = {3.2,4.3,6.3,8.6};
	ArrayUtil array ={arr,sizeof(float),4};
	assertEqual(findIndex(array, &x),1);
	assertEqual(findIndex(array, &y), -1);
};

void test_ArrayUtil_dispose_to_free_the_memory_allocated_for_the_intType_array(){
	ArrayUtil array1,array2;
	array1 = create(sizeof(int),5);
	array2 = create(sizeof(float),7);
	dispose(array1);
	dispose(array2);
	assertEqual(areEqual(array1,array2),0);
}

void test_ArrayUtil_dispose_to_free_the_memory_allocated_for_the_charType_array(){
	ArrayUtil array1,array2;
	array1 = create(sizeof(char),7);
	array2 = create(sizeof(char*),5);
	dispose(array1);
	dispose(array2);
}

int isEvenNumber(void* hint , void* element){
		return ((*(int*)element) % (*(int*)hint)==0) ;
};

void test_for_findFirst_gives_the_first_element_of_an_array(){
	int hint = 2;
	int *result;
	MatchFunc *match = &isEvenNumber;
	ArrayUtil util = {(int[]){3,5,8,8,7,2},sizeof(int),6};
	result = (int*)findFirst(util,match,&hint);
	assertEqual(*result,8);
}

int isCompareCharecter(void* hint,void* element){
	return ((*(char*)hint) == (*(char*)element));
}

void test_for_findFirst_gives_the_first_element_of_charecter_an_array(){
	char hint = 'c';
	char *result;
	MatchFunc *match = &isCompareCharecter;
	ArrayUtil util = {(char[]){'a','b','c','c','d','c'},sizeof(char),6};
	result = findFirst(util,match,&hint);
	assertEqual(*result,'c');
}

int isLessThanTheHints(void* hint,void* element){
	return (*(float*)element) < (*(float*)hint);

}

void test_for_findFirst_gives_the_first_element_of_greater_than_float_value_an_array(){
	float hint = 6.3;
	float *result;
	MatchFunc *match = &isLessThanTheHints;
	ArrayUtil util = {(float[]){2.3,4.5,6.3,4.5,6.0},sizeof(float),5};
	result = findFirst(util,match,&hint);
	assertEqual(*result,2.3);

};

void test_for_findLast_gives_the_last_element_of_an_array(){
	int hint = 2;
	int *result;
	MatchFunc *match = &isEvenNumber;
	ArrayUtil util = {(int[]){3,5,8,8,7,2,5},sizeof(int),7};
	result = findLast(util,match,&hint);
	assertEqual(*result,2);
};

void test_for_findLast_gives_the_null_if_charecter_is_not_existing_in_an_array(){
	char hint = 'e';
	char *result;
	MatchFunc *match = &isCompareCharecter;
	ArrayUtil util = {(char[]){'a','b','c','c','d','c'},sizeof(char),6};
	result = (char*)findFirst(util,match,&hint);
	assert(result == NULL);
}


void test_for_findLast_gives_the_last_element_of_less_than_float_value_an_array(){
	float hint = 6.3;
	float *result;
	MatchFunc *match = &isLessThanTheHints;
	ArrayUtil util = {(float[]){2.3,4.5,6.3,4.5,6.0},sizeof(float),5};
	result = findFirst(util,match,&hint);
	assertEqual(*result,2.3);
};