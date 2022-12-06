// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: net/CashCow.proto

#ifndef PROTOBUF_net_2fCashCow_2eproto__INCLUDED
#define PROTOBUF_net_2fCashCow_2eproto__INCLUDED

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
#include "net/CommonReward.pb.h"
// @@protoc_insertion_point(includes)

namespace pb {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_net_2fCashCow_2eproto();
void protobuf_AssignDesc_net_2fCashCow_2eproto();
void protobuf_ShutdownFile_net_2fCashCow_2eproto();

class TCashCowGetInfoRsp;
class TCashCowDivineRsp;
class TCashCowRollReq;
class TCashCowRollResult;
class TCashCowRollRsp;

// ===================================================================

/*FOR2LUA
<Record>
	<name>TCashCowGetInfoRsp</name>
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
		<replaceName>net/CashCow.proto</replaceName>
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
class TCashCowGetInfoRsp : public ::google::protobuf::Message {
 public:
  TCashCowGetInfoRsp();
  virtual ~TCashCowGetInfoRsp();

  TCashCowGetInfoRsp(const TCashCowGetInfoRsp& from);

  inline TCashCowGetInfoRsp& operator=(const TCashCowGetInfoRsp& from) {
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
  static const TCashCowGetInfoRsp& default_instance();

  void Swap(TCashCowGetInfoRsp* other);

  // implements Message ----------------------------------------------

  TCashCowGetInfoRsp* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const TCashCowGetInfoRsp& from);
  void MergeFrom(const TCashCowGetInfoRsp& from);
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

  // optional uint32 SysDivination = 1;
  inline bool has_sysdivination() const;
  inline void clear_sysdivination();
  static const int kSysDivinationFieldNumber = 1;
  /*FOR2LUA
  <Record>
  	<name>TCashCowGetInfoRsp</name>
  	<Function>
  		<name>sysdivination</name>
  		<replaceName>SysDivination</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>set_sysdivination</name>
  		<replaceName>SysDivination</replaceName>
  		<handler>descripter = pb_set_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_sysdivination</name>
  		<replaceName>SysDivination</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline ::google::protobuf::uint32 sysdivination() const;
  inline void set_sysdivination(::google::protobuf::uint32 value);

  // optional uint32 Divination = 2;
  inline bool has_divination() const;
  inline void clear_divination();
  static const int kDivinationFieldNumber = 2;
  /*FOR2LUA
  <Record>
  	<name>TCashCowGetInfoRsp</name>
  	<Function>
  		<name>divination</name>
  		<replaceName>Divination</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>set_divination</name>
  		<replaceName>Divination</replaceName>
  		<handler>descripter = pb_set_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_divination</name>
  		<replaceName>Divination</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline ::google::protobuf::uint32 divination() const;
  inline void set_divination(::google::protobuf::uint32 value);

  // optional uint32 RollNum = 3;
  inline bool has_rollnum() const;
  inline void clear_rollnum();
  static const int kRollNumFieldNumber = 3;
  /*FOR2LUA
  <Record>
  	<name>TCashCowGetInfoRsp</name>
  	<Function>
  		<name>rollnum</name>
  		<replaceName>RollNum</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>set_rollnum</name>
  		<replaceName>RollNum</replaceName>
  		<handler>descripter = pb_set_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_rollnum</name>
  		<replaceName>RollNum</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline ::google::protobuf::uint32 rollnum() const;
  inline void set_rollnum(::google::protobuf::uint32 value);

  // optional uint32 FreeNum = 4;
  inline bool has_freenum() const;
  inline void clear_freenum();
  static const int kFreeNumFieldNumber = 4;
  /*FOR2LUA
  <Record>
  	<name>TCashCowGetInfoRsp</name>
  	<Function>
  		<name>freenum</name>
  		<replaceName>FreeNum</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>set_freenum</name>
  		<replaceName>FreeNum</replaceName>
  		<handler>descripter = pb_set_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_freenum</name>
  		<replaceName>FreeNum</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline ::google::protobuf::uint32 freenum() const;
  inline void set_freenum(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:pb.TCashCowGetInfoRsp)
 private:
  inline void set_has_sysdivination();
  inline void clear_has_sysdivination();
  inline void set_has_divination();
  inline void clear_has_divination();
  inline void set_has_rollnum();
  inline void clear_has_rollnum();
  inline void set_has_freenum();
  inline void clear_has_freenum();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::uint32 sysdivination_;
  ::google::protobuf::uint32 divination_;
  ::google::protobuf::uint32 rollnum_;
  ::google::protobuf::uint32 freenum_;
  friend void  protobuf_AddDesc_net_2fCashCow_2eproto();
  friend void protobuf_AssignDesc_net_2fCashCow_2eproto();
  friend void protobuf_ShutdownFile_net_2fCashCow_2eproto();

  void InitAsDefaultInstance();
  static TCashCowGetInfoRsp* default_instance_;
};
// -------------------------------------------------------------------

/*FOR2LUA
<Record>
	<name>TCashCowDivineRsp</name>
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
		<replaceName>net/CashCow.proto</replaceName>
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
class TCashCowDivineRsp : public ::google::protobuf::Message {
 public:
  TCashCowDivineRsp();
  virtual ~TCashCowDivineRsp();

  TCashCowDivineRsp(const TCashCowDivineRsp& from);

  inline TCashCowDivineRsp& operator=(const TCashCowDivineRsp& from) {
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
  static const TCashCowDivineRsp& default_instance();

  void Swap(TCashCowDivineRsp* other);

  // implements Message ----------------------------------------------

  TCashCowDivineRsp* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const TCashCowDivineRsp& from);
  void MergeFrom(const TCashCowDivineRsp& from);
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

  // optional uint32 Divination = 1;
  inline bool has_divination() const;
  inline void clear_divination();
  static const int kDivinationFieldNumber = 1;
  /*FOR2LUA
  <Record>
  	<name>TCashCowDivineRsp</name>
  	<Function>
  		<name>divination</name>
  		<replaceName>Divination</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>set_divination</name>
  		<replaceName>Divination</replaceName>
  		<handler>descripter = pb_set_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_divination</name>
  		<replaceName>Divination</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline ::google::protobuf::uint32 divination() const;
  inline void set_divination(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:pb.TCashCowDivineRsp)
 private:
  inline void set_has_divination();
  inline void clear_has_divination();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::uint32 divination_;
  friend void  protobuf_AddDesc_net_2fCashCow_2eproto();
  friend void protobuf_AssignDesc_net_2fCashCow_2eproto();
  friend void protobuf_ShutdownFile_net_2fCashCow_2eproto();

  void InitAsDefaultInstance();
  static TCashCowDivineRsp* default_instance_;
};
// -------------------------------------------------------------------

/*FOR2LUA
<Record>
	<name>TCashCowRollReq</name>
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
		<replaceName>net/CashCow.proto</replaceName>
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
class TCashCowRollReq : public ::google::protobuf::Message {
 public:
  TCashCowRollReq();
  virtual ~TCashCowRollReq();

  TCashCowRollReq(const TCashCowRollReq& from);

  inline TCashCowRollReq& operator=(const TCashCowRollReq& from) {
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
  static const TCashCowRollReq& default_instance();

  void Swap(TCashCowRollReq* other);

  // implements Message ----------------------------------------------

  TCashCowRollReq* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const TCashCowRollReq& from);
  void MergeFrom(const TCashCowRollReq& from);
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

  // optional uint32 RollType = 1;
  inline bool has_rolltype() const;
  inline void clear_rolltype();
  static const int kRollTypeFieldNumber = 1;
  /*FOR2LUA
  <Record>
  	<name>TCashCowRollReq</name>
  	<Function>
  		<name>rolltype</name>
  		<replaceName>RollType</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>set_rolltype</name>
  		<replaceName>RollType</replaceName>
  		<handler>descripter = pb_set_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_rolltype</name>
  		<replaceName>RollType</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline ::google::protobuf::uint32 rolltype() const;
  inline void set_rolltype(::google::protobuf::uint32 value);

  // optional uint32 RollNum = 2;
  inline bool has_rollnum() const;
  inline void clear_rollnum();
  static const int kRollNumFieldNumber = 2;
  /*FOR2LUA
  <Record>
  	<name>TCashCowRollReq</name>
  	<Function>
  		<name>rollnum</name>
  		<replaceName>RollNum</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>set_rollnum</name>
  		<replaceName>RollNum</replaceName>
  		<handler>descripter = pb_set_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_rollnum</name>
  		<replaceName>RollNum</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline ::google::protobuf::uint32 rollnum() const;
  inline void set_rollnum(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:pb.TCashCowRollReq)
 private:
  inline void set_has_rolltype();
  inline void clear_has_rolltype();
  inline void set_has_rollnum();
  inline void clear_has_rollnum();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::uint32 rolltype_;
  ::google::protobuf::uint32 rollnum_;
  friend void  protobuf_AddDesc_net_2fCashCow_2eproto();
  friend void protobuf_AssignDesc_net_2fCashCow_2eproto();
  friend void protobuf_ShutdownFile_net_2fCashCow_2eproto();

  void InitAsDefaultInstance();
  static TCashCowRollReq* default_instance_;
};
// -------------------------------------------------------------------

/*FOR2LUA
<Record>
	<name>TCashCowRollResult</name>
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
		<replaceName>net/CashCow.proto</replaceName>
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
class TCashCowRollResult : public ::google::protobuf::Message {
 public:
  TCashCowRollResult();
  virtual ~TCashCowRollResult();

  TCashCowRollResult(const TCashCowRollResult& from);

  inline TCashCowRollResult& operator=(const TCashCowRollResult& from) {
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
  static const TCashCowRollResult& default_instance();

  void Swap(TCashCowRollResult* other);

  // implements Message ----------------------------------------------

  TCashCowRollResult* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const TCashCowRollResult& from);
  void MergeFrom(const TCashCowRollResult& from);
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

  // optional uint32 CritRatio = 1;
  inline bool has_critratio() const;
  inline void clear_critratio();
  static const int kCritRatioFieldNumber = 1;
  /*FOR2LUA
  <Record>
  	<name>TCashCowRollResult</name>
  	<Function>
  		<name>critratio</name>
  		<replaceName>CritRatio</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>set_critratio</name>
  		<replaceName>CritRatio</replaceName>
  		<handler>descripter = pb_set_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_critratio</name>
  		<replaceName>CritRatio</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline ::google::protobuf::uint32 critratio() const;
  inline void set_critratio(::google::protobuf::uint32 value);

  // optional .pb.TCommonReward Reward = 2;
  inline bool has_reward() const;
  inline void clear_reward();
  static const int kRewardFieldNumber = 2;
  /*FOR2LUA
  <Record>
  	<name>TCashCowRollResult</name>
  	<Function>
  		<name>reward</name>
  		<replaceName>Reward</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>set_reward</name>
  		<replaceName>Reward</replaceName>
  		<handler>descripter = pb_set_message_cpp()</handler>
  	</Function>
  	<Function>
  		<name>set_allocated_reward</name>
  		<replaceName>Reward</replaceName>
  		<handler>descripter = pb_set_message_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_reward</name>
  		<replaceName>Reward</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline const ::pb::TCommonReward& reward() const;
  inline ::pb::TCommonReward* mutable_reward();
  inline ::pb::TCommonReward* release_reward();
  inline void set_allocated_reward(::pb::TCommonReward* reward);

  // @@protoc_insertion_point(class_scope:pb.TCashCowRollResult)
 private:
  inline void set_has_critratio();
  inline void clear_has_critratio();
  inline void set_has_reward();
  inline void clear_has_reward();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::pb::TCommonReward* reward_;
  ::google::protobuf::uint32 critratio_;
  friend void  protobuf_AddDesc_net_2fCashCow_2eproto();
  friend void protobuf_AssignDesc_net_2fCashCow_2eproto();
  friend void protobuf_ShutdownFile_net_2fCashCow_2eproto();

  void InitAsDefaultInstance();
  static TCashCowRollResult* default_instance_;
};
// -------------------------------------------------------------------

/*FOR2LUA
<Record>
	<name>TCashCowRollRsp</name>
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
		<replaceName>net/CashCow.proto</replaceName>
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
class TCashCowRollRsp : public ::google::protobuf::Message {
 public:
  TCashCowRollRsp();
  virtual ~TCashCowRollRsp();

  TCashCowRollRsp(const TCashCowRollRsp& from);

  inline TCashCowRollRsp& operator=(const TCashCowRollRsp& from) {
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
  static const TCashCowRollRsp& default_instance();

  void Swap(TCashCowRollRsp* other);

  // implements Message ----------------------------------------------

  TCashCowRollRsp* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const TCashCowRollRsp& from);
  void MergeFrom(const TCashCowRollRsp& from);
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

  // repeated .pb.TCashCowRollResult ResultArr = 1;
  inline int resultarr_size() const;
  inline void clear_resultarr();
  static const int kResultArrFieldNumber = 1;
  /*FOR2LUA
  <Record>
  	<name>TCashCowRollRsp</name>
  	<Function>
  		<name>resultarr</name>
  		<replaceName>ResultArr</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>mutable_resultarr</name>
  		<replaceName>ResultArr</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>add_resultarr</name>
  		<replaceName>ResultArr</replaceName>
  		<handler>descripter = pb_repeated_add_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_resultarr</name>
  		<replaceName>ResultArr</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  	<Function>
  		<name>resultarr_size</name>
  		<replaceName>ResultArr</replaceName>
  		<handler>descripter = pb_repeated_size_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline const ::pb::TCashCowRollResult& resultarr(int index) const;
  inline ::pb::TCashCowRollResult* mutable_resultarr(int index);
  inline ::pb::TCashCowRollResult* add_resultarr();
  inline const ::google::protobuf::RepeatedPtrField< ::pb::TCashCowRollResult >&
      resultarr() const;
  inline ::google::protobuf::RepeatedPtrField< ::pb::TCashCowRollResult >*
      mutable_resultarr();

  // @@protoc_insertion_point(class_scope:pb.TCashCowRollRsp)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::RepeatedPtrField< ::pb::TCashCowRollResult > resultarr_;
  friend void  protobuf_AddDesc_net_2fCashCow_2eproto();
  friend void protobuf_AssignDesc_net_2fCashCow_2eproto();
  friend void protobuf_ShutdownFile_net_2fCashCow_2eproto();

  void InitAsDefaultInstance();
  static TCashCowRollRsp* default_instance_;
};
// ===================================================================


// ===================================================================

// TCashCowGetInfoRsp

// optional uint32 SysDivination = 1;
inline bool TCashCowGetInfoRsp::has_sysdivination() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void TCashCowGetInfoRsp::set_has_sysdivination() {
  _has_bits_[0] |= 0x00000001u;
}
inline void TCashCowGetInfoRsp::clear_has_sysdivination() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void TCashCowGetInfoRsp::clear_sysdivination() {
  sysdivination_ = 0u;
  clear_has_sysdivination();
}
inline ::google::protobuf::uint32 TCashCowGetInfoRsp::sysdivination() const {
  // @@protoc_insertion_point(field_get:pb.TCashCowGetInfoRsp.SysDivination)
  return sysdivination_;
}
inline void TCashCowGetInfoRsp::set_sysdivination(::google::protobuf::uint32 value) {
  set_has_sysdivination();
  sysdivination_ = value;
  // @@protoc_insertion_point(field_set:pb.TCashCowGetInfoRsp.SysDivination)
}

// optional uint32 Divination = 2;
inline bool TCashCowGetInfoRsp::has_divination() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void TCashCowGetInfoRsp::set_has_divination() {
  _has_bits_[0] |= 0x00000002u;
}
inline void TCashCowGetInfoRsp::clear_has_divination() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void TCashCowGetInfoRsp::clear_divination() {
  divination_ = 0u;
  clear_has_divination();
}
inline ::google::protobuf::uint32 TCashCowGetInfoRsp::divination() const {
  // @@protoc_insertion_point(field_get:pb.TCashCowGetInfoRsp.Divination)
  return divination_;
}
inline void TCashCowGetInfoRsp::set_divination(::google::protobuf::uint32 value) {
  set_has_divination();
  divination_ = value;
  // @@protoc_insertion_point(field_set:pb.TCashCowGetInfoRsp.Divination)
}

// optional uint32 RollNum = 3;
inline bool TCashCowGetInfoRsp::has_rollnum() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void TCashCowGetInfoRsp::set_has_rollnum() {
  _has_bits_[0] |= 0x00000004u;
}
inline void TCashCowGetInfoRsp::clear_has_rollnum() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void TCashCowGetInfoRsp::clear_rollnum() {
  rollnum_ = 0u;
  clear_has_rollnum();
}
inline ::google::protobuf::uint32 TCashCowGetInfoRsp::rollnum() const {
  // @@protoc_insertion_point(field_get:pb.TCashCowGetInfoRsp.RollNum)
  return rollnum_;
}
inline void TCashCowGetInfoRsp::set_rollnum(::google::protobuf::uint32 value) {
  set_has_rollnum();
  rollnum_ = value;
  // @@protoc_insertion_point(field_set:pb.TCashCowGetInfoRsp.RollNum)
}

// optional uint32 FreeNum = 4;
inline bool TCashCowGetInfoRsp::has_freenum() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void TCashCowGetInfoRsp::set_has_freenum() {
  _has_bits_[0] |= 0x00000008u;
}
inline void TCashCowGetInfoRsp::clear_has_freenum() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void TCashCowGetInfoRsp::clear_freenum() {
  freenum_ = 0u;
  clear_has_freenum();
}
inline ::google::protobuf::uint32 TCashCowGetInfoRsp::freenum() const {
  // @@protoc_insertion_point(field_get:pb.TCashCowGetInfoRsp.FreeNum)
  return freenum_;
}
inline void TCashCowGetInfoRsp::set_freenum(::google::protobuf::uint32 value) {
  set_has_freenum();
  freenum_ = value;
  // @@protoc_insertion_point(field_set:pb.TCashCowGetInfoRsp.FreeNum)
}

// -------------------------------------------------------------------

// TCashCowDivineRsp

// optional uint32 Divination = 1;
inline bool TCashCowDivineRsp::has_divination() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void TCashCowDivineRsp::set_has_divination() {
  _has_bits_[0] |= 0x00000001u;
}
inline void TCashCowDivineRsp::clear_has_divination() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void TCashCowDivineRsp::clear_divination() {
  divination_ = 0u;
  clear_has_divination();
}
inline ::google::protobuf::uint32 TCashCowDivineRsp::divination() const {
  // @@protoc_insertion_point(field_get:pb.TCashCowDivineRsp.Divination)
  return divination_;
}
inline void TCashCowDivineRsp::set_divination(::google::protobuf::uint32 value) {
  set_has_divination();
  divination_ = value;
  // @@protoc_insertion_point(field_set:pb.TCashCowDivineRsp.Divination)
}

// -------------------------------------------------------------------

// TCashCowRollReq

// optional uint32 RollType = 1;
inline bool TCashCowRollReq::has_rolltype() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void TCashCowRollReq::set_has_rolltype() {
  _has_bits_[0] |= 0x00000001u;
}
inline void TCashCowRollReq::clear_has_rolltype() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void TCashCowRollReq::clear_rolltype() {
  rolltype_ = 0u;
  clear_has_rolltype();
}
inline ::google::protobuf::uint32 TCashCowRollReq::rolltype() const {
  // @@protoc_insertion_point(field_get:pb.TCashCowRollReq.RollType)
  return rolltype_;
}
inline void TCashCowRollReq::set_rolltype(::google::protobuf::uint32 value) {
  set_has_rolltype();
  rolltype_ = value;
  // @@protoc_insertion_point(field_set:pb.TCashCowRollReq.RollType)
}

// optional uint32 RollNum = 2;
inline bool TCashCowRollReq::has_rollnum() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void TCashCowRollReq::set_has_rollnum() {
  _has_bits_[0] |= 0x00000002u;
}
inline void TCashCowRollReq::clear_has_rollnum() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void TCashCowRollReq::clear_rollnum() {
  rollnum_ = 0u;
  clear_has_rollnum();
}
inline ::google::protobuf::uint32 TCashCowRollReq::rollnum() const {
  // @@protoc_insertion_point(field_get:pb.TCashCowRollReq.RollNum)
  return rollnum_;
}
inline void TCashCowRollReq::set_rollnum(::google::protobuf::uint32 value) {
  set_has_rollnum();
  rollnum_ = value;
  // @@protoc_insertion_point(field_set:pb.TCashCowRollReq.RollNum)
}

// -------------------------------------------------------------------

// TCashCowRollResult

// optional uint32 CritRatio = 1;
inline bool TCashCowRollResult::has_critratio() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void TCashCowRollResult::set_has_critratio() {
  _has_bits_[0] |= 0x00000001u;
}
inline void TCashCowRollResult::clear_has_critratio() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void TCashCowRollResult::clear_critratio() {
  critratio_ = 0u;
  clear_has_critratio();
}
inline ::google::protobuf::uint32 TCashCowRollResult::critratio() const {
  // @@protoc_insertion_point(field_get:pb.TCashCowRollResult.CritRatio)
  return critratio_;
}
inline void TCashCowRollResult::set_critratio(::google::protobuf::uint32 value) {
  set_has_critratio();
  critratio_ = value;
  // @@protoc_insertion_point(field_set:pb.TCashCowRollResult.CritRatio)
}

// optional .pb.TCommonReward Reward = 2;
inline bool TCashCowRollResult::has_reward() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void TCashCowRollResult::set_has_reward() {
  _has_bits_[0] |= 0x00000002u;
}
inline void TCashCowRollResult::clear_has_reward() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void TCashCowRollResult::clear_reward() {
  if (reward_ != NULL) reward_->::pb::TCommonReward::Clear();
  clear_has_reward();
}
inline const ::pb::TCommonReward& TCashCowRollResult::reward() const {
  // @@protoc_insertion_point(field_get:pb.TCashCowRollResult.Reward)
  return reward_ != NULL ? *reward_ : *default_instance_->reward_;
}
inline ::pb::TCommonReward* TCashCowRollResult::mutable_reward() {
  set_has_reward();
  if (reward_ == NULL) reward_ = new ::pb::TCommonReward;
  // @@protoc_insertion_point(field_mutable:pb.TCashCowRollResult.Reward)
  return reward_;
}
inline ::pb::TCommonReward* TCashCowRollResult::release_reward() {
  clear_has_reward();
  ::pb::TCommonReward* temp = reward_;
  reward_ = NULL;
  return temp;
}
inline void TCashCowRollResult::set_allocated_reward(::pb::TCommonReward* reward) {
  delete reward_;
  reward_ = reward;
  if (reward) {
    set_has_reward();
  } else {
    clear_has_reward();
  }
  // @@protoc_insertion_point(field_set_allocated:pb.TCashCowRollResult.Reward)
}

// -------------------------------------------------------------------

// TCashCowRollRsp

// repeated .pb.TCashCowRollResult ResultArr = 1;
inline int TCashCowRollRsp::resultarr_size() const {
  return resultarr_.size();
}
inline void TCashCowRollRsp::clear_resultarr() {
  resultarr_.Clear();
}
inline const ::pb::TCashCowRollResult& TCashCowRollRsp::resultarr(int index) const {
  // @@protoc_insertion_point(field_get:pb.TCashCowRollRsp.ResultArr)
  return resultarr_.Get(index);
}
inline ::pb::TCashCowRollResult* TCashCowRollRsp::mutable_resultarr(int index) {
  // @@protoc_insertion_point(field_mutable:pb.TCashCowRollRsp.ResultArr)
  return resultarr_.Mutable(index);
}
inline ::pb::TCashCowRollResult* TCashCowRollRsp::add_resultarr() {
  // @@protoc_insertion_point(field_add:pb.TCashCowRollRsp.ResultArr)
  return resultarr_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::pb::TCashCowRollResult >&
TCashCowRollRsp::resultarr() const {
  // @@protoc_insertion_point(field_list:pb.TCashCowRollRsp.ResultArr)
  return resultarr_;
}
inline ::google::protobuf::RepeatedPtrField< ::pb::TCashCowRollResult >*
TCashCowRollRsp::mutable_resultarr() {
  // @@protoc_insertion_point(field_mutable_list:pb.TCashCowRollRsp.ResultArr)
  return &resultarr_;
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

#endif  // PROTOBUF_net_2fCashCow_2eproto__INCLUDED
