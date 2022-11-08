// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: net/ActHeroTestuse.proto

#ifndef PROTOBUF_net_2fActHeroTestuse_2eproto__INCLUDED
#define PROTOBUF_net_2fActHeroTestuse_2eproto__INCLUDED

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
void  protobuf_AddDesc_net_2fActHeroTestuse_2eproto();
void protobuf_AssignDesc_net_2fActHeroTestuse_2eproto();
void protobuf_ShutdownFile_net_2fActHeroTestuse_2eproto();

class TActHeroTestUseGetInfoRsp;
class TActHeroTestUseTryOutReq;

// ===================================================================

/*FOR2LUA
<Record>
	<name>TActHeroTestUseGetInfoRsp</name>
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
		<replaceName>net/ActHeroTestuse.proto</replaceName>
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
class TActHeroTestUseGetInfoRsp : public ::google::protobuf::Message {
 public:
  TActHeroTestUseGetInfoRsp();
  virtual ~TActHeroTestUseGetInfoRsp();

  TActHeroTestUseGetInfoRsp(const TActHeroTestUseGetInfoRsp& from);

  inline TActHeroTestUseGetInfoRsp& operator=(const TActHeroTestUseGetInfoRsp& from) {
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
  static const TActHeroTestUseGetInfoRsp& default_instance();

  void Swap(TActHeroTestUseGetInfoRsp* other);

  // implements Message ----------------------------------------------

  TActHeroTestUseGetInfoRsp* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const TActHeroTestUseGetInfoRsp& from);
  void MergeFrom(const TActHeroTestUseGetInfoRsp& from);
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

  // optional uint32 TryOutId = 1;
  inline bool has_tryoutid() const;
  inline void clear_tryoutid();
  static const int kTryOutIdFieldNumber = 1;
  /*FOR2LUA
  <Record>
  	<name>TActHeroTestUseGetInfoRsp</name>
  	<Function>
  		<name>tryoutid</name>
  		<replaceName>TryOutId</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>set_tryoutid</name>
  		<replaceName>TryOutId</replaceName>
  		<handler>descripter = pb_set_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_tryoutid</name>
  		<replaceName>TryOutId</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline ::google::protobuf::uint32 tryoutid() const;
  inline void set_tryoutid(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:pb.TActHeroTestUseGetInfoRsp)
 private:
  inline void set_has_tryoutid();
  inline void clear_has_tryoutid();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::uint32 tryoutid_;
  friend void  protobuf_AddDesc_net_2fActHeroTestuse_2eproto();
  friend void protobuf_AssignDesc_net_2fActHeroTestuse_2eproto();
  friend void protobuf_ShutdownFile_net_2fActHeroTestuse_2eproto();

  void InitAsDefaultInstance();
  static TActHeroTestUseGetInfoRsp* default_instance_;
};
// -------------------------------------------------------------------

/*FOR2LUA
<Record>
	<name>TActHeroTestUseTryOutReq</name>
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
		<replaceName>net/ActHeroTestuse.proto</replaceName>
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
class TActHeroTestUseTryOutReq : public ::google::protobuf::Message {
 public:
  TActHeroTestUseTryOutReq();
  virtual ~TActHeroTestUseTryOutReq();

  TActHeroTestUseTryOutReq(const TActHeroTestUseTryOutReq& from);

  inline TActHeroTestUseTryOutReq& operator=(const TActHeroTestUseTryOutReq& from) {
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
  static const TActHeroTestUseTryOutReq& default_instance();

  void Swap(TActHeroTestUseTryOutReq* other);

  // implements Message ----------------------------------------------

  TActHeroTestUseTryOutReq* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const TActHeroTestUseTryOutReq& from);
  void MergeFrom(const TActHeroTestUseTryOutReq& from);
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

  // optional uint32 TryOutId = 1;
  inline bool has_tryoutid() const;
  inline void clear_tryoutid();
  static const int kTryOutIdFieldNumber = 1;
  /*FOR2LUA
  <Record>
  	<name>TActHeroTestUseTryOutReq</name>
  	<Function>
  		<name>tryoutid</name>
  		<replaceName>TryOutId</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>set_tryoutid</name>
  		<replaceName>TryOutId</replaceName>
  		<handler>descripter = pb_set_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_tryoutid</name>
  		<replaceName>TryOutId</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline ::google::protobuf::uint32 tryoutid() const;
  inline void set_tryoutid(::google::protobuf::uint32 value);

  // optional uint32 StarLv = 2;
  inline bool has_starlv() const;
  inline void clear_starlv();
  static const int kStarLvFieldNumber = 2;
  /*FOR2LUA
  <Record>
  	<name>TActHeroTestUseTryOutReq</name>
  	<Function>
  		<name>starlv</name>
  		<replaceName>StarLv</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>set_starlv</name>
  		<replaceName>StarLv</replaceName>
  		<handler>descripter = pb_set_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_starlv</name>
  		<replaceName>StarLv</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline ::google::protobuf::uint32 starlv() const;
  inline void set_starlv(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:pb.TActHeroTestUseTryOutReq)
 private:
  inline void set_has_tryoutid();
  inline void clear_has_tryoutid();
  inline void set_has_starlv();
  inline void clear_has_starlv();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::uint32 tryoutid_;
  ::google::protobuf::uint32 starlv_;
  friend void  protobuf_AddDesc_net_2fActHeroTestuse_2eproto();
  friend void protobuf_AssignDesc_net_2fActHeroTestuse_2eproto();
  friend void protobuf_ShutdownFile_net_2fActHeroTestuse_2eproto();

  void InitAsDefaultInstance();
  static TActHeroTestUseTryOutReq* default_instance_;
};
// ===================================================================


// ===================================================================

// TActHeroTestUseGetInfoRsp

// optional uint32 TryOutId = 1;
inline bool TActHeroTestUseGetInfoRsp::has_tryoutid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void TActHeroTestUseGetInfoRsp::set_has_tryoutid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void TActHeroTestUseGetInfoRsp::clear_has_tryoutid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void TActHeroTestUseGetInfoRsp::clear_tryoutid() {
  tryoutid_ = 0u;
  clear_has_tryoutid();
}
inline ::google::protobuf::uint32 TActHeroTestUseGetInfoRsp::tryoutid() const {
  // @@protoc_insertion_point(field_get:pb.TActHeroTestUseGetInfoRsp.TryOutId)
  return tryoutid_;
}
inline void TActHeroTestUseGetInfoRsp::set_tryoutid(::google::protobuf::uint32 value) {
  set_has_tryoutid();
  tryoutid_ = value;
  // @@protoc_insertion_point(field_set:pb.TActHeroTestUseGetInfoRsp.TryOutId)
}

// -------------------------------------------------------------------

// TActHeroTestUseTryOutReq

// optional uint32 TryOutId = 1;
inline bool TActHeroTestUseTryOutReq::has_tryoutid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void TActHeroTestUseTryOutReq::set_has_tryoutid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void TActHeroTestUseTryOutReq::clear_has_tryoutid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void TActHeroTestUseTryOutReq::clear_tryoutid() {
  tryoutid_ = 0u;
  clear_has_tryoutid();
}
inline ::google::protobuf::uint32 TActHeroTestUseTryOutReq::tryoutid() const {
  // @@protoc_insertion_point(field_get:pb.TActHeroTestUseTryOutReq.TryOutId)
  return tryoutid_;
}
inline void TActHeroTestUseTryOutReq::set_tryoutid(::google::protobuf::uint32 value) {
  set_has_tryoutid();
  tryoutid_ = value;
  // @@protoc_insertion_point(field_set:pb.TActHeroTestUseTryOutReq.TryOutId)
}

// optional uint32 StarLv = 2;
inline bool TActHeroTestUseTryOutReq::has_starlv() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void TActHeroTestUseTryOutReq::set_has_starlv() {
  _has_bits_[0] |= 0x00000002u;
}
inline void TActHeroTestUseTryOutReq::clear_has_starlv() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void TActHeroTestUseTryOutReq::clear_starlv() {
  starlv_ = 0u;
  clear_has_starlv();
}
inline ::google::protobuf::uint32 TActHeroTestUseTryOutReq::starlv() const {
  // @@protoc_insertion_point(field_get:pb.TActHeroTestUseTryOutReq.StarLv)
  return starlv_;
}
inline void TActHeroTestUseTryOutReq::set_starlv(::google::protobuf::uint32 value) {
  set_has_starlv();
  starlv_ = value;
  // @@protoc_insertion_point(field_set:pb.TActHeroTestUseTryOutReq.StarLv)
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

#endif  // PROTOBUF_net_2fActHeroTestuse_2eproto__INCLUDED