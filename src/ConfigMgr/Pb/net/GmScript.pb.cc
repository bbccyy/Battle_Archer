// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: net/GmScript.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "net/GmScript.pb.h"

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

const ::google::protobuf::Descriptor* TGmScriptLuaCodeNotify_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  TGmScriptLuaCodeNotify_reflection_ = NULL;
const ::google::protobuf::Descriptor* TGmScriptReportResultReq_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  TGmScriptReportResultReq_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_net_2fGmScript_2eproto() {
  protobuf_AddDesc_net_2fGmScript_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "net/GmScript.proto");
  GOOGLE_CHECK(file != NULL);
  TGmScriptLuaCodeNotify_descriptor_ = file->message_type(0);
  static const int TGmScriptLuaCodeNotify_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TGmScriptLuaCodeNotify, luastring_),
  };
  TGmScriptLuaCodeNotify_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      TGmScriptLuaCodeNotify_descriptor_,
      TGmScriptLuaCodeNotify::default_instance_,
      TGmScriptLuaCodeNotify_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TGmScriptLuaCodeNotify, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TGmScriptLuaCodeNotify, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(TGmScriptLuaCodeNotify));
  TGmScriptReportResultReq_descriptor_ = file->message_type(1);
  static const int TGmScriptReportResultReq_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TGmScriptReportResultReq, result_),
  };
  TGmScriptReportResultReq_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      TGmScriptReportResultReq_descriptor_,
      TGmScriptReportResultReq::default_instance_,
      TGmScriptReportResultReq_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TGmScriptReportResultReq, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TGmScriptReportResultReq, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(TGmScriptReportResultReq));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_net_2fGmScript_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    TGmScriptLuaCodeNotify_descriptor_, &TGmScriptLuaCodeNotify::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    TGmScriptReportResultReq_descriptor_, &TGmScriptReportResultReq::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_net_2fGmScript_2eproto() {
  delete TGmScriptLuaCodeNotify::default_instance_;
  delete TGmScriptLuaCodeNotify_reflection_;
  delete TGmScriptReportResultReq::default_instance_;
  delete TGmScriptReportResultReq_reflection_;
}

void protobuf_AddDesc_net_2fGmScript_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\022net/GmScript.proto\022\002pb\"+\n\026TGmScriptLua"
    "CodeNotify\022\021\n\tLuaString\030\001 \001(\t\"*\n\030TGmScri"
    "ptReportResultReq\022\016\n\006Result\030\001 \001(\t", 113);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "net/GmScript.proto", &protobuf_RegisterTypes);
  TGmScriptLuaCodeNotify::default_instance_ = new TGmScriptLuaCodeNotify();
  TGmScriptReportResultReq::default_instance_ = new TGmScriptReportResultReq();
  TGmScriptLuaCodeNotify::default_instance_->InitAsDefaultInstance();
  TGmScriptReportResultReq::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_net_2fGmScript_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_net_2fGmScript_2eproto {
  StaticDescriptorInitializer_net_2fGmScript_2eproto() {
    protobuf_AddDesc_net_2fGmScript_2eproto();
  }
} static_descriptor_initializer_net_2fGmScript_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int TGmScriptLuaCodeNotify::kLuaStringFieldNumber;
#endif  // !_MSC_VER

TGmScriptLuaCodeNotify::TGmScriptLuaCodeNotify()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:pb.TGmScriptLuaCodeNotify)
}

void TGmScriptLuaCodeNotify::InitAsDefaultInstance() {
}

TGmScriptLuaCodeNotify::TGmScriptLuaCodeNotify(const TGmScriptLuaCodeNotify& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:pb.TGmScriptLuaCodeNotify)
}

void TGmScriptLuaCodeNotify::SharedCtor() {
  ::google::protobuf::internal::GetEmptyString();
  _cached_size_ = 0;
  luastring_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

TGmScriptLuaCodeNotify::~TGmScriptLuaCodeNotify() {
  // @@protoc_insertion_point(destructor:pb.TGmScriptLuaCodeNotify)
  SharedDtor();
}

void TGmScriptLuaCodeNotify::SharedDtor() {
  if (luastring_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete luastring_;
  }
  if (this != default_instance_) {
  }
}

void TGmScriptLuaCodeNotify::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* TGmScriptLuaCodeNotify::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return TGmScriptLuaCodeNotify_descriptor_;
}

const TGmScriptLuaCodeNotify& TGmScriptLuaCodeNotify::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_net_2fGmScript_2eproto();
  return *default_instance_;
}

TGmScriptLuaCodeNotify* TGmScriptLuaCodeNotify::default_instance_ = NULL;

TGmScriptLuaCodeNotify* TGmScriptLuaCodeNotify::New() const {
  return new TGmScriptLuaCodeNotify;
}

void TGmScriptLuaCodeNotify::Clear() {
  if (has_luastring()) {
    if (luastring_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
      luastring_->clear();
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool TGmScriptLuaCodeNotify::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:pb.TGmScriptLuaCodeNotify)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional string LuaString = 1;
      case 1: {
        if (tag == 10) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_luastring()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->luastring().data(), this->luastring().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "luastring");
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
  // @@protoc_insertion_point(parse_success:pb.TGmScriptLuaCodeNotify)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:pb.TGmScriptLuaCodeNotify)
  return false;
#undef DO_
}

void TGmScriptLuaCodeNotify::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:pb.TGmScriptLuaCodeNotify)
  // optional string LuaString = 1;
  if (has_luastring()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->luastring().data(), this->luastring().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "luastring");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      1, this->luastring(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:pb.TGmScriptLuaCodeNotify)
}

::google::protobuf::uint8* TGmScriptLuaCodeNotify::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:pb.TGmScriptLuaCodeNotify)
  // optional string LuaString = 1;
  if (has_luastring()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->luastring().data(), this->luastring().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "luastring");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        1, this->luastring(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:pb.TGmScriptLuaCodeNotify)
  return target;
}

int TGmScriptLuaCodeNotify::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional string LuaString = 1;
    if (has_luastring()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->luastring());
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

void TGmScriptLuaCodeNotify::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const TGmScriptLuaCodeNotify* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const TGmScriptLuaCodeNotify*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void TGmScriptLuaCodeNotify::MergeFrom(const TGmScriptLuaCodeNotify& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_luastring()) {
      set_luastring(from.luastring());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void TGmScriptLuaCodeNotify::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void TGmScriptLuaCodeNotify::CopyFrom(const TGmScriptLuaCodeNotify& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool TGmScriptLuaCodeNotify::IsInitialized() const {

  return true;
}

void TGmScriptLuaCodeNotify::Swap(TGmScriptLuaCodeNotify* other) {
  if (other != this) {
    std::swap(luastring_, other->luastring_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata TGmScriptLuaCodeNotify::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = TGmScriptLuaCodeNotify_descriptor_;
  metadata.reflection = TGmScriptLuaCodeNotify_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int TGmScriptReportResultReq::kResultFieldNumber;
#endif  // !_MSC_VER

TGmScriptReportResultReq::TGmScriptReportResultReq()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:pb.TGmScriptReportResultReq)
}

void TGmScriptReportResultReq::InitAsDefaultInstance() {
}

TGmScriptReportResultReq::TGmScriptReportResultReq(const TGmScriptReportResultReq& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:pb.TGmScriptReportResultReq)
}

void TGmScriptReportResultReq::SharedCtor() {
  ::google::protobuf::internal::GetEmptyString();
  _cached_size_ = 0;
  result_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

TGmScriptReportResultReq::~TGmScriptReportResultReq() {
  // @@protoc_insertion_point(destructor:pb.TGmScriptReportResultReq)
  SharedDtor();
}

void TGmScriptReportResultReq::SharedDtor() {
  if (result_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete result_;
  }
  if (this != default_instance_) {
  }
}

void TGmScriptReportResultReq::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* TGmScriptReportResultReq::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return TGmScriptReportResultReq_descriptor_;
}

const TGmScriptReportResultReq& TGmScriptReportResultReq::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_net_2fGmScript_2eproto();
  return *default_instance_;
}

TGmScriptReportResultReq* TGmScriptReportResultReq::default_instance_ = NULL;

TGmScriptReportResultReq* TGmScriptReportResultReq::New() const {
  return new TGmScriptReportResultReq;
}

void TGmScriptReportResultReq::Clear() {
  if (has_result()) {
    if (result_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
      result_->clear();
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool TGmScriptReportResultReq::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:pb.TGmScriptReportResultReq)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional string Result = 1;
      case 1: {
        if (tag == 10) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_result()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->result().data(), this->result().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "result");
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
  // @@protoc_insertion_point(parse_success:pb.TGmScriptReportResultReq)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:pb.TGmScriptReportResultReq)
  return false;
#undef DO_
}

void TGmScriptReportResultReq::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:pb.TGmScriptReportResultReq)
  // optional string Result = 1;
  if (has_result()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->result().data(), this->result().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "result");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      1, this->result(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:pb.TGmScriptReportResultReq)
}

::google::protobuf::uint8* TGmScriptReportResultReq::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:pb.TGmScriptReportResultReq)
  // optional string Result = 1;
  if (has_result()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->result().data(), this->result().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "result");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        1, this->result(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:pb.TGmScriptReportResultReq)
  return target;
}

int TGmScriptReportResultReq::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional string Result = 1;
    if (has_result()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->result());
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

void TGmScriptReportResultReq::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const TGmScriptReportResultReq* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const TGmScriptReportResultReq*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void TGmScriptReportResultReq::MergeFrom(const TGmScriptReportResultReq& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_result()) {
      set_result(from.result());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void TGmScriptReportResultReq::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void TGmScriptReportResultReq::CopyFrom(const TGmScriptReportResultReq& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool TGmScriptReportResultReq::IsInitialized() const {

  return true;
}

void TGmScriptReportResultReq::Swap(TGmScriptReportResultReq* other) {
  if (other != this) {
    std::swap(result_, other->result_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata TGmScriptReportResultReq::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = TGmScriptReportResultReq_descriptor_;
  metadata.reflection = TGmScriptReportResultReq_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace pb

// @@protoc_insertion_point(global_scope)
