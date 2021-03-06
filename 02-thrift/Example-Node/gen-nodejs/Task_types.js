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


var ttypes = module.exports = {};
ttypes.FetchState = {
  'PENDING' : 1,
  'ITEMS' : 2,
  'ENDED' : 3
};
var InvalidKeyException = module.exports.InvalidKeyException = function(args) {
  Thrift.TException.call(this, "InvalidKeyException");
  this.name = "InvalidKeyException";
  this.invalidKey = null;
  this.expectedKey = null;
  if (args) {
    if (args.invalidKey !== undefined && args.invalidKey !== null) {
      this.invalidKey = args.invalidKey;
    }
    if (args.expectedKey !== undefined && args.expectedKey !== null) {
      this.expectedKey = args.expectedKey;
    }
  }
};
Thrift.inherits(InvalidKeyException, Thrift.TException);
InvalidKeyException.prototype.name = 'InvalidKeyException';
InvalidKeyException.prototype.read = function(input) {
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
      if (ftype == Thrift.Type.I32) {
        this.invalidKey = input.readI32();
      } else {
        input.skip(ftype);
      }
      break;
      case 2:
      if (ftype == Thrift.Type.I32) {
        this.expectedKey = input.readI32();
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

InvalidKeyException.prototype.write = function(output) {
  output.writeStructBegin('InvalidKeyException');
  if (this.invalidKey !== null && this.invalidKey !== undefined) {
    output.writeFieldBegin('invalidKey', Thrift.Type.I32, 1);
    output.writeI32(this.invalidKey);
    output.writeFieldEnd();
  }
  if (this.expectedKey !== null && this.expectedKey !== undefined) {
    output.writeFieldBegin('expectedKey', Thrift.Type.I32, 2);
    output.writeI32(this.expectedKey);
    output.writeFieldEnd();
  }
  output.writeFieldStop();
  output.writeStructEnd();
  return;
};

var ProtocolException = module.exports.ProtocolException = function(args) {
  Thrift.TException.call(this, "ProtocolException");
  this.name = "ProtocolException";
  this.message = null;
  if (args) {
    if (args.message !== undefined && args.message !== null) {
      this.message = args.message;
    }
  }
};
Thrift.inherits(ProtocolException, Thrift.TException);
ProtocolException.prototype.name = 'ProtocolException';
ProtocolException.prototype.read = function(input) {
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
        this.message = input.readString();
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

ProtocolException.prototype.write = function(output) {
  output.writeStructBegin('ProtocolException');
  if (this.message !== null && this.message !== undefined) {
    output.writeFieldBegin('message', Thrift.Type.STRING, 1);
    output.writeString(this.message);
    output.writeFieldEnd();
  }
  output.writeFieldStop();
  output.writeStructEnd();
  return;
};

var ItemA = module.exports.ItemA = function(args) {
  this.fieldA = null;
  this.fieldB = null;
  this.fieldC = null;
  if (args) {
    if (args.fieldA !== undefined && args.fieldA !== null) {
      this.fieldA = args.fieldA;
    } else {
      throw new Thrift.TProtocolException(Thrift.TProtocolExceptionType.UNKNOWN, 'Required field fieldA is unset!');
    }
    if (args.fieldB !== undefined && args.fieldB !== null) {
      this.fieldB = Thrift.copyList(args.fieldB, [null]);
    } else {
      throw new Thrift.TProtocolException(Thrift.TProtocolExceptionType.UNKNOWN, 'Required field fieldB is unset!');
    }
    if (args.fieldC !== undefined && args.fieldC !== null) {
      this.fieldC = args.fieldC;
    } else {
      throw new Thrift.TProtocolException(Thrift.TProtocolExceptionType.UNKNOWN, 'Required field fieldC is unset!');
    }
  }
};
ItemA.prototype = {};
ItemA.prototype.read = function(input) {
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
      if (ftype == Thrift.Type.I16) {
        this.fieldA = input.readI16();
      } else {
        input.skip(ftype);
      }
      break;
      case 2:
      if (ftype == Thrift.Type.LIST) {
        this.fieldB = [];
        var _rtmp31 = input.readListBegin();
        var _size0 = _rtmp31.size || 0;
        for (var _i2 = 0; _i2 < _size0; ++_i2) {
          var elem3 = null;
          elem3 = input.readI16();
          this.fieldB.push(elem3);
        }
        input.readListEnd();
      } else {
        input.skip(ftype);
      }
      break;
      case 3:
      if (ftype == Thrift.Type.I32) {
        this.fieldC = input.readI32();
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

ItemA.prototype.write = function(output) {
  output.writeStructBegin('ItemA');
  if (this.fieldA !== null && this.fieldA !== undefined) {
    output.writeFieldBegin('fieldA', Thrift.Type.I16, 1);
    output.writeI16(this.fieldA);
    output.writeFieldEnd();
  }
  if (this.fieldB !== null && this.fieldB !== undefined) {
    output.writeFieldBegin('fieldB', Thrift.Type.LIST, 2);
    output.writeListBegin(Thrift.Type.I16, this.fieldB.length);
    for (var iter4 in this.fieldB) {
      if (this.fieldB.hasOwnProperty(iter4)) {
        iter4 = this.fieldB[iter4];
        output.writeI16(iter4);
      }
    }
    output.writeListEnd();
    output.writeFieldEnd();
  }
  if (this.fieldC !== null && this.fieldC !== undefined) {
    output.writeFieldBegin('fieldC', Thrift.Type.I32, 3);
    output.writeI32(this.fieldC);
    output.writeFieldEnd();
  }
  output.writeFieldStop();
  output.writeStructEnd();
  return;
};

var ItemB = module.exports.ItemB = function(args) {
  this.fieldA = null;
  this.fieldB = null;
  this.fieldC = null;
  if (args) {
    if (args.fieldA !== undefined && args.fieldA !== null) {
      this.fieldA = args.fieldA;
    }
    if (args.fieldB !== undefined && args.fieldB !== null) {
      this.fieldB = Thrift.copyList(args.fieldB, [null]);
    }
    if (args.fieldC !== undefined && args.fieldC !== null) {
      this.fieldC = Thrift.copyList(args.fieldC, [null]);
    }
  }
};
ItemB.prototype = {};
ItemB.prototype.read = function(input) {
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
        this.fieldA = input.readString();
      } else {
        input.skip(ftype);
      }
      break;
      case 2:
      if (ftype == Thrift.Type.SET) {
        this.fieldB = [];
        var _rtmp36 = input.readSetBegin();
        var _size5 = _rtmp36.size || 0;
        for (var _i7 = 0; _i7 < _size5; ++_i7) {
          var elem8 = null;
          elem8 = input.readString();
          this.fieldB.push(elem8);
        }
        input.readSetEnd();
      } else {
        input.skip(ftype);
      }
      break;
      case 3:
      if (ftype == Thrift.Type.LIST) {
        this.fieldC = [];
        var _rtmp310 = input.readListBegin();
        var _size9 = _rtmp310.size || 0;
        for (var _i11 = 0; _i11 < _size9; ++_i11) {
          var elem12 = null;
          elem12 = input.readString();
          this.fieldC.push(elem12);
        }
        input.readListEnd();
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

ItemB.prototype.write = function(output) {
  output.writeStructBegin('ItemB');
  if (this.fieldA !== null && this.fieldA !== undefined) {
    output.writeFieldBegin('fieldA', Thrift.Type.STRING, 1);
    output.writeString(this.fieldA);
    output.writeFieldEnd();
  }
  if (this.fieldB !== null && this.fieldB !== undefined) {
    output.writeFieldBegin('fieldB', Thrift.Type.SET, 2);
    output.writeSetBegin(Thrift.Type.STRING, this.fieldB.length);
    for (var iter13 in this.fieldB) {
      if (this.fieldB.hasOwnProperty(iter13)) {
        iter13 = this.fieldB[iter13];
        output.writeString(iter13);
      }
    }
    output.writeSetEnd();
    output.writeFieldEnd();
  }
  if (this.fieldC !== null && this.fieldC !== undefined) {
    output.writeFieldBegin('fieldC', Thrift.Type.LIST, 3);
    output.writeListBegin(Thrift.Type.STRING, this.fieldC.length);
    for (var iter14 in this.fieldC) {
      if (this.fieldC.hasOwnProperty(iter14)) {
        iter14 = this.fieldC[iter14];
        output.writeString(iter14);
      }
    }
    output.writeListEnd();
    output.writeFieldEnd();
  }
  output.writeFieldStop();
  output.writeStructEnd();
  return;
};

var ItemC = module.exports.ItemC = function(args) {
  this.fieldA = null;
  if (args) {
    if (args.fieldA !== undefined && args.fieldA !== null) {
      this.fieldA = args.fieldA;
    }
  }
};
ItemC.prototype = {};
ItemC.prototype.read = function(input) {
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
      if (ftype == Thrift.Type.BOOL) {
        this.fieldA = input.readBool();
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

ItemC.prototype.write = function(output) {
  output.writeStructBegin('ItemC');
  if (this.fieldA !== null && this.fieldA !== undefined) {
    output.writeFieldBegin('fieldA', Thrift.Type.BOOL, 1);
    output.writeBool(this.fieldA);
    output.writeFieldEnd();
  }
  output.writeFieldStop();
  output.writeStructEnd();
  return;
};

var ItemD = module.exports.ItemD = function(args) {
  this.fieldD = null;
  if (args) {
    if (args.fieldD !== undefined && args.fieldD !== null) {
      this.fieldD = args.fieldD;
    }
  }
};
ItemD.prototype = {};
ItemD.prototype.read = function(input) {
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
      if (ftype == Thrift.Type.BOOL) {
        this.fieldD = input.readBool();
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

ItemD.prototype.write = function(output) {
  output.writeStructBegin('ItemD');
  if (this.fieldD !== null && this.fieldD !== undefined) {
    output.writeFieldBegin('fieldD', Thrift.Type.BOOL, 1);
    output.writeBool(this.fieldD);
    output.writeFieldEnd();
  }
  output.writeFieldStop();
  output.writeStructEnd();
  return;
};

var Item = module.exports.Item = function(args) {
  this.itemA = null;
  this.itemB = null;
  this.itemC = null;
  this.itemD = null;
  if (args) {
    if (args.itemA !== undefined && args.itemA !== null) {
      this.itemA = new ttypes.ItemA(args.itemA);
    }
    if (args.itemB !== undefined && args.itemB !== null) {
      this.itemB = new ttypes.ItemB(args.itemB);
    }
    if (args.itemC !== undefined && args.itemC !== null) {
      this.itemC = new ttypes.ItemC(args.itemC);
    }
    if (args.itemD !== undefined && args.itemD !== null) {
      this.itemD = new ttypes.ItemD(args.itemD);
    }
  }
};
Item.prototype = {};
Item.prototype.read = function(input) {
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
        this.itemA = new ttypes.ItemA();
        this.itemA.read(input);
      } else {
        input.skip(ftype);
      }
      break;
      case 2:
      if (ftype == Thrift.Type.STRUCT) {
        this.itemB = new ttypes.ItemB();
        this.itemB.read(input);
      } else {
        input.skip(ftype);
      }
      break;
      case 3:
      if (ftype == Thrift.Type.STRUCT) {
        this.itemC = new ttypes.ItemC();
        this.itemC.read(input);
      } else {
        input.skip(ftype);
      }
      break;
      case 4:
      if (ftype == Thrift.Type.STRUCT) {
        this.itemD = new ttypes.ItemD();
        this.itemD.read(input);
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

Item.prototype.write = function(output) {
  output.writeStructBegin('Item');
  if (this.itemA !== null && this.itemA !== undefined) {
    output.writeFieldBegin('itemA', Thrift.Type.STRUCT, 1);
    this.itemA.write(output);
    output.writeFieldEnd();
  }
  if (this.itemB !== null && this.itemB !== undefined) {
    output.writeFieldBegin('itemB', Thrift.Type.STRUCT, 2);
    this.itemB.write(output);
    output.writeFieldEnd();
  }
  if (this.itemC !== null && this.itemC !== undefined) {
    output.writeFieldBegin('itemC', Thrift.Type.STRUCT, 3);
    this.itemC.write(output);
    output.writeFieldEnd();
  }
  if (this.itemD !== null && this.itemD !== undefined) {
    output.writeFieldBegin('itemD', Thrift.Type.STRUCT, 4);
    this.itemD.write(output);
    output.writeFieldEnd();
  }
  output.writeFieldStop();
  output.writeStructEnd();
  return;
};

var SearchState = module.exports.SearchState = function(args) {
  this.countEstimate = null;
  this.fetchedItems = null;
  this.multimode = false;
  if (args) {
    if (args.countEstimate !== undefined && args.countEstimate !== null) {
      this.countEstimate = args.countEstimate;
    }
    if (args.fetchedItems !== undefined && args.fetchedItems !== null) {
      this.fetchedItems = args.fetchedItems;
    }
    if (args.multimode !== undefined && args.multimode !== null) {
      this.multimode = args.multimode;
    }
  }
};
SearchState.prototype = {};
SearchState.prototype.read = function(input) {
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
      if (ftype == Thrift.Type.I32) {
        this.countEstimate = input.readI32();
      } else {
        input.skip(ftype);
      }
      break;
      case 2:
      if (ftype == Thrift.Type.I32) {
        this.fetchedItems = input.readI32();
      } else {
        input.skip(ftype);
      }
      break;
      case 3:
      if (ftype == Thrift.Type.BOOL) {
        this.multimode = input.readBool();
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

SearchState.prototype.write = function(output) {
  output.writeStructBegin('SearchState');
  if (this.countEstimate !== null && this.countEstimate !== undefined) {
    output.writeFieldBegin('countEstimate', Thrift.Type.I32, 1);
    output.writeI32(this.countEstimate);
    output.writeFieldEnd();
  }
  if (this.fetchedItems !== null && this.fetchedItems !== undefined) {
    output.writeFieldBegin('fetchedItems', Thrift.Type.I32, 2);
    output.writeI32(this.fetchedItems);
    output.writeFieldEnd();
  }
  if (this.multimode !== null && this.multimode !== undefined) {
    output.writeFieldBegin('multimode', Thrift.Type.BOOL, 3);
    output.writeBool(this.multimode);
    output.writeFieldEnd();
  }
  output.writeFieldStop();
  output.writeStructEnd();
  return;
};

var FetchResult = module.exports.FetchResult = function(args) {
  this.state = null;
  this.item = null;
  this.nextSearchState = null;
  this.items = null;
  if (args) {
    if (args.state !== undefined && args.state !== null) {
      this.state = args.state;
    }
    if (args.item !== undefined && args.item !== null) {
      this.item = new ttypes.Item(args.item);
    }
    if (args.nextSearchState !== undefined && args.nextSearchState !== null) {
      this.nextSearchState = new ttypes.SearchState(args.nextSearchState);
    }
    if (args.items !== undefined && args.items !== null) {
      this.items = Thrift.copyList(args.items, [ttypes.Item]);
    }
  }
};
FetchResult.prototype = {};
FetchResult.prototype.read = function(input) {
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
      if (ftype == Thrift.Type.I32) {
        this.state = input.readI32();
      } else {
        input.skip(ftype);
      }
      break;
      case 2:
      if (ftype == Thrift.Type.STRUCT) {
        this.item = new ttypes.Item();
        this.item.read(input);
      } else {
        input.skip(ftype);
      }
      break;
      case 3:
      if (ftype == Thrift.Type.STRUCT) {
        this.nextSearchState = new ttypes.SearchState();
        this.nextSearchState.read(input);
      } else {
        input.skip(ftype);
      }
      break;
      case 4:
      if (ftype == Thrift.Type.LIST) {
        this.items = [];
        var _rtmp316 = input.readListBegin();
        var _size15 = _rtmp316.size || 0;
        for (var _i17 = 0; _i17 < _size15; ++_i17) {
          var elem18 = null;
          elem18 = new ttypes.Item();
          elem18.read(input);
          this.items.push(elem18);
        }
        input.readListEnd();
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

FetchResult.prototype.write = function(output) {
  output.writeStructBegin('FetchResult');
  if (this.state !== null && this.state !== undefined) {
    output.writeFieldBegin('state', Thrift.Type.I32, 1);
    output.writeI32(this.state);
    output.writeFieldEnd();
  }
  if (this.item !== null && this.item !== undefined) {
    output.writeFieldBegin('item', Thrift.Type.STRUCT, 2);
    this.item.write(output);
    output.writeFieldEnd();
  }
  if (this.nextSearchState !== null && this.nextSearchState !== undefined) {
    output.writeFieldBegin('nextSearchState', Thrift.Type.STRUCT, 3);
    this.nextSearchState.write(output);
    output.writeFieldEnd();
  }
  if (this.items !== null && this.items !== undefined) {
    output.writeFieldBegin('items', Thrift.Type.LIST, 4);
    output.writeListBegin(Thrift.Type.STRUCT, this.items.length);
    for (var iter19 in this.items) {
      if (this.items.hasOwnProperty(iter19)) {
        iter19 = this.items[iter19];
        iter19.write(output);
      }
    }
    output.writeListEnd();
    output.writeFieldEnd();
  }
  output.writeFieldStop();
  output.writeStructEnd();
  return;
};

