// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: net/ActTimeLimitedMerchant.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "net/ActTimeLimitedMerchant.pb.h"

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

const ::google::protobuf::Descriptor* TActTimeLimitedMerchantInfo_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  TActTimeLimitedMerchantInfo_reflection_ = NULL;
const ::google::protobuf::Descriptor* TActTimeLimitedMerchantGetInfoRsp_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  TActTimeLimitedMerchantGetInfoRsp_reflection_ = NULL;
const ::google::protobuf::Descriptor* TActTimeLimitedMerchantNotify_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  TActTimeLimitedMerchantNotify_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_net_2fActTimeLimitedMerchant_2eproto() {
  protobuf_AddDesc_net_2fActTimeLimitedMerchant_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "net/ActTimeLimitedMerchant.proto");
  GOOGLE_CHECK(file != NULL);
  TActTimeLimitedMerchantInfo_descriptor_ = file->message_type(0);
  static const int TActTimeLimitedMerchantInfo_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TActTimeLimitedMerchantInfo, id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TActTimeLimitedMerchantInfo, buynum_),
  };
  TActTimeLimitedMerchantInfo_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      TActTimeLimitedMerchantInfo_descriptor_,
      TActTimeLimitedMerchantInfo::default_instance_,
      TActTimeLimitedMerchantInfo_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TActTimeLimitedMerchantInfo, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TActTimeLimitedMerchantInfo, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(TActTimeLimitedMerchantInfo));
  TActTimeLimitedMerchantGetInfoRsp_descriptor_ = file->message_type(1);
  static const int TActTimeLimitedMerchantGetInfoRsp_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TActTimeLimitedMerchantGetInfoRsp, arrinfo_),
  };
  TActTimeLimitedMerchantGetInfoRsp_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      TActTimeLimitedMerchantGetInfoRsp_descriptor_,
      TActTimeLimitedMerchantGetInfoRsp::default_instance_,
      TActTimeLimitedMerchantGetInfoRsp_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TActTimeLimitedMerchantGetInfoRsp, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TActTimeLimitedMerchantGetInfoRsp, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(TActTimeLimitedMerchantGetInfoRsp));
  TActTimeLimitedMerchantNotify_descriptor_ = file->message_type(2);
  static const int TActTimeLimitedMerchantNotify_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TActTimeLimitedMerchantNotify, arrinfo_),
  };
  TActTimeLimitedMerchantNotify_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      TActTimeLimitedMerchantNotify_descriptor_,
      TActTimeLimitedMerchantNotify::default_instance_,
      TActTimeLimitedMerchantNotify_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TActTimeLimitedMerchantNotify, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TActTimeLimitedMerchantNotify, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(TActTimeLimitedMerchantNotify));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_net_2fActTimeLimitedMerchant_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    TActTimeLimitedMerchantInfo_descriptor_, &TActTimeLimitedMerchantInfo::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    TActTimeLimitedMerchantGetInfoRsp_descriptor_, &TActTimeLimitedMerchantGetInfoRsp::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    TActTimeLimitedMerchantNotify_descriptor_, &TActTimeLimitedMerchantNotify::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_net_2fActTimeLimitedMerchant_2eproto() {
  delete TActTimeLimitedMerchantInfo::default_instance_;
  delete TActTimeLimitedMerchantInfo_reflection_;
  delete TActTimeLimitedMerchantGetInfoRsp::default_instance_;
  delete TActTimeLimitedMerchantGetInfoRsp_reflection_;
  delete TActTimeLimitedMerchantNotify::default_instance_;
  delete TActTimeLimitedMerchantNotify_reflection_;
}

void protobuf_AddDesc_net_2fActTimeLimitedMerchant_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n net/ActTimeLimitedMerchant.proto\022\002pb\"9"
    "\n\033TActTimeLimitedMerchantInfo\022\n\n\002Id\030\001 \001("
    "\r\022\016\n\006BuyNum\030\002 \001(\r\"U\n!TActTimeLimitedMerc"
    "hantGetInfoRsp\0220\n\007ArrInfo\030\001 \003(\0132\037.pb.TAc"
    "tTimeLimitedMerchantInfo\"Q\n\035TActTimeLimi"
    "tedMerchantNotify\0220\n\007ArrInfo\030\001 \003(\0132\037.pb."
    "TActTimeLimitedMerchantInfo", 267);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "net/ActTimeLimitedMerchant.proto", &protobuf_RegisterTypes);
  TActTimeLimitedMerchantInfo::default_instance_ = new TActTimeLimitedMerchantInfo();
  TActTimeLimitedMerchantGetInfoRsp::default_instance_ = new TActTimeLimitedMerchantGetInfoRsp();
  TActTimeLimitedMerchantNotify::default_instance_ = new TActTimeLimitedMerchantNotify();
  TActTimeLimitedMerchantInfo::default_instance_->InitAsDefaultInstance();
  TActTimeLimitedMerchantGetInfoRsp::default_instance_->InitAsDefaultInstance();
  TActTimeLimitedMerchantNotify::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_net_2fActTimeLimitedMerchant_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_net_2fActTimeLimitedMerchant_2eproto {
  StaticDescriptorInitializer_net_2fActTimeLimitedMerchant_2eproto() {
    protobuf_AddDesc_net_2fActTimeLimitedMerchant_2eproto();
  }
} static_descriptor_initializer_net_2fActTimeLimitedMerchant_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int TActTimeLimitedMerchantInfo::kIdFieldNumber;
const int TActTimeLimitedMerchantInfo::kBuyNumFieldNumber;
#endif  // !_MSC_VER

TActTimeLimitedMerchantInfo::TActTimeLimitedMerchantInfo()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:pb.TActTimeLimitedMerchantInfo)
}

void TActTimeLimitedMerchantInfo::InitAsDefaultInstance() {
}

TActTimeLimitedMerchantInfo::TActTimeLimitedMerchantInfo(const TActTimeLimitedMerchantInfo& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:pb.TActTimeLimitedMerchantInfo)
}

void TActTimeLimitedMerchantInfo::SharedCtor() {
  _cached_size_ = 0;
  id_ = 0u;
  buynum_ = 0u;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

TActTimeLimitedMerchantInfo::~TActTimeLimitedMerchantInfo() {
  // @@protoc_insertion_point(destructor:pb.TActTimeLimitedMerchantInfo)
  SharedDtor();
}

void TActTimeLimitedMerchantInfo::SharedDtor() {
  if (this != default_instance_) {
  }
}

void TActTimeLimitedMerchantInfo::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* TActTimeLimitedMerchantInfo::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return TActTimeLimitedMerchantInfo_descriptor_;
}

const TActTimeLimitedMerchantInfo& TActTimeLimitedMerchantInfo::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_net_2fActTimeLimitedMerchant_2eproto();
  return *default_instance_;
}

TActTimeLimitedMerchantInfo* TActTimeLimitedMerchantInfo::default_instance_ = NULL;

TActTimeLimitedMerchantInfo* TActTimeLimitedMerchantInfo::New() const {
  return new TActTimeLimitedMerchantInfo;
}

void TActTimeLimitedMerchantInfo::Clear() {
#define OFFSET_OF_FIELD_(f) (reinterpret_cast<char*>(      \
  &reinterpret_cast<TActTimeLimitedMerchantInfo*>(16)->f) - \
   reinterpret_cast<char*>(16))

#define ZR_(first, last) do {                              \
    size_t f = OFFSET_OF_FIELD_(first);                    \
    size_t n = OFFSET_OF_FIELD_(last) - f + sizeof(last);  \
    ::memset(&first, 0, n);                                \
  } while (0)

  ZR_(id_, buynum_);

#undef OFFSET_OF_FIELD_
#undef ZR_

  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool TActTimeLimitedMerchantInfo::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:pb.TActTimeLimitedMerchantInfo)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional uint32 Id = 1;
      case 1: {
        if (tag == 8) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &id_)));
          set_has_id();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(16)) goto parse_BuyNum;
        break;
      }

      // optional uint32 BuyNum = 2;
      case 2: {
        if (tag == 16) {
         parse_BuyNum:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &buynum_)));
          set_has_buynum();
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
  // @@protoc_insertion_point(parse_success:pb.TActTimeLimitedMerchantInfo)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:pb.TActTimeLimitedMerchantInfo)
  return false;
#undef DO_
}

void TActTimeLimitedMerchantInfo::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:pb.TActTimeLimitedMerchantInfo)
  // optional uint32 Id = 1;
  if (has_id()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->id(), output);
  }

  // optional uint32 BuyNum = 2;
  if (has_buynum()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(2, this->buynum(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:pb.TActTimeLimitedMerchantInfo)
}

::google::protobuf::uint8* TActTimeLimitedMerchantInfo::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:pb.TActTimeLimitedMerchantInfo)
  // optional uint32 Id = 1;
  if (has_id()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->id(), target);
  }

  // optional uint32 BuyNum = 2;
  if (has_buynum()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(2, this->buynum(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:pb.TActTimeLimitedMerchantInfo)
  return target;
}

int TActTimeLimitedMerchantInfo::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional uint32 Id = 1;
    if (has_id()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->id());
    }

    // optional uint32 BuyNum = 2;
    if (has_buynum()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->buynum());
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

void TActTimeLimitedMerchantInfo::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const TActTimeLimitedMerchantInfo* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const TActTimeLimitedMerchantInfo*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void TActTimeLimitedMerchantInfo::MergeFrom(const TActTimeLimitedMerchantInfo& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_id()) {
      set_id(from.id());
    }
    if (from.has_buynum()) {
      set_buynum(from.buynum());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void TActTimeLimitedMerchantInfo::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void TActTimeLimitedMerchantInfo::CopyFrom(const TActTimeLimitedMerchantInfo& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool TActTimeLimitedMerchantInfo::IsInitialized() const {

  return true;
}

void TActTimeLimitedMerchantInfo::Swap(TActTimeLimitedMerchantInfo* other) {
  if (other != this) {
    std::swap(id_, other->id_);
    std::swap(buynum_, other->buynum_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata TActTimeLimitedMerchantInfo::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = TActTimeLimitedMerchantInfo_descriptor_;
  metadata.reflection = TActTimeLimitedMerchantInfo_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int TActTimeLimitedMerchantGetInfoRsp::kArrInfoFieldNumber;
#endif  // !_MSC_VER

TActTimeLimitedMerchantGetInfoRsp::TActTimeLimitedMerchantGetInfoRsp()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:pb.TActTimeLimitedMerchantGetInfoRsp)
}

void TActTimeLimitedMerchantGetInfoRsp::InitAsDefaultInstance() {
}

TActTimeLimitedMerchantGetInfoRsp::TActTimeLimitedMerchantGetInfoRsp(const TActTimeLimitedMerchantGetInfoRsp& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:pb.TActTimeLimitedMerchantGetInfoRsp)
}

void TActTimeLimitedMerchantGetInfoRsp::SharedCtor() {
  _cached_size_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

TActTimeLimitedMerchantGetInfoRsp::~TActTimeLimitedMerchantGetInfoRsp() {
  // @@protoc_insertion_point(destructor:pb.TActTimeLimitedMerchantGetInfoRsp)
  SharedDtor();
}

void TActTimeLimitedMerchantGetInfoRsp::SharedDtor() {
  if (this != default_instance_) {
  }
}

void TActTimeLimitedMerchantGetInfoRsp::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* TActTimeLimitedMerchantGetInfoRsp::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return TActTimeLimitedMerchantGetInfoRsp_descriptor_;
}

const TActTimeLimitedMerchantGetInfoRsp& TActTimeLimitedMerchantGetInfoRsp::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_net_2fActTimeLimitedMerchant_2eproto();
  return *default_instance_;
}

TActTimeLimitedMerchantGetInfoRsp* TActTimeLimitedMerchantGetInfoRsp::default_instance_ = NULL;

TActTimeLimitedMerchantGetInfoRsp* TActTimeLimitedMerchantGetInfoRsp::New() const {
  return new TActTimeLimitedMerchantGetInfoRsp;
}

void TActTimeLimitedMerchantGetInfoRsp::Clear() {
  arrinfo_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool TActTimeLimitedMerchantGetInfoRsp::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:pb.TActTimeLimitedMerchantGetInfoRsp)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated .pb.TActTimeLimitedMerchantInfo ArrInfo = 1;
      case 1: {
        if (tag == 10) {
         parse_ArrInfo:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_arrinfo()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(10)) goto parse_ArrInfo;
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
  // @@protoc_insertion_point(parse_success:pb.TActTimeLimitedMerchantGetInfoRsp)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:pb.TActTimeLimitedMerchantGetInfoRsp)
  return false;
#undef DO_
}

void TActTimeLimitedMerchantGetInfoRsp::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:pb.TActTimeLimitedMerchantGetInfoRsp)
  // repeated .pb.TActTimeLimitedMerchantInfo ArrInfo = 1;
  for (int i = 0; i < this->arrinfo_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->arrinfo(i), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:pb.TActTimeLimitedMerchantGetInfoRsp)
}

::google::protobuf::uint8* TActTimeLimitedMerchantGetInfoRsp::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:pb.TActTimeLimitedMerchantGetInfoRsp)
  // repeated .pb.TActTimeLimitedMerchantInfo ArrInfo = 1;
  for (int i = 0; i < this->arrinfo_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        1, this->arrinfo(i), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:pb.TActTimeLimitedMerchantGetInfoRsp)
  return target;
}

int TActTimeLimitedMerchantGetInfoRsp::ByteSize() const {
  int total_size = 0;

  // repeated .pb.TActTimeLimitedMerchantInfo ArrInfo = 1;
  total_size += 1 * this->arrinfo_size();
  for (int i = 0; i < this->arrinfo_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->arrinfo(i));
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

void TActTimeLimitedMerchantGetInfoRsp::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const TActTimeLimitedMerchantGetInfoRsp* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const TActTimeLimitedMerchantGetInfoRsp*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void TActTimeLimitedMerchantGetInfoRsp::MergeFrom(const TActTimeLimitedMerchantGetInfoRsp& from) {
  GOOGLE_CHECK_NE(&from, this);
  arrinfo_.MergeFrom(from.arrinfo_);
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void TActTimeLimitedMerchantGetInfoRsp::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void TActTimeLimitedMerchantGetInfoRsp::CopyFrom(const TActTimeLimitedMerchantGetInfoRsp& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool TActTimeLimitedMerchantGetInfoRsp::IsInitialized() const {

  return true;
}

void TActTimeLimitedMerchantGetInfoRsp::Swap(TActTimeLimitedMerchantGetInfoRsp* other) {
  if (other != this) {
    arrinfo_.Swap(&other->arrinfo_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata TActTimeLimitedMerchantGetInfoRsp::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = TActTimeLimitedMerchantGetInfoRsp_descriptor_;
  metadata.reflection = TActTimeLimitedMerchantGetInfoRsp_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int TActTimeLimitedMerchantNotify::kArrInfoFieldNumber;
#endif  // !_MSC_VER

TActTimeLimitedMerchantNotify::TActTimeLimitedMerchantNotify()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:pb.TActTimeLimitedMerchantNotify)
}

void TActTimeLimitedMerchantNotify::InitAsDefaultInstance() {
}

TActTimeLimitedMerchantNotify::TActTimeLimitedMerchantNotify(const TActTimeLimitedMerchantNotify& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:pb.TActTimeLimitedMerchantNotify)
}

void TActTimeLimitedMerchantNotify::SharedCtor() {
  _cached_size_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

TActTimeLimitedMerchantNotify::~TActTimeLimitedMerchantNotify() {
  // @@protoc_insertion_point(destructor:pb.TActTimeLimitedMerchantNotify)
  SharedDtor();
}

void TActTimeLimitedMerchantNotify::SharedDtor() {
  if (this != default_instance_) {
  }
}

void TActTimeLimitedMerchantNotify::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* TActTimeLimitedMerchantNotify::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return TActTimeLimitedMerchantNotify_descriptor_;
}

const TActTimeLimitedMerchantNotify& TActTimeLimitedMerchantNotify::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_net_2fActTimeLimitedMerchant_2eproto();
  return *default_instance_;
}

TActTimeLimitedMerchantNotify* TActTimeLimitedMerchantNotify::default_instance_ = NULL;

TActTimeLimitedMerchantNotify* TActTimeLimitedMerchantNotify::New() const {
  return new TActTimeLimitedMerchantNotify;
}

void TActTimeLimitedMerchantNotify::Clear() {
  arrinfo_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool TActTimeLimitedMerchantNotify::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:pb.TActTimeLimitedMerchantNotify)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated .pb.TActTimeLimitedMerchantInfo ArrInfo = 1;
      case 1: {
        if (tag == 10) {
         parse_ArrInfo:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_arrinfo()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(10)) goto parse_ArrInfo;
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
  // @@protoc_insertion_point(parse_success:pb.TActTimeLimitedMerchantNotify)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:pb.TActTimeLimitedMerchantNotify)
  return false;
#undef DO_
}

void TActTimeLimitedMerchantNotify::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:pb.TActTimeLimitedMerchantNotify)
  // repeated .pb.TActTimeLimitedMerchantInfo ArrInfo = 1;
  for (int i = 0; i < this->arrinfo_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->arrinfo(i), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:pb.TActTimeLimitedMerchantNotify)
}

::google::protobuf::uint8* TActTimeLimitedMerchantNotify::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:pb.TActTimeLimitedMerchantNotify)
  // repeated .pb.TActTimeLimitedMerchantInfo ArrInfo = 1;
  for (int i = 0; i < this->arrinfo_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        1, this->arrinfo(i), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:pb.TActTimeLimitedMerchantNotify)
  return target;
}

int TActTimeLimitedMerchantNotify::ByteSize() const {
  int total_size = 0;

  // repeated .pb.TActTimeLimitedMerchantInfo ArrInfo = 1;
  total_size += 1 * this->arrinfo_size();
  for (int i = 0; i < this->arrinfo_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->arrinfo(i));
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

void TActTimeLimitedMerchantNotify::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const TActTimeLimitedMerchantNotify* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const TActTimeLimitedMerchantNotify*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void TActTimeLimitedMerchantNotify::MergeFrom(const TActTimeLimitedMerchantNotify& from) {
  GOOGLE_CHECK_NE(&from, this);
  arrinfo_.MergeFrom(from.arrinfo_);
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void TActTimeLimitedMerchantNotify::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void TActTimeLimitedMerchantNotify::CopyFrom(const TActTimeLimitedMerchantNotify& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool TActTimeLimitedMerchantNotify::IsInitialized() const {

  return true;
}

void TActTimeLimitedMerchantNotify::Swap(TActTimeLimitedMerchantNotify* other) {
  if (other != this) {
    arrinfo_.Swap(&other->arrinfo_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata TActTimeLimitedMerchantNotify::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = TActTimeLimitedMerchantNotify_descriptor_;
  metadata.reflection = TActTimeLimitedMerchantNotify_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace pb

// @@protoc_insertion_point(global_scope)