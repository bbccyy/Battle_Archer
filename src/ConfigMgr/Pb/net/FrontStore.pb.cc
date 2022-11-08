// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: net/FrontStore.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "net/FrontStore.pb.h"

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

const ::google::protobuf::Descriptor* TFrontStore_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  TFrontStore_reflection_ = NULL;
const ::google::protobuf::Descriptor* TFrontStoreSetKeyReq_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  TFrontStoreSetKeyReq_reflection_ = NULL;
const ::google::protobuf::Descriptor* TFrontStoreDelKeyReq_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  TFrontStoreDelKeyReq_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_net_2fFrontStore_2eproto() {
  protobuf_AddDesc_net_2fFrontStore_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "net/FrontStore.proto");
  GOOGLE_CHECK(file != NULL);
  TFrontStore_descriptor_ = file->message_type(0);
  static const int TFrontStore_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TFrontStore, key_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TFrontStore, value_),
  };
  TFrontStore_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      TFrontStore_descriptor_,
      TFrontStore::default_instance_,
      TFrontStore_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TFrontStore, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TFrontStore, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(TFrontStore));
  TFrontStoreSetKeyReq_descriptor_ = file->message_type(1);
  static const int TFrontStoreSetKeyReq_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TFrontStoreSetKeyReq, key_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TFrontStoreSetKeyReq, value_),
  };
  TFrontStoreSetKeyReq_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      TFrontStoreSetKeyReq_descriptor_,
      TFrontStoreSetKeyReq::default_instance_,
      TFrontStoreSetKeyReq_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TFrontStoreSetKeyReq, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TFrontStoreSetKeyReq, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(TFrontStoreSetKeyReq));
  TFrontStoreDelKeyReq_descriptor_ = file->message_type(2);
  static const int TFrontStoreDelKeyReq_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TFrontStoreDelKeyReq, key_),
  };
  TFrontStoreDelKeyReq_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      TFrontStoreDelKeyReq_descriptor_,
      TFrontStoreDelKeyReq::default_instance_,
      TFrontStoreDelKeyReq_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TFrontStoreDelKeyReq, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TFrontStoreDelKeyReq, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(TFrontStoreDelKeyReq));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_net_2fFrontStore_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    TFrontStore_descriptor_, &TFrontStore::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    TFrontStoreSetKeyReq_descriptor_, &TFrontStoreSetKeyReq::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    TFrontStoreDelKeyReq_descriptor_, &TFrontStoreDelKeyReq::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_net_2fFrontStore_2eproto() {
  delete TFrontStore::default_instance_;
  delete TFrontStore_reflection_;
  delete TFrontStoreSetKeyReq::default_instance_;
  delete TFrontStoreSetKeyReq_reflection_;
  delete TFrontStoreDelKeyReq::default_instance_;
  delete TFrontStoreDelKeyReq_reflection_;
}

void protobuf_AddDesc_net_2fFrontStore_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\024net/FrontStore.proto\022\002pb\")\n\013TFrontStor"
    "e\022\013\n\003key\030\001 \001(\004\022\r\n\005value\030\002 \001(\014\"2\n\024TFrontS"
    "toreSetKeyReq\022\013\n\003key\030\001 \001(\004\022\r\n\005value\030\002 \001("
    "\014\"#\n\024TFrontStoreDelKeyReq\022\013\n\003key\030\001 \001(\004", 158);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "net/FrontStore.proto", &protobuf_RegisterTypes);
  TFrontStore::default_instance_ = new TFrontStore();
  TFrontStoreSetKeyReq::default_instance_ = new TFrontStoreSetKeyReq();
  TFrontStoreDelKeyReq::default_instance_ = new TFrontStoreDelKeyReq();
  TFrontStore::default_instance_->InitAsDefaultInstance();
  TFrontStoreSetKeyReq::default_instance_->InitAsDefaultInstance();
  TFrontStoreDelKeyReq::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_net_2fFrontStore_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_net_2fFrontStore_2eproto {
  StaticDescriptorInitializer_net_2fFrontStore_2eproto() {
    protobuf_AddDesc_net_2fFrontStore_2eproto();
  }
} static_descriptor_initializer_net_2fFrontStore_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int TFrontStore::kKeyFieldNumber;
const int TFrontStore::kValueFieldNumber;
#endif  // !_MSC_VER

TFrontStore::TFrontStore()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:pb.TFrontStore)
}

void TFrontStore::InitAsDefaultInstance() {
}

TFrontStore::TFrontStore(const TFrontStore& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:pb.TFrontStore)
}

void TFrontStore::SharedCtor() {
  ::google::protobuf::internal::GetEmptyString();
  _cached_size_ = 0;
  key_ = GOOGLE_ULONGLONG(0);
  value_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

TFrontStore::~TFrontStore() {
  // @@protoc_insertion_point(destructor:pb.TFrontStore)
  SharedDtor();
}

void TFrontStore::SharedDtor() {
  if (value_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete value_;
  }
  if (this != default_instance_) {
  }
}

void TFrontStore::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* TFrontStore::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return TFrontStore_descriptor_;
}

const TFrontStore& TFrontStore::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_net_2fFrontStore_2eproto();
  return *default_instance_;
}

TFrontStore* TFrontStore::default_instance_ = NULL;

TFrontStore* TFrontStore::New() const {
  return new TFrontStore;
}

void TFrontStore::Clear() {
  if (_has_bits_[0 / 32] & 3) {
    key_ = GOOGLE_ULONGLONG(0);
    if (has_value()) {
      if (value_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        value_->clear();
      }
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool TFrontStore::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:pb.TFrontStore)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional uint64 key = 1;
      case 1: {
        if (tag == 8) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint64, ::google::protobuf::internal::WireFormatLite::TYPE_UINT64>(
                 input, &key_)));
          set_has_key();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(18)) goto parse_value;
        break;
      }

      // optional bytes value = 2;
      case 2: {
        if (tag == 18) {
         parse_value:
          DO_(::google::protobuf::internal::WireFormatLite::ReadBytes(
                input, this->mutable_value()));
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
  // @@protoc_insertion_point(parse_success:pb.TFrontStore)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:pb.TFrontStore)
  return false;
#undef DO_
}

void TFrontStore::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:pb.TFrontStore)
  // optional uint64 key = 1;
  if (has_key()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt64(1, this->key(), output);
  }

  // optional bytes value = 2;
  if (has_value()) {
    ::google::protobuf::internal::WireFormatLite::WriteBytesMaybeAliased(
      2, this->value(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:pb.TFrontStore)
}

::google::protobuf::uint8* TFrontStore::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:pb.TFrontStore)
  // optional uint64 key = 1;
  if (has_key()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt64ToArray(1, this->key(), target);
  }

  // optional bytes value = 2;
  if (has_value()) {
    target =
      ::google::protobuf::internal::WireFormatLite::WriteBytesToArray(
        2, this->value(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:pb.TFrontStore)
  return target;
}

int TFrontStore::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional uint64 key = 1;
    if (has_key()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt64Size(
          this->key());
    }

    // optional bytes value = 2;
    if (has_value()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::BytesSize(
          this->value());
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

void TFrontStore::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const TFrontStore* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const TFrontStore*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void TFrontStore::MergeFrom(const TFrontStore& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_key()) {
      set_key(from.key());
    }
    if (from.has_value()) {
      set_value(from.value());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void TFrontStore::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void TFrontStore::CopyFrom(const TFrontStore& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool TFrontStore::IsInitialized() const {

  return true;
}

void TFrontStore::Swap(TFrontStore* other) {
  if (other != this) {
    std::swap(key_, other->key_);
    std::swap(value_, other->value_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata TFrontStore::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = TFrontStore_descriptor_;
  metadata.reflection = TFrontStore_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int TFrontStoreSetKeyReq::kKeyFieldNumber;
const int TFrontStoreSetKeyReq::kValueFieldNumber;
#endif  // !_MSC_VER

TFrontStoreSetKeyReq::TFrontStoreSetKeyReq()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:pb.TFrontStoreSetKeyReq)
}

void TFrontStoreSetKeyReq::InitAsDefaultInstance() {
}

TFrontStoreSetKeyReq::TFrontStoreSetKeyReq(const TFrontStoreSetKeyReq& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:pb.TFrontStoreSetKeyReq)
}

void TFrontStoreSetKeyReq::SharedCtor() {
  ::google::protobuf::internal::GetEmptyString();
  _cached_size_ = 0;
  key_ = GOOGLE_ULONGLONG(0);
  value_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

TFrontStoreSetKeyReq::~TFrontStoreSetKeyReq() {
  // @@protoc_insertion_point(destructor:pb.TFrontStoreSetKeyReq)
  SharedDtor();
}

void TFrontStoreSetKeyReq::SharedDtor() {
  if (value_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete value_;
  }
  if (this != default_instance_) {
  }
}

void TFrontStoreSetKeyReq::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* TFrontStoreSetKeyReq::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return TFrontStoreSetKeyReq_descriptor_;
}

const TFrontStoreSetKeyReq& TFrontStoreSetKeyReq::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_net_2fFrontStore_2eproto();
  return *default_instance_;
}

TFrontStoreSetKeyReq* TFrontStoreSetKeyReq::default_instance_ = NULL;

TFrontStoreSetKeyReq* TFrontStoreSetKeyReq::New() const {
  return new TFrontStoreSetKeyReq;
}

void TFrontStoreSetKeyReq::Clear() {
  if (_has_bits_[0 / 32] & 3) {
    key_ = GOOGLE_ULONGLONG(0);
    if (has_value()) {
      if (value_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        value_->clear();
      }
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool TFrontStoreSetKeyReq::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:pb.TFrontStoreSetKeyReq)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional uint64 key = 1;
      case 1: {
        if (tag == 8) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint64, ::google::protobuf::internal::WireFormatLite::TYPE_UINT64>(
                 input, &key_)));
          set_has_key();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(18)) goto parse_value;
        break;
      }

      // optional bytes value = 2;
      case 2: {
        if (tag == 18) {
         parse_value:
          DO_(::google::protobuf::internal::WireFormatLite::ReadBytes(
                input, this->mutable_value()));
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
  // @@protoc_insertion_point(parse_success:pb.TFrontStoreSetKeyReq)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:pb.TFrontStoreSetKeyReq)
  return false;
#undef DO_
}

void TFrontStoreSetKeyReq::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:pb.TFrontStoreSetKeyReq)
  // optional uint64 key = 1;
  if (has_key()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt64(1, this->key(), output);
  }

  // optional bytes value = 2;
  if (has_value()) {
    ::google::protobuf::internal::WireFormatLite::WriteBytesMaybeAliased(
      2, this->value(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:pb.TFrontStoreSetKeyReq)
}

::google::protobuf::uint8* TFrontStoreSetKeyReq::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:pb.TFrontStoreSetKeyReq)
  // optional uint64 key = 1;
  if (has_key()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt64ToArray(1, this->key(), target);
  }

  // optional bytes value = 2;
  if (has_value()) {
    target =
      ::google::protobuf::internal::WireFormatLite::WriteBytesToArray(
        2, this->value(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:pb.TFrontStoreSetKeyReq)
  return target;
}

int TFrontStoreSetKeyReq::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional uint64 key = 1;
    if (has_key()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt64Size(
          this->key());
    }

    // optional bytes value = 2;
    if (has_value()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::BytesSize(
          this->value());
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

void TFrontStoreSetKeyReq::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const TFrontStoreSetKeyReq* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const TFrontStoreSetKeyReq*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void TFrontStoreSetKeyReq::MergeFrom(const TFrontStoreSetKeyReq& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_key()) {
      set_key(from.key());
    }
    if (from.has_value()) {
      set_value(from.value());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void TFrontStoreSetKeyReq::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void TFrontStoreSetKeyReq::CopyFrom(const TFrontStoreSetKeyReq& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool TFrontStoreSetKeyReq::IsInitialized() const {

  return true;
}

void TFrontStoreSetKeyReq::Swap(TFrontStoreSetKeyReq* other) {
  if (other != this) {
    std::swap(key_, other->key_);
    std::swap(value_, other->value_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata TFrontStoreSetKeyReq::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = TFrontStoreSetKeyReq_descriptor_;
  metadata.reflection = TFrontStoreSetKeyReq_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int TFrontStoreDelKeyReq::kKeyFieldNumber;
#endif  // !_MSC_VER

TFrontStoreDelKeyReq::TFrontStoreDelKeyReq()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:pb.TFrontStoreDelKeyReq)
}

void TFrontStoreDelKeyReq::InitAsDefaultInstance() {
}

TFrontStoreDelKeyReq::TFrontStoreDelKeyReq(const TFrontStoreDelKeyReq& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:pb.TFrontStoreDelKeyReq)
}

void TFrontStoreDelKeyReq::SharedCtor() {
  _cached_size_ = 0;
  key_ = GOOGLE_ULONGLONG(0);
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

TFrontStoreDelKeyReq::~TFrontStoreDelKeyReq() {
  // @@protoc_insertion_point(destructor:pb.TFrontStoreDelKeyReq)
  SharedDtor();
}

void TFrontStoreDelKeyReq::SharedDtor() {
  if (this != default_instance_) {
  }
}

void TFrontStoreDelKeyReq::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* TFrontStoreDelKeyReq::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return TFrontStoreDelKeyReq_descriptor_;
}

const TFrontStoreDelKeyReq& TFrontStoreDelKeyReq::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_net_2fFrontStore_2eproto();
  return *default_instance_;
}

TFrontStoreDelKeyReq* TFrontStoreDelKeyReq::default_instance_ = NULL;

TFrontStoreDelKeyReq* TFrontStoreDelKeyReq::New() const {
  return new TFrontStoreDelKeyReq;
}

void TFrontStoreDelKeyReq::Clear() {
  key_ = GOOGLE_ULONGLONG(0);
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool TFrontStoreDelKeyReq::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:pb.TFrontStoreDelKeyReq)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional uint64 key = 1;
      case 1: {
        if (tag == 8) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint64, ::google::protobuf::internal::WireFormatLite::TYPE_UINT64>(
                 input, &key_)));
          set_has_key();
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
  // @@protoc_insertion_point(parse_success:pb.TFrontStoreDelKeyReq)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:pb.TFrontStoreDelKeyReq)
  return false;
#undef DO_
}

void TFrontStoreDelKeyReq::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:pb.TFrontStoreDelKeyReq)
  // optional uint64 key = 1;
  if (has_key()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt64(1, this->key(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:pb.TFrontStoreDelKeyReq)
}

::google::protobuf::uint8* TFrontStoreDelKeyReq::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:pb.TFrontStoreDelKeyReq)
  // optional uint64 key = 1;
  if (has_key()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt64ToArray(1, this->key(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:pb.TFrontStoreDelKeyReq)
  return target;
}

int TFrontStoreDelKeyReq::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional uint64 key = 1;
    if (has_key()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt64Size(
          this->key());
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

void TFrontStoreDelKeyReq::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const TFrontStoreDelKeyReq* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const TFrontStoreDelKeyReq*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void TFrontStoreDelKeyReq::MergeFrom(const TFrontStoreDelKeyReq& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_key()) {
      set_key(from.key());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void TFrontStoreDelKeyReq::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void TFrontStoreDelKeyReq::CopyFrom(const TFrontStoreDelKeyReq& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool TFrontStoreDelKeyReq::IsInitialized() const {

  return true;
}

void TFrontStoreDelKeyReq::Swap(TFrontStoreDelKeyReq* other) {
  if (other != this) {
    std::swap(key_, other->key_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata TFrontStoreDelKeyReq::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = TFrontStoreDelKeyReq_descriptor_;
  metadata.reflection = TFrontStoreDelKeyReq_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace pb

// @@protoc_insertion_point(global_scope)
