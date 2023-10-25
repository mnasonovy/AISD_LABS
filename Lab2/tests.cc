#include <gtest/gtest.h>
#include "linked_list.cc"

TEST(LinkedListTest, DefaultConstructor) {
    LinkedList<int> list;

    EXPECT_TRUE(list.isEmpty());
}

TEST(LinkedListTest, CopyConstructor) {
    LinkedList<int> list1;
    list1.push_tail(1);
    list1.push_tail(2);
    list1.push_tail(3);
    LinkedList<int> list2(list1);

    EXPECT_EQ(list1[0], list2[0]);
    EXPECT_EQ(list1[1], list2[1]);
    EXPECT_EQ(list1[2], list2[2]);
}

TEST(LinkedListTest, PushTail) {
    LinkedList<int> list;
    list.push_tail(1);
    list.push_tail(2);

    EXPECT_EQ(list[0], 1);
    EXPECT_EQ(list[1], 2);
}

TEST(LinkedListTest, PushTailOther) {
    LinkedList<int> list1;
    list1.push_tail(1);
    list1.push_tail(2);
    LinkedList<int> list2;
    list2.push_tail(3);
    list2.push_tail(4);
    list1.push_tail(list2);

    EXPECT_EQ(list1[0], 1);
    EXPECT_EQ(list1[1], 2);
    EXPECT_EQ(list1[2], 3);
    EXPECT_EQ(list1[3], 4);
}

TEST(LinkedListTest, PushHead) {
    LinkedList<int> list;
    list.push_head(1);
    list.push_head(2);

    EXPECT_EQ(list[0], 2);
    EXPECT_EQ(list[1], 1);
}

TEST(LinkedListTest, PushHeadOther) {
    LinkedList<int> list1;
    list1.push_head(1);
    list1.push_head(2);
    LinkedList<int> list2;
    list2.push_head(3);
    list2.push_head(4);
    list1.push_head(list2);

    EXPECT_EQ(list1[0], 4);
    EXPECT_EQ(list1[1], 3);
    EXPECT_EQ(list1[2], 2);
    EXPECT_EQ(list1[3], 1);
}

TEST(LinkedListTest, PopHead) {
    LinkedList<int> list;
    list.push_tail(1);
    list.push_tail(2);
    list.pop_head();

    EXPECT_EQ(list[0], 2);
    EXPECT_FALSE(list.isEmpty());
}

TEST(LinkedListTest, PopTail) {
    LinkedList<int> list;
    list.push_tail(1);
    list.push_tail(2);
    list.pop_tail();

    ASSERT_THROW(list[1], std::out_of_range);
}

TEST(LinkedListTest, DeleteNode) {
    LinkedList<int> list;
    list.push_tail(1);
    list.push_tail(2);
    list.push_tail(3);
    list.delete_node(2);

    EXPECT_EQ(list[0], 1);
    EXPECT_EQ(list[1], 3);
}

TEST(LinkedListTest, IndexOperator) {
    LinkedList<int> list;
    list.push_tail(1);
    list.push_tail(2);
    list.push_tail(3);

    EXPECT_EQ(list[0], 1);
    EXPECT_EQ(list[1], 2);
    EXPECT_EQ(list[2], 3);
}

TEST(LinkedListTest, Clear) {
    LinkedList<int> list;
    list.push_tail(1);
    list.push_tail(2);
    list.clear();

    EXPECT_TRUE(list.isEmpty());
}

TEST(HappyNumbersTest, PrintUnhappyNumbers) {
    LinkedList<int> list;

    for (int i = 1; i <21; ++i) {
        list.push_tail(i);
    }

    testing::internal::CaptureStdout();
    HappyNumbers<int>::printUnhappyNumbers(list);
    std::string output = testing::internal::GetCapturedStdout();

    std::string expectedOutput = "2 3 4 5 6 8 9 11 12 14 15 16 17 18 20 \n";
    ASSERT_EQ(output, expectedOutput);
}

