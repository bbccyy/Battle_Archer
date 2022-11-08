// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: net/WholeGroupWelfare.proto

#ifndef PROTOBUF_net_2fWholeGroupWelfare_2eproto__INCLUDED
#define PROTOBUF_net_2fWholeGroupWelfare_2eproto__INCLUDED

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
void  protobuf_AddDesc_net_2fWholeGroupWelfare_2eproto();
void protobuf_AssignDesc_net_2fWholeGroupWelfare_2eproto();
void protobuf_ShutdownFile_net_2fWholeGroupWelfare_2eproto();

class TWGWSingleFundInfo;
class TWholeGroupWelfareGetInfoRsp;
class TWholeGroupWelfareReceiveRewardReq;
class TUpdateFundBuyNumNotify;

// ===================================================================

/*FOR2LUA
<Record>
	<name>TWGWSingleFundInfo</name>
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
		<replaceName>net/WholeGroupWelfare.proto</replaceName>
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
class TWGWSingleFundInfo : public ::google::protobuf::Message {
 public:
  TWGWSingleFundInfo();
  virtual ~TWGWSingleFundInfo();

  TWGWSingleFundInfo(const TWGWSingleFundInfo& from);

  inline TWGWSingleFundInfo& operator=(const TWGWSingleFundInfo& from) {
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
  static const TWGWSingleFundInfo& default_instance();

  void Swap(TWGWSingleFundInfo* other);

  // implements Message ----------------------------------------------

  TWGWSingleFundInfo* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const TWGWSingleFundInfo& from);
  void MergeFrom(const TWGWSingleFundInfo& from);
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

  // optional uint32 FundId = 1;
  inline bool has_fundid() const;
  inline void clear_fundid();
  static const int kFundIdFieldNumber = 1;
  /*FOR2LUA
  <Record>
  	<name>TWGWSingleFundInfo</name>
  	<Function>
  		<name>fundid</name>
  		<replaceName>FundId</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>set_fundid</name>
  		<replaceName>FundId</replaceName>
  		<handler>descripter = pb_set_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_fundid</name>
  		<replaceName>FundId</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline ::google::protobuf::uint32 fundid() const;
  inline void set_fundid(::google::protobuf::uint32 value);

  // repeated uint32 RewardIndexArr = 2;
  inline int rewardindexarr_size() const;
  inline void clear_rewardindexarr();
  static const int kRewardIndexArrFieldNumber = 2;
  /*FOR2LUA
  <Record>
  	<name>TWGWSingleFundInfo</name>
  	<Function>
  		<name>rewardindexarr</name>
  		<replaceName>RewardIndexArr</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>mutable_rewardindexarr</name>
  		<replaceName>RewardIndexArr</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>add_rewardindexarr</name>
  		<replaceName>RewardIndexArr</replaceName>
  		<handler>descripter = pb_repeated_add_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_rewardindexarr</name>
  		<replaceName>RewardIndexArr</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  	<Function>
  		<name>rewardindexarr_size</name>
  		<replaceName>RewardIndexArr</replaceName>
  		<handler>descripter = pb_repeated_size_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline ::google::protobuf::uint32 rewardindexarr(int index) const;
  inline void set_rewardindexarr(int index, ::google::protobuf::uint32 value);
  inline void add_rewardindexarr(::google::protobuf::uint32 value);
  inline const ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >&
      rewardindexarr() const;
  inline ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >*
      mutable_rewardindexarr();

  // optional uint64 BuyNum = 3;
  inline bool has_buynum() const;
  inline void clear_buynum();
  static const int kBuyNumFieldNumber = 3;
  /*FOR2LUA
  <Record>
  	<name>TWGWSingleFundInfo</name>
  	<Function>
  		<name>buynum</name>
  		<replaceName>BuyNum</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>set_buynum</name>
  		<replaceName>BuyNum</replaceName>
  		<handler>descripter = pb_set_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_buynum</name>
  		<replaceName>BuyNum</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline ::google::protobuf::uint64 buynum() const;
  inline void set_buynum(::google::protobuf::uint64 value);

  // @@protoc_insertion_point(class_scope:pb.TWGWSingleFundInfo)
 private:
  inline void set_has_fundid();
  inline void clear_has_fundid();
  inline void set_has_buynum();
  inline void clear_has_buynum();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::RepeatedField< ::google::protobuf::uint32 > rewardindexarr_;
  ::google::protobuf::uint64 buynum_;
  ::google::protobuf::uint32 fundid_;
  friend void  protobuf_AddDesc_net_2fWholeGroupWelfare_2eproto();
  friend void protobuf_AssignDesc_net_2fWholeGroupWelfare_2eproto();
  friend void protobuf_ShutdownFile_net_2fWholeGroupWelfare_2eproto();

  void InitAsDefaultInstance();
  static TWGWSingleFundInfo* default_instance_;
};
// -------------------------------------------------------------------

/*FOR2LUA
<Record>
	<name>TWholeGroupWelfareGetInfoRsp</name>
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
		<replaceName>net/WholeGroupWelfare.proto</replaceName>
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
class TWholeGroupWelfareGetInfoRsp : public ::google::protobuf::Message {
 public:
  TWholeGroupWelfareGetInfoRsp();
  virtual ~TWholeGroupWelfareGetInfoRsp();

  TWholeGroupWelfareGetInfoRsp(const TWholeGroupWelfareGetInfoRsp& from);

  inline TWholeGroupWelfareGetInfoRsp& operator=(const TWholeGroupWelfareGetInfoRsp& from) {
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
  static const TWholeGroupWelfareGetInfoRsp& default_instance();

  void Swap(TWholeGroupWelfareGetInfoRsp* other);

  // implements Message ----------------------------------------------

  TWholeGroupWelfareGetInfoRsp* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const TWholeGroupWelfareGetInfoRsp& from);
  void MergeFrom(const TWholeGroupWelfareGetInfoRsp& from);
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

  // repeated .pb.TWGWSingleFundInfo FundArr = 1;
  inline int fundarr_size() const;
  inline void clear_fundarr();
  static const int kFundArrFieldNumber = 1;
  /*FOR2LUA
  <Record>
  	<name>TWholeGroupWelfareGetInfoRsp</name>
  	<Function>
  		<name>fundarr</name>
  		<replaceName>FundArr</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>mutable_fundarr</name>
  		<replaceName>FundArr</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>add_fundarr</name>
  		<replaceName>FundArr</replaceName>
  		<handler>descripter = pb_repeated_add_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_fundarr</name>
  		<replaceName>FundArr</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  	<Function>
  		<name>fundarr_size</name>
  		<replaceName>FundArr</replaceName>
  		<handler>descripter = pb_repeated_size_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline const ::pb::TWGWSingleFundInfo& fundarr(int index) const;
  inline ::pb::TWGWSingleFundInfo* mutable_fundarr(int index);
  inline ::pb::TWGWSingleFundInfo* add_fundarr();
  inline const ::google::protobuf::RepeatedPtrField< ::pb::TWGWSingleFundInfo >&
      fundarr() const;
  inline ::google::protobuf::RepeatedPtrField< ::pb::TWGWSingleFundInfo >*
      mutable_fundarr();

  // @@protoc_insertion_point(class_scope:pb.TWholeGroupWelfareGetInfoRsp)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::RepeatedPtrField< ::pb::TWGWSingleFundInfo > fundarr_;
  friend void  protobuf_AddDesc_net_2fWholeGroupWelfare_2eproto();
  friend void protobuf_AssignDesc_net_2fWholeGroupWelfare_2eproto();
  friend void protobuf_ShutdownFile_net_2fWholeGroupWelfare_2eproto();

  void InitAsDefaultInstance();
  static TWholeGroupWelfareGetInfoRsp* default_instance_;
};
// -------------------------------------------------------------------

/*FOR2LUA
<Record>
	<name>TWholeGroupWelfareReceiveRewardReq</name>
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
		<replaceName>net/WholeGroupWelfare.proto</replaceName>
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
class TWholeGroupWelfareReceiveRewardReq : public ::google::protobuf::Message {
 public:
  TWholeGroupWelfareReceiveRewardReq();
  virtual ~TWholeGroupWelfareReceiveRewardReq();

  TWholeGroupWelfareReceiveRewardReq(const TWholeGroupWelfareReceiveRewardReq& from);

  inline TWholeGroupWelfareReceiveRewardReq& operator=(const TWholeGroupWelfareReceiveRewardReq& from) {
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
  static const TWholeGroupWelfareReceiveRewardReq& default_instance();

  void Swap(TWholeGroupWelfareReceiveRewardReq* other);

  // implements Message ----------------------------------------------

  TWholeGroupWelfareReceiveRewardReq* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const TWholeGroupWelfareReceiveRewardReq& from);
  void MergeFrom(const TWholeGroupWelfareReceiveRewardReq& from);
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

  // optional uint32 FundId = 1;
  inline bool has_fundid() const;
  inline void clear_fundid();
  static const int kFundIdFieldNumber = 1;
  /*FOR2LUA
  <Record>
  	<name>TWholeGroupWelfareReceiveRewardReq</name>
  	<Function>
  		<name>fundid</name>
  		<replaceName>FundId</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>set_fundid</name>
  		<replaceName>FundId</replaceName>
  		<handler>descripter = pb_set_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_fundid</name>
  		<replaceName>FundId</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline ::google::protobuf::uint32 fundid() const;
  inline void set_fundid(::google::protobuf::uint32 value);

  // optional uint32 RewardIndex = 2;
  inline bool has_rewardindex() const;
  inline void clear_rewardindex();
  static const int kRewardIndexFieldNumber = 2;
  /*FOR2LUA
  <Record>
  	<name>TWholeGroupWelfareReceiveRewardReq</name>
  	<Function>
  		<name>rewardindex</name>
  		<replaceName>RewardIndex</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>set_rewardindex</name>
  		<replaceName>RewardIndex</replaceName>
  		<handler>descripter = pb_set_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_rewardindex</name>
  		<replaceName>RewardIndex</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline ::google::protobuf::uint32 rewardindex() const;
  inline void set_rewardindex(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:pb.TWholeGroupWelfareReceiveRewardReq)
 private:
  inline void set_has_fundid();
  inline void clear_has_fundid();
  inline void set_has_rewardindex();
  inline void clear_has_rewardindex();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::uint32 fundid_;
  ::google::protobuf::uint32 rewardindex_;
  friend void  protobuf_AddDesc_net_2fWholeGroupWelfare_2eproto();
  friend void protobuf_AssignDesc_net_2fWholeGroupWelfare_2eproto();
  friend void protobuf_ShutdownFile_net_2fWholeGroupWelfare_2eproto();

  void InitAsDefaultInstance();
  static TWholeGroupWelfareReceiveRewardReq* default_instance_;
};
// -------------------------------------------------------------------

/*FOR2LUA
<Record>
	<name>TUpdateFundBuyNumNotify</name>
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
		<replaceName>net/WholeGroupWelfare.proto</replaceName>
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
class TUpdateFundBuyNumNotify : public ::google::protobuf::Message {
 public:
  TUpdateFundBuyNumNotify();
  virtual ~TUpdateFundBuyNumNotify();

  TUpdateFundBuyNumNotify(const TUpdateFundBuyNumNotify& from);

  inline TUpdateFundBuyNumNotify& operator=(const TUpdateFundBuyNumNotify& from) {
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
  static const TUpdateFundBuyNumNotify& default_instance();

  void Swap(TUpdateFundBuyNumNotify* other);

  // implements Message ----------------------------------------------

  TUpdateFundBuyNumNotify* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const TUpdateFundBuyNumNotify& from);
  void MergeFrom(const TUpdateFundBuyNumNotify& from);
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

  // optional uint32 FundId = 1;
  inline bool has_fundid() const;
  inline void clear_fundid();
  static const int kFundIdFieldNumber = 1;
  /*FOR2LUA
  <Record>
  	<name>TUpdateFundBuyNumNotify</name>
  	<Function>
  		<name>fundid</name>
  		<replaceName>FundId</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>set_fundid</name>
  		<replaceName>FundId</replaceName>
  		<handler>descripter = pb_set_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_fundid</name>
  		<replaceName>FundId</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline ::google::protobuf::uint32 fundid() const;
  inline void set_fundid(::google::protobuf::uint32 value);

  // optional uint64 BuyNum = 2;
  inline bool has_buynum() const;
  inline void clear_buynum();
  static const int kBuyNumFieldNumber = 2;
  /*FOR2LUA
  <Record>
  	<name>TUpdateFundBuyNumNotify</name>
  	<Function>
  		<name>buynum</name>
  		<replaceName>BuyNum</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>set_buynum</name>
  		<replaceName>BuyNum</replaceName>
  		<handler>descripter = pb_set_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_buynum</name>
  		<replaceName>BuyNum</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline ::google::protobuf::uint64 buynum() const;
  inline void set_buynum(::google::protobuf::uint64 value);

  // @@protoc_insertion_point(class_scope:pb.TUpdateFundBuyNumNotify)
 private:
  inline void set_has_fundid();
  inline void clear_has_fundid();
  inline void set_has_buynum();
  inline void clear_has_buynum();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::uint64 buynum_;
  ::google::protobuf::uint32 fundid_;
  friend void  protobuf_AddDesc_net_2fWholeGroupWelfare_2eproto();
  friend void protobuf_AssignDesc_net_2fWholeGroupWelfare_2eproto();
  friend void protobuf_ShutdownFile_net_2fWholeGroupWelfare_2eproto();

  void InitAsDefaultInstance();
  static TUpdateFundBuyNumNotify* default_instance_;
};
// ===================================================================


// ===================================================================

// TWGWSingleFundInfo

// optional uint32 FundId = 1;
inline bool TWGWSingleFundInfo::has_fundid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void TWGWSingleFundInfo::set_has_fundid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void TWGWSingleFundInfo::clear_has_fundid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void TWGWSingleFundInfo::clear_fundid() {
  fundid_ = 0u;
  clear_has_fundid();
}
inline ::google::protobuf::uint32 TWGWSingleFundInfo::fundid() const {
  // @@protoc_insertion_point(field_get:pb.TWGWSingleFundInfo.FundId)
  return fundid_;
}
inline void TWGWSingleFundInfo::set_fundid(::google::protobuf::uint32 value) {
  set_has_fundid();
  fundid_ = value;
  // @@protoc_insertion_point(field_set:pb.TWGWSingleFundInfo.FundId)
}

// repeated uint32 RewardIndexArr = 2;
inline int TWGWSingleFundInfo::rewardindexarr_size() const {
  return rewardindexarr_.size();
}
inline void TWGWSingleFundInfo::clear_rewardindexarr() {
  rewardindexarr_.Clear();
}
inline ::google::protobuf::uint32 TWGWSingleFundInfo::rewardindexarr(int index) const {
  // @@protoc_insertion_point(field_get:pb.TWGWSingleFundInfo.RewardIndexArr)
  return rewardindexarr_.Get(index);
}
inline void TWGWSingleFundInfo::set_rewardindexarr(int index, ::google::protobuf::uint32 value) {
  rewardindexarr_.Set(index, value);
  // @@protoc_insertion_point(field_set:pb.TWGWSingleFundInfo.RewardIndexArr)
}
inline void TWGWSingleFundInfo::add_rewardindexarr(::google::protobuf::uint32 value) {
  rewardindexarr_.Add(value);
  // @@protoc_insertion_point(field_add:pb.TWGWSingleFundInfo.RewardIndexArr)
}
inline const ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >&
TWGWSingleFundInfo::rewardindexarr() const {
  // @@protoc_insertion_point(field_list:pb.TWGWSingleFundInfo.RewardIndexArr)
  return rewardindexarr_;
}
inline ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >*
TWGWSingleFundInfo::mutable_rewardindexarr() {
  // @@protoc_insertion_point(field_mutable_list:pb.TWGWSingleFundInfo.RewardIndexArr)
  return &rewardindexarr_;
}

// optional uint64 BuyNum = 3;
inline bool TWGWSingleFundInfo::has_buynum() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void TWGWSingleFundInfo::set_has_buynum() {
  _has_bits_[0] |= 0x00000004u;
}
inline void TWGWSingleFundInfo::clear_has_buynum() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void TWGWSingleFundInfo::clear_buynum() {
  buynum_ = GOOGLE_ULONGLONG(0);
  clear_has_buynum();
}
inline ::google::protobuf::uint64 TWGWSingleFundInfo::buynum() const {
  // @@protoc_insertion_point(field_get:pb.TWGWSingleFundInfo.BuyNum)
  return buynum_;
}
inline void TWGWSingleFundInfo::set_buynum(::google::protobuf::uint64 value) {
  set_has_buynum();
  buynum_ = value;
  // @@protoc_insertion_point(field_set:pb.TWGWSingleFundInfo.BuyNum)
}

// -------------------------------------------------------------------

// TWholeGroupWelfareGetInfoRsp

// repeated .pb.TWGWSingleFundInfo FundArr = 1;
inline int TWholeGroupWelfareGetInfoRsp::fundarr_size() const {
  return fundarr_.size();
}
inline void TWholeGroupWelfareGetInfoRsp::clear_fundarr() {
  fundarr_.Clear();
}
inline const ::pb::TWGWSingleFundInfo& TWholeGroupWelfareGetInfoRsp::fundarr(int index) const {
  // @@protoc_insertion_point(field_get:pb.TWholeGroupWelfareGetInfoRsp.FundArr)
  return fundarr_.Get(index);
}
inline ::pb::TWGWSingleFundInfo* TWholeGroupWelfareGetInfoRsp::mutable_fundarr(int index) {
  // @@protoc_insertion_point(field_mutable:pb.TWholeGroupWelfareGetInfoRsp.FundArr)
  return fundarr_.Mutable(index);
}
inline ::pb::TWGWSingleFundInfo* TWholeGroupWelfareGetInfoRsp::add_fundarr() {
  // @@protoc_insertion_point(field_add:pb.TWholeGroupWelfareGetInfoRsp.FundArr)
  return fundarr_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::pb::TWGWSingleFundInfo >&
TWholeGroupWelfareGetInfoRsp::fundarr() const {
  // @@protoc_insertion_point(field_list:pb.TWholeGroupWelfareGetInfoRsp.FundArr)
  return fundarr_;
}
inline ::google::protobuf::RepeatedPtrField< ::pb::TWGWSingleFundInfo >*
TWholeGroupWelfareGetInfoRsp::mutable_fundarr() {
  // @@protoc_insertion_point(field_mutable_list:pb.TWholeGroupWelfareGetInfoRsp.FundArr)
  return &fundarr_;
}

// -------------------------------------------------------------------

// TWholeGroupWelfareReceiveRewardReq

// optional uint32 FundId = 1;
inline bool TWholeGroupWelfareReceiveRewardReq::has_fundid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void TWholeGroupWelfareReceiveRewardReq::set_has_fundid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void TWholeGroupWelfareReceiveRewardReq::clear_has_fundid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void TWholeGroupWelfareReceiveRewardReq::clear_fundid() {
  fundid_ = 0u;
  clear_has_fundid();
}
inline ::google::protobuf::uint32 TWholeGroupWelfareReceiveRewardReq::fundid() const {
  // @@protoc_insertion_point(field_get:pb.TWholeGroupWelfareReceiveRewardReq.FundId)
  return fundid_;
}
inline void TWholeGroupWelfareReceiveRewardReq::set_fundid(::google::protobuf::uint32 value) {
  set_has_fundid();
  fundid_ = value;
  // @@protoc_insertion_point(field_set:pb.TWholeGroupWelfareReceiveRewardReq.FundId)
}

// optional uint32 RewardIndex = 2;
inline bool TWholeGroupWelfareReceiveRewardReq::has_rewardindex() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void TWholeGroupWelfareReceiveRewardReq::set_has_rewardindex() {
  _has_bits_[0] |= 0x00000002u;
}
inline void TWholeGroupWelfareReceiveRewardReq::clear_has_rewardindex() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void TWholeGroupWelfareReceiveRewardReq::clear_rewardindex() {
  rewardindex_ = 0u;
  clear_has_rewardindex();
}
inline ::google::protobuf::uint32 TWholeGroupWelfareReceiveRewardReq::rewardindex() const {
  // @@protoc_insertion_point(field_get:pb.TWholeGroupWelfareReceiveRewardReq.RewardIndex)
  return rewardindex_;
}
inline void TWholeGroupWelfareReceiveRewardReq::set_rewardindex(::google::protobuf::uint32 value) {
  set_has_rewardindex();
  rewardindex_ = value;
  // @@protoc_insertion_point(field_set:pb.TWholeGroupWelfareReceiveRewardReq.RewardIndex)
}

// -------------------------------------------------------------------

// TUpdateFundBuyNumNotify

// optional uint32 FundId = 1;
inline bool TUpdateFundBuyNumNotify::has_fundid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void TUpdateFundBuyNumNotify::set_has_fundid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void TUpdateFundBuyNumNotify::clear_has_fundid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void TUpdateFundBuyNumNotify::clear_fundid() {
  fundid_ = 0u;
  clear_has_fundid();
}
inline ::google::protobuf::uint32 TUpdateFundBuyNumNotify::fundid() const {
  // @@protoc_insertion_point(field_get:pb.TUpdateFundBuyNumNotify.FundId)
  return fundid_;
}
inline void TUpdateFundBuyNumNotify::set_fundid(::google::protobuf::uint32 value) {
  set_has_fundid();
  fundid_ = value;
  // @@protoc_insertion_point(field_set:pb.TUpdateFundBuyNumNotify.FundId)
}

// optional uint64 BuyNum = 2;
inline bool TUpdateFundBuyNumNotify::has_buynum() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void TUpdateFundBuyNumNotify::set_has_buynum() {
  _has_bits_[0] |= 0x00000002u;
}
inline void TUpdateFundBuyNumNotify::clear_has_buynum() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void TUpdateFundBuyNumNotify::clear_buynum() {
  buynum_ = GOOGLE_ULONGLONG(0);
  clear_has_buynum();
}
inline ::google::protobuf::uint64 TUpdateFundBuyNumNotify::buynum() const {
  // @@protoc_insertion_point(field_get:pb.TUpdateFundBuyNumNotify.BuyNum)
  return buynum_;
}
inline void TUpdateFundBuyNumNotify::set_buynum(::google::protobuf::uint64 value) {
  set_has_buynum();
  buynum_ = value;
  // @@protoc_insertion_point(field_set:pb.TUpdateFundBuyNumNotify.BuyNum)
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

#endif  // PROTOBUF_net_2fWholeGroupWelfare_2eproto__INCLUDED
