/**
 * Autogenerated by Thrift Compiler (0.14.1)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef Search_H
#define Search_H

#include <thrift/TDispatchProcessor.h>
#include <thrift/async/TConcurrentClientSyncInfo.h>
#include <memory>
#include "Task_types.h"



#ifdef _MSC_VER
  #pragma warning( push )
  #pragma warning (disable : 4250 ) //inheriting methods via dominance 
#endif

class SearchIf {
 public:
  virtual ~SearchIf() {}
  virtual void search(SearchState& _return, const std::string& query, const int32_t limit) = 0;
  virtual void fetch(FetchResult& _return, const SearchState& state) = 0;
};

class SearchIfFactory {
 public:
  typedef SearchIf Handler;

  virtual ~SearchIfFactory() {}

  virtual SearchIf* getHandler(const ::apache::thrift::TConnectionInfo& connInfo) = 0;
  virtual void releaseHandler(SearchIf* /* handler */) = 0;
};

class SearchIfSingletonFactory : virtual public SearchIfFactory {
 public:
  SearchIfSingletonFactory(const ::std::shared_ptr<SearchIf>& iface) : iface_(iface) {}
  virtual ~SearchIfSingletonFactory() {}

  virtual SearchIf* getHandler(const ::apache::thrift::TConnectionInfo&) {
    return iface_.get();
  }
  virtual void releaseHandler(SearchIf* /* handler */) {}

 protected:
  ::std::shared_ptr<SearchIf> iface_;
};

class SearchNull : virtual public SearchIf {
 public:
  virtual ~SearchNull() {}
  void search(SearchState& /* _return */, const std::string& /* query */, const int32_t /* limit */) {
    return;
  }
  void fetch(FetchResult& /* _return */, const SearchState& /* state */) {
    return;
  }
};

typedef struct _Search_search_args__isset {
  _Search_search_args__isset() : query(false), limit(true) {}
  bool query :1;
  bool limit :1;
} _Search_search_args__isset;

class Search_search_args {
 public:

  Search_search_args(const Search_search_args&);
  Search_search_args& operator=(const Search_search_args&);
  Search_search_args() : query(), limit(100) {
  }

  virtual ~Search_search_args() noexcept;
  std::string query;
  int32_t limit;

  _Search_search_args__isset __isset;

  void __set_query(const std::string& val);

  void __set_limit(const int32_t val);

  bool operator == (const Search_search_args & rhs) const
  {
    if (!(query == rhs.query))
      return false;
    if (!(limit == rhs.limit))
      return false;
    return true;
  }
  bool operator != (const Search_search_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const Search_search_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class Search_search_pargs {
 public:


  virtual ~Search_search_pargs() noexcept;
  const std::string* query;
  const int32_t* limit;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _Search_search_result__isset {
  _Search_search_result__isset() : success(false), protocolException(false) {}
  bool success :1;
  bool protocolException :1;
} _Search_search_result__isset;

class Search_search_result {
 public:

  Search_search_result(const Search_search_result&);
  Search_search_result& operator=(const Search_search_result&);
  Search_search_result() {
  }

  virtual ~Search_search_result() noexcept;
  SearchState success;
  ProtocolException protocolException;

  _Search_search_result__isset __isset;

  void __set_success(const SearchState& val);

  void __set_protocolException(const ProtocolException& val);

  bool operator == (const Search_search_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    if (!(protocolException == rhs.protocolException))
      return false;
    return true;
  }
  bool operator != (const Search_search_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const Search_search_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _Search_search_presult__isset {
  _Search_search_presult__isset() : success(false), protocolException(false) {}
  bool success :1;
  bool protocolException :1;
} _Search_search_presult__isset;

class Search_search_presult {
 public:


  virtual ~Search_search_presult() noexcept;
  SearchState* success;
  ProtocolException protocolException;

  _Search_search_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};


class Search_fetch_args {
 public:

  Search_fetch_args(const Search_fetch_args&);
  Search_fetch_args& operator=(const Search_fetch_args&);
  Search_fetch_args() {
  }

  virtual ~Search_fetch_args() noexcept;
  SearchState state;

  void __set_state(const SearchState& val);

  bool operator == (const Search_fetch_args & rhs) const
  {
    if (!(state == rhs.state))
      return false;
    return true;
  }
  bool operator != (const Search_fetch_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const Search_fetch_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class Search_fetch_pargs {
 public:


  virtual ~Search_fetch_pargs() noexcept;
  const SearchState* state;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _Search_fetch_result__isset {
  _Search_fetch_result__isset() : success(false), protocolException(false) {}
  bool success :1;
  bool protocolException :1;
} _Search_fetch_result__isset;

class Search_fetch_result {
 public:

  Search_fetch_result(const Search_fetch_result&);
  Search_fetch_result& operator=(const Search_fetch_result&);
  Search_fetch_result() {
  }

  virtual ~Search_fetch_result() noexcept;
  FetchResult success;
  ProtocolException protocolException;

  _Search_fetch_result__isset __isset;

  void __set_success(const FetchResult& val);

  void __set_protocolException(const ProtocolException& val);

  bool operator == (const Search_fetch_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    if (!(protocolException == rhs.protocolException))
      return false;
    return true;
  }
  bool operator != (const Search_fetch_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const Search_fetch_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _Search_fetch_presult__isset {
  _Search_fetch_presult__isset() : success(false), protocolException(false) {}
  bool success :1;
  bool protocolException :1;
} _Search_fetch_presult__isset;

class Search_fetch_presult {
 public:


  virtual ~Search_fetch_presult() noexcept;
  FetchResult* success;
  ProtocolException protocolException;

  _Search_fetch_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

class SearchClient : virtual public SearchIf {
 public:
  SearchClient(std::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
    setProtocol(prot);
  }
  SearchClient(std::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, std::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    setProtocol(iprot,oprot);
  }
 private:
  void setProtocol(std::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
  setProtocol(prot,prot);
  }
  void setProtocol(std::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, std::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    piprot_=iprot;
    poprot_=oprot;
    iprot_ = iprot.get();
    oprot_ = oprot.get();
  }
 public:
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> getInputProtocol() {
    return piprot_;
  }
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> getOutputProtocol() {
    return poprot_;
  }
  void search(SearchState& _return, const std::string& query, const int32_t limit);
  void send_search(const std::string& query, const int32_t limit);
  void recv_search(SearchState& _return);
  void fetch(FetchResult& _return, const SearchState& state);
  void send_fetch(const SearchState& state);
  void recv_fetch(FetchResult& _return);
 protected:
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
  ::apache::thrift::protocol::TProtocol* iprot_;
  ::apache::thrift::protocol::TProtocol* oprot_;
};

class SearchProcessor : public ::apache::thrift::TDispatchProcessor {
 protected:
  ::std::shared_ptr<SearchIf> iface_;
  virtual bool dispatchCall(::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, const std::string& fname, int32_t seqid, void* callContext);
 private:
  typedef  void (SearchProcessor::*ProcessFunction)(int32_t, ::apache::thrift::protocol::TProtocol*, ::apache::thrift::protocol::TProtocol*, void*);
  typedef std::map<std::string, ProcessFunction> ProcessMap;
  ProcessMap processMap_;
  void process_search(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_fetch(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
 public:
  SearchProcessor(::std::shared_ptr<SearchIf> iface) :
    iface_(iface) {
    processMap_["search"] = &SearchProcessor::process_search;
    processMap_["fetch"] = &SearchProcessor::process_fetch;
  }

  virtual ~SearchProcessor() {}
};

class SearchProcessorFactory : public ::apache::thrift::TProcessorFactory {
 public:
  SearchProcessorFactory(const ::std::shared_ptr< SearchIfFactory >& handlerFactory) :
      handlerFactory_(handlerFactory) {}

  ::std::shared_ptr< ::apache::thrift::TProcessor > getProcessor(const ::apache::thrift::TConnectionInfo& connInfo);

 protected:
  ::std::shared_ptr< SearchIfFactory > handlerFactory_;
};

class SearchMultiface : virtual public SearchIf {
 public:
  SearchMultiface(std::vector<std::shared_ptr<SearchIf> >& ifaces) : ifaces_(ifaces) {
  }
  virtual ~SearchMultiface() {}
 protected:
  std::vector<std::shared_ptr<SearchIf> > ifaces_;
  SearchMultiface() {}
  void add(::std::shared_ptr<SearchIf> iface) {
    ifaces_.push_back(iface);
  }
 public:
  void search(SearchState& _return, const std::string& query, const int32_t limit) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->search(_return, query, limit);
    }
    ifaces_[i]->search(_return, query, limit);
    return;
  }

  void fetch(FetchResult& _return, const SearchState& state) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->fetch(_return, state);
    }
    ifaces_[i]->fetch(_return, state);
    return;
  }

};

// The 'concurrent' client is a thread safe client that correctly handles
// out of order responses.  It is slower than the regular client, so should
// only be used when you need to share a connection among multiple threads
class SearchConcurrentClient : virtual public SearchIf {
 public:
  SearchConcurrentClient(std::shared_ptr< ::apache::thrift::protocol::TProtocol> prot, std::shared_ptr<::apache::thrift::async::TConcurrentClientSyncInfo> sync) : sync_(sync)
{
    setProtocol(prot);
  }
  SearchConcurrentClient(std::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, std::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot, std::shared_ptr<::apache::thrift::async::TConcurrentClientSyncInfo> sync) : sync_(sync)
{
    setProtocol(iprot,oprot);
  }
 private:
  void setProtocol(std::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
  setProtocol(prot,prot);
  }
  void setProtocol(std::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, std::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    piprot_=iprot;
    poprot_=oprot;
    iprot_ = iprot.get();
    oprot_ = oprot.get();
  }
 public:
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> getInputProtocol() {
    return piprot_;
  }
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> getOutputProtocol() {
    return poprot_;
  }
  void search(SearchState& _return, const std::string& query, const int32_t limit);
  int32_t send_search(const std::string& query, const int32_t limit);
  void recv_search(SearchState& _return, const int32_t seqid);
  void fetch(FetchResult& _return, const SearchState& state);
  int32_t send_fetch(const SearchState& state);
  void recv_fetch(FetchResult& _return, const int32_t seqid);
 protected:
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
  ::apache::thrift::protocol::TProtocol* iprot_;
  ::apache::thrift::protocol::TProtocol* oprot_;
  std::shared_ptr<::apache::thrift::async::TConcurrentClientSyncInfo> sync_;
};

#ifdef _MSC_VER
  #pragma warning( pop )
#endif



#endif
