// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: module/AdventureTerrainResGroupCfg.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "module/AdventureTerrainResGroupCfg.pb.h"

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

const ::google::protobuf::Descriptor* TerrainResConf_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  TerrainResConf_reflection_ = NULL;
const ::google::protobuf::Descriptor* TerrainResGroupConf_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  TerrainResGroupConf_reflection_ = NULL;
const ::google::protobuf::Descriptor* AdventureTerrainResGroupCfg_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  AdventureTerrainResGroupCfg_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_module_2fAdventureTerrainResGroupCfg_2eproto() {
  protobuf_AddDesc_module_2fAdventureTerrainResGroupCfg_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "module/AdventureTerrainResGroupCfg.proto");
  GOOGLE_CHECK(file != NULL);
  TerrainResConf_descriptor_ = file->message_type(0);
  static const int TerrainResConf_offsets_[3] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TerrainResConf, resid_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TerrainResConf, weight_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TerrainResConf, path_),
  };
  TerrainResConf_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      TerrainResConf_descriptor_,
      TerrainResConf::default_instance_,
      TerrainResConf_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TerrainResConf, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TerrainResConf, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(TerrainResConf));
  TerrainResGroupConf_descriptor_ = file->message_type(1);
  static const int TerrainResGroupConf_offsets_[4] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TerrainResGroupConf, terrainid_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TerrainResGroupConf, resgroupname_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TerrainResGroupConf, isobstacle_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TerrainResGroupConf, terrainresarr_),
  };
  TerrainResGroupConf_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      TerrainResGroupConf_descriptor_,
      TerrainResGroupConf::default_instance_,
      TerrainResGroupConf_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TerrainResGroupConf, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TerrainResGroupConf, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(TerrainResGroupConf));
  AdventureTerrainResGroupCfg_descriptor_ = file->message_type(2);
  static const int AdventureTerrainResGroupCfg_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AdventureTerrainResGroupCfg, id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AdventureTerrainResGroupCfg, terrainresgrouparr_),
  };
  AdventureTerrainResGroupCfg_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      AdventureTerrainResGroupCfg_descriptor_,
      AdventureTerrainResGroupCfg::default_instance_,
      AdventureTerrainResGroupCfg_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AdventureTerrainResGroupCfg, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AdventureTerrainResGroupCfg, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(AdventureTerrainResGroupCfg));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_module_2fAdventureTerrainResGroupCfg_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    TerrainResConf_descriptor_, &TerrainResConf::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    TerrainResGroupConf_descriptor_, &TerrainResGroupConf::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    AdventureTerrainResGroupCfg_descriptor_, &AdventureTerrainResGroupCfg::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_module_2fAdventureTerrainResGroupCfg_2eproto() {
  delete TerrainResConf::default_instance_;
  delete TerrainResConf_reflection_;
  delete TerrainResGroupConf::default_instance_;
  delete TerrainResGroupConf_reflection_;
  delete AdventureTerrainResGroupCfg::default_instance_;
  delete AdventureTerrainResGroupCfg_reflection_;
}

void protobuf_AddDesc_module_2fAdventureTerrainResGroupCfg_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n(module/AdventureTerrainResGroupCfg.pro"
    "to\022\002pb\"=\n\016TerrainResConf\022\r\n\005ResId\030\001 \001(\r\022"
    "\016\n\006Weight\030\002 \001(\005\022\014\n\004Path\030\003 \001(\t\"}\n\023Terrain"
    "ResGroupConf\022\021\n\tTerrainId\030\001 \001(\r\022\024\n\014ResGr"
    "oupName\030\002 \001(\t\022\022\n\nIsObstacle\030\003 \001(\010\022)\n\rTer"
    "rainResArr\030\004 \003(\0132\022.pb.TerrainResConf\"^\n\033"
    "AdventureTerrainResGroupCfg\022\n\n\002Id\030\001 \001(\005\022"
    "3\n\022TerrainResGroupArr\030\002 \003(\0132\027.pb.Terrain"
    "ResGroupConf", 332);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "module/AdventureTerrainResGroupCfg.proto", &protobuf_RegisterTypes);
  TerrainResConf::default_instance_ = new TerrainResConf();
  TerrainResGroupConf::default_instance_ = new TerrainResGroupConf();
  AdventureTerrainResGroupCfg::default_instance_ = new AdventureTerrainResGroupCfg();
  TerrainResConf::default_instance_->InitAsDefaultInstance();
  TerrainResGroupConf::default_instance_->InitAsDefaultInstance();
  AdventureTerrainResGroupCfg::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_module_2fAdventureTerrainResGroupCfg_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_module_2fAdventureTerrainResGroupCfg_2eproto {
  StaticDescriptorInitializer_module_2fAdventureTerrainResGroupCfg_2eproto() {
    protobuf_AddDesc_module_2fAdventureTerrainResGroupCfg_2eproto();
  }
} static_descriptor_initializer_module_2fAdventureTerrainResGroupCfg_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int TerrainResConf::kResIdFieldNumber;
const int TerrainResConf::kWeightFieldNumber;
const int TerrainResConf::kPathFieldNumber;
#endif  // !_MSC_VER

TerrainResConf::TerrainResConf()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:pb.TerrainResConf)
}

void TerrainResConf::InitAsDefaultInstance() {
}

TerrainResConf::TerrainResConf(const TerrainResConf& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:pb.TerrainResConf)
}

void TerrainResConf::SharedCtor() {
  ::google::protobuf::internal::GetEmptyString();
  _cached_size_ = 0;
  resid_ = 0u;
  weight_ = 0;
  path_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

TerrainResConf::~TerrainResConf() {
  // @@protoc_insertion_point(destructor:pb.TerrainResConf)
  SharedDtor();
}

void TerrainResConf::SharedDtor() {
  if (path_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete path_;
  }
  if (this != default_instance_) {
  }
}

void TerrainResConf::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* TerrainResConf::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return TerrainResConf_descriptor_;
}

const TerrainResConf& TerrainResConf::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_module_2fAdventureTerrainResGroupCfg_2eproto();
  return *default_instance_;
}

TerrainResConf* TerrainResConf::default_instance_ = NULL;

TerrainResConf* TerrainResConf::New() const {
  return new TerrainResConf;
}

void TerrainResConf::Clear() {
#define OFFSET_OF_FIELD_(f) (reinterpret_cast<char*>(      \
  &reinterpret_cast<TerrainResConf*>(16)->f) - \
   reinterpret_cast<char*>(16))

#define ZR_(first, last) do {                              \
    size_t f = OFFSET_OF_FIELD_(first);                    \
    size_t n = OFFSET_OF_FIELD_(last) - f + sizeof(last);  \
    ::memset(&first, 0, n);                                \
  } while (0)

  if (_has_bits_[0 / 32] & 7) {
    ZR_(resid_, weight_);
    if (has_path()) {
      if (path_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        path_->clear();
      }
    }
  }

#undef OFFSET_OF_FIELD_
#undef ZR_

  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool TerrainResConf::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:pb.TerrainResConf)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional uint32 ResId = 1;
      case 1: {
        if (tag == 8) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &resid_)));
          set_has_resid();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(16)) goto parse_Weight;
        break;
      }

      // optional int32 Weight = 2;
      case 2: {
        if (tag == 16) {
         parse_Weight:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &weight_)));
          set_has_weight();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(26)) goto parse_Path;
        break;
      }

      // optional string Path = 3;
      case 3: {
        if (tag == 26) {
         parse_Path:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_path()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->path().data(), this->path().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "path");
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
  // @@protoc_insertion_point(parse_success:pb.TerrainResConf)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:pb.TerrainResConf)
  return false;
#undef DO_
}

void TerrainResConf::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:pb.TerrainResConf)
  // optional uint32 ResId = 1;
  if (has_resid()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->resid(), output);
  }

  // optional int32 Weight = 2;
  if (has_weight()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(2, this->weight(), output);
  }

  // optional string Path = 3;
  if (has_path()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->path().data(), this->path().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "path");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      3, this->path(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:pb.TerrainResConf)
}

::google::protobuf::uint8* TerrainResConf::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:pb.TerrainResConf)
  // optional uint32 ResId = 1;
  if (has_resid()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->resid(), target);
  }

  // optional int32 Weight = 2;
  if (has_weight()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(2, this->weight(), target);
  }

  // optional string Path = 3;
  if (has_path()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->path().data(), this->path().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "path");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        3, this->path(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:pb.TerrainResConf)
  return target;
}

int TerrainResConf::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional uint32 ResId = 1;
    if (has_resid()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->resid());
    }

    // optional int32 Weight = 2;
    if (has_weight()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->weight());
    }

    // optional string Path = 3;
    if (has_path()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->path());
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

void TerrainResConf::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const TerrainResConf* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const TerrainResConf*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void TerrainResConf::MergeFrom(const TerrainResConf& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_resid()) {
      set_resid(from.resid());
    }
    if (from.has_weight()) {
      set_weight(from.weight());
    }
    if (from.has_path()) {
      set_path(from.path());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void TerrainResConf::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void TerrainResConf::CopyFrom(const TerrainResConf& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool TerrainResConf::IsInitialized() const {

  return true;
}

void TerrainResConf::Swap(TerrainResConf* other) {
  if (other != this) {
    std::swap(resid_, other->resid_);
    std::swap(weight_, other->weight_);
    std::swap(path_, other->path_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata TerrainResConf::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = TerrainResConf_descriptor_;
  metadata.reflection = TerrainResConf_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int TerrainResGroupConf::kTerrainIdFieldNumber;
const int TerrainResGroupConf::kResGroupNameFieldNumber;
const int TerrainResGroupConf::kIsObstacleFieldNumber;
const int TerrainResGroupConf::kTerrainResArrFieldNumber;
#endif  // !_MSC_VER

TerrainResGroupConf::TerrainResGroupConf()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:pb.TerrainResGroupConf)
}

void TerrainResGroupConf::InitAsDefaultInstance() {
}

TerrainResGroupConf::TerrainResGroupConf(const TerrainResGroupConf& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:pb.TerrainResGroupConf)
}

void TerrainResGroupConf::SharedCtor() {
  ::google::protobuf::internal::GetEmptyString();
  _cached_size_ = 0;
  terrainid_ = 0u;
  resgroupname_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  isobstacle_ = false;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

TerrainResGroupConf::~TerrainResGroupConf() {
  // @@protoc_insertion_point(destructor:pb.TerrainResGroupConf)
  SharedDtor();
}

void TerrainResGroupConf::SharedDtor() {
  if (resgroupname_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete resgroupname_;
  }
  if (this != default_instance_) {
  }
}

void TerrainResGroupConf::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* TerrainResGroupConf::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return TerrainResGroupConf_descriptor_;
}

const TerrainResGroupConf& TerrainResGroupConf::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_module_2fAdventureTerrainResGroupCfg_2eproto();
  return *default_instance_;
}

TerrainResGroupConf* TerrainResGroupConf::default_instance_ = NULL;

TerrainResGroupConf* TerrainResGroupConf::New() const {
  return new TerrainResGroupConf;
}

void TerrainResGroupConf::Clear() {
#define OFFSET_OF_FIELD_(f) (reinterpret_cast<char*>(      \
  &reinterpret_cast<TerrainResGroupConf*>(16)->f) - \
   reinterpret_cast<char*>(16))

#define ZR_(first, last) do {                              \
    size_t f = OFFSET_OF_FIELD_(first);                    \
    size_t n = OFFSET_OF_FIELD_(last) - f + sizeof(last);  \
    ::memset(&first, 0, n);                                \
  } while (0)

  if (_has_bits_[0 / 32] & 7) {
    ZR_(terrainid_, isobstacle_);
    if (has_resgroupname()) {
      if (resgroupname_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        resgroupname_->clear();
      }
    }
  }

#undef OFFSET_OF_FIELD_
#undef ZR_

  terrainresarr_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool TerrainResGroupConf::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:pb.TerrainResGroupConf)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional uint32 TerrainId = 1;
      case 1: {
        if (tag == 8) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &terrainid_)));
          set_has_terrainid();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(18)) goto parse_ResGroupName;
        break;
      }

      // optional string ResGroupName = 2;
      case 2: {
        if (tag == 18) {
         parse_ResGroupName:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_resgroupname()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->resgroupname().data(), this->resgroupname().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "resgroupname");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(24)) goto parse_IsObstacle;
        break;
      }

      // optional bool IsObstacle = 3;
      case 3: {
        if (tag == 24) {
         parse_IsObstacle:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &isobstacle_)));
          set_has_isobstacle();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(34)) goto parse_TerrainResArr;
        break;
      }

      // repeated .pb.TerrainResConf TerrainResArr = 4;
      case 4: {
        if (tag == 34) {
         parse_TerrainResArr:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_terrainresarr()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(34)) goto parse_TerrainResArr;
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
  // @@protoc_insertion_point(parse_success:pb.TerrainResGroupConf)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:pb.TerrainResGroupConf)
  return false;
#undef DO_
}

void TerrainResGroupConf::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:pb.TerrainResGroupConf)
  // optional uint32 TerrainId = 1;
  if (has_terrainid()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->terrainid(), output);
  }

  // optional string ResGroupName = 2;
  if (has_resgroupname()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->resgroupname().data(), this->resgroupname().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "resgroupname");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      2, this->resgroupname(), output);
  }

  // optional bool IsObstacle = 3;
  if (has_isobstacle()) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(3, this->isobstacle(), output);
  }

  // repeated .pb.TerrainResConf TerrainResArr = 4;
  for (int i = 0; i < this->terrainresarr_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      4, this->terrainresarr(i), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:pb.TerrainResGroupConf)
}

::google::protobuf::uint8* TerrainResGroupConf::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:pb.TerrainResGroupConf)
  // optional uint32 TerrainId = 1;
  if (has_terrainid()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->terrainid(), target);
  }

  // optional string ResGroupName = 2;
  if (has_resgroupname()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->resgroupname().data(), this->resgroupname().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "resgroupname");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        2, this->resgroupname(), target);
  }

  // optional bool IsObstacle = 3;
  if (has_isobstacle()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(3, this->isobstacle(), target);
  }

  // repeated .pb.TerrainResConf TerrainResArr = 4;
  for (int i = 0; i < this->terrainresarr_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        4, this->terrainresarr(i), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:pb.TerrainResGroupConf)
  return target;
}

int TerrainResGroupConf::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional uint32 TerrainId = 1;
    if (has_terrainid()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->terrainid());
    }

    // optional string ResGroupName = 2;
    if (has_resgroupname()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->resgroupname());
    }

    // optional bool IsObstacle = 3;
    if (has_isobstacle()) {
      total_size += 1 + 1;
    }

  }
  // repeated .pb.TerrainResConf TerrainResArr = 4;
  total_size += 1 * this->terrainresarr_size();
  for (int i = 0; i < this->terrainresarr_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->terrainresarr(i));
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

void TerrainResGroupConf::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const TerrainResGroupConf* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const TerrainResGroupConf*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void TerrainResGroupConf::MergeFrom(const TerrainResGroupConf& from) {
  GOOGLE_CHECK_NE(&from, this);
  terrainresarr_.MergeFrom(from.terrainresarr_);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_terrainid()) {
      set_terrainid(from.terrainid());
    }
    if (from.has_resgroupname()) {
      set_resgroupname(from.resgroupname());
    }
    if (from.has_isobstacle()) {
      set_isobstacle(from.isobstacle());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void TerrainResGroupConf::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void TerrainResGroupConf::CopyFrom(const TerrainResGroupConf& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool TerrainResGroupConf::IsInitialized() const {

  return true;
}

void TerrainResGroupConf::Swap(TerrainResGroupConf* other) {
  if (other != this) {
    std::swap(terrainid_, other->terrainid_);
    std::swap(resgroupname_, other->resgroupname_);
    std::swap(isobstacle_, other->isobstacle_);
    terrainresarr_.Swap(&other->terrainresarr_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata TerrainResGroupConf::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = TerrainResGroupConf_descriptor_;
  metadata.reflection = TerrainResGroupConf_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int AdventureTerrainResGroupCfg::kIdFieldNumber;
const int AdventureTerrainResGroupCfg::kTerrainResGroupArrFieldNumber;
#endif  // !_MSC_VER

AdventureTerrainResGroupCfg::AdventureTerrainResGroupCfg()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:pb.AdventureTerrainResGroupCfg)
}

void AdventureTerrainResGroupCfg::InitAsDefaultInstance() {
}

AdventureTerrainResGroupCfg::AdventureTerrainResGroupCfg(const AdventureTerrainResGroupCfg& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:pb.AdventureTerrainResGroupCfg)
}

void AdventureTerrainResGroupCfg::SharedCtor() {
  _cached_size_ = 0;
  id_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

AdventureTerrainResGroupCfg::~AdventureTerrainResGroupCfg() {
  // @@protoc_insertion_point(destructor:pb.AdventureTerrainResGroupCfg)
  SharedDtor();
}

void AdventureTerrainResGroupCfg::SharedDtor() {
  if (this != default_instance_) {
  }
}

void AdventureTerrainResGroupCfg::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* AdventureTerrainResGroupCfg::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return AdventureTerrainResGroupCfg_descriptor_;
}

const AdventureTerrainResGroupCfg& AdventureTerrainResGroupCfg::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_module_2fAdventureTerrainResGroupCfg_2eproto();
  return *default_instance_;
}

AdventureTerrainResGroupCfg* AdventureTerrainResGroupCfg::default_instance_ = NULL;

AdventureTerrainResGroupCfg* AdventureTerrainResGroupCfg::New() const {
  return new AdventureTerrainResGroupCfg;
}

void AdventureTerrainResGroupCfg::Clear() {
  id_ = 0;
  terrainresgrouparr_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool AdventureTerrainResGroupCfg::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:pb.AdventureTerrainResGroupCfg)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional int32 Id = 1;
      case 1: {
        if (tag == 8) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &id_)));
          set_has_id();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(18)) goto parse_TerrainResGroupArr;
        break;
      }

      // repeated .pb.TerrainResGroupConf TerrainResGroupArr = 2;
      case 2: {
        if (tag == 18) {
         parse_TerrainResGroupArr:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_terrainresgrouparr()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(18)) goto parse_TerrainResGroupArr;
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
  // @@protoc_insertion_point(parse_success:pb.AdventureTerrainResGroupCfg)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:pb.AdventureTerrainResGroupCfg)
  return false;
#undef DO_
}

void AdventureTerrainResGroupCfg::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:pb.AdventureTerrainResGroupCfg)
  // optional int32 Id = 1;
  if (has_id()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->id(), output);
  }

  // repeated .pb.TerrainResGroupConf TerrainResGroupArr = 2;
  for (int i = 0; i < this->terrainresgrouparr_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      2, this->terrainresgrouparr(i), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:pb.AdventureTerrainResGroupCfg)
}

::google::protobuf::uint8* AdventureTerrainResGroupCfg::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:pb.AdventureTerrainResGroupCfg)
  // optional int32 Id = 1;
  if (has_id()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, this->id(), target);
  }

  // repeated .pb.TerrainResGroupConf TerrainResGroupArr = 2;
  for (int i = 0; i < this->terrainresgrouparr_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        2, this->terrainresgrouparr(i), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:pb.AdventureTerrainResGroupCfg)
  return target;
}

int AdventureTerrainResGroupCfg::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional int32 Id = 1;
    if (has_id()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->id());
    }

  }
  // repeated .pb.TerrainResGroupConf TerrainResGroupArr = 2;
  total_size += 1 * this->terrainresgrouparr_size();
  for (int i = 0; i < this->terrainresgrouparr_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->terrainresgrouparr(i));
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

void AdventureTerrainResGroupCfg::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const AdventureTerrainResGroupCfg* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const AdventureTerrainResGroupCfg*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void AdventureTerrainResGroupCfg::MergeFrom(const AdventureTerrainResGroupCfg& from) {
  GOOGLE_CHECK_NE(&from, this);
  terrainresgrouparr_.MergeFrom(from.terrainresgrouparr_);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_id()) {
      set_id(from.id());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void AdventureTerrainResGroupCfg::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void AdventureTerrainResGroupCfg::CopyFrom(const AdventureTerrainResGroupCfg& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool AdventureTerrainResGroupCfg::IsInitialized() const {

  return true;
}

void AdventureTerrainResGroupCfg::Swap(AdventureTerrainResGroupCfg* other) {
  if (other != this) {
    std::swap(id_, other->id_);
    terrainresgrouparr_.Swap(&other->terrainresgrouparr_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata AdventureTerrainResGroupCfg::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = AdventureTerrainResGroupCfg_descriptor_;
  metadata.reflection = AdventureTerrainResGroupCfg_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace pb

// @@protoc_insertion_point(global_scope)
