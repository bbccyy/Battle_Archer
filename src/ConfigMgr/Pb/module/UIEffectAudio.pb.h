// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: module/UIEffectAudio.proto

#ifndef PROTOBUF_module_2fUIEffectAudio_2eproto__INCLUDED
#define PROTOBUF_module_2fUIEffectAudio_2eproto__INCLUDED

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
#include "module/AudioDefine.pb.h"
// @@protoc_insertion_point(includes)

namespace pb {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_module_2fUIEffectAudio_2eproto();
void protobuf_AssignDesc_module_2fUIEffectAudio_2eproto();
void protobuf_ShutdownFile_module_2fUIEffectAudio_2eproto();

class UIEffectAudio;
class UIEffectAudioWithLayer;

// ===================================================================

/*FOR2LUA
<Record>
	<name>UIEffectAudio</name>
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
		<replaceName>module/UIEffectAudio.proto</replaceName>
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
class UIEffectAudio : public ::google::protobuf::Message {
 public:
  UIEffectAudio();
  virtual ~UIEffectAudio();

  UIEffectAudio(const UIEffectAudio& from);

  inline UIEffectAudio& operator=(const UIEffectAudio& from) {
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
  static const UIEffectAudio& default_instance();

  void Swap(UIEffectAudio* other);

  // implements Message ----------------------------------------------

  UIEffectAudio* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const UIEffectAudio& from);
  void MergeFrom(const UIEffectAudio& from);
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

  // optional int32 Id = 1;
  inline bool has_id() const;
  inline void clear_id();
  static const int kIdFieldNumber = 1;
  /*FOR2LUA
  <Record>
  	<name>UIEffectAudio</name>
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
  inline ::google::protobuf::int32 id() const;
  inline void set_id(::google::protobuf::int32 value);

  // optional string LayerName = 2;
  inline bool has_layername() const;
  inline void clear_layername();
  static const int kLayerNameFieldNumber = 2;
  /*FOR2LUA
  <Record>
  	<name>UIEffectAudio</name>
  	<Function>
  		<name>layername</name>
  		<replaceName>LayerName</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>set_layername</name>
  		<replaceName>LayerName</replaceName>
  		<handler>descripter = pb_set_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_layername</name>
  		<replaceName>LayerName</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline const ::std::string& layername() const;
  inline void set_layername(const ::std::string& value);
  inline void set_layername(const char* value);
  inline void set_layername(const char* value, size_t size);
  inline ::std::string* mutable_layername();
  inline ::std::string* release_layername();
  inline void set_allocated_layername(::std::string* layername);

  // repeated .pb.UIEffectAudioWithLayer UIEffectAudioInfoArr = 3;
  inline int uieffectaudioinfoarr_size() const;
  inline void clear_uieffectaudioinfoarr();
  static const int kUIEffectAudioInfoArrFieldNumber = 3;
  /*FOR2LUA
  <Record>
  	<name>UIEffectAudio</name>
  	<Function>
  		<name>uieffectaudioinfoarr</name>
  		<replaceName>UIEffectAudioInfoArr</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>mutable_uieffectaudioinfoarr</name>
  		<replaceName>UIEffectAudioInfoArr</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>add_uieffectaudioinfoarr</name>
  		<replaceName>UIEffectAudioInfoArr</replaceName>
  		<handler>descripter = pb_repeated_add_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_uieffectaudioinfoarr</name>
  		<replaceName>UIEffectAudioInfoArr</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  	<Function>
  		<name>uieffectaudioinfoarr_size</name>
  		<replaceName>UIEffectAudioInfoArr</replaceName>
  		<handler>descripter = pb_repeated_size_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline const ::pb::UIEffectAudioWithLayer& uieffectaudioinfoarr(int index) const;
  inline ::pb::UIEffectAudioWithLayer* mutable_uieffectaudioinfoarr(int index);
  inline ::pb::UIEffectAudioWithLayer* add_uieffectaudioinfoarr();
  inline const ::google::protobuf::RepeatedPtrField< ::pb::UIEffectAudioWithLayer >&
      uieffectaudioinfoarr() const;
  inline ::google::protobuf::RepeatedPtrField< ::pb::UIEffectAudioWithLayer >*
      mutable_uieffectaudioinfoarr();

  // @@protoc_insertion_point(class_scope:pb.UIEffectAudio)
 private:
  inline void set_has_id();
  inline void clear_has_id();
  inline void set_has_layername();
  inline void clear_has_layername();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::std::string* layername_;
  ::google::protobuf::RepeatedPtrField< ::pb::UIEffectAudioWithLayer > uieffectaudioinfoarr_;
  ::google::protobuf::int32 id_;
  friend void  protobuf_AddDesc_module_2fUIEffectAudio_2eproto();
  friend void protobuf_AssignDesc_module_2fUIEffectAudio_2eproto();
  friend void protobuf_ShutdownFile_module_2fUIEffectAudio_2eproto();

  void InitAsDefaultInstance();
  static UIEffectAudio* default_instance_;
};
// -------------------------------------------------------------------

/*FOR2LUA
<Record>
	<name>UIEffectAudioWithLayer</name>
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
		<replaceName>module/UIEffectAudio.proto</replaceName>
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
class UIEffectAudioWithLayer : public ::google::protobuf::Message {
 public:
  UIEffectAudioWithLayer();
  virtual ~UIEffectAudioWithLayer();

  UIEffectAudioWithLayer(const UIEffectAudioWithLayer& from);

  inline UIEffectAudioWithLayer& operator=(const UIEffectAudioWithLayer& from) {
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
  static const UIEffectAudioWithLayer& default_instance();

  void Swap(UIEffectAudioWithLayer* other);

  // implements Message ----------------------------------------------

  UIEffectAudioWithLayer* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const UIEffectAudioWithLayer& from);
  void MergeFrom(const UIEffectAudioWithLayer& from);
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

  // optional string EffectName = 1;
  inline bool has_effectname() const;
  inline void clear_effectname();
  static const int kEffectNameFieldNumber = 1;
  /*FOR2LUA
  <Record>
  	<name>UIEffectAudioWithLayer</name>
  	<Function>
  		<name>effectname</name>
  		<replaceName>EffectName</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>set_effectname</name>
  		<replaceName>EffectName</replaceName>
  		<handler>descripter = pb_set_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_effectname</name>
  		<replaceName>EffectName</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline const ::std::string& effectname() const;
  inline void set_effectname(const ::std::string& value);
  inline void set_effectname(const char* value);
  inline void set_effectname(const char* value, size_t size);
  inline ::std::string* mutable_effectname();
  inline ::std::string* release_effectname();
  inline void set_allocated_effectname(::std::string* effectname);

  // optional .pb.AudioInfo AudioInfo = 2;
  inline bool has_audioinfo() const;
  inline void clear_audioinfo();
  static const int kAudioInfoFieldNumber = 2;
  /*FOR2LUA
  <Record>
  	<name>UIEffectAudioWithLayer</name>
  	<Function>
  		<name>audioinfo</name>
  		<replaceName>AudioInfo</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>set_audioinfo</name>
  		<replaceName>AudioInfo</replaceName>
  		<handler>descripter = pb_set_message_cpp()</handler>
  	</Function>
  	<Function>
  		<name>set_allocated_audioinfo</name>
  		<replaceName>AudioInfo</replaceName>
  		<handler>descripter = pb_set_message_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_audioinfo</name>
  		<replaceName>AudioInfo</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline const ::pb::AudioInfo& audioinfo() const;
  inline ::pb::AudioInfo* mutable_audioinfo();
  inline ::pb::AudioInfo* release_audioinfo();
  inline void set_allocated_audioinfo(::pb::AudioInfo* audioinfo);

  // @@protoc_insertion_point(class_scope:pb.UIEffectAudioWithLayer)
 private:
  inline void set_has_effectname();
  inline void clear_has_effectname();
  inline void set_has_audioinfo();
  inline void clear_has_audioinfo();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::std::string* effectname_;
  ::pb::AudioInfo* audioinfo_;
  friend void  protobuf_AddDesc_module_2fUIEffectAudio_2eproto();
  friend void protobuf_AssignDesc_module_2fUIEffectAudio_2eproto();
  friend void protobuf_ShutdownFile_module_2fUIEffectAudio_2eproto();

  void InitAsDefaultInstance();
  static UIEffectAudioWithLayer* default_instance_;
};
// ===================================================================


// ===================================================================

// UIEffectAudio

// optional int32 Id = 1;
inline bool UIEffectAudio::has_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void UIEffectAudio::set_has_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void UIEffectAudio::clear_has_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void UIEffectAudio::clear_id() {
  id_ = 0;
  clear_has_id();
}
inline ::google::protobuf::int32 UIEffectAudio::id() const {
  // @@protoc_insertion_point(field_get:pb.UIEffectAudio.Id)
  return id_;
}
inline void UIEffectAudio::set_id(::google::protobuf::int32 value) {
  set_has_id();
  id_ = value;
  // @@protoc_insertion_point(field_set:pb.UIEffectAudio.Id)
}

// optional string LayerName = 2;
inline bool UIEffectAudio::has_layername() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void UIEffectAudio::set_has_layername() {
  _has_bits_[0] |= 0x00000002u;
}
inline void UIEffectAudio::clear_has_layername() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void UIEffectAudio::clear_layername() {
  if (layername_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    layername_->clear();
  }
  clear_has_layername();
}
inline const ::std::string& UIEffectAudio::layername() const {
  // @@protoc_insertion_point(field_get:pb.UIEffectAudio.LayerName)
  return *layername_;
}
inline void UIEffectAudio::set_layername(const ::std::string& value) {
  set_has_layername();
  if (layername_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    layername_ = new ::std::string;
  }
  layername_->assign(value);
  // @@protoc_insertion_point(field_set:pb.UIEffectAudio.LayerName)
}
inline void UIEffectAudio::set_layername(const char* value) {
  set_has_layername();
  if (layername_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    layername_ = new ::std::string;
  }
  layername_->assign(value);
  // @@protoc_insertion_point(field_set_char:pb.UIEffectAudio.LayerName)
}
inline void UIEffectAudio::set_layername(const char* value, size_t size) {
  set_has_layername();
  if (layername_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    layername_ = new ::std::string;
  }
  layername_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:pb.UIEffectAudio.LayerName)
}
inline ::std::string* UIEffectAudio::mutable_layername() {
  set_has_layername();
  if (layername_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    layername_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:pb.UIEffectAudio.LayerName)
  return layername_;
}
inline ::std::string* UIEffectAudio::release_layername() {
  clear_has_layername();
  if (layername_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = layername_;
    layername_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void UIEffectAudio::set_allocated_layername(::std::string* layername) {
  if (layername_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete layername_;
  }
  if (layername) {
    set_has_layername();
    layername_ = layername;
  } else {
    clear_has_layername();
    layername_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:pb.UIEffectAudio.LayerName)
}

// repeated .pb.UIEffectAudioWithLayer UIEffectAudioInfoArr = 3;
inline int UIEffectAudio::uieffectaudioinfoarr_size() const {
  return uieffectaudioinfoarr_.size();
}
inline void UIEffectAudio::clear_uieffectaudioinfoarr() {
  uieffectaudioinfoarr_.Clear();
}
inline const ::pb::UIEffectAudioWithLayer& UIEffectAudio::uieffectaudioinfoarr(int index) const {
  // @@protoc_insertion_point(field_get:pb.UIEffectAudio.UIEffectAudioInfoArr)
  return uieffectaudioinfoarr_.Get(index);
}
inline ::pb::UIEffectAudioWithLayer* UIEffectAudio::mutable_uieffectaudioinfoarr(int index) {
  // @@protoc_insertion_point(field_mutable:pb.UIEffectAudio.UIEffectAudioInfoArr)
  return uieffectaudioinfoarr_.Mutable(index);
}
inline ::pb::UIEffectAudioWithLayer* UIEffectAudio::add_uieffectaudioinfoarr() {
  // @@protoc_insertion_point(field_add:pb.UIEffectAudio.UIEffectAudioInfoArr)
  return uieffectaudioinfoarr_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::pb::UIEffectAudioWithLayer >&
UIEffectAudio::uieffectaudioinfoarr() const {
  // @@protoc_insertion_point(field_list:pb.UIEffectAudio.UIEffectAudioInfoArr)
  return uieffectaudioinfoarr_;
}
inline ::google::protobuf::RepeatedPtrField< ::pb::UIEffectAudioWithLayer >*
UIEffectAudio::mutable_uieffectaudioinfoarr() {
  // @@protoc_insertion_point(field_mutable_list:pb.UIEffectAudio.UIEffectAudioInfoArr)
  return &uieffectaudioinfoarr_;
}

// -------------------------------------------------------------------

// UIEffectAudioWithLayer

// optional string EffectName = 1;
inline bool UIEffectAudioWithLayer::has_effectname() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void UIEffectAudioWithLayer::set_has_effectname() {
  _has_bits_[0] |= 0x00000001u;
}
inline void UIEffectAudioWithLayer::clear_has_effectname() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void UIEffectAudioWithLayer::clear_effectname() {
  if (effectname_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    effectname_->clear();
  }
  clear_has_effectname();
}
inline const ::std::string& UIEffectAudioWithLayer::effectname() const {
  // @@protoc_insertion_point(field_get:pb.UIEffectAudioWithLayer.EffectName)
  return *effectname_;
}
inline void UIEffectAudioWithLayer::set_effectname(const ::std::string& value) {
  set_has_effectname();
  if (effectname_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    effectname_ = new ::std::string;
  }
  effectname_->assign(value);
  // @@protoc_insertion_point(field_set:pb.UIEffectAudioWithLayer.EffectName)
}
inline void UIEffectAudioWithLayer::set_effectname(const char* value) {
  set_has_effectname();
  if (effectname_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    effectname_ = new ::std::string;
  }
  effectname_->assign(value);
  // @@protoc_insertion_point(field_set_char:pb.UIEffectAudioWithLayer.EffectName)
}
inline void UIEffectAudioWithLayer::set_effectname(const char* value, size_t size) {
  set_has_effectname();
  if (effectname_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    effectname_ = new ::std::string;
  }
  effectname_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:pb.UIEffectAudioWithLayer.EffectName)
}
inline ::std::string* UIEffectAudioWithLayer::mutable_effectname() {
  set_has_effectname();
  if (effectname_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    effectname_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:pb.UIEffectAudioWithLayer.EffectName)
  return effectname_;
}
inline ::std::string* UIEffectAudioWithLayer::release_effectname() {
  clear_has_effectname();
  if (effectname_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = effectname_;
    effectname_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void UIEffectAudioWithLayer::set_allocated_effectname(::std::string* effectname) {
  if (effectname_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete effectname_;
  }
  if (effectname) {
    set_has_effectname();
    effectname_ = effectname;
  } else {
    clear_has_effectname();
    effectname_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:pb.UIEffectAudioWithLayer.EffectName)
}

// optional .pb.AudioInfo AudioInfo = 2;
inline bool UIEffectAudioWithLayer::has_audioinfo() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void UIEffectAudioWithLayer::set_has_audioinfo() {
  _has_bits_[0] |= 0x00000002u;
}
inline void UIEffectAudioWithLayer::clear_has_audioinfo() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void UIEffectAudioWithLayer::clear_audioinfo() {
  if (audioinfo_ != NULL) audioinfo_->::pb::AudioInfo::Clear();
  clear_has_audioinfo();
}
inline const ::pb::AudioInfo& UIEffectAudioWithLayer::audioinfo() const {
  // @@protoc_insertion_point(field_get:pb.UIEffectAudioWithLayer.AudioInfo)
  return audioinfo_ != NULL ? *audioinfo_ : *default_instance_->audioinfo_;
}
inline ::pb::AudioInfo* UIEffectAudioWithLayer::mutable_audioinfo() {
  set_has_audioinfo();
  if (audioinfo_ == NULL) audioinfo_ = new ::pb::AudioInfo;
  // @@protoc_insertion_point(field_mutable:pb.UIEffectAudioWithLayer.AudioInfo)
  return audioinfo_;
}
inline ::pb::AudioInfo* UIEffectAudioWithLayer::release_audioinfo() {
  clear_has_audioinfo();
  ::pb::AudioInfo* temp = audioinfo_;
  audioinfo_ = NULL;
  return temp;
}
inline void UIEffectAudioWithLayer::set_allocated_audioinfo(::pb::AudioInfo* audioinfo) {
  delete audioinfo_;
  audioinfo_ = audioinfo;
  if (audioinfo) {
    set_has_audioinfo();
  } else {
    clear_has_audioinfo();
  }
  // @@protoc_insertion_point(field_set_allocated:pb.UIEffectAudioWithLayer.AudioInfo)
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

#endif  // PROTOBUF_module_2fUIEffectAudio_2eproto__INCLUDED
