#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Request {
    Request(int arrival_time, int process_time):
        arrival_time(arrival_time),
        process_time(process_time)
    {}

    int arrival_time;
    int process_time;
};

struct Response {
    Response(bool dropped, int start_time):
        dropped(dropped),
        start_time(start_time)
    {}

    bool dropped;
    int start_time;
};

class Buffer {
    public:
        Buffer(int size):
            size_(size),
            finish_time()
        {}

        Response Process(const Request &request) {
            Response res(false, 0);
            if (finish_time.empty()) {
                finish_time.push(request.arrival_time + request.process_time);
                res.start_time = request.arrival_time;
            }
            else {
                if (request.arrival_time >= finish_time.front()) {
                    finish_time.pop();
                }

                if (finish_time.size() == size_) {                 
                        res.dropped = true;                 
                }
                else if(finish_time.empty()) {
                    finish_time.push(request.arrival_time + request.process_time);
                    res.start_time = request.arrival_time;                       
                }
                else {
                    res.start_time = finish_time.back();
                    finish_time.push(finish_time.back() + request.process_time);                 
                }                
            }
            return res;
        }
    private:
        int size_;
        queue <int> finish_time;
};

vector <Request> ReadRequests() {
    vector <Request> requests;
    int num_request;
    cin >> num_request;
    for (int i = 0; i < num_request; i++) {
        int arrival_time, process_time;
        cin >> arrival_time >> process_time;
        requests.push_back(Request(arrival_time, process_time));
    }
    return requests;
}

vector <Response> ProcessRequests(const vector <Request> &requests, Buffer *buffer) {
    vector <Response> responses;
    for (int i = 0; i < requests.size(); i++) {
        responses.push_back(buffer->Process(requests[i]));
    }     
    return responses;
}

void PrintResponses(const std::vector <Response> &responses) {
    for (int i = 0; i < responses.size(); i++) {
        cout << (responses[i].dropped ? -1 : responses[i].start_time) << endl;
    }        
}

int main() {
    int size;
    cin >> size;
    vector <Request> requests = ReadRequests();

    Buffer buffer(size);
    vector <Response> responses = ProcessRequests(requests, &buffer);

    PrintResponses(responses);
    return 0;
}
