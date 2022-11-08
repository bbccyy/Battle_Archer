// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: net/FamousBook.proto

#ifndef PROTOBUF_net_2fFamousBook_2eproto__INCLUDED
#define PROTOBUF_net_2fFamousBook_2eproto__INCLUDED

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
void  protobuf_AddDesc_net_2fFamousBook_2eproto();
void protobuf_AssignDesc_net_2fFamousBook_2eproto();
void protobuf_ShutdownFile_net_2fFamousBook_2eproto();

class TFamousBookGetFamousBookSlotNode;
class TFamousBookGetFamousBookSingleInfo;
class TFamousBookGetFamousBookInfoRsp;
class TFamousBookLightUpOrExtinguishedSlotNodeReq;

enum EItemType {
  FASHION = 1,
  MOUNT = 2,
  TITLE = 3
};
bool EItemType_IsValid(int value);
const EItemType EItemType_MIN = FASHION;
const EItemType EItemType_MAX = TITLE;
const int EItemType_ARRAYSIZE = EItemType_MAX + 1;

const ::google::protobuf::EnumDescriptor* EItemType_descriptor();
inline const ::std::string& EItemType_Name(EItemType value) {
  return ::google::protobuf::internal::NameOfEnum(
    EItemType_descriptor(), value);
}
inline bool EItemType_Parse(
    const ::std::string& name, EItemType* value) {
  return ::google::protobuf::internal::ParseNamedEnum<EItemType>(
    EItemType_descriptor(), name, value);
}
// ===================================================================

/*FOR2LUA
<Record>
	<name>TFamousBookGetFamousBookSlotNode</name>
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
		<replaceName>net/FamousBook.proto</replaceName>
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
class TFamousBookGetFamousBookSlotNode : public ::google::protobuf::Message {
 public:
  TFamousBookGetFamousBookSlotNode();
  virtual ~TFamousBookGetFamousBookSlotNode();

  TFamousBookGetFamousBookSlotNode(const TFamousBookGetFamousBookSlotNode& from);

  inline TFamousBookGetFamousBookSlotNode& operator=(const TFamousBookGetFamousBookSlotNode& from) {
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
  static const TFamousBookGetFamousBookSlotNode& default_instance();

  void Swap(TFamousBookGetFamousBookSlotNode* other);

  // implements Message ----------------------------------------------

  TFamousBookGetFamousBookSlotNode* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const TFamousBookGetFamousBookSlotNode& from);
  void MergeFrom(const TFamousBookGetFamousBookSlotNode& from);
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

  // optional uint32 Index = 1;
  inline bool has_index() const;
  inline void clear_index();
  static const int kIndexFieldNumber = 1;
  /*FOR2LUA
  <Record>
  	<name>TFamousBookGetFamousBookSlotNode</name>
  	<Function>
  		<name>index</name>
  		<replaceName>Index</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>set_index</name>
  		<replaceName>Index</replaceName>
  		<handler>descripter = pb_set_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_index</name>
  		<replaceName>Index</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline ::google::protobuf::uint32 index() const;
  inline void set_index(::google::protobuf::uint32 value);

  // optional uint32 Tid = 2;
  inline bool has_tid() const;
  inline void clear_tid();
  static const int kTidFieldNumber = 2;
  /*FOR2LUA
  <Record>
  	<name>TFamousBookGetFamousBookSlotNode</name>
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

  // optional .pb.EItemType Type = 3;
  inline bool has_type() const;
  inline void clear_type();
  static const int kTypeFieldNumber = 3;
  /*FOR2LUA
  <Record>
  	<name>TFamousBookGetFamousBookSlotNode</name>
  	<Function>
  		<name>type</name>
  		<replaceName>Type</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>set_type</name>
  		<replaceName>Type</replaceName>
  		<handler>descripter = pb_set_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_type</name>
  		<replaceName>Type</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline ::pb::EItemType type() const;
  inline void set_type(::pb::EItemType value);

  // @@protoc_insertion_point(class_scope:pb.TFamousBookGetFamousBookSlotNode)
 private:
  inline void set_has_index();
  inline void clear_has_index();
  inline void set_has_tid();
  inline void clear_has_tid();
  inline void set_has_type();
  inline void clear_has_type();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::uint32 index_;
  ::google::protobuf::uint32 tid_;
  int type_;
  friend void  protobuf_AddDesc_net_2fFamousBook_2eproto();
  friend void protobuf_AssignDesc_net_2fFamousBook_2eproto();
  friend void protobuf_ShutdownFile_net_2fFamousBook_2eproto();

  void InitAsDefaultInstance();
  static TFamousBookGetFamousBookSlotNode* default_instance_;
};
// -------------------------------------------------------------------

/*FOR2LUA
<Record>
	<name>TFamousBookGetFamousBookSingleInfo</name>
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
		<replaceName>net/FamousBook.proto</replaceName>
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
class TFamousBookGetFamousBookSingleInfo : public ::google::protobuf::Message {
 public:
  TFamousBookGetFamousBookSingleInfo();
  virtual ~TFamousBookGetFamousBookSingleInfo();

  TFamousBookGetFamousBookSingleInfo(const TFamousBookGetFamousBookSingleInfo& from);

  inline TFamousBookGetFamousBookSingleInfo& operator=(const TFamousBookGetFamousBookSingleInfo& from) {
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
  static const TFamousBookGetFamousBookSingleInfo& default_instance();

  void Swap(TFamousBookGetFamousBookSingleInfo* other);

  // implements Message ----------------------------------------------

  TFamousBookGetFamousBookSingleInfo* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const TFamousBookGetFamousBookSingleInfo& from);
  void MergeFrom(const TFamousBookGetFamousBookSingleInfo& from);
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

  // optional uint32 Index = 1;
  inline bool has_index() const;
  inline void clear_index();
  static const int kIndexFieldNumber = 1;
  /*FOR2LUA
  <Record>
  	<name>TFamousBookGetFamousBookSingleInfo</name>
  	<Function>
  		<name>index</name>
  		<replaceName>Index</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>set_index</name>
  		<replaceName>Index</replaceName>
  		<handler>descripter = pb_set_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_index</name>
  		<replaceName>Index</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline ::google::protobuf::uint32 index() const;
  inline void set_index(::google::protobuf::uint32 value);

  // repeated .pb.TFamousBookGetFamousBookSlotNode SlotNodeArr = 2;
  inline int slotnodearr_size() const;
  inline void clear_slotnodearr();
  static const int kSlotNodeArrFieldNumber = 2;
  /*FOR2LUA
  <Record>
  	<name>TFamousBookGetFamousBookSingleInfo</name>
  	<Function>
  		<name>slotnodearr</name>
  		<replaceName>SlotNodeArr</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>mutable_slotnodearr</name>
  		<replaceName>SlotNodeArr</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>add_slotnodearr</name>
  		<replaceName>SlotNodeArr</replaceName>
  		<handler>descripter = pb_repeated_add_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_slotnodearr</name>
  		<replaceName>SlotNodeArr</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  	<Function>
  		<name>slotnodearr_size</name>
  		<replaceName>SlotNodeArr</replaceName>
  		<handler>descripter = pb_repeated_size_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline const ::pb::TFamousBookGetFamousBookSlotNode& slotnodearr(int index) const;
  inline ::pb::TFamousBookGetFamousBookSlotNode* mutable_slotnodearr(int index);
  inline ::pb::TFamousBookGetFamousBookSlotNode* add_slotnodearr();
  inline const ::google::protobuf::RepeatedPtrField< ::pb::TFamousBookGetFamousBookSlotNode >&
      slotnodearr() const;
  inline ::google::protobuf::RepeatedPtrField< ::pb::TFamousBookGetFamousBookSlotNode >*
      mutable_slotnodearr();

  // @@protoc_insertion_point(class_scope:pb.TFamousBookGetFamousBookSingleInfo)
 private:
  inline void set_has_index();
  inline void clear_has_index();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::RepeatedPtrField< ::pb::TFamousBookGetFamousBookSlotNode > slotnodearr_;
  ::google::protobuf::uint32 index_;
  friend void  protobuf_AddDesc_net_2fFamousBook_2eproto();
  friend void protobuf_AssignDesc_net_2fFamousBook_2eproto();
  friend void protobuf_ShutdownFile_net_2fFamousBook_2eproto();

  void InitAsDefaultInstance();
  static TFamousBookGetFamousBookSingleInfo* default_instance_;
};
// -------------------------------------------------------------------

/*FOR2LUA
<Record>
	<name>TFamousBookGetFamousBookInfoRsp</name>
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
		<replaceName>net/FamousBook.proto</replaceName>
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
class TFamousBookGetFamousBookInfoRsp : public ::google::protobuf::Message {
 public:
  TFamousBookGetFamousBookInfoRsp();
  virtual ~TFamousBookGetFamousBookInfoRsp();

  TFamousBookGetFamousBookInfoRsp(const TFamousBookGetFamousBookInfoRsp& from);

  inline TFamousBookGetFamousBookInfoRsp& operator=(const TFamousBookGetFamousBookInfoRsp& from) {
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
  static const TFamousBookGetFamousBookInfoRsp& default_instance();

  void Swap(TFamousBookGetFamousBookInfoRsp* other);

  // implements Message ----------------------------------------------

  TFamousBookGetFamousBookInfoRsp* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const TFamousBookGetFamousBookInfoRsp& from);
  void MergeFrom(const TFamousBookGetFamousBookInfoRsp& from);
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

  // repeated .pb.TFamousBookGetFamousBookSingleInfo BookInfoArr = 1;
  inline int bookinfoarr_size() const;
  inline void clear_bookinfoarr();
  static const int kBookInfoArrFieldNumber = 1;
  /*FOR2LUA
  <Record>
  	<name>TFamousBookGetFamousBookInfoRsp</name>
  	<Function>
  		<name>bookinfoarr</name>
  		<replaceName>BookInfoArr</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>mutable_bookinfoarr</name>
  		<replaceName>BookInfoArr</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>add_bookinfoarr</name>
  		<replaceName>BookInfoArr</replaceName>
  		<handler>descripter = pb_repeated_add_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_bookinfoarr</name>
  		<replaceName>BookInfoArr</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  	<Function>
  		<name>bookinfoarr_size</name>
  		<replaceName>BookInfoArr</replaceName>
  		<handler>descripter = pb_repeated_size_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline const ::pb::TFamousBookGetFamousBookSingleInfo& bookinfoarr(int index) const;
  inline ::pb::TFamousBookGetFamousBookSingleInfo* mutable_bookinfoarr(int index);
  inline ::pb::TFamousBookGetFamousBookSingleInfo* add_bookinfoarr();
  inline const ::google::protobuf::RepeatedPtrField< ::pb::TFamousBookGetFamousBookSingleInfo >&
      bookinfoarr() const;
  inline ::google::protobuf::RepeatedPtrField< ::pb::TFamousBookGetFamousBookSingleInfo >*
      mutable_bookinfoarr();

  // @@protoc_insertion_point(class_scope:pb.TFamousBookGetFamousBookInfoRsp)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::RepeatedPtrField< ::pb::TFamousBookGetFamousBookSingleInfo > bookinfoarr_;
  friend void  protobuf_AddDesc_net_2fFamousBook_2eproto();
  friend void protobuf_AssignDesc_net_2fFamousBook_2eproto();
  friend void protobuf_ShutdownFile_net_2fFamousBook_2eproto();

  void InitAsDefaultInstance();
  static TFamousBookGetFamousBookInfoRsp* default_instance_;
};
// -------------------------------------------------------------------

/*FOR2LUA
<Record>
	<name>TFamousBookLightUpOrExtinguishedSlotNodeReq</name>
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
		<replaceName>net/FamousBook.proto</replaceName>
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
class TFamousBookLightUpOrExtinguishedSlotNodeReq : public ::google::protobuf::Message {
 public:
  TFamousBookLightUpOrExtinguishedSlotNodeReq();
  virtual ~TFamousBookLightUpOrExtinguishedSlotNodeReq();

  TFamousBookLightUpOrExtinguishedSlotNodeReq(const TFamousBookLightUpOrExtinguishedSlotNodeReq& from);

  inline TFamousBookLightUpOrExtinguishedSlotNodeReq& operator=(const TFamousBookLightUpOrExtinguishedSlotNodeReq& from) {
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
  static const TFamousBookLightUpOrExtinguishedSlotNodeReq& default_instance();

  void Swap(TFamousBookLightUpOrExtinguishedSlotNodeReq* other);

  // implements Message ----------------------------------------------

  TFamousBookLightUpOrExtinguishedSlotNodeReq* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const TFamousBookLightUpOrExtinguishedSlotNodeReq& from);
  void MergeFrom(const TFamousBookLightUpOrExtinguishedSlotNodeReq& from);
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

  // optional uint32 BookIndex = 1;
  inline bool has_bookindex() const;
  inline void clear_bookindex();
  static const int kBookIndexFieldNumber = 1;
  /*FOR2LUA
  <Record>
  	<name>TFamousBookLightUpOrExtinguishedSlotNodeReq</name>
  	<Function>
  		<name>bookindex</name>
  		<replaceName>BookIndex</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>set_bookindex</name>
  		<replaceName>BookIndex</replaceName>
  		<handler>descripter = pb_set_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_bookindex</name>
  		<replaceName>BookIndex</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline ::google::protobuf::uint32 bookindex() const;
  inline void set_bookindex(::google::protobuf::uint32 value);

  // optional uint32 SlotNodeIndex = 2;
  inline bool has_slotnodeindex() const;
  inline void clear_slotnodeindex();
  static const int kSlotNodeIndexFieldNumber = 2;
  /*FOR2LUA
  <Record>
  	<name>TFamousBookLightUpOrExtinguishedSlotNodeReq</name>
  	<Function>
  		<name>slotnodeindex</name>
  		<replaceName>SlotNodeIndex</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>set_slotnodeindex</name>
  		<replaceName>SlotNodeIndex</replaceName>
  		<handler>descripter = pb_set_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_slotnodeindex</name>
  		<replaceName>SlotNodeIndex</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline ::google::protobuf::uint32 slotnodeindex() const;
  inline void set_slotnodeindex(::google::protobuf::uint32 value);

  // optional uint32 Tid = 3;
  inline bool has_tid() const;
  inline void clear_tid();
  static const int kTidFieldNumber = 3;
  /*FOR2LUA
  <Record>
  	<name>TFamousBookLightUpOrExtinguishedSlotNodeReq</name>
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

  // optional .pb.EItemType Type = 4;
  inline bool has_type() const;
  inline void clear_type();
  static const int kTypeFieldNumber = 4;
  /*FOR2LUA
  <Record>
  	<name>TFamousBookLightUpOrExtinguishedSlotNodeReq</name>
  	<Function>
  		<name>type</name>
  		<replaceName>Type</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>set_type</name>
  		<replaceName>Type</replaceName>
  		<handler>descripter = pb_set_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_type</name>
  		<replaceName>Type</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline ::pb::EItemType type() const;
  inline void set_type(::pb::EItemType value);

  // @@protoc_insertion_point(class_scope:pb.TFamousBookLightUpOrExtinguishedSlotNodeReq)
 private:
  inline void set_has_bookindex();
  inline void clear_has_bookindex();
  inline void set_has_slotnodeindex();
  inline void clear_has_slotnodeindex();
  inline void set_has_tid();
  inline void clear_has_tid();
  inline void set_has_type();
  inline void clear_has_type();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::uint32 bookindex_;
  ::google::protobuf::uint32 slotnodeindex_;
  ::google::protobuf::uint32 tid_;
  int type_;
  friend void  protobuf_AddDesc_net_2fFamousBook_2eproto();
  friend void protobuf_AssignDesc_net_2fFamousBook_2eproto();
  friend void protobuf_ShutdownFile_net_2fFamousBook_2eproto();

  void InitAsDefaultInstance();
  static TFamousBookLightUpOrExtinguishedSlotNodeReq* default_instance_;
};
// ===================================================================


// ===================================================================

// TFamousBookGetFamousBookSlotNode

// optional uint32 Index = 1;
inline bool TFamousBookGetFamousBookSlotNode::has_index() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void TFamousBookGetFamousBookSlotNode::set_has_index() {
  _has_bits_[0] |= 0x00000001u;
}
inline void TFamousBookGetFamousBookSlotNode::clear_has_index() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void TFamousBookGetFamousBookSlotNode::clear_index() {
  index_ = 0u;
  clear_has_index();
}
inline ::google::protobuf::uint32 TFamousBookGetFamousBookSlotNode::index() const {
  // @@protoc_insertion_point(field_get:pb.TFamousBookGetFamousBookSlotNode.Index)
  return index_;
}
inline void TFamousBookGetFamousBookSlotNode::set_index(::google::protobuf::uint32 value) {
  set_has_index();
  index_ = value;
  // @@protoc_insertion_point(field_set:pb.TFamousBookGetFamousBookSlotNode.Index)
}

// optional uint32 Tid = 2;
inline bool TFamousBookGetFamousBookSlotNode::has_tid() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void TFamousBookGetFamousBookSlotNode::set_has_tid() {
  _has_bits_[0] |= 0x00000002u;
}
inline void TFamousBookGetFamousBookSlotNode::clear_has_tid() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void TFamousBookGetFamousBookSlotNode::clear_tid() {
  tid_ = 0u;
  clear_has_tid();
}
inline ::google::protobuf::uint32 TFamousBookGetFamousBookSlotNode::tid() const {
  // @@protoc_insertion_point(field_get:pb.TFamousBookGetFamousBookSlotNode.Tid)
  return tid_;
}
inline void TFamousBookGetFamousBookSlotNode::set_tid(::google::protobuf::uint32 value) {
  set_has_tid();
  tid_ = value;
  // @@protoc_insertion_point(field_set:pb.TFamousBookGetFamousBookSlotNode.Tid)
}

// optional .pb.EItemType Type = 3;
inline bool TFamousBookGetFamousBookSlotNode::has_type() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void TFamousBookGetFamousBookSlotNode::set_has_type() {
  _has_bits_[0] |= 0x00000004u;
}
inline void TFamousBookGetFamousBookSlotNode::clear_has_type() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void TFamousBookGetFamousBookSlotNode::clear_type() {
  type_ = 1;
  clear_has_type();
}
inline ::pb::EItemType TFamousBookGetFamousBookSlotNode::type() const {
  // @@protoc_insertion_point(field_get:pb.TFamousBookGetFamousBookSlotNode.Type)
  return static_cast< ::pb::EItemType >(type_);
}
inline void TFamousBookGetFamousBookSlotNode::set_type(::pb::EItemType value) {
  assert(::pb::EItemType_IsValid(value));
  set_has_type();
  type_ = value;
  // @@protoc_insertion_point(field_set:pb.TFamousBookGetFamousBookSlotNode.Type)
}

// -------------------------------------------------------------------

// TFamousBookGetFamousBookSingleInfo

// optional uint32 Index = 1;
inline bool TFamousBookGetFamousBookSingleInfo::has_index() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void TFamousBookGetFamousBookSingleInfo::set_has_index() {
  _has_bits_[0] |= 0x00000001u;
}
inline void TFamousBookGetFamousBookSingleInfo::clear_has_index() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void TFamousBookGetFamousBookSingleInfo::clear_index() {
  index_ = 0u;
  clear_has_index();
}
inline ::google::protobuf::uint32 TFamousBookGetFamousBookSingleInfo::index() const {
  // @@protoc_insertion_point(field_get:pb.TFamousBookGetFamousBookSingleInfo.Index)
  return index_;
}
inline void TFamousBookGetFamousBookSingleInfo::set_index(::google::protobuf::uint32 value) {
  set_has_index();
  index_ = value;
  // @@protoc_insertion_point(field_set:pb.TFamousBookGetFamousBookSingleInfo.Index)
}

// repeated .pb.TFamousBookGetFamousBookSlotNode SlotNodeArr = 2;
inline int TFamousBookGetFamousBookSingleInfo::slotnodearr_size() const {
  return slotnodearr_.size();
}
inline void TFamousBookGetFamousBookSingleInfo::clear_slotnodearr() {
  slotnodearr_.Clear();
}
inline const ::pb::TFamousBookGetFamousBookSlotNode& TFamousBookGetFamousBookSingleInfo::slotnodearr(int index) const {
  // @@protoc_insertion_point(field_get:pb.TFamousBookGetFamousBookSingleInfo.SlotNodeArr)
  return slotnodearr_.Get(index);
}
inline ::pb::TFamousBookGetFamousBookSlotNode* TFamousBookGetFamousBookSingleInfo::mutable_slotnodearr(int index) {
  // @@protoc_insertion_point(field_mutable:pb.TFamousBookGetFamousBookSingleInfo.SlotNodeArr)
  return slotnodearr_.Mutable(index);
}
inline ::pb::TFamousBookGetFamousBookSlotNode* TFamousBookGetFamousBookSingleInfo::add_slotnodearr() {
  // @@protoc_insertion_point(field_add:pb.TFamousBookGetFamousBookSingleInfo.SlotNodeArr)
  return slotnodearr_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::pb::TFamousBookGetFamousBookSlotNode >&
TFamousBookGetFamousBookSingleInfo::slotnodearr() const {
  // @@protoc_insertion_point(field_list:pb.TFamousBookGetFamousBookSingleInfo.SlotNodeArr)
  return slotnodearr_;
}
inline ::google::protobuf::RepeatedPtrField< ::pb::TFamousBookGetFamousBookSlotNode >*
TFamousBookGetFamousBookSingleInfo::mutable_slotnodearr() {
  // @@protoc_insertion_point(field_mutable_list:pb.TFamousBookGetFamousBookSingleInfo.SlotNodeArr)
  return &slotnodearr_;
}

// -------------------------------------------------------------------

// TFamousBookGetFamousBookInfoRsp

// repeated .pb.TFamousBookGetFamousBookSingleInfo BookInfoArr = 1;
inline int TFamousBookGetFamousBookInfoRsp::bookinfoarr_size() const {
  return bookinfoarr_.size();
}
inline void TFamousBookGetFamousBookInfoRsp::clear_bookinfoarr() {
  bookinfoarr_.Clear();
}
inline const ::pb::TFamousBookGetFamousBookSingleInfo& TFamousBookGetFamousBookInfoRsp::bookinfoarr(int index) const {
  // @@protoc_insertion_point(field_get:pb.TFamousBookGetFamousBookInfoRsp.BookInfoArr)
  return bookinfoarr_.Get(index);
}
inline ::pb::TFamousBookGetFamousBookSingleInfo* TFamousBookGetFamousBookInfoRsp::mutable_bookinfoarr(int index) {
  // @@protoc_insertion_point(field_mutable:pb.TFamousBookGetFamousBookInfoRsp.BookInfoArr)
  return bookinfoarr_.Mutable(index);
}
inline ::pb::TFamousBookGetFamousBookSingleInfo* TFamousBookGetFamousBookInfoRsp::add_bookinfoarr() {
  // @@protoc_insertion_point(field_add:pb.TFamousBookGetFamousBookInfoRsp.BookInfoArr)
  return bookinfoarr_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::pb::TFamousBookGetFamousBookSingleInfo >&
TFamousBookGetFamousBookInfoRsp::bookinfoarr() const {
  // @@protoc_insertion_point(field_list:pb.TFamousBookGetFamousBookInfoRsp.BookInfoArr)
  return bookinfoarr_;
}
inline ::google::protobuf::RepeatedPtrField< ::pb::TFamousBookGetFamousBookSingleInfo >*
TFamousBookGetFamousBookInfoRsp::mutable_bookinfoarr() {
  // @@protoc_insertion_point(field_mutable_list:pb.TFamousBookGetFamousBookInfoRsp.BookInfoArr)
  return &bookinfoarr_;
}

// -------------------------------------------------------------------

// TFamousBookLightUpOrExtinguishedSlotNodeReq

// optional uint32 BookIndex = 1;
inline bool TFamousBookLightUpOrExtinguishedSlotNodeReq::has_bookindex() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void TFamousBookLightUpOrExtinguishedSlotNodeReq::set_has_bookindex() {
  _has_bits_[0] |= 0x00000001u;
}
inline void TFamousBookLightUpOrExtinguishedSlotNodeReq::clear_has_bookindex() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void TFamousBookLightUpOrExtinguishedSlotNodeReq::clear_bookindex() {
  bookindex_ = 0u;
  clear_has_bookindex();
}
inline ::google::protobuf::uint32 TFamousBookLightUpOrExtinguishedSlotNodeReq::bookindex() const {
  // @@protoc_insertion_point(field_get:pb.TFamousBookLightUpOrExtinguishedSlotNodeReq.BookIndex)
  return bookindex_;
}
inline void TFamousBookLightUpOrExtinguishedSlotNodeReq::set_bookindex(::google::protobuf::uint32 value) {
  set_has_bookindex();
  bookindex_ = value;
  // @@protoc_insertion_point(field_set:pb.TFamousBookLightUpOrExtinguishedSlotNodeReq.BookIndex)
}

// optional uint32 SlotNodeIndex = 2;
inline bool TFamousBookLightUpOrExtinguishedSlotNodeReq::has_slotnodeindex() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void TFamousBookLightUpOrExtinguishedSlotNodeReq::set_has_slotnodeindex() {
  _has_bits_[0] |= 0x00000002u;
}
inline void TFamousBookLightUpOrExtinguishedSlotNodeReq::clear_has_slotnodeindex() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void TFamousBookLightUpOrExtinguishedSlotNodeReq::clear_slotnodeindex() {
  slotnodeindex_ = 0u;
  clear_has_slotnodeindex();
}
inline ::google::protobuf::uint32 TFamousBookLightUpOrExtinguishedSlotNodeReq::slotnodeindex() const {
  // @@protoc_insertion_point(field_get:pb.TFamousBookLightUpOrExtinguishedSlotNodeReq.SlotNodeIndex)
  return slotnodeindex_;
}
inline void TFamousBookLightUpOrExtinguishedSlotNodeReq::set_slotnodeindex(::google::protobuf::uint32 value) {
  set_has_slotnodeindex();
  slotnodeindex_ = value;
  // @@protoc_insertion_point(field_set:pb.TFamousBookLightUpOrExtinguishedSlotNodeReq.SlotNodeIndex)
}

// optional uint32 Tid = 3;
inline bool TFamousBookLightUpOrExtinguishedSlotNodeReq::has_tid() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void TFamousBookLightUpOrExtinguishedSlotNodeReq::set_has_tid() {
  _has_bits_[0] |= 0x00000004u;
}
inline void TFamousBookLightUpOrExtinguishedSlotNodeReq::clear_has_tid() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void TFamousBookLightUpOrExtinguishedSlotNodeReq::clear_tid() {
  tid_ = 0u;
  clear_has_tid();
}
inline ::google::protobuf::uint32 TFamousBookLightUpOrExtinguishedSlotNodeReq::tid() const {
  // @@protoc_insertion_point(field_get:pb.TFamousBookLightUpOrExtinguishedSlotNodeReq.Tid)
  return tid_;
}
inline void TFamousBookLightUpOrExtinguishedSlotNodeReq::set_tid(::google::protobuf::uint32 value) {
  set_has_tid();
  tid_ = value;
  // @@protoc_insertion_point(field_set:pb.TFamousBookLightUpOrExtinguishedSlotNodeReq.Tid)
}

// optional .pb.EItemType Type = 4;
inline bool TFamousBookLightUpOrExtinguishedSlotNodeReq::has_type() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void TFamousBookLightUpOrExtinguishedSlotNodeReq::set_has_type() {
  _has_bits_[0] |= 0x00000008u;
}
inline void TFamousBookLightUpOrExtinguishedSlotNodeReq::clear_has_type() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void TFamousBookLightUpOrExtinguishedSlotNodeReq::clear_type() {
  type_ = 1;
  clear_has_type();
}
inline ::pb::EItemType TFamousBookLightUpOrExtinguishedSlotNodeReq::type() const {
  // @@protoc_insertion_point(field_get:pb.TFamousBookLightUpOrExtinguishedSlotNodeReq.Type)
  return static_cast< ::pb::EItemType >(type_);
}
inline void TFamousBookLightUpOrExtinguishedSlotNodeReq::set_type(::pb::EItemType value) {
  assert(::pb::EItemType_IsValid(value));
  set_has_type();
  type_ = value;
  // @@protoc_insertion_point(field_set:pb.TFamousBookLightUpOrExtinguishedSlotNodeReq.Type)
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace pb

#ifndef SWIG
namespace google {
namespace protobuf {

template <> struct is_proto_enum< ::pb::EItemType> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::pb::EItemType>() {
  return ::pb::EItemType_descriptor();
}

}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_net_2fFamousBook_2eproto__INCLUDED
