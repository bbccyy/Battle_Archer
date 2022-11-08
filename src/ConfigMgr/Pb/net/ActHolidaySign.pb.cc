// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: net/ActHolidaySign.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "net/ActHolidaySign.pb.h"

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

const ::google::protobuf::Descriptor* TActHolidaySignGetInfoReq_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  TActHolidaySignGetInfoReq_reflection_ = NULL;
const ::google::protobuf::Descriptor* TActHolidaySignGetInfoRsp_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  TActHolidaySignGetInfoRsp_reflection_ = NULL;
const ::google::protobuf::Descriptor* TActHolidaySignGetRewardReq_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  TActHolidaySignGetRewardReq_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_net_2fActHolidaySign_2eproto() {
  protobuf_AddDesc_net_2fActHolidaySign_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "net/ActHolidaySign.proto");
  GOOGLE_CHECK(file != NULL);
  TActHolidaySignGetInfoReq_descriptor_ = file->message_type(0);
  static const int TActHolidaySignGetInfoReq_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TActHolidaySignGetInfoReq, actid_),
  };
  TActHolidaySignGetInfoReq_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      TActHolidaySignGetInfoReq_descriptor_,
      TActHolidaySignGetInfoReq::default_instance_,
      TActHolidaySignGetInfoReq_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TActHolidaySignGetInfoReq, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TActHolidaySignGetInfoReq, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(TActHolidaySignGetInfoReq));
  TActHolidaySignGetInfoRsp_descriptor_ = file->message_type(1);
  static const int TActHolidaySignGetInfoRsp_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TActHolidaySignGetInfoRsp, accudaynum_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TActHolidaySignGetInfoRsp, arrrewardday_),
  };
  TActHolidaySignGetInfoRsp_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      TActHolidaySignGetInfoRsp_descriptor_,
      TActHolidaySignGetInfoRsp::default_instance_,
      TActHolidaySignGetInfoRsp_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TActHolidaySignGetInfoRsp, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TActHolidaySignGetInfoRsp, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(TActHolidaySignGetInfoRsp));
  TActHolidaySignGetRewardReq_descriptor_ = file->message_type(2);
  static const int TActHolidaySignGetRewardReq_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TActHolidaySignGetRewardReq, actid_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TActHolidaySignGetRewardReq, day_),
  };
  TActHolidaySignGetRewardReq_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      TActHolidaySignGetRewardReq_descriptor_,
      TActHolidaySignGetRewardReq::default_instance_,
      TActHolidaySignGetRewardReq_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TActHolidaySignGetRewardReq, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TActHolidaySignGetRewardReq, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(TActHolidaySignGetRewardReq));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_net_2fActHolidaySign_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    TActHolidaySignGetInfoReq_descriptor_, &TActHolidaySignGetInfoReq::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    TActHolidaySignGetInfoRsp_descriptor_, &TActHolidaySignGetInfoRsp::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    TActHolidaySignGetRewardReq_descriptor_, &TActHolidaySignGetRewardReq::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_net_2fActHolidaySign_2eproto() {
  delete TActHolidaySignGetInfoReq::default_instance_;
  delete TActHolidaySignGetInfoReq_reflection_;
  delete TActHolidaySignGetInfoRsp::default_instance_;
  delete TActHolidaySignGetInfoRsp_reflection_;
  delete TActHolidaySignGetRewardReq::default_instance_;
  delete TActHolidaySignGetRewardReq_reflection_;
}

void protobuf_AddDesc_net_2fActHolidaySign_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\030net/ActHolidaySign.proto\022\002pb\"*\n\031TActHo"
    "lidaySignGetInfoReq\022\r\n\005ActId\030\001 \001(\r\"E\n\031TA"
    "ctHolidaySignGetInfoRsp\022\022\n\nAccuDayNum\030\001 "
    "\001(\r\022\024\n\014arrRewardDay\030\002 \003(\r\"9\n\033TActHoliday"
    "SignGetRewardReq\022\r\n\005ActId\030\001 \001(\r\022\013\n\003Day\030\002"
    " \001(\r", 204);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "net/ActHolidaySign.proto", &protobuf_RegisterTypes);
  TActHolidaySignGetInfoReq::default_instance_ = new TActHolidaySignGetInfoReq();
  TActHolidaySignGetInfoRsp::default_instance_ = new TActHolidaySignGetInfoRsp();
  TActHolidaySignGetRewardReq::default_instance_ = new TActHolidaySignGetRewardReq();
  TActHolidaySignGetInfoReq::default_instance_->InitAsDefaultInstance();
  TActHolidaySignGetInfoRsp::default_instance_->InitAsDefaultInstance();
  TActHolidaySignGetRewardReq::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_net_2fActHolidaySign_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_net_2fActHolidaySign_2eproto {
  StaticDescriptorInitializer_net_2fActHolidaySign_2eproto() {
    protobuf_AddDesc_net_2fActHolidaySign_2eproto();
  }
} static_descriptor_initializer_net_2fActHolidaySign_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int TActHolidaySignGetInfoReq::kActIdFieldNumber;
#endif  // !_MSC_VER

TActHolidaySignGetInfoReq::TActHolidaySignGetInfoReq()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:pb.TActHolidaySignGetInfoReq)
}

void TActHolidaySignGetInfoReq::InitAsDefaultInstance() {
}

TActHolidaySignGetInfoReq::TActHolidaySignGetInfoReq(const TActHolidaySignGetInfoReq& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:pb.TActHolidaySignGetInfoReq)
}

void TActHolidaySignGetInfoReq::SharedCtor() {
  _cached_size_ = 0;
  actid_ = 0u;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

TActHolidaySignGetInfoReq::~TActHolidaySignGetInfoReq() {
  // @@protoc_insertion_point(destructor:pb.TActHolidaySignGetInfoReq)
  SharedDtor();
}

void TActHolidaySignGetInfoReq::SharedDtor() {
  if (this != default_instance_) {
  }
}

void TActHolidaySignGetInfoReq::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* TActHolidaySignGetInfoReq::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return TActHolidaySignGetInfoReq_descriptor_;
}

const TActHolidaySignGetInfoReq& TActHolidaySignGetInfoReq::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_net_2fActHolidaySign_2eproto();
  return *default_instance_;
}

TActHolidaySignGetInfoReq* TActHolidaySignGetInfoReq::default_instance_ = NULL;

TActHolidaySignGetInfoReq* TActHolidaySignGetInfoReq::New() const {
  return new TActHolidaySignGetInfoReq;
}

void TActHolidaySignGetInfoReq::Clear() {
  actid_ = 0u;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool TActHolidaySignGetInfoReq::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:pb.TActHolidaySignGetInfoReq)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional uint32 ActId = 1;
      case 1: {
        if (tag == 8) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &actid_)));
          set_has_actid();
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
  // @@protoc_insertion_point(parse_success:pb.TActHolidaySignGetInfoReq)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:pb.TActHolidaySignGetInfoReq)
  return false;
#undef DO_
}

void TActHolidaySignGetInfoReq::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:pb.TActHolidaySignGetInfoReq)
  // optional uint32 ActId = 1;
  if (has_actid()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->actid(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:pb.TActHolidaySignGetInfoReq)
}

::google::protobuf::uint8* TActHolidaySignGetInfoReq::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:pb.TActHolidaySignGetInfoReq)
  // optional uint32 ActId = 1;
  if (has_actid()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->actid(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:pb.TActHolidaySignGetInfoReq)
  return target;
}

int TActHolidaySignGetInfoReq::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional uint32 ActId = 1;
    if (has_actid()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->actid());
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

void TActHolidaySignGetInfoReq::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const TActHolidaySignGetInfoReq* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const TActHolidaySignGetInfoReq*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void TActHolidaySignGetInfoReq::MergeFrom(const TActHolidaySignGetInfoReq& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_actid()) {
      set_actid(from.actid());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void TActHolidaySignGetInfoReq::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void TActHolidaySignGetInfoReq::CopyFrom(const TActHolidaySignGetInfoReq& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool TActHolidaySignGetInfoReq::IsInitialized() const {

  return true;
}

void TActHolidaySignGetInfoReq::Swap(TActHolidaySignGetInfoReq* other) {
  if (other != this) {
    std::swap(actid_, other->actid_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata TActHolidaySignGetInfoReq::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = TActHolidaySignGetInfoReq_descriptor_;
  metadata.reflection = TActHolidaySignGetInfoReq_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int TActHolidaySignGetInfoRsp::kAccuDayNumFieldNumber;
const int TActHolidaySignGetInfoRsp::kArrRewardDayFieldNumber;
#endif  // !_MSC_VER

TActHolidaySignGetInfoRsp::TActHolidaySignGetInfoRsp()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:pb.TActHolidaySignGetInfoRsp)
}

void TActHolidaySignGetInfoRsp::InitAsDefaultInstance() {
}

TActHolidaySignGetInfoRsp::TActHolidaySignGetInfoRsp(const TActHolidaySignGetInfoRsp& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:pb.TActHolidaySignGetInfoRsp)
}

void TActHolidaySignGetInfoRsp::SharedCtor() {
  _cached_size_ = 0;
  accudaynum_ = 0u;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

TActHolidaySignGetInfoRsp::~TActHolidaySignGetInfoRsp() {
  // @@protoc_insertion_point(destructor:pb.TActHolidaySignGetInfoRsp)
  SharedDtor();
}

void TActHolidaySignGetInfoRsp::SharedDtor() {
  if (this != default_instance_) {
  }
}

void TActHolidaySignGetInfoRsp::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* TActHolidaySignGetInfoRsp::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return TActHolidaySignGetInfoRsp_descriptor_;
}

const TActHolidaySignGetInfoRsp& TActHolidaySignGetInfoRsp::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_net_2fActHolidaySign_2eproto();
  return *default_instance_;
}

TActHolidaySignGetInfoRsp* TActHolidaySignGetInfoRsp::default_instance_ = NULL;

TActHolidaySignGetInfoRsp* TActHolidaySignGetInfoRsp::New() const {
  return new TActHolidaySignGetInfoRsp;
}

void TActHolidaySignGetInfoRsp::Clear() {
  accudaynum_ = 0u;
  arrrewardday_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool TActHolidaySignGetInfoRsp::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:pb.TActHolidaySignGetInfoRsp)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional uint32 AccuDayNum = 1;
      case 1: {
        if (tag == 8) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &accudaynum_)));
          set_has_accudaynum();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(16)) goto parse_arrRewardDay;
        break;
      }

      // repeated uint32 arrRewardDay = 2;
      case 2: {
        if (tag == 16) {
         parse_arrRewardDay:
          DO_((::google::protobuf::internal::WireFormatLite::ReadRepeatedPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 1, 16, input, this->mutable_arrrewardday())));
        } else if (tag == 18) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPackedPrimitiveNoInline<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, this->mutable_arrrewardday())));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(16)) goto parse_arrRewardDay;
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
  // @@protoc_insertion_point(parse_success:pb.TActHolidaySignGetInfoRsp)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:pb.TActHolidaySignGetInfoRsp)
  return false;
#undef DO_
}

void TActHolidaySignGetInfoRsp::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:pb.TActHolidaySignGetInfoRsp)
  // optional uint32 AccuDayNum = 1;
  if (has_accudaynum()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->accudaynum(), output);
  }

  // repeated uint32 arrRewardDay = 2;
  for (int i = 0; i < this->arrrewardday_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(
      2, this->arrrewardday(i), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:pb.TActHolidaySignGetInfoRsp)
}

::google::protobuf::uint8* TActHolidaySignGetInfoRsp::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:pb.TActHolidaySignGetInfoRsp)
  // optional uint32 AccuDayNum = 1;
  if (has_accudaynum()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->accudaynum(), target);
  }

  // repeated uint32 arrRewardDay = 2;
  for (int i = 0; i < this->arrrewardday_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteUInt32ToArray(2, this->arrrewardday(i), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:pb.TActHolidaySignGetInfoRsp)
  return target;
}

int TActHolidaySignGetInfoRsp::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional uint32 AccuDayNum = 1;
    if (has_accudaynum()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->accudaynum());
    }

  }
  // repeated uint32 arrRewardDay = 2;
  {
    int data_size = 0;
    for (int i = 0; i < this->arrrewardday_size(); i++) {
      data_size += ::google::protobuf::internal::WireFormatLite::
        UInt32Size(this->arrrewardday(i));
    }
    total_size += 1 * this->arrrewardday_size() + data_size;
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

void TActHolidaySignGetInfoRsp::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const TActHolidaySignGetInfoRsp* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const TActHolidaySignGetInfoRsp*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void TActHolidaySignGetInfoRsp::MergeFrom(const TActHolidaySignGetInfoRsp& from) {
  GOOGLE_CHECK_NE(&from, this);
  arrrewardday_.MergeFrom(from.arrrewardday_);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_accudaynum()) {
      set_accudaynum(from.accudaynum());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void TActHolidaySignGetInfoRsp::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void TActHolidaySignGetInfoRsp::CopyFrom(const TActHolidaySignGetInfoRsp& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool TActHolidaySignGetInfoRsp::IsInitialized() const {

  return true;
}

void TActHolidaySignGetInfoRsp::Swap(TActHolidaySignGetInfoRsp* other) {
  if (other != this) {
    std::swap(accudaynum_, other->accudaynum_);
    arrrewardday_.Swap(&other->arrrewardday_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata TActHolidaySignGetInfoRsp::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = TActHolidaySignGetInfoRsp_descriptor_;
  metadata.reflection = TActHolidaySignGetInfoRsp_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int TActHolidaySignGetRewardReq::kActIdFieldNumber;
const int TActHolidaySignGetRewardReq::kDayFieldNumber;
#endif  // !_MSC_VER

TActHolidaySignGetRewardReq::TActHolidaySignGetRewardReq()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:pb.TActHolidaySignGetRewardReq)
}

void TActHolidaySignGetRewardReq::InitAsDefaultInstance() {
}

TActHolidaySignGetRewardReq::TActHolidaySignGetRewardReq(const TActHolidaySignGetRewardReq& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:pb.TActHolidaySignGetRewardReq)
}

void TActHolidaySignGetRewardReq::SharedCtor() {
  _cached_size_ = 0;
  actid_ = 0u;
  day_ = 0u;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

TActHolidaySignGetRewardReq::~TActHolidaySignGetRewardReq() {
  // @@protoc_insertion_point(destructor:pb.TActHolidaySignGetRewardReq)
  SharedDtor();
}

void TActHolidaySignGetRewardReq::SharedDtor() {
  if (this != default_instance_) {
  }
}

void TActHolidaySignGetRewardReq::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* TActHolidaySignGetRewardReq::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return TActHolidaySignGetRewardReq_descriptor_;
}

const TActHolidaySignGetRewardReq& TActHolidaySignGetRewardReq::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_net_2fActHolidaySign_2eproto();
  return *default_instance_;
}

TActHolidaySignGetRewardReq* TActHolidaySignGetRewardReq::default_instance_ = NULL;

TActHolidaySignGetRewardReq* TActHolidaySignGetRewardReq::New() const {
  return new TActHolidaySignGetRewardReq;
}

void TActHolidaySignGetRewardReq::Clear() {
#define OFFSET_OF_FIELD_(f) (reinterpret_cast<char*>(      \
  &reinterpret_cast<TActHolidaySignGetRewardReq*>(16)->f) - \
   reinterpret_cast<char*>(16))

#define ZR_(first, last) do {                              \
    size_t f = OFFSET_OF_FIELD_(first);                    \
    size_t n = OFFSET_OF_FIELD_(last) - f + sizeof(last);  \
    ::memset(&first, 0, n);                                \
  } while (0)

  ZR_(actid_, day_);

#undef OFFSET_OF_FIELD_
#undef ZR_

  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool TActHolidaySignGetRewardReq::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:pb.TActHolidaySignGetRewardReq)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional uint32 ActId = 1;
      case 1: {
        if (tag == 8) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &actid_)));
          set_has_actid();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(16)) goto parse_Day;
        break;
      }

      // optional uint32 Day = 2;
      case 2: {
        if (tag == 16) {
         parse_Day:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &day_)));
          set_has_day();
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
  // @@protoc_insertion_point(parse_success:pb.TActHolidaySignGetRewardReq)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:pb.TActHolidaySignGetRewardReq)
  return false;
#undef DO_
}

void TActHolidaySignGetRewardReq::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:pb.TActHolidaySignGetRewardReq)
  // optional uint32 ActId = 1;
  if (has_actid()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->actid(), output);
  }

  // optional uint32 Day = 2;
  if (has_day()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(2, this->day(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:pb.TActHolidaySignGetRewardReq)
}

::google::protobuf::uint8* TActHolidaySignGetRewardReq::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:pb.TActHolidaySignGetRewardReq)
  // optional uint32 ActId = 1;
  if (has_actid()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->actid(), target);
  }

  // optional uint32 Day = 2;
  if (has_day()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(2, this->day(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:pb.TActHolidaySignGetRewardReq)
  return target;
}

int TActHolidaySignGetRewardReq::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional uint32 ActId = 1;
    if (has_actid()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->actid());
    }

    // optional uint32 Day = 2;
    if (has_day()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->day());
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

void TActHolidaySignGetRewardReq::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const TActHolidaySignGetRewardReq* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const TActHolidaySignGetRewardReq*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void TActHolidaySignGetRewardReq::MergeFrom(const TActHolidaySignGetRewardReq& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_actid()) {
      set_actid(from.actid());
    }
    if (from.has_day()) {
      set_day(from.day());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void TActHolidaySignGetRewardReq::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void TActHolidaySignGetRewardReq::CopyFrom(const TActHolidaySignGetRewardReq& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool TActHolidaySignGetRewardReq::IsInitialized() const {

  return true;
}

void TActHolidaySignGetRewardReq::Swap(TActHolidaySignGetRewardReq* other) {
  if (other != this) {
    std::swap(actid_, other->actid_);
    std::swap(day_, other->day_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata TActHolidaySignGetRewardReq::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = TActHolidaySignGetRewardReq_descriptor_;
  metadata.reflection = TActHolidaySignGetRewardReq_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace pb

// @@protoc_insertion_point(global_scope)