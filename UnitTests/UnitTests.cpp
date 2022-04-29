#include "pch.h"
#include "CppUnitTest.h"
#include "..\lab2\queue.h"
#include "..\lab2\stack.h"
#include "..\lab2\sortStation.h"
#include "..\lab2\sortStation.cpp"
#include "..\lab2\Person.h"
#include "..\lab2\complex.h"
#include "..\lab2\Person.cpp"
#include "..\lab2\complex.cpp"



using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(UnitTests)
	{
	public:
		//DynamicArrayTest
		TEST_METHOD(DynamicArrayTest)
		{
			int src1[10] = { 1,4,9,16,25,36,49,64,81,100 };
			int src2[3] = { 777,666,555 };
			DynamicArray<int> test1(src1, 10); DynamicArray<int> test1_1(src2, 3);
			double src3[7] = { 0.5, 0.66, 1.56, 12773.9865, -17.5, 0.22222, 9.78 };

			//test1
			test1 = *(test1.Concat(&test1_1));
			DynamicArray<int> expected1 = { 1,4,9,16,25,36,49,64,81,100,777,666,555 };
			Assert::IsTrue(expected1 == test1, L"DynamicArray: wrong answer, test 1");

			//test2
			test1_1 = *(test1.SplitArray([](int a) {return a > 15; }));
			DynamicArray<int> expected2_1 = { 16,25,36,49,64,81,100,777,666,555 };
			DynamicArray<int> expected2_2 = { 1,4,9 };
			Assert::IsTrue(expected2_1 == test1_1 && expected2_2 == test1, L"DynamicArray: wrong answer, test 2");

			//test3
			DynamicArray<double> test3(src3, 7);
			DynamicArray<double> test3_1 = *(test3.GetSubArray(1, 5));
			DynamicArray<double> expected3 = { 0.66, 1.56, 12773.9865, -17.5, 0.22222 };
			Assert::IsTrue(expected3 == test3_1, L"DynamicArray: wrong answer, test 3");

			//test4
			DynamicArray<complex> test4 = { complex(1,2), complex(2,3), complex(4,1) };
			test4.Append(complex(-1, -1));
			test4.Prepend(complex(0, 3));
			test4.InsertAt(complex(2, 7), 3);
			test4.del_item(0);
			test4.Resize(6);
			test4.Set(5, complex(7, 7));
			complex check4_1 = test4[1];
			complex check4_2 = test4.Get(1);
			DynamicArray<complex> expected4 = { complex(1,2),complex(2,3),complex(2,7), complex(4,1),  complex(-1,-1), complex(7,7) };
			Assert::IsTrue((expected4 == test4) && (check4_1 == complex(2, 3) && (check4_1 == check4_2)), L"DynamicArray: wrong answer, test 4");

			//test5
			DynamicArray<Teacher> test5 = { Teacher("3301 546743", "Теляковский","Дмитрий","Сергеевич",62,"Математик",30),
									Teacher("3302 567803", "Храмченков","Дмитрий","Викторович",65,"Физик",23),
									Teacher("3302 567333", "Барыкин","Леонид","Романович",25,"Программист",22),
									Teacher("3317 123123", "Камынин","Виталий","Леонидович",67,"Математик",30),
									Teacher("3306 567892", "Курнаев","Александр","Алексеевич",31,"Лингвист",50) };

			int check5_1 = test5.find(0, 2, Teacher("1", "1", "1", "1", 40, "2", 30));
			int check5_2 = test5.find(0, 2, Teacher("3302 567803", "Храмченков", "Дмитрий", "Викторович", 65, "Физик", 23));
			DynamicArray<Teacher> test5_cur = { Teacher("3317 123456", "Клинов","Никита","Андреевич",17,"Б21-514",22) };
			Assert::IsTrue((check5_1 == -1) && (check5_2 == 1) && (!test5.Equals(&test5_cur)), L"DynamicArray: wrong answer, test 5");

			//test6
			DynamicArray<Student> test6 = { Student("3317 567232", "Костяев","Артём","Сергеевич",18,"Б21-514","Программная инженерия"),
											Student("3317 123456", "Джо","Байден","Андреевич",178,"РФ","Промышленное уничтожение подъездов"),
											Student("3317 987721", "Путин","Владимир","Владимирович",65,"Б21-514","Бизнес-информатика"),
											Student("3314 445366", "Обама","Барак","Владимирович",54,"НАТО","Промышленная кулинария") };

			DynamicArray<Student> test6_1_cur = { Student("3317 987721", "Путин","Владимир","Владимирович",65,"Б21-514","Бизнес-информатика"),
												  Student("3314 445366", "Обама","Барак","Владимирович",54,"НАТО","Промышленная кулинария") };
			DynamicArray<Student> test6_2_cur = { Student("3317 987721", "Путин","Владимир","Владимирович",65,"Б21-514","Бизнес-информатика"),
												  Student("3302 567333", "Барыкин","Леонид","Романович",25,"Программист","22") };
			bool f = (test6.IsSubArr(&test6_1_cur)) && (!test6.IsSubArr(&test6_2_cur));
			Assert::IsTrue(f == 1, L"DynamicArray: wrong answer, test 6");
			//test7
			Assert::ExpectException<SetException>([&test1]() {test1[-1] = 0; }, L"DynamicArray: wrong exception, test 7");
			Assert::ExpectException<SetException>([&test1]() {test1.find(1, 0, 1); }, L"DynamicArray: wrong exception, test 7");
			Assert::ExpectException<SetException>([&test1]() {test1.find(-2, 0, 1); }, L"DynamicArray: wrong exception, test 7");
			Assert::ExpectException<SetException>([&test1]() {test1.Resize(-1); }, L"DynamicArray: wrong exception, test 7");
			Assert::ExpectException<SetException>([&test1]() {test1.InsertAt(20, 20); }, L"DynamicArray: wrong exception, test 7");
			Assert::ExpectException<SetException>([&test1]() {test1.GetSubArray(2, -2); }, L"DynamicArray: wrong exception, test 7");
			Assert::ExpectException<SetException>([&test1]() {test1.del_item(20); }, L"DynamicArray: wrong exception, test 7");
		}
		TEST_METHOD(LinkedListTest)
		{
			int src1[10] = { 1,4,9,16,25,36,49,64,81,100 };
			int src2[3] = { 777,666,555 };
			LinkedList<int> test1(src1, 10); LinkedList<int> test1_1(src2, 3);
			double src3[7] = { 0.5, 0.66, 1.56, 12773.9865, -17.5, 0.22222, 9.78 };

			//test1
			test1 = *(test1.Concat(&test1_1));
			LinkedList<int> expected1 = { 1,4,9,16,25,36,49,64,81,100,777,666,555 };
			Assert::IsTrue(expected1 == test1, L"LinkedList: wrong answer, test 1");

			//test2
			test1_1 = *(test1.SplitList([](int a) {return a > 15; }));
			LinkedList<int> expected2_1 = { 16,25,36,49,64,81,100,777,666,555 };
			LinkedList<int> expected2_2 = { 1,4,9 };
			Assert::IsTrue(expected2_1 == test1_1 && expected2_2 == test1, L"LinkedList: wrong answer, test 2");

			//test3
			LinkedList<double> test3(src3, 7); LinkedList<double> test3_1;

			test3_1 = *(test3.GetSubList(1, 5));
			LinkedList<double> expected3 = { 0.66, 1.56, 12773.9865, -17.5, 0.22222 };
			Assert::IsTrue(expected3 == test3_1, L"LinkedList: wrong answer, test 3");

			//test4
			LinkedList<complex> test4 = { complex(1,2), complex(2,3), complex(4,1) };

			test4.Append(complex(-1, -1));
			test4.Prepend(complex(0, 3));
			test4.InsertAt(complex(2, 7), 3);
			test4.del_item(0);
			test4.Set(3, complex(7, 7));
			complex check4_1 = test4[1];
			complex check4_2 = test4.Get(1);
			LinkedList<complex> expected4 = { complex(1,2),complex(2,3),complex(2,7), complex(7,7),  complex(-1,-1) };
			Assert::IsTrue((expected4 == test4) && (check4_1 == complex(2, 3) && (check4_1 == check4_2)), L"LinkedList: wrong answer, test 4");

			//test5
			LinkedList<Teacher> test5 = { Teacher("3301 546743", "Теляковский","Дмитрий","Сергеевич",62,"Математик",30),
									Teacher("3302 567803", "Храмченков","Дмитрий","Викторович",65,"Физик",23),
									Teacher("3302 567333", "Барыкин","Леонид","Романович",25,"Программист",22),
									Teacher("3317 123123", "Камынин","Виталий","Леонидович",67,"Математик",30),
									Teacher("3306 567892", "Курнаев","Александр","Алексеевич",31,"Лингвист",50) };

			int check5_1 = test5.find(0, 2, Teacher("1", "1", "1", "1", 40, "2", 30));
			int check5_2 = test5.find(0, 2, Teacher("3302 567803", "Храмченков", "Дмитрий", "Викторович", 65, "Физик", 23));
			LinkedList<Teacher> test5_cur = { Teacher("3317 123456", "Клинов","Никита","Андреевич",17,"Б21-514",22) };
			Assert::IsTrue((check5_1 == -1) && (check5_2 == 1) && (!test5.Equals(&test5_cur)), L"LinkedList: wrong answer, test 5");

			//test6
			LinkedList<Student> test6 = { Student("3317 567232", "Костяев","Артём","Сергеевич",18,"Б21-514","Программная инженерия"),
											Student("3317 123456", "Джо","Байден","Андреевич",178,"РФ","Промышленное уничтожение подъездов"),
											Student("3317 987721", "Путин","Владимир","Владимирович",65,"Б21-514","Бизнес-информатика"),
											Student("3314 445366", "Обама","Барак","Владимирович",54,"НАТО","Промышленная кулинария") };

			LinkedList<Student> test6_1_cur = { Student("3317 987721", "Путин","Владимир","Владимирович",65,"Б21-514","Бизнес-информатика"),
												Student("3314 445366", "Обама","Барак","Владимирович",54,"НАТО","Промышленная кулинария") };
			LinkedList<Student> test6_2_cur = { Student("3317 987721", "Путин","Владимир","Владимирович",65,"Б21-514","Бизнес-информатика"),
												  Student("3302 567333", "Барыкин","Леонид","Романович",25,"Программист","22") };
			bool f = (test6.IsSubList(&test6_1_cur)) && (!test6.IsSubList(&test6_2_cur));
			Assert::IsTrue(f == 1, L"LinkedList: wrong answer, test 6");
			//test7
			Assert::ExpectException<SetException>([&test1]() {test1[-1] = 0; }, L"LinkedList: wrong exception, test 7");
			Assert::ExpectException<SetException>([&test1]() {test1.find(1, 0, 1); }, L"LinkedList: wrong exception, test 7");
			Assert::ExpectException<SetException>([&test1]() {test1.find(-2, 0, 1); }, L"LinkedList: wrong exception, test 7");
			Assert::ExpectException<SetException>([&test1]() {test1.InsertAt(20, 20); }, L"LinkedList: wrong exception, test 7");
			Assert::ExpectException<SetException>([&test1]() {test1.GetSubList(2, -2); }, L"LinkedList: wrong exception, test 7");
			Assert::ExpectException<SetException>([&test1]() {test1.del_item(20); }, L"LinkedList: wrong exception, test 7");
		}

		TEST_METHOD(QueueTest)
		{
			//test1
			queue<int> test1_a1(ArrayType);
			queue<int> test1_a2(ArrayType);
			test1_a1.push(1);
			test1_a1.push(3);
			test1_a1.push(8);
			test1_a1.pop();
			test1_a1.push(11);
			test1_a1.push(-9);
			test1_a1.pop();
			test1_a2.push(9);
			test1_a2.push(0);
			test1_a2.pop();
			test1_a2.push(77);
			bool check1 = test1_a1.find(3);
			bool check2 = test1_a1.find(-9);
			test1_a1 = *(test1_a1.Concat(&test1_a2));
			queue<int> expected1({ 8,11,-9,0,77 }, ArrayType);
			Assert::IsTrue((expected1 == test1_a1) && (!check1) && (check2), L"queue: wrong answer, test 1");

			//test2
			queue<int> test2_l1(ListType);
			queue<int> test2_l2(ListType);
			test2_l1.push(20);
			test2_l1.push(14);
			test2_l1.push(8);
			test2_l1.pop();
			test2_l1.push(14);
			test2_l1.push(-11);
			test2_l1.push(16);
			test2_l1.pop();
			test2_l1.push(0);
			test2_l1.push(77);
			int check3 = test2_l1.front();
			test2_l2 = *(test2_l1.SplitQueue([](int a) {return a > 8; }));
			queue<int> expected2_1({ 14, 16, 77 }, ListType);
			queue<int> expected2_2({ 8, -11, 0 }, ListType);
			Assert::IsTrue((test2_l2 == expected2_1) && (test2_l1 == expected2_2) && (check3 == 8), L"queue: wrong answer, test 2");

			//test3
			queue<double> test3({ 1.56, 0.89, 15.76, -122.44, 15.66 }, ArrayType);
			queue<double> test3_1((*test3.GetSubQueue(0, 2)));
			queue<double> expected3({ 1.56, 0.89, 15.76 }, ArrayType);
			Assert::IsTrue(test3_1 == expected3, L"queue: wrong answer, test 3");

			//test4
			queue<Teacher> test4_s1({ Teacher("3301 546743", "Теляковский","Дмитрий","Сергеевич",62,"Математик",30),
									Teacher("3302 567803", "Храмченков","Дмитрий","Викторович",65,"Физик",23),
									Teacher("3302 567333", "Барыкин","Леонид","Романович",25,"Программист",22),
									Teacher("3317 123123", "Камынин","Виталий","Леонидович",67,"Математик",30),
									Teacher("3306 567892", "Курнаев","Александр","Алексеевич",31,"Лингвист",50) }, ArrayType);
			queue<Student> test4_s2({ Student("3317 567232", "Костяев","Артём","Сергеевич",18,"Б21-514","Программная инженерия"),
											Student("3317 123456", "Джо","Байден","Андреевич",178,"РФ","Промышленное уничтожение подъездов"),
											Student("3317 987721", "Путин","Владимир","Владимирович",65,"Б21-514","Бизнес-информатика"),
											Student("3314 445366", "Обама","Барак","Владимирович",54,"НАТО","Промышленная кулинария") }, ArrayType);
			queue<Student> test4_1({ Student("3317 567232", "Костяев","Артём","Сергеевич",18,"Б21-514","Программная инженерия"),
									 Student("3314 445366", "Обама","Барак","Владимирович",54,"НАТО","Промышленная кулинария") }, ArrayType);
			queue<Teacher> test4_2({ Teacher("3317 123123", "Камынин","Виталий","Леонидович",67,"Математик",30) ,
									 Teacher("3317 123456", "Джо","Байден","Андреевич",178,"РФ",30) }, ArrayType);
			Assert::IsTrue(test4_s2.IsSubQueue(&test4_1) && !test4_s1.IsSubQueue(&test4_2), L"queue: wrong answe, test 4");

			//test5
			queue<complex> test5_s1({ complex(1,2), complex(2,3), complex(4,1), complex(7, -10), complex(5,6), complex(-3,2) }, ArrayType);
			queue<complex> expected5_1({ complex(4,1), complex(7, -10), complex(5,6) }, ArrayType);
			queue<complex> test5_1 = *(test5_s1.where([](complex c) {return c.GetAbs() >= 4; }));
			Assert::IsTrue(test5_1 == expected5_1, L"queue: wrong answer, test 5");

			//test6
			queue<int> test6({ 10,7,18,13,-9,-16,3,7,15 }, ArrayType);
			queue<int> expected6({ 100,49,324,169,81,256,9,49,225 }, ArrayType);
			test6.map([](int x) {return x * x; });
			Assert::IsTrue(test6 == expected6, L"queue: wrong answer, test 6");

			//test7
			queue<int> test7({ 1,4,-5,9,-10,12,3,5 }, ArrayType);
			int expected7 = 19;
			int res = test7.reduce([](int a, int b) {return a + b; }, 0);
			Assert::IsTrue(res == expected7, L"queue: wrong answer, test 7");
		}

		TEST_METHOD(StackTest)
		{
			//test1
			stack<int> test1_a1(ArrayType);
			stack<int> test1_a2(ArrayType);
			test1_a1.push(1);
			test1_a1.push(3);
			test1_a1.push(8);
			test1_a1.pop();
			test1_a1.push(11);
			test1_a1.push(-9);
			test1_a1.pop();
			test1_a2.push(9);
			test1_a2.push(0);
			test1_a2.pop();
			test1_a2.push(77);
			bool check1 = test1_a1.find(8);
			bool check2 = test1_a1.find(11);
			test1_a1 = *(test1_a1.Concat(&test1_a2));
			stack<int> expected1({ 11,3,1, 77,9 }, ArrayType);
			Assert::IsTrue((expected1 == test1_a1) && (!check1) && (check2), L"stack: wrong answer, test 1");



			//test2
			stack<double> test2({ 1.56, 0.89, 15.76, -122.44, 15.66 }, ArrayType);
			stack<double> test2_1((*test2.GetSubStack(0, 3)));
			stack<double> expected2({ 1.56, 0.89, 15.76, -122.44 }, ArrayType);
			Assert::IsTrue(test2_1 == expected2, L"stack: wrong answer, test 2");

			//test3
			stack<Teacher> test3_s1({ Teacher("3301 546743", "Теляковский","Дмитрий","Сергеевич",62,"Математик",30),
									Teacher("3302 567803", "Храмченков","Дмитрий","Викторович",65,"Физик",23),
									Teacher("3302 567333", "Барыкин","Леонид","Романович",25,"Программист",22),
									Teacher("3317 123123", "Камынин","Виталий","Леонидович",67,"Математик",30),
									Teacher("3306 567892", "Курнаев","Александр","Алексеевич",31,"Лингвист",50) }, ArrayType);
			stack<Student> test3_s2({ Student("3317 567232", "Костяев","Артём","Сергеевич",18,"Б21-514","Программная инженерия"),
											Student("3317 123456", "Джо","Байден","Андреевич",178,"РФ","Промышленное уничтожение подъездов"),
											Student("3317 987721", "Путин","Владимир","Владимирович",65,"Б21-514","Бизнес-информатика"),
											Student("3314 445366", "Обама","Барак","Владимирович",54,"НАТО","Промышленная кулинария") }, ArrayType);
			stack<Student> test3_1({ Student("3317 567232", "Костяев","Артём","Сергеевич",18,"Б21-514","Программная инженерия"),
									 Student("3314 445366", "Обама","Барак","Владимирович",54,"НАТО","Промышленная кулинария") }, ArrayType);
			stack<Teacher> test3_2({ Teacher("3317 123123", "Камынин","Виталий","Леонидович",67,"Математик",30) ,
									 Teacher("3317 123456", "Джо","Байден","Андреевич",178,"РФ",30) }, ArrayType);
			Assert::IsTrue(test3_s2.IsSubStack(&test3_1) && !test3_s1.IsSubStack(&test3_2), L"stack: wrong answer, test 3");

			//test4
			stack<complex> test4_s1({ complex(1,2), complex(2,3), complex(4,1), complex(7, -10), complex(5,6), complex(-3,2) }, ArrayType);
			stack<complex> expected4_1({ complex(4,1), complex(7, -10), complex(5,6) }, ArrayType);
			stack<complex> test4_1 = *(test4_s1.where([](complex c) {return c.GetAbs() >= 4; }));
			Assert::IsTrue(test4_1 == expected4_1, L"stack: wrong answer, test 4");

			//test5
			stack<int> test6({ 10,7,18,13,-9,-16,3,7,15 }, ArrayType);
			stack<int> expected6({ 100,49,324,169,81,256,9,49,225 }, ArrayType);
			test6.map([](int x) {return x * x; });
			Assert::IsTrue(test6 == expected6, L"stack: wrong answer, test 5");

			//test6
			stack<int> test7({ 1,4,-5,9,-10,12,3,5 }, ArrayType);
			int expected7 = 19;
			int res = test7.reduce([](int a, int b) {return a + b; }, 0);
			Assert::IsTrue(res == expected7, L"queue: wrong answer, test 6");
		}

		TEST_METHOD(SortStationTest) {
			queue<my_pair> test1({ my_pair("t1", 3), my_pair("t2",4), my_pair("t1",2),
				my_pair("t3",1), my_pair("t2",6), my_pair("t2",5) }, ListType);
			queue<my_pair> test2({ my_pair("t1", 12), my_pair("t1",0), my_pair("t1",2),
				my_pair("t3",1), my_pair("t2",8), my_pair("t1",5), my_pair("t7",12) }, ListType);
			queue<my_pair> test3({ my_pair("t1", 3), my_pair("t2",4), my_pair("t1",2),
				my_pair("t3",1) }, ListType);

			queue<my_pair> expected1({ my_pair("t1", 3), my_pair("t1",2), my_pair("t2",4),
				my_pair("t2",6), my_pair("t2",5), my_pair("t3",1) }, ListType);
			queue<my_pair> expected2({ my_pair("t1", 12), my_pair("t1",0), my_pair("t1",2),
				my_pair("t1",5), my_pair("t3",1), my_pair("t2",8), my_pair("t7",12) }, ListType);
			queue<my_pair> expected3({ my_pair("t1", 3), my_pair("t1",2), my_pair("t2",4),
				my_pair("t3",1) }, ListType);
			sort(test1);
			sort(test2);
			sort(test3);
			Assert::IsTrue((test1 == expected1) && (test2 == expected2) && (test3 == expected3),
				L"SortStation: wrong answer, test 1");
		}
		TEST_METHOD(ComplexTest) {
			complex test1(3, 2);
			complex test2(-1, 3);//
			complex test3(4, 2);
			complex test4(7, 1);
			complex test5(-3, 3);
			complex exp1(6,(double)-1/3);
			test1 += test2;
			test1 -= test3;
			test1 *= test4;
			test1 /= test5;
			Assert::IsTrue(test1 == exp1, L"Complex: wrong answer, test 1");
		}
	};
}