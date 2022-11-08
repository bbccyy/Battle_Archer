// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: net/UgcUser.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "net/UgcUser.pb.h"

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

const ::google::protobuf::Descriptor* TUgcChangeUserSimpleInfoReq_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  TUgcChangeUserSimpleInfoReq_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_net_2fUgcUser_2eproto() {
  protobuf_AddDesc_net_2fUgcUser_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "net/UgcUser.proto");
  GOOGLE_CHECK(file != NULL);
  TUgcChangeUserSimpleInfoReq_descriptor_ = file->message_type(0);
  static const int TUgcChangeUserSimpleInfoReq_offsets_[4] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TUgcChangeUserSimpleInfoReq, uid_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TUgcChangeUserSimpleInfoReq, uname_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TUgcChangeUserSimpleInfoReq, imagetid_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TUgcChangeUserSimpleInfoReq, imageframetid_),
  };
  TUgcChangeUserSimpleInfoReq_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      TUgcChangeUserSimpleInfoReq_descriptor_,
      TUgcChangeUserSimpleInfoReq::default_instance_,
      TUgcChangeUserSimpleInfoReq_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TUgcChangeUserSimpleInfoReq, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TUgcChangeUserSimpleInfoReq, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(TUgcChangeUserSimpleInfoReq));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_net_2fUgcUser_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    TUgcChangeUserSimpleInfoReq_descriptor_, &TUgcChangeUserSimpleInfoReq::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_net_2fUgcUser_2eproto() {
  delete TUgcChangeUserSimpleInfoReq::default_instance_;
  delete TUgcChangeUserSimpleInfoReq_reflection_;
}

void protobuf_AddDesc_net_2fUgcUser_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\021net/UgcUser.proto\022\002pb\"b\n\033TUgcChangeUse"
    "rSimpleInfoReq\022\013\n\003Uid\030\001 \001(\004\022\r\n\005Uname\030\002 \001"
    "(\t\022\020\n\010ImageTid\030\003 \001(\r\022\025\n\rImageFrameTid\030\004 "
    "\001(\r", 123);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "net/UgcUser.proto", &protobuf_RegisterTypes);
  TUgcChangeUserSimpleInfoReq::default_instance_ = new TUgcChangeUserSimpleInfoReq();
  TUgcChangeUserSimpleInfoReq::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_net_2fUgcUser_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_net_2fUgcUser_2eproto {
  StaticDescriptorInitializer_net_2fUgcUser_2eproto() {
    protobuf_AddDesc_net_2fUgcUser_2eproto();
  }
} static_descriptor_initializer_net_2fUgcUser_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int TUgcChangeUserSimpleInfoReq::kUidFieldNumber;
const int TUgcChangeUserSimpleInfoReq::kUnameFieldNumber;
const int TUgcChangeUserSimpleInfoReq::kImageTidFieldNumber;
const int TUgcChangeUserSimpleInfoReq::kImageFrameTidFieldNumber;
#endif  // !_MSC_VER

TUgcChangeUserSimpleInfoReq::TUgcChangeUserSimpleInfoReq()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:pb.TUgcChangeUserSimpleInfoReq)
}

void TUgcChangeUserSimpleInfoReq::InitAsDefaultInstance() {
}

TUgcChangeUserSimpleInfoReq::TUgcChangeUserSimpleInfoReq(const TUgcChangeUserSimpleInfoReq& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:pb.TUgcChangeUserSimpleInfoReq)
}

void TUgcChangeUserSimpleInfoReq::SharedCtor() {
  ::google::protobuf::internal::GetEmptyString();
  _cached_size_ = 0;
  uid_ = GOOGLE_ULONGLONG(0);
  uname_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  imagetid_ = 0u;
  imageframetid_ = 0u;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

TUgcChangeUserSimpleInfoReq::~TUgcChangeUserSimpleInfoReq() {
  // @@protoc_insertion_point(destructor:pb.TUgcChangeUserSimpleInfoReq)
  SharedDtor();
}

void TUgcChangeUserSimpleInfoReq::SharedDtor() {
  if (uname_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete uname_;
  }
  if (this != default_instance_) {
  }
}

void TUgcChangeUserSimpleInfoReq::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* TUgcChangeUserSimpleInfoReq::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return TUgcChangeUserSimpleInfoReq_descriptor_;
}

const TUgcChangeUserSimpleInfoReq& TUgcChangeUserSimpleInfoReq::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_net_2fUgcUser_2eproto();
  return *default_instance_;
}

TUgcChangeUserSimpleInfoReq* TUgcChangeUserSimpleInfoReq::default_instance_ = NULL;

TUgcChangeUserSimpleInfoReq* TUgcChangeUserSimpleInfoReq::New() const {
  return new TUgcChangeUserSimpleInfoReq;
}

void TUgcChangeUserSimpleInfoReq::Clear() {
#define OFFSET_OF_FIELD_(f) (reinterpret_cast<char*>(      \
  &reinterpret_cast<TUgcChangeUserSimpleInfoReq*>(16)->f) - \
   reinterpret_cast<char*>(16))

#define ZR_(first, last) do {                              \
    size_t f = OFFSET_OF_FIELD_(first);                    \
    size_t n = OFFSET_OF_FIELD_(last) - f + sizeof(last);  \
    ::memset(&first, 0, n);                                \
  } while (0)

  if (_has_bits_[0 / 32] & 15) {
    ZR_(imagetid_, imageframetid_);
    uid_ = GOOGLE_ULONGLONG(0);
    if (has_uname()) {
      if (uname_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        uname_->clear();
      }
    }
  }

#undef OFFSET_OF_FIELD_
#undef ZR_

  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool TUgcChangeUserSimpleInfoReq::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:pb.TUgcChangeUserSimpleInfoReq)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional uint64 Uid = 1;
      case 1: {
        if (tag == 8) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint64, ::google::protobuf::internal::WireFormatLite::TYPE_UINT64>(
                 input, &uid_)));
          set_has_uid();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(18)) goto parse_Uname;
        break;
      }

      // optional string Uname = 2;
      case 2: {
        if (tag == 18) {
         parse_Uname:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_uname()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->uname().data(), this->uname().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "uname");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(24)) goto parse_ImageTid;
        break;
      }

      // optional uint32 ImageTid = 3;
      case 3: {
        if (tag == 24) {
         parse_ImageTid:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &imagetid_)));
          set_has_imagetid();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(32)) goto parse_ImageFrameTid;
        break;
      }

      // optional uint32 ImageFrameTid = 4;
      case 4: {
        if (tag == 32) {
         parse_ImageFrameTid:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &imageframetid_)));
          set_has_imageframetid();
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
  // @@protoc_insertion_point(parse_success:pb.TUgcChangeUserSimpleInfoReq)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:pb.TUgcChangeUserSimpleInfoReq)
  return false;
#undef DO_
}

void TUgcChangeUserSimpleInfoReq::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:pb.TUgcChangeUserSimpleInfoReq)
  // optional uint64 Uid = 1;
  if (has_uid()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt64(1, this->uid(), output);
  }

  // optional string Uname = 2;
  if (has_uname()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->uname().data(), this->uname().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "uname");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      2, this->uname(), output);
  }

  // optional uint32 ImageTid = 3;
  if (has_imagetid()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(3, this->imagetid(), output);
  }

  // optional uint32 ImageFrameTid = 4;
  if (has_imageframetid()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(4, this->imageframetid(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:pb.TUgcChangeUserSimpleInfoReq)
}

::google::protobuf::uint8* TUgcChangeUserSimpleInfoReq::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:pb.TUgcChangeUserSimpleInfoReq)
  // optional uint64 Uid = 1;
  if (has_uid()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt64ToArray(1, this->uid(), target);
  }

  // optional string Uname = 2;
  if (has_uname()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->uname().data(), this->uname().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "uname");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        2, this->uname(), target);
  }

  // optional uint32 ImageTid = 3;
  if (has_imagetid()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(3, this->imagetid(), target);
  }

  // optional uint32 ImageFrameTid = 4;
  if (has_imageframetid()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(4, this->imageframetid(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:pb.TUgcChangeUserSimpleInfoReq)
  return target;
}

int TUgcChangeUserSimpleInfoReq::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional uint64 Uid = 1;
    if (has_uid()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt64Size(
          this->uid());
    }

    // optional string Uname = 2;
    if (has_uname()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->uname());
    }

    // optional uint32 ImageTid = 3;
    if (has_imagetid()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->imagetid());
    }

    // optional uint32 ImageFrameTid = 4;
    if (has_imageframetid()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->imageframetid());
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

void TUgcChangeUserSimpleInfoReq::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const TUgcChangeUserSimpleInfoReq* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const TUgcChangeUserSimpleInfoReq*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void TUgcChangeUserSimpleInfoReq::MergeFrom(const TUgcChangeUserSimpleInfoReq& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_uid()) {
      set_uid(from.uid());
    }
    if (from.has_uname()) {
      set_uname(from.uname());
    }
    if (from.has_imagetid()) {
      set_imagetid(from.imagetid());
    }
    if (from.has_imageframetid()) {
      set_imageframetid(from.imageframetid());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void TUgcChangeUserSimpleInfoReq::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void TUgcChangeUserSimpleInfoReq::CopyFrom(const TUgcChangeUserSimpleInfoReq& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool TUgcChangeUserSimpleInfoReq::IsInitialized() const {

  return true;
}

void TUgcChangeUserSimpleInfoReq::Swap(TUgcChangeUserSimpleInfoReq* other) {
  if (other != this) {
    std::swap(uid_, other->uid_);
    std::swap(uname_, other->uname_);
    std::swap(imagetid_, other->imagetid_);
    std::swap(imageframetid_, other->imageframetid_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata TUgcChangeUserSimpleInfoReq::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = TUgcChangeUserSimpleInfoReq_descriptor_;
  metadata.reflection = TUgcChangeUserSimpleInfoReq_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace pb

// @@protoc_insertion_point(global_scope)
