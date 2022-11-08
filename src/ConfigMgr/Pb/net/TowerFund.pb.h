// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: net/TowerFund.proto

#ifndef PROTOBUF_net_2fTowerFund_2eproto__INCLUDED
#define PROTOBUF_net_2fTowerFund_2eproto__INCLUDED

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
void  protobuf_AddDesc_net_2fTowerFund_2eproto();
void protobuf_AssignDesc_net_2fTowerFund_2eproto();
void protobuf_ShutdownFile_net_2fTowerFund_2eproto();

class TTowerFundGetInfoRsp;
class TTowerFundSingleInfo;
class TTowerFundReceiveRewardReq;
class TTowerFundBuyNotify;

// ===================================================================

/*FOR2LUA
<Record>
	<name>TTowerFundGetInfoRsp</name>
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
		<replaceName>net/TowerFund.proto</replaceName>
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
class TTowerFundGetInfoRsp : public ::google::protobuf::Message {
 public:
  TTowerFundGetInfoRsp();
  virtual ~TTowerFundGetInfoRsp();

  TTowerFundGetInfoRsp(const TTowerFundGetInfoRsp& from);

  inline TTowerFundGetInfoRsp& operator=(const TTowerFundGetInfoRsp& from) {
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
  static const TTowerFundGetInfoRsp& default_instance();

  void Swap(TTowerFundGetInfoRsp* other);

  // implements Message ----------------------------------------------

  TTowerFundGetInfoRsp* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const TTowerFundGetInfoRsp& from);
  void MergeFrom(const TTowerFundGetInfoRsp& from);
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

  // repeated .pb.TTowerFundSingleInfo TowerFundArr = 1;
  inline int towerfundarr_size() const;
  inline void clear_towerfundarr();
  static const int kTowerFundArrFieldNumber = 1;
  /*FOR2LUA
  <Record>
  	<name>TTowerFundGetInfoRsp</name>
  	<Function>
  		<name>towerfundarr</name>
  		<replaceName>TowerFundArr</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>mutable_towerfundarr</name>
  		<replaceName>TowerFundArr</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>add_towerfundarr</name>
  		<replaceName>TowerFundArr</replaceName>
  		<handler>descripter = pb_repeated_add_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_towerfundarr</name>
  		<replaceName>TowerFundArr</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  	<Function>
  		<name>towerfundarr_size</name>
  		<replaceName>TowerFundArr</replaceName>
  		<handler>descripter = pb_repeated_size_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline const ::pb::TTowerFundSingleInfo& towerfundarr(int index) const;
  inline ::pb::TTowerFundSingleInfo* mutable_towerfundarr(int index);
  inline ::pb::TTowerFundSingleInfo* add_towerfundarr();
  inline const ::google::protobuf::RepeatedPtrField< ::pb::TTowerFundSingleInfo >&
      towerfundarr() const;
  inline ::google::protobuf::RepeatedPtrField< ::pb::TTowerFundSingleInfo >*
      mutable_towerfundarr();

  // optional uint64 OpenTime = 2;
  inline bool has_opentime() const;
  inline void clear_opentime();
  static const int kOpenTimeFieldNumber = 2;
  /*FOR2LUA
  <Record>
  	<name>TTowerFundGetInfoRsp</name>
  	<Function>
  		<name>opentime</name>
  		<replaceName>OpenTime</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>set_opentime</name>
  		<replaceName>OpenTime</replaceName>
  		<handler>descripter = pb_set_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_opentime</name>
  		<replaceName>OpenTime</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline ::google::protobuf::uint64 opentime() const;
  inline void set_opentime(::google::protobuf::uint64 value);

  // @@protoc_insertion_point(class_scope:pb.TTowerFundGetInfoRsp)
 private:
  inline void set_has_opentime();
  inline void clear_has_opentime();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::RepeatedPtrField< ::pb::TTowerFundSingleInfo > towerfundarr_;
  ::google::protobuf::uint64 opentime_;
  friend void  protobuf_AddDesc_net_2fTowerFund_2eproto();
  friend void protobuf_AssignDesc_net_2fTowerFund_2eproto();
  friend void protobuf_ShutdownFile_net_2fTowerFund_2eproto();

  void InitAsDefaultInstance();
  static TTowerFundGetInfoRsp* default_instance_;
};
// -------------------------------------------------------------------

/*FOR2LUA
<Record>
	<name>TTowerFundSingleInfo</name>
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
		<replaceName>net/TowerFund.proto</replaceName>
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
class TTowerFundSingleInfo : public ::google::protobuf::Message {
 public:
  TTowerFundSingleInfo();
  virtual ~TTowerFundSingleInfo();

  TTowerFundSingleInfo(const TTowerFundSingleInfo& from);

  inline TTowerFundSingleInfo& operator=(const TTowerFundSingleInfo& from) {
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
  static const TTowerFundSingleInfo& default_instance();

  void Swap(TTowerFundSingleInfo* other);

  // implements Message ----------------------------------------------

  TTowerFundSingleInfo* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const TTowerFundSingleInfo& from);
  void MergeFrom(const TTowerFundSingleInfo& from);
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

  // optional uint32 TowerFundId = 1;
  inline bool has_towerfundid() const;
  inline void clear_towerfundid();
  static const int kTowerFundIdFieldNumber = 1;
  /*FOR2LUA
  <Record>
  	<name>TTowerFundSingleInfo</name>
  	<Function>
  		<name>towerfundid</name>
  		<replaceName>TowerFundId</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>set_towerfundid</name>
  		<replaceName>TowerFundId</replaceName>
  		<handler>descripter = pb_set_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_towerfundid</name>
  		<replaceName>TowerFundId</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline ::google::protobuf::uint32 towerfundid() const;
  inline void set_towerfundid(::google::protobuf::uint32 value);

  // optional uint64 BuyTime = 2;
  inline bool has_buytime() const;
  inline void clear_buytime();
  static const int kBuyTimeFieldNumber = 2;
  /*FOR2LUA
  <Record>
  	<name>TTowerFundSingleInfo</name>
  	<Function>
  		<name>buytime</name>
  		<replaceName>BuyTime</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>set_buytime</name>
  		<replaceName>BuyTime</replaceName>
  		<handler>descripter = pb_set_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_buytime</name>
  		<replaceName>BuyTime</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline ::google::protobuf::uint64 buytime() const;
  inline void set_buytime(::google::protobuf::uint64 value);

  // repeated uint32 ReceivedRewardIndex = 3;
  inline int receivedrewardindex_size() const;
  inline void clear_receivedrewardindex();
  static const int kReceivedRewardIndexFieldNumber = 3;
  /*FOR2LUA
  <Record>
  	<name>TTowerFundSingleInfo</name>
  	<Function>
  		<name>receivedrewardindex</name>
  		<replaceName>ReceivedRewardIndex</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>mutable_receivedrewardindex</name>
  		<replaceName>ReceivedRewardIndex</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>add_receivedrewardindex</name>
  		<replaceName>ReceivedRewardIndex</replaceName>
  		<handler>descripter = pb_repeated_add_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_receivedrewardindex</name>
  		<replaceName>ReceivedRewardIndex</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  	<Function>
  		<name>receivedrewardindex_size</name>
  		<replaceName>ReceivedRewardIndex</replaceName>
  		<handler>descripter = pb_repeated_size_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline ::google::protobuf::uint32 receivedrewardindex(int index) const;
  inline void set_receivedrewardindex(int index, ::google::protobuf::uint32 value);
  inline void add_receivedrewardindex(::google::protobuf::uint32 value);
  inline const ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >&
      receivedrewardindex() const;
  inline ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >*
      mutable_receivedrewardindex();

  // @@protoc_insertion_point(class_scope:pb.TTowerFundSingleInfo)
 private:
  inline void set_has_towerfundid();
  inline void clear_has_towerfundid();
  inline void set_has_buytime();
  inline void clear_has_buytime();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::uint64 buytime_;
  ::google::protobuf::RepeatedField< ::google::protobuf::uint32 > receivedrewardindex_;
  ::google::protobuf::uint32 towerfundid_;
  friend void  protobuf_AddDesc_net_2fTowerFund_2eproto();
  friend void protobuf_AssignDesc_net_2fTowerFund_2eproto();
  friend void protobuf_ShutdownFile_net_2fTowerFund_2eproto();

  void InitAsDefaultInstance();
  static TTowerFundSingleInfo* default_instance_;
};
// -------------------------------------------------------------------

/*FOR2LUA
<Record>
	<name>TTowerFundReceiveRewardReq</name>
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
		<replaceName>net/TowerFund.proto</replaceName>
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
class TTowerFundReceiveRewardReq : public ::google::protobuf::Message {
 public:
  TTowerFundReceiveRewardReq();
  virtual ~TTowerFundReceiveRewardReq();

  TTowerFundReceiveRewardReq(const TTowerFundReceiveRewardReq& from);

  inline TTowerFundReceiveRewardReq& operator=(const TTowerFundReceiveRewardReq& from) {
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
  static const TTowerFundReceiveRewardReq& default_instance();

  void Swap(TTowerFundReceiveRewardReq* other);

  // implements Message ----------------------------------------------

  TTowerFundReceiveRewardReq* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const TTowerFundReceiveRewardReq& from);
  void MergeFrom(const TTowerFundReceiveRewardReq& from);
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

  // optional uint32 TowerFundId = 1;
  inline bool has_towerfundid() const;
  inline void clear_towerfundid();
  static const int kTowerFundIdFieldNumber = 1;
  /*FOR2LUA
  <Record>
  	<name>TTowerFundReceiveRewardReq</name>
  	<Function>
  		<name>towerfundid</name>
  		<replaceName>TowerFundId</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>set_towerfundid</name>
  		<replaceName>TowerFundId</replaceName>
  		<handler>descripter = pb_set_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_towerfundid</name>
  		<replaceName>TowerFundId</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline ::google::protobuf::uint32 towerfundid() const;
  inline void set_towerfundid(::google::protobuf::uint32 value);

  // optional uint32 RewardIndex = 2;
  inline bool has_rewardindex() const;
  inline void clear_rewardindex();
  static const int kRewardIndexFieldNumber = 2;
  /*FOR2LUA
  <Record>
  	<name>TTowerFundReceiveRewardReq</name>
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

  // @@protoc_insertion_point(class_scope:pb.TTowerFundReceiveRewardReq)
 private:
  inline void set_has_towerfundid();
  inline void clear_has_towerfundid();
  inline void set_has_rewardindex();
  inline void clear_has_rewardindex();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::uint32 towerfundid_;
  ::google::protobuf::uint32 rewardindex_;
  friend void  protobuf_AddDesc_net_2fTowerFund_2eproto();
  friend void protobuf_AssignDesc_net_2fTowerFund_2eproto();
  friend void protobuf_ShutdownFile_net_2fTowerFund_2eproto();

  void InitAsDefaultInstance();
  static TTowerFundReceiveRewardReq* default_instance_;
};
// -------------------------------------------------------------------

/*FOR2LUA
<Record>
	<name>TTowerFundBuyNotify</name>
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
		<replaceName>net/TowerFund.proto</replaceName>
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
class TTowerFundBuyNotify : public ::google::protobuf::Message {
 public:
  TTowerFundBuyNotify();
  virtual ~TTowerFundBuyNotify();

  TTowerFundBuyNotify(const TTowerFundBuyNotify& from);

  inline TTowerFundBuyNotify& operator=(const TTowerFundBuyNotify& from) {
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
  static const TTowerFundBuyNotify& default_instance();

  void Swap(TTowerFundBuyNotify* other);

  // implements Message ----------------------------------------------

  TTowerFundBuyNotify* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const TTowerFundBuyNotify& from);
  void MergeFrom(const TTowerFundBuyNotify& from);
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

  // optional uint32 TowerFundId = 1;
  inline bool has_towerfundid() const;
  inline void clear_towerfundid();
  static const int kTowerFundIdFieldNumber = 1;
  /*FOR2LUA
  <Record>
  	<name>TTowerFundBuyNotify</name>
  	<Function>
  		<name>towerfundid</name>
  		<replaceName>TowerFundId</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>set_towerfundid</name>
  		<replaceName>TowerFundId</replaceName>
  		<handler>descripter = pb_set_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_towerfundid</name>
  		<replaceName>TowerFundId</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline ::google::protobuf::uint32 towerfundid() const;
  inline void set_towerfundid(::google::protobuf::uint32 value);

  // optional uint64 BuyTime = 2;
  inline bool has_buytime() const;
  inline void clear_buytime();
  static const int kBuyTimeFieldNumber = 2;
  /*FOR2LUA
  <Record>
  	<name>TTowerFundBuyNotify</name>
  	<Function>
  		<name>buytime</name>
  		<replaceName>BuyTime</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>set_buytime</name>
  		<replaceName>BuyTime</replaceName>
  		<handler>descripter = pb_set_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_buytime</name>
  		<replaceName>BuyTime</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline ::google::protobuf::uint64 buytime() const;
  inline void set_buytime(::google::protobuf::uint64 value);

  // @@protoc_insertion_point(class_scope:pb.TTowerFundBuyNotify)
 private:
  inline void set_has_towerfundid();
  inline void clear_has_towerfundid();
  inline void set_has_buytime();
  inline void clear_has_buytime();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::uint64 buytime_;
  ::google::protobuf::uint32 towerfundid_;
  friend void  protobuf_AddDesc_net_2fTowerFund_2eproto();
  friend void protobuf_AssignDesc_net_2fTowerFund_2eproto();
  friend void protobuf_ShutdownFile_net_2fTowerFund_2eproto();

  void InitAsDefaultInstance();
  static TTowerFundBuyNotify* default_instance_;
};
// ===================================================================


// ===================================================================

// TTowerFundGetInfoRsp

// repeated .pb.TTowerFundSingleInfo TowerFundArr = 1;
inline int TTowerFundGetInfoRsp::towerfundarr_size() const {
  return towerfundarr_.size();
}
inline void TTowerFundGetInfoRsp::clear_towerfundarr() {
  towerfundarr_.Clear();
}
inline const ::pb::TTowerFundSingleInfo& TTowerFundGetInfoRsp::towerfundarr(int index) const {
  // @@protoc_insertion_point(field_get:pb.TTowerFundGetInfoRsp.TowerFundArr)
  return towerfundarr_.Get(index);
}
inline ::pb::TTowerFundSingleInfo* TTowerFundGetInfoRsp::mutable_towerfundarr(int index) {
  // @@protoc_insertion_point(field_mutable:pb.TTowerFundGetInfoRsp.TowerFundArr)
  return towerfundarr_.Mutable(index);
}
inline ::pb::TTowerFundSingleInfo* TTowerFundGetInfoRsp::add_towerfundarr() {
  // @@protoc_insertion_point(field_add:pb.TTowerFundGetInfoRsp.TowerFundArr)
  return towerfundarr_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::pb::TTowerFundSingleInfo >&
TTowerFundGetInfoRsp::towerfundarr() const {
  // @@protoc_insertion_point(field_list:pb.TTowerFundGetInfoRsp.TowerFundArr)
  return towerfundarr_;
}
inline ::google::protobuf::RepeatedPtrField< ::pb::TTowerFundSingleInfo >*
TTowerFundGetInfoRsp::mutable_towerfundarr() {
  // @@protoc_insertion_point(field_mutable_list:pb.TTowerFundGetInfoRsp.TowerFundArr)
  return &towerfundarr_;
}

// optional uint64 OpenTime = 2;
inline bool TTowerFundGetInfoRsp::has_opentime() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void TTowerFundGetInfoRsp::set_has_opentime() {
  _has_bits_[0] |= 0x00000002u;
}
inline void TTowerFundGetInfoRsp::clear_has_opentime() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void TTowerFundGetInfoRsp::clear_opentime() {
  opentime_ = GOOGLE_ULONGLONG(0);
  clear_has_opentime();
}
inline ::google::protobuf::uint64 TTowerFundGetInfoRsp::opentime() const {
  // @@protoc_insertion_point(field_get:pb.TTowerFundGetInfoRsp.OpenTime)
  return opentime_;
}
inline void TTowerFundGetInfoRsp::set_opentime(::google::protobuf::uint64 value) {
  set_has_opentime();
  opentime_ = value;
  // @@protoc_insertion_point(field_set:pb.TTowerFundGetInfoRsp.OpenTime)
}

// -------------------------------------------------------------------

// TTowerFundSingleInfo

// optional uint32 TowerFundId = 1;
inline bool TTowerFundSingleInfo::has_towerfundid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void TTowerFundSingleInfo::set_has_towerfundid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void TTowerFundSingleInfo::clear_has_towerfundid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void TTowerFundSingleInfo::clear_towerfundid() {
  towerfundid_ = 0u;
  clear_has_towerfundid();
}
inline ::google::protobuf::uint32 TTowerFundSingleInfo::towerfundid() const {
  // @@protoc_insertion_point(field_get:pb.TTowerFundSingleInfo.TowerFundId)
  return towerfundid_;
}
inline void TTowerFundSingleInfo::set_towerfundid(::google::protobuf::uint32 value) {
  set_has_towerfundid();
  towerfundid_ = value;
  // @@protoc_insertion_point(field_set:pb.TTowerFundSingleInfo.TowerFundId)
}

// optional uint64 BuyTime = 2;
inline bool TTowerFundSingleInfo::has_buytime() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void TTowerFundSingleInfo::set_has_buytime() {
  _has_bits_[0] |= 0x00000002u;
}
inline void TTowerFundSingleInfo::clear_has_buytime() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void TTowerFundSingleInfo::clear_buytime() {
  buytime_ = GOOGLE_ULONGLONG(0);
  clear_has_buytime();
}
inline ::google::protobuf::uint64 TTowerFundSingleInfo::buytime() const {
  // @@protoc_insertion_point(field_get:pb.TTowerFundSingleInfo.BuyTime)
  return buytime_;
}
inline void TTowerFundSingleInfo::set_buytime(::google::protobuf::uint64 value) {
  set_has_buytime();
  buytime_ = value;
  // @@protoc_insertion_point(field_set:pb.TTowerFundSingleInfo.BuyTime)
}

// repeated uint32 ReceivedRewardIndex = 3;
inline int TTowerFundSingleInfo::receivedrewardindex_size() const {
  return receivedrewardindex_.size();
}
inline void TTowerFundSingleInfo::clear_receivedrewardindex() {
  receivedrewardindex_.Clear();
}
inline ::google::protobuf::uint32 TTowerFundSingleInfo::receivedrewardindex(int index) const {
  // @@protoc_insertion_point(field_get:pb.TTowerFundSingleInfo.ReceivedRewardIndex)
  return receivedrewardindex_.Get(index);
}
inline void TTowerFundSingleInfo::set_receivedrewardindex(int index, ::google::protobuf::uint32 value) {
  receivedrewardindex_.Set(index, value);
  // @@protoc_insertion_point(field_set:pb.TTowerFundSingleInfo.ReceivedRewardIndex)
}
inline void TTowerFundSingleInfo::add_receivedrewardindex(::google::protobuf::uint32 value) {
  receivedrewardindex_.Add(value);
  // @@protoc_insertion_point(field_add:pb.TTowerFundSingleInfo.ReceivedRewardIndex)
}
inline const ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >&
TTowerFundSingleInfo::receivedrewardindex() const {
  // @@protoc_insertion_point(field_list:pb.TTowerFundSingleInfo.ReceivedRewardIndex)
  return receivedrewardindex_;
}
inline ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >*
TTowerFundSingleInfo::mutable_receivedrewardindex() {
  // @@protoc_insertion_point(field_mutable_list:pb.TTowerFundSingleInfo.ReceivedRewardIndex)
  return &receivedrewardindex_;
}

// -------------------------------------------------------------------

// TTowerFundReceiveRewardReq

// optional uint32 TowerFundId = 1;
inline bool TTowerFundReceiveRewardReq::has_towerfundid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void TTowerFundReceiveRewardReq::set_has_towerfundid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void TTowerFundReceiveRewardReq::clear_has_towerfundid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void TTowerFundReceiveRewardReq::clear_towerfundid() {
  towerfundid_ = 0u;
  clear_has_towerfundid();
}
inline ::google::protobuf::uint32 TTowerFundReceiveRewardReq::towerfundid() const {
  // @@protoc_insertion_point(field_get:pb.TTowerFundReceiveRewardReq.TowerFundId)
  return towerfundid_;
}
inline void TTowerFundReceiveRewardReq::set_towerfundid(::google::protobuf::uint32 value) {
  set_has_towerfundid();
  towerfundid_ = value;
  // @@protoc_insertion_point(field_set:pb.TTowerFundReceiveRewardReq.TowerFundId)
}

// optional uint32 RewardIndex = 2;
inline bool TTowerFundReceiveRewardReq::has_rewardindex() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void TTowerFundReceiveRewardReq::set_has_rewardindex() {
  _has_bits_[0] |= 0x00000002u;
}
inline void TTowerFundReceiveRewardReq::clear_has_rewardindex() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void TTowerFundReceiveRewardReq::clear_rewardindex() {
  rewardindex_ = 0u;
  clear_has_rewardindex();
}
inline ::google::protobuf::uint32 TTowerFundReceiveRewardReq::rewardindex() const {
  // @@protoc_insertion_point(field_get:pb.TTowerFundReceiveRewardReq.RewardIndex)
  return rewardindex_;
}
inline void TTowerFundReceiveRewardReq::set_rewardindex(::google::protobuf::uint32 value) {
  set_has_rewardindex();
  rewardindex_ = value;
  // @@protoc_insertion_point(field_set:pb.TTowerFundReceiveRewardReq.RewardIndex)
}

// -------------------------------------------------------------------

// TTowerFundBuyNotify

// optional uint32 TowerFundId = 1;
inline bool TTowerFundBuyNotify::has_towerfundid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void TTowerFundBuyNotify::set_has_towerfundid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void TTowerFundBuyNotify::clear_has_towerfundid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void TTowerFundBuyNotify::clear_towerfundid() {
  towerfundid_ = 0u;
  clear_has_towerfundid();
}
inline ::google::protobuf::uint32 TTowerFundBuyNotify::towerfundid() const {
  // @@protoc_insertion_point(field_get:pb.TTowerFundBuyNotify.TowerFundId)
  return towerfundid_;
}
inline void TTowerFundBuyNotify::set_towerfundid(::google::protobuf::uint32 value) {
  set_has_towerfundid();
  towerfundid_ = value;
  // @@protoc_insertion_point(field_set:pb.TTowerFundBuyNotify.TowerFundId)
}

// optional uint64 BuyTime = 2;
inline bool TTowerFundBuyNotify::has_buytime() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void TTowerFundBuyNotify::set_has_buytime() {
  _has_bits_[0] |= 0x00000002u;
}
inline void TTowerFundBuyNotify::clear_has_buytime() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void TTowerFundBuyNotify::clear_buytime() {
  buytime_ = GOOGLE_ULONGLONG(0);
  clear_has_buytime();
}
inline ::google::protobuf::uint64 TTowerFundBuyNotify::buytime() const {
  // @@protoc_insertion_point(field_get:pb.TTowerFundBuyNotify.BuyTime)
  return buytime_;
}
inline void TTowerFundBuyNotify::set_buytime(::google::protobuf::uint64 value) {
  set_has_buytime();
  buytime_ = value;
  // @@protoc_insertion_point(field_set:pb.TTowerFundBuyNotify.BuyTime)
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

#endif  // PROTOBUF_net_2fTowerFund_2eproto__INCLUDED
