// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: net/ActFestivalPackage.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "net/ActFestivalPackage.pb.h"

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

const ::google::protobuf::Descriptor* TActFestivalPackageInfo_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  TActFestivalPackageInfo_reflection_ = NULL;
const ::google::protobuf::Descriptor* TActFestivalPackageGetInfoRsp_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  TActFestivalPackageGetInfoRsp_reflection_ = NULL;
const ::google::protobuf::Descriptor* TActFestivalPackageNotify_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  TActFestivalPackageNotify_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_net_2fActFestivalPackage_2eproto() {
  protobuf_AddDesc_net_2fActFestivalPackage_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "net/ActFestivalPackage.proto");
  GOOGLE_CHECK(file != NULL);
  TActFestivalPackageInfo_descriptor_ = file->message_type(0);
  static const int TActFestivalPackageInfo_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TActFestivalPackageInfo, id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TActFestivalPackageInfo, buynum_),
  };
  TActFestivalPackageInfo_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      TActFestivalPackageInfo_descriptor_,
      TActFestivalPackageInfo::default_instance_,
      TActFestivalPackageInfo_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TActFestivalPackageInfo, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TActFestivalPackageInfo, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(TActFestivalPackageInfo));
  TActFestivalPackageGetInfoRsp_descriptor_ = file->message_type(1);
  static const int TActFestivalPackageGetInfoRsp_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TActFestivalPackageGetInfoRsp, arrpackageinfo_),
  };
  TActFestivalPackageGetInfoRsp_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      TActFestivalPackageGetInfoRsp_descriptor_,
      TActFestivalPackageGetInfoRsp::default_instance_,
      TActFestivalPackageGetInfoRsp_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TActFestivalPackageGetInfoRsp, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TActFestivalPackageGetInfoRsp, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(TActFestivalPackageGetInfoRsp));
  TActFestivalPackageNotify_descriptor_ = file->message_type(2);
  static const int TActFestivalPackageNotify_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TActFestivalPackageNotify, arrpackageinfo_),
  };
  TActFestivalPackageNotify_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      TActFestivalPackageNotify_descriptor_,
      TActFestivalPackageNotify::default_instance_,
      TActFestivalPackageNotify_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TActFestivalPackageNotify, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TActFestivalPackageNotify, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(TActFestivalPackageNotify));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_net_2fActFestivalPackage_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    TActFestivalPackageInfo_descriptor_, &TActFestivalPackageInfo::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    TActFestivalPackageGetInfoRsp_descriptor_, &TActFestivalPackageGetInfoRsp::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    TActFestivalPackageNotify_descriptor_, &TActFestivalPackageNotify::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_net_2fActFestivalPackage_2eproto() {
  delete TActFestivalPackageInfo::default_instance_;
  delete TActFestivalPackageInfo_reflection_;
  delete TActFestivalPackageGetInfoRsp::default_instance_;
  delete TActFestivalPackageGetInfoRsp_reflection_;
  delete TActFestivalPackageNotify::default_instance_;
  delete TActFestivalPackageNotify_reflection_;
}

void protobuf_AddDesc_net_2fActFestivalPackage_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\034net/ActFestivalPackage.proto\022\002pb\"5\n\027TA"
    "ctFestivalPackageInfo\022\n\n\002Id\030\001 \001(\r\022\016\n\006Buy"
    "Num\030\002 \001(\r\"T\n\035TActFestivalPackageGetInfoR"
    "sp\0223\n\016ArrPackageInfo\030\001 \003(\0132\033.pb.TActFest"
    "ivalPackageInfo\"P\n\031TActFestivalPackageNo"
    "tify\0223\n\016ArrPackageInfo\030\001 \003(\0132\033.pb.TActFe"
    "stivalPackageInfo", 257);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "net/ActFestivalPackage.proto", &protobuf_RegisterTypes);
  TActFestivalPackageInfo::default_instance_ = new TActFestivalPackageInfo();
  TActFestivalPackageGetInfoRsp::default_instance_ = new TActFestivalPackageGetInfoRsp();
  TActFestivalPackageNotify::default_instance_ = new TActFestivalPackageNotify();
  TActFestivalPackageInfo::default_instance_->InitAsDefaultInstance();
  TActFestivalPackageGetInfoRsp::default_instance_->InitAsDefaultInstance();
  TActFestivalPackageNotify::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_net_2fActFestivalPackage_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_net_2fActFestivalPackage_2eproto {
  StaticDescriptorInitializer_net_2fActFestivalPackage_2eproto() {
    protobuf_AddDesc_net_2fActFestivalPackage_2eproto();
  }
} static_descriptor_initializer_net_2fActFestivalPackage_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int TActFestivalPackageInfo::kIdFieldNumber;
const int TActFestivalPackageInfo::kBuyNumFieldNumber;
#endif  // !_MSC_VER

TActFestivalPackageInfo::TActFestivalPackageInfo()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:pb.TActFestivalPackageInfo)
}

void TActFestivalPackageInfo::InitAsDefaultInstance() {
}

TActFestivalPackageInfo::TActFestivalPackageInfo(const TActFestivalPackageInfo& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:pb.TActFestivalPackageInfo)
}

void TActFestivalPackageInfo::SharedCtor() {
  _cached_size_ = 0;
  id_ = 0u;
  buynum_ = 0u;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

TActFestivalPackageInfo::~TActFestivalPackageInfo() {
  // @@protoc_insertion_point(destructor:pb.TActFestivalPackageInfo)
  SharedDtor();
}

void TActFestivalPackageInfo::SharedDtor() {
  if (this != default_instance_) {
  }
}

void TActFestivalPackageInfo::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* TActFestivalPackageInfo::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return TActFestivalPackageInfo_descriptor_;
}

const TActFestivalPackageInfo& TActFestivalPackageInfo::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_net_2fActFestivalPackage_2eproto();
  return *default_instance_;
}

TActFestivalPackageInfo* TActFestivalPackageInfo::default_instance_ = NULL;

TActFestivalPackageInfo* TActFestivalPackageInfo::New() const {
  return new TActFestivalPackageInfo;
}

void TActFestivalPackageInfo::Clear() {
#define OFFSET_OF_FIELD_(f) (reinterpret_cast<char*>(      \
  &reinterpret_cast<TActFestivalPackageInfo*>(16)->f) - \
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

bool TActFestivalPackageInfo::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:pb.TActFestivalPackageInfo)
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
  // @@protoc_insertion_point(parse_success:pb.TActFestivalPackageInfo)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:pb.TActFestivalPackageInfo)
  return false;
#undef DO_
}

void TActFestivalPackageInfo::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:pb.TActFestivalPackageInfo)
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
  // @@protoc_insertion_point(serialize_end:pb.TActFestivalPackageInfo)
}

::google::protobuf::uint8* TActFestivalPackageInfo::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:pb.TActFestivalPackageInfo)
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
  // @@protoc_insertion_point(serialize_to_array_end:pb.TActFestivalPackageInfo)
  return target;
}

int TActFestivalPackageInfo::ByteSize() const {
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

void TActFestivalPackageInfo::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const TActFestivalPackageInfo* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const TActFestivalPackageInfo*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void TActFestivalPackageInfo::MergeFrom(const TActFestivalPackageInfo& from) {
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

void TActFestivalPackageInfo::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void TActFestivalPackageInfo::CopyFrom(const TActFestivalPackageInfo& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool TActFestivalPackageInfo::IsInitialized() const {

  return true;
}

void TActFestivalPackageInfo::Swap(TActFestivalPackageInfo* other) {
  if (other != this) {
    std::swap(id_, other->id_);
    std::swap(buynum_, other->buynum_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata TActFestivalPackageInfo::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = TActFestivalPackageInfo_descriptor_;
  metadata.reflection = TActFestivalPackageInfo_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int TActFestivalPackageGetInfoRsp::kArrPackageInfoFieldNumber;
#endif  // !_MSC_VER

TActFestivalPackageGetInfoRsp::TActFestivalPackageGetInfoRsp()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:pb.TActFestivalPackageGetInfoRsp)
}

void TActFestivalPackageGetInfoRsp::InitAsDefaultInstance() {
}

TActFestivalPackageGetInfoRsp::TActFestivalPackageGetInfoRsp(const TActFestivalPackageGetInfoRsp& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:pb.TActFestivalPackageGetInfoRsp)
}

void TActFestivalPackageGetInfoRsp::SharedCtor() {
  _cached_size_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

TActFestivalPackageGetInfoRsp::~TActFestivalPackageGetInfoRsp() {
  // @@protoc_insertion_point(destructor:pb.TActFestivalPackageGetInfoRsp)
  SharedDtor();
}

void TActFestivalPackageGetInfoRsp::SharedDtor() {
  if (this != default_instance_) {
  }
}

void TActFestivalPackageGetInfoRsp::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* TActFestivalPackageGetInfoRsp::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return TActFestivalPackageGetInfoRsp_descriptor_;
}

const TActFestivalPackageGetInfoRsp& TActFestivalPackageGetInfoRsp::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_net_2fActFestivalPackage_2eproto();
  return *default_instance_;
}

TActFestivalPackageGetInfoRsp* TActFestivalPackageGetInfoRsp::default_instance_ = NULL;

TActFestivalPackageGetInfoRsp* TActFestivalPackageGetInfoRsp::New() const {
  return new TActFestivalPackageGetInfoRsp;
}

void TActFestivalPackageGetInfoRsp::Clear() {
  arrpackageinfo_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool TActFestivalPackageGetInfoRsp::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:pb.TActFestivalPackageGetInfoRsp)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated .pb.TActFestivalPackageInfo ArrPackageInfo = 1;
      case 1: {
        if (tag == 10) {
         parse_ArrPackageInfo:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_arrpackageinfo()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(10)) goto parse_ArrPackageInfo;
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
  // @@protoc_insertion_point(parse_success:pb.TActFestivalPackageGetInfoRsp)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:pb.TActFestivalPackageGetInfoRsp)
  return false;
#undef DO_
}

void TActFestivalPackageGetInfoRsp::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:pb.TActFestivalPackageGetInfoRsp)
  // repeated .pb.TActFestivalPackageInfo ArrPackageInfo = 1;
  for (int i = 0; i < this->arrpackageinfo_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->arrpackageinfo(i), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:pb.TActFestivalPackageGetInfoRsp)
}

::google::protobuf::uint8* TActFestivalPackageGetInfoRsp::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:pb.TActFestivalPackageGetInfoRsp)
  // repeated .pb.TActFestivalPackageInfo ArrPackageInfo = 1;
  for (int i = 0; i < this->arrpackageinfo_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        1, this->arrpackageinfo(i), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:pb.TActFestivalPackageGetInfoRsp)
  return target;
}

int TActFestivalPackageGetInfoRsp::ByteSize() const {
  int total_size = 0;

  // repeated .pb.TActFestivalPackageInfo ArrPackageInfo = 1;
  total_size += 1 * this->arrpackageinfo_size();
  for (int i = 0; i < this->arrpackageinfo_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->arrpackageinfo(i));
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

void TActFestivalPackageGetInfoRsp::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const TActFestivalPackageGetInfoRsp* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const TActFestivalPackageGetInfoRsp*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void TActFestivalPackageGetInfoRsp::MergeFrom(const TActFestivalPackageGetInfoRsp& from) {
  GOOGLE_CHECK_NE(&from, this);
  arrpackageinfo_.MergeFrom(from.arrpackageinfo_);
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void TActFestivalPackageGetInfoRsp::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void TActFestivalPackageGetInfoRsp::CopyFrom(const TActFestivalPackageGetInfoRsp& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool TActFestivalPackageGetInfoRsp::IsInitialized() const {

  return true;
}

void TActFestivalPackageGetInfoRsp::Swap(TActFestivalPackageGetInfoRsp* other) {
  if (other != this) {
    arrpackageinfo_.Swap(&other->arrpackageinfo_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata TActFestivalPackageGetInfoRsp::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = TActFestivalPackageGetInfoRsp_descriptor_;
  metadata.reflection = TActFestivalPackageGetInfoRsp_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int TActFestivalPackageNotify::kArrPackageInfoFieldNumber;
#endif  // !_MSC_VER

TActFestivalPackageNotify::TActFestivalPackageNotify()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:pb.TActFestivalPackageNotify)
}

void TActFestivalPackageNotify::InitAsDefaultInstance() {
}

TActFestivalPackageNotify::TActFestivalPackageNotify(const TActFestivalPackageNotify& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:pb.TActFestivalPackageNotify)
}

void TActFestivalPackageNotify::SharedCtor() {
  _cached_size_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

TActFestivalPackageNotify::~TActFestivalPackageNotify() {
  // @@protoc_insertion_point(destructor:pb.TActFestivalPackageNotify)
  SharedDtor();
}

void TActFestivalPackageNotify::SharedDtor() {
  if (this != default_instance_) {
  }
}

void TActFestivalPackageNotify::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* TActFestivalPackageNotify::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return TActFestivalPackageNotify_descriptor_;
}

const TActFestivalPackageNotify& TActFestivalPackageNotify::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_net_2fActFestivalPackage_2eproto();
  return *default_instance_;
}

TActFestivalPackageNotify* TActFestivalPackageNotify::default_instance_ = NULL;

TActFestivalPackageNotify* TActFestivalPackageNotify::New() const {
  return new TActFestivalPackageNotify;
}

void TActFestivalPackageNotify::Clear() {
  arrpackageinfo_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool TActFestivalPackageNotify::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:pb.TActFestivalPackageNotify)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated .pb.TActFestivalPackageInfo ArrPackageInfo = 1;
      case 1: {
        if (tag == 10) {
         parse_ArrPackageInfo:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_arrpackageinfo()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(10)) goto parse_ArrPackageInfo;
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
  // @@protoc_insertion_point(parse_success:pb.TActFestivalPackageNotify)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:pb.TActFestivalPackageNotify)
  return false;
#undef DO_
}

void TActFestivalPackageNotify::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:pb.TActFestivalPackageNotify)
  // repeated .pb.TActFestivalPackageInfo ArrPackageInfo = 1;
  for (int i = 0; i < this->arrpackageinfo_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->arrpackageinfo(i), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:pb.TActFestivalPackageNotify)
}

::google::protobuf::uint8* TActFestivalPackageNotify::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:pb.TActFestivalPackageNotify)
  // repeated .pb.TActFestivalPackageInfo ArrPackageInfo = 1;
  for (int i = 0; i < this->arrpackageinfo_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        1, this->arrpackageinfo(i), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:pb.TActFestivalPackageNotify)
  return target;
}

int TActFestivalPackageNotify::ByteSize() const {
  int total_size = 0;

  // repeated .pb.TActFestivalPackageInfo ArrPackageInfo = 1;
  total_size += 1 * this->arrpackageinfo_size();
  for (int i = 0; i < this->arrpackageinfo_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->arrpackageinfo(i));
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

void TActFestivalPackageNotify::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const TActFestivalPackageNotify* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const TActFestivalPackageNotify*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void TActFestivalPackageNotify::MergeFrom(const TActFestivalPackageNotify& from) {
  GOOGLE_CHECK_NE(&from, this);
  arrpackageinfo_.MergeFrom(from.arrpackageinfo_);
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void TActFestivalPackageNotify::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void TActFestivalPackageNotify::CopyFrom(const TActFestivalPackageNotify& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool TActFestivalPackageNotify::IsInitialized() const {

  return true;
}

void TActFestivalPackageNotify::Swap(TActFestivalPackageNotify* other) {
  if (other != this) {
    arrpackageinfo_.Swap(&other->arrpackageinfo_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata TActFestivalPackageNotify::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = TActFestivalPackageNotify_descriptor_;
  metadata.reflection = TActFestivalPackageNotify_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace pb

// @@protoc_insertion_point(global_scope)
