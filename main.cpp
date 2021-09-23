#include "server.h"
using namespace std;

int main(int, char *[]) {
    short port = 8031;
    boost::asio::io_service io_service;
    Server server(port, io_service);
    io_service.run();
/*
    Server S;
    cout << S.receive("INSERT A 0 lean") << endl;
    cout << S.receive("INSERT A 0 understand") << endl;
    cout << S.receive("INSERT A 1 sweater")<< endl;
    cout << S.receive("INSERT A 2 frank")<< endl;
    cout << S.receive("INSERT A 3 violation")<< endl;
    cout << S.receive("INSERT A 4 quality")<< endl;
    cout << S.receive("INSERT A 5 precision")<< endl;

    cout << S.receive("INSERT B 3 proposal")<< endl;
    cout << S.receive("INSERT B 4 example")<< endl;
    cout << S.receive("INSERT B 5 lake")<< endl;
    cout << S.receive("INSERT B 6 flour")<< endl;
    cout << S.receive("INSERT B 7 wonder")<< endl;
    cout << S.receive("INSERT B 8 selection")<< endl;
    cout << S.receive("INTERSECTION")<< endl;
    cout << S.receive("SYMMETRIC_DIFFERENCE")<< endl;
    cout << S.receive("TRUNCATE A")<< endl;
*/
    return 0;
}