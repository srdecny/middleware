// Standard library headers
#include <memory>
#include <iostream>
#include <string>
#include <sstream>
#include <mutex>
#include <functional>
#include <regex>
// Thrift headers
#include <thrift/protocol/TProtocol.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/protocol/TMultiplexedProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>
#include <thrift/server/TServer.h>
#include <thrift/server/TThreadedServer.h>
#include <thrift/processor/TMultiplexedProcessor.h>
#include <thrift/TProcessor.h>
#include <thrift/Thrift.h>

// Generated headers
#include "gen-cpp/Login.h"
#include "gen-cpp/Reports.h"
#include "gen-cpp/Search.h"

using namespace apache::thrift;
using namespace apache::thrift::transport;
using namespace apache::thrift::protocol;
using namespace apache::thrift::server;
using namespace std;

// Not thread-safe. Too bad!
std::set<unsigned> loggedClients;
std::map<unsigned, std::vector<Item>> searchQueries;

// Implementation of the Login service
class LoginHandler: public LoginIf {

    // Each connection gets assigned an id
    // That allows us to see how for each connection, a new handler is used
    unsigned connectionId;

public:
    LoginHandler(unsigned connectionId):
        connectionId(connectionId){}

    void logIn(const std::string& userName, const int32_t key) {
        std::hash<std::string> hasher;
        auto hash = (int32_t)hasher(userName);
        if (hash != key) {
            InvalidKeyException ex;
            ex.invalidKey = key;
            ex.expectedKey = hash;
            throw ex;
        } else {
            cout << "Logged in: " << connectionId << endl;
            loggedClients.insert(connectionId);
        }
    }

    void logOut() {
        cout << "Logged out: " << connectionId << endl;
        loggedClients.erase(connectionId);
    }
};
    
class SearchHandler: public SearchIf {

    unsigned connectionId;
public:
    SearchHandler(unsigned connectionId):
        connectionId(connectionId){}

  void search(SearchState& _return, const std::string& query, const int32_t limit) {
    std::set<std::string> allowedItems { "ItemA", "ItemB", "ItemC", "ItemD"};
    std::vector<std::string> queryItems;

    // One does not simply split a string with a given delimiter, C++ is too powerful for that!
    // Rust, on the other hand... 🦀 https://doc.rust-lang.org/std/string/struct.String.html#method.split 🦀
    std::regex rgx(",");
    std::sregex_token_iterator iter(query.begin(), query.end(), rgx, -1);
    std::sregex_token_iterator end;
    while (iter != end)  {
        queryItems.push_back(*iter);
        if (!allowedItems.count(*iter)) {
            ProtocolException ex;
            ex.message = "Invalid query";
            throw ex;
        } 
        ++iter;
    }

    _return.countEstimate = (int32_t)1 + (rand() % (limit + 1));
    std::vector<Item> queryResults;
    for (int32_t count = 0; count < _return.countEstimate; count++) {
        auto index = (int32_t)(rand() % queryItems.size());
        if (queryItems[index] == "ItemA") {
            ItemA a;
            a.fieldA = (int16_t)rand() % 32;
            a.fieldB = std::vector<int16_t> {(int16_t)rand() % 32, (int16_t)rand() % 32};
            a.fieldC = (int32_t)rand() % 1024;
            Item i;
            i.__set_itemA(a);
            queryResults.push_back(i);
        }
        if (queryItems[index] == "ItemB") {
            ItemB b;
            b.fieldA = std::to_string(rand() % 128);
            auto rand_int = rand() % 128;

            // I wish I knew why it's sufficient to directly assign the set, but the vector has to be assigned with a setter
            b.fieldB = std::set<std::string>{std::to_string(rand_int), std::to_string(rand_int + 1)};
            b.__set_fieldC(std::vector<std::string>{std::to_string(rand_int + 2), std::to_string(rand_int + 2)});
            Item i;
            i.__set_itemB(b);
            queryResults.push_back(i);
        }
        if (queryItems[index] == "ItemC") {
            ItemC c;
            c.fieldA = (bool)rand() % 2;
            Item i;
            i.__set_itemC(c);
            queryResults.push_back(i);
        }
        if (queryItems[index] == "ItemD") {
            ItemD d;
            d.fieldD = (bool)rand() % 2;
            Item i;
            i.__set_itemD(d);
            queryResults.push_back(i);
        }
    }
    searchQueries[connectionId] = queryResults;

    _return.fetchedItems = 0;
    return;
  }
  void fetch(FetchResult& _return, const SearchState& state) {
    if (!searchQueries.count(connectionId)) {
        ProtocolException ex;
        ex.message = "No search query stored!";
        throw ex;
    }

    // All items fetched
    if (state.fetchedItems >= searchQueries[connectionId].size()) {
        _return.state = FetchState::ENDED;
        _return.nextSearchState = state;
        return;
    }

    // Simulate delay, 25%
    if (rand() % 4 == 0) {
        _return.state = FetchState::PENDING;
        _return.nextSearchState = state;
        return;
    }

    // Everything OK
    _return.state = FetchState::ITEMS;
    SearchState newState;
    newState.__set_countEstimate(state.countEstimate);
    newState.__set_fetchedItems(state.fetchedItems);
    newState.__set_multimode(state.multimode);
    // UPDATED PART
    if (state.multimode) {
        std::vector<Item> items;
        // Are we returning last item?
       if (searchQueries[connectionId].size() >= newState.fetchedItems + 2) {
           items.push_back(searchQueries[connectionId][newState.fetchedItems++]);
       }
        items.push_back(searchQueries[connectionId][newState.fetchedItems++]);
        _return.__set_items(items);
    } else {
        _return.__set_item(searchQueries[connectionId][newState.fetchedItems++]);
    }
    
    _return.__set_nextSearchState(newState);
  }
};

class ReportsHandler: public ReportsIf {
    
    unsigned connectionId;
public:
    ReportsHandler(unsigned connectionId):
        connectionId(connectionId){}

    
   bool saveReport(const Report& report) {
        // Skipping the boilerplate implementation, as it's not educational to implement 
        // Just a bunch of boring (and tedious) string manipulation
        return true;

        // Outline of implementation:
        /*
        for (const auto &keyVal : report) {
            std::string expected;
            for (const auto &item: searchQueries[connectionId]) {

                // This has to be much more verbose, because C++
                // ... you get the idea, hopefully.
                if (item[keyVal.first]) {
                    expected += item[keyVal.first] // or join, if it's an array
                }
            }
            if (keyVal.second != expected) {
                return false;
            }
        }

        return true;
        */

   }
};

// This factory creates a new handler for each conection
class PerConnectionExampleProcessorFactory: public TProcessorFactory{
    // We assign each handler an id
    unsigned connectionIdCounter;
    mutex lock;

public:
    PerConnectionExampleProcessorFactory(): connectionIdCounter(0) {}

    // The counter is incremented for each connection
    unsigned assignId() {
        lock_guard<mutex> counterGuard(lock);
        return ++connectionIdCounter;
    }

    // This metod is called for each connection
    virtual std::shared_ptr<TProcessor> getProcessor(const TConnectionInfo& connInfo) {
        // Assign a new id to this connection
        unsigned connectionId = assignId();
        shared_ptr<TMultiplexedProcessor> muxProcessor(new TMultiplexedProcessor());

        shared_ptr<LoginHandler> loginHandler(new LoginHandler(connectionId));
        shared_ptr<TProcessor> loginProcessor(new LoginProcessor(loginHandler));
        muxProcessor->registerProcessor("Login", loginProcessor);

        shared_ptr<SearchHandler> searchHandler(new SearchHandler(connectionId));
        shared_ptr<TProcessor> searchProcessor(new SearchProcessor(searchHandler));
        muxProcessor->registerProcessor("Search", searchProcessor);
        
        shared_ptr<ReportsHandler> reportsHandler(new ReportsHandler(connectionId));
        shared_ptr<TProcessor> reportsProcessor(new ReportsProcessor(reportsHandler));
        muxProcessor->registerProcessor("Reports", reportsProcessor);
        // Use the multiplexed processor
        return muxProcessor;
    }
};

int main(){
    
    try{
        // Accept connections on a TCP socket
        shared_ptr<TServerTransport> serverTransport(new TServerSocket(5000));
        // Use buffering
        shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
        // Use a binary protocol to serialize data
        shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());
        // Use a processor factory to create a processor per connection
        shared_ptr<TProcessorFactory> processorFactory(new PerConnectionExampleProcessorFactory());
        cout << "Started server..." << endl;
        // Start the server
        TThreadedServer server(processorFactory, serverTransport, transportFactory, protocolFactory);
        server.serve();
    }
    catch (TException& tx) {
        cout << "ERROR: " << tx.what() << endl;
    }

}
