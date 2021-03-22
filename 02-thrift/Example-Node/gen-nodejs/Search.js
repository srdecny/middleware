//
// Autogenerated by Thrift Compiler (0.14.1)
//
// DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
//
"use strict";

var thrift = require('thrift');
var Thrift = thrift.Thrift;
var Q = thrift.Q;
var Int64 = require('node-int64');


var ttypes = require('./Task_types');
//HELPER FUNCTIONS AND STRUCTURES

var Search_search_args = function(args) {
  this.query = null;
  this.limit = 100;
  if (args) {
    if (args.query !== undefined && args.query !== null) {
      this.query = args.query;
    }
    if (args.limit !== undefined && args.limit !== null) {
      this.limit = args.limit;
    }
  }
};
Search_search_args.prototype = {};
Search_search_args.prototype.read = function(input) {
  input.readStructBegin();
  while (true) {
    var ret = input.readFieldBegin();
    var ftype = ret.ftype;
    var fid = ret.fid;
    if (ftype == Thrift.Type.STOP) {
      break;
    }
    switch (fid) {
      case 1:
      if (ftype == Thrift.Type.STRING) {
        this.query = input.readString();
      } else {
        input.skip(ftype);
      }
      break;
      case 2:
      if (ftype == Thrift.Type.I32) {
        this.limit = input.readI32();
      } else {
        input.skip(ftype);
      }
      break;
      default:
        input.skip(ftype);
    }
    input.readFieldEnd();
  }
  input.readStructEnd();
  return;
};

Search_search_args.prototype.write = function(output) {
  output.writeStructBegin('Search_search_args');
  if (this.query !== null && this.query !== undefined) {
    output.writeFieldBegin('query', Thrift.Type.STRING, 1);
    output.writeString(this.query);
    output.writeFieldEnd();
  }
  if (this.limit !== null && this.limit !== undefined) {
    output.writeFieldBegin('limit', Thrift.Type.I32, 2);
    output.writeI32(this.limit);
    output.writeFieldEnd();
  }
  output.writeFieldStop();
  output.writeStructEnd();
  return;
};

var Search_search_result = function(args) {
  this.success = null;
  this.protocolException = null;
  if (args instanceof ttypes.ProtocolException) {
    this.protocolException = args;
    return;
  }
  if (args) {
    if (args.success !== undefined && args.success !== null) {
      this.success = new ttypes.SearchState(args.success);
    }
    if (args.protocolException !== undefined && args.protocolException !== null) {
      this.protocolException = args.protocolException;
    }
  }
};
Search_search_result.prototype = {};
Search_search_result.prototype.read = function(input) {
  input.readStructBegin();
  while (true) {
    var ret = input.readFieldBegin();
    var ftype = ret.ftype;
    var fid = ret.fid;
    if (ftype == Thrift.Type.STOP) {
      break;
    }
    switch (fid) {
      case 0:
      if (ftype == Thrift.Type.STRUCT) {
        this.success = new ttypes.SearchState();
        this.success.read(input);
      } else {
        input.skip(ftype);
      }
      break;
      case 1:
      if (ftype == Thrift.Type.STRUCT) {
        this.protocolException = new ttypes.ProtocolException();
        this.protocolException.read(input);
      } else {
        input.skip(ftype);
      }
      break;
      default:
        input.skip(ftype);
    }
    input.readFieldEnd();
  }
  input.readStructEnd();
  return;
};

Search_search_result.prototype.write = function(output) {
  output.writeStructBegin('Search_search_result');
  if (this.success !== null && this.success !== undefined) {
    output.writeFieldBegin('success', Thrift.Type.STRUCT, 0);
    this.success.write(output);
    output.writeFieldEnd();
  }
  if (this.protocolException !== null && this.protocolException !== undefined) {
    output.writeFieldBegin('protocolException', Thrift.Type.STRUCT, 1);
    this.protocolException.write(output);
    output.writeFieldEnd();
  }
  output.writeFieldStop();
  output.writeStructEnd();
  return;
};

var Search_fetch_args = function(args) {
  this.state = null;
  if (args) {
    if (args.state !== undefined && args.state !== null) {
      this.state = new ttypes.SearchState(args.state);
    } else {
      throw new Thrift.TProtocolException(Thrift.TProtocolExceptionType.UNKNOWN, 'Required field state is unset!');
    }
  }
};
Search_fetch_args.prototype = {};
Search_fetch_args.prototype.read = function(input) {
  input.readStructBegin();
  while (true) {
    var ret = input.readFieldBegin();
    var ftype = ret.ftype;
    var fid = ret.fid;
    if (ftype == Thrift.Type.STOP) {
      break;
    }
    switch (fid) {
      case 1:
      if (ftype == Thrift.Type.STRUCT) {
        this.state = new ttypes.SearchState();
        this.state.read(input);
      } else {
        input.skip(ftype);
      }
      break;
      case 0:
        input.skip(ftype);
        break;
      default:
        input.skip(ftype);
    }
    input.readFieldEnd();
  }
  input.readStructEnd();
  return;
};

Search_fetch_args.prototype.write = function(output) {
  output.writeStructBegin('Search_fetch_args');
  if (this.state !== null && this.state !== undefined) {
    output.writeFieldBegin('state', Thrift.Type.STRUCT, 1);
    this.state.write(output);
    output.writeFieldEnd();
  }
  output.writeFieldStop();
  output.writeStructEnd();
  return;
};

var Search_fetch_result = function(args) {
  this.success = null;
  this.protocolException = null;
  if (args instanceof ttypes.ProtocolException) {
    this.protocolException = args;
    return;
  }
  if (args) {
    if (args.success !== undefined && args.success !== null) {
      this.success = new ttypes.FetchResult(args.success);
    }
    if (args.protocolException !== undefined && args.protocolException !== null) {
      this.protocolException = args.protocolException;
    }
  }
};
Search_fetch_result.prototype = {};
Search_fetch_result.prototype.read = function(input) {
  input.readStructBegin();
  while (true) {
    var ret = input.readFieldBegin();
    var ftype = ret.ftype;
    var fid = ret.fid;
    if (ftype == Thrift.Type.STOP) {
      break;
    }
    switch (fid) {
      case 0:
      if (ftype == Thrift.Type.STRUCT) {
        this.success = new ttypes.FetchResult();
        this.success.read(input);
      } else {
        input.skip(ftype);
      }
      break;
      case 1:
      if (ftype == Thrift.Type.STRUCT) {
        this.protocolException = new ttypes.ProtocolException();
        this.protocolException.read(input);
      } else {
        input.skip(ftype);
      }
      break;
      default:
        input.skip(ftype);
    }
    input.readFieldEnd();
  }
  input.readStructEnd();
  return;
};

Search_fetch_result.prototype.write = function(output) {
  output.writeStructBegin('Search_fetch_result');
  if (this.success !== null && this.success !== undefined) {
    output.writeFieldBegin('success', Thrift.Type.STRUCT, 0);
    this.success.write(output);
    output.writeFieldEnd();
  }
  if (this.protocolException !== null && this.protocolException !== undefined) {
    output.writeFieldBegin('protocolException', Thrift.Type.STRUCT, 1);
    this.protocolException.write(output);
    output.writeFieldEnd();
  }
  output.writeFieldStop();
  output.writeStructEnd();
  return;
};

var SearchClient = exports.Client = function(output, pClass) {
  this.output = output;
  this.pClass = pClass;
  this._seqid = 0;
  this._reqs = {};
};
SearchClient.prototype = {};
SearchClient.prototype.seqid = function() { return this._seqid; };
SearchClient.prototype.new_seqid = function() { return this._seqid += 1; };

SearchClient.prototype.search = function(query, limit, callback) {
  this._seqid = this.new_seqid();
  if (callback === undefined) {
    var _defer = Q.defer();
    this._reqs[this.seqid()] = function(error, result) {
      if (error) {
        _defer.reject(error);
      } else {
        _defer.resolve(result);
      }
    };
    this.send_search(query, limit);
    return _defer.promise;
  } else {
    this._reqs[this.seqid()] = callback;
    this.send_search(query, limit);
  }
};

SearchClient.prototype.send_search = function(query, limit) {
  var output = new this.pClass(this.output);
  var params = {
    query: query,
    limit: limit
  };
  var args = new Search_search_args(params);
  try {
    output.writeMessageBegin('search', Thrift.MessageType.CALL, this.seqid());
    args.write(output);
    output.writeMessageEnd();
    return this.output.flush();
  }
  catch (e) {
    delete this._reqs[this.seqid()];
    if (typeof output.reset === 'function') {
      output.reset();
    }
    throw e;
  }
};

SearchClient.prototype.recv_search = function(input,mtype,rseqid) {
  var callback = this._reqs[rseqid] || function() {};
  delete this._reqs[rseqid];
  if (mtype == Thrift.MessageType.EXCEPTION) {
    var x = new Thrift.TApplicationException();
    x.read(input);
    input.readMessageEnd();
    return callback(x);
  }
  var result = new Search_search_result();
  result.read(input);
  input.readMessageEnd();

  if (null !== result.protocolException) {
    return callback(result.protocolException);
  }
  if (null !== result.success) {
    return callback(null, result.success);
  }
  return callback('search failed: unknown result');
};

SearchClient.prototype.fetch = function(state, callback) {
  this._seqid = this.new_seqid();
  if (callback === undefined) {
    var _defer = Q.defer();
    this._reqs[this.seqid()] = function(error, result) {
      if (error) {
        _defer.reject(error);
      } else {
        _defer.resolve(result);
      }
    };
    this.send_fetch(state);
    return _defer.promise;
  } else {
    this._reqs[this.seqid()] = callback;
    this.send_fetch(state);
  }
};

SearchClient.prototype.send_fetch = function(state) {
  var output = new this.pClass(this.output);
  var params = {
    state: state
  };
  var args = new Search_fetch_args(params);
  try {
    output.writeMessageBegin('fetch', Thrift.MessageType.CALL, this.seqid());
    args.write(output);
    output.writeMessageEnd();
    return this.output.flush();
  }
  catch (e) {
    delete this._reqs[this.seqid()];
    if (typeof output.reset === 'function') {
      output.reset();
    }
    throw e;
  }
};

SearchClient.prototype.recv_fetch = function(input,mtype,rseqid) {
  var callback = this._reqs[rseqid] || function() {};
  delete this._reqs[rseqid];
  if (mtype == Thrift.MessageType.EXCEPTION) {
    var x = new Thrift.TApplicationException();
    x.read(input);
    input.readMessageEnd();
    return callback(x);
  }
  var result = new Search_fetch_result();
  result.read(input);
  input.readMessageEnd();

  if (null !== result.protocolException) {
    return callback(result.protocolException);
  }
  if (null !== result.success) {
    return callback(null, result.success);
  }
  return callback('fetch failed: unknown result');
};
var SearchProcessor = exports.Processor = function(handler) {
  this._handler = handler;
};
SearchProcessor.prototype.process = function(input, output) {
  var r = input.readMessageBegin();
  if (this['process_' + r.fname]) {
    return this['process_' + r.fname].call(this, r.rseqid, input, output);
  } else {
    input.skip(Thrift.Type.STRUCT);
    input.readMessageEnd();
    var x = new Thrift.TApplicationException(Thrift.TApplicationExceptionType.UNKNOWN_METHOD, 'Unknown function ' + r.fname);
    output.writeMessageBegin(r.fname, Thrift.MessageType.EXCEPTION, r.rseqid);
    x.write(output);
    output.writeMessageEnd();
    output.flush();
  }
};
SearchProcessor.prototype.process_search = function(seqid, input, output) {
  var args = new Search_search_args();
  args.read(input);
  input.readMessageEnd();
  if (this._handler.search.length === 2) {
    Q.fcall(this._handler.search.bind(this._handler),
      args.query,
      args.limit
    ).then(function(result) {
      var result_obj = new Search_search_result({success: result});
      output.writeMessageBegin("search", Thrift.MessageType.REPLY, seqid);
      result_obj.write(output);
      output.writeMessageEnd();
      output.flush();
    }).catch(function (err) {
      var result;
      if (err instanceof ttypes.ProtocolException) {
        result = new Search_search_result(err);
        output.writeMessageBegin("search", Thrift.MessageType.REPLY, seqid);
      } else {
        result = new Thrift.TApplicationException(Thrift.TApplicationExceptionType.UNKNOWN, err.message);
        output.writeMessageBegin("search", Thrift.MessageType.EXCEPTION, seqid);
      }
      result.write(output);
      output.writeMessageEnd();
      output.flush();
    });
  } else {
    this._handler.search(args.query, args.limit, function (err, result) {
      var result_obj;
      if ((err === null || typeof err === 'undefined') || err instanceof ttypes.ProtocolException) {
        result_obj = new Search_search_result((err !== null || typeof err === 'undefined') ? err : {success: result});
        output.writeMessageBegin("search", Thrift.MessageType.REPLY, seqid);
      } else {
        result_obj = new Thrift.TApplicationException(Thrift.TApplicationExceptionType.UNKNOWN, err.message);
        output.writeMessageBegin("search", Thrift.MessageType.EXCEPTION, seqid);
      }
      result_obj.write(output);
      output.writeMessageEnd();
      output.flush();
    });
  }
};
SearchProcessor.prototype.process_fetch = function(seqid, input, output) {
  var args = new Search_fetch_args();
  args.read(input);
  input.readMessageEnd();
  if (this._handler.fetch.length === 1) {
    Q.fcall(this._handler.fetch.bind(this._handler),
      args.state
    ).then(function(result) {
      var result_obj = new Search_fetch_result({success: result});
      output.writeMessageBegin("fetch", Thrift.MessageType.REPLY, seqid);
      result_obj.write(output);
      output.writeMessageEnd();
      output.flush();
    }).catch(function (err) {
      var result;
      if (err instanceof ttypes.ProtocolException) {
        result = new Search_fetch_result(err);
        output.writeMessageBegin("fetch", Thrift.MessageType.REPLY, seqid);
      } else {
        result = new Thrift.TApplicationException(Thrift.TApplicationExceptionType.UNKNOWN, err.message);
        output.writeMessageBegin("fetch", Thrift.MessageType.EXCEPTION, seqid);
      }
      result.write(output);
      output.writeMessageEnd();
      output.flush();
    });
  } else {
    this._handler.fetch(args.state, function (err, result) {
      var result_obj;
      if ((err === null || typeof err === 'undefined') || err instanceof ttypes.ProtocolException) {
        result_obj = new Search_fetch_result((err !== null || typeof err === 'undefined') ? err : {success: result});
        output.writeMessageBegin("fetch", Thrift.MessageType.REPLY, seqid);
      } else {
        result_obj = new Thrift.TApplicationException(Thrift.TApplicationExceptionType.UNKNOWN, err.message);
        output.writeMessageBegin("fetch", Thrift.MessageType.EXCEPTION, seqid);
      }
      result_obj.write(output);
      output.writeMessageEnd();
      output.flush();
    });
  }
};
