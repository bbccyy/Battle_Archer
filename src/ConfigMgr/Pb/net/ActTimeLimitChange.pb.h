// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: net/ActTimeLimitChange.proto

#ifndef PROTOBUF_net_2fActTimeLimitChange_2eproto__INCLUDED
#define PROTOBUF_net_2fActTimeLimitChange_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2006000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2006001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

namespace pb {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_net_2fActTimeLimitChange_2eproto();
void protobuf_AssignDesc_net_2fActTimeLimitChange_2eproto();
void protobuf_ShutdownFile_net_2fActTimeLimitChange_2eproto();

class TActTimeLimitChangeFreeNumInfo;
class TActTimeLimitChangeGetInfoRsp;
class TActTimeLimitChangeFreeNumNotify;

enum EChangeType {
  EChangeTypeRed = 1,
  EChangeTypeGold = 2,
  EChangeTypeCountry = 3
};
bool EChangeType_IsValid(int value);
const EChangeType EChangeType_MIN = EChangeTypeRed;
const EChangeType EChangeType_MAX = EChangeTypeCountry;
const int EChangeType_ARRAYSIZE = EChangeType_MAX + 1;

const ::google::protobuf::EnumDescriptor* EChangeType_descriptor();
inline const ::std::string& EChangeType_Name(EChangeType value) {
  return ::google::protobuf::internal::NameOfEnum(
    EChangeType_descriptor(), value);
}
inline bool EChangeType_Parse(
    const ::std::string& name, EChangeType* value) {
  return ::google::protobuf::internal::ParseNamedEnum<EChangeType>(
    EChangeType_descriptor(), name, value);
}
// ===================================================================

/*FOR2LUA
<Record>
	<name>TActTimeLimitChangeFreeNumInfo</name>
	<Function>
		<name>CopyFrom</name>
		<replaceName>MergeFrom</replaceName>
		<handler>descripter = pb_copyfrom_cpp()</handler>
	</Function>
	<Function>
		<name>operator_equal</name>
		<replaceName>MergeFrom</replaceName>
		<handler>descripter = pb_operator_equal_cpp()</handler>
	</Function>
	<Function>
		<name>new</name>
		<replaceName>net/ActTimeLimitChange.proto</replaceName>
		<handler>descripter = pb_new_cpp()</handler>
	</Function>
	<Function>
		<name>ParsePartialFromArray</name>
		<replaceName>ParseFromString</replaceName>
		<handler>descripter = pb_decode_cpp()</handler>
	</Function>
	<Function>
		<name>SerializePartialToArray</name>
		<replaceName>SerializeToString</replaceName>
		<handler>descripter = pb_encode_cpp()</handler>
	</Function>
</Record>
FOR2LUA*/
class TActTimeLimitChangeFreeNumInfo : public ::google::protobuf::Message {
 public:
  TActTimeLimitChangeFreeNumInfo();
  virtual ~TActTimeLimitChangeFreeNumInfo();

  TActTimeLimitChangeFreeNumInfo(const TActTimeLimitChangeFreeNumInfo& from);

  inline TActTimeLimitChangeFreeNumInfo& operator=(const TActTimeLimitChangeFreeNumInfo& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const TActTimeLimitChangeFreeNumInfo& default_instance();

  void Swap(TActTimeLimitChangeFreeNumInfo* other);

  // implements Message ----------------------------------------------

  TActTimeLimitChangeFreeNumInfo* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const TActTimeLimitChangeFreeNumInfo& from);
  void MergeFrom(const TActTimeLimitChangeFreeNumInfo& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional .pb.EChangeType ChangeType = 1;
  inline bool has_changetype() const;
  inline void clear_changetype();
  static const int kChangeTypeFieldNumber = 1;
  /*FOR2LUA
  <Record>
  	<name>TActTimeLimitChangeFreeNumInfo</name>
  	<Function>
  		<name>changetype</name>
  		<replaceName>ChangeType</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>set_changetype</name>
  		<replaceName>ChangeType</replaceName>
  		<handler>descripter = pb_set_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_changetype</name>
  		<replaceName>ChangeType</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline ::pb::EChangeType changetype() const;
  inline void set_changetype(::pb::EChangeType value);

  // optional uint32 CostFreeChangeNum = 2;
  inline bool has_costfreechangenum() const;
  inline void clear_costfreechangenum();
  static const int kCostFreeChangeNumFieldNumber = 2;
  /*FOR2LUA
  <Record>
  	<name>TActTimeLimitChangeFreeNumInfo</name>
  	<Function>
  		<name>costfreechangenum</name>
  		<replaceName>CostFreeChangeNum</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>set_costfreechangenum</name>
  		<replaceName>CostFreeChangeNum</replaceName>
  		<handler>descripter = pb_set_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_costfreechangenum</name>
  		<replaceName>CostFreeChangeNum</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline ::google::protobuf::uint32 costfreechangenum() const;
  inline void set_costfreechangenum(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:pb.TActTimeLimitChangeFreeNumInfo)
 private:
  inline void set_has_changetype();
  inline void clear_has_changetype();
  inline void set_has_costfreechangenum();
  inline void clear_has_costfreechangenum();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  int changetype_;
  ::google::protobuf::uint32 costfreechangenum_;
  friend void  protobuf_AddDesc_net_2fActTimeLimitChange_2eproto();
  friend void protobuf_AssignDesc_net_2fActTimeLimitChange_2eproto();
  friend void protobuf_ShutdownFile_net_2fActTimeLimitChange_2eproto();

  void InitAsDefaultInstance();
  static TActTimeLimitChangeFreeNumInfo* default_instance_;
};
// -------------------------------------------------------------------

/*FOR2LUA
<Record>
	<name>TActTimeLimitChangeGetInfoRsp</name>
	<Function>
		<name>CopyFrom</name>
		<replaceName>MergeFrom</replaceName>
		<handler>descripter = pb_copyfrom_cpp()</handler>
	</Function>
	<Function>
		<name>operator_equal</name>
		<replaceName>MergeFrom</replaceName>
		<handler>descripter = pb_operator_equal_cpp()</handler>
	</Function>
	<Function>
		<name>new</name>
		<replaceName>net/ActTimeLimitChange.proto</replaceName>
		<handler>descripter = pb_new_cpp()</handler>
	</Function>
	<Function>
		<name>ParsePartialFromArray</name>
		<replaceName>ParseFromString</replaceName>
		<handler>descripter = pb_decode_cpp()</handler>
	</Function>
	<Function>
		<name>SerializePartialToArray</name>
		<replaceName>SerializeToString</replaceName>
		<handler>descripter = pb_encode_cpp()</handler>
	</Function>
</Record>
FOR2LUA*/
class TActTimeLimitChangeGetInfoRsp : public ::google::protobuf::Message {
 public:
  TActTimeLimitChangeGetInfoRsp();
  virtual ~TActTimeLimitChangeGetInfoRsp();

  TActTimeLimitChangeGetInfoRsp(const TActTimeLimitChangeGetInfoRsp& from);

  inline TActTimeLimitChangeGetInfoRsp& operator=(const TActTimeLimitChangeGetInfoRsp& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const TActTimeLimitChangeGetInfoRsp& default_instance();

  void Swap(TActTimeLimitChangeGetInfoRsp* other);

  // implements Message ----------------------------------------------

  TActTimeLimitChangeGetInfoRsp* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const TActTimeLimitChangeGetInfoRsp& from);
  void MergeFrom(const TActTimeLimitChangeGetInfoRsp& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // repeated .pb.TActTimeLimitChangeFreeNumInfo ChangeFreeNumInfo = 1;
  inline int changefreenuminfo_size() const;
  inline void clear_changefreenuminfo();
  static const int kChangeFreeNumInfoFieldNumber = 1;
  /*FOR2LUA
  <Record>
  	<name>TActTimeLimitChangeGetInfoRsp</name>
  	<Function>
  		<name>changefreenuminfo</name>
  		<replaceName>ChangeFreeNumInfo</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>mutable_changefreenuminfo</name>
  		<replaceName>ChangeFreeNumInfo</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>add_changefreenuminfo</name>
  		<replaceName>ChangeFreeNumInfo</replaceName>
  		<handler>descripter = pb_repeated_add_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_changefreenuminfo</name>
  		<replaceName>ChangeFreeNumInfo</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  	<Function>
  		<name>changefreenuminfo_size</name>
  		<replaceName>ChangeFreeNumInfo</replaceName>
  		<handler>descripter = pb_repeated_size_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline const ::pb::TActTimeLimitChangeFreeNumInfo& changefreenuminfo(int index) const;
  inline ::pb::TActTimeLimitChangeFreeNumInfo* mutable_changefreenuminfo(int index);
  inline ::pb::TActTimeLimitChangeFreeNumInfo* add_changefreenuminfo();
  inline const ::google::protobuf::RepeatedPtrField< ::pb::TActTimeLimitChangeFreeNumInfo >&
      changefreenuminfo() const;
  inline ::google::protobuf::RepeatedPtrField< ::pb::TActTimeLimitChangeFreeNumInfo >*
      mutable_changefreenuminfo();

  // @@protoc_insertion_point(class_scope:pb.TActTimeLimitChangeGetInfoRsp)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::RepeatedPtrField< ::pb::TActTimeLimitChangeFreeNumInfo > changefreenuminfo_;
  friend void  protobuf_AddDesc_net_2fActTimeLimitChange_2eproto();
  friend void protobuf_AssignDesc_net_2fActTimeLimitChange_2eproto();
  friend void protobuf_ShutdownFile_net_2fActTimeLimitChange_2eproto();

  void InitAsDefaultInstance();
  static TActTimeLimitChangeGetInfoRsp* default_instance_;
};
// -------------------------------------------------------------------

/*FOR2LUA
<Record>
	<name>TActTimeLimitChangeFreeNumNotify</name>
	<Function>
		<name>CopyFrom</name>
		<replaceName>MergeFrom</replaceName>
		<handler>descripter = pb_copyfrom_cpp()</handler>
	</Function>
	<Function>
		<name>operator_equal</name>
		<replaceName>MergeFrom</replaceName>
		<handler>descripter = pb_operator_equal_cpp()</handler>
	</Function>
	<Function>
		<name>new</name>
		<replaceName>net/ActTimeLimitChange.proto</replaceName>
		<handler>descripter = pb_new_cpp()</handler>
	</Function>
	<Function>
		<name>ParsePartialFromArray</name>
		<replaceName>ParseFromString</replaceName>
		<handler>descripter = pb_decode_cpp()</handler>
	</Function>
	<Function>
		<name>SerializePartialToArray</name>
		<replaceName>SerializeToString</replaceName>
		<handler>descripter = pb_encode_cpp()</handler>
	</Function>
</Record>
FOR2LUA*/
class TActTimeLimitChangeFreeNumNotify : public ::google::protobuf::Message {
 public:
  TActTimeLimitChangeFreeNumNotify();
  virtual ~TActTimeLimitChangeFreeNumNotify();

  TActTimeLimitChangeFreeNumNotify(const TActTimeLimitChangeFreeNumNotify& from);

  inline TActTimeLimitChangeFreeNumNotify& operator=(const TActTimeLimitChangeFreeNumNotify& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const TActTimeLimitChangeFreeNumNotify& default_instance();

  void Swap(TActTimeLimitChangeFreeNumNotify* other);

  // implements Message ----------------------------------------------

  TActTimeLimitChangeFreeNumNotify* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const TActTimeLimitChangeFreeNumNotify& from);
  void MergeFrom(const TActTimeLimitChangeFreeNumNotify& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional .pb.TActTimeLimitChangeFreeNumInfo ChangeFreeNumInfo = 1;
  inline bool has_changefreenuminfo() const;
  inline void clear_changefreenuminfo();
  static const int kChangeFreeNumInfoFieldNumber = 1;
  /*FOR2LUA
  <Record>
  	<name>TActTimeLimitChangeFreeNumNotify</name>
  	<Function>
  		<name>changefreenuminfo</name>
  		<replaceName>ChangeFreeNumInfo</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>set_changefreenuminfo</name>
  		<replaceName>ChangeFreeNumInfo</replaceName>
  		<handler>descripter = pb_set_message_cpp()</handler>
  	</Function>
  	<Function>
  		<name>set_allocated_changefreenuminfo</name>
  		<replaceName>ChangeFreeNumInfo</replaceName>
  		<handler>descripter = pb_set_message_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_changefreenuminfo</name>
  		<replaceName>ChangeFreeNumInfo</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline const ::pb::TActTimeLimitChangeFreeNumInfo& changefreenuminfo() const;
  inline ::pb::TActTimeLimitChangeFreeNumInfo* mutable_changefreenuminfo();
  inline ::pb::TActTimeLimitChangeFreeNumInfo* release_changefreenuminfo();
  inline void set_allocated_changefreenuminfo(::pb::TActTimeLimitChangeFreeNumInfo* changefreenuminfo);

  // @@protoc_insertion_point(class_scope:pb.TActTimeLimitChangeFreeNumNotify)
 private:
  inline void set_has_changefreenuminfo();
  inline void clear_has_changefreenuminfo();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::pb::TActTimeLimitChangeFreeNumInfo* changefreenuminfo_;
  friend void  protobuf_AddDesc_net_2fActTimeLimitChange_2eproto();
  friend void protobuf_AssignDesc_net_2fActTimeLimitChange_2eproto();
  friend void protobuf_ShutdownFile_net_2fActTimeLimitChange_2eproto();

  void InitAsDefaultInstance();
  static TActTimeLimitChangeFreeNumNotify* default_instance_;
};
// ===================================================================


// ===================================================================

// TActTimeLimitChangeFreeNumInfo

// optional .pb.EChangeType ChangeType = 1;
inline bool TActTimeLimitChangeFreeNumInfo::has_changetype() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void TActTimeLimitChangeFreeNumInfo::set_has_changetype() {
  _has_bits_[0] |= 0x00000001u;
}
inline void TActTimeLimitChangeFreeNumInfo::clear_has_changetype() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void TActTimeLimitChangeFreeNumInfo::clear_changetype() {
  changetype_ = 1;
  clear_has_changetype();
}
inline ::pb::EChangeType TActTimeLimitChangeFreeNumInfo::changetype() const {
  // @@protoc_insertion_point(field_get:pb.TActTimeLimitChangeFreeNumInfo.ChangeType)
  return static_cast< ::pb::EChangeType >(changetype_);
}
inline void TActTimeLimitChangeFreeNumInfo::set_changetype(::pb::EChangeType value) {
  assert(::pb::EChangeType_IsValid(value));
  set_has_changetype();
  changetype_ = value;
  // @@protoc_insertion_point(field_set:pb.TActTimeLimitChangeFreeNumInfo.ChangeType)
}

// optional uint32 CostFreeChangeNum = 2;
inline bool TActTimeLimitChangeFreeNumInfo::has_costfreechangenum() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void TActTimeLimitChangeFreeNumInfo::set_has_costfreechangenum() {
  _has_bits_[0] |= 0x00000002u;
}
inline void TActTimeLimitChangeFreeNumInfo::clear_has_costfreechangenum() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void TActTimeLimitChangeFreeNumInfo::clear_costfreechangenum() {
  costfreechangenum_ = 0u;
  clear_has_costfreechangenum();
}
inline ::google::protobuf::uint32 TActTimeLimitChangeFreeNumInfo::costfreechangenum() const {
  // @@protoc_insertion_point(field_get:pb.TActTimeLimitChangeFreeNumInfo.CostFreeChangeNum)
  return costfreechangenum_;
}
inline void TActTimeLimitChangeFreeNumInfo::set_costfreechangenum(::google::protobuf::uint32 value) {
  set_has_costfreechangenum();
  costfreechangenum_ = value;
  // @@protoc_insertion_point(field_set:pb.TActTimeLimitChangeFreeNumInfo.CostFreeChangeNum)
}

// -------------------------------------------------------------------

// TActTimeLimitChangeGetInfoRsp

// repeated .pb.TActTimeLimitChangeFreeNumInfo ChangeFreeNumInfo = 1;
inline int TActTimeLimitChangeGetInfoRsp::changefreenuminfo_size() const {
  return changefreenuminfo_.size();
}
inline void TActTimeLimitChangeGetInfoRsp::clear_changefreenuminfo() {
  changefreenuminfo_.Clear();
}
inline const ::pb::TActTimeLimitChangeFreeNumInfo& TActTimeLimitChangeGetInfoRsp::changefreenuminfo(int index) const {
  // @@protoc_insertion_point(field_get:pb.TActTimeLimitChangeGetInfoRsp.ChangeFreeNumInfo)
  return changefreenuminfo_.Get(index);
}
inline ::pb::TActTimeLimitChangeFreeNumInfo* TActTimeLimitChangeGetInfoRsp::mutable_changefreenuminfo(int index) {
  // @@protoc_insertion_point(field_mutable:pb.TActTimeLimitChangeGetInfoRsp.ChangeFreeNumInfo)
  return changefreenuminfo_.Mutable(index);
}
inline ::pb::TActTimeLimitChangeFreeNumInfo* TActTimeLimitChangeGetInfoRsp::add_changefreenuminfo() {
  // @@protoc_insertion_point(field_add:pb.TActTimeLimitChangeGetInfoRsp.ChangeFreeNumInfo)
  return changefreenuminfo_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::pb::TActTimeLimitChangeFreeNumInfo >&
TActTimeLimitChangeGetInfoRsp::changefreenuminfo() const {
  // @@protoc_insertion_point(field_list:pb.TActTimeLimitChangeGetInfoRsp.ChangeFreeNumInfo)
  return changefreenuminfo_;
}
inline ::google::protobuf::RepeatedPtrField< ::pb::TActTimeLimitChangeFreeNumInfo >*
TActTimeLimitChangeGetInfoRsp::mutable_changefreenuminfo() {
  // @@protoc_insertion_point(field_mutable_list:pb.TActTimeLimitChangeGetInfoRsp.ChangeFreeNumInfo)
  return &changefreenuminfo_;
}

// -------------------------------------------------------------------

// TActTimeLimitChangeFreeNumNotify

// optional .pb.TActTimeLimitChangeFreeNumInfo ChangeFreeNumInfo = 1;
inline bool TActTimeLimitChangeFreeNumNotify::has_changefreenuminfo() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void TActTimeLimitChangeFreeNumNotify::set_has_changefreenuminfo() {
  _has_bits_[0] |= 0x00000001u;
}
inline void TActTimeLimitChangeFreeNumNotify::clear_has_changefreenuminfo() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void TActTimeLimitChangeFreeNumNotify::clear_changefreenuminfo() {
  if (changefreenuminfo_ != NULL) changefreenuminfo_->::pb::TActTimeLimitChangeFreeNumInfo::Clear();
  clear_has_changefreenuminfo();
}
inline const ::pb::TActTimeLimitChangeFreeNumInfo& TActTimeLimitChangeFreeNumNotify::changefreenuminfo() const {
  // @@protoc_insertion_point(field_get:pb.TActTimeLimitChangeFreeNumNotify.ChangeFreeNumInfo)
  return changefreenuminfo_ != NULL ? *changefreenuminfo_ : *default_instance_->changefreenuminfo_;
}
inline ::pb::TActTimeLimitChangeFreeNumInfo* TActTimeLimitChangeFreeNumNotify::mutable_changefreenuminfo() {
  set_has_changefreenuminfo();
  if (changefreenuminfo_ == NULL) changefreenuminfo_ = new ::pb::TActTimeLimitChangeFreeNumInfo;
  // @@protoc_insertion_point(field_mutable:pb.TActTimeLimitChangeFreeNumNotify.ChangeFreeNumInfo)
  return changefreenuminfo_;
}
inline ::pb::TActTimeLimitChangeFreeNumInfo* TActTimeLimitChangeFreeNumNotify::release_changefreenuminfo() {
  clear_has_changefreenuminfo();
  ::pb::TActTimeLimitChangeFreeNumInfo* temp = changefreenuminfo_;
  changefreenuminfo_ = NULL;
  return temp;
}
inline void TActTimeLimitChangeFreeNumNotify::set_allocated_changefreenuminfo(::pb::TActTimeLimitChangeFreeNumInfo* changefreenuminfo) {
  delete changefreenuminfo_;
  changefreenuminfo_ = changefreenuminfo;
  if (changefreenuminfo) {
    set_has_changefreenuminfo();
  } else {
    clear_has_changefreenuminfo();
  }
  // @@protoc_insertion_point(field_set_allocated:pb.TActTimeLimitChangeFreeNumNotify.ChangeFreeNumInfo)
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace pb

#ifndef SWIG
namespace google {
namespace protobuf {

template <> struct is_proto_enum< ::pb::EChangeType> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::pb::EChangeType>() {
  return ::pb::EChangeType_descriptor();
}

}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_net_2fActTimeLimitChange_2eproto__INCLUDED