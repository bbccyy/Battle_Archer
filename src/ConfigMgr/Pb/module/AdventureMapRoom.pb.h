// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: module/AdventureMapRoom.proto

#ifndef PROTOBUF_module_2fAdventureMapRoom_2eproto__INCLUDED
#define PROTOBUF_module_2fAdventureMapRoom_2eproto__INCLUDED

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
#include "module/AdventureMap.pb.h"
// @@protoc_insertion_point(includes)

namespace pb {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_module_2fAdventureMapRoom_2eproto();
void protobuf_AssignDesc_module_2fAdventureMapRoom_2eproto();
void protobuf_ShutdownFile_module_2fAdventureMapRoom_2eproto();

class AdventureMapRoom;

// ===================================================================

/*FOR2LUA
<Record>
	<name>AdventureMapRoom</name>
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
		<replaceName>module/AdventureMapRoom.proto</replaceName>
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
class AdventureMapRoom : public ::google::protobuf::Message {
 public:
  AdventureMapRoom();
  virtual ~AdventureMapRoom();

  AdventureMapRoom(const AdventureMapRoom& from);

  inline AdventureMapRoom& operator=(const AdventureMapRoom& from) {
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
  static const AdventureMapRoom& default_instance();

  void Swap(AdventureMapRoom* other);

  // implements Message ----------------------------------------------

  AdventureMapRoom* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const AdventureMapRoom& from);
  void MergeFrom(const AdventureMapRoom& from);
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

  // optional uint64 Id = 1;
  inline bool has_id() const;
  inline void clear_id();
  static const int kIdFieldNumber = 1;
  /*FOR2LUA
  <Record>
  	<name>AdventureMapRoom</name>
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
  inline ::google::protobuf::uint64 id() const;
  inline void set_id(::google::protobuf::uint64 value);

  // optional string RoomName = 2;
  inline bool has_roomname() const;
  inline void clear_roomname();
  static const int kRoomNameFieldNumber = 2;
  /*FOR2LUA
  <Record>
  	<name>AdventureMapRoom</name>
  	<Function>
  		<name>roomname</name>
  		<replaceName>RoomName</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>set_roomname</name>
  		<replaceName>RoomName</replaceName>
  		<handler>descripter = pb_set_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_roomname</name>
  		<replaceName>RoomName</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline const ::std::string& roomname() const;
  inline void set_roomname(const ::std::string& value);
  inline void set_roomname(const char* value);
  inline void set_roomname(const char* value, size_t size);
  inline ::std::string* mutable_roomname();
  inline ::std::string* release_roomname();
  inline void set_allocated_roomname(::std::string* roomname);

  // repeated .pb.AdventureBlock BlockArr = 3;
  inline int blockarr_size() const;
  inline void clear_blockarr();
  static const int kBlockArrFieldNumber = 3;
  /*FOR2LUA
  <Record>
  	<name>AdventureMapRoom</name>
  	<Function>
  		<name>blockarr</name>
  		<replaceName>BlockArr</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>mutable_blockarr</name>
  		<replaceName>BlockArr</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>add_blockarr</name>
  		<replaceName>BlockArr</replaceName>
  		<handler>descripter = pb_repeated_add_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_blockarr</name>
  		<replaceName>BlockArr</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  	<Function>
  		<name>blockarr_size</name>
  		<replaceName>BlockArr</replaceName>
  		<handler>descripter = pb_repeated_size_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline const ::pb::AdventureBlock& blockarr(int index) const;
  inline ::pb::AdventureBlock* mutable_blockarr(int index);
  inline ::pb::AdventureBlock* add_blockarr();
  inline const ::google::protobuf::RepeatedPtrField< ::pb::AdventureBlock >&
      blockarr() const;
  inline ::google::protobuf::RepeatedPtrField< ::pb::AdventureBlock >*
      mutable_blockarr();

  // repeated .pb.AdventureObject ObjectArr = 4;
  inline int objectarr_size() const;
  inline void clear_objectarr();
  static const int kObjectArrFieldNumber = 4;
  /*FOR2LUA
  <Record>
  	<name>AdventureMapRoom</name>
  	<Function>
  		<name>objectarr</name>
  		<replaceName>ObjectArr</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>mutable_objectarr</name>
  		<replaceName>ObjectArr</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>add_objectarr</name>
  		<replaceName>ObjectArr</replaceName>
  		<handler>descripter = pb_repeated_add_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_objectarr</name>
  		<replaceName>ObjectArr</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  	<Function>
  		<name>objectarr_size</name>
  		<replaceName>ObjectArr</replaceName>
  		<handler>descripter = pb_repeated_size_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline const ::pb::AdventureObject& objectarr(int index) const;
  inline ::pb::AdventureObject* mutable_objectarr(int index);
  inline ::pb::AdventureObject* add_objectarr();
  inline const ::google::protobuf::RepeatedPtrField< ::pb::AdventureObject >&
      objectarr() const;
  inline ::google::protobuf::RepeatedPtrField< ::pb::AdventureObject >*
      mutable_objectarr();

  // optional .pb.PbVector2_Int LayerSize = 5;
  inline bool has_layersize() const;
  inline void clear_layersize();
  static const int kLayerSizeFieldNumber = 5;
  /*FOR2LUA
  <Record>
  	<name>AdventureMapRoom</name>
  	<Function>
  		<name>layersize</name>
  		<replaceName>LayerSize</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>set_layersize</name>
  		<replaceName>LayerSize</replaceName>
  		<handler>descripter = pb_set_message_cpp()</handler>
  	</Function>
  	<Function>
  		<name>set_allocated_layersize</name>
  		<replaceName>LayerSize</replaceName>
  		<handler>descripter = pb_set_message_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_layersize</name>
  		<replaceName>LayerSize</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline const ::pb::PbVector2_Int& layersize() const;
  inline ::pb::PbVector2_Int* mutable_layersize();
  inline ::pb::PbVector2_Int* release_layersize();
  inline void set_allocated_layersize(::pb::PbVector2_Int* layersize);

  // repeated .pb.PbVector2_Int LinkPosArr = 6;
  inline int linkposarr_size() const;
  inline void clear_linkposarr();
  static const int kLinkPosArrFieldNumber = 6;
  /*FOR2LUA
  <Record>
  	<name>AdventureMapRoom</name>
  	<Function>
  		<name>linkposarr</name>
  		<replaceName>LinkPosArr</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>mutable_linkposarr</name>
  		<replaceName>LinkPosArr</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>add_linkposarr</name>
  		<replaceName>LinkPosArr</replaceName>
  		<handler>descripter = pb_repeated_add_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_linkposarr</name>
  		<replaceName>LinkPosArr</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  	<Function>
  		<name>linkposarr_size</name>
  		<replaceName>LinkPosArr</replaceName>
  		<handler>descripter = pb_repeated_size_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline const ::pb::PbVector2_Int& linkposarr(int index) const;
  inline ::pb::PbVector2_Int* mutable_linkposarr(int index);
  inline ::pb::PbVector2_Int* add_linkposarr();
  inline const ::google::protobuf::RepeatedPtrField< ::pb::PbVector2_Int >&
      linkposarr() const;
  inline ::google::protobuf::RepeatedPtrField< ::pb::PbVector2_Int >*
      mutable_linkposarr();

  // repeated .pb.TrapResetPoint TrapPosArr = 7;
  inline int trapposarr_size() const;
  inline void clear_trapposarr();
  static const int kTrapPosArrFieldNumber = 7;
  /*FOR2LUA
  <Record>
  	<name>AdventureMapRoom</name>
  	<Function>
  		<name>trapposarr</name>
  		<replaceName>TrapPosArr</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>mutable_trapposarr</name>
  		<replaceName>TrapPosArr</replaceName>
  		<handler>descripter = pb_cpp()</handler>
  	</Function>
  	<Function>
  		<name>add_trapposarr</name>
  		<replaceName>TrapPosArr</replaceName>
  		<handler>descripter = pb_repeated_add_cpp()</handler>
  	</Function>
  	<Function>
  		<name>has_trapposarr</name>
  		<replaceName>TrapPosArr</replaceName>
  		<handler>descripter = pb_has_cpp()</handler>
  	</Function>
  	<Function>
  		<name>trapposarr_size</name>
  		<replaceName>TrapPosArr</replaceName>
  		<handler>descripter = pb_repeated_size_cpp()</handler>
  	</Function>
  </Record>
  FOR2LUA*/
  inline const ::pb::TrapResetPoint& trapposarr(int index) const;
  inline ::pb::TrapResetPoint* mutable_trapposarr(int index);
  inline ::pb::TrapResetPoint* add_trapposarr();
  inline const ::google::protobuf::RepeatedPtrField< ::pb::TrapResetPoint >&
      trapposarr() const;
  inline ::google::protobuf::RepeatedPtrField< ::pb::TrapResetPoint >*
      mutable_trapposarr();

  // @@protoc_insertion_point(class_scope:pb.AdventureMapRoom)
 private:
  inline void set_has_id();
  inline void clear_has_id();
  inline void set_has_roomname();
  inline void clear_has_roomname();
  inline void set_has_layersize();
  inline void clear_has_layersize();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::uint64 id_;
  ::std::string* roomname_;
  ::google::protobuf::RepeatedPtrField< ::pb::AdventureBlock > blockarr_;
  ::google::protobuf::RepeatedPtrField< ::pb::AdventureObject > objectarr_;
  ::pb::PbVector2_Int* layersize_;
  ::google::protobuf::RepeatedPtrField< ::pb::PbVector2_Int > linkposarr_;
  ::google::protobuf::RepeatedPtrField< ::pb::TrapResetPoint > trapposarr_;
  friend void  protobuf_AddDesc_module_2fAdventureMapRoom_2eproto();
  friend void protobuf_AssignDesc_module_2fAdventureMapRoom_2eproto();
  friend void protobuf_ShutdownFile_module_2fAdventureMapRoom_2eproto();

  void InitAsDefaultInstance();
  static AdventureMapRoom* default_instance_;
};
// ===================================================================


// ===================================================================

// AdventureMapRoom

// optional uint64 Id = 1;
inline bool AdventureMapRoom::has_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void AdventureMapRoom::set_has_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void AdventureMapRoom::clear_has_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void AdventureMapRoom::clear_id() {
  id_ = GOOGLE_ULONGLONG(0);
  clear_has_id();
}
inline ::google::protobuf::uint64 AdventureMapRoom::id() const {
  // @@protoc_insertion_point(field_get:pb.AdventureMapRoom.Id)
  return id_;
}
inline void AdventureMapRoom::set_id(::google::protobuf::uint64 value) {
  set_has_id();
  id_ = value;
  // @@protoc_insertion_point(field_set:pb.AdventureMapRoom.Id)
}

// optional string RoomName = 2;
inline bool AdventureMapRoom::has_roomname() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void AdventureMapRoom::set_has_roomname() {
  _has_bits_[0] |= 0x00000002u;
}
inline void AdventureMapRoom::clear_has_roomname() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void AdventureMapRoom::clear_roomname() {
  if (roomname_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    roomname_->clear();
  }
  clear_has_roomname();
}
inline const ::std::string& AdventureMapRoom::roomname() const {
  // @@protoc_insertion_point(field_get:pb.AdventureMapRoom.RoomName)
  return *roomname_;
}
inline void AdventureMapRoom::set_roomname(const ::std::string& value) {
  set_has_roomname();
  if (roomname_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    roomname_ = new ::std::string;
  }
  roomname_->assign(value);
  // @@protoc_insertion_point(field_set:pb.AdventureMapRoom.RoomName)
}
inline void AdventureMapRoom::set_roomname(const char* value) {
  set_has_roomname();
  if (roomname_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    roomname_ = new ::std::string;
  }
  roomname_->assign(value);
  // @@protoc_insertion_point(field_set_char:pb.AdventureMapRoom.RoomName)
}
inline void AdventureMapRoom::set_roomname(const char* value, size_t size) {
  set_has_roomname();
  if (roomname_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    roomname_ = new ::std::string;
  }
  roomname_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:pb.AdventureMapRoom.RoomName)
}
inline ::std::string* AdventureMapRoom::mutable_roomname() {
  set_has_roomname();
  if (roomname_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    roomname_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:pb.AdventureMapRoom.RoomName)
  return roomname_;
}
inline ::std::string* AdventureMapRoom::release_roomname() {
  clear_has_roomname();
  if (roomname_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = roomname_;
    roomname_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void AdventureMapRoom::set_allocated_roomname(::std::string* roomname) {
  if (roomname_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete roomname_;
  }
  if (roomname) {
    set_has_roomname();
    roomname_ = roomname;
  } else {
    clear_has_roomname();
    roomname_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:pb.AdventureMapRoom.RoomName)
}

// repeated .pb.AdventureBlock BlockArr = 3;
inline int AdventureMapRoom::blockarr_size() const {
  return blockarr_.size();
}
inline void AdventureMapRoom::clear_blockarr() {
  blockarr_.Clear();
}
inline const ::pb::AdventureBlock& AdventureMapRoom::blockarr(int index) const {
  // @@protoc_insertion_point(field_get:pb.AdventureMapRoom.BlockArr)
  return blockarr_.Get(index);
}
inline ::pb::AdventureBlock* AdventureMapRoom::mutable_blockarr(int index) {
  // @@protoc_insertion_point(field_mutable:pb.AdventureMapRoom.BlockArr)
  return blockarr_.Mutable(index);
}
inline ::pb::AdventureBlock* AdventureMapRoom::add_blockarr() {
  // @@protoc_insertion_point(field_add:pb.AdventureMapRoom.BlockArr)
  return blockarr_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::pb::AdventureBlock >&
AdventureMapRoom::blockarr() const {
  // @@protoc_insertion_point(field_list:pb.AdventureMapRoom.BlockArr)
  return blockarr_;
}
inline ::google::protobuf::RepeatedPtrField< ::pb::AdventureBlock >*
AdventureMapRoom::mutable_blockarr() {
  // @@protoc_insertion_point(field_mutable_list:pb.AdventureMapRoom.BlockArr)
  return &blockarr_;
}

// repeated .pb.AdventureObject ObjectArr = 4;
inline int AdventureMapRoom::objectarr_size() const {
  return objectarr_.size();
}
inline void AdventureMapRoom::clear_objectarr() {
  objectarr_.Clear();
}
inline const ::pb::AdventureObject& AdventureMapRoom::objectarr(int index) const {
  // @@protoc_insertion_point(field_get:pb.AdventureMapRoom.ObjectArr)
  return objectarr_.Get(index);
}
inline ::pb::AdventureObject* AdventureMapRoom::mutable_objectarr(int index) {
  // @@protoc_insertion_point(field_mutable:pb.AdventureMapRoom.ObjectArr)
  return objectarr_.Mutable(index);
}
inline ::pb::AdventureObject* AdventureMapRoom::add_objectarr() {
  // @@protoc_insertion_point(field_add:pb.AdventureMapRoom.ObjectArr)
  return objectarr_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::pb::AdventureObject >&
AdventureMapRoom::objectarr() const {
  // @@protoc_insertion_point(field_list:pb.AdventureMapRoom.ObjectArr)
  return objectarr_;
}
inline ::google::protobuf::RepeatedPtrField< ::pb::AdventureObject >*
AdventureMapRoom::mutable_objectarr() {
  // @@protoc_insertion_point(field_mutable_list:pb.AdventureMapRoom.ObjectArr)
  return &objectarr_;
}

// optional .pb.PbVector2_Int LayerSize = 5;
inline bool AdventureMapRoom::has_layersize() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void AdventureMapRoom::set_has_layersize() {
  _has_bits_[0] |= 0x00000010u;
}
inline void AdventureMapRoom::clear_has_layersize() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void AdventureMapRoom::clear_layersize() {
  if (layersize_ != NULL) layersize_->::pb::PbVector2_Int::Clear();
  clear_has_layersize();
}
inline const ::pb::PbVector2_Int& AdventureMapRoom::layersize() const {
  // @@protoc_insertion_point(field_get:pb.AdventureMapRoom.LayerSize)
  return layersize_ != NULL ? *layersize_ : *default_instance_->layersize_;
}
inline ::pb::PbVector2_Int* AdventureMapRoom::mutable_layersize() {
  set_has_layersize();
  if (layersize_ == NULL) layersize_ = new ::pb::PbVector2_Int;
  // @@protoc_insertion_point(field_mutable:pb.AdventureMapRoom.LayerSize)
  return layersize_;
}
inline ::pb::PbVector2_Int* AdventureMapRoom::release_layersize() {
  clear_has_layersize();
  ::pb::PbVector2_Int* temp = layersize_;
  layersize_ = NULL;
  return temp;
}
inline void AdventureMapRoom::set_allocated_layersize(::pb::PbVector2_Int* layersize) {
  delete layersize_;
  layersize_ = layersize;
  if (layersize) {
    set_has_layersize();
  } else {
    clear_has_layersize();
  }
  // @@protoc_insertion_point(field_set_allocated:pb.AdventureMapRoom.LayerSize)
}

// repeated .pb.PbVector2_Int LinkPosArr = 6;
inline int AdventureMapRoom::linkposarr_size() const {
  return linkposarr_.size();
}
inline void AdventureMapRoom::clear_linkposarr() {
  linkposarr_.Clear();
}
inline const ::pb::PbVector2_Int& AdventureMapRoom::linkposarr(int index) const {
  // @@protoc_insertion_point(field_get:pb.AdventureMapRoom.LinkPosArr)
  return linkposarr_.Get(index);
}
inline ::pb::PbVector2_Int* AdventureMapRoom::mutable_linkposarr(int index) {
  // @@protoc_insertion_point(field_mutable:pb.AdventureMapRoom.LinkPosArr)
  return linkposarr_.Mutable(index);
}
inline ::pb::PbVector2_Int* AdventureMapRoom::add_linkposarr() {
  // @@protoc_insertion_point(field_add:pb.AdventureMapRoom.LinkPosArr)
  return linkposarr_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::pb::PbVector2_Int >&
AdventureMapRoom::linkposarr() const {
  // @@protoc_insertion_point(field_list:pb.AdventureMapRoom.LinkPosArr)
  return linkposarr_;
}
inline ::google::protobuf::RepeatedPtrField< ::pb::PbVector2_Int >*
AdventureMapRoom::mutable_linkposarr() {
  // @@protoc_insertion_point(field_mutable_list:pb.AdventureMapRoom.LinkPosArr)
  return &linkposarr_;
}

// repeated .pb.TrapResetPoint TrapPosArr = 7;
inline int AdventureMapRoom::trapposarr_size() const {
  return trapposarr_.size();
}
inline void AdventureMapRoom::clear_trapposarr() {
  trapposarr_.Clear();
}
inline const ::pb::TrapResetPoint& AdventureMapRoom::trapposarr(int index) const {
  // @@protoc_insertion_point(field_get:pb.AdventureMapRoom.TrapPosArr)
  return trapposarr_.Get(index);
}
inline ::pb::TrapResetPoint* AdventureMapRoom::mutable_trapposarr(int index) {
  // @@protoc_insertion_point(field_mutable:pb.AdventureMapRoom.TrapPosArr)
  return trapposarr_.Mutable(index);
}
inline ::pb::TrapResetPoint* AdventureMapRoom::add_trapposarr() {
  // @@protoc_insertion_point(field_add:pb.AdventureMapRoom.TrapPosArr)
  return trapposarr_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::pb::TrapResetPoint >&
AdventureMapRoom::trapposarr() const {
  // @@protoc_insertion_point(field_list:pb.AdventureMapRoom.TrapPosArr)
  return trapposarr_;
}
inline ::google::protobuf::RepeatedPtrField< ::pb::TrapResetPoint >*
AdventureMapRoom::mutable_trapposarr() {
  // @@protoc_insertion_point(field_mutable_list:pb.AdventureMapRoom.TrapPosArr)
  return &trapposarr_;
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

#endif  // PROTOBUF_module_2fAdventureMapRoom_2eproto__INCLUDED