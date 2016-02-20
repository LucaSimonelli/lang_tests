#include <iostream>
#include <thread>
#include <mutex>
#include <algorithm>

int foo(int i) {
  std::cout << "Foo is running: id=" << std::this_thread::get_id() 
            << " i=" << i << std::endl;
  return i;
}

class Task {
  public:
    void operator()() const {
      std::cout << "Task is running: " << std::this_thread::get_id() << std::endl;
    }
};

class ThreadGuard {
  public:
    explicit ThreadGuard(std::thread & aThread) : mThread(aThread) {}
    ~ThreadGuard() {
      if (mThread.joinable()) {
        mThread.join();
      }
    }
    ThreadGuard(ThreadGuard const &)=delete;
    ThreadGuard & operator=(ThreadGuard const &)=delete;
  private:
    std::thread & mThread;
};

int main(int argc, char * argv[]) {
  std::cout << "Test Task" << std::endl;
  unsigned maxNumberOfThreads = std::thread::hardware_concurrency();
  std::cout << maxNumberOfThreads << std::endl;

  std::thread myThread{Task()};
  std::thread myThread2(foo, 3);
  std::thread myLambdaThread([] () {
    std::cout << "Test Lambda Thread" << std::endl;
  });
  ThreadGuard gMyThread(myThread);
  ThreadGuard gMyLambdaThread(myLambdaThread);
  //myLambdaThread.join();
  myThread2.join();
  return 0;
}
