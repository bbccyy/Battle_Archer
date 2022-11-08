// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: net/ActPresentLove.proto

#ifndef PROTOBUF_net_2fActPresentLove_2eproto__INCLUDED
#define PROTOBUF_net_2fActPresentLove_2eproto__INCLUDED

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
void  protobuf_AddDesc_net_2fActPresentLove_2eproto();
void protobuf_AssignDesc_net_2fActPresentLove_2eproto();
void protobuf_ShutdownFile_net_2fActPresentLove_2eproto();

class TActPresentLoveGetInfoRsp;
class TActPresentLovePresentLoveRsp;
class TActPresentLoveGetRewardReq;
class TActPresentLoveGetRewardRsp;

// ===================================================================

/*FOR2LUA
<Record>
	<name>TActPresentLoveGetInfoRsp</name>
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
		<replaceName>net/ActPresentLove.proto</replaceName>
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
class TActPresentLoveGetInfoRsp : public ::google::protobuf::Message {
 public:
  TActPresentLoveGetInfoRsp();
  virtual ~TActPresentLoveGetInfoRsp();

  TActPresentLoveGetInfoRsp(const TActPresentLoveGetInfoRsp& from);

  inline TActPresentLoveGetInfoRsp& operator=(const TActPresentLoveGetInfoRsp& from) {
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
  static const TActPresentLoveGetInfoRsp& default_instance();

  void Swap(TActPresentLoveGetInfoRsp* other);

  // implements Message ----------------------------------------------

  TActPresentLoveGetInfoRsp* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const TActPresentLoveGetInfoRsp& from);
  void MergeFrom(const TActPresentLoveGetInfoRsp& from);
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

  // optional uint64 LoveCount = 1;
  inline bool has_lovecount() const;
  inline void clear_lovecount();
  static const int kLoveCountFieldNumber = 1;
  /*FOR2LUA
  <Record>
  	<name>TActPresentLoveGetInfoRsp</name>
  	<Function>
  		<name>lovecount</name>
  		<replaceName>LoveCount</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>set_lovecount</name>
  		<replaceName>LoveCount</replaceName>
  		<handler>descripter = pb_set_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_lovecount</name>
  		<replaceName>LoveCount</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline ::google::protobuf::uint64 lovecount() const;
  inline void set_lovecount(::google::protobuf::uint64 value);

  // optional uint32 DailyLoveNum = 2;
  inline bool has_dailylovenum() const;
  inline void clear_dailylovenum();
  static const int kDailyLoveNumFieldNumber = 2;
  /*FOR2LUA
  <Record>
  	<name>TActPresentLoveGetInfoRsp</name>
  	<Function>
  		<name>dailylovenum</name>
  		<replaceName>DailyLoveNum</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>set_dailylovenum</name>
  		<replaceName>DailyLoveNum</replaceName>
  		<handler>descripter = pb_set_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_dailylovenum</name>
  		<replaceName>DailyLoveNum</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline ::google::protobuf::uint32 dailylovenum() const;
  inline void set_dailylovenum(::google::protobuf::uint32 value);

  // repeated uint32 RewardIdArr = 3;
  inline int rewardidarr_size() const;
  inline void clear_rewardidarr();
  static const int kRewardIdArrFieldNumber = 3;
  /*FOR2LUA
  <Record>
  	<name>TActPresentLoveGetInfoRsp</name>
  	<Function>
  		<name>rewardidarr</name>
  		<replaceName>RewardIdArr</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>mutable_rewardidarr</name>
  		<replaceName>RewardIdArr</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>add_rewardidarr</name>
  		<replaceName>RewardIdArr</replaceName>
  		<handler>descripter = pb_repeated_add_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_rewardidarr</name>
  		<replaceName>RewardIdArr</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  	<Function>
  		<name>rewardidarr_size</name>
  		<replaceName>RewardIdArr</replaceName>
  		<handler>descripter = pb_repeated_size_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline ::google::protobuf::uint32 rewardidarr(int index) const;
  inline void set_rewardidarr(int index, ::google::protobuf::uint32 value);
  inline void add_rewardidarr(::google::protobuf::uint32 value);
  inline const ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >&
      rewardidarr() const;
  inline ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >*
      mutable_rewardidarr();

  // @@protoc_insertion_point(class_scope:pb.TActPresentLoveGetInfoRsp)
 private:
  inline void set_has_lovecount();
  inline void clear_has_lovecount();
  inline void set_has_dailylovenum();
  inline void clear_has_dailylovenum();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::uint64 lovecount_;
  ::google::protobuf::RepeatedField< ::google::protobuf::uint32 > rewardidarr_;
  ::google::protobuf::uint32 dailylovenum_;
  friend void  protobuf_AddDesc_net_2fActPresentLove_2eproto();
  friend void protobuf_AssignDesc_net_2fActPresentLove_2eproto();
  friend void protobuf_ShutdownFile_net_2fActPresentLove_2eproto();

  void InitAsDefaultInstance();
  static TActPresentLoveGetInfoRsp* default_instance_;
};
// -------------------------------------------------------------------

/*FOR2LUA
<Record>
	<name>TActPresentLovePresentLoveRsp</name>
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
		<replaceName>net/ActPresentLove.proto</replaceName>
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
class TActPresentLovePresentLoveRsp : public ::google::protobuf::Message {
 public:
  TActPresentLovePresentLoveRsp();
  virtual ~TActPresentLovePresentLoveRsp();

  TActPresentLovePresentLoveRsp(const TActPresentLovePresentLoveRsp& from);

  inline TActPresentLovePresentLoveRsp& operator=(const TActPresentLovePresentLoveRsp& from) {
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
  static const TActPresentLovePresentLoveRsp& default_instance();

  void Swap(TActPresentLovePresentLoveRsp* other);

  // implements Message ----------------------------------------------

  TActPresentLovePresentLoveRsp* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const TActPresentLovePresentLoveRsp& from);
  void MergeFrom(const TActPresentLovePresentLoveRsp& from);
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

  // optional uint32 DailyLoveNum = 1;
  inline bool has_dailylovenum() const;
  inline void clear_dailylovenum();
  static const int kDailyLoveNumFieldNumber = 1;
  /*FOR2LUA
  <Record>
  	<name>TActPresentLovePresentLoveRsp</name>
  	<Function>
  		<name>dailylovenum</name>
  		<replaceName>DailyLoveNum</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>set_dailylovenum</name>
  		<replaceName>DailyLoveNum</replaceName>
  		<handler>descripter = pb_set_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_dailylovenum</name>
  		<replaceName>DailyLoveNum</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline ::google::protobuf::uint32 dailylovenum() const;
  inline void set_dailylovenum(::google::protobuf::uint32 value);

  // optional uint64 LoveCount = 2;
  inline bool has_lovecount() const;
  inline void clear_lovecount();
  static const int kLoveCountFieldNumber = 2;
  /*FOR2LUA
  <Record>
  	<name>TActPresentLovePresentLoveRsp</name>
  	<Function>
  		<name>lovecount</name>
  		<replaceName>LoveCount</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>set_lovecount</name>
  		<replaceName>LoveCount</replaceName>
  		<handler>descripter = pb_set_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_lovecount</name>
  		<replaceName>LoveCount</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline ::google::protobuf::uint64 lovecount() const;
  inline void set_lovecount(::google::protobuf::uint64 value);

  // repeated .pb.TCommonReward RewardArr = 3;
  inline int rewardarr_size() const;
  inline void clear_rewardarr();
  static const int kRewardArrFieldNumber = 3;
  /*FOR2LUA
  <Record>
  	<name>TActPresentLovePresentLoveRsp</name>
  	<Function>
  		<name>rewardarr</name>
  		<replaceName>RewardArr</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>mutable_rewardarr</name>
  		<replaceName>RewardArr</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>add_rewardarr</name>
  		<replaceName>RewardArr</replaceName>
  		<handler>descripter = pb_repeated_add_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_rewardarr</name>
  		<replaceName>RewardArr</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  	<Function>
  		<name>rewardarr_size</name>
  		<replaceName>RewardArr</replaceName>
  		<handler>descripter = pb_repeated_size_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline const ::pb::TCommonReward& rewardarr(int index) const;
  inline ::pb::TCommonReward* mutable_rewardarr(int index);
  inline ::pb::TCommonReward* add_rewardarr();
  inline const ::google::protobuf::RepeatedPtrField< ::pb::TCommonReward >&
      rewardarr() const;
  inline ::google::protobuf::RepeatedPtrField< ::pb::TCommonReward >*
      mutable_rewardarr();

  // @@protoc_insertion_point(class_scope:pb.TActPresentLovePresentLoveRsp)
 private:
  inline void set_has_dailylovenum();
  inline void clear_has_dailylovenum();
  inline void set_has_lovecount();
  inline void clear_has_lovecount();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::uint64 lovecount_;
  ::google::protobuf::RepeatedPtrField< ::pb::TCommonReward > rewardarr_;
  ::google::protobuf::uint32 dailylovenum_;
  friend void  protobuf_AddDesc_net_2fActPresentLove_2eproto();
  friend void protobuf_AssignDesc_net_2fActPresentLove_2eproto();
  friend void protobuf_ShutdownFile_net_2fActPresentLove_2eproto();

  void InitAsDefaultInstance();
  static TActPresentLovePresentLoveRsp* default_instance_;
};
// -------------------------------------------------------------------

/*FOR2LUA
<Record>
	<name>TActPresentLoveGetRewardReq</name>
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
		<replaceName>net/ActPresentLove.proto</replaceName>
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
class TActPresentLoveGetRewardReq : public ::google::protobuf::Message {
 public:
  TActPresentLoveGetRewardReq();
  virtual ~TActPresentLoveGetRewardReq();

  TActPresentLoveGetRewardReq(const TActPresentLoveGetRewardReq& from);

  inline TActPresentLoveGetRewardReq& operator=(const TActPresentLoveGetRewardReq& from) {
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
  static const TActPresentLoveGetRewardReq& default_instance();

  void Swap(TActPresentLoveGetRewardReq* other);

  // implements Message ----------------------------------------------

  TActPresentLoveGetRewardReq* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const TActPresentLoveGetRewardReq& from);
  void MergeFrom(const TActPresentLoveGetRewardReq& from);
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

  // optional uint32 RewardId = 1;
  inline bool has_rewardid() const;
  inline void clear_rewardid();
  static const int kRewardIdFieldNumber = 1;
  /*FOR2LUA
  <Record>
  	<name>TActPresentLoveGetRewardReq</name>
  	<Function>
  		<name>rewardid</name>
  		<replaceName>RewardId</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>set_rewardid</name>
  		<replaceName>RewardId</replaceName>
  		<handler>descripter = pb_set_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_rewardid</name>
  		<replaceName>RewardId</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline ::google::protobuf::uint32 rewardid() const;
  inline void set_rewardid(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:pb.TActPresentLoveGetRewardReq)
 private:
  inline void set_has_rewardid();
  inline void clear_has_rewardid();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::uint32 rewardid_;
  friend void  protobuf_AddDesc_net_2fActPresentLove_2eproto();
  friend void protobuf_AssignDesc_net_2fActPresentLove_2eproto();
  friend void protobuf_ShutdownFile_net_2fActPresentLove_2eproto();

  void InitAsDefaultInstance();
  static TActPresentLoveGetRewardReq* default_instance_;
};
// -------------------------------------------------------------------

/*FOR2LUA
<Record>
	<name>TActPresentLoveGetRewardRsp</name>
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
		<replaceName>net/ActPresentLove.proto</replaceName>
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
class TActPresentLoveGetRewardRsp : public ::google::protobuf::Message {
 public:
  TActPresentLoveGetRewardRsp();
  virtual ~TActPresentLoveGetRewardRsp();

  TActPresentLoveGetRewardRsp(const TActPresentLoveGetRewardRsp& from);

  inline TActPresentLoveGetRewardRsp& operator=(const TActPresentLoveGetRewardRsp& from) {
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
  static const TActPresentLoveGetRewardRsp& default_instance();

  void Swap(TActPresentLoveGetRewardRsp* other);

  // implements Message ----------------------------------------------

  TActPresentLoveGetRewardRsp* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const TActPresentLoveGetRewardRsp& from);
  void MergeFrom(const TActPresentLoveGetRewardRsp& from);
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

  // repeated .pb.TCommonReward RewardArr = 3;
  inline int rewardarr_size() const;
  inline void clear_rewardarr();
  static const int kRewardArrFieldNumber = 3;
  /*FOR2LUA
  <Record>
  	<name>TActPresentLoveGetRewardRsp</name>
  	<Function>
  		<name>rewardarr</name>
  		<replaceName>RewardArr</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>mutable_rewardarr</name>
  		<replaceName>RewardArr</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>add_rewardarr</name>
  		<replaceName>RewardArr</replaceName>
  		<handler>descripter = pb_repeated_add_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_rewardarr</name>
  		<replaceName>RewardArr</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  	<Function>
  		<name>rewardarr_size</name>
  		<replaceName>RewardArr</replaceName>
  		<handler>descripter = pb_repeated_size_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline const ::pb::TCommonReward& rewardarr(int index) const;
  inline ::pb::TCommonReward* mutable_rewardarr(int index);
  inline ::pb::TCommonReward* add_rewardarr();
  inline const ::google::protobuf::RepeatedPtrField< ::pb::TCommonReward >&
      rewardarr() const;
  inline ::google::protobuf::RepeatedPtrField< ::pb::TCommonReward >*
      mutable_rewardarr();

  // @@protoc_insertion_point(class_scope:pb.TActPresentLoveGetRewardRsp)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::RepeatedPtrField< ::pb::TCommonReward > rewardarr_;
  friend void  protobuf_AddDesc_net_2fActPresentLove_2eproto();
  friend void protobuf_AssignDesc_net_2fActPresentLove_2eproto();
  friend void protobuf_ShutdownFile_net_2fActPresentLove_2eproto();

  void InitAsDefaultInstance();
  static TActPresentLoveGetRewardRsp* default_instance_;
};
// ===================================================================


// ===================================================================

// TActPresentLoveGetInfoRsp

// optional uint64 LoveCount = 1;
inline bool TActPresentLoveGetInfoRsp::has_lovecount() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void TActPresentLoveGetInfoRsp::set_has_lovecount() {
  _has_bits_[0] |= 0x00000001u;
}
inline void TActPresentLoveGetInfoRsp::clear_has_lovecount() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void TActPresentLoveGetInfoRsp::clear_lovecount() {
  lovecount_ = GOOGLE_ULONGLONG(0);
  clear_has_lovecount();
}
inline ::google::protobuf::uint64 TActPresentLoveGetInfoRsp::lovecount() const {
  // @@protoc_insertion_point(field_get:pb.TActPresentLoveGetInfoRsp.LoveCount)
  return lovecount_;
}
inline void TActPresentLoveGetInfoRsp::set_lovecount(::google::protobuf::uint64 value) {
  set_has_lovecount();
  lovecount_ = value;
  // @@protoc_insertion_point(field_set:pb.TActPresentLoveGetInfoRsp.LoveCount)
}

// optional uint32 DailyLoveNum = 2;
inline bool TActPresentLoveGetInfoRsp::has_dailylovenum() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void TActPresentLoveGetInfoRsp::set_has_dailylovenum() {
  _has_bits_[0] |= 0x00000002u;
}
inline void TActPresentLoveGetInfoRsp::clear_has_dailylovenum() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void TActPresentLoveGetInfoRsp::clear_dailylovenum() {
  dailylovenum_ = 0u;
  clear_has_dailylovenum();
}
inline ::google::protobuf::uint32 TActPresentLoveGetInfoRsp::dailylovenum() const {
  // @@protoc_insertion_point(field_get:pb.TActPresentLoveGetInfoRsp.DailyLoveNum)
  return dailylovenum_;
}
inline void TActPresentLoveGetInfoRsp::set_dailylovenum(::google::protobuf::uint32 value) {
  set_has_dailylovenum();
  dailylovenum_ = value;
  // @@protoc_insertion_point(field_set:pb.TActPresentLoveGetInfoRsp.DailyLoveNum)
}

// repeated uint32 RewardIdArr = 3;
inline int TActPresentLoveGetInfoRsp::rewardidarr_size() const {
  return rewardidarr_.size();
}
inline void TActPresentLoveGetInfoRsp::clear_rewardidarr() {
  rewardidarr_.Clear();
}
inline ::google::protobuf::uint32 TActPresentLoveGetInfoRsp::rewardidarr(int index) const {
  // @@protoc_insertion_point(field_get:pb.TActPresentLoveGetInfoRsp.RewardIdArr)
  return rewardidarr_.Get(index);
}
inline void TActPresentLoveGetInfoRsp::set_rewardidarr(int index, ::google::protobuf::uint32 value) {
  rewardidarr_.Set(index, value);
  // @@protoc_insertion_point(field_set:pb.TActPresentLoveGetInfoRsp.RewardIdArr)
}
inline void TActPresentLoveGetInfoRsp::add_rewardidarr(::google::protobuf::uint32 value) {
  rewardidarr_.Add(value);
  // @@protoc_insertion_point(field_add:pb.TActPresentLoveGetInfoRsp.RewardIdArr)
}
inline const ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >&
TActPresentLoveGetInfoRsp::rewardidarr() const {
  // @@protoc_insertion_point(field_list:pb.TActPresentLoveGetInfoRsp.RewardIdArr)
  return rewardidarr_;
}
inline ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >*
TActPresentLoveGetInfoRsp::mutable_rewardidarr() {
  // @@protoc_insertion_point(field_mutable_list:pb.TActPresentLoveGetInfoRsp.RewardIdArr)
  return &rewardidarr_;
}

// -------------------------------------------------------------------

// TActPresentLovePresentLoveRsp

// optional uint32 DailyLoveNum = 1;
inline bool TActPresentLovePresentLoveRsp::has_dailylovenum() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void TActPresentLovePresentLoveRsp::set_has_dailylovenum() {
  _has_bits_[0] |= 0x00000001u;
}
inline void TActPresentLovePresentLoveRsp::clear_has_dailylovenum() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void TActPresentLovePresentLoveRsp::clear_dailylovenum() {
  dailylovenum_ = 0u;
  clear_has_dailylovenum();
}
inline ::google::protobuf::uint32 TActPresentLovePresentLoveRsp::dailylovenum() const {
  // @@protoc_insertion_point(field_get:pb.TActPresentLovePresentLoveRsp.DailyLoveNum)
  return dailylovenum_;
}
inline void TActPresentLovePresentLoveRsp::set_dailylovenum(::google::protobuf::uint32 value) {
  set_has_dailylovenum();
  dailylovenum_ = value;
  // @@protoc_insertion_point(field_set:pb.TActPresentLovePresentLoveRsp.DailyLoveNum)
}

// optional uint64 LoveCount = 2;
inline bool TActPresentLovePresentLoveRsp::has_lovecount() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void TActPresentLovePresentLoveRsp::set_has_lovecount() {
  _has_bits_[0] |= 0x00000002u;
}
inline void TActPresentLovePresentLoveRsp::clear_has_lovecount() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void TActPresentLovePresentLoveRsp::clear_lovecount() {
  lovecount_ = GOOGLE_ULONGLONG(0);
  clear_has_lovecount();
}
inline ::google::protobuf::uint64 TActPresentLovePresentLoveRsp::lovecount() const {
  // @@protoc_insertion_point(field_get:pb.TActPresentLovePresentLoveRsp.LoveCount)
  return lovecount_;
}
inline void TActPresentLovePresentLoveRsp::set_lovecount(::google::protobuf::uint64 value) {
  set_has_lovecount();
  lovecount_ = value;
  // @@protoc_insertion_point(field_set:pb.TActPresentLovePresentLoveRsp.LoveCount)
}

// repeated .pb.TCommonReward RewardArr = 3;
inline int TActPresentLovePresentLoveRsp::rewardarr_size() const {
  return rewardarr_.size();
}
inline void TActPresentLovePresentLoveRsp::clear_rewardarr() {
  rewardarr_.Clear();
}
inline const ::pb::TCommonReward& TActPresentLovePresentLoveRsp::rewardarr(int index) const {
  // @@protoc_insertion_point(field_get:pb.TActPresentLovePresentLoveRsp.RewardArr)
  return rewardarr_.Get(index);
}
inline ::pb::TCommonReward* TActPresentLovePresentLoveRsp::mutable_rewardarr(int index) {
  // @@protoc_insertion_point(field_mutable:pb.TActPresentLovePresentLoveRsp.RewardArr)
  return rewardarr_.Mutable(index);
}
inline ::pb::TCommonReward* TActPresentLovePresentLoveRsp::add_rewardarr() {
  // @@protoc_insertion_point(field_add:pb.TActPresentLovePresentLoveRsp.RewardArr)
  return rewardarr_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::pb::TCommonReward >&
TActPresentLovePresentLoveRsp::rewardarr() const {
  // @@protoc_insertion_point(field_list:pb.TActPresentLovePresentLoveRsp.RewardArr)
  return rewardarr_;
}
inline ::google::protobuf::RepeatedPtrField< ::pb::TCommonReward >*
TActPresentLovePresentLoveRsp::mutable_rewardarr() {
  // @@protoc_insertion_point(field_mutable_list:pb.TActPresentLovePresentLoveRsp.RewardArr)
  return &rewardarr_;
}

// -------------------------------------------------------------------

// TActPresentLoveGetRewardReq

// optional uint32 RewardId = 1;
inline bool TActPresentLoveGetRewardReq::has_rewardid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void TActPresentLoveGetRewardReq::set_has_rewardid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void TActPresentLoveGetRewardReq::clear_has_rewardid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void TActPresentLoveGetRewardReq::clear_rewardid() {
  rewardid_ = 0u;
  clear_has_rewardid();
}
inline ::google::protobuf::uint32 TActPresentLoveGetRewardReq::rewardid() const {
  // @@protoc_insertion_point(field_get:pb.TActPresentLoveGetRewardReq.RewardId)
  return rewardid_;
}
inline void TActPresentLoveGetRewardReq::set_rewardid(::google::protobuf::uint32 value) {
  set_has_rewardid();
  rewardid_ = value;
  // @@protoc_insertion_point(field_set:pb.TActPresentLoveGetRewardReq.RewardId)
}

// -------------------------------------------------------------------

// TActPresentLoveGetRewardRsp

// repeated .pb.TCommonReward RewardArr = 3;
inline int TActPresentLoveGetRewardRsp::rewardarr_size() const {
  return rewardarr_.size();
}
inline void TActPresentLoveGetRewardRsp::clear_rewardarr() {
  rewardarr_.Clear();
}
inline const ::pb::TCommonReward& TActPresentLoveGetRewardRsp::rewardarr(int index) const {
  // @@protoc_insertion_point(field_get:pb.TActPresentLoveGetRewardRsp.RewardArr)
  return rewardarr_.Get(index);
}
inline ::pb::TCommonReward* TActPresentLoveGetRewardRsp::mutable_rewardarr(int index) {
  // @@protoc_insertion_point(field_mutable:pb.TActPresentLoveGetRewardRsp.RewardArr)
  return rewardarr_.Mutable(index);
}
inline ::pb::TCommonReward* TActPresentLoveGetRewardRsp::add_rewardarr() {
  // @@protoc_insertion_point(field_add:pb.TActPresentLoveGetRewardRsp.RewardArr)
  return rewardarr_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::pb::TCommonReward >&
TActPresentLoveGetRewardRsp::rewardarr() const {
  // @@protoc_insertion_point(field_list:pb.TActPresentLoveGetRewardRsp.RewardArr)
  return rewardarr_;
}
inline ::google::protobuf::RepeatedPtrField< ::pb::TCommonReward >*
TActPresentLoveGetRewardRsp::mutable_rewardarr() {
  // @@protoc_insertion_point(field_mutable_list:pb.TActPresentLoveGetRewardRsp.RewardArr)
  return &rewardarr_;
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

#endif  // PROTOBUF_net_2fActPresentLove_2eproto__INCLUDED
