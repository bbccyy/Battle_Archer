// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: net/ActBackGroundPush.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "net/ActBackGroundPush.pb.h"

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

const ::google::protobuf::Descriptor* TActBackgroundPushGiftInfo_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  TActBackgroundPushGiftInfo_reflection_ = NULL;
const ::google::protobuf::Descriptor* TActBackgroundPushGetInfoRsp_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  TActBackgroundPushGetInfoRsp_reflection_ = NULL;
const ::google::protobuf::Descriptor* TActBackgroundPushNotify_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  TActBackgroundPushNotify_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_net_2fActBackGroundPush_2eproto() {
  protobuf_AddDesc_net_2fActBackGroundPush_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "net/ActBackGroundPush.proto");
  GOOGLE_CHECK(file != NULL);
  TActBackgroundPushGiftInfo_descriptor_ = file->message_type(0);
  static const int TActBackgroundPushGiftInfo_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TActBackgroundPushGiftInfo, giftid_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TActBackgroundPushGiftInfo, buynum_),
  };
  TActBackgroundPushGiftInfo_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      TActBackgroundPushGiftInfo_descriptor_,
      TActBackgroundPushGiftInfo::default_instance_,
      TActBackgroundPushGiftInfo_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TActBackgroundPushGiftInfo, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TActBackgroundPushGiftInfo, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(TActBackgroundPushGiftInfo));
  TActBackgroundPushGetInfoRsp_descriptor_ = file->message_type(1);
  static const int TActBackgroundPushGetInfoRsp_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TActBackgroundPushGetInfoRsp, isopen_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TActBackgroundPushGetInfoRsp, giftarr_),
  };
  TActBackgroundPushGetInfoRsp_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      TActBackgroundPushGetInfoRsp_descriptor_,
      TActBackgroundPushGetInfoRsp::default_instance_,
      TActBackgroundPushGetInfoRsp_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TActBackgroundPushGetInfoRsp, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TActBackgroundPushGetInfoRsp, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(TActBackgroundPushGetInfoRsp));
  TActBackgroundPushNotify_descriptor_ = file->message_type(2);
  static const int TActBackgroundPushNotify_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TActBackgroundPushNotify, giftarr_),
  };
  TActBackgroundPushNotify_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      TActBackgroundPushNotify_descriptor_,
      TActBackgroundPushNotify::default_instance_,
      TActBackgroundPushNotify_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TActBackgroundPushNotify, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TActBackgroundPushNotify, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(TActBackgroundPushNotify));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_net_2fActBackGroundPush_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    TActBackgroundPushGiftInfo_descriptor_, &TActBackgroundPushGiftInfo::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    TActBackgroundPushGetInfoRsp_descriptor_, &TActBackgroundPushGetInfoRsp::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    TActBackgroundPushNotify_descriptor_, &TActBackgroundPushNotify::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_net_2fActBackGroundPush_2eproto() {
  delete TActBackgroundPushGiftInfo::default_instance_;
  delete TActBackgroundPushGiftInfo_reflection_;
  delete TActBackgroundPushGetInfoRsp::default_instance_;
  delete TActBackgroundPushGetInfoRsp_reflection_;
  delete TActBackgroundPushNotify::default_instance_;
  delete TActBackgroundPushNotify_reflection_;
}

void protobuf_AddDesc_net_2fActBackGroundPush_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\033net/ActBackGroundPush.proto\022\002pb\"<\n\032TAc"
    "tBackgroundPushGiftInfo\022\016\n\006GiftId\030\001 \001(\r\022"
    "\016\n\006BuyNum\030\002 \001(\r\"_\n\034TActBackgroundPushGet"
    "InfoRsp\022\016\n\006IsOpen\030\001 \001(\010\022/\n\007GiftArr\030\002 \003(\013"
    "2\036.pb.TActBackgroundPushGiftInfo\"K\n\030TAct"
    "BackgroundPushNotify\022/\n\007GiftArr\030\001 \003(\0132\036."
    "pb.TActBackgroundPushGiftInfo", 269);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "net/ActBackGroundPush.proto", &protobuf_RegisterTypes);
  TActBackgroundPushGiftInfo::default_instance_ = new TActBackgroundPushGiftInfo();
  TActBackgroundPushGetInfoRsp::default_instance_ = new TActBackgroundPushGetInfoRsp();
  TActBackgroundPushNotify::default_instance_ = new TActBackgroundPushNotify();
  TActBackgroundPushGiftInfo::default_instance_->InitAsDefaultInstance();
  TActBackgroundPushGetInfoRsp::default_instance_->InitAsDefaultInstance();
  TActBackgroundPushNotify::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_net_2fActBackGroundPush_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_net_2fActBackGroundPush_2eproto {
  StaticDescriptorInitializer_net_2fActBackGroundPush_2eproto() {
    protobuf_AddDesc_net_2fActBackGroundPush_2eproto();
  }
} static_descriptor_initializer_net_2fActBackGroundPush_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int TActBackgroundPushGiftInfo::kGiftIdFieldNumber;
const int TActBackgroundPushGiftInfo::kBuyNumFieldNumber;
#endif  // !_MSC_VER

TActBackgroundPushGiftInfo::TActBackgroundPushGiftInfo()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:pb.TActBackgroundPushGiftInfo)
}

void TActBackgroundPushGiftInfo::InitAsDefaultInstance() {
}

TActBackgroundPushGiftInfo::TActBackgroundPushGiftInfo(const TActBackgroundPushGiftInfo& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:pb.TActBackgroundPushGiftInfo)
}

void TActBackgroundPushGiftInfo::SharedCtor() {
  _cached_size_ = 0;
  giftid_ = 0u;
  buynum_ = 0u;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

TActBackgroundPushGiftInfo::~TActBackgroundPushGiftInfo() {
  // @@protoc_insertion_point(destructor:pb.TActBackgroundPushGiftInfo)
  SharedDtor();
}

void TActBackgroundPushGiftInfo::SharedDtor() {
  if (this != default_instance_) {
  }
}

void TActBackgroundPushGiftInfo::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* TActBackgroundPushGiftInfo::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return TActBackgroundPushGiftInfo_descriptor_;
}

const TActBackgroundPushGiftInfo& TActBackgroundPushGiftInfo::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_net_2fActBackGroundPush_2eproto();
  return *default_instance_;
}

TActBackgroundPushGiftInfo* TActBackgroundPushGiftInfo::default_instance_ = NULL;

TActBackgroundPushGiftInfo* TActBackgroundPushGiftInfo::New() const {
  return new TActBackgroundPushGiftInfo;
}

void TActBackgroundPushGiftInfo::Clear() {
#define OFFSET_OF_FIELD_(f) (reinterpret_cast<char*>(      \
  &reinterpret_cast<TActBackgroundPushGiftInfo*>(16)->f) - \
   reinterpret_cast<char*>(16))

#define ZR_(first, last) do {                              \
    size_t f = OFFSET_OF_FIELD_(first);                    \
    size_t n = OFFSET_OF_FIELD_(last) - f + sizeof(last);  \
    ::memset(&first, 0, n);                                \
  } while (0)

  ZR_(giftid_, buynum_);

#undef OFFSET_OF_FIELD_
#undef ZR_

  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool TActBackgroundPushGiftInfo::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:pb.TActBackgroundPushGiftInfo)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional uint32 GiftId = 1;
      case 1: {
        if (tag == 8) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &giftid_)));
          set_has_giftid();
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
  // @@protoc_insertion_point(parse_success:pb.TActBackgroundPushGiftInfo)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:pb.TActBackgroundPushGiftInfo)
  return false;
#undef DO_
}

void TActBackgroundPushGiftInfo::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:pb.TActBackgroundPushGiftInfo)
  // optional uint32 GiftId = 1;
  if (has_giftid()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->giftid(), output);
  }

  // optional uint32 BuyNum = 2;
  if (has_buynum()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(2, this->buynum(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:pb.TActBackgroundPushGiftInfo)
}

::google::protobuf::uint8* TActBackgroundPushGiftInfo::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:pb.TActBackgroundPushGiftInfo)
  // optional uint32 GiftId = 1;
  if (has_giftid()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->giftid(), target);
  }

  // optional uint32 BuyNum = 2;
  if (has_buynum()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(2, this->buynum(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:pb.TActBackgroundPushGiftInfo)
  return target;
}

int TActBackgroundPushGiftInfo::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional uint32 GiftId = 1;
    if (has_giftid()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->giftid());
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

void TActBackgroundPushGiftInfo::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const TActBackgroundPushGiftInfo* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const TActBackgroundPushGiftInfo*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void TActBackgroundPushGiftInfo::MergeFrom(const TActBackgroundPushGiftInfo& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_giftid()) {
      set_giftid(from.giftid());
    }
    if (from.has_buynum()) {
      set_buynum(from.buynum());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void TActBackgroundPushGiftInfo::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void TActBackgroundPushGiftInfo::CopyFrom(const TActBackgroundPushGiftInfo& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool TActBackgroundPushGiftInfo::IsInitialized() const {

  return true;
}

void TActBackgroundPushGiftInfo::Swap(TActBackgroundPushGiftInfo* other) {
  if (other != this) {
    std::swap(giftid_, other->giftid_);
    std::swap(buynum_, other->buynum_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata TActBackgroundPushGiftInfo::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = TActBackgroundPushGiftInfo_descriptor_;
  metadata.reflection = TActBackgroundPushGiftInfo_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int TActBackgroundPushGetInfoRsp::kIsOpenFieldNumber;
const int TActBackgroundPushGetInfoRsp::kGiftArrFieldNumber;
#endif  // !_MSC_VER

TActBackgroundPushGetInfoRsp::TActBackgroundPushGetInfoRsp()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:pb.TActBackgroundPushGetInfoRsp)
}

void TActBackgroundPushGetInfoRsp::InitAsDefaultInstance() {
}

TActBackgroundPushGetInfoRsp::TActBackgroundPushGetInfoRsp(const TActBackgroundPushGetInfoRsp& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:pb.TActBackgroundPushGetInfoRsp)
}

void TActBackgroundPushGetInfoRsp::SharedCtor() {
  _cached_size_ = 0;
  isopen_ = false;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

TActBackgroundPushGetInfoRsp::~TActBackgroundPushGetInfoRsp() {
  // @@protoc_insertion_point(destructor:pb.TActBackgroundPushGetInfoRsp)
  SharedDtor();
}

void TActBackgroundPushGetInfoRsp::SharedDtor() {
  if (this != default_instance_) {
  }
}

void TActBackgroundPushGetInfoRsp::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* TActBackgroundPushGetInfoRsp::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return TActBackgroundPushGetInfoRsp_descriptor_;
}

const TActBackgroundPushGetInfoRsp& TActBackgroundPushGetInfoRsp::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_net_2fActBackGroundPush_2eproto();
  return *default_instance_;
}

TActBackgroundPushGetInfoRsp* TActBackgroundPushGetInfoRsp::default_instance_ = NULL;

TActBackgroundPushGetInfoRsp* TActBackgroundPushGetInfoRsp::New() const {
  return new TActBackgroundPushGetInfoRsp;
}

void TActBackgroundPushGetInfoRsp::Clear() {
  isopen_ = false;
  giftarr_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool TActBackgroundPushGetInfoRsp::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:pb.TActBackgroundPushGetInfoRsp)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional bool IsOpen = 1;
      case 1: {
        if (tag == 8) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &isopen_)));
          set_has_isopen();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(18)) goto parse_GiftArr;
        break;
      }

      // repeated .pb.TActBackgroundPushGiftInfo GiftArr = 2;
      case 2: {
        if (tag == 18) {
         parse_GiftArr:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_giftarr()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(18)) goto parse_GiftArr;
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
  // @@protoc_insertion_point(parse_success:pb.TActBackgroundPushGetInfoRsp)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:pb.TActBackgroundPushGetInfoRsp)
  return false;
#undef DO_
}

void TActBackgroundPushGetInfoRsp::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:pb.TActBackgroundPushGetInfoRsp)
  // optional bool IsOpen = 1;
  if (has_isopen()) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(1, this->isopen(), output);
  }

  // repeated .pb.TActBackgroundPushGiftInfo GiftArr = 2;
  for (int i = 0; i < this->giftarr_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      2, this->giftarr(i), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:pb.TActBackgroundPushGetInfoRsp)
}

::google::protobuf::uint8* TActBackgroundPushGetInfoRsp::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:pb.TActBackgroundPushGetInfoRsp)
  // optional bool IsOpen = 1;
  if (has_isopen()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(1, this->isopen(), target);
  }

  // repeated .pb.TActBackgroundPushGiftInfo GiftArr = 2;
  for (int i = 0; i < this->giftarr_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        2, this->giftarr(i), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:pb.TActBackgroundPushGetInfoRsp)
  return target;
}

int TActBackgroundPushGetInfoRsp::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional bool IsOpen = 1;
    if (has_isopen()) {
      total_size += 1 + 1;
    }

  }
  // repeated .pb.TActBackgroundPushGiftInfo GiftArr = 2;
  total_size += 1 * this->giftarr_size();
  for (int i = 0; i < this->giftarr_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->giftarr(i));
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

void TActBackgroundPushGetInfoRsp::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const TActBackgroundPushGetInfoRsp* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const TActBackgroundPushGetInfoRsp*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void TActBackgroundPushGetInfoRsp::MergeFrom(const TActBackgroundPushGetInfoRsp& from) {
  GOOGLE_CHECK_NE(&from, this);
  giftarr_.MergeFrom(from.giftarr_);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_isopen()) {
      set_isopen(from.isopen());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void TActBackgroundPushGetInfoRsp::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void TActBackgroundPushGetInfoRsp::CopyFrom(const TActBackgroundPushGetInfoRsp& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool TActBackgroundPushGetInfoRsp::IsInitialized() const {

  return true;
}

void TActBackgroundPushGetInfoRsp::Swap(TActBackgroundPushGetInfoRsp* other) {
  if (other != this) {
    std::swap(isopen_, other->isopen_);
    giftarr_.Swap(&other->giftarr_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata TActBackgroundPushGetInfoRsp::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = TActBackgroundPushGetInfoRsp_descriptor_;
  metadata.reflection = TActBackgroundPushGetInfoRsp_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int TActBackgroundPushNotify::kGiftArrFieldNumber;
#endif  // !_MSC_VER

TActBackgroundPushNotify::TActBackgroundPushNotify()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:pb.TActBackgroundPushNotify)
}

void TActBackgroundPushNotify::InitAsDefaultInstance() {
}

TActBackgroundPushNotify::TActBackgroundPushNotify(const TActBackgroundPushNotify& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:pb.TActBackgroundPushNotify)
}

void TActBackgroundPushNotify::SharedCtor() {
  _cached_size_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

TActBackgroundPushNotify::~TActBackgroundPushNotify() {
  // @@protoc_insertion_point(destructor:pb.TActBackgroundPushNotify)
  SharedDtor();
}

void TActBackgroundPushNotify::SharedDtor() {
  if (this != default_instance_) {
  }
}

void TActBackgroundPushNotify::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* TActBackgroundPushNotify::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return TActBackgroundPushNotify_descriptor_;
}

const TActBackgroundPushNotify& TActBackgroundPushNotify::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_net_2fActBackGroundPush_2eproto();
  return *default_instance_;
}

TActBackgroundPushNotify* TActBackgroundPushNotify::default_instance_ = NULL;

TActBackgroundPushNotify* TActBackgroundPushNotify::New() const {
  return new TActBackgroundPushNotify;
}

void TActBackgroundPushNotify::Clear() {
  giftarr_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool TActBackgroundPushNotify::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:pb.TActBackgroundPushNotify)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated .pb.TActBackgroundPushGiftInfo GiftArr = 1;
      case 1: {
        if (tag == 10) {
         parse_GiftArr:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_giftarr()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(10)) goto parse_GiftArr;
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
  // @@protoc_insertion_point(parse_success:pb.TActBackgroundPushNotify)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:pb.TActBackgroundPushNotify)
  return false;
#undef DO_
}

void TActBackgroundPushNotify::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:pb.TActBackgroundPushNotify)
  // repeated .pb.TActBackgroundPushGiftInfo GiftArr = 1;
  for (int i = 0; i < this->giftarr_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->giftarr(i), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:pb.TActBackgroundPushNotify)
}

::google::protobuf::uint8* TActBackgroundPushNotify::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:pb.TActBackgroundPushNotify)
  // repeated .pb.TActBackgroundPushGiftInfo GiftArr = 1;
  for (int i = 0; i < this->giftarr_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        1, this->giftarr(i), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:pb.TActBackgroundPushNotify)
  return target;
}

int TActBackgroundPushNotify::ByteSize() const {
  int total_size = 0;

  // repeated .pb.TActBackgroundPushGiftInfo GiftArr = 1;
  total_size += 1 * this->giftarr_size();
  for (int i = 0; i < this->giftarr_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->giftarr(i));
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

void TActBackgroundPushNotify::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const TActBackgroundPushNotify* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const TActBackgroundPushNotify*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void TActBackgroundPushNotify::MergeFrom(const TActBackgroundPushNotify& from) {
  GOOGLE_CHECK_NE(&from, this);
  giftarr_.MergeFrom(from.giftarr_);
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void TActBackgroundPushNotify::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void TActBackgroundPushNotify::CopyFrom(const TActBackgroundPushNotify& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool TActBackgroundPushNotify::IsInitialized() const {

  return true;
}

void TActBackgroundPushNotify::Swap(TActBackgroundPushNotify* other) {
  if (other != this) {
    giftarr_.Swap(&other->giftarr_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata TActBackgroundPushNotify::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = TActBackgroundPushNotify_descriptor_;
  metadata.reflection = TActBackgroundPushNotify_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace pb

// @@protoc_insertion_point(global_scope)
