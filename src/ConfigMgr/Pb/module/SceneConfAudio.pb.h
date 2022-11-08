// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: module/SceneConfAudio.proto

#ifndef PROTOBUF_module_2fSceneConfAudio_2eproto__INCLUDED
#define PROTOBUF_module_2fSceneConfAudio_2eproto__INCLUDED

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
#include "module/Util.pb.h"
// @@protoc_insertion_point(includes)

namespace pb {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_module_2fSceneConfAudio_2eproto();
void protobuf_AssignDesc_module_2fSceneConfAudio_2eproto();
void protobuf_ShutdownFile_module_2fSceneConfAudio_2eproto();

class PointAudioInfo;
class SceneConfAudio;

// ===================================================================

/*FOR2LUA
<Record>
	<name>PointAudioInfo</name>
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
		<replaceName>module/SceneConfAudio.proto</replaceName>
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
class PointAudioInfo : public ::google::protobuf::Message {
 public:
  PointAudioInfo();
  virtual ~PointAudioInfo();

  PointAudioInfo(const PointAudioInfo& from);

  inline PointAudioInfo& operator=(const PointAudioInfo& from) {
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
  static const PointAudioInfo& default_instance();

  void Swap(PointAudioInfo* other);

  // implements Message ----------------------------------------------

  PointAudioInfo* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const PointAudioInfo& from);
  void MergeFrom(const PointAudioInfo& from);
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

  // optional .pb.AudioInfo EnterAudioInfo = 1;
  inline bool has_enteraudioinfo() const;
  inline void clear_enteraudioinfo();
  static const int kEnterAudioInfoFieldNumber = 1;
  /*FOR2LUA
  <Record>
  	<name>PointAudioInfo</name>
  	<Function>
  		<name>enteraudioinfo</name>
  		<replaceName>EnterAudioInfo</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>set_enteraudioinfo</name>
  		<replaceName>EnterAudioInfo</replaceName>
  		<handler>descripter = pb_set_message_cpp()</handler>
  	</Function>
  	<Function>
  		<name>set_allocated_enteraudioinfo</name>
  		<replaceName>EnterAudioInfo</replaceName>
  		<handler>descripter = pb_set_message_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_enteraudioinfo</name>
  		<replaceName>EnterAudioInfo</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline const ::pb::AudioInfo& enteraudioinfo() const;
  inline ::pb::AudioInfo* mutable_enteraudioinfo();
  inline ::pb::AudioInfo* release_enteraudioinfo();
  inline void set_allocated_enteraudioinfo(::pb::AudioInfo* enteraudioinfo);

  // optional .pb.AudioInfo LeaveAudioInfo = 2;
  inline bool has_leaveaudioinfo() const;
  inline void clear_leaveaudioinfo();
  static const int kLeaveAudioInfoFieldNumber = 2;
  /*FOR2LUA
  <Record>
  	<name>PointAudioInfo</name>
  	<Function>
  		<name>leaveaudioinfo</name>
  		<replaceName>LeaveAudioInfo</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>set_leaveaudioinfo</name>
  		<replaceName>LeaveAudioInfo</replaceName>
  		<handler>descripter = pb_set_message_cpp()</handler>
  	</Function>
  	<Function>
  		<name>set_allocated_leaveaudioinfo</name>
  		<replaceName>LeaveAudioInfo</replaceName>
  		<handler>descripter = pb_set_message_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_leaveaudioinfo</name>
  		<replaceName>LeaveAudioInfo</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline const ::pb::AudioInfo& leaveaudioinfo() const;
  inline ::pb::AudioInfo* mutable_leaveaudioinfo();
  inline ::pb::AudioInfo* release_leaveaudioinfo();
  inline void set_allocated_leaveaudioinfo(::pb::AudioInfo* leaveaudioinfo);

  // optional float Radius = 3;
  inline bool has_radius() const;
  inline void clear_radius();
  static const int kRadiusFieldNumber = 3;
  /*FOR2LUA
  <Record>
  	<name>PointAudioInfo</name>
  	<Function>
  		<name>radius</name>
  		<replaceName>Radius</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>set_radius</name>
  		<replaceName>Radius</replaceName>
  		<handler>descripter = pb_set_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_radius</name>
  		<replaceName>Radius</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline float radius() const;
  inline void set_radius(float value);

  // optional .pb.PbVector2 Position = 4;
  inline bool has_position() const;
  inline void clear_position();
  static const int kPositionFieldNumber = 4;
  /*FOR2LUA
  <Record>
  	<name>PointAudioInfo</name>
  	<Function>
  		<name>position</name>
  		<replaceName>Position</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>set_position</name>
  		<replaceName>Position</replaceName>
  		<handler>descripter = pb_set_message_cpp()</handler>
  	</Function>
  	<Function>
  		<name>set_allocated_position</name>
  		<replaceName>Position</replaceName>
  		<handler>descripter = pb_set_message_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_position</name>
  		<replaceName>Position</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline const ::pb::PbVector2& position() const;
  inline ::pb::PbVector2* mutable_position();
  inline ::pb::PbVector2* release_position();
  inline void set_allocated_position(::pb::PbVector2* position);

  // @@protoc_insertion_point(class_scope:pb.PointAudioInfo)
 private:
  inline void set_has_enteraudioinfo();
  inline void clear_has_enteraudioinfo();
  inline void set_has_leaveaudioinfo();
  inline void clear_has_leaveaudioinfo();
  inline void set_has_radius();
  inline void clear_has_radius();
  inline void set_has_position();
  inline void clear_has_position();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::pb::AudioInfo* enteraudioinfo_;
  ::pb::AudioInfo* leaveaudioinfo_;
  ::pb::PbVector2* position_;
  float radius_;
  friend void  protobuf_AddDesc_module_2fSceneConfAudio_2eproto();
  friend void protobuf_AssignDesc_module_2fSceneConfAudio_2eproto();
  friend void protobuf_ShutdownFile_module_2fSceneConfAudio_2eproto();

  void InitAsDefaultInstance();
  static PointAudioInfo* default_instance_;
};
// -------------------------------------------------------------------

/*FOR2LUA
<Record>
	<name>SceneConfAudio</name>
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
		<replaceName>module/SceneConfAudio.proto</replaceName>
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
class SceneConfAudio : public ::google::protobuf::Message {
 public:
  SceneConfAudio();
  virtual ~SceneConfAudio();

  SceneConfAudio(const SceneConfAudio& from);

  inline SceneConfAudio& operator=(const SceneConfAudio& from) {
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
  static const SceneConfAudio& default_instance();

  void Swap(SceneConfAudio* other);

  // implements Message ----------------------------------------------

  SceneConfAudio* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const SceneConfAudio& from);
  void MergeFrom(const SceneConfAudio& from);
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
  	<name>SceneConfAudio</name>
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

  // optional string SceneConfName = 2;
  inline bool has_sceneconfname() const;
  inline void clear_sceneconfname();
  static const int kSceneConfNameFieldNumber = 2;
  /*FOR2LUA
  <Record>
  	<name>SceneConfAudio</name>
  	<Function>
  		<name>sceneconfname</name>
  		<replaceName>SceneConfName</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>set_sceneconfname</name>
  		<replaceName>SceneConfName</replaceName>
  		<handler>descripter = pb_set_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_sceneconfname</name>
  		<replaceName>SceneConfName</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline const ::std::string& sceneconfname() const;
  inline void set_sceneconfname(const ::std::string& value);
  inline void set_sceneconfname(const char* value);
  inline void set_sceneconfname(const char* value, size_t size);
  inline ::std::string* mutable_sceneconfname();
  inline ::std::string* release_sceneconfname();
  inline void set_allocated_sceneconfname(::std::string* sceneconfname);

  // repeated .pb.PointAudioInfo PointAudioInfoArr = 3;
  inline int pointaudioinfoarr_size() const;
  inline void clear_pointaudioinfoarr();
  static const int kPointAudioInfoArrFieldNumber = 3;
  /*FOR2LUA
  <Record>
  	<name>SceneConfAudio</name>
  	<Function>
  		<name>pointaudioinfoarr</name>
  		<replaceName>PointAudioInfoArr</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>mutable_pointaudioinfoarr</name>
  		<replaceName>PointAudioInfoArr</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>add_pointaudioinfoarr</name>
  		<replaceName>PointAudioInfoArr</replaceName>
  		<handler>descripter = pb_repeated_add_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_pointaudioinfoarr</name>
  		<replaceName>PointAudioInfoArr</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  	<Function>
  		<name>pointaudioinfoarr_size</name>
  		<replaceName>PointAudioInfoArr</replaceName>
  		<handler>descripter = pb_repeated_size_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline const ::pb::PointAudioInfo& pointaudioinfoarr(int index) const;
  inline ::pb::PointAudioInfo* mutable_pointaudioinfoarr(int index);
  inline ::pb::PointAudioInfo* add_pointaudioinfoarr();
  inline const ::google::protobuf::RepeatedPtrField< ::pb::PointAudioInfo >&
      pointaudioinfoarr() const;
  inline ::google::protobuf::RepeatedPtrField< ::pb::PointAudioInfo >*
      mutable_pointaudioinfoarr();

  // optional .pb.AudioInfo AriariAudioInfo = 4;
  inline bool has_ariariaudioinfo() const;
  inline void clear_ariariaudioinfo();
  static const int kAriariAudioInfoFieldNumber = 4;
  /*FOR2LUA
  <Record>
  	<name>SceneConfAudio</name>
  	<Function>
  		<name>ariariaudioinfo</name>
  		<replaceName>AriariAudioInfo</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>set_ariariaudioinfo</name>
  		<replaceName>AriariAudioInfo</replaceName>
  		<handler>descripter = pb_set_message_cpp()</handler>
  	</Function>
  	<Function>
  		<name>set_allocated_ariariaudioinfo</name>
  		<replaceName>AriariAudioInfo</replaceName>
  		<handler>descripter = pb_set_message_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_ariariaudioinfo</name>
  		<replaceName>AriariAudioInfo</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline const ::pb::AudioInfo& ariariaudioinfo() const;
  inline ::pb::AudioInfo* mutable_ariariaudioinfo();
  inline ::pb::AudioInfo* release_ariariaudioinfo();
  inline void set_allocated_ariariaudioinfo(::pb::AudioInfo* ariariaudioinfo);

  // optional .pb.AudioInfo AmbientAudioInfo = 5;
  inline bool has_ambientaudioinfo() const;
  inline void clear_ambientaudioinfo();
  static const int kAmbientAudioInfoFieldNumber = 5;
  /*FOR2LUA
  <Record>
  	<name>SceneConfAudio</name>
  	<Function>
  		<name>ambientaudioinfo</name>
  		<replaceName>AmbientAudioInfo</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>set_ambientaudioinfo</name>
  		<replaceName>AmbientAudioInfo</replaceName>
  		<handler>descripter = pb_set_message_cpp()</handler>
  	</Function>
  	<Function>
  		<name>set_allocated_ambientaudioinfo</name>
  		<replaceName>AmbientAudioInfo</replaceName>
  		<handler>descripter = pb_set_message_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_ambientaudioinfo</name>
  		<replaceName>AmbientAudioInfo</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline const ::pb::AudioInfo& ambientaudioinfo() const;
  inline ::pb::AudioInfo* mutable_ambientaudioinfo();
  inline ::pb::AudioInfo* release_ambientaudioinfo();
  inline void set_allocated_ambientaudioinfo(::pb::AudioInfo* ambientaudioinfo);

  // repeated .pb.AudioInfo EnterSceneAudioInfoArr = 6;
  inline int entersceneaudioinfoarr_size() const;
  inline void clear_entersceneaudioinfoarr();
  static const int kEnterSceneAudioInfoArrFieldNumber = 6;
  /*FOR2LUA
  <Record>
  	<name>SceneConfAudio</name>
  	<Function>
  		<name>entersceneaudioinfoarr</name>
  		<replaceName>EnterSceneAudioInfoArr</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>mutable_entersceneaudioinfoarr</name>
  		<replaceName>EnterSceneAudioInfoArr</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>add_entersceneaudioinfoarr</name>
  		<replaceName>EnterSceneAudioInfoArr</replaceName>
  		<handler>descripter = pb_repeated_add_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_entersceneaudioinfoarr</name>
  		<replaceName>EnterSceneAudioInfoArr</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  	<Function>
  		<name>entersceneaudioinfoarr_size</name>
  		<replaceName>EnterSceneAudioInfoArr</replaceName>
  		<handler>descripter = pb_repeated_size_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline const ::pb::AudioInfo& entersceneaudioinfoarr(int index) const;
  inline ::pb::AudioInfo* mutable_entersceneaudioinfoarr(int index);
  inline ::pb::AudioInfo* add_entersceneaudioinfoarr();
  inline const ::google::protobuf::RepeatedPtrField< ::pb::AudioInfo >&
      entersceneaudioinfoarr() const;
  inline ::google::protobuf::RepeatedPtrField< ::pb::AudioInfo >*
      mutable_entersceneaudioinfoarr();

  // repeated .pb.AudioInfo LeaveSceneAudioInfoArr = 7;
  inline int leavesceneaudioinfoarr_size() const;
  inline void clear_leavesceneaudioinfoarr();
  static const int kLeaveSceneAudioInfoArrFieldNumber = 7;
  /*FOR2LUA
  <Record>
  	<name>SceneConfAudio</name>
  	<Function>
  		<name>leavesceneaudioinfoarr</name>
  		<replaceName>LeaveSceneAudioInfoArr</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>mutable_leavesceneaudioinfoarr</name>
  		<replaceName>LeaveSceneAudioInfoArr</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>add_leavesceneaudioinfoarr</name>
  		<replaceName>LeaveSceneAudioInfoArr</replaceName>
  		<handler>descripter = pb_repeated_add_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_leavesceneaudioinfoarr</name>
  		<replaceName>LeaveSceneAudioInfoArr</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  	<Function>
  		<name>leavesceneaudioinfoarr_size</name>
  		<replaceName>LeaveSceneAudioInfoArr</replaceName>
  		<handler>descripter = pb_repeated_size_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline const ::pb::AudioInfo& leavesceneaudioinfoarr(int index) const;
  inline ::pb::AudioInfo* mutable_leavesceneaudioinfoarr(int index);
  inline ::pb::AudioInfo* add_leavesceneaudioinfoarr();
  inline const ::google::protobuf::RepeatedPtrField< ::pb::AudioInfo >&
      leavesceneaudioinfoarr() const;
  inline ::google::protobuf::RepeatedPtrField< ::pb::AudioInfo >*
      mutable_leavesceneaudioinfoarr();

  // @@protoc_insertion_point(class_scope:pb.SceneConfAudio)
 private:
  inline void set_has_id();
  inline void clear_has_id();
  inline void set_has_sceneconfname();
  inline void clear_has_sceneconfname();
  inline void set_has_ariariaudioinfo();
  inline void clear_has_ariariaudioinfo();
  inline void set_has_ambientaudioinfo();
  inline void clear_has_ambientaudioinfo();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::std::string* sceneconfname_;
  ::google::protobuf::RepeatedPtrField< ::pb::PointAudioInfo > pointaudioinfoarr_;
  ::pb::AudioInfo* ariariaudioinfo_;
  ::pb::AudioInfo* ambientaudioinfo_;
  ::google::protobuf::RepeatedPtrField< ::pb::AudioInfo > entersceneaudioinfoarr_;
  ::google::protobuf::RepeatedPtrField< ::pb::AudioInfo > leavesceneaudioinfoarr_;
  ::google::protobuf::int32 id_;
  friend void  protobuf_AddDesc_module_2fSceneConfAudio_2eproto();
  friend void protobuf_AssignDesc_module_2fSceneConfAudio_2eproto();
  friend void protobuf_ShutdownFile_module_2fSceneConfAudio_2eproto();

  void InitAsDefaultInstance();
  static SceneConfAudio* default_instance_;
};
// ===================================================================


// ===================================================================

// PointAudioInfo

// optional .pb.AudioInfo EnterAudioInfo = 1;
inline bool PointAudioInfo::has_enteraudioinfo() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void PointAudioInfo::set_has_enteraudioinfo() {
  _has_bits_[0] |= 0x00000001u;
}
inline void PointAudioInfo::clear_has_enteraudioinfo() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void PointAudioInfo::clear_enteraudioinfo() {
  if (enteraudioinfo_ != NULL) enteraudioinfo_->::pb::AudioInfo::Clear();
  clear_has_enteraudioinfo();
}
inline const ::pb::AudioInfo& PointAudioInfo::enteraudioinfo() const {
  // @@protoc_insertion_point(field_get:pb.PointAudioInfo.EnterAudioInfo)
  return enteraudioinfo_ != NULL ? *enteraudioinfo_ : *default_instance_->enteraudioinfo_;
}
inline ::pb::AudioInfo* PointAudioInfo::mutable_enteraudioinfo() {
  set_has_enteraudioinfo();
  if (enteraudioinfo_ == NULL) enteraudioinfo_ = new ::pb::AudioInfo;
  // @@protoc_insertion_point(field_mutable:pb.PointAudioInfo.EnterAudioInfo)
  return enteraudioinfo_;
}
inline ::pb::AudioInfo* PointAudioInfo::release_enteraudioinfo() {
  clear_has_enteraudioinfo();
  ::pb::AudioInfo* temp = enteraudioinfo_;
  enteraudioinfo_ = NULL;
  return temp;
}
inline void PointAudioInfo::set_allocated_enteraudioinfo(::pb::AudioInfo* enteraudioinfo) {
  delete enteraudioinfo_;
  enteraudioinfo_ = enteraudioinfo;
  if (enteraudioinfo) {
    set_has_enteraudioinfo();
  } else {
    clear_has_enteraudioinfo();
  }
  // @@protoc_insertion_point(field_set_allocated:pb.PointAudioInfo.EnterAudioInfo)
}

// optional .pb.AudioInfo LeaveAudioInfo = 2;
inline bool PointAudioInfo::has_leaveaudioinfo() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void PointAudioInfo::set_has_leaveaudioinfo() {
  _has_bits_[0] |= 0x00000002u;
}
inline void PointAudioInfo::clear_has_leaveaudioinfo() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void PointAudioInfo::clear_leaveaudioinfo() {
  if (leaveaudioinfo_ != NULL) leaveaudioinfo_->::pb::AudioInfo::Clear();
  clear_has_leaveaudioinfo();
}
inline const ::pb::AudioInfo& PointAudioInfo::leaveaudioinfo() const {
  // @@protoc_insertion_point(field_get:pb.PointAudioInfo.LeaveAudioInfo)
  return leaveaudioinfo_ != NULL ? *leaveaudioinfo_ : *default_instance_->leaveaudioinfo_;
}
inline ::pb::AudioInfo* PointAudioInfo::mutable_leaveaudioinfo() {
  set_has_leaveaudioinfo();
  if (leaveaudioinfo_ == NULL) leaveaudioinfo_ = new ::pb::AudioInfo;
  // @@protoc_insertion_point(field_mutable:pb.PointAudioInfo.LeaveAudioInfo)
  return leaveaudioinfo_;
}
inline ::pb::AudioInfo* PointAudioInfo::release_leaveaudioinfo() {
  clear_has_leaveaudioinfo();
  ::pb::AudioInfo* temp = leaveaudioinfo_;
  leaveaudioinfo_ = NULL;
  return temp;
}
inline void PointAudioInfo::set_allocated_leaveaudioinfo(::pb::AudioInfo* leaveaudioinfo) {
  delete leaveaudioinfo_;
  leaveaudioinfo_ = leaveaudioinfo;
  if (leaveaudioinfo) {
    set_has_leaveaudioinfo();
  } else {
    clear_has_leaveaudioinfo();
  }
  // @@protoc_insertion_point(field_set_allocated:pb.PointAudioInfo.LeaveAudioInfo)
}

// optional float Radius = 3;
inline bool PointAudioInfo::has_radius() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void PointAudioInfo::set_has_radius() {
  _has_bits_[0] |= 0x00000004u;
}
inline void PointAudioInfo::clear_has_radius() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void PointAudioInfo::clear_radius() {
  radius_ = 0;
  clear_has_radius();
}
inline float PointAudioInfo::radius() const {
  // @@protoc_insertion_point(field_get:pb.PointAudioInfo.Radius)
  return radius_;
}
inline void PointAudioInfo::set_radius(float value) {
  set_has_radius();
  radius_ = value;
  // @@protoc_insertion_point(field_set:pb.PointAudioInfo.Radius)
}

// optional .pb.PbVector2 Position = 4;
inline bool PointAudioInfo::has_position() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void PointAudioInfo::set_has_position() {
  _has_bits_[0] |= 0x00000008u;
}
inline void PointAudioInfo::clear_has_position() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void PointAudioInfo::clear_position() {
  if (position_ != NULL) position_->::pb::PbVector2::Clear();
  clear_has_position();
}
inline const ::pb::PbVector2& PointAudioInfo::position() const {
  // @@protoc_insertion_point(field_get:pb.PointAudioInfo.Position)
  return position_ != NULL ? *position_ : *default_instance_->position_;
}
inline ::pb::PbVector2* PointAudioInfo::mutable_position() {
  set_has_position();
  if (position_ == NULL) position_ = new ::pb::PbVector2;
  // @@protoc_insertion_point(field_mutable:pb.PointAudioInfo.Position)
  return position_;
}
inline ::pb::PbVector2* PointAudioInfo::release_position() {
  clear_has_position();
  ::pb::PbVector2* temp = position_;
  position_ = NULL;
  return temp;
}
inline void PointAudioInfo::set_allocated_position(::pb::PbVector2* position) {
  delete position_;
  position_ = position;
  if (position) {
    set_has_position();
  } else {
    clear_has_position();
  }
  // @@protoc_insertion_point(field_set_allocated:pb.PointAudioInfo.Position)
}

// -------------------------------------------------------------------

// SceneConfAudio

// optional int32 Id = 1;
inline bool SceneConfAudio::has_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void SceneConfAudio::set_has_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void SceneConfAudio::clear_has_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void SceneConfAudio::clear_id() {
  id_ = 0;
  clear_has_id();
}
inline ::google::protobuf::int32 SceneConfAudio::id() const {
  // @@protoc_insertion_point(field_get:pb.SceneConfAudio.Id)
  return id_;
}
inline void SceneConfAudio::set_id(::google::protobuf::int32 value) {
  set_has_id();
  id_ = value;
  // @@protoc_insertion_point(field_set:pb.SceneConfAudio.Id)
}

// optional string SceneConfName = 2;
inline bool SceneConfAudio::has_sceneconfname() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void SceneConfAudio::set_has_sceneconfname() {
  _has_bits_[0] |= 0x00000002u;
}
inline void SceneConfAudio::clear_has_sceneconfname() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void SceneConfAudio::clear_sceneconfname() {
  if (sceneconfname_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    sceneconfname_->clear();
  }
  clear_has_sceneconfname();
}
inline const ::std::string& SceneConfAudio::sceneconfname() const {
  // @@protoc_insertion_point(field_get:pb.SceneConfAudio.SceneConfName)
  return *sceneconfname_;
}
inline void SceneConfAudio::set_sceneconfname(const ::std::string& value) {
  set_has_sceneconfname();
  if (sceneconfname_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    sceneconfname_ = new ::std::string;
  }
  sceneconfname_->assign(value);
  // @@protoc_insertion_point(field_set:pb.SceneConfAudio.SceneConfName)
}
inline void SceneConfAudio::set_sceneconfname(const char* value) {
  set_has_sceneconfname();
  if (sceneconfname_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    sceneconfname_ = new ::std::string;
  }
  sceneconfname_->assign(value);
  // @@protoc_insertion_point(field_set_char:pb.SceneConfAudio.SceneConfName)
}
inline void SceneConfAudio::set_sceneconfname(const char* value, size_t size) {
  set_has_sceneconfname();
  if (sceneconfname_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    sceneconfname_ = new ::std::string;
  }
  sceneconfname_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:pb.SceneConfAudio.SceneConfName)
}
inline ::std::string* SceneConfAudio::mutable_sceneconfname() {
  set_has_sceneconfname();
  if (sceneconfname_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    sceneconfname_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:pb.SceneConfAudio.SceneConfName)
  return sceneconfname_;
}
inline ::std::string* SceneConfAudio::release_sceneconfname() {
  clear_has_sceneconfname();
  if (sceneconfname_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = sceneconfname_;
    sceneconfname_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void SceneConfAudio::set_allocated_sceneconfname(::std::string* sceneconfname) {
  if (sceneconfname_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete sceneconfname_;
  }
  if (sceneconfname) {
    set_has_sceneconfname();
    sceneconfname_ = sceneconfname;
  } else {
    clear_has_sceneconfname();
    sceneconfname_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:pb.SceneConfAudio.SceneConfName)
}

// repeated .pb.PointAudioInfo PointAudioInfoArr = 3;
inline int SceneConfAudio::pointaudioinfoarr_size() const {
  return pointaudioinfoarr_.size();
}
inline void SceneConfAudio::clear_pointaudioinfoarr() {
  pointaudioinfoarr_.Clear();
}
inline const ::pb::PointAudioInfo& SceneConfAudio::pointaudioinfoarr(int index) const {
  // @@protoc_insertion_point(field_get:pb.SceneConfAudio.PointAudioInfoArr)
  return pointaudioinfoarr_.Get(index);
}
inline ::pb::PointAudioInfo* SceneConfAudio::mutable_pointaudioinfoarr(int index) {
  // @@protoc_insertion_point(field_mutable:pb.SceneConfAudio.PointAudioInfoArr)
  return pointaudioinfoarr_.Mutable(index);
}
inline ::pb::PointAudioInfo* SceneConfAudio::add_pointaudioinfoarr() {
  // @@protoc_insertion_point(field_add:pb.SceneConfAudio.PointAudioInfoArr)
  return pointaudioinfoarr_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::pb::PointAudioInfo >&
SceneConfAudio::pointaudioinfoarr() const {
  // @@protoc_insertion_point(field_list:pb.SceneConfAudio.PointAudioInfoArr)
  return pointaudioinfoarr_;
}
inline ::google::protobuf::RepeatedPtrField< ::pb::PointAudioInfo >*
SceneConfAudio::mutable_pointaudioinfoarr() {
  // @@protoc_insertion_point(field_mutable_list:pb.SceneConfAudio.PointAudioInfoArr)
  return &pointaudioinfoarr_;
}

// optional .pb.AudioInfo AriariAudioInfo = 4;
inline bool SceneConfAudio::has_ariariaudioinfo() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void SceneConfAudio::set_has_ariariaudioinfo() {
  _has_bits_[0] |= 0x00000008u;
}
inline void SceneConfAudio::clear_has_ariariaudioinfo() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void SceneConfAudio::clear_ariariaudioinfo() {
  if (ariariaudioinfo_ != NULL) ariariaudioinfo_->::pb::AudioInfo::Clear();
  clear_has_ariariaudioinfo();
}
inline const ::pb::AudioInfo& SceneConfAudio::ariariaudioinfo() const {
  // @@protoc_insertion_point(field_get:pb.SceneConfAudio.AriariAudioInfo)
  return ariariaudioinfo_ != NULL ? *ariariaudioinfo_ : *default_instance_->ariariaudioinfo_;
}
inline ::pb::AudioInfo* SceneConfAudio::mutable_ariariaudioinfo() {
  set_has_ariariaudioinfo();
  if (ariariaudioinfo_ == NULL) ariariaudioinfo_ = new ::pb::AudioInfo;
  // @@protoc_insertion_point(field_mutable:pb.SceneConfAudio.AriariAudioInfo)
  return ariariaudioinfo_;
}
inline ::pb::AudioInfo* SceneConfAudio::release_ariariaudioinfo() {
  clear_has_ariariaudioinfo();
  ::pb::AudioInfo* temp = ariariaudioinfo_;
  ariariaudioinfo_ = NULL;
  return temp;
}
inline void SceneConfAudio::set_allocated_ariariaudioinfo(::pb::AudioInfo* ariariaudioinfo) {
  delete ariariaudioinfo_;
  ariariaudioinfo_ = ariariaudioinfo;
  if (ariariaudioinfo) {
    set_has_ariariaudioinfo();
  } else {
    clear_has_ariariaudioinfo();
  }
  // @@protoc_insertion_point(field_set_allocated:pb.SceneConfAudio.AriariAudioInfo)
}

// optional .pb.AudioInfo AmbientAudioInfo = 5;
inline bool SceneConfAudio::has_ambientaudioinfo() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void SceneConfAudio::set_has_ambientaudioinfo() {
  _has_bits_[0] |= 0x00000010u;
}
inline void SceneConfAudio::clear_has_ambientaudioinfo() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void SceneConfAudio::clear_ambientaudioinfo() {
  if (ambientaudioinfo_ != NULL) ambientaudioinfo_->::pb::AudioInfo::Clear();
  clear_has_ambientaudioinfo();
}
inline const ::pb::AudioInfo& SceneConfAudio::ambientaudioinfo() const {
  // @@protoc_insertion_point(field_get:pb.SceneConfAudio.AmbientAudioInfo)
  return ambientaudioinfo_ != NULL ? *ambientaudioinfo_ : *default_instance_->ambientaudioinfo_;
}
inline ::pb::AudioInfo* SceneConfAudio::mutable_ambientaudioinfo() {
  set_has_ambientaudioinfo();
  if (ambientaudioinfo_ == NULL) ambientaudioinfo_ = new ::pb::AudioInfo;
  // @@protoc_insertion_point(field_mutable:pb.SceneConfAudio.AmbientAudioInfo)
  return ambientaudioinfo_;
}
inline ::pb::AudioInfo* SceneConfAudio::release_ambientaudioinfo() {
  clear_has_ambientaudioinfo();
  ::pb::AudioInfo* temp = ambientaudioinfo_;
  ambientaudioinfo_ = NULL;
  return temp;
}
inline void SceneConfAudio::set_allocated_ambientaudioinfo(::pb::AudioInfo* ambientaudioinfo) {
  delete ambientaudioinfo_;
  ambientaudioinfo_ = ambientaudioinfo;
  if (ambientaudioinfo) {
    set_has_ambientaudioinfo();
  } else {
    clear_has_ambientaudioinfo();
  }
  // @@protoc_insertion_point(field_set_allocated:pb.SceneConfAudio.AmbientAudioInfo)
}

// repeated .pb.AudioInfo EnterSceneAudioInfoArr = 6;
inline int SceneConfAudio::entersceneaudioinfoarr_size() const {
  return entersceneaudioinfoarr_.size();
}
inline void SceneConfAudio::clear_entersceneaudioinfoarr() {
  entersceneaudioinfoarr_.Clear();
}
inline const ::pb::AudioInfo& SceneConfAudio::entersceneaudioinfoarr(int index) const {
  // @@protoc_insertion_point(field_get:pb.SceneConfAudio.EnterSceneAudioInfoArr)
  return entersceneaudioinfoarr_.Get(index);
}
inline ::pb::AudioInfo* SceneConfAudio::mutable_entersceneaudioinfoarr(int index) {
  // @@protoc_insertion_point(field_mutable:pb.SceneConfAudio.EnterSceneAudioInfoArr)
  return entersceneaudioinfoarr_.Mutable(index);
}
inline ::pb::AudioInfo* SceneConfAudio::add_entersceneaudioinfoarr() {
  // @@protoc_insertion_point(field_add:pb.SceneConfAudio.EnterSceneAudioInfoArr)
  return entersceneaudioinfoarr_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::pb::AudioInfo >&
SceneConfAudio::entersceneaudioinfoarr() const {
  // @@protoc_insertion_point(field_list:pb.SceneConfAudio.EnterSceneAudioInfoArr)
  return entersceneaudioinfoarr_;
}
inline ::google::protobuf::RepeatedPtrField< ::pb::AudioInfo >*
SceneConfAudio::mutable_entersceneaudioinfoarr() {
  // @@protoc_insertion_point(field_mutable_list:pb.SceneConfAudio.EnterSceneAudioInfoArr)
  return &entersceneaudioinfoarr_;
}

// repeated .pb.AudioInfo LeaveSceneAudioInfoArr = 7;
inline int SceneConfAudio::leavesceneaudioinfoarr_size() const {
  return leavesceneaudioinfoarr_.size();
}
inline void SceneConfAudio::clear_leavesceneaudioinfoarr() {
  leavesceneaudioinfoarr_.Clear();
}
inline const ::pb::AudioInfo& SceneConfAudio::leavesceneaudioinfoarr(int index) const {
  // @@protoc_insertion_point(field_get:pb.SceneConfAudio.LeaveSceneAudioInfoArr)
  return leavesceneaudioinfoarr_.Get(index);
}
inline ::pb::AudioInfo* SceneConfAudio::mutable_leavesceneaudioinfoarr(int index) {
  // @@protoc_insertion_point(field_mutable:pb.SceneConfAudio.LeaveSceneAudioInfoArr)
  return leavesceneaudioinfoarr_.Mutable(index);
}
inline ::pb::AudioInfo* SceneConfAudio::add_leavesceneaudioinfoarr() {
  // @@protoc_insertion_point(field_add:pb.SceneConfAudio.LeaveSceneAudioInfoArr)
  return leavesceneaudioinfoarr_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::pb::AudioInfo >&
SceneConfAudio::leavesceneaudioinfoarr() const {
  // @@protoc_insertion_point(field_list:pb.SceneConfAudio.LeaveSceneAudioInfoArr)
  return leavesceneaudioinfoarr_;
}
inline ::google::protobuf::RepeatedPtrField< ::pb::AudioInfo >*
SceneConfAudio::mutable_leavesceneaudioinfoarr() {
  // @@protoc_insertion_point(field_mutable_list:pb.SceneConfAudio.LeaveSceneAudioInfoArr)
  return &leavesceneaudioinfoarr_;
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

#endif  // PROTOBUF_module_2fSceneConfAudio_2eproto__INCLUDED