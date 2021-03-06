/**
 * Autogenerated by Thrift Compiler (0.14.1)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#include "Task_types.h"

#include <algorithm>
#include <ostream>

#include <thrift/TToString.h>



int _kFetchStateValues[] = {
  FetchState::PENDING,
  FetchState::ITEMS,
  FetchState::ENDED
};
const char* _kFetchStateNames[] = {
  "PENDING",
  "ITEMS",
  "ENDED"
};
const std::map<int, const char*> _FetchState_VALUES_TO_NAMES(::apache::thrift::TEnumIterator(3, _kFetchStateValues, _kFetchStateNames), ::apache::thrift::TEnumIterator(-1, nullptr, nullptr));

std::ostream& operator<<(std::ostream& out, const FetchState::type& val) {
  std::map<int, const char*>::const_iterator it = _FetchState_VALUES_TO_NAMES.find(val);
  if (it != _FetchState_VALUES_TO_NAMES.end()) {
    out << it->second;
  } else {
    out << static_cast<int>(val);
  }
  return out;
}

std::string to_string(const FetchState::type& val) {
  std::map<int, const char*>::const_iterator it = _FetchState_VALUES_TO_NAMES.find(val);
  if (it != _FetchState_VALUES_TO_NAMES.end()) {
    return std::string(it->second);
  } else {
    return std::to_string(static_cast<int>(val));
  }
}


InvalidKeyException::~InvalidKeyException() noexcept {
}


void InvalidKeyException::__set_invalidKey(const int32_t val) {
  this->invalidKey = val;
}

void InvalidKeyException::__set_expectedKey(const int32_t val) {
  this->expectedKey = val;
}
std::ostream& operator<<(std::ostream& out, const InvalidKeyException& obj)
{
  obj.printTo(out);
  return out;
}


uint32_t InvalidKeyException::read(::apache::thrift::protocol::TProtocol* iprot) {

  ::apache::thrift::protocol::TInputRecursionTracker tracker(*iprot);
  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->invalidKey);
          this->__isset.invalidKey = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->expectedKey);
          this->__isset.expectedKey = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t InvalidKeyException::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  ::apache::thrift::protocol::TOutputRecursionTracker tracker(*oprot);
  xfer += oprot->writeStructBegin("InvalidKeyException");

  xfer += oprot->writeFieldBegin("invalidKey", ::apache::thrift::protocol::T_I32, 1);
  xfer += oprot->writeI32(this->invalidKey);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("expectedKey", ::apache::thrift::protocol::T_I32, 2);
  xfer += oprot->writeI32(this->expectedKey);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(InvalidKeyException &a, InvalidKeyException &b) {
  using ::std::swap;
  swap(a.invalidKey, b.invalidKey);
  swap(a.expectedKey, b.expectedKey);
  swap(a.__isset, b.__isset);
}

InvalidKeyException::InvalidKeyException(const InvalidKeyException& other0) : TException() {
  invalidKey = other0.invalidKey;
  expectedKey = other0.expectedKey;
  __isset = other0.__isset;
}
InvalidKeyException& InvalidKeyException::operator=(const InvalidKeyException& other1) {
  invalidKey = other1.invalidKey;
  expectedKey = other1.expectedKey;
  __isset = other1.__isset;
  return *this;
}
void InvalidKeyException::printTo(std::ostream& out) const {
  using ::apache::thrift::to_string;
  out << "InvalidKeyException(";
  out << "invalidKey=" << to_string(invalidKey);
  out << ", " << "expectedKey=" << to_string(expectedKey);
  out << ")";
}

const char* InvalidKeyException::what() const noexcept {
  try {
    std::stringstream ss;
    ss << "TException - service has thrown: " << *this;
    this->thriftTExceptionMessageHolder_ = ss.str();
    return this->thriftTExceptionMessageHolder_.c_str();
  } catch (const std::exception&) {
    return "TException - service has thrown: InvalidKeyException";
  }
}


ProtocolException::~ProtocolException() noexcept {
}


void ProtocolException::__set_message(const std::string& val) {
  this->message = val;
}
std::ostream& operator<<(std::ostream& out, const ProtocolException& obj)
{
  obj.printTo(out);
  return out;
}


uint32_t ProtocolException::read(::apache::thrift::protocol::TProtocol* iprot) {

  ::apache::thrift::protocol::TInputRecursionTracker tracker(*iprot);
  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->message);
          this->__isset.message = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t ProtocolException::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  ::apache::thrift::protocol::TOutputRecursionTracker tracker(*oprot);
  xfer += oprot->writeStructBegin("ProtocolException");

  xfer += oprot->writeFieldBegin("message", ::apache::thrift::protocol::T_STRING, 1);
  xfer += oprot->writeString(this->message);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(ProtocolException &a, ProtocolException &b) {
  using ::std::swap;
  swap(a.message, b.message);
  swap(a.__isset, b.__isset);
}

ProtocolException::ProtocolException(const ProtocolException& other2) : TException() {
  message = other2.message;
  __isset = other2.__isset;
}
ProtocolException& ProtocolException::operator=(const ProtocolException& other3) {
  message = other3.message;
  __isset = other3.__isset;
  return *this;
}
void ProtocolException::printTo(std::ostream& out) const {
  using ::apache::thrift::to_string;
  out << "ProtocolException(";
  out << "message=" << to_string(message);
  out << ")";
}

const char* ProtocolException::what() const noexcept {
  try {
    std::stringstream ss;
    ss << "TException - service has thrown: " << *this;
    this->thriftTExceptionMessageHolder_ = ss.str();
    return this->thriftTExceptionMessageHolder_.c_str();
  } catch (const std::exception&) {
    return "TException - service has thrown: ProtocolException";
  }
}


ItemA::~ItemA() noexcept {
}


void ItemA::__set_fieldA(const int16_t val) {
  this->fieldA = val;
}

void ItemA::__set_fieldB(const std::vector<int16_t> & val) {
  this->fieldB = val;
}

void ItemA::__set_fieldC(const int32_t val) {
  this->fieldC = val;
}
std::ostream& operator<<(std::ostream& out, const ItemA& obj)
{
  obj.printTo(out);
  return out;
}


uint32_t ItemA::read(::apache::thrift::protocol::TProtocol* iprot) {

  ::apache::thrift::protocol::TInputRecursionTracker tracker(*iprot);
  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;

  bool isset_fieldA = false;
  bool isset_fieldB = false;
  bool isset_fieldC = false;

  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_I16) {
          xfer += iprot->readI16(this->fieldA);
          isset_fieldA = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_LIST) {
          {
            this->fieldB.clear();
            uint32_t _size4;
            ::apache::thrift::protocol::TType _etype7;
            xfer += iprot->readListBegin(_etype7, _size4);
            this->fieldB.resize(_size4);
            uint32_t _i8;
            for (_i8 = 0; _i8 < _size4; ++_i8)
            {
              xfer += iprot->readI16(this->fieldB[_i8]);
            }
            xfer += iprot->readListEnd();
          }
          isset_fieldB = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 3:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->fieldC);
          isset_fieldC = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  if (!isset_fieldA)
    throw TProtocolException(TProtocolException::INVALID_DATA);
  if (!isset_fieldB)
    throw TProtocolException(TProtocolException::INVALID_DATA);
  if (!isset_fieldC)
    throw TProtocolException(TProtocolException::INVALID_DATA);
  return xfer;
}

uint32_t ItemA::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  ::apache::thrift::protocol::TOutputRecursionTracker tracker(*oprot);
  xfer += oprot->writeStructBegin("ItemA");

  xfer += oprot->writeFieldBegin("fieldA", ::apache::thrift::protocol::T_I16, 1);
  xfer += oprot->writeI16(this->fieldA);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("fieldB", ::apache::thrift::protocol::T_LIST, 2);
  {
    xfer += oprot->writeListBegin(::apache::thrift::protocol::T_I16, static_cast<uint32_t>(this->fieldB.size()));
    std::vector<int16_t> ::const_iterator _iter9;
    for (_iter9 = this->fieldB.begin(); _iter9 != this->fieldB.end(); ++_iter9)
    {
      xfer += oprot->writeI16((*_iter9));
    }
    xfer += oprot->writeListEnd();
  }
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("fieldC", ::apache::thrift::protocol::T_I32, 3);
  xfer += oprot->writeI32(this->fieldC);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(ItemA &a, ItemA &b) {
  using ::std::swap;
  swap(a.fieldA, b.fieldA);
  swap(a.fieldB, b.fieldB);
  swap(a.fieldC, b.fieldC);
}

ItemA::ItemA(const ItemA& other10) {
  fieldA = other10.fieldA;
  fieldB = other10.fieldB;
  fieldC = other10.fieldC;
}
ItemA& ItemA::operator=(const ItemA& other11) {
  fieldA = other11.fieldA;
  fieldB = other11.fieldB;
  fieldC = other11.fieldC;
  return *this;
}
void ItemA::printTo(std::ostream& out) const {
  using ::apache::thrift::to_string;
  out << "ItemA(";
  out << "fieldA=" << to_string(fieldA);
  out << ", " << "fieldB=" << to_string(fieldB);
  out << ", " << "fieldC=" << to_string(fieldC);
  out << ")";
}


ItemB::~ItemB() noexcept {
}


void ItemB::__set_fieldA(const std::string& val) {
  this->fieldA = val;
}

void ItemB::__set_fieldB(const std::set<std::string> & val) {
  this->fieldB = val;
}

void ItemB::__set_fieldC(const std::vector<std::string> & val) {
  this->fieldC = val;
__isset.fieldC = true;
}
std::ostream& operator<<(std::ostream& out, const ItemB& obj)
{
  obj.printTo(out);
  return out;
}


uint32_t ItemB::read(::apache::thrift::protocol::TProtocol* iprot) {

  ::apache::thrift::protocol::TInputRecursionTracker tracker(*iprot);
  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->fieldA);
          this->__isset.fieldA = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_SET) {
          {
            this->fieldB.clear();
            uint32_t _size12;
            ::apache::thrift::protocol::TType _etype15;
            xfer += iprot->readSetBegin(_etype15, _size12);
            uint32_t _i16;
            for (_i16 = 0; _i16 < _size12; ++_i16)
            {
              std::string _elem17;
              xfer += iprot->readString(_elem17);
              this->fieldB.insert(_elem17);
            }
            xfer += iprot->readSetEnd();
          }
          this->__isset.fieldB = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 3:
        if (ftype == ::apache::thrift::protocol::T_LIST) {
          {
            this->fieldC.clear();
            uint32_t _size18;
            ::apache::thrift::protocol::TType _etype21;
            xfer += iprot->readListBegin(_etype21, _size18);
            this->fieldC.resize(_size18);
            uint32_t _i22;
            for (_i22 = 0; _i22 < _size18; ++_i22)
            {
              xfer += iprot->readString(this->fieldC[_i22]);
            }
            xfer += iprot->readListEnd();
          }
          this->__isset.fieldC = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t ItemB::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  ::apache::thrift::protocol::TOutputRecursionTracker tracker(*oprot);
  xfer += oprot->writeStructBegin("ItemB");

  xfer += oprot->writeFieldBegin("fieldA", ::apache::thrift::protocol::T_STRING, 1);
  xfer += oprot->writeString(this->fieldA);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("fieldB", ::apache::thrift::protocol::T_SET, 2);
  {
    xfer += oprot->writeSetBegin(::apache::thrift::protocol::T_STRING, static_cast<uint32_t>(this->fieldB.size()));
    std::set<std::string> ::const_iterator _iter23;
    for (_iter23 = this->fieldB.begin(); _iter23 != this->fieldB.end(); ++_iter23)
    {
      xfer += oprot->writeString((*_iter23));
    }
    xfer += oprot->writeSetEnd();
  }
  xfer += oprot->writeFieldEnd();

  if (this->__isset.fieldC) {
    xfer += oprot->writeFieldBegin("fieldC", ::apache::thrift::protocol::T_LIST, 3);
    {
      xfer += oprot->writeListBegin(::apache::thrift::protocol::T_STRING, static_cast<uint32_t>(this->fieldC.size()));
      std::vector<std::string> ::const_iterator _iter24;
      for (_iter24 = this->fieldC.begin(); _iter24 != this->fieldC.end(); ++_iter24)
      {
        xfer += oprot->writeString((*_iter24));
      }
      xfer += oprot->writeListEnd();
    }
    xfer += oprot->writeFieldEnd();
  }
  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(ItemB &a, ItemB &b) {
  using ::std::swap;
  swap(a.fieldA, b.fieldA);
  swap(a.fieldB, b.fieldB);
  swap(a.fieldC, b.fieldC);
  swap(a.__isset, b.__isset);
}

ItemB::ItemB(const ItemB& other25) {
  fieldA = other25.fieldA;
  fieldB = other25.fieldB;
  fieldC = other25.fieldC;
  __isset = other25.__isset;
}
ItemB& ItemB::operator=(const ItemB& other26) {
  fieldA = other26.fieldA;
  fieldB = other26.fieldB;
  fieldC = other26.fieldC;
  __isset = other26.__isset;
  return *this;
}
void ItemB::printTo(std::ostream& out) const {
  using ::apache::thrift::to_string;
  out << "ItemB(";
  out << "fieldA=" << to_string(fieldA);
  out << ", " << "fieldB=" << to_string(fieldB);
  out << ", " << "fieldC="; (__isset.fieldC ? (out << to_string(fieldC)) : (out << "<null>"));
  out << ")";
}


ItemC::~ItemC() noexcept {
}


void ItemC::__set_fieldA(const bool val) {
  this->fieldA = val;
}
std::ostream& operator<<(std::ostream& out, const ItemC& obj)
{
  obj.printTo(out);
  return out;
}


uint32_t ItemC::read(::apache::thrift::protocol::TProtocol* iprot) {

  ::apache::thrift::protocol::TInputRecursionTracker tracker(*iprot);
  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_BOOL) {
          xfer += iprot->readBool(this->fieldA);
          this->__isset.fieldA = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t ItemC::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  ::apache::thrift::protocol::TOutputRecursionTracker tracker(*oprot);
  xfer += oprot->writeStructBegin("ItemC");

  xfer += oprot->writeFieldBegin("fieldA", ::apache::thrift::protocol::T_BOOL, 1);
  xfer += oprot->writeBool(this->fieldA);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(ItemC &a, ItemC &b) {
  using ::std::swap;
  swap(a.fieldA, b.fieldA);
  swap(a.__isset, b.__isset);
}

ItemC::ItemC(const ItemC& other27) {
  fieldA = other27.fieldA;
  __isset = other27.__isset;
}
ItemC& ItemC::operator=(const ItemC& other28) {
  fieldA = other28.fieldA;
  __isset = other28.__isset;
  return *this;
}
void ItemC::printTo(std::ostream& out) const {
  using ::apache::thrift::to_string;
  out << "ItemC(";
  out << "fieldA=" << to_string(fieldA);
  out << ")";
}


ItemD::~ItemD() noexcept {
}


void ItemD::__set_fieldD(const bool val) {
  this->fieldD = val;
}
std::ostream& operator<<(std::ostream& out, const ItemD& obj)
{
  obj.printTo(out);
  return out;
}


uint32_t ItemD::read(::apache::thrift::protocol::TProtocol* iprot) {

  ::apache::thrift::protocol::TInputRecursionTracker tracker(*iprot);
  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_BOOL) {
          xfer += iprot->readBool(this->fieldD);
          this->__isset.fieldD = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t ItemD::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  ::apache::thrift::protocol::TOutputRecursionTracker tracker(*oprot);
  xfer += oprot->writeStructBegin("ItemD");

  xfer += oprot->writeFieldBegin("fieldD", ::apache::thrift::protocol::T_BOOL, 1);
  xfer += oprot->writeBool(this->fieldD);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(ItemD &a, ItemD &b) {
  using ::std::swap;
  swap(a.fieldD, b.fieldD);
  swap(a.__isset, b.__isset);
}

ItemD::ItemD(const ItemD& other29) {
  fieldD = other29.fieldD;
  __isset = other29.__isset;
}
ItemD& ItemD::operator=(const ItemD& other30) {
  fieldD = other30.fieldD;
  __isset = other30.__isset;
  return *this;
}
void ItemD::printTo(std::ostream& out) const {
  using ::apache::thrift::to_string;
  out << "ItemD(";
  out << "fieldD=" << to_string(fieldD);
  out << ")";
}


Item::~Item() noexcept {
}


void Item::__set_itemA(const ItemA& val) {
  this->itemA = val;
__isset.itemA = true;
}

void Item::__set_itemB(const ItemB& val) {
  this->itemB = val;
__isset.itemB = true;
}

void Item::__set_itemC(const ItemC& val) {
  this->itemC = val;
__isset.itemC = true;
}

void Item::__set_itemD(const ItemD& val) {
  this->itemD = val;
__isset.itemD = true;
}
std::ostream& operator<<(std::ostream& out, const Item& obj)
{
  obj.printTo(out);
  return out;
}


uint32_t Item::read(::apache::thrift::protocol::TProtocol* iprot) {

  ::apache::thrift::protocol::TInputRecursionTracker tracker(*iprot);
  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_STRUCT) {
          xfer += this->itemA.read(iprot);
          this->__isset.itemA = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_STRUCT) {
          xfer += this->itemB.read(iprot);
          this->__isset.itemB = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 3:
        if (ftype == ::apache::thrift::protocol::T_STRUCT) {
          xfer += this->itemC.read(iprot);
          this->__isset.itemC = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 4:
        if (ftype == ::apache::thrift::protocol::T_STRUCT) {
          xfer += this->itemD.read(iprot);
          this->__isset.itemD = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t Item::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  ::apache::thrift::protocol::TOutputRecursionTracker tracker(*oprot);
  xfer += oprot->writeStructBegin("Item");

  if (this->__isset.itemA) {
    xfer += oprot->writeFieldBegin("itemA", ::apache::thrift::protocol::T_STRUCT, 1);
    xfer += this->itemA.write(oprot);
    xfer += oprot->writeFieldEnd();
  }
  if (this->__isset.itemB) {
    xfer += oprot->writeFieldBegin("itemB", ::apache::thrift::protocol::T_STRUCT, 2);
    xfer += this->itemB.write(oprot);
    xfer += oprot->writeFieldEnd();
  }
  if (this->__isset.itemC) {
    xfer += oprot->writeFieldBegin("itemC", ::apache::thrift::protocol::T_STRUCT, 3);
    xfer += this->itemC.write(oprot);
    xfer += oprot->writeFieldEnd();
  }
  if (this->__isset.itemD) {
    xfer += oprot->writeFieldBegin("itemD", ::apache::thrift::protocol::T_STRUCT, 4);
    xfer += this->itemD.write(oprot);
    xfer += oprot->writeFieldEnd();
  }
  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(Item &a, Item &b) {
  using ::std::swap;
  swap(a.itemA, b.itemA);
  swap(a.itemB, b.itemB);
  swap(a.itemC, b.itemC);
  swap(a.itemD, b.itemD);
  swap(a.__isset, b.__isset);
}

Item::Item(const Item& other31) {
  itemA = other31.itemA;
  itemB = other31.itemB;
  itemC = other31.itemC;
  itemD = other31.itemD;
  __isset = other31.__isset;
}
Item& Item::operator=(const Item& other32) {
  itemA = other32.itemA;
  itemB = other32.itemB;
  itemC = other32.itemC;
  itemD = other32.itemD;
  __isset = other32.__isset;
  return *this;
}
void Item::printTo(std::ostream& out) const {
  using ::apache::thrift::to_string;
  out << "Item(";
  out << "itemA="; (__isset.itemA ? (out << to_string(itemA)) : (out << "<null>"));
  out << ", " << "itemB="; (__isset.itemB ? (out << to_string(itemB)) : (out << "<null>"));
  out << ", " << "itemC="; (__isset.itemC ? (out << to_string(itemC)) : (out << "<null>"));
  out << ", " << "itemD="; (__isset.itemD ? (out << to_string(itemD)) : (out << "<null>"));
  out << ")";
}


SearchState::~SearchState() noexcept {
}


void SearchState::__set_countEstimate(const int32_t val) {
  this->countEstimate = val;
}

void SearchState::__set_fetchedItems(const int32_t val) {
  this->fetchedItems = val;
}

void SearchState::__set_multimode(const bool val) {
  this->multimode = val;
__isset.multimode = true;
}
std::ostream& operator<<(std::ostream& out, const SearchState& obj)
{
  obj.printTo(out);
  return out;
}


uint32_t SearchState::read(::apache::thrift::protocol::TProtocol* iprot) {

  ::apache::thrift::protocol::TInputRecursionTracker tracker(*iprot);
  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->countEstimate);
          this->__isset.countEstimate = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->fetchedItems);
          this->__isset.fetchedItems = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 3:
        if (ftype == ::apache::thrift::protocol::T_BOOL) {
          xfer += iprot->readBool(this->multimode);
          this->__isset.multimode = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t SearchState::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  ::apache::thrift::protocol::TOutputRecursionTracker tracker(*oprot);
  xfer += oprot->writeStructBegin("SearchState");

  xfer += oprot->writeFieldBegin("countEstimate", ::apache::thrift::protocol::T_I32, 1);
  xfer += oprot->writeI32(this->countEstimate);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("fetchedItems", ::apache::thrift::protocol::T_I32, 2);
  xfer += oprot->writeI32(this->fetchedItems);
  xfer += oprot->writeFieldEnd();

  if (this->__isset.multimode) {
    xfer += oprot->writeFieldBegin("multimode", ::apache::thrift::protocol::T_BOOL, 3);
    xfer += oprot->writeBool(this->multimode);
    xfer += oprot->writeFieldEnd();
  }
  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(SearchState &a, SearchState &b) {
  using ::std::swap;
  swap(a.countEstimate, b.countEstimate);
  swap(a.fetchedItems, b.fetchedItems);
  swap(a.multimode, b.multimode);
  swap(a.__isset, b.__isset);
}

SearchState::SearchState(const SearchState& other33) {
  countEstimate = other33.countEstimate;
  fetchedItems = other33.fetchedItems;
  multimode = other33.multimode;
  __isset = other33.__isset;
}
SearchState& SearchState::operator=(const SearchState& other34) {
  countEstimate = other34.countEstimate;
  fetchedItems = other34.fetchedItems;
  multimode = other34.multimode;
  __isset = other34.__isset;
  return *this;
}
void SearchState::printTo(std::ostream& out) const {
  using ::apache::thrift::to_string;
  out << "SearchState(";
  out << "countEstimate=" << to_string(countEstimate);
  out << ", " << "fetchedItems=" << to_string(fetchedItems);
  out << ", " << "multimode="; (__isset.multimode ? (out << to_string(multimode)) : (out << "<null>"));
  out << ")";
}


FetchResult::~FetchResult() noexcept {
}


void FetchResult::__set_state(const FetchState::type val) {
  this->state = val;
}

void FetchResult::__set_item(const Item& val) {
  this->item = val;
__isset.item = true;
}

void FetchResult::__set_nextSearchState(const SearchState& val) {
  this->nextSearchState = val;
}

void FetchResult::__set_items(const std::vector<Item> & val) {
  this->items = val;
__isset.items = true;
}
std::ostream& operator<<(std::ostream& out, const FetchResult& obj)
{
  obj.printTo(out);
  return out;
}


uint32_t FetchResult::read(::apache::thrift::protocol::TProtocol* iprot) {

  ::apache::thrift::protocol::TInputRecursionTracker tracker(*iprot);
  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          int32_t ecast35;
          xfer += iprot->readI32(ecast35);
          this->state = (FetchState::type)ecast35;
          this->__isset.state = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_STRUCT) {
          xfer += this->item.read(iprot);
          this->__isset.item = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 3:
        if (ftype == ::apache::thrift::protocol::T_STRUCT) {
          xfer += this->nextSearchState.read(iprot);
          this->__isset.nextSearchState = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 4:
        if (ftype == ::apache::thrift::protocol::T_LIST) {
          {
            this->items.clear();
            uint32_t _size36;
            ::apache::thrift::protocol::TType _etype39;
            xfer += iprot->readListBegin(_etype39, _size36);
            this->items.resize(_size36);
            uint32_t _i40;
            for (_i40 = 0; _i40 < _size36; ++_i40)
            {
              xfer += this->items[_i40].read(iprot);
            }
            xfer += iprot->readListEnd();
          }
          this->__isset.items = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t FetchResult::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  ::apache::thrift::protocol::TOutputRecursionTracker tracker(*oprot);
  xfer += oprot->writeStructBegin("FetchResult");

  xfer += oprot->writeFieldBegin("state", ::apache::thrift::protocol::T_I32, 1);
  xfer += oprot->writeI32((int32_t)this->state);
  xfer += oprot->writeFieldEnd();

  if (this->__isset.item) {
    xfer += oprot->writeFieldBegin("item", ::apache::thrift::protocol::T_STRUCT, 2);
    xfer += this->item.write(oprot);
    xfer += oprot->writeFieldEnd();
  }
  xfer += oprot->writeFieldBegin("nextSearchState", ::apache::thrift::protocol::T_STRUCT, 3);
  xfer += this->nextSearchState.write(oprot);
  xfer += oprot->writeFieldEnd();

  if (this->__isset.items) {
    xfer += oprot->writeFieldBegin("items", ::apache::thrift::protocol::T_LIST, 4);
    {
      xfer += oprot->writeListBegin(::apache::thrift::protocol::T_STRUCT, static_cast<uint32_t>(this->items.size()));
      std::vector<Item> ::const_iterator _iter41;
      for (_iter41 = this->items.begin(); _iter41 != this->items.end(); ++_iter41)
      {
        xfer += (*_iter41).write(oprot);
      }
      xfer += oprot->writeListEnd();
    }
    xfer += oprot->writeFieldEnd();
  }
  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(FetchResult &a, FetchResult &b) {
  using ::std::swap;
  swap(a.state, b.state);
  swap(a.item, b.item);
  swap(a.nextSearchState, b.nextSearchState);
  swap(a.items, b.items);
  swap(a.__isset, b.__isset);
}

FetchResult::FetchResult(const FetchResult& other42) {
  state = other42.state;
  item = other42.item;
  nextSearchState = other42.nextSearchState;
  items = other42.items;
  __isset = other42.__isset;
}
FetchResult& FetchResult::operator=(const FetchResult& other43) {
  state = other43.state;
  item = other43.item;
  nextSearchState = other43.nextSearchState;
  items = other43.items;
  __isset = other43.__isset;
  return *this;
}
void FetchResult::printTo(std::ostream& out) const {
  using ::apache::thrift::to_string;
  out << "FetchResult(";
  out << "state=" << to_string(state);
  out << ", " << "item="; (__isset.item ? (out << to_string(item)) : (out << "<null>"));
  out << ", " << "nextSearchState=" << to_string(nextSearchState);
  out << ", " << "items="; (__isset.items ? (out << to_string(items)) : (out << "<null>"));
  out << ")";
}


