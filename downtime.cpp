#include <iostream>
#include <vector>
using namespace std;

class Server {
    private:
    vector<int> startTime;
    int currentSlot = 0;
    public:
    Server(int capacity) {
        for(int i = 0; i < capacity; i++) {
            startTime.push_back(-1000);
        }
    }
    bool handleRequest(int timeStamp) {
       if(timeStamp - startTime[currentSlot] >= 1000) {
           startTime[currentSlot] = timeStamp;
           currentSlot = ++currentSlot >= startTime.size() ? 0 : currentSlot;
           return true;
       }
       return false;
    }
};

class ServerPool {
    private:
    vector<Server> servers;
    int serverCapacity;
    int startIndex = 0;

    public:
    ServerPool(int serverCapacity) {
        this->servers.push_back(Server(serverCapacity));
        this->serverCapacity = serverCapacity;
    }

    void handleRequest(int timestamp) {
        bool requestHandled = false;
        
        int currentIndex = startIndex;
       
        requestHandled = servers[currentIndex].handleRequest(timestamp);
        if(requestHandled) {
           startIndex = currentIndex;
           return;
        }
        int nextIndex = currentIndex + 1 > servers.size()-1 ? 0 : currentIndex + 1;
        requestHandled = servers[nextIndex].handleRequest(timestamp);
        if(requestHandled) {
            startIndex = nextIndex;
            return;
        }
        this->servers.push_back(Server(serverCapacity));
        servers.back().handleRequest(timestamp);
        startIndex = servers.size()-1;       
    }

    int getServersRequired(void) {
        return servers.size();
    }

};

int main(void) {
    int numRequests;
    int serverCapacity;
    cin >> numRequests;
    cin >> serverCapacity;
    int requests[100000];
    int index = 0;
    for(int i = 0; i < numRequests; i++) {
        cin >> requests[i];
    }
    ServerPool pool(serverCapacity);
    while(index < numRequests) {
        pool.handleRequest(requests[index]);
        index++;
    }

    cout << pool.getServersRequired();
    return 0;
}