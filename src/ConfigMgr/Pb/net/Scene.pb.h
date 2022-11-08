// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: net/Scene.proto

#ifndef PROTOBUF_net_2fScene_2eproto__INCLUDED
#define PROTOBUF_net_2fScene_2eproto__INCLUDED

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
void  protobuf_AddDesc_net_2fScene_2eproto();
void protobuf_AssignDesc_net_2fScene_2eproto();
void protobuf_ShutdownFile_net_2fScene_2eproto();

class TSceneGetSceneIdByTypeReq;
class TSceneGetSceneIdByTypeRsp;

// ===================================================================

/*FOR2LUA
<Record>
	<name>TSceneGetSceneIdByTypeReq</name>
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
		<replaceName>net/Scene.proto</replaceName>
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
class TSceneGetSceneIdByTypeReq : public ::google::protobuf::Message {
 public:
  TSceneGetSceneIdByTypeReq();
  virtual ~TSceneGetSceneIdByTypeReq();

  TSceneGetSceneIdByTypeReq(const TSceneGetSceneIdByTypeReq& from);

  inline TSceneGetSceneIdByTypeReq& operator=(const TSceneGetSceneIdByTypeReq& from) {
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
  static const TSceneGetSceneIdByTypeReq& default_instance();

  void Swap(TSceneGetSceneIdByTypeReq* other);

  // implements Message ----------------------------------------------

  TSceneGetSceneIdByTypeReq* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const TSceneGetSceneIdByTypeReq& from);
  void MergeFrom(const TSceneGetSceneIdByTypeReq& from);
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

  // optional string SceneType = 1;
  inline bool has_scenetype() const;
  inline void clear_scenetype();
  static const int kSceneTypeFieldNumber = 1;
  /*FOR2LUA
  <Record>
  	<name>TSceneGetSceneIdByTypeReq</name>
  	<Function>
  		<name>scenetype</name>
  		<replaceName>SceneType</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>set_scenetype</name>
  		<replaceName>SceneType</replaceName>
  		<handler>descripter = pb_set_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_scenetype</name>
  		<replaceName>SceneType</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline const ::std::string& scenetype() const;
  inline void set_scenetype(const ::std::string& value);
  inline void set_scenetype(const char* value);
  inline void set_scenetype(const char* value, size_t size);
  inline ::std::string* mutable_scenetype();
  inline ::std::string* release_scenetype();
  inline void set_allocated_scenetype(::std::string* scenetype);

  // @@protoc_insertion_point(class_scope:pb.TSceneGetSceneIdByTypeReq)
 private:
  inline void set_has_scenetype();
  inline void clear_has_scenetype();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::std::string* scenetype_;
  friend void  protobuf_AddDesc_net_2fScene_2eproto();
  friend void protobuf_AssignDesc_net_2fScene_2eproto();
  friend void protobuf_ShutdownFile_net_2fScene_2eproto();

  void InitAsDefaultInstance();
  static TSceneGetSceneIdByTypeReq* default_instance_;
};
// -------------------------------------------------------------------

/*FOR2LUA
<Record>
	<name>TSceneGetSceneIdByTypeRsp</name>
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
		<replaceName>net/Scene.proto</replaceName>
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
class TSceneGetSceneIdByTypeRsp : public ::google::protobuf::Message {
 public:
  TSceneGetSceneIdByTypeRsp();
  virtual ~TSceneGetSceneIdByTypeRsp();

  TSceneGetSceneIdByTypeRsp(const TSceneGetSceneIdByTypeRsp& from);

  inline TSceneGetSceneIdByTypeRsp& operator=(const TSceneGetSceneIdByTypeRsp& from) {
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
  static const TSceneGetSceneIdByTypeRsp& default_instance();

  void Swap(TSceneGetSceneIdByTypeRsp* other);

  // implements Message ----------------------------------------------

  TSceneGetSceneIdByTypeRsp* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const TSceneGetSceneIdByTypeRsp& from);
  void MergeFrom(const TSceneGetSceneIdByTypeRsp& from);
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

  // optional string SceneId = 1;
  inline bool has_sceneid() const;
  inline void clear_sceneid();
  static const int kSceneIdFieldNumber = 1;
  /*FOR2LUA
  <Record>
  	<name>TSceneGetSceneIdByTypeRsp</name>
  	<Function>
  		<name>sceneid</name>
  		<replaceName>SceneId</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>set_sceneid</name>
  		<replaceName>SceneId</replaceName>
  		<handler>descripter = pb_set_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_sceneid</name>
  		<replaceName>SceneId</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline const ::std::string& sceneid() const;
  inline void set_sceneid(const ::std::string& value);
  inline void set_sceneid(const char* value);
  inline void set_sceneid(const char* value, size_t size);
  inline ::std::string* mutable_sceneid();
  inline ::std::string* release_sceneid();
  inline void set_allocated_sceneid(::std::string* sceneid);

  // @@protoc_insertion_point(class_scope:pb.TSceneGetSceneIdByTypeRsp)
 private:
  inline void set_has_sceneid();
  inline void clear_has_sceneid();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::std::string* sceneid_;
  friend void  protobuf_AddDesc_net_2fScene_2eproto();
  friend void protobuf_AssignDesc_net_2fScene_2eproto();
  friend void protobuf_ShutdownFile_net_2fScene_2eproto();

  void InitAsDefaultInstance();
  static TSceneGetSceneIdByTypeRsp* default_instance_;
};
// ===================================================================


// ===================================================================

// TSceneGetSceneIdByTypeReq

// optional string SceneType = 1;
inline bool TSceneGetSceneIdByTypeReq::has_scenetype() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void TSceneGetSceneIdByTypeReq::set_has_scenetype() {
  _has_bits_[0] |= 0x00000001u;
}
inline void TSceneGetSceneIdByTypeReq::clear_has_scenetype() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void TSceneGetSceneIdByTypeReq::clear_scenetype() {
  if (scenetype_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    scenetype_->clear();
  }
  clear_has_scenetype();
}
inline const ::std::string& TSceneGetSceneIdByTypeReq::scenetype() const {
  // @@protoc_insertion_point(field_get:pb.TSceneGetSceneIdByTypeReq.SceneType)
  return *scenetype_;
}
inline void TSceneGetSceneIdByTypeReq::set_scenetype(const ::std::string& value) {
  set_has_scenetype();
  if (scenetype_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    scenetype_ = new ::std::string;
  }
  scenetype_->assign(value);
  // @@protoc_insertion_point(field_set:pb.TSceneGetSceneIdByTypeReq.SceneType)
}
inline void TSceneGetSceneIdByTypeReq::set_scenetype(const char* value) {
  set_has_scenetype();
  if (scenetype_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    scenetype_ = new ::std::string;
  }
  scenetype_->assign(value);
  // @@protoc_insertion_point(field_set_char:pb.TSceneGetSceneIdByTypeReq.SceneType)
}
inline void TSceneGetSceneIdByTypeReq::set_scenetype(const char* value, size_t size) {
  set_has_scenetype();
  if (scenetype_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    scenetype_ = new ::std::string;
  }
  scenetype_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:pb.TSceneGetSceneIdByTypeReq.SceneType)
}
inline ::std::string* TSceneGetSceneIdByTypeReq::mutable_scenetype() {
  set_has_scenetype();
  if (scenetype_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    scenetype_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:pb.TSceneGetSceneIdByTypeReq.SceneType)
  return scenetype_;
}
inline ::std::string* TSceneGetSceneIdByTypeReq::release_scenetype() {
  clear_has_scenetype();
  if (scenetype_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = scenetype_;
    scenetype_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void TSceneGetSceneIdByTypeReq::set_allocated_scenetype(::std::string* scenetype) {
  if (scenetype_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete scenetype_;
  }
  if (scenetype) {
    set_has_scenetype();
    scenetype_ = scenetype;
  } else {
    clear_has_scenetype();
    scenetype_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:pb.TSceneGetSceneIdByTypeReq.SceneType)
}

// -------------------------------------------------------------------

// TSceneGetSceneIdByTypeRsp

// optional string SceneId = 1;
inline bool TSceneGetSceneIdByTypeRsp::has_sceneid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void TSceneGetSceneIdByTypeRsp::set_has_sceneid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void TSceneGetSceneIdByTypeRsp::clear_has_sceneid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void TSceneGetSceneIdByTypeRsp::clear_sceneid() {
  if (sceneid_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    sceneid_->clear();
  }
  clear_has_sceneid();
}
inline const ::std::string& TSceneGetSceneIdByTypeRsp::sceneid() const {
  // @@protoc_insertion_point(field_get:pb.TSceneGetSceneIdByTypeRsp.SceneId)
  return *sceneid_;
}
inline void TSceneGetSceneIdByTypeRsp::set_sceneid(const ::std::string& value) {
  set_has_sceneid();
  if (sceneid_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    sceneid_ = new ::std::string;
  }
  sceneid_->assign(value);
  // @@protoc_insertion_point(field_set:pb.TSceneGetSceneIdByTypeRsp.SceneId)
}
inline void TSceneGetSceneIdByTypeRsp::set_sceneid(const char* value) {
  set_has_sceneid();
  if (sceneid_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    sceneid_ = new ::std::string;
  }
  sceneid_->assign(value);
  // @@protoc_insertion_point(field_set_char:pb.TSceneGetSceneIdByTypeRsp.SceneId)
}
inline void TSceneGetSceneIdByTypeRsp::set_sceneid(const char* value, size_t size) {
  set_has_sceneid();
  if (sceneid_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    sceneid_ = new ::std::string;
  }
  sceneid_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:pb.TSceneGetSceneIdByTypeRsp.SceneId)
}
inline ::std::string* TSceneGetSceneIdByTypeRsp::mutable_sceneid() {
  set_has_sceneid();
  if (sceneid_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    sceneid_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:pb.TSceneGetSceneIdByTypeRsp.SceneId)
  return sceneid_;
}
inline ::std::string* TSceneGetSceneIdByTypeRsp::release_sceneid() {
  clear_has_sceneid();
  if (sceneid_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = sceneid_;
    sceneid_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void TSceneGetSceneIdByTypeRsp::set_allocated_sceneid(::std::string* sceneid) {
  if (sceneid_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete sceneid_;
  }
  if (sceneid) {
    set_has_sceneid();
    sceneid_ = sceneid;
  } else {
    clear_has_sceneid();
    sceneid_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:pb.TSceneGetSceneIdByTypeRsp.SceneId)
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

#endif  // PROTOBUF_net_2fScene_2eproto__INCLUDED
