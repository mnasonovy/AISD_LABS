#include <gtest/gtest.h>
#include "linked_list.cc"

    TEST(LinkedListTest, DefaultConstructor) {
        LinkedList<int> list;

        EXPECT_TRUE(list.IsEmpty());
    }

    TEST(LinkedListTest, CopyConstructor) {
        LinkedList<int> list1;
        list1.PushTail(1);
        list1.PushTail(2);
        list1.PushTail(3);
        LinkedList<int> list2{ list1 };

        EXPECT_EQ(list1[0], list2[0]);
        EXPECT_EQ(list1[1], list2[1]);
        EXPECT_EQ(list1[2], list2[2]);
    }


    TEST(LinkedListTest, PushTail) {
        LinkedList<int> list;
        list.PushTail(1);
        list.PushTail(2);

        EXPECT_EQ(list[0], 1);
        EXPECT_EQ(list[1], 2);
    }

 
    TEST(LinkedListTest, PushTailOther) {
        LinkedList<int> list1;
        list1.PushTail(1);
        list1.PushTail(2);
        LinkedList<int> list2;
        list2.PushTail(3);
        list2.PushTail(4);
        list1.PushTail(list2);

        EXPECT_EQ(list1[0], 1);
        EXPECT_EQ(list1[1], 2);
        EXPECT_EQ(list1[2], 3);
        EXPECT_EQ(list1[3], 4);
    }

  
    TEST(LinkedListTest, PushHead) {
        LinkedList<int> list;
        list.PushHead(1);
        list.PushHead(2);

        EXPECT_EQ(list[0], 2);
        EXPECT_EQ(list[1], 1);
    }

    TEST(LinkedListTest, PushHeadOther) {
        LinkedList<int> list1;
        list1.PushHead(1);
        list1.PushHead(2);
        LinkedList<int> list2;
        list2.PushHead(3);
        list2.PushHead(4);
        list1.PushHead(list2);

        EXPECT_EQ(list1[0], 4);
        EXPECT_EQ(list1[1], 3);
        EXPECT_EQ(list1[2], 2);
        EXPECT_EQ(list1[3], 1);
    }


    TEST(LinkedListTest, PopHead) {
        LinkedList<int> list;
        list.PushTail(1);
        list.PushTail(2);
        list.PopHead();

        EXPECT_EQ(list[0], 2);
        EXPECT_FALSE(list.IsEmpty());
    }


    TEST(LinkedListTest, PopTail) {
        LinkedList<int> list;
        list.PushTail(1);
        list.PushTail(2);
        list.PopTail();

        EXPECT_THROW(list[1], std::out_of_range);
    }


    TEST(LinkedListTest, DeleteNode) {
        LinkedList<int> list;
        list.PushTail(1);
        list.PushTail(2);
        list.PushTail(3);
        list.DeleteNode(2);

        EXPECT_EQ(list[0], 1);
        EXPECT_EQ(list[1], 3);
    }


    TEST(LinkedListTest, IndexOperator) {
        LinkedList<int> list;
        list.PushTail(1);
        list.PushTail(2);
        list.PushTail(3);

        EXPECT_EQ(list[0], 1);
        EXPECT_EQ(list[1], 2);
        EXPECT_EQ(list[2], 3);
    }

    TEST(LinkedListTest, Clear) {
        LinkedList<int> list;
        list.PushTail(1);
        list.PushTail(2);
        list.Clear();

        EXPECT_TRUE(list.IsEmpty());
    }

    TEST(HappyNumbersTest, PrintUnhappyNumbers) {
        LinkedList<int> list;

        for (int i = 1; i < 21; ++i) {
            list.PushTail(i);
        }

        testing::internal::CaptureStdout();
        HappyNumbers<int>::PrintUnhappyNumbers(list);
        std::string output = testing::internal::GetCapturedStdout();

        std::string expected_output = "2 3 4 5 6 8 9 11 12 14 15 16 17 18 20 \n";
        EXPECT_EQ(output, expected_output);
    }
