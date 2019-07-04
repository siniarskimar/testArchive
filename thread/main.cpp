#include <iostream>
#include <memory>
#include <thread>
#include <mutex>

std::mutex mutex;

template<typename... Args>
class Thread {
protected:
	std::unique_ptr<std::thread> stl_thread;
public:
	Thread() {}
	Thread(const Thread& other) = delete;

	~Thread() {
		if(joinable())
			join();
	}

	void start(Args... args) {
		stl_thread = std::unique_ptr<std::thread>(new std::thread(&Thread::run, this, args...));
	}

	void join() {
		(*stl_thread).join();
	}
	bool joinable() const { return (*stl_thread).joinable(); }

private:
	virtual void run(Args... args) {};
};

class TestThread : public Thread<> {
private:
	void run() {
		mutex.lock();
		std::cout << std::this_thread::get_id() << std::endl;
		mutex.unlock();
	}
};

int main(int argc, char** argv){

	TestThread threads[50];

	for(int i = 0; i < 50; i++) {
		(threads[i]).start();
	}

	std::cin.get();
	return 0;
}