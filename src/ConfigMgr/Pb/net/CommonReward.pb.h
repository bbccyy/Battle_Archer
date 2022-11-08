// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: net/CommonReward.proto

#ifndef PROTOBUF_net_2fCommonReward_2eproto__INCLUDED
#define PROTOBUF_net_2fCommonReward_2eproto__INCLUDED

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
void  protobuf_AddDesc_net_2fCommonReward_2eproto();
void protobuf_AssignDesc_net_2fCommonReward_2eproto();
void protobuf_ShutdownFile_net_2fCommonReward_2eproto();

class TCommonReward;

// ===================================================================

/*FOR2LUA
<Record>
	<name>TCommonReward</name>
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
		<replaceName>net/CommonReward.proto</replaceName>
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
class TCommonReward : public ::google::protobuf::Message {
 public:
  TCommonReward();
  virtual ~TCommonReward();

  TCommonReward(const TCommonReward& from);

  inline TCommonReward& operator=(const TCommonReward& from) {
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
  static const TCommonReward& default_instance();

  void Swap(TCommonReward* other);

  // implements Message ----------------------------------------------

  TCommonReward* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const TCommonReward& from);
  void MergeFrom(const TCommonReward& from);
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

  // optional uint32 RewardType = 1;
  inline bool has_rewardtype() const;
  inline void clear_rewardtype();
  static const int kRewardTypeFieldNumber = 1;
  /*FOR2LUA
  <Record>
  	<name>TCommonReward</name>
  	<Function>
  		<name>rewardtype</name>
  		<replaceName>RewardType</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>set_rewardtype</name>
  		<replaceName>RewardType</replaceName>
  		<handler>descripter = pb_set_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_rewardtype</name>
  		<replaceName>RewardType</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline ::google::protobuf::uint32 rewardtype() const;
  inline void set_rewardtype(::google::protobuf::uint32 value);

  // optional uint32 Tid = 2;
  inline bool has_tid() const;
  inline void clear_tid();
  static const int kTidFieldNumber = 2;
  /*FOR2LUA
  <Record>
  	<name>TCommonReward</name>
  	<Function>
  		<name>tid</name>
  		<replaceName>Tid</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>set_tid</name>
  		<replaceName>Tid</replaceName>
  		<handler>descripter = pb_set_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_tid</name>
  		<replaceName>Tid</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline ::google::protobuf::uint32 tid() const;
  inline void set_tid(::google::protobuf::uint32 value);

  // optional uint64 Num = 3;
  inline bool has_num() const;
  inline void clear_num();
  static const int kNumFieldNumber = 3;
  /*FOR2LUA
  <Record>
  	<name>TCommonReward</name>
  	<Function>
  		<name>num</name>
  		<replaceName>Num</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>set_num</name>
  		<replaceName>Num</replaceName>
  		<handler>descripter = pb_set_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_num</name>
  		<replaceName>Num</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline ::google::protobuf::uint64 num() const;
  inline void set_num(::google::protobuf::uint64 value);

  // @@protoc_insertion_point(class_scope:pb.TCommonReward)
 private:
  inline void set_has_rewardtype();
  inline void clear_has_rewardtype();
  inline void set_has_tid();
  inline void clear_has_tid();
  inline void set_has_num();
  inline void clear_has_num();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::uint32 rewardtype_;
  ::google::protobuf::uint32 tid_;
  ::google::protobuf::uint64 num_;
  friend void  protobuf_AddDesc_net_2fCommonReward_2eproto();
  friend void protobuf_AssignDesc_net_2fCommonReward_2eproto();
  friend void protobuf_ShutdownFile_net_2fCommonReward_2eproto();

  void InitAsDefaultInstance();
  static TCommonReward* default_instance_;
};
// ===================================================================


// ===================================================================

// TCommonReward

// optional uint32 RewardType = 1;
inline bool TCommonReward::has_rewardtype() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void TCommonReward::set_has_rewardtype() {
  _has_bits_[0] |= 0x00000001u;
}
inline void TCommonReward::clear_has_rewardtype() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void TCommonReward::clear_rewardtype() {
  rewardtype_ = 0u;
  clear_has_rewardtype();
}
inline ::google::protobuf::uint32 TCommonReward::rewardtype() const {
  // @@protoc_insertion_point(field_get:pb.TCommonReward.RewardType)
  return rewardtype_;
}
inline void TCommonReward::set_rewardtype(::google::protobuf::uint32 value) {
  set_has_rewardtype();
  rewardtype_ = value;
  // @@protoc_insertion_point(field_set:pb.TCommonReward.RewardType)
}

// optional uint32 Tid = 2;
inline bool TCommonReward::has_tid() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void TCommonReward::set_has_tid() {
  _has_bits_[0] |= 0x00000002u;
}
inline void TCommonReward::clear_has_tid() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void TCommonReward::clear_tid() {
  tid_ = 0u;
  clear_has_tid();
}
inline ::google::protobuf::uint32 TCommonReward::tid() const {
  // @@protoc_insertion_point(field_get:pb.TCommonReward.Tid)
  return tid_;
}
inline void TCommonReward::set_tid(::google::protobuf::uint32 value) {
  set_has_tid();
  tid_ = value;
  // @@protoc_insertion_point(field_set:pb.TCommonReward.Tid)
}

// optional uint64 Num = 3;
inline bool TCommonReward::has_num() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void TCommonReward::set_has_num() {
  _has_bits_[0] |= 0x00000004u;
}
inline void TCommonReward::clear_has_num() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void TCommonReward::clear_num() {
  num_ = GOOGLE_ULONGLONG(0);
  clear_has_num();
}
inline ::google::protobuf::uint64 TCommonReward::num() const {
  // @@protoc_insertion_point(field_get:pb.TCommonReward.Num)
  return num_;
}
inline void TCommonReward::set_num(::google::protobuf::uint64 value) {
  set_has_num();
  num_ = value;
  // @@protoc_insertion_point(field_set:pb.TCommonReward.Num)
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

#endif  // PROTOBUF_net_2fCommonReward_2eproto__INCLUDED