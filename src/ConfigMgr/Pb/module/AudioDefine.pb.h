// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: module/AudioDefine.proto

#ifndef PROTOBUF_module_2fAudioDefine_2eproto__INCLUDED
#define PROTOBUF_module_2fAudioDefine_2eproto__INCLUDED

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
void  protobuf_AddDesc_module_2fAudioDefine_2eproto();
void protobuf_AssignDesc_module_2fAudioDefine_2eproto();
void protobuf_ShutdownFile_module_2fAudioDefine_2eproto();

class AudioInfo;
class AnimationStateAudio;
class AudioDefine;

// ===================================================================

/*FOR2LUA
<Record>
	<name>AudioInfo</name>
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
		<replaceName>module/AudioDefine.proto</replaceName>
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
class AudioInfo : public ::google::protobuf::Message {
 public:
  AudioInfo();
  virtual ~AudioInfo();

  AudioInfo(const AudioInfo& from);

  inline AudioInfo& operator=(const AudioInfo& from) {
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
  static const AudioInfo& default_instance();

  void Swap(AudioInfo* other);

  // implements Message ----------------------------------------------

  AudioInfo* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const AudioInfo& from);
  void MergeFrom(const AudioInfo& from);
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

  // optional float StartTime = 1;
  inline bool has_starttime() const;
  inline void clear_starttime();
  static const int kStartTimeFieldNumber = 1;
  /*FOR2LUA
  <Record>
  	<name>AudioInfo</name>
  	<Function>
  		<name>starttime</name>
  		<replaceName>StartTime</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>set_starttime</name>
  		<replaceName>StartTime</replaceName>
  		<handler>descripter = pb_set_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_starttime</name>
  		<replaceName>StartTime</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline float starttime() const;
  inline void set_starttime(float value);

  // optional string AudioEventName = 2;
  inline bool has_audioeventname() const;
  inline void clear_audioeventname();
  static const int kAudioEventNameFieldNumber = 2;
  /*FOR2LUA
  <Record>
  	<name>AudioInfo</name>
  	<Function>
  		<name>audioeventname</name>
  		<replaceName>AudioEventName</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>set_audioeventname</name>
  		<replaceName>AudioEventName</replaceName>
  		<handler>descripter = pb_set_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_audioeventname</name>
  		<replaceName>AudioEventName</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline const ::std::string& audioeventname() const;
  inline void set_audioeventname(const ::std::string& value);
  inline void set_audioeventname(const char* value);
  inline void set_audioeventname(const char* value, size_t size);
  inline ::std::string* mutable_audioeventname();
  inline ::std::string* release_audioeventname();
  inline void set_allocated_audioeventname(::std::string* audioeventname);

  // repeated .pb.AnimationStateAudio AnimaAudioInfo = 3;
  inline int animaaudioinfo_size() const;
  inline void clear_animaaudioinfo();
  static const int kAnimaAudioInfoFieldNumber = 3;
  /*FOR2LUA
  <Record>
  	<name>AudioInfo</name>
  	<Function>
  		<name>animaaudioinfo</name>
  		<replaceName>AnimaAudioInfo</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>mutable_animaaudioinfo</name>
  		<replaceName>AnimaAudioInfo</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>add_animaaudioinfo</name>
  		<replaceName>AnimaAudioInfo</replaceName>
  		<handler>descripter = pb_repeated_add_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_animaaudioinfo</name>
  		<replaceName>AnimaAudioInfo</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  	<Function>
  		<name>animaaudioinfo_size</name>
  		<replaceName>AnimaAudioInfo</replaceName>
  		<handler>descripter = pb_repeated_size_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline const ::pb::AnimationStateAudio& animaaudioinfo(int index) const;
  inline ::pb::AnimationStateAudio* mutable_animaaudioinfo(int index);
  inline ::pb::AnimationStateAudio* add_animaaudioinfo();
  inline const ::google::protobuf::RepeatedPtrField< ::pb::AnimationStateAudio >&
      animaaudioinfo() const;
  inline ::google::protobuf::RepeatedPtrField< ::pb::AnimationStateAudio >*
      mutable_animaaudioinfo();

  // @@protoc_insertion_point(class_scope:pb.AudioInfo)
 private:
  inline void set_has_starttime();
  inline void clear_has_starttime();
  inline void set_has_audioeventname();
  inline void clear_has_audioeventname();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::std::string* audioeventname_;
  ::google::protobuf::RepeatedPtrField< ::pb::AnimationStateAudio > animaaudioinfo_;
  float starttime_;
  friend void  protobuf_AddDesc_module_2fAudioDefine_2eproto();
  friend void protobuf_AssignDesc_module_2fAudioDefine_2eproto();
  friend void protobuf_ShutdownFile_module_2fAudioDefine_2eproto();

  void InitAsDefaultInstance();
  static AudioInfo* default_instance_;
};
// -------------------------------------------------------------------

/*FOR2LUA
<Record>
	<name>AnimationStateAudio</name>
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
		<replaceName>module/AudioDefine.proto</replaceName>
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
class AnimationStateAudio : public ::google::protobuf::Message {
 public:
  AnimationStateAudio();
  virtual ~AnimationStateAudio();

  AnimationStateAudio(const AnimationStateAudio& from);

  inline AnimationStateAudio& operator=(const AnimationStateAudio& from) {
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
  static const AnimationStateAudio& default_instance();

  void Swap(AnimationStateAudio* other);

  // implements Message ----------------------------------------------

  AnimationStateAudio* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const AnimationStateAudio& from);
  void MergeFrom(const AnimationStateAudio& from);
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

  // optional float StartTime = 1;
  inline bool has_starttime() const;
  inline void clear_starttime();
  static const int kStartTimeFieldNumber = 1;
  /*FOR2LUA
  <Record>
  	<name>AnimationStateAudio</name>
  	<Function>
  		<name>starttime</name>
  		<replaceName>StartTime</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>set_starttime</name>
  		<replaceName>StartTime</replaceName>
  		<handler>descripter = pb_set_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_starttime</name>
  		<replaceName>StartTime</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline float starttime() const;
  inline void set_starttime(float value);

  // optional string AudioEventName = 2;
  inline bool has_audioeventname() const;
  inline void clear_audioeventname();
  static const int kAudioEventNameFieldNumber = 2;
  /*FOR2LUA
  <Record>
  	<name>AnimationStateAudio</name>
  	<Function>
  		<name>audioeventname</name>
  		<replaceName>AudioEventName</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>set_audioeventname</name>
  		<replaceName>AudioEventName</replaceName>
  		<handler>descripter = pb_set_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_audioeventname</name>
  		<replaceName>AudioEventName</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline const ::std::string& audioeventname() const;
  inline void set_audioeventname(const ::std::string& value);
  inline void set_audioeventname(const char* value);
  inline void set_audioeventname(const char* value, size_t size);
  inline ::std::string* mutable_audioeventname();
  inline ::std::string* release_audioeventname();
  inline void set_allocated_audioeventname(::std::string* audioeventname);

  // optional string AnimaStateName = 3;
  inline bool has_animastatename() const;
  inline void clear_animastatename();
  static const int kAnimaStateNameFieldNumber = 3;
  /*FOR2LUA
  <Record>
  	<name>AnimationStateAudio</name>
  	<Function>
  		<name>animastatename</name>
  		<replaceName>AnimaStateName</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>set_animastatename</name>
  		<replaceName>AnimaStateName</replaceName>
  		<handler>descripter = pb_set_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_animastatename</name>
  		<replaceName>AnimaStateName</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline const ::std::string& animastatename() const;
  inline void set_animastatename(const ::std::string& value);
  inline void set_animastatename(const char* value);
  inline void set_animastatename(const char* value, size_t size);
  inline ::std::string* mutable_animastatename();
  inline ::std::string* release_animastatename();
  inline void set_allocated_animastatename(::std::string* animastatename);

  // optional string AnimaTransName = 4;
  inline bool has_animatransname() const;
  inline void clear_animatransname();
  static const int kAnimaTransNameFieldNumber = 4;
  /*FOR2LUA
  <Record>
  	<name>AnimationStateAudio</name>
  	<Function>
  		<name>animatransname</name>
  		<replaceName>AnimaTransName</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>set_animatransname</name>
  		<replaceName>AnimaTransName</replaceName>
  		<handler>descripter = pb_set_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_animatransname</name>
  		<replaceName>AnimaTransName</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline const ::std::string& animatransname() const;
  inline void set_animatransname(const ::std::string& value);
  inline void set_animatransname(const char* value);
  inline void set_animatransname(const char* value, size_t size);
  inline ::std::string* mutable_animatransname();
  inline ::std::string* release_animatransname();
  inline void set_allocated_animatransname(::std::string* animatransname);

  // @@protoc_insertion_point(class_scope:pb.AnimationStateAudio)
 private:
  inline void set_has_starttime();
  inline void clear_has_starttime();
  inline void set_has_audioeventname();
  inline void clear_has_audioeventname();
  inline void set_has_animastatename();
  inline void clear_has_animastatename();
  inline void set_has_animatransname();
  inline void clear_has_animatransname();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::std::string* audioeventname_;
  ::std::string* animastatename_;
  ::std::string* animatransname_;
  float starttime_;
  friend void  protobuf_AddDesc_module_2fAudioDefine_2eproto();
  friend void protobuf_AssignDesc_module_2fAudioDefine_2eproto();
  friend void protobuf_ShutdownFile_module_2fAudioDefine_2eproto();

  void InitAsDefaultInstance();
  static AnimationStateAudio* default_instance_;
};
// -------------------------------------------------------------------

/*FOR2LUA
<Record>
	<name>AudioDefine</name>
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
		<replaceName>module/AudioDefine.proto</replaceName>
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
class AudioDefine : public ::google::protobuf::Message {
 public:
  AudioDefine();
  virtual ~AudioDefine();

  AudioDefine(const AudioDefine& from);

  inline AudioDefine& operator=(const AudioDefine& from) {
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
  static const AudioDefine& default_instance();

  void Swap(AudioDefine* other);

  // implements Message ----------------------------------------------

  AudioDefine* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const AudioDefine& from);
  void MergeFrom(const AudioDefine& from);
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

  // @@protoc_insertion_point(class_scope:pb.AudioDefine)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  friend void  protobuf_AddDesc_module_2fAudioDefine_2eproto();
  friend void protobuf_AssignDesc_module_2fAudioDefine_2eproto();
  friend void protobuf_ShutdownFile_module_2fAudioDefine_2eproto();

  void InitAsDefaultInstance();
  static AudioDefine* default_instance_;
};
// ===================================================================


// ===================================================================

// AudioInfo

// optional float StartTime = 1;
inline bool AudioInfo::has_starttime() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void AudioInfo::set_has_starttime() {
  _has_bits_[0] |= 0x00000001u;
}
inline void AudioInfo::clear_has_starttime() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void AudioInfo::clear_starttime() {
  starttime_ = 0;
  clear_has_starttime();
}
inline float AudioInfo::starttime() const {
  // @@protoc_insertion_point(field_get:pb.AudioInfo.StartTime)
  return starttime_;
}
inline void AudioInfo::set_starttime(float value) {
  set_has_starttime();
  starttime_ = value;
  // @@protoc_insertion_point(field_set:pb.AudioInfo.StartTime)
}

// optional string AudioEventName = 2;
inline bool AudioInfo::has_audioeventname() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void AudioInfo::set_has_audioeventname() {
  _has_bits_[0] |= 0x00000002u;
}
inline void AudioInfo::clear_has_audioeventname() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void AudioInfo::clear_audioeventname() {
  if (audioeventname_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    audioeventname_->clear();
  }
  clear_has_audioeventname();
}
inline const ::std::string& AudioInfo::audioeventname() const {
  // @@protoc_insertion_point(field_get:pb.AudioInfo.AudioEventName)
  return *audioeventname_;
}
inline void AudioInfo::set_audioeventname(const ::std::string& value) {
  set_has_audioeventname();
  if (audioeventname_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    audioeventname_ = new ::std::string;
  }
  audioeventname_->assign(value);
  // @@protoc_insertion_point(field_set:pb.AudioInfo.AudioEventName)
}
inline void AudioInfo::set_audioeventname(const char* value) {
  set_has_audioeventname();
  if (audioeventname_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    audioeventname_ = new ::std::string;
  }
  audioeventname_->assign(value);
  // @@protoc_insertion_point(field_set_char:pb.AudioInfo.AudioEventName)
}
inline void AudioInfo::set_audioeventname(const char* value, size_t size) {
  set_has_audioeventname();
  if (audioeventname_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    audioeventname_ = new ::std::string;
  }
  audioeventname_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:pb.AudioInfo.AudioEventName)
}
inline ::std::string* AudioInfo::mutable_audioeventname() {
  set_has_audioeventname();
  if (audioeventname_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    audioeventname_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:pb.AudioInfo.AudioEventName)
  return audioeventname_;
}
inline ::std::string* AudioInfo::release_audioeventname() {
  clear_has_audioeventname();
  if (audioeventname_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = audioeventname_;
    audioeventname_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void AudioInfo::set_allocated_audioeventname(::std::string* audioeventname) {
  if (audioeventname_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete audioeventname_;
  }
  if (audioeventname) {
    set_has_audioeventname();
    audioeventname_ = audioeventname;
  } else {
    clear_has_audioeventname();
    audioeventname_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:pb.AudioInfo.AudioEventName)
}

// repeated .pb.AnimationStateAudio AnimaAudioInfo = 3;
inline int AudioInfo::animaaudioinfo_size() const {
  return animaaudioinfo_.size();
}
inline void AudioInfo::clear_animaaudioinfo() {
  animaaudioinfo_.Clear();
}
inline const ::pb::AnimationStateAudio& AudioInfo::animaaudioinfo(int index) const {
  // @@protoc_insertion_point(field_get:pb.AudioInfo.AnimaAudioInfo)
  return animaaudioinfo_.Get(index);
}
inline ::pb::AnimationStateAudio* AudioInfo::mutable_animaaudioinfo(int index) {
  // @@protoc_insertion_point(field_mutable:pb.AudioInfo.AnimaAudioInfo)
  return animaaudioinfo_.Mutable(index);
}
inline ::pb::AnimationStateAudio* AudioInfo::add_animaaudioinfo() {
  // @@protoc_insertion_point(field_add:pb.AudioInfo.AnimaAudioInfo)
  return animaaudioinfo_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::pb::AnimationStateAudio >&
AudioInfo::animaaudioinfo() const {
  // @@protoc_insertion_point(field_list:pb.AudioInfo.AnimaAudioInfo)
  return animaaudioinfo_;
}
inline ::google::protobuf::RepeatedPtrField< ::pb::AnimationStateAudio >*
AudioInfo::mutable_animaaudioinfo() {
  // @@protoc_insertion_point(field_mutable_list:pb.AudioInfo.AnimaAudioInfo)
  return &animaaudioinfo_;
}

// -------------------------------------------------------------------

// AnimationStateAudio

// optional float StartTime = 1;
inline bool AnimationStateAudio::has_starttime() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void AnimationStateAudio::set_has_starttime() {
  _has_bits_[0] |= 0x00000001u;
}
inline void AnimationStateAudio::clear_has_starttime() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void AnimationStateAudio::clear_starttime() {
  starttime_ = 0;
  clear_has_starttime();
}
inline float AnimationStateAudio::starttime() const {
  // @@protoc_insertion_point(field_get:pb.AnimationStateAudio.StartTime)
  return starttime_;
}
inline void AnimationStateAudio::set_starttime(float value) {
  set_has_starttime();
  starttime_ = value;
  // @@protoc_insertion_point(field_set:pb.AnimationStateAudio.StartTime)
}

// optional string AudioEventName = 2;
inline bool AnimationStateAudio::has_audioeventname() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void AnimationStateAudio::set_has_audioeventname() {
  _has_bits_[0] |= 0x00000002u;
}
inline void AnimationStateAudio::clear_has_audioeventname() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void AnimationStateAudio::clear_audioeventname() {
  if (audioeventname_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    audioeventname_->clear();
  }
  clear_has_audioeventname();
}
inline const ::std::string& AnimationStateAudio::audioeventname() const {
  // @@protoc_insertion_point(field_get:pb.AnimationStateAudio.AudioEventName)
  return *audioeventname_;
}
inline void AnimationStateAudio::set_audioeventname(const ::std::string& value) {
  set_has_audioeventname();
  if (audioeventname_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    audioeventname_ = new ::std::string;
  }
  audioeventname_->assign(value);
  // @@protoc_insertion_point(field_set:pb.AnimationStateAudio.AudioEventName)
}
inline void AnimationStateAudio::set_audioeventname(const char* value) {
  set_has_audioeventname();
  if (audioeventname_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    audioeventname_ = new ::std::string;
  }
  audioeventname_->assign(value);
  // @@protoc_insertion_point(field_set_char:pb.AnimationStateAudio.AudioEventName)
}
inline void AnimationStateAudio::set_audioeventname(const char* value, size_t size) {
  set_has_audioeventname();
  if (audioeventname_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    audioeventname_ = new ::std::string;
  }
  audioeventname_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:pb.AnimationStateAudio.AudioEventName)
}
inline ::std::string* AnimationStateAudio::mutable_audioeventname() {
  set_has_audioeventname();
  if (audioeventname_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    audioeventname_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:pb.AnimationStateAudio.AudioEventName)
  return audioeventname_;
}
inline ::std::string* AnimationStateAudio::release_audioeventname() {
  clear_has_audioeventname();
  if (audioeventname_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = audioeventname_;
    audioeventname_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void AnimationStateAudio::set_allocated_audioeventname(::std::string* audioeventname) {
  if (audioeventname_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete audioeventname_;
  }
  if (audioeventname) {
    set_has_audioeventname();
    audioeventname_ = audioeventname;
  } else {
    clear_has_audioeventname();
    audioeventname_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:pb.AnimationStateAudio.AudioEventName)
}

// optional string AnimaStateName = 3;
inline bool AnimationStateAudio::has_animastatename() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void AnimationStateAudio::set_has_animastatename() {
  _has_bits_[0] |= 0x00000004u;
}
inline void AnimationStateAudio::clear_has_animastatename() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void AnimationStateAudio::clear_animastatename() {
  if (animastatename_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    animastatename_->clear();
  }
  clear_has_animastatename();
}
inline const ::std::string& AnimationStateAudio::animastatename() const {
  // @@protoc_insertion_point(field_get:pb.AnimationStateAudio.AnimaStateName)
  return *animastatename_;
}
inline void AnimationStateAudio::set_animastatename(const ::std::string& value) {
  set_has_animastatename();
  if (animastatename_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    animastatename_ = new ::std::string;
  }
  animastatename_->assign(value);
  // @@protoc_insertion_point(field_set:pb.AnimationStateAudio.AnimaStateName)
}
inline void AnimationStateAudio::set_animastatename(const char* value) {
  set_has_animastatename();
  if (animastatename_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    animastatename_ = new ::std::string;
  }
  animastatename_->assign(value);
  // @@protoc_insertion_point(field_set_char:pb.AnimationStateAudio.AnimaStateName)
}
inline void AnimationStateAudio::set_animastatename(const char* value, size_t size) {
  set_has_animastatename();
  if (animastatename_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    animastatename_ = new ::std::string;
  }
  animastatename_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:pb.AnimationStateAudio.AnimaStateName)
}
inline ::std::string* AnimationStateAudio::mutable_animastatename() {
  set_has_animastatename();
  if (animastatename_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    animastatename_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:pb.AnimationStateAudio.AnimaStateName)
  return animastatename_;
}
inline ::std::string* AnimationStateAudio::release_animastatename() {
  clear_has_animastatename();
  if (animastatename_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = animastatename_;
    animastatename_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void AnimationStateAudio::set_allocated_animastatename(::std::string* animastatename) {
  if (animastatename_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete animastatename_;
  }
  if (animastatename) {
    set_has_animastatename();
    animastatename_ = animastatename;
  } else {
    clear_has_animastatename();
    animastatename_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:pb.AnimationStateAudio.AnimaStateName)
}

// optional string AnimaTransName = 4;
inline bool AnimationStateAudio::has_animatransname() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void AnimationStateAudio::set_has_animatransname() {
  _has_bits_[0] |= 0x00000008u;
}
inline void AnimationStateAudio::clear_has_animatransname() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void AnimationStateAudio::clear_animatransname() {
  if (animatransname_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    animatransname_->clear();
  }
  clear_has_animatransname();
}
inline const ::std::string& AnimationStateAudio::animatransname() const {
  // @@protoc_insertion_point(field_get:pb.AnimationStateAudio.AnimaTransName)
  return *animatransname_;
}
inline void AnimationStateAudio::set_animatransname(const ::std::string& value) {
  set_has_animatransname();
  if (animatransname_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    animatransname_ = new ::std::string;
  }
  animatransname_->assign(value);
  // @@protoc_insertion_point(field_set:pb.AnimationStateAudio.AnimaTransName)
}
inline void AnimationStateAudio::set_animatransname(const char* value) {
  set_has_animatransname();
  if (animatransname_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    animatransname_ = new ::std::string;
  }
  animatransname_->assign(value);
  // @@protoc_insertion_point(field_set_char:pb.AnimationStateAudio.AnimaTransName)
}
inline void AnimationStateAudio::set_animatransname(const char* value, size_t size) {
  set_has_animatransname();
  if (animatransname_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    animatransname_ = new ::std::string;
  }
  animatransname_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:pb.AnimationStateAudio.AnimaTransName)
}
inline ::std::string* AnimationStateAudio::mutable_animatransname() {
  set_has_animatransname();
  if (animatransname_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    animatransname_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:pb.AnimationStateAudio.AnimaTransName)
  return animatransname_;
}
inline ::std::string* AnimationStateAudio::release_animatransname() {
  clear_has_animatransname();
  if (animatransname_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = animatransname_;
    animatransname_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void AnimationStateAudio::set_allocated_animatransname(::std::string* animatransname) {
  if (animatransname_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete animatransname_;
  }
  if (animatransname) {
    set_has_animatransname();
    animatransname_ = animatransname;
  } else {
    clear_has_animatransname();
    animatransname_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:pb.AnimationStateAudio.AnimaTransName)
}

// -------------------------------------------------------------------

// AudioDefine


// @@protoc_insertion_point(namespace_scope)

}  // namespace pb

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_module_2fAudioDefine_2eproto__INCLUDED
