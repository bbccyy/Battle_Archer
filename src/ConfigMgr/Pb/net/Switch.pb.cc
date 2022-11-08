// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: net/Switch.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "net/Switch.pb.h"

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

const ::google::protobuf::Descriptor* TSwitchGetSwitchInfoReq_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  TSwitchGetSwitchInfoReq_reflection_ = NULL;
const ::google::protobuf::Descriptor* TSwitchGetSwitchInfoRsp_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  TSwitchGetSwitchInfoRsp_reflection_ = NULL;
const ::google::protobuf::Descriptor* TSwitchUpdateSwitchInfoNotify_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  TSwitchUpdateSwitchInfoNotify_reflection_ = NULL;
const ::google::protobuf::Descriptor* TSwitch_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  TSwitch_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_net_2fSwitch_2eproto() {
  protobuf_AddDesc_net_2fSwitch_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "net/Switch.proto");
  GOOGLE_CHECK(file != NULL);
  TSwitchGetSwitchInfoReq_descriptor_ = file->message_type(0);
  static const int TSwitchGetSwitchInfoReq_offsets_[1] = {
  };
  TSwitchGetSwitchInfoReq_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      TSwitchGetSwitchInfoReq_descriptor_,
      TSwitchGetSwitchInfoReq::default_instance_,
      TSwitchGetSwitchInfoReq_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TSwitchGetSwitchInfoReq, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TSwitchGetSwitchInfoReq, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(TSwitchGetSwitchInfoReq));
  TSwitchGetSwitchInfoRsp_descriptor_ = file->message_type(1);
  static const int TSwitchGetSwitchInfoRsp_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TSwitchGetSwitchInfoRsp, info_),
  };
  TSwitchGetSwitchInfoRsp_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      TSwitchGetSwitchInfoRsp_descriptor_,
      TSwitchGetSwitchInfoRsp::default_instance_,
      TSwitchGetSwitchInfoRsp_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TSwitchGetSwitchInfoRsp, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TSwitchGetSwitchInfoRsp, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(TSwitchGetSwitchInfoRsp));
  TSwitchUpdateSwitchInfoNotify_descriptor_ = file->message_type(2);
  static const int TSwitchUpdateSwitchInfoNotify_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TSwitchUpdateSwitchInfoNotify, info_),
  };
  TSwitchUpdateSwitchInfoNotify_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      TSwitchUpdateSwitchInfoNotify_descriptor_,
      TSwitchUpdateSwitchInfoNotify::default_instance_,
      TSwitchUpdateSwitchInfoNotify_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TSwitchUpdateSwitchInfoNotify, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TSwitchUpdateSwitchInfoNotify, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(TSwitchUpdateSwitchInfoNotify));
  TSwitch_descriptor_ = file->message_type(3);
  static const int TSwitch_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TSwitch, combination_),
  };
  TSwitch_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      TSwitch_descriptor_,
      TSwitch::default_instance_,
      TSwitch_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TSwitch, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TSwitch, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(TSwitch));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_net_2fSwitch_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    TSwitchGetSwitchInfoReq_descriptor_, &TSwitchGetSwitchInfoReq::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    TSwitchGetSwitchInfoRsp_descriptor_, &TSwitchGetSwitchInfoRsp::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    TSwitchUpdateSwitchInfoNotify_descriptor_, &TSwitchUpdateSwitchInfoNotify::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    TSwitch_descriptor_, &TSwitch::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_net_2fSwitch_2eproto() {
  delete TSwitchGetSwitchInfoReq::default_instance_;
  delete TSwitchGetSwitchInfoReq_reflection_;
  delete TSwitchGetSwitchInfoRsp::default_instance_;
  delete TSwitchGetSwitchInfoRsp_reflection_;
  delete TSwitchUpdateSwitchInfoNotify::default_instance_;
  delete TSwitchUpdateSwitchInfoNotify_reflection_;
  delete TSwitch::default_instance_;
  delete TSwitch_reflection_;
}

void protobuf_AddDesc_net_2fSwitch_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\020net/Switch.proto\022\002pb\"\031\n\027TSwitchGetSwit"
    "chInfoReq\"4\n\027TSwitchGetSwitchInfoRsp\022\031\n\004"
    "Info\030\001 \001(\0132\013.pb.TSwitch\":\n\035TSwitchUpdate"
    "SwitchInfoNotify\022\031\n\004Info\030\001 \001(\0132\013.pb.TSwi"
    "tch\"\036\n\007TSwitch\022\023\n\013Combination\030\001 \001(\010", 195);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "net/Switch.proto", &protobuf_RegisterTypes);
  TSwitchGetSwitchInfoReq::default_instance_ = new TSwitchGetSwitchInfoReq();
  TSwitchGetSwitchInfoRsp::default_instance_ = new TSwitchGetSwitchInfoRsp();
  TSwitchUpdateSwitchInfoNotify::default_instance_ = new TSwitchUpdateSwitchInfoNotify();
  TSwitch::default_instance_ = new TSwitch();
  TSwitchGetSwitchInfoReq::default_instance_->InitAsDefaultInstance();
  TSwitchGetSwitchInfoRsp::default_instance_->InitAsDefaultInstance();
  TSwitchUpdateSwitchInfoNotify::default_instance_->InitAsDefaultInstance();
  TSwitch::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_net_2fSwitch_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_net_2fSwitch_2eproto {
  StaticDescriptorInitializer_net_2fSwitch_2eproto() {
    protobuf_AddDesc_net_2fSwitch_2eproto();
  }
} static_descriptor_initializer_net_2fSwitch_2eproto_;

// ===================================================================

#ifndef _MSC_VER
#endif  // !_MSC_VER

TSwitchGetSwitchInfoReq::TSwitchGetSwitchInfoReq()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:pb.TSwitchGetSwitchInfoReq)
}

void TSwitchGetSwitchInfoReq::InitAsDefaultInstance() {
}

TSwitchGetSwitchInfoReq::TSwitchGetSwitchInfoReq(const TSwitchGetSwitchInfoReq& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:pb.TSwitchGetSwitchInfoReq)
}

void TSwitchGetSwitchInfoReq::SharedCtor() {
  _cached_size_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

TSwitchGetSwitchInfoReq::~TSwitchGetSwitchInfoReq() {
  // @@protoc_insertion_point(destructor:pb.TSwitchGetSwitchInfoReq)
  SharedDtor();
}

void TSwitchGetSwitchInfoReq::SharedDtor() {
  if (this != default_instance_) {
  }
}

void TSwitchGetSwitchInfoReq::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* TSwitchGetSwitchInfoReq::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return TSwitchGetSwitchInfoReq_descriptor_;
}

const TSwitchGetSwitchInfoReq& TSwitchGetSwitchInfoReq::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_net_2fSwitch_2eproto();
  return *default_instance_;
}

TSwitchGetSwitchInfoReq* TSwitchGetSwitchInfoReq::default_instance_ = NULL;

TSwitchGetSwitchInfoReq* TSwitchGetSwitchInfoReq::New() const {
  return new TSwitchGetSwitchInfoReq;
}

void TSwitchGetSwitchInfoReq::Clear() {
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool TSwitchGetSwitchInfoReq::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:pb.TSwitchGetSwitchInfoReq)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
  handle_unusual:
    if (tag == 0 ||
        ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
        ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
      goto success;
    }
    DO_(::google::protobuf::internal::WireFormat::SkipField(
          input, tag, mutable_unknown_fields()));
  }
success:
  // @@protoc_insertion_point(parse_success:pb.TSwitchGetSwitchInfoReq)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:pb.TSwitchGetSwitchInfoReq)
  return false;
#undef DO_
}

void TSwitchGetSwitchInfoReq::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:pb.TSwitchGetSwitchInfoReq)
  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:pb.TSwitchGetSwitchInfoReq)
}

::google::protobuf::uint8* TSwitchGetSwitchInfoReq::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:pb.TSwitchGetSwitchInfoReq)
  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:pb.TSwitchGetSwitchInfoReq)
  return target;
}

int TSwitchGetSwitchInfoReq::ByteSize() const {
  int total_size = 0;

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

void TSwitchGetSwitchInfoReq::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const TSwitchGetSwitchInfoReq* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const TSwitchGetSwitchInfoReq*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void TSwitchGetSwitchInfoReq::MergeFrom(const TSwitchGetSwitchInfoReq& from) {
  GOOGLE_CHECK_NE(&from, this);
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void TSwitchGetSwitchInfoReq::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void TSwitchGetSwitchInfoReq::CopyFrom(const TSwitchGetSwitchInfoReq& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool TSwitchGetSwitchInfoReq::IsInitialized() const {

  return true;
}

void TSwitchGetSwitchInfoReq::Swap(TSwitchGetSwitchInfoReq* other) {
  if (other != this) {
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata TSwitchGetSwitchInfoReq::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = TSwitchGetSwitchInfoReq_descriptor_;
  metadata.reflection = TSwitchGetSwitchInfoReq_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int TSwitchGetSwitchInfoRsp::kInfoFieldNumber;
#endif  // !_MSC_VER

TSwitchGetSwitchInfoRsp::TSwitchGetSwitchInfoRsp()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:pb.TSwitchGetSwitchInfoRsp)
}

void TSwitchGetSwitchInfoRsp::InitAsDefaultInstance() {
  info_ = const_cast< ::pb::TSwitch*>(&::pb::TSwitch::default_instance());
}

TSwitchGetSwitchInfoRsp::TSwitchGetSwitchInfoRsp(const TSwitchGetSwitchInfoRsp& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:pb.TSwitchGetSwitchInfoRsp)
}

void TSwitchGetSwitchInfoRsp::SharedCtor() {
  _cached_size_ = 0;
  info_ = NULL;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

TSwitchGetSwitchInfoRsp::~TSwitchGetSwitchInfoRsp() {
  // @@protoc_insertion_point(destructor:pb.TSwitchGetSwitchInfoRsp)
  SharedDtor();
}

void TSwitchGetSwitchInfoRsp::SharedDtor() {
  if (this != default_instance_) {
    delete info_;
  }
}

void TSwitchGetSwitchInfoRsp::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* TSwitchGetSwitchInfoRsp::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return TSwitchGetSwitchInfoRsp_descriptor_;
}

const TSwitchGetSwitchInfoRsp& TSwitchGetSwitchInfoRsp::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_net_2fSwitch_2eproto();
  return *default_instance_;
}

TSwitchGetSwitchInfoRsp* TSwitchGetSwitchInfoRsp::default_instance_ = NULL;

TSwitchGetSwitchInfoRsp* TSwitchGetSwitchInfoRsp::New() const {
  return new TSwitchGetSwitchInfoRsp;
}

void TSwitchGetSwitchInfoRsp::Clear() {
  if (has_info()) {
    if (info_ != NULL) info_->::pb::TSwitch::Clear();
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool TSwitchGetSwitchInfoRsp::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:pb.TSwitchGetSwitchInfoRsp)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional .pb.TSwitch Info = 1;
      case 1: {
        if (tag == 10) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_info()));
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
  // @@protoc_insertion_point(parse_success:pb.TSwitchGetSwitchInfoRsp)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:pb.TSwitchGetSwitchInfoRsp)
  return false;
#undef DO_
}

void TSwitchGetSwitchInfoRsp::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:pb.TSwitchGetSwitchInfoRsp)
  // optional .pb.TSwitch Info = 1;
  if (has_info()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->info(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:pb.TSwitchGetSwitchInfoRsp)
}

::google::protobuf::uint8* TSwitchGetSwitchInfoRsp::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:pb.TSwitchGetSwitchInfoRsp)
  // optional .pb.TSwitch Info = 1;
  if (has_info()) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        1, this->info(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:pb.TSwitchGetSwitchInfoRsp)
  return target;
}

int TSwitchGetSwitchInfoRsp::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional .pb.TSwitch Info = 1;
    if (has_info()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->info());
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

void TSwitchGetSwitchInfoRsp::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const TSwitchGetSwitchInfoRsp* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const TSwitchGetSwitchInfoRsp*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void TSwitchGetSwitchInfoRsp::MergeFrom(const TSwitchGetSwitchInfoRsp& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_info()) {
      mutable_info()->::pb::TSwitch::MergeFrom(from.info());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void TSwitchGetSwitchInfoRsp::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void TSwitchGetSwitchInfoRsp::CopyFrom(const TSwitchGetSwitchInfoRsp& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool TSwitchGetSwitchInfoRsp::IsInitialized() const {

  return true;
}

void TSwitchGetSwitchInfoRsp::Swap(TSwitchGetSwitchInfoRsp* other) {
  if (other != this) {
    std::swap(info_, other->info_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata TSwitchGetSwitchInfoRsp::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = TSwitchGetSwitchInfoRsp_descriptor_;
  metadata.reflection = TSwitchGetSwitchInfoRsp_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int TSwitchUpdateSwitchInfoNotify::kInfoFieldNumber;
#endif  // !_MSC_VER

TSwitchUpdateSwitchInfoNotify::TSwitchUpdateSwitchInfoNotify()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:pb.TSwitchUpdateSwitchInfoNotify)
}

void TSwitchUpdateSwitchInfoNotify::InitAsDefaultInstance() {
  info_ = const_cast< ::pb::TSwitch*>(&::pb::TSwitch::default_instance());
}

TSwitchUpdateSwitchInfoNotify::TSwitchUpdateSwitchInfoNotify(const TSwitchUpdateSwitchInfoNotify& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:pb.TSwitchUpdateSwitchInfoNotify)
}

void TSwitchUpdateSwitchInfoNotify::SharedCtor() {
  _cached_size_ = 0;
  info_ = NULL;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

TSwitchUpdateSwitchInfoNotify::~TSwitchUpdateSwitchInfoNotify() {
  // @@protoc_insertion_point(destructor:pb.TSwitchUpdateSwitchInfoNotify)
  SharedDtor();
}

void TSwitchUpdateSwitchInfoNotify::SharedDtor() {
  if (this != default_instance_) {
    delete info_;
  }
}

void TSwitchUpdateSwitchInfoNotify::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* TSwitchUpdateSwitchInfoNotify::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return TSwitchUpdateSwitchInfoNotify_descriptor_;
}

const TSwitchUpdateSwitchInfoNotify& TSwitchUpdateSwitchInfoNotify::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_net_2fSwitch_2eproto();
  return *default_instance_;
}

TSwitchUpdateSwitchInfoNotify* TSwitchUpdateSwitchInfoNotify::default_instance_ = NULL;

TSwitchUpdateSwitchInfoNotify* TSwitchUpdateSwitchInfoNotify::New() const {
  return new TSwitchUpdateSwitchInfoNotify;
}

void TSwitchUpdateSwitchInfoNotify::Clear() {
  if (has_info()) {
    if (info_ != NULL) info_->::pb::TSwitch::Clear();
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool TSwitchUpdateSwitchInfoNotify::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:pb.TSwitchUpdateSwitchInfoNotify)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional .pb.TSwitch Info = 1;
      case 1: {
        if (tag == 10) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_info()));
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
  // @@protoc_insertion_point(parse_success:pb.TSwitchUpdateSwitchInfoNotify)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:pb.TSwitchUpdateSwitchInfoNotify)
  return false;
#undef DO_
}

void TSwitchUpdateSwitchInfoNotify::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:pb.TSwitchUpdateSwitchInfoNotify)
  // optional .pb.TSwitch Info = 1;
  if (has_info()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->info(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:pb.TSwitchUpdateSwitchInfoNotify)
}

::google::protobuf::uint8* TSwitchUpdateSwitchInfoNotify::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:pb.TSwitchUpdateSwitchInfoNotify)
  // optional .pb.TSwitch Info = 1;
  if (has_info()) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        1, this->info(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:pb.TSwitchUpdateSwitchInfoNotify)
  return target;
}

int TSwitchUpdateSwitchInfoNotify::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional .pb.TSwitch Info = 1;
    if (has_info()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->info());
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

void TSwitchUpdateSwitchInfoNotify::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const TSwitchUpdateSwitchInfoNotify* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const TSwitchUpdateSwitchInfoNotify*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void TSwitchUpdateSwitchInfoNotify::MergeFrom(const TSwitchUpdateSwitchInfoNotify& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_info()) {
      mutable_info()->::pb::TSwitch::MergeFrom(from.info());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void TSwitchUpdateSwitchInfoNotify::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void TSwitchUpdateSwitchInfoNotify::CopyFrom(const TSwitchUpdateSwitchInfoNotify& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool TSwitchUpdateSwitchInfoNotify::IsInitialized() const {

  return true;
}

void TSwitchUpdateSwitchInfoNotify::Swap(TSwitchUpdateSwitchInfoNotify* other) {
  if (other != this) {
    std::swap(info_, other->info_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata TSwitchUpdateSwitchInfoNotify::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = TSwitchUpdateSwitchInfoNotify_descriptor_;
  metadata.reflection = TSwitchUpdateSwitchInfoNotify_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int TSwitch::kCombinationFieldNumber;
#endif  // !_MSC_VER

TSwitch::TSwitch()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:pb.TSwitch)
}

void TSwitch::InitAsDefaultInstance() {
}

TSwitch::TSwitch(const TSwitch& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:pb.TSwitch)
}

void TSwitch::SharedCtor() {
  _cached_size_ = 0;
  combination_ = false;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

TSwitch::~TSwitch() {
  // @@protoc_insertion_point(destructor:pb.TSwitch)
  SharedDtor();
}

void TSwitch::SharedDtor() {
  if (this != default_instance_) {
  }
}

void TSwitch::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* TSwitch::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return TSwitch_descriptor_;
}

const TSwitch& TSwitch::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_net_2fSwitch_2eproto();
  return *default_instance_;
}

TSwitch* TSwitch::default_instance_ = NULL;

TSwitch* TSwitch::New() const {
  return new TSwitch;
}

void TSwitch::Clear() {
  combination_ = false;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool TSwitch::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:pb.TSwitch)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional bool Combination = 1;
      case 1: {
        if (tag == 8) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &combination_)));
          set_has_combination();
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
  // @@protoc_insertion_point(parse_success:pb.TSwitch)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:pb.TSwitch)
  return false;
#undef DO_
}

void TSwitch::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:pb.TSwitch)
  // optional bool Combination = 1;
  if (has_combination()) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(1, this->combination(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:pb.TSwitch)
}

::google::protobuf::uint8* TSwitch::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:pb.TSwitch)
  // optional bool Combination = 1;
  if (has_combination()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(1, this->combination(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:pb.TSwitch)
  return target;
}

int TSwitch::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional bool Combination = 1;
    if (has_combination()) {
      total_size += 1 + 1;
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

void TSwitch::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const TSwitch* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const TSwitch*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void TSwitch::MergeFrom(const TSwitch& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_combination()) {
      set_combination(from.combination());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void TSwitch::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void TSwitch::CopyFrom(const TSwitch& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool TSwitch::IsInitialized() const {

  return true;
}

void TSwitch::Swap(TSwitch* other) {
  if (other != this) {
    std::swap(combination_, other->combination_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata TSwitch::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = TSwitch_descriptor_;
  metadata.reflection = TSwitch_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace pb

// @@protoc_insertion_point(global_scope)
