#include "gtest/gtest.h"
#include <EasyBlockingQueue.h>
#include <atomic>
#include <thread>

TEST(EasyBlockingQueueTest, Constructor) {
  EasyBlockingQueue<int> unboundedQueue;
  EXPECT_EQ(0, unboundedQueue.size());
  EXPECT_FALSE(unboundedQueue.isClosed());

  EasyBlockingQueue<std::string> boundedQueue(5);
  EXPECT_EQ(0, boundedQueue.size());
  EXPECT_FALSE(boundedQueue.isClosed());
}

TEST(EasyBlockingQueueTest, BasicOfferTake) {
  EasyBlockingQueue<int> queue(2);

  EXPECT_EQ(queue.offer(1), EasyBlockingQueue<int>::State::OK);
  EXPECT_EQ(queue.size(), 1);

  int val = 0;
  EXPECT_EQ(queue.take(val), EasyBlockingQueue<int>::State::OK);
  EXPECT_EQ(val, 1);
  EXPECT_EQ(queue.size(), 0);
}

TEST(EasyBlockingQueueTest, CloseBehavior) {
  EasyBlockingQueue<int> queue;

  queue.close();
  EXPECT_TRUE(queue.isClosed());
  EXPECT_EQ(queue.offer(1), EasyBlockingQueue<int>::State::CLOSED);

  int val;
  EXPECT_EQ(queue.take(val), EasyBlockingQueue<int>::State::CLOSED);
}

TEST(EasyBlockingQueueTest, EmplaceSupport) {
  struct TestStruct {
    int a;
    double b;
    TestStruct(int a, double b) : a(a), b(b) {}
  };

  EasyBlockingQueue<TestStruct> queue;

  EXPECT_EQ(queue.emplace(42, 3.14), EasyBlockingQueue<TestStruct>::State::OK);

  TestStruct item{0, 0};
  ASSERT_EQ(queue.take(item), EasyBlockingQueue<TestStruct>::State::OK);
  EXPECT_EQ(item.a, 42);
  EXPECT_DOUBLE_EQ(item.b, 3.14);
}

TEST(EasyBlockingQueueTest, PopOperation) {
  EasyBlockingQueue<int> queue(2);

  queue.offer(1);
  queue.offer(2);

  EXPECT_EQ(queue.pop(), EasyBlockingQueue<int>::State::OK);
  EXPECT_EQ(queue.size(), 1);

  // queue.close(EasyBlockingQueue<int>::ClosePolicy::Immediate);
  // EXPECT_EQ(queue.pop(), EasyBlockingQueue<int>::State::CLOSED);

  queue.close();
  EXPECT_EQ(queue.pop(), EasyBlockingQueue<int>::State::OK);
}

TEST(EasyBlockingQueueTest, MultiThreadBlocking) {
  EasyBlockingQueue<int> queue(1);
  std::atomic<bool> producer_blocked{false};
  std::atomic<bool> consumer_blocked{false};

  auto producer = [&queue, &producer_blocked]() {
    EXPECT_EQ(queue.offer(1), EasyBlockingQueue<int>::State::OK);

    auto state = queue.offer(2);
    producer_blocked.store(true);
  };

  auto consumer = [&queue, &consumer_blocked]() {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    int item;
    auto state = queue.take(item);
    consumer_blocked = (state == EasyBlockingQueue<int>::State::OK);

    EXPECT_EQ(item, 1);
  };

  std::thread t1(producer);
  std::thread t2(consumer);

  t1.join();
  t2.join();

  EXPECT_TRUE(producer_blocked);
  EXPECT_TRUE(consumer_blocked);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}