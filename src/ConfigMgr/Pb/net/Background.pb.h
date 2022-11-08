// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: net/Background.proto

#ifndef PROTOBUF_net_2fBackground_2eproto__INCLUDED
#define PROTOBUF_net_2fBackground_2eproto__INCLUDED

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
void  protobuf_AddDesc_net_2fBackground_2eproto();
void protobuf_AssignDesc_net_2fBackground_2eproto();
void protobuf_ShutdownFile_net_2fBackground_2eproto();

class TBackgroundInfo;
class THeroBackground;
class TBackgroundGetInfoRsp;
class TBackgroundSetBackgroundReq;

// ===================================================================

/*FOR2LUA
<Record>
	<name>TBackgroundInfo</name>
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
		<replaceName>net/Background.proto</replaceName>
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
class TBackgroundInfo : public ::google::protobuf::Message {
 public:
  TBackgroundInfo();
  virtual ~TBackgroundInfo();

  TBackgroundInfo(const TBackgroundInfo& from);

  inline TBackgroundInfo& operator=(const TBackgroundInfo& from) {
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
  static const TBackgroundInfo& default_instance();

  void Swap(TBackgroundInfo* other);

  // implements Message ----------------------------------------------

  TBackgroundInfo* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const TBackgroundInfo& from);
  void MergeFrom(const TBackgroundInfo& from);
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

  // optional uint32 BackgroundId = 1;
  inline bool has_backgroundid() const;
  inline void clear_backgroundid();
  static const int kBackgroundIdFieldNumber = 1;
  /*FOR2LUA
  <Record>
  	<name>TBackgroundInfo</name>
  	<Function>
  		<name>backgroundid</name>
  		<replaceName>BackgroundId</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>set_backgroundid</name>
  		<replaceName>BackgroundId</replaceName>
  		<handler>descripter = pb_set_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_backgroundid</name>
  		<replaceName>BackgroundId</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline ::google::protobuf::uint32 backgroundid() const;
  inline void set_backgroundid(::google::protobuf::uint32 value);

  // optional uint64 ActivationTime = 2;
  inline bool has_activationtime() const;
  inline void clear_activationtime();
  static const int kActivationTimeFieldNumber = 2;
  /*FOR2LUA
  <Record>
  	<name>TBackgroundInfo</name>
  	<Function>
  		<name>activationtime</name>
  		<replaceName>ActivationTime</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>set_activationtime</name>
  		<replaceName>ActivationTime</replaceName>
  		<handler>descripter = pb_set_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_activationtime</name>
  		<replaceName>ActivationTime</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline ::google::protobuf::uint64 activationtime() const;
  inline void set_activationtime(::google::protobuf::uint64 value);

  // @@protoc_insertion_point(class_scope:pb.TBackgroundInfo)
 private:
  inline void set_has_backgroundid();
  inline void clear_has_backgroundid();
  inline void set_has_activationtime();
  inline void clear_has_activationtime();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::uint64 activationtime_;
  ::google::protobuf::uint32 backgroundid_;
  friend void  protobuf_AddDesc_net_2fBackground_2eproto();
  friend void protobuf_AssignDesc_net_2fBackground_2eproto();
  friend void protobuf_ShutdownFile_net_2fBackground_2eproto();

  void InitAsDefaultInstance();
  static TBackgroundInfo* default_instance_;
};
// -------------------------------------------------------------------

/*FOR2LUA
<Record>
	<name>THeroBackground</name>
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
		<replaceName>net/Background.proto</replaceName>
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
class THeroBackground : public ::google::protobuf::Message {
 public:
  THeroBackground();
  virtual ~THeroBackground();

  THeroBackground(const THeroBackground& from);

  inline THeroBackground& operator=(const THeroBackground& from) {
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
  static const THeroBackground& default_instance();

  void Swap(THeroBackground* other);

  // implements Message ----------------------------------------------

  THeroBackground* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const THeroBackground& from);
  void MergeFrom(const THeroBackground& from);
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

  // optional uint32 ModelId = 1;
  inline bool has_modelid() const;
  inline void clear_modelid();
  static const int kModelIdFieldNumber = 1;
  /*FOR2LUA
  <Record>
  	<name>THeroBackground</name>
  	<Function>
  		<name>modelid</name>
  		<replaceName>ModelId</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>set_modelid</name>
  		<replaceName>ModelId</replaceName>
  		<handler>descripter = pb_set_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_modelid</name>
  		<replaceName>ModelId</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline ::google::protobuf::uint32 modelid() const;
  inline void set_modelid(::google::protobuf::uint32 value);

  // optional uint32 BackgroundId = 2;
  inline bool has_backgroundid() const;
  inline void clear_backgroundid();
  static const int kBackgroundIdFieldNumber = 2;
  /*FOR2LUA
  <Record>
  	<name>THeroBackground</name>
  	<Function>
  		<name>backgroundid</name>
  		<replaceName>BackgroundId</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>set_backgroundid</name>
  		<replaceName>BackgroundId</replaceName>
  		<handler>descripter = pb_set_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_backgroundid</name>
  		<replaceName>BackgroundId</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline ::google::protobuf::uint32 backgroundid() const;
  inline void set_backgroundid(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:pb.THeroBackground)
 private:
  inline void set_has_modelid();
  inline void clear_has_modelid();
  inline void set_has_backgroundid();
  inline void clear_has_backgroundid();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::uint32 modelid_;
  ::google::protobuf::uint32 backgroundid_;
  friend void  protobuf_AddDesc_net_2fBackground_2eproto();
  friend void protobuf_AssignDesc_net_2fBackground_2eproto();
  friend void protobuf_ShutdownFile_net_2fBackground_2eproto();

  void InitAsDefaultInstance();
  static THeroBackground* default_instance_;
};
// -------------------------------------------------------------------

/*FOR2LUA
<Record>
	<name>TBackgroundGetInfoRsp</name>
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
		<replaceName>net/Background.proto</replaceName>
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
class TBackgroundGetInfoRsp : public ::google::protobuf::Message {
 public:
  TBackgroundGetInfoRsp();
  virtual ~TBackgroundGetInfoRsp();

  TBackgroundGetInfoRsp(const TBackgroundGetInfoRsp& from);

  inline TBackgroundGetInfoRsp& operator=(const TBackgroundGetInfoRsp& from) {
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
  static const TBackgroundGetInfoRsp& default_instance();

  void Swap(TBackgroundGetInfoRsp* other);

  // implements Message ----------------------------------------------

  TBackgroundGetInfoRsp* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const TBackgroundGetInfoRsp& from);
  void MergeFrom(const TBackgroundGetInfoRsp& from);
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

  // repeated .pb.TBackgroundInfo BackgroundInfoArray = 1;
  inline int backgroundinfoarray_size() const;
  inline void clear_backgroundinfoarray();
  static const int kBackgroundInfoArrayFieldNumber = 1;
  /*FOR2LUA
  <Record>
  	<name>TBackgroundGetInfoRsp</name>
  	<Function>
  		<name>backgroundinfoarray</name>
  		<replaceName>BackgroundInfoArray</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>mutable_backgroundinfoarray</name>
  		<replaceName>BackgroundInfoArray</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>add_backgroundinfoarray</name>
  		<replaceName>BackgroundInfoArray</replaceName>
  		<handler>descripter = pb_repeated_add_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_backgroundinfoarray</name>
  		<replaceName>BackgroundInfoArray</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  	<Function>
  		<name>backgroundinfoarray_size</name>
  		<replaceName>BackgroundInfoArray</replaceName>
  		<handler>descripter = pb_repeated_size_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline const ::pb::TBackgroundInfo& backgroundinfoarray(int index) const;
  inline ::pb::TBackgroundInfo* mutable_backgroundinfoarray(int index);
  inline ::pb::TBackgroundInfo* add_backgroundinfoarray();
  inline const ::google::protobuf::RepeatedPtrField< ::pb::TBackgroundInfo >&
      backgroundinfoarray() const;
  inline ::google::protobuf::RepeatedPtrField< ::pb::TBackgroundInfo >*
      mutable_backgroundinfoarray();

  // repeated .pb.THeroBackground HeroBackgroundArray = 2;
  inline int herobackgroundarray_size() const;
  inline void clear_herobackgroundarray();
  static const int kHeroBackgroundArrayFieldNumber = 2;
  /*FOR2LUA
  <Record>
  	<name>TBackgroundGetInfoRsp</name>
  	<Function>
  		<name>herobackgroundarray</name>
  		<replaceName>HeroBackgroundArray</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>mutable_herobackgroundarray</name>
  		<replaceName>HeroBackgroundArray</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>add_herobackgroundarray</name>
  		<replaceName>HeroBackgroundArray</replaceName>
  		<handler>descripter = pb_repeated_add_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_herobackgroundarray</name>
  		<replaceName>HeroBackgroundArray</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  	<Function>
  		<name>herobackgroundarray_size</name>
  		<replaceName>HeroBackgroundArray</replaceName>
  		<handler>descripter = pb_repeated_size_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline const ::pb::THeroBackground& herobackgroundarray(int index) const;
  inline ::pb::THeroBackground* mutable_herobackgroundarray(int index);
  inline ::pb::THeroBackground* add_herobackgroundarray();
  inline const ::google::protobuf::RepeatedPtrField< ::pb::THeroBackground >&
      herobackgroundarray() const;
  inline ::google::protobuf::RepeatedPtrField< ::pb::THeroBackground >*
      mutable_herobackgroundarray();

  // @@protoc_insertion_point(class_scope:pb.TBackgroundGetInfoRsp)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::RepeatedPtrField< ::pb::TBackgroundInfo > backgroundinfoarray_;
  ::google::protobuf::RepeatedPtrField< ::pb::THeroBackground > herobackgroundarray_;
  friend void  protobuf_AddDesc_net_2fBackground_2eproto();
  friend void protobuf_AssignDesc_net_2fBackground_2eproto();
  friend void protobuf_ShutdownFile_net_2fBackground_2eproto();

  void InitAsDefaultInstance();
  static TBackgroundGetInfoRsp* default_instance_;
};
// -------------------------------------------------------------------

/*FOR2LUA
<Record>
	<name>TBackgroundSetBackgroundReq</name>
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
		<replaceName>net/Background.proto</replaceName>
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
class TBackgroundSetBackgroundReq : public ::google::protobuf::Message {
 public:
  TBackgroundSetBackgroundReq();
  virtual ~TBackgroundSetBackgroundReq();

  TBackgroundSetBackgroundReq(const TBackgroundSetBackgroundReq& from);

  inline TBackgroundSetBackgroundReq& operator=(const TBackgroundSetBackgroundReq& from) {
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
  static const TBackgroundSetBackgroundReq& default_instance();

  void Swap(TBackgroundSetBackgroundReq* other);

  // implements Message ----------------------------------------------

  TBackgroundSetBackgroundReq* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const TBackgroundSetBackgroundReq& from);
  void MergeFrom(const TBackgroundSetBackgroundReq& from);
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

  // optional .pb.THeroBackground HeroBackgroundSingle = 1;
  inline bool has_herobackgroundsingle() const;
  inline void clear_herobackgroundsingle();
  static const int kHeroBackgroundSingleFieldNumber = 1;
  /*FOR2LUA
  <Record>
  	<name>TBackgroundSetBackgroundReq</name>
  	<Function>
  		<name>herobackgroundsingle</name>
  		<replaceName>HeroBackgroundSingle</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>set_herobackgroundsingle</name>
  		<replaceName>HeroBackgroundSingle</replaceName>
  		<handler>descripter = pb_set_message_cpp()</handler>
  	</Function>
  	<Function>
  		<name>set_allocated_herobackgroundsingle</name>
  		<replaceName>HeroBackgroundSingle</replaceName>
  		<handler>descripter = pb_set_message_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_herobackgroundsingle</name>
  		<replaceName>HeroBackgroundSingle</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline const ::pb::THeroBackground& herobackgroundsingle() const;
  inline ::pb::THeroBackground* mutable_herobackgroundsingle();
  inline ::pb::THeroBackground* release_herobackgroundsingle();
  inline void set_allocated_herobackgroundsingle(::pb::THeroBackground* herobackgroundsingle);

  // optional bool IsUsedForAll = 2;
  inline bool has_isusedforall() const;
  inline void clear_isusedforall();
  static const int kIsUsedForAllFieldNumber = 2;
  /*FOR2LUA
  <Record>
  	<name>TBackgroundSetBackgroundReq</name>
  	<Function>
  		<name>isusedforall</name>
  		<replaceName>IsUsedForAll</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>set_isusedforall</name>
  		<replaceName>IsUsedForAll</replaceName>
  		<handler>descripter = pb_set_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_isusedforall</name>
  		<replaceName>IsUsedForAll</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline bool isusedforall() const;
  inline void set_isusedforall(bool value);

  // @@protoc_insertion_point(class_scope:pb.TBackgroundSetBackgroundReq)
 private:
  inline void set_has_herobackgroundsingle();
  inline void clear_has_herobackgroundsingle();
  inline void set_has_isusedforall();
  inline void clear_has_isusedforall();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::pb::THeroBackground* herobackgroundsingle_;
  bool isusedforall_;
  friend void  protobuf_AddDesc_net_2fBackground_2eproto();
  friend void protobuf_AssignDesc_net_2fBackground_2eproto();
  friend void protobuf_ShutdownFile_net_2fBackground_2eproto();

  void InitAsDefaultInstance();
  static TBackgroundSetBackgroundReq* default_instance_;
};
// ===================================================================


// ===================================================================

// TBackgroundInfo

// optional uint32 BackgroundId = 1;
inline bool TBackgroundInfo::has_backgroundid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void TBackgroundInfo::set_has_backgroundid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void TBackgroundInfo::clear_has_backgroundid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void TBackgroundInfo::clear_backgroundid() {
  backgroundid_ = 0u;
  clear_has_backgroundid();
}
inline ::google::protobuf::uint32 TBackgroundInfo::backgroundid() const {
  // @@protoc_insertion_point(field_get:pb.TBackgroundInfo.BackgroundId)
  return backgroundid_;
}
inline void TBackgroundInfo::set_backgroundid(::google::protobuf::uint32 value) {
  set_has_backgroundid();
  backgroundid_ = value;
  // @@protoc_insertion_point(field_set:pb.TBackgroundInfo.BackgroundId)
}

// optional uint64 ActivationTime = 2;
inline bool TBackgroundInfo::has_activationtime() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void TBackgroundInfo::set_has_activationtime() {
  _has_bits_[0] |= 0x00000002u;
}
inline void TBackgroundInfo::clear_has_activationtime() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void TBackgroundInfo::clear_activationtime() {
  activationtime_ = GOOGLE_ULONGLONG(0);
  clear_has_activationtime();
}
inline ::google::protobuf::uint64 TBackgroundInfo::activationtime() const {
  // @@protoc_insertion_point(field_get:pb.TBackgroundInfo.ActivationTime)
  return activationtime_;
}
inline void TBackgroundInfo::set_activationtime(::google::protobuf::uint64 value) {
  set_has_activationtime();
  activationtime_ = value;
  // @@protoc_insertion_point(field_set:pb.TBackgroundInfo.ActivationTime)
}

// -------------------------------------------------------------------

// THeroBackground

// optional uint32 ModelId = 1;
inline bool THeroBackground::has_modelid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void THeroBackground::set_has_modelid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void THeroBackground::clear_has_modelid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void THeroBackground::clear_modelid() {
  modelid_ = 0u;
  clear_has_modelid();
}
inline ::google::protobuf::uint32 THeroBackground::modelid() const {
  // @@protoc_insertion_point(field_get:pb.THeroBackground.ModelId)
  return modelid_;
}
inline void THeroBackground::set_modelid(::google::protobuf::uint32 value) {
  set_has_modelid();
  modelid_ = value;
  // @@protoc_insertion_point(field_set:pb.THeroBackground.ModelId)
}

// optional uint32 BackgroundId = 2;
inline bool THeroBackground::has_backgroundid() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void THeroBackground::set_has_backgroundid() {
  _has_bits_[0] |= 0x00000002u;
}
inline void THeroBackground::clear_has_backgroundid() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void THeroBackground::clear_backgroundid() {
  backgroundid_ = 0u;
  clear_has_backgroundid();
}
inline ::google::protobuf::uint32 THeroBackground::backgroundid() const {
  // @@protoc_insertion_point(field_get:pb.THeroBackground.BackgroundId)
  return backgroundid_;
}
inline void THeroBackground::set_backgroundid(::google::protobuf::uint32 value) {
  set_has_backgroundid();
  backgroundid_ = value;
  // @@protoc_insertion_point(field_set:pb.THeroBackground.BackgroundId)
}

// -------------------------------------------------------------------

// TBackgroundGetInfoRsp

// repeated .pb.TBackgroundInfo BackgroundInfoArray = 1;
inline int TBackgroundGetInfoRsp::backgroundinfoarray_size() const {
  return backgroundinfoarray_.size();
}
inline void TBackgroundGetInfoRsp::clear_backgroundinfoarray() {
  backgroundinfoarray_.Clear();
}
inline const ::pb::TBackgroundInfo& TBackgroundGetInfoRsp::backgroundinfoarray(int index) const {
  // @@protoc_insertion_point(field_get:pb.TBackgroundGetInfoRsp.BackgroundInfoArray)
  return backgroundinfoarray_.Get(index);
}
inline ::pb::TBackgroundInfo* TBackgroundGetInfoRsp::mutable_backgroundinfoarray(int index) {
  // @@protoc_insertion_point(field_mutable:pb.TBackgroundGetInfoRsp.BackgroundInfoArray)
  return backgroundinfoarray_.Mutable(index);
}
inline ::pb::TBackgroundInfo* TBackgroundGetInfoRsp::add_backgroundinfoarray() {
  // @@protoc_insertion_point(field_add:pb.TBackgroundGetInfoRsp.BackgroundInfoArray)
  return backgroundinfoarray_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::pb::TBackgroundInfo >&
TBackgroundGetInfoRsp::backgroundinfoarray() const {
  // @@protoc_insertion_point(field_list:pb.TBackgroundGetInfoRsp.BackgroundInfoArray)
  return backgroundinfoarray_;
}
inline ::google::protobuf::RepeatedPtrField< ::pb::TBackgroundInfo >*
TBackgroundGetInfoRsp::mutable_backgroundinfoarray() {
  // @@protoc_insertion_point(field_mutable_list:pb.TBackgroundGetInfoRsp.BackgroundInfoArray)
  return &backgroundinfoarray_;
}

// repeated .pb.THeroBackground HeroBackgroundArray = 2;
inline int TBackgroundGetInfoRsp::herobackgroundarray_size() const {
  return herobackgroundarray_.size();
}
inline void TBackgroundGetInfoRsp::clear_herobackgroundarray() {
  herobackgroundarray_.Clear();
}
inline const ::pb::THeroBackground& TBackgroundGetInfoRsp::herobackgroundarray(int index) const {
  // @@protoc_insertion_point(field_get:pb.TBackgroundGetInfoRsp.HeroBackgroundArray)
  return herobackgroundarray_.Get(index);
}
inline ::pb::THeroBackground* TBackgroundGetInfoRsp::mutable_herobackgroundarray(int index) {
  // @@protoc_insertion_point(field_mutable:pb.TBackgroundGetInfoRsp.HeroBackgroundArray)
  return herobackgroundarray_.Mutable(index);
}
inline ::pb::THeroBackground* TBackgroundGetInfoRsp::add_herobackgroundarray() {
  // @@protoc_insertion_point(field_add:pb.TBackgroundGetInfoRsp.HeroBackgroundArray)
  return herobackgroundarray_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::pb::THeroBackground >&
TBackgroundGetInfoRsp::herobackgroundarray() const {
  // @@protoc_insertion_point(field_list:pb.TBackgroundGetInfoRsp.HeroBackgroundArray)
  return herobackgroundarray_;
}
inline ::google::protobuf::RepeatedPtrField< ::pb::THeroBackground >*
TBackgroundGetInfoRsp::mutable_herobackgroundarray() {
  // @@protoc_insertion_point(field_mutable_list:pb.TBackgroundGetInfoRsp.HeroBackgroundArray)
  return &herobackgroundarray_;
}

// -------------------------------------------------------------------

// TBackgroundSetBackgroundReq

// optional .pb.THeroBackground HeroBackgroundSingle = 1;
inline bool TBackgroundSetBackgroundReq::has_herobackgroundsingle() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void TBackgroundSetBackgroundReq::set_has_herobackgroundsingle() {
  _has_bits_[0] |= 0x00000001u;
}
inline void TBackgroundSetBackgroundReq::clear_has_herobackgroundsingle() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void TBackgroundSetBackgroundReq::clear_herobackgroundsingle() {
  if (herobackgroundsingle_ != NULL) herobackgroundsingle_->::pb::THeroBackground::Clear();
  clear_has_herobackgroundsingle();
}
inline const ::pb::THeroBackground& TBackgroundSetBackgroundReq::herobackgroundsingle() const {
  // @@protoc_insertion_point(field_get:pb.TBackgroundSetBackgroundReq.HeroBackgroundSingle)
  return herobackgroundsingle_ != NULL ? *herobackgroundsingle_ : *default_instance_->herobackgroundsingle_;
}
inline ::pb::THeroBackground* TBackgroundSetBackgroundReq::mutable_herobackgroundsingle() {
  set_has_herobackgroundsingle();
  if (herobackgroundsingle_ == NULL) herobackgroundsingle_ = new ::pb::THeroBackground;
  // @@protoc_insertion_point(field_mutable:pb.TBackgroundSetBackgroundReq.HeroBackgroundSingle)
  return herobackgroundsingle_;
}
inline ::pb::THeroBackground* TBackgroundSetBackgroundReq::release_herobackgroundsingle() {
  clear_has_herobackgroundsingle();
  ::pb::THeroBackground* temp = herobackgroundsingle_;
  herobackgroundsingle_ = NULL;
  return temp;
}
inline void TBackgroundSetBackgroundReq::set_allocated_herobackgroundsingle(::pb::THeroBackground* herobackgroundsingle) {
  delete herobackgroundsingle_;
  herobackgroundsingle_ = herobackgroundsingle;
  if (herobackgroundsingle) {
    set_has_herobackgroundsingle();
  } else {
    clear_has_herobackgroundsingle();
  }
  // @@protoc_insertion_point(field_set_allocated:pb.TBackgroundSetBackgroundReq.HeroBackgroundSingle)
}

// optional bool IsUsedForAll = 2;
inline bool TBackgroundSetBackgroundReq::has_isusedforall() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void TBackgroundSetBackgroundReq::set_has_isusedforall() {
  _has_bits_[0] |= 0x00000002u;
}
inline void TBackgroundSetBackgroundReq::clear_has_isusedforall() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void TBackgroundSetBackgroundReq::clear_isusedforall() {
  isusedforall_ = false;
  clear_has_isusedforall();
}
inline bool TBackgroundSetBackgroundReq::isusedforall() const {
  // @@protoc_insertion_point(field_get:pb.TBackgroundSetBackgroundReq.IsUsedForAll)
  return isusedforall_;
}
inline void TBackgroundSetBackgroundReq::set_isusedforall(bool value) {
  set_has_isusedforall();
  isusedforall_ = value;
  // @@protoc_insertion_point(field_set:pb.TBackgroundSetBackgroundReq.IsUsedForAll)
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

#endif  // PROTOBUF_net_2fBackground_2eproto__INCLUDED
