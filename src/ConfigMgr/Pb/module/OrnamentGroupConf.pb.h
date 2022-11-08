// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: module/OrnamentGroupConf.proto

#ifndef PROTOBUF_module_2fOrnamentGroupConf_2eproto__INCLUDED
#define PROTOBUF_module_2fOrnamentGroupConf_2eproto__INCLUDED

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
#include "module/Util.pb.h"
// @@protoc_insertion_point(includes)

namespace pb {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_module_2fOrnamentGroupConf_2eproto();
void protobuf_AssignDesc_module_2fOrnamentGroupConf_2eproto();
void protobuf_ShutdownFile_module_2fOrnamentGroupConf_2eproto();

class OrnamentGroupConf;

// ===================================================================

/*FOR2LUA
<Record>
	<name>OrnamentGroupConf</name>
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
		<replaceName>module/OrnamentGroupConf.proto</replaceName>
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
class OrnamentGroupConf : public ::google::protobuf::Message {
 public:
  OrnamentGroupConf();
  virtual ~OrnamentGroupConf();

  OrnamentGroupConf(const OrnamentGroupConf& from);

  inline OrnamentGroupConf& operator=(const OrnamentGroupConf& from) {
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
  static const OrnamentGroupConf& default_instance();

  void Swap(OrnamentGroupConf* other);

  // implements Message ----------------------------------------------

  OrnamentGroupConf* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const OrnamentGroupConf& from);
  void MergeFrom(const OrnamentGroupConf& from);
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

  // required int32 Id = 1;
  inline bool has_id() const;
  inline void clear_id();
  static const int kIdFieldNumber = 1;
  /*FOR2LUA
  <Record>
  	<name>OrnamentGroupConf</name>
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

  // optional string Name = 2;
  inline bool has_name() const;
  inline void clear_name();
  static const int kNameFieldNumber = 2;
  /*FOR2LUA
  <Record>
  	<name>OrnamentGroupConf</name>
  	<Function>
  		<name>name</name>
  		<replaceName>Name</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>set_name</name>
  		<replaceName>Name</replaceName>
  		<handler>descripter = pb_set_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_name</name>
  		<replaceName>Name</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline const ::std::string& name() const;
  inline void set_name(const ::std::string& value);
  inline void set_name(const char* value);
  inline void set_name(const char* value, size_t size);
  inline ::std::string* mutable_name();
  inline ::std::string* release_name();
  inline void set_allocated_name(::std::string* name);

  // optional string AssetPath = 3;
  inline bool has_assetpath() const;
  inline void clear_assetpath();
  static const int kAssetPathFieldNumber = 3;
  /*FOR2LUA
  <Record>
  	<name>OrnamentGroupConf</name>
  	<Function>
  		<name>assetpath</name>
  		<replaceName>AssetPath</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>set_assetpath</name>
  		<replaceName>AssetPath</replaceName>
  		<handler>descripter = pb_set_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_assetpath</name>
  		<replaceName>AssetPath</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline const ::std::string& assetpath() const;
  inline void set_assetpath(const ::std::string& value);
  inline void set_assetpath(const char* value);
  inline void set_assetpath(const char* value, size_t size);
  inline ::std::string* mutable_assetpath();
  inline ::std::string* release_assetpath();
  inline void set_allocated_assetpath(::std::string* assetpath);

  // optional .pb.PbVector2_Int GroupSize = 4;
  inline bool has_groupsize() const;
  inline void clear_groupsize();
  static const int kGroupSizeFieldNumber = 4;
  /*FOR2LUA
  <Record>
  	<name>OrnamentGroupConf</name>
  	<Function>
  		<name>groupsize</name>
  		<replaceName>GroupSize</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>set_groupsize</name>
  		<replaceName>GroupSize</replaceName>
  		<handler>descripter = pb_set_message_cpp()</handler>
  	</Function>
  	<Function>
  		<name>set_allocated_groupsize</name>
  		<replaceName>GroupSize</replaceName>
  		<handler>descripter = pb_set_message_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_groupsize</name>
  		<replaceName>GroupSize</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline const ::pb::PbVector2_Int& groupsize() const;
  inline ::pb::PbVector2_Int* mutable_groupsize();
  inline ::pb::PbVector2_Int* release_groupsize();
  inline void set_allocated_groupsize(::pb::PbVector2_Int* groupsize);

  // repeated uint32 UnreplaceGridIndexArr = 5;
  inline int unreplacegridindexarr_size() const;
  inline void clear_unreplacegridindexarr();
  static const int kUnreplaceGridIndexArrFieldNumber = 5;
  /*FOR2LUA
  <Record>
  	<name>OrnamentGroupConf</name>
  	<Function>
  		<name>unreplacegridindexarr</name>
  		<replaceName>UnreplaceGridIndexArr</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>mutable_unreplacegridindexarr</name>
  		<replaceName>UnreplaceGridIndexArr</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>add_unreplacegridindexarr</name>
  		<replaceName>UnreplaceGridIndexArr</replaceName>
  		<handler>descripter = pb_repeated_add_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_unreplacegridindexarr</name>
  		<replaceName>UnreplaceGridIndexArr</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  	<Function>
  		<name>unreplacegridindexarr_size</name>
  		<replaceName>UnreplaceGridIndexArr</replaceName>
  		<handler>descripter = pb_repeated_size_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline ::google::protobuf::uint32 unreplacegridindexarr(int index) const;
  inline void set_unreplacegridindexarr(int index, ::google::protobuf::uint32 value);
  inline void add_unreplacegridindexarr(::google::protobuf::uint32 value);
  inline const ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >&
      unreplacegridindexarr() const;
  inline ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >*
      mutable_unreplacegridindexarr();

  // optional int32 ShowPriority = 6;
  inline bool has_showpriority() const;
  inline void clear_showpriority();
  static const int kShowPriorityFieldNumber = 6;
  /*FOR2LUA
  <Record>
  	<name>OrnamentGroupConf</name>
  	<Function>
  		<name>showpriority</name>
  		<replaceName>ShowPriority</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>set_showpriority</name>
  		<replaceName>ShowPriority</replaceName>
  		<handler>descripter = pb_set_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_showpriority</name>
  		<replaceName>ShowPriority</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline ::google::protobuf::int32 showpriority() const;
  inline void set_showpriority(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:pb.OrnamentGroupConf)
 private:
  inline void set_has_id();
  inline void clear_has_id();
  inline void set_has_name();
  inline void clear_has_name();
  inline void set_has_assetpath();
  inline void clear_has_assetpath();
  inline void set_has_groupsize();
  inline void clear_has_groupsize();
  inline void set_has_showpriority();
  inline void clear_has_showpriority();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::std::string* name_;
  ::std::string* assetpath_;
  ::google::protobuf::int32 id_;
  ::google::protobuf::int32 showpriority_;
  ::pb::PbVector2_Int* groupsize_;
  ::google::protobuf::RepeatedField< ::google::protobuf::uint32 > unreplacegridindexarr_;
  friend void  protobuf_AddDesc_module_2fOrnamentGroupConf_2eproto();
  friend void protobuf_AssignDesc_module_2fOrnamentGroupConf_2eproto();
  friend void protobuf_ShutdownFile_module_2fOrnamentGroupConf_2eproto();

  void InitAsDefaultInstance();
  static OrnamentGroupConf* default_instance_;
};
// ===================================================================


// ===================================================================

// OrnamentGroupConf

// required int32 Id = 1;
inline bool OrnamentGroupConf::has_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void OrnamentGroupConf::set_has_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void OrnamentGroupConf::clear_has_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void OrnamentGroupConf::clear_id() {
  id_ = 0;
  clear_has_id();
}
inline ::google::protobuf::int32 OrnamentGroupConf::id() const {
  // @@protoc_insertion_point(field_get:pb.OrnamentGroupConf.Id)
  return id_;
}
inline void OrnamentGroupConf::set_id(::google::protobuf::int32 value) {
  set_has_id();
  id_ = value;
  // @@protoc_insertion_point(field_set:pb.OrnamentGroupConf.Id)
}

// optional string Name = 2;
inline bool OrnamentGroupConf::has_name() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void OrnamentGroupConf::set_has_name() {
  _has_bits_[0] |= 0x00000002u;
}
inline void OrnamentGroupConf::clear_has_name() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void OrnamentGroupConf::clear_name() {
  if (name_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    name_->clear();
  }
  clear_has_name();
}
inline const ::std::string& OrnamentGroupConf::name() const {
  // @@protoc_insertion_point(field_get:pb.OrnamentGroupConf.Name)
  return *name_;
}
inline void OrnamentGroupConf::set_name(const ::std::string& value) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    name_ = new ::std::string;
  }
  name_->assign(value);
  // @@protoc_insertion_point(field_set:pb.OrnamentGroupConf.Name)
}
inline void OrnamentGroupConf::set_name(const char* value) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    name_ = new ::std::string;
  }
  name_->assign(value);
  // @@protoc_insertion_point(field_set_char:pb.OrnamentGroupConf.Name)
}
inline void OrnamentGroupConf::set_name(const char* value, size_t size) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    name_ = new ::std::string;
  }
  name_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:pb.OrnamentGroupConf.Name)
}
inline ::std::string* OrnamentGroupConf::mutable_name() {
  set_has_name();
  if (name_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    name_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:pb.OrnamentGroupConf.Name)
  return name_;
}
inline ::std::string* OrnamentGroupConf::release_name() {
  clear_has_name();
  if (name_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = name_;
    name_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void OrnamentGroupConf::set_allocated_name(::std::string* name) {
  if (name_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete name_;
  }
  if (name) {
    set_has_name();
    name_ = name;
  } else {
    clear_has_name();
    name_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:pb.OrnamentGroupConf.Name)
}

// optional string AssetPath = 3;
inline bool OrnamentGroupConf::has_assetpath() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void OrnamentGroupConf::set_has_assetpath() {
  _has_bits_[0] |= 0x00000004u;
}
inline void OrnamentGroupConf::clear_has_assetpath() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void OrnamentGroupConf::clear_assetpath() {
  if (assetpath_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    assetpath_->clear();
  }
  clear_has_assetpath();
}
inline const ::std::string& OrnamentGroupConf::assetpath() const {
  // @@protoc_insertion_point(field_get:pb.OrnamentGroupConf.AssetPath)
  return *assetpath_;
}
inline void OrnamentGroupConf::set_assetpath(const ::std::string& value) {
  set_has_assetpath();
  if (assetpath_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    assetpath_ = new ::std::string;
  }
  assetpath_->assign(value);
  // @@protoc_insertion_point(field_set:pb.OrnamentGroupConf.AssetPath)
}
inline void OrnamentGroupConf::set_assetpath(const char* value) {
  set_has_assetpath();
  if (assetpath_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    assetpath_ = new ::std::string;
  }
  assetpath_->assign(value);
  // @@protoc_insertion_point(field_set_char:pb.OrnamentGroupConf.AssetPath)
}
inline void OrnamentGroupConf::set_assetpath(const char* value, size_t size) {
  set_has_assetpath();
  if (assetpath_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    assetpath_ = new ::std::string;
  }
  assetpath_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:pb.OrnamentGroupConf.AssetPath)
}
inline ::std::string* OrnamentGroupConf::mutable_assetpath() {
  set_has_assetpath();
  if (assetpath_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    assetpath_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:pb.OrnamentGroupConf.AssetPath)
  return assetpath_;
}
inline ::std::string* OrnamentGroupConf::release_assetpath() {
  clear_has_assetpath();
  if (assetpath_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = assetpath_;
    assetpath_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void OrnamentGroupConf::set_allocated_assetpath(::std::string* assetpath) {
  if (assetpath_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete assetpath_;
  }
  if (assetpath) {
    set_has_assetpath();
    assetpath_ = assetpath;
  } else {
    clear_has_assetpath();
    assetpath_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:pb.OrnamentGroupConf.AssetPath)
}

// optional .pb.PbVector2_Int GroupSize = 4;
inline bool OrnamentGroupConf::has_groupsize() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void OrnamentGroupConf::set_has_groupsize() {
  _has_bits_[0] |= 0x00000008u;
}
inline void OrnamentGroupConf::clear_has_groupsize() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void OrnamentGroupConf::clear_groupsize() {
  if (groupsize_ != NULL) groupsize_->::pb::PbVector2_Int::Clear();
  clear_has_groupsize();
}
inline const ::pb::PbVector2_Int& OrnamentGroupConf::groupsize() const {
  // @@protoc_insertion_point(field_get:pb.OrnamentGroupConf.GroupSize)
  return groupsize_ != NULL ? *groupsize_ : *default_instance_->groupsize_;
}
inline ::pb::PbVector2_Int* OrnamentGroupConf::mutable_groupsize() {
  set_has_groupsize();
  if (groupsize_ == NULL) groupsize_ = new ::pb::PbVector2_Int;
  // @@protoc_insertion_point(field_mutable:pb.OrnamentGroupConf.GroupSize)
  return groupsize_;
}
inline ::pb::PbVector2_Int* OrnamentGroupConf::release_groupsize() {
  clear_has_groupsize();
  ::pb::PbVector2_Int* temp = groupsize_;
  groupsize_ = NULL;
  return temp;
}
inline void OrnamentGroupConf::set_allocated_groupsize(::pb::PbVector2_Int* groupsize) {
  delete groupsize_;
  groupsize_ = groupsize;
  if (groupsize) {
    set_has_groupsize();
  } else {
    clear_has_groupsize();
  }
  // @@protoc_insertion_point(field_set_allocated:pb.OrnamentGroupConf.GroupSize)
}

// repeated uint32 UnreplaceGridIndexArr = 5;
inline int OrnamentGroupConf::unreplacegridindexarr_size() const {
  return unreplacegridindexarr_.size();
}
inline void OrnamentGroupConf::clear_unreplacegridindexarr() {
  unreplacegridindexarr_.Clear();
}
inline ::google::protobuf::uint32 OrnamentGroupConf::unreplacegridindexarr(int index) const {
  // @@protoc_insertion_point(field_get:pb.OrnamentGroupConf.UnreplaceGridIndexArr)
  return unreplacegridindexarr_.Get(index);
}
inline void OrnamentGroupConf::set_unreplacegridindexarr(int index, ::google::protobuf::uint32 value) {
  unreplacegridindexarr_.Set(index, value);
  // @@protoc_insertion_point(field_set:pb.OrnamentGroupConf.UnreplaceGridIndexArr)
}
inline void OrnamentGroupConf::add_unreplacegridindexarr(::google::protobuf::uint32 value) {
  unreplacegridindexarr_.Add(value);
  // @@protoc_insertion_point(field_add:pb.OrnamentGroupConf.UnreplaceGridIndexArr)
}
inline const ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >&
OrnamentGroupConf::unreplacegridindexarr() const {
  // @@protoc_insertion_point(field_list:pb.OrnamentGroupConf.UnreplaceGridIndexArr)
  return unreplacegridindexarr_;
}
inline ::google::protobuf::RepeatedField< ::google::protobuf::uint32 >*
OrnamentGroupConf::mutable_unreplacegridindexarr() {
  // @@protoc_insertion_point(field_mutable_list:pb.OrnamentGroupConf.UnreplaceGridIndexArr)
  return &unreplacegridindexarr_;
}

// optional int32 ShowPriority = 6;
inline bool OrnamentGroupConf::has_showpriority() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void OrnamentGroupConf::set_has_showpriority() {
  _has_bits_[0] |= 0x00000020u;
}
inline void OrnamentGroupConf::clear_has_showpriority() {
  _has_bits_[0] &= ~0x00000020u;
}
inline void OrnamentGroupConf::clear_showpriority() {
  showpriority_ = 0;
  clear_has_showpriority();
}
inline ::google::protobuf::int32 OrnamentGroupConf::showpriority() const {
  // @@protoc_insertion_point(field_get:pb.OrnamentGroupConf.ShowPriority)
  return showpriority_;
}
inline void OrnamentGroupConf::set_showpriority(::google::protobuf::int32 value) {
  set_has_showpriority();
  showpriority_ = value;
  // @@protoc_insertion_point(field_set:pb.OrnamentGroupConf.ShowPriority)
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

#endif  // PROTOBUF_module_2fOrnamentGroupConf_2eproto__INCLUDED
