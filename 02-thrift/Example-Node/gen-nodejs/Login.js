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

var Login_logIn_args = function(args) {
  this.userName = null;
  this.key = null;
  if (args) {
    if (args.userName !== undefined && args.userName !== null) {
      this.userName = args.userName;
    }
    if (args.key !== undefined && args.key !== null) {
      this.key = args.key;
    }
  }
};
Login_logIn_args.prototype = {};
Login_logIn_args.prototype.read = function(input) {
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
        this.userName = input.readString();
      } else {
        input.skip(ftype);
      }
      break;
      case 2:
      if (ftype == Thrift.Type.I32) {
        this.key = input.readI32();
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

Login_logIn_args.prototype.write = function(output) {
  output.writeStructBegin('Login_logIn_args');
  if (this.userName !== null && this.userName !== undefined) {
    output.writeFieldBegin('userName', Thrift.Type.STRING, 1);
    output.writeString(this.userName);
    output.writeFieldEnd();
  }
  if (this.key !== null && this.key !== undefined) {
    output.writeFieldBegin('key', Thrift.Type.I32, 2);
    output.writeI32(this.key);
    output.writeFieldEnd();
  }
  output.writeFieldStop();
  output.writeStructEnd();
  return;
};

var Login_logIn_result = function(args) {
  this.invalidKeyException = null;
  this.protocolException = null;
  if (args instanceof ttypes.InvalidKeyException) {
    this.invalidKeyException = args;
    return;
  }
  if (args instanceof ttypes.ProtocolException) {
    this.protocolException = args;
    return;
  }
  if (args) {
    if (args.invalidKeyException !== undefined && args.invalidKeyException !== null) {
      this.invalidKeyException = args.invalidKeyException;
    }
    if (args.protocolException !== undefined && args.protocolException !== null) {
      this.protocolException = args.protocolException;
    }
  }
};
Login_logIn_result.prototype = {};
Login_logIn_result.prototype.read = function(input) {
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
        this.invalidKeyException = new ttypes.InvalidKeyException();
        this.invalidKeyException.read(input);
      } else {
        input.skip(ftype);
      }
      break;
      case 2:
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

Login_logIn_result.prototype.write = function(output) {
  output.writeStructBegin('Login_logIn_result');
  if (this.invalidKeyException !== null && this.invalidKeyException !== undefined) {
    output.writeFieldBegin('invalidKeyException', Thrift.Type.STRUCT, 1);
    this.invalidKeyException.write(output);
    output.writeFieldEnd();
  }
  if (this.protocolException !== null && this.protocolException !== undefined) {
    output.writeFieldBegin('protocolException', Thrift.Type.STRUCT, 2);
    this.protocolException.write(output);
    output.writeFieldEnd();
  }
  output.writeFieldStop();
  output.writeStructEnd();
  return;
};

var Login_logOut_args = function(args) {
};
Login_logOut_args.prototype = {};
Login_logOut_args.prototype.read = function(input) {
  input.readStructBegin();
  while (true) {
    var ret = input.readFieldBegin();
    var ftype = ret.ftype;
    if (ftype == Thrift.Type.STOP) {
      break;
    }
    input.skip(ftype);
    input.readFieldEnd();
  }
  input.readStructEnd();
  return;
};

Login_logOut_args.prototype.write = function(output) {
  output.writeStructBegin('Login_logOut_args');
  output.writeFieldStop();
  output.writeStructEnd();
  return;
};

var Login_logOut_result = function(args) {
};
Login_logOut_result.prototype = {};
Login_logOut_result.prototype.read = function(input) {
  input.readStructBegin();
  while (true) {
    var ret = input.readFieldBegin();
    var ftype = ret.ftype;
    if (ftype == Thrift.Type.STOP) {
      break;
    }
    input.skip(ftype);
    input.readFieldEnd();
  }
  input.readStructEnd();
  return;
};

Login_logOut_result.prototype.write = function(output) {
  output.writeStructBegin('Login_logOut_result');
  output.writeFieldStop();
  output.writeStructEnd();
  return;
};

var LoginClient = exports.Client = function(output, pClass) {
  this.output = output;
  this.pClass = pClass;
  this._seqid = 0;
  this._reqs = {};
};
LoginClient.prototype = {};
LoginClient.prototype.seqid = function() { return this._seqid; };
LoginClient.prototype.new_seqid = function() { return this._seqid += 1; };

LoginClient.prototype.logIn = function(userName, key, callback) {
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
    this.send_logIn(userName, key);
    return _defer.promise;
  } else {
    this._reqs[this.seqid()] = callback;
    this.send_logIn(userName, key);
  }
};

LoginClient.prototype.send_logIn = function(userName, key) {
  var output = new this.pClass(this.output);
  var params = {
    userName: userName,
    key: key
  };
  var args = new Login_logIn_args(params);
  try {
    output.writeMessageBegin('logIn', Thrift.MessageType.CALL, this.seqid());
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

LoginClient.prototype.recv_logIn = function(input,mtype,rseqid) {
  var callback = this._reqs[rseqid] || function() {};
  delete this._reqs[rseqid];
  if (mtype == Thrift.MessageType.EXCEPTION) {
    var x = new Thrift.TApplicationException();
    x.read(input);
    input.readMessageEnd();
    return callback(x);
  }
  var result = new Login_logIn_result();
  result.read(input);
  input.readMessageEnd();

  if (null !== result.invalidKeyException) {
    return callback(result.invalidKeyException);
  }
  if (null !== result.protocolException) {
    return callback(result.protocolException);
  }
  callback(null);
};

LoginClient.prototype.logOut = function(callback) {
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
    this.send_logOut();
    return _defer.promise;
  } else {
    this._reqs[this.seqid()] = callback;
    this.send_logOut();
  }
};

LoginClient.prototype.send_logOut = function() {
  var output = new this.pClass(this.output);
  var args = new Login_logOut_args();
  try {
    output.writeMessageBegin('logOut', Thrift.MessageType.ONEWAY, this.seqid());
    args.write(output);
    output.writeMessageEnd();
    this.output.flush();
    var callback = this._reqs[this.seqid()] || function() {};
    delete this._reqs[this.seqid()];
    callback(null);
  }
  catch (e) {
    delete this._reqs[this.seqid()];
    if (typeof output.reset === 'function') {
      output.reset();
    }
    throw e;
  }
};
var LoginProcessor = exports.Processor = function(handler) {
  this._handler = handler;
};
LoginProcessor.prototype.process = function(input, output) {
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
LoginProcessor.prototype.process_logIn = function(seqid, input, output) {
  var args = new Login_logIn_args();
  args.read(input);
  input.readMessageEnd();
  if (this._handler.logIn.length === 2) {
    Q.fcall(this._handler.logIn.bind(this._handler),
      args.userName,
      args.key
    ).then(function(result) {
      var result_obj = new Login_logIn_result({success: result});
      output.writeMessageBegin("logIn", Thrift.MessageType.REPLY, seqid);
      result_obj.write(output);
      output.writeMessageEnd();
      output.flush();
    }).catch(function (err) {
      var result;
      if (err instanceof ttypes.InvalidKeyException || err instanceof ttypes.ProtocolException) {
        result = new Login_logIn_result(err);
        output.writeMessageBegin("logIn", Thrift.MessageType.REPLY, seqid);
      } else {
        result = new Thrift.TApplicationException(Thrift.TApplicationExceptionType.UNKNOWN, err.message);
        output.writeMessageBegin("logIn", Thrift.MessageType.EXCEPTION, seqid);
      }
      result.write(output);
      output.writeMessageEnd();
      output.flush();
    });
  } else {
    this._handler.logIn(args.userName, args.key, function (err, result) {
      var result_obj;
      if ((err === null || typeof err === 'undefined') || err instanceof ttypes.InvalidKeyException || err instanceof ttypes.ProtocolException) {
        result_obj = new Login_logIn_result((err !== null || typeof err === 'undefined') ? err : {success: result});
        output.writeMessageBegin("logIn", Thrift.MessageType.REPLY, seqid);
      } else {
        result_obj = new Thrift.TApplicationException(Thrift.TApplicationExceptionType.UNKNOWN, err.message);
        output.writeMessageBegin("logIn", Thrift.MessageType.EXCEPTION, seqid);
      }
      result_obj.write(output);
      output.writeMessageEnd();
      output.flush();
    });
  }
};
LoginProcessor.prototype.process_logOut = function(seqid, input, output) {
  var args = new Login_logOut_args();
  args.read(input);
  input.readMessageEnd();
  this._handler.logOut();
};
