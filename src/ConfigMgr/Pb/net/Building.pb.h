// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: net/Building.proto

#ifndef PROTOBUF_net_2fBuilding_2eproto__INCLUDED
#define PROTOBUF_net_2fBuilding_2eproto__INCLUDED

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
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

namespace pb {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_net_2fBuilding_2eproto();
void protobuf_AssignDesc_net_2fBuilding_2eproto();
void protobuf_ShutdownFile_net_2fBuilding_2eproto();

class TBuildingInfo;

// ===================================================================

/*FOR2LUA
<Record>
	<name>TBuildingInfo</name>
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
		<replaceName>net/Building.proto</replaceName>
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
class TBuildingInfo : public ::google::protobuf::Message {
 public:
  TBuildingInfo();
  virtual ~TBuildingInfo();

  TBuildingInfo(const TBuildingInfo& from);

  inline TBuildingInfo& operator=(const TBuildingInfo& from) {
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
  static const TBuildingInfo& default_instance();

  void Swap(TBuildingInfo* other);

  // implements Message ----------------------------------------------

  TBuildingInfo* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const TBuildingInfo& from);
  void MergeFrom(const TBuildingInfo& from);
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

  // optional int32 FieldId = 1;
  inline bool has_fieldid() const;
  inline void clear_fieldid();
  static const int kFieldIdFieldNumber = 1;
  /*FOR2LUA
  <Record>
  	<name>TBuildingInfo</name>
  	<Function>
  		<name>fieldid</name>
  		<replaceName>FieldId</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>set_fieldid</name>
  		<replaceName>FieldId</replaceName>
  		<handler>descripter = pb_set_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_fieldid</name>
  		<replaceName>FieldId</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline ::google::protobuf::int32 fieldid() const;
  inline void set_fieldid(::google::protobuf::int32 value);

  // optional uint64 ConfId = 2;
  inline bool has_confid() const;
  inline void clear_confid();
  static const int kConfIdFieldNumber = 2;
  /*FOR2LUA
  <Record>
  	<name>TBuildingInfo</name>
  	<Function>
  		<name>confid</name>
  		<replaceName>ConfId</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>set_confid</name>
  		<replaceName>ConfId</replaceName>
  		<handler>descripter = pb_set_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_confid</name>
  		<replaceName>ConfId</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline ::google::protobuf::uint64 confid() const;
  inline void set_confid(::google::protobuf::uint64 value);

  // optional int32 Yield = 3;
  inline bool has_yield() const;
  inline void clear_yield();
  static const int kYieldFieldNumber = 3;
  /*FOR2LUA
  <Record>
  	<name>TBuildingInfo</name>
  	<Function>
  		<name>yield</name>
  		<replaceName>Yield</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>set_yield</name>
  		<replaceName>Yield</replaceName>
  		<handler>descripter = pb_set_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_yield</name>
  		<replaceName>Yield</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline ::google::protobuf::int32 yield() const;
  inline void set_yield(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:pb.TBuildingInfo)
 private:
  inline void set_has_fieldid();
  inline void clear_has_fieldid();
  inline void set_has_confid();
  inline void clear_has_confid();
  inline void set_has_yield();
  inline void clear_has_yield();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::uint64 confid_;
  ::google::protobuf::int32 fieldid_;
  ::google::protobuf::int32 yield_;
  friend void  protobuf_AddDesc_net_2fBuilding_2eproto();
  friend void protobuf_AssignDesc_net_2fBuilding_2eproto();
  friend void protobuf_ShutdownFile_net_2fBuilding_2eproto();

  void InitAsDefaultInstance();
  static TBuildingInfo* default_instance_;
};
// ===================================================================


// ===================================================================

// TBuildingInfo

// optional int32 FieldId = 1;
inline bool TBuildingInfo::has_fieldid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void TBuildingInfo::set_has_fieldid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void TBuildingInfo::clear_has_fieldid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void TBuildingInfo::clear_fieldid() {
  fieldid_ = 0;
  clear_has_fieldid();
}
inline ::google::protobuf::int32 TBuildingInfo::fieldid() const {
  // @@protoc_insertion_point(field_get:pb.TBuildingInfo.FieldId)
  return fieldid_;
}
inline void TBuildingInfo::set_fieldid(::google::protobuf::int32 value) {
  set_has_fieldid();
  fieldid_ = value;
  // @@protoc_insertion_point(field_set:pb.TBuildingInfo.FieldId)
}

// optional uint64 ConfId = 2;
inline bool TBuildingInfo::has_confid() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void TBuildingInfo::set_has_confid() {
  _has_bits_[0] |= 0x00000002u;
}
inline void TBuildingInfo::clear_has_confid() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void TBuildingInfo::clear_confid() {
  confid_ = GOOGLE_ULONGLONG(0);
  clear_has_confid();
}
inline ::google::protobuf::uint64 TBuildingInfo::confid() const {
  // @@protoc_insertion_point(field_get:pb.TBuildingInfo.ConfId)
  return confid_;
}
inline void TBuildingInfo::set_confid(::google::protobuf::uint64 value) {
  set_has_confid();
  confid_ = value;
  // @@protoc_insertion_point(field_set:pb.TBuildingInfo.ConfId)
}

// optional int32 Yield = 3;
inline bool TBuildingInfo::has_yield() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void TBuildingInfo::set_has_yield() {
  _has_bits_[0] |= 0x00000004u;
}
inline void TBuildingInfo::clear_has_yield() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void TBuildingInfo::clear_yield() {
  yield_ = 0;
  clear_has_yield();
}
inline ::google::protobuf::int32 TBuildingInfo::yield() const {
  // @@protoc_insertion_point(field_get:pb.TBuildingInfo.Yield)
  return yield_;
}
inline void TBuildingInfo::set_yield(::google::protobuf::int32 value) {
  set_has_yield();
  yield_ = value;
  // @@protoc_insertion_point(field_set:pb.TBuildingInfo.Yield)
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace pb

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_net_2fBuilding_2eproto__INCLUDED
