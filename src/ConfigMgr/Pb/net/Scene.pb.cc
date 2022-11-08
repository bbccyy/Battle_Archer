// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: net/Scene.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "net/Scene.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace pb {

namespace {

const ::google::protobuf::Descriptor* TSceneGetSceneIdByTypeReq_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  TSceneGetSceneIdByTypeReq_reflection_ = NULL;
const ::google::protobuf::Descriptor* TSceneGetSceneIdByTypeRsp_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  TSceneGetSceneIdByTypeRsp_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_net_2fScene_2eproto() {
  protobuf_AddDesc_net_2fScene_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "net/Scene.proto");
  GOOGLE_CHECK(file != NULL);
  TSceneGetSceneIdByTypeReq_descriptor_ = file->message_type(0);
  static const int TSceneGetSceneIdByTypeReq_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TSceneGetSceneIdByTypeReq, scenetype_),
  };
  TSceneGetSceneIdByTypeReq_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      TSceneGetSceneIdByTypeReq_descriptor_,
      TSceneGetSceneIdByTypeReq::default_instance_,
      TSceneGetSceneIdByTypeReq_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TSceneGetSceneIdByTypeReq, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TSceneGetSceneIdByTypeReq, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(TSceneGetSceneIdByTypeReq));
  TSceneGetSceneIdByTypeRsp_descriptor_ = file->message_type(1);
  static const int TSceneGetSceneIdByTypeRsp_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TSceneGetSceneIdByTypeRsp, sceneid_),
  };
  TSceneGetSceneIdByTypeRsp_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      TSceneGetSceneIdByTypeRsp_descriptor_,
      TSceneGetSceneIdByTypeRsp::default_instance_,
      TSceneGetSceneIdByTypeRsp_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TSceneGetSceneIdByTypeRsp, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TSceneGetSceneIdByTypeRsp, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(TSceneGetSceneIdByTypeRsp));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_net_2fScene_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    TSceneGetSceneIdByTypeReq_descriptor_, &TSceneGetSceneIdByTypeReq::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    TSceneGetSceneIdByTypeRsp_descriptor_, &TSceneGetSceneIdByTypeRsp::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_net_2fScene_2eproto() {
  delete TSceneGetSceneIdByTypeReq::default_instance_;
  delete TSceneGetSceneIdByTypeReq_reflection_;
  delete TSceneGetSceneIdByTypeRsp::default_instance_;
  delete TSceneGetSceneIdByTypeRsp_reflection_;
}

void protobuf_AddDesc_net_2fScene_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\017net/Scene.proto\022\002pb\".\n\031TSceneGetSceneI"
    "dByTypeReq\022\021\n\tSceneType\030\001 \001(\t\",\n\031TSceneG"
    "etSceneIdByTypeRsp\022\017\n\007SceneId\030\001 \001(\t", 115);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "net/Scene.proto", &protobuf_RegisterTypes);
  TSceneGetSceneIdByTypeReq::default_instance_ = new TSceneGetSceneIdByTypeReq();
  TSceneGetSceneIdByTypeRsp::default_instance_ = new TSceneGetSceneIdByTypeRsp();
  TSceneGetSceneIdByTypeReq::default_instance_->InitAsDefaultInstance();
  TSceneGetSceneIdByTypeRsp::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_net_2fScene_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_net_2fScene_2eproto {
  StaticDescriptorInitializer_net_2fScene_2eproto() {
    protobuf_AddDesc_net_2fScene_2eproto();
  }
} static_descriptor_initializer_net_2fScene_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int TSceneGetSceneIdByTypeReq::kSceneTypeFieldNumber;
#endif  // !_MSC_VER

TSceneGetSceneIdByTypeReq::TSceneGetSceneIdByTypeReq()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:pb.TSceneGetSceneIdByTypeReq)
}

void TSceneGetSceneIdByTypeReq::InitAsDefaultInstance() {
}

TSceneGetSceneIdByTypeReq::TSceneGetSceneIdByTypeReq(const TSceneGetSceneIdByTypeReq& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:pb.TSceneGetSceneIdByTypeReq)
}

void TSceneGetSceneIdByTypeReq::SharedCtor() {
  ::google::protobuf::internal::GetEmptyString();
  _cached_size_ = 0;
  scenetype_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

TSceneGetSceneIdByTypeReq::~TSceneGetSceneIdByTypeReq() {
  // @@protoc_insertion_point(destructor:pb.TSceneGetSceneIdByTypeReq)
  SharedDtor();
}

void TSceneGetSceneIdByTypeReq::SharedDtor() {
  if (scenetype_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete scenetype_;
  }
  if (this != default_instance_) {
  }
}

void TSceneGetSceneIdByTypeReq::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* TSceneGetSceneIdByTypeReq::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return TSceneGetSceneIdByTypeReq_descriptor_;
}

const TSceneGetSceneIdByTypeReq& TSceneGetSceneIdByTypeReq::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_net_2fScene_2eproto();
  return *default_instance_;
}

TSceneGetSceneIdByTypeReq* TSceneGetSceneIdByTypeReq::default_instance_ = NULL;

TSceneGetSceneIdByTypeReq* TSceneGetSceneIdByTypeReq::New() const {
  return new TSceneGetSceneIdByTypeReq;
}

void TSceneGetSceneIdByTypeReq::Clear() {
  if (has_scenetype()) {
    if (scenetype_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
      scenetype_->clear();
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool TSceneGetSceneIdByTypeReq::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:pb.TSceneGetSceneIdByTypeReq)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional string SceneType = 1;
      case 1: {
        if (tag == 10) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_scenetype()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->scenetype().data(), this->scenetype().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "scenetype");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectAtEnd()) goto success;
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:pb.TSceneGetSceneIdByTypeReq)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:pb.TSceneGetSceneIdByTypeReq)
  return false;
#undef DO_
}

void TSceneGetSceneIdByTypeReq::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:pb.TSceneGetSceneIdByTypeReq)
  // optional string SceneType = 1;
  if (has_scenetype()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->scenetype().data(), this->scenetype().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "scenetype");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      1, this->scenetype(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:pb.TSceneGetSceneIdByTypeReq)
}

::google::protobuf::uint8* TSceneGetSceneIdByTypeReq::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:pb.TSceneGetSceneIdByTypeReq)
  // optional string SceneType = 1;
  if (has_scenetype()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->scenetype().data(), this->scenetype().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "scenetype");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        1, this->scenetype(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:pb.TSceneGetSceneIdByTypeReq)
  return target;
}

int TSceneGetSceneIdByTypeReq::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional string SceneType = 1;
    if (has_scenetype()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->scenetype());
    }

  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void TSceneGetSceneIdByTypeReq::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const TSceneGetSceneIdByTypeReq* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const TSceneGetSceneIdByTypeReq*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void TSceneGetSceneIdByTypeReq::MergeFrom(const TSceneGetSceneIdByTypeReq& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_scenetype()) {
      set_scenetype(from.scenetype());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void TSceneGetSceneIdByTypeReq::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void TSceneGetSceneIdByTypeReq::CopyFrom(const TSceneGetSceneIdByTypeReq& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool TSceneGetSceneIdByTypeReq::IsInitialized() const {

  return true;
}

void TSceneGetSceneIdByTypeReq::Swap(TSceneGetSceneIdByTypeReq* other) {
  if (other != this) {
    std::swap(scenetype_, other->scenetype_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata TSceneGetSceneIdByTypeReq::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = TSceneGetSceneIdByTypeReq_descriptor_;
  metadata.reflection = TSceneGetSceneIdByTypeReq_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int TSceneGetSceneIdByTypeRsp::kSceneIdFieldNumber;
#endif  // !_MSC_VER

TSceneGetSceneIdByTypeRsp::TSceneGetSceneIdByTypeRsp()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:pb.TSceneGetSceneIdByTypeRsp)
}

void TSceneGetSceneIdByTypeRsp::InitAsDefaultInstance() {
}

TSceneGetSceneIdByTypeRsp::TSceneGetSceneIdByTypeRsp(const TSceneGetSceneIdByTypeRsp& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:pb.TSceneGetSceneIdByTypeRsp)
}

void TSceneGetSceneIdByTypeRsp::SharedCtor() {
  ::google::protobuf::internal::GetEmptyString();
  _cached_size_ = 0;
  sceneid_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

TSceneGetSceneIdByTypeRsp::~TSceneGetSceneIdByTypeRsp() {
  // @@protoc_insertion_point(destructor:pb.TSceneGetSceneIdByTypeRsp)
  SharedDtor();
}

void TSceneGetSceneIdByTypeRsp::SharedDtor() {
  if (sceneid_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete sceneid_;
  }
  if (this != default_instance_) {
  }
}

void TSceneGetSceneIdByTypeRsp::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* TSceneGetSceneIdByTypeRsp::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return TSceneGetSceneIdByTypeRsp_descriptor_;
}

const TSceneGetSceneIdByTypeRsp& TSceneGetSceneIdByTypeRsp::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_net_2fScene_2eproto();
  return *default_instance_;
}

TSceneGetSceneIdByTypeRsp* TSceneGetSceneIdByTypeRsp::default_instance_ = NULL;

TSceneGetSceneIdByTypeRsp* TSceneGetSceneIdByTypeRsp::New() const {
  return new TSceneGetSceneIdByTypeRsp;
}

void TSceneGetSceneIdByTypeRsp::Clear() {
  if (has_sceneid()) {
    if (sceneid_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
      sceneid_->clear();
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool TSceneGetSceneIdByTypeRsp::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:pb.TSceneGetSceneIdByTypeRsp)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional string SceneId = 1;
      case 1: {
        if (tag == 10) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_sceneid()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->sceneid().data(), this->sceneid().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "sceneid");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectAtEnd()) goto success;
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:pb.TSceneGetSceneIdByTypeRsp)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:pb.TSceneGetSceneIdByTypeRsp)
  return false;
#undef DO_
}

void TSceneGetSceneIdByTypeRsp::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:pb.TSceneGetSceneIdByTypeRsp)
  // optional string SceneId = 1;
  if (has_sceneid()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->sceneid().data(), this->sceneid().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "sceneid");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      1, this->sceneid(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:pb.TSceneGetSceneIdByTypeRsp)
}

::google::protobuf::uint8* TSceneGetSceneIdByTypeRsp::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:pb.TSceneGetSceneIdByTypeRsp)
  // optional string SceneId = 1;
  if (has_sceneid()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->sceneid().data(), this->sceneid().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "sceneid");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        1, this->sceneid(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:pb.TSceneGetSceneIdByTypeRsp)
  return target;
}

int TSceneGetSceneIdByTypeRsp::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional string SceneId = 1;
    if (has_sceneid()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->sceneid());
    }

  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void TSceneGetSceneIdByTypeRsp::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const TSceneGetSceneIdByTypeRsp* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const TSceneGetSceneIdByTypeRsp*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void TSceneGetSceneIdByTypeRsp::MergeFrom(const TSceneGetSceneIdByTypeRsp& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_sceneid()) {
      set_sceneid(from.sceneid());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void TSceneGetSceneIdByTypeRsp::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void TSceneGetSceneIdByTypeRsp::CopyFrom(const TSceneGetSceneIdByTypeRsp& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool TSceneGetSceneIdByTypeRsp::IsInitialized() const {

  return true;
}

void TSceneGetSceneIdByTypeRsp::Swap(TSceneGetSceneIdByTypeRsp* other) {
  if (other != this) {
    std::swap(sceneid_, other->sceneid_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata TSceneGetSceneIdByTypeRsp::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = TSceneGetSceneIdByTypeRsp_descriptor_;
  metadata.reflection = TSceneGetSceneIdByTypeRsp_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace pb

// @@protoc_insertion_point(global_scope)
