#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <string>
#include <atomic>
#include <vector>
#include <chrono>

struct MyMessage {
    std::string content;
    int thread_id;
};
static std::queue<MyMessage> msgQueue;
static std::mutex stackMutex;
static std::mutex idMutex;
static int idCount = 0;

void helperThread() {
    idMutex.lock();
    int id = ++idCount;
    idMutex.unlock();
    stackMutex.lock();
    msgQueue.push({"hello", id});
    msgQueue.push({"world", id});
    stackMutex.unlock();
}
std::atomic<bool> stopReceiver = false;
void receiverThread() {
    while(true) {
        if(stopReceiver) {
            std::cout << "Stopping the receiver" << std::endl;
            break;
        }
        stackMutex.lock();
        if(!msgQueue.empty()) {
            MyMessage msg = msgQueue.front();
            msgQueue.pop();
            std::cout << msg.thread_id << " " << msg.content << std::endl;
        }
        stackMutex.unlock();
    }
}

int main(int argc, char** argv) {

    {
        std::vector<std::thread*> helperPool;
        int maxHelpers = 10;
        std::cout << "Number of helpers: " << maxHelpers << std::endl;

        for(int i = 0; i < maxHelpers; i++) {
            helperPool.push_back(new std::thread(helperThread));
        }
        std::thread receiver(receiverThread);
        while(true) {
            stackMutex.lock();
            if(msgQueue.empty()) {
                stackMutex.unlock();
                break;
            }
            stackMutex.unlock();
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
        stopReceiver = true;
        receiver.join();
        std::cout << "Receiver is stopped" << std::endl;
        for(int i = 0; i < helperPool.size(); i++) {
            (helperPool[i])->join();
            delete (helperPool[i]);
        }
    }

    std::cin.get();
    return 0;
}