// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: net/ActTimeLimitedMerchant.proto

#ifndef PROTOBUF_net_2fActTimeLimitedMerchant_2eproto__INCLUDED
#define PROTOBUF_net_2fActTimeLimitedMerchant_2eproto__INCLUDED

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
void  protobuf_AddDesc_net_2fActTimeLimitedMerchant_2eproto();
void protobuf_AssignDesc_net_2fActTimeLimitedMerchant_2eproto();
void protobuf_ShutdownFile_net_2fActTimeLimitedMerchant_2eproto();

class TActTimeLimitedMerchantInfo;
class TActTimeLimitedMerchantGetInfoRsp;
class TActTimeLimitedMerchantNotify;

// ===================================================================

/*FOR2LUA
<Record>
	<name>TActTimeLimitedMerchantInfo</name>
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
		<replaceName>net/ActTimeLimitedMerchant.proto</replaceName>
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
class TActTimeLimitedMerchantInfo : public ::google::protobuf::Message {
 public:
  TActTimeLimitedMerchantInfo();
  virtual ~TActTimeLimitedMerchantInfo();

  TActTimeLimitedMerchantInfo(const TActTimeLimitedMerchantInfo& from);

  inline TActTimeLimitedMerchantInfo& operator=(const TActTimeLimitedMerchantInfo& from) {
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
  static const TActTimeLimitedMerchantInfo& default_instance();

  void Swap(TActTimeLimitedMerchantInfo* other);

  // implements Message ----------------------------------------------

  TActTimeLimitedMerchantInfo* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const TActTimeLimitedMerchantInfo& from);
  void MergeFrom(const TActTimeLimitedMerchantInfo& from);
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

  // optional uint32 Id = 1;
  inline bool has_id() const;
  inline void clear_id();
  static const int kIdFieldNumber = 1;
  /*FOR2LUA
  <Record>
  	<name>TActTimeLimitedMerchantInfo</name>
  	<Function>
  		<name>id</name>
  		<replaceName>Id</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>set_id</name>
  		<replaceName>Id</replaceName>
  		<handler>descripter = pb_set_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_id</name>
  		<replaceName>Id</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline ::google::protobuf::uint32 id() const;
  inline void set_id(::google::protobuf::uint32 value);

  // optional uint32 BuyNum = 2;
  inline bool has_buynum() const;
  inline void clear_buynum();
  static const int kBuyNumFieldNumber = 2;
  /*FOR2LUA
  <Record>
  	<name>TActTimeLimitedMerchantInfo</name>
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
  inline ::google::protobuf::uint32 buynum() const;
  inline void set_buynum(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:pb.TActTimeLimitedMerchantInfo)
 private:
  inline void set_has_id();
  inline void clear_has_id();
  inline void set_has_buynum();
  inline void clear_has_buynum();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::uint32 id_;
  ::google::protobuf::uint32 buynum_;
  friend void  protobuf_AddDesc_net_2fActTimeLimitedMerchant_2eproto();
  friend void protobuf_AssignDesc_net_2fActTimeLimitedMerchant_2eproto();
  friend void protobuf_ShutdownFile_net_2fActTimeLimitedMerchant_2eproto();

  void InitAsDefaultInstance();
  static TActTimeLimitedMerchantInfo* default_instance_;
};
// -------------------------------------------------------------------

/*FOR2LUA
<Record>
	<name>TActTimeLimitedMerchantGetInfoRsp</name>
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
		<replaceName>net/ActTimeLimitedMerchant.proto</replaceName>
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
class TActTimeLimitedMerchantGetInfoRsp : public ::google::protobuf::Message {
 public:
  TActTimeLimitedMerchantGetInfoRsp();
  virtual ~TActTimeLimitedMerchantGetInfoRsp();

  TActTimeLimitedMerchantGetInfoRsp(const TActTimeLimitedMerchantGetInfoRsp& from);

  inline TActTimeLimitedMerchantGetInfoRsp& operator=(const TActTimeLimitedMerchantGetInfoRsp& from) {
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
  static const TActTimeLimitedMerchantGetInfoRsp& default_instance();

  void Swap(TActTimeLimitedMerchantGetInfoRsp* other);

  // implements Message ----------------------------------------------

  TActTimeLimitedMerchantGetInfoRsp* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const TActTimeLimitedMerchantGetInfoRsp& from);
  void MergeFrom(const TActTimeLimitedMerchantGetInfoRsp& from);
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

  // repeated .pb.TActTimeLimitedMerchantInfo ArrInfo = 1;
  inline int arrinfo_size() const;
  inline void clear_arrinfo();
  static const int kArrInfoFieldNumber = 1;
  /*FOR2LUA
  <Record>
  	<name>TActTimeLimitedMerchantGetInfoRsp</name>
  	<Function>
  		<name>arrinfo</name>
  		<replaceName>ArrInfo</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>mutable_arrinfo</name>
  		<replaceName>ArrInfo</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>add_arrinfo</name>
  		<replaceName>ArrInfo</replaceName>
  		<handler>descripter = pb_repeated_add_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_arrinfo</name>
  		<replaceName>ArrInfo</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  	<Function>
  		<name>arrinfo_size</name>
  		<replaceName>ArrInfo</replaceName>
  		<handler>descripter = pb_repeated_size_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline const ::pb::TActTimeLimitedMerchantInfo& arrinfo(int index) const;
  inline ::pb::TActTimeLimitedMerchantInfo* mutable_arrinfo(int index);
  inline ::pb::TActTimeLimitedMerchantInfo* add_arrinfo();
  inline const ::google::protobuf::RepeatedPtrField< ::pb::TActTimeLimitedMerchantInfo >&
      arrinfo() const;
  inline ::google::protobuf::RepeatedPtrField< ::pb::TActTimeLimitedMerchantInfo >*
      mutable_arrinfo();

  // @@protoc_insertion_point(class_scope:pb.TActTimeLimitedMerchantGetInfoRsp)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::RepeatedPtrField< ::pb::TActTimeLimitedMerchantInfo > arrinfo_;
  friend void  protobuf_AddDesc_net_2fActTimeLimitedMerchant_2eproto();
  friend void protobuf_AssignDesc_net_2fActTimeLimitedMerchant_2eproto();
  friend void protobuf_ShutdownFile_net_2fActTimeLimitedMerchant_2eproto();

  void InitAsDefaultInstance();
  static TActTimeLimitedMerchantGetInfoRsp* default_instance_;
};
// -------------------------------------------------------------------

/*FOR2LUA
<Record>
	<name>TActTimeLimitedMerchantNotify</name>
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
		<replaceName>net/ActTimeLimitedMerchant.proto</replaceName>
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
class TActTimeLimitedMerchantNotify : public ::google::protobuf::Message {
 public:
  TActTimeLimitedMerchantNotify();
  virtual ~TActTimeLimitedMerchantNotify();

  TActTimeLimitedMerchantNotify(const TActTimeLimitedMerchantNotify& from);

  inline TActTimeLimitedMerchantNotify& operator=(const TActTimeLimitedMerchantNotify& from) {
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
  static const TActTimeLimitedMerchantNotify& default_instance();

  void Swap(TActTimeLimitedMerchantNotify* other);

  // implements Message ----------------------------------------------

  TActTimeLimitedMerchantNotify* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const TActTimeLimitedMerchantNotify& from);
  void MergeFrom(const TActTimeLimitedMerchantNotify& from);
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

  // repeated .pb.TActTimeLimitedMerchantInfo ArrInfo = 1;
  inline int arrinfo_size() const;
  inline void clear_arrinfo();
  static const int kArrInfoFieldNumber = 1;
  /*FOR2LUA
  <Record>
  	<name>TActTimeLimitedMerchantNotify</name>
  	<Function>
  		<name>arrinfo</name>
  		<replaceName>ArrInfo</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>mutable_arrinfo</name>
  		<replaceName>ArrInfo</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>add_arrinfo</name>
  		<replaceName>ArrInfo</replaceName>
  		<handler>descripter = pb_repeated_add_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_arrinfo</name>
  		<replaceName>ArrInfo</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  	<Function>
  		<name>arrinfo_size</name>
  		<replaceName>ArrInfo</replaceName>
  		<handler>descripter = pb_repeated_size_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline const ::pb::TActTimeLimitedMerchantInfo& arrinfo(int index) const;
  inline ::pb::TActTimeLimitedMerchantInfo* mutable_arrinfo(int index);
  inline ::pb::TActTimeLimitedMerchantInfo* add_arrinfo();
  inline const ::google::protobuf::RepeatedPtrField< ::pb::TActTimeLimitedMerchantInfo >&
      arrinfo() const;
  inline ::google::protobuf::RepeatedPtrField< ::pb::TActTimeLimitedMerchantInfo >*
      mutable_arrinfo();

  // @@protoc_insertion_point(class_scope:pb.TActTimeLimitedMerchantNotify)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::RepeatedPtrField< ::pb::TActTimeLimitedMerchantInfo > arrinfo_;
  friend void  protobuf_AddDesc_net_2fActTimeLimitedMerchant_2eproto();
  friend void protobuf_AssignDesc_net_2fActTimeLimitedMerchant_2eproto();
  friend void protobuf_ShutdownFile_net_2fActTimeLimitedMerchant_2eproto();

  void InitAsDefaultInstance();
  static TActTimeLimitedMerchantNotify* default_instance_;
};
// ===================================================================


// ===================================================================

// TActTimeLimitedMerchantInfo

// optional uint32 Id = 1;
inline bool TActTimeLimitedMerchantInfo::has_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void TActTimeLimitedMerchantInfo::set_has_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void TActTimeLimitedMerchantInfo::clear_has_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void TActTimeLimitedMerchantInfo::clear_id() {
  id_ = 0u;
  clear_has_id();
}
inline ::google::protobuf::uint32 TActTimeLimitedMerchantInfo::id() const {
  // @@protoc_insertion_point(field_get:pb.TActTimeLimitedMerchantInfo.Id)
  return id_;
}
inline void TActTimeLimitedMerchantInfo::set_id(::google::protobuf::uint32 value) {
  set_has_id();
  id_ = value;
  // @@protoc_insertion_point(field_set:pb.TActTimeLimitedMerchantInfo.Id)
}

// optional uint32 BuyNum = 2;
inline bool TActTimeLimitedMerchantInfo::has_buynum() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void TActTimeLimitedMerchantInfo::set_has_buynum() {
  _has_bits_[0] |= 0x00000002u;
}
inline void TActTimeLimitedMerchantInfo::clear_has_buynum() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void TActTimeLimitedMerchantInfo::clear_buynum() {
  buynum_ = 0u;
  clear_has_buynum();
}
inline ::google::protobuf::uint32 TActTimeLimitedMerchantInfo::buynum() const {
  // @@protoc_insertion_point(field_get:pb.TActTimeLimitedMerchantInfo.BuyNum)
  return buynum_;
}
inline void TActTimeLimitedMerchantInfo::set_buynum(::google::protobuf::uint32 value) {
  set_has_buynum();
  buynum_ = value;
  // @@protoc_insertion_point(field_set:pb.TActTimeLimitedMerchantInfo.BuyNum)
}

// -------------------------------------------------------------------

// TActTimeLimitedMerchantGetInfoRsp

// repeated .pb.TActTimeLimitedMerchantInfo ArrInfo = 1;
inline int TActTimeLimitedMerchantGetInfoRsp::arrinfo_size() const {
  return arrinfo_.size();
}
inline void TActTimeLimitedMerchantGetInfoRsp::clear_arrinfo() {
  arrinfo_.Clear();
}
inline const ::pb::TActTimeLimitedMerchantInfo& TActTimeLimitedMerchantGetInfoRsp::arrinfo(int index) const {
  // @@protoc_insertion_point(field_get:pb.TActTimeLimitedMerchantGetInfoRsp.ArrInfo)
  return arrinfo_.Get(index);
}
inline ::pb::TActTimeLimitedMerchantInfo* TActTimeLimitedMerchantGetInfoRsp::mutable_arrinfo(int index) {
  // @@protoc_insertion_point(field_mutable:pb.TActTimeLimitedMerchantGetInfoRsp.ArrInfo)
  return arrinfo_.Mutable(index);
}
inline ::pb::TActTimeLimitedMerchantInfo* TActTimeLimitedMerchantGetInfoRsp::add_arrinfo() {
  // @@protoc_insertion_point(field_add:pb.TActTimeLimitedMerchantGetInfoRsp.ArrInfo)
  return arrinfo_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::pb::TActTimeLimitedMerchantInfo >&
TActTimeLimitedMerchantGetInfoRsp::arrinfo() const {
  // @@protoc_insertion_point(field_list:pb.TActTimeLimitedMerchantGetInfoRsp.ArrInfo)
  return arrinfo_;
}
inline ::google::protobuf::RepeatedPtrField< ::pb::TActTimeLimitedMerchantInfo >*
TActTimeLimitedMerchantGetInfoRsp::mutable_arrinfo() {
  // @@protoc_insertion_point(field_mutable_list:pb.TActTimeLimitedMerchantGetInfoRsp.ArrInfo)
  return &arrinfo_;
}

// -------------------------------------------------------------------

// TActTimeLimitedMerchantNotify

// repeated .pb.TActTimeLimitedMerchantInfo ArrInfo = 1;
inline int TActTimeLimitedMerchantNotify::arrinfo_size() const {
  return arrinfo_.size();
}
inline void TActTimeLimitedMerchantNotify::clear_arrinfo() {
  arrinfo_.Clear();
}
inline const ::pb::TActTimeLimitedMerchantInfo& TActTimeLimitedMerchantNotify::arrinfo(int index) const {
  // @@protoc_insertion_point(field_get:pb.TActTimeLimitedMerchantNotify.ArrInfo)
  return arrinfo_.Get(index);
}
inline ::pb::TActTimeLimitedMerchantInfo* TActTimeLimitedMerchantNotify::mutable_arrinfo(int index) {
  // @@protoc_insertion_point(field_mutable:pb.TActTimeLimitedMerchantNotify.ArrInfo)
  return arrinfo_.Mutable(index);
}
inline ::pb::TActTimeLimitedMerchantInfo* TActTimeLimitedMerchantNotify::add_arrinfo() {
  // @@protoc_insertion_point(field_add:pb.TActTimeLimitedMerchantNotify.ArrInfo)
  return arrinfo_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::pb::TActTimeLimitedMerchantInfo >&
TActTimeLimitedMerchantNotify::arrinfo() const {
  // @@protoc_insertion_point(field_list:pb.TActTimeLimitedMerchantNotify.ArrInfo)
  return arrinfo_;
}
inline ::google::protobuf::RepeatedPtrField< ::pb::TActTimeLimitedMerchantInfo >*
TActTimeLimitedMerchantNotify::mutable_arrinfo() {
  // @@protoc_insertion_point(field_mutable_list:pb.TActTimeLimitedMerchantNotify.ArrInfo)
  return &arrinfo_;
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

#endif  // PROTOBUF_net_2fActTimeLimitedMerchant_2eproto__INCLUDED
