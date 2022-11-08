// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: net/Web.proto

#ifndef PROTOBUF_net_2fWeb_2eproto__INCLUDED
#define PROTOBUF_net_2fWeb_2eproto__INCLUDED

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
void  protobuf_AddDesc_net_2fWeb_2eproto();
void protobuf_AssignDesc_net_2fWeb_2eproto();
void protobuf_ShutdownFile_net_2fWeb_2eproto();

class TWebReq;
class TWebRsp;

// ===================================================================

/*FOR2LUA
<Record>
	<name>TWebReq</name>
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
		<replaceName>net/Web.proto</replaceName>
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
class TWebReq : public ::google::protobuf::Message {
 public:
  TWebReq();
  virtual ~TWebReq();

  TWebReq(const TWebReq& from);

  inline TWebReq& operator=(const TWebReq& from) {
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
  static const TWebReq& default_instance();

  void Swap(TWebReq* other);

  // implements Message ----------------------------------------------

  TWebReq* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const TWebReq& from);
  void MergeFrom(const TWebReq& from);
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

  // optional string JsonArgs = 1;
  inline bool has_jsonargs() const;
  inline void clear_jsonargs();
  static const int kJsonArgsFieldNumber = 1;
  /*FOR2LUA
  <Record>
  	<name>TWebReq</name>
  	<Function>
  		<name>jsonargs</name>
  		<replaceName>JsonArgs</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>set_jsonargs</name>
  		<replaceName>JsonArgs</replaceName>
  		<handler>descripter = pb_set_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_jsonargs</name>
  		<replaceName>JsonArgs</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline const ::std::string& jsonargs() const;
  inline void set_jsonargs(const ::std::string& value);
  inline void set_jsonargs(const char* value);
  inline void set_jsonargs(const char* value, size_t size);
  inline ::std::string* mutable_jsonargs();
  inline ::std::string* release_jsonargs();
  inline void set_allocated_jsonargs(::std::string* jsonargs);

  // @@protoc_insertion_point(class_scope:pb.TWebReq)
 private:
  inline void set_has_jsonargs();
  inline void clear_has_jsonargs();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::std::string* jsonargs_;
  friend void  protobuf_AddDesc_net_2fWeb_2eproto();
  friend void protobuf_AssignDesc_net_2fWeb_2eproto();
  friend void protobuf_ShutdownFile_net_2fWeb_2eproto();

  void InitAsDefaultInstance();
  static TWebReq* default_instance_;
};
// -------------------------------------------------------------------

/*FOR2LUA
<Record>
	<name>TWebRsp</name>
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
		<replaceName>net/Web.proto</replaceName>
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
class TWebRsp : public ::google::protobuf::Message {
 public:
  TWebRsp();
  virtual ~TWebRsp();

  TWebRsp(const TWebRsp& from);

  inline TWebRsp& operator=(const TWebRsp& from) {
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
  static const TWebRsp& default_instance();

  void Swap(TWebRsp* other);

  // implements Message ----------------------------------------------

  TWebRsp* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const TWebRsp& from);
  void MergeFrom(const TWebRsp& from);
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

  // optional string JsonMsg = 1;
  inline bool has_jsonmsg() const;
  inline void clear_jsonmsg();
  static const int kJsonMsgFieldNumber = 1;
  /*FOR2LUA
  <Record>
  	<name>TWebRsp</name>
  	<Function>
  		<name>jsonmsg</name>
  		<replaceName>JsonMsg</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>set_jsonmsg</name>
  		<replaceName>JsonMsg</replaceName>
  		<handler>descripter = pb_set_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_jsonmsg</name>
  		<replaceName>JsonMsg</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline const ::std::string& jsonmsg() const;
  inline void set_jsonmsg(const ::std::string& value);
  inline void set_jsonmsg(const char* value);
  inline void set_jsonmsg(const char* value, size_t size);
  inline ::std::string* mutable_jsonmsg();
  inline ::std::string* release_jsonmsg();
  inline void set_allocated_jsonmsg(::std::string* jsonmsg);

  // @@protoc_insertion_point(class_scope:pb.TWebRsp)
 private:
  inline void set_has_jsonmsg();
  inline void clear_has_jsonmsg();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::std::string* jsonmsg_;
  friend void  protobuf_AddDesc_net_2fWeb_2eproto();
  friend void protobuf_AssignDesc_net_2fWeb_2eproto();
  friend void protobuf_ShutdownFile_net_2fWeb_2eproto();

  void InitAsDefaultInstance();
  static TWebRsp* default_instance_;
};
// ===================================================================


// ===================================================================

// TWebReq

// optional string JsonArgs = 1;
inline bool TWebReq::has_jsonargs() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void TWebReq::set_has_jsonargs() {
  _has_bits_[0] |= 0x00000001u;
}
inline void TWebReq::clear_has_jsonargs() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void TWebReq::clear_jsonargs() {
  if (jsonargs_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    jsonargs_->clear();
  }
  clear_has_jsonargs();
}
inline const ::std::string& TWebReq::jsonargs() const {
  // @@protoc_insertion_point(field_get:pb.TWebReq.JsonArgs)
  return *jsonargs_;
}
inline void TWebReq::set_jsonargs(const ::std::string& value) {
  set_has_jsonargs();
  if (jsonargs_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    jsonargs_ = new ::std::string;
  }
  jsonargs_->assign(value);
  // @@protoc_insertion_point(field_set:pb.TWebReq.JsonArgs)
}
inline void TWebReq::set_jsonargs(const char* value) {
  set_has_jsonargs();
  if (jsonargs_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    jsonargs_ = new ::std::string;
  }
  jsonargs_->assign(value);
  // @@protoc_insertion_point(field_set_char:pb.TWebReq.JsonArgs)
}
inline void TWebReq::set_jsonargs(const char* value, size_t size) {
  set_has_jsonargs();
  if (jsonargs_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    jsonargs_ = new ::std::string;
  }
  jsonargs_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:pb.TWebReq.JsonArgs)
}
inline ::std::string* TWebReq::mutable_jsonargs() {
  set_has_jsonargs();
  if (jsonargs_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    jsonargs_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:pb.TWebReq.JsonArgs)
  return jsonargs_;
}
inline ::std::string* TWebReq::release_jsonargs() {
  clear_has_jsonargs();
  if (jsonargs_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = jsonargs_;
    jsonargs_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void TWebReq::set_allocated_jsonargs(::std::string* jsonargs) {
  if (jsonargs_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete jsonargs_;
  }
  if (jsonargs) {
    set_has_jsonargs();
    jsonargs_ = jsonargs;
  } else {
    clear_has_jsonargs();
    jsonargs_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:pb.TWebReq.JsonArgs)
}

// -------------------------------------------------------------------

// TWebRsp

// optional string JsonMsg = 1;
inline bool TWebRsp::has_jsonmsg() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void TWebRsp::set_has_jsonmsg() {
  _has_bits_[0] |= 0x00000001u;
}
inline void TWebRsp::clear_has_jsonmsg() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void TWebRsp::clear_jsonmsg() {
  if (jsonmsg_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    jsonmsg_->clear();
  }
  clear_has_jsonmsg();
}
inline const ::std::string& TWebRsp::jsonmsg() const {
  // @@protoc_insertion_point(field_get:pb.TWebRsp.JsonMsg)
  return *jsonmsg_;
}
inline void TWebRsp::set_jsonmsg(const ::std::string& value) {
  set_has_jsonmsg();
  if (jsonmsg_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    jsonmsg_ = new ::std::string;
  }
  jsonmsg_->assign(value);
  // @@protoc_insertion_point(field_set:pb.TWebRsp.JsonMsg)
}
inline void TWebRsp::set_jsonmsg(const char* value) {
  set_has_jsonmsg();
  if (jsonmsg_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    jsonmsg_ = new ::std::string;
  }
  jsonmsg_->assign(value);
  // @@protoc_insertion_point(field_set_char:pb.TWebRsp.JsonMsg)
}
inline void TWebRsp::set_jsonmsg(const char* value, size_t size) {
  set_has_jsonmsg();
  if (jsonmsg_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    jsonmsg_ = new ::std::string;
  }
  jsonmsg_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:pb.TWebRsp.JsonMsg)
}
inline ::std::string* TWebRsp::mutable_jsonmsg() {
  set_has_jsonmsg();
  if (jsonmsg_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    jsonmsg_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:pb.TWebRsp.JsonMsg)
  return jsonmsg_;
}
inline ::std::string* TWebRsp::release_jsonmsg() {
  clear_has_jsonmsg();
  if (jsonmsg_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = jsonmsg_;
    jsonmsg_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void TWebRsp::set_allocated_jsonmsg(::std::string* jsonmsg) {
  if (jsonmsg_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete jsonmsg_;
  }
  if (jsonmsg) {
    set_has_jsonmsg();
    jsonmsg_ = jsonmsg;
  } else {
    clear_has_jsonmsg();
    jsonmsg_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:pb.TWebRsp.JsonMsg)
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

#endif  // PROTOBUF_net_2fWeb_2eproto__INCLUDED
