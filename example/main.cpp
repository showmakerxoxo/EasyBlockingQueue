#include <iostream>
#include <EasyBlockingQueue.h>
#include <chrono>
#include <thread>

int main() {
  EasyBlockingQueue<int> queue(3);

  std::thread producer([&]() {
    for (int i = 0; i < 10; ++i) {
      auto state = queue.offer(i);

      switch (state) {
        case EasyBlockingQueue<int>::State::OK:
          std::cout << "Producer task: " << i << std::endl;
          break;
        case EasyBlockingQueue<int>::State::CLOSED:
          std::cout << "queue is closed, producer exit" << std::endl;
          return;
        default:
          break;
      }
    }

    queue.close();
    //    queue.close(EasyBlockingQueue<int>::ClosePolicy::Immediate);
    std::cout << "Producer completes all tasks" << std::endl;
  });

  std::thread consumer([&]() {
    while (true) {
      int item;
      auto state = queue.take(item);

      switch (state) {
        case EasyBlockingQueue<int>::State::OK:
          std::cout << "consumer task: " << item << " (over: " << queue.size() << ")" << std::endl;
          break;
        case EasyBlockingQueue<int>::State::CLOSED:
          std::cout << "queue is closed, consumer exit" << std::endl;
          return;
        default:
          break;
      }
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
  });

  producer.join();
  consumer.join();
  
  std::cout << "the end ->" << " queue size:" << queue.size() 
            << " is closed: " << (queue.isClosed()) << std::endl;

  return 0;
}