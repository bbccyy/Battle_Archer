// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: net/SquadStats.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "net/SquadStats.pb.h"

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

const ::google::protobuf::Descriptor* TSquadStats_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  TSquadStats_reflection_ = NULL;
const ::google::protobuf::Descriptor* TSquadStatsGetSquadStatsReq_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  TSquadStatsGetSquadStatsReq_reflection_ = NULL;
const ::google::protobuf::Descriptor* TSquadStatsGetSquadStatsRsp_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  TSquadStatsGetSquadStatsRsp_reflection_ = NULL;
const ::google::protobuf::EnumDescriptor* ESquadSortType_descriptor_ = NULL;

}  // namespace


void protobuf_AssignDesc_net_2fSquadStats_2eproto() {
  protobuf_AddDesc_net_2fSquadStats_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "net/SquadStats.proto");
  GOOGLE_CHECK(file != NULL);
  TSquadStats_descriptor_ = file->message_type(0);
  static const int TSquadStats_offsets_[5] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TSquadStats, squad_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TSquadStats, totalnum_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TSquadStats, winnum_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TSquadStats, winpercentage_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TSquadStats, damageout_),
  };
  TSquadStats_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      TSquadStats_descriptor_,
      TSquadStats::default_instance_,
      TSquadStats_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TSquadStats, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TSquadStats, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(TSquadStats));
  TSquadStatsGetSquadStatsReq_descriptor_ = file->message_type(1);
  static const int TSquadStatsGetSquadStatsReq_offsets_[3] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TSquadStatsGetSquadStatsReq, htid_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TSquadStatsGetSquadStatsReq, starter_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TSquadStatsGetSquadStatsReq, sorttype_),
  };
  TSquadStatsGetSquadStatsReq_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      TSquadStatsGetSquadStatsReq_descriptor_,
      TSquadStatsGetSquadStatsReq::default_instance_,
      TSquadStatsGetSquadStatsReq_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TSquadStatsGetSquadStatsReq, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TSquadStatsGetSquadStatsReq, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(TSquadStatsGetSquadStatsReq));
  TSquadStatsGetSquadStatsRsp_descriptor_ = file->message_type(2);
  static const int TSquadStatsGetSquadStatsRsp_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TSquadStatsGetSquadStatsRsp, arraysquadstats_),
  };
  TSquadStatsGetSquadStatsRsp_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      TSquadStatsGetSquadStatsRsp_descriptor_,
      TSquadStatsGetSquadStatsRsp::default_instance_,
      TSquadStatsGetSquadStatsRsp_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TSquadStatsGetSquadStatsRsp, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(TSquadStatsGetSquadStatsRsp, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(TSquadStatsGetSquadStatsRsp));
  ESquadSortType_descriptor_ = file->enum_type(0);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_net_2fSquadStats_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    TSquadStats_descriptor_, &TSquadStats::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    TSquadStatsGetSquadStatsReq_descriptor_, &TSquadStatsGetSquadStatsReq::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    TSquadStatsGetSquadStatsRsp_descriptor_, &TSquadStatsGetSquadStatsRsp::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_net_2fSquadStats_2eproto() {
  delete TSquadStats::default_instance_;
  delete TSquadStats_reflection_;
  delete TSquadStatsGetSquadStatsReq::default_instance_;
  delete TSquadStatsGetSquadStatsReq_reflection_;
  delete TSquadStatsGetSquadStatsRsp::default_instance_;
  delete TSquadStatsGetSquadStatsRsp_reflection_;
}

void protobuf_AddDesc_net_2fSquadStats_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::pb::protobuf_AddDesc_net_2fBattleStarter_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\024net/SquadStats.proto\022\002pb\032\027net/BattleSt"
    "arter.proto\"h\n\013TSquadStats\022\r\n\005Squad\030\001 \001("
    "\t\022\020\n\010TotalNum\030\002 \001(\004\022\016\n\006WinNum\030\003 \001(\004\022\025\n\rW"
    "inPercentage\030\004 \001(\004\022\021\n\tDamageOut\030\005 \001(\004\"v\n"
    "\033TSquadStatsGetSquadStatsReq\022\014\n\004Htid\030\001 \001"
    "(\r\022#\n\007Starter\030\002 \001(\0162\022.pb.EBattleStarter\022"
    "$\n\010SortType\030\003 \001(\0162\022.pb.ESquadSortType\"G\n"
    "\033TSquadStatsGetSquadStatsRsp\022(\n\017ArraySqu"
    "adStats\030\001 \003(\0132\017.pb.TSquadStats*L\n\016ESquad"
    "SortType\022\014\n\010TotalNum\020\001\022\n\n\006WinNum\020\002\022\021\n\rWi"
    "nPercentage\020\003\022\r\n\tDamageOut\020\004", 428);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "net/SquadStats.proto", &protobuf_RegisterTypes);
  TSquadStats::default_instance_ = new TSquadStats();
  TSquadStatsGetSquadStatsReq::default_instance_ = new TSquadStatsGetSquadStatsReq();
  TSquadStatsGetSquadStatsRsp::default_instance_ = new TSquadStatsGetSquadStatsRsp();
  TSquadStats::default_instance_->InitAsDefaultInstance();
  TSquadStatsGetSquadStatsReq::default_instance_->InitAsDefaultInstance();
  TSquadStatsGetSquadStatsRsp::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_net_2fSquadStats_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_net_2fSquadStats_2eproto {
  StaticDescriptorInitializer_net_2fSquadStats_2eproto() {
    protobuf_AddDesc_net_2fSquadStats_2eproto();
  }
} static_descriptor_initializer_net_2fSquadStats_2eproto_;
const ::google::protobuf::EnumDescriptor* ESquadSortType_descriptor() {
  protobuf_AssignDescriptorsOnce();
  return ESquadSortType_descriptor_;
}
bool ESquadSortType_IsValid(int value) {
  switch(value) {
    case 1:
    case 2:
    case 3:
    case 4:
      return true;
    default:
      return false;
  }
}


// ===================================================================

#ifndef _MSC_VER
const int TSquadStats::kSquadFieldNumber;
const int TSquadStats::kTotalNumFieldNumber;
const int TSquadStats::kWinNumFieldNumber;
const int TSquadStats::kWinPercentageFieldNumber;
const int TSquadStats::kDamageOutFieldNumber;
#endif  // !_MSC_VER

TSquadStats::TSquadStats()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:pb.TSquadStats)
}

void TSquadStats::InitAsDefaultInstance() {
}

TSquadStats::TSquadStats(const TSquadStats& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:pb.TSquadStats)
}

void TSquadStats::SharedCtor() {
  ::google::protobuf::internal::GetEmptyString();
  _cached_size_ = 0;
  squad_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  totalnum_ = GOOGLE_ULONGLONG(0);
  winnum_ = GOOGLE_ULONGLONG(0);
  winpercentage_ = GOOGLE_ULONGLONG(0);
  damageout_ = GOOGLE_ULONGLONG(0);
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

TSquadStats::~TSquadStats() {
  // @@protoc_insertion_point(destructor:pb.TSquadStats)
  SharedDtor();
}

void TSquadStats::SharedDtor() {
  if (squad_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete squad_;
  }
  if (this != default_instance_) {
  }
}

void TSquadStats::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* TSquadStats::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return TSquadStats_descriptor_;
}

const TSquadStats& TSquadStats::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_net_2fSquadStats_2eproto();
  return *default_instance_;
}

TSquadStats* TSquadStats::default_instance_ = NULL;

TSquadStats* TSquadStats::New() const {
  return new TSquadStats;
}

void TSquadStats::Clear() {
#define OFFSET_OF_FIELD_(f) (reinterpret_cast<char*>(      \
  &reinterpret_cast<TSquadStats*>(16)->f) - \
   reinterpret_cast<char*>(16))

#define ZR_(first, last) do {                              \
    size_t f = OFFSET_OF_FIELD_(first);                    \
    size_t n = OFFSET_OF_FIELD_(last) - f + sizeof(last);  \
    ::memset(&first, 0, n);                                \
  } while (0)

  if (_has_bits_[0 / 32] & 31) {
    ZR_(totalnum_, damageout_);
    if (has_squad()) {
      if (squad_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        squad_->clear();
      }
    }
  }

#undef OFFSET_OF_FIELD_
#undef ZR_

  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool TSquadStats::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:pb.TSquadStats)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional string Squad = 1;
      case 1: {
        if (tag == 10) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_squad()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->squad().data(), this->squad().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "squad");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(16)) goto parse_TotalNum;
        break;
      }

      // optional uint64 TotalNum = 2;
      case 2: {
        if (tag == 16) {
         parse_TotalNum:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint64, ::google::protobuf::internal::WireFormatLite::TYPE_UINT64>(
                 input, &totalnum_)));
          set_has_totalnum();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(24)) goto parse_WinNum;
        break;
      }

      // optional uint64 WinNum = 3;
      case 3: {
        if (tag == 24) {
         parse_WinNum:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint64, ::google::protobuf::internal::WireFormatLite::TYPE_UINT64>(
                 input, &winnum_)));
          set_has_winnum();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(32)) goto parse_WinPercentage;
        break;
      }

      // optional uint64 WinPercentage = 4;
      case 4: {
        if (tag == 32) {
         parse_WinPercentage:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint64, ::google::protobuf::internal::WireFormatLite::TYPE_UINT64>(
                 input, &winpercentage_)));
          set_has_winpercentage();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(40)) goto parse_DamageOut;
        break;
      }

      // optional uint64 DamageOut = 5;
      case 5: {
        if (tag == 40) {
         parse_DamageOut:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint64, ::google::protobuf::internal::WireFormatLite::TYPE_UINT64>(
                 input, &damageout_)));
          set_has_damageout();
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
  // @@protoc_insertion_point(parse_success:pb.TSquadStats)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:pb.TSquadStats)
  return false;
#undef DO_
}

void TSquadStats::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:pb.TSquadStats)
  // optional string Squad = 1;
  if (has_squad()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->squad().data(), this->squad().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "squad");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      1, this->squad(), output);
  }

  // optional uint64 TotalNum = 2;
  if (has_totalnum()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt64(2, this->totalnum(), output);
  }

  // optional uint64 WinNum = 3;
  if (has_winnum()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt64(3, this->winnum(), output);
  }

  // optional uint64 WinPercentage = 4;
  if (has_winpercentage()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt64(4, this->winpercentage(), output);
  }

  // optional uint64 DamageOut = 5;
  if (has_damageout()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt64(5, this->damageout(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:pb.TSquadStats)
}

::google::protobuf::uint8* TSquadStats::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:pb.TSquadStats)
  // optional string Squad = 1;
  if (has_squad()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->squad().data(), this->squad().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "squad");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        1, this->squad(), target);
  }

  // optional uint64 TotalNum = 2;
  if (has_totalnum()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt64ToArray(2, this->totalnum(), target);
  }

  // optional uint64 WinNum = 3;
  if (has_winnum()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt64ToArray(3, this->winnum(), target);
  }

  // optional uint64 WinPercentage = 4;
  if (has_winpercentage()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt64ToArray(4, this->winpercentage(), target);
  }

  // optional uint64 DamageOut = 5;
  if (has_damageout()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt64ToArray(5, this->damageout(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:pb.TSquadStats)
  return target;
}

int TSquadStats::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional string Squad = 1;
    if (has_squad()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->squad());
    }

    // optional uint64 TotalNum = 2;
    if (has_totalnum()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt64Size(
          this->totalnum());
    }

    // optional uint64 WinNum = 3;
    if (has_winnum()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt64Size(
          this->winnum());
    }

    // optional uint64 WinPercentage = 4;
    if (has_winpercentage()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt64Size(
          this->winpercentage());
    }

    // optional uint64 DamageOut = 5;
    if (has_damageout()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt64Size(
          this->damageout());
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

void TSquadStats::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const TSquadStats* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const TSquadStats*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void TSquadStats::MergeFrom(const TSquadStats& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_squad()) {
      set_squad(from.squad());
    }
    if (from.has_totalnum()) {
      set_totalnum(from.totalnum());
    }
    if (from.has_winnum()) {
      set_winnum(from.winnum());
    }
    if (from.has_winpercentage()) {
      set_winpercentage(from.winpercentage());
    }
    if (from.has_damageout()) {
      set_damageout(from.damageout());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void TSquadStats::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void TSquadStats::CopyFrom(const TSquadStats& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool TSquadStats::IsInitialized() const {

  return true;
}

void TSquadStats::Swap(TSquadStats* other) {
  if (other != this) {
    std::swap(squad_, other->squad_);
    std::swap(totalnum_, other->totalnum_);
    std::swap(winnum_, other->winnum_);
    std::swap(winpercentage_, other->winpercentage_);
    std::swap(damageout_, other->damageout_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata TSquadStats::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = TSquadStats_descriptor_;
  metadata.reflection = TSquadStats_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int TSquadStatsGetSquadStatsReq::kHtidFieldNumber;
const int TSquadStatsGetSquadStatsReq::kStarterFieldNumber;
const int TSquadStatsGetSquadStatsReq::kSortTypeFieldNumber;
#endif  // !_MSC_VER

TSquadStatsGetSquadStatsReq::TSquadStatsGetSquadStatsReq()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:pb.TSquadStatsGetSquadStatsReq)
}

void TSquadStatsGetSquadStatsReq::InitAsDefaultInstance() {
}

TSquadStatsGetSquadStatsReq::TSquadStatsGetSquadStatsReq(const TSquadStatsGetSquadStatsReq& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:pb.TSquadStatsGetSquadStatsReq)
}

void TSquadStatsGetSquadStatsReq::SharedCtor() {
  _cached_size_ = 0;
  htid_ = 0u;
  starter_ = 0;
  sorttype_ = 1;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

TSquadStatsGetSquadStatsReq::~TSquadStatsGetSquadStatsReq() {
  // @@protoc_insertion_point(destructor:pb.TSquadStatsGetSquadStatsReq)
  SharedDtor();
}

void TSquadStatsGetSquadStatsReq::SharedDtor() {
  if (this != default_instance_) {
  }
}

void TSquadStatsGetSquadStatsReq::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* TSquadStatsGetSquadStatsReq::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return TSquadStatsGetSquadStatsReq_descriptor_;
}

const TSquadStatsGetSquadStatsReq& TSquadStatsGetSquadStatsReq::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_net_2fSquadStats_2eproto();
  return *default_instance_;
}

TSquadStatsGetSquadStatsReq* TSquadStatsGetSquadStatsReq::default_instance_ = NULL;

TSquadStatsGetSquadStatsReq* TSquadStatsGetSquadStatsReq::New() const {
  return new TSquadStatsGetSquadStatsReq;
}

void TSquadStatsGetSquadStatsReq::Clear() {
#define OFFSET_OF_FIELD_(f) (reinterpret_cast<char*>(      \
  &reinterpret_cast<TSquadStatsGetSquadStatsReq*>(16)->f) - \
   reinterpret_cast<char*>(16))

#define ZR_(first, last) do {                              \
    size_t f = OFFSET_OF_FIELD_(first);                    \
    size_t n = OFFSET_OF_FIELD_(last) - f + sizeof(last);  \
    ::memset(&first, 0, n);                                \
  } while (0)

  if (_has_bits_[0 / 32] & 7) {
    ZR_(htid_, starter_);
    sorttype_ = 1;
  }

#undef OFFSET_OF_FIELD_
#undef ZR_

  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool TSquadStatsGetSquadStatsReq::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:pb.TSquadStatsGetSquadStatsReq)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional uint32 Htid = 1;
      case 1: {
        if (tag == 8) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &htid_)));
          set_has_htid();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(16)) goto parse_Starter;
        break;
      }

      // optional .pb.EBattleStarter Starter = 2;
      case 2: {
        if (tag == 16) {
         parse_Starter:
          int value;
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          if (::pb::EBattleStarter_IsValid(value)) {
            set_starter(static_cast< ::pb::EBattleStarter >(value));
          } else {
            mutable_unknown_fields()->AddVarint(2, value);
          }
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(24)) goto parse_SortType;
        break;
      }

      // optional .pb.ESquadSortType SortType = 3;
      case 3: {
        if (tag == 24) {
         parse_SortType:
          int value;
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          if (::pb::ESquadSortType_IsValid(value)) {
            set_sorttype(static_cast< ::pb::ESquadSortType >(value));
          } else {
            mutable_unknown_fields()->AddVarint(3, value);
          }
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
  // @@protoc_insertion_point(parse_success:pb.TSquadStatsGetSquadStatsReq)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:pb.TSquadStatsGetSquadStatsReq)
  return false;
#undef DO_
}

void TSquadStatsGetSquadStatsReq::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:pb.TSquadStatsGetSquadStatsReq)
  // optional uint32 Htid = 1;
  if (has_htid()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->htid(), output);
  }

  // optional .pb.EBattleStarter Starter = 2;
  if (has_starter()) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      2, this->starter(), output);
  }

  // optional .pb.ESquadSortType SortType = 3;
  if (has_sorttype()) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      3, this->sorttype(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:pb.TSquadStatsGetSquadStatsReq)
}

::google::protobuf::uint8* TSquadStatsGetSquadStatsReq::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:pb.TSquadStatsGetSquadStatsReq)
  // optional uint32 Htid = 1;
  if (has_htid()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->htid(), target);
  }

  // optional .pb.EBattleStarter Starter = 2;
  if (has_starter()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
      2, this->starter(), target);
  }

  // optional .pb.ESquadSortType SortType = 3;
  if (has_sorttype()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
      3, this->sorttype(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:pb.TSquadStatsGetSquadStatsReq)
  return target;
}

int TSquadStatsGetSquadStatsReq::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional uint32 Htid = 1;
    if (has_htid()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->htid());
    }

    // optional .pb.EBattleStarter Starter = 2;
    if (has_starter()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::EnumSize(this->starter());
    }

    // optional .pb.ESquadSortType SortType = 3;
    if (has_sorttype()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::EnumSize(this->sorttype());
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

void TSquadStatsGetSquadStatsReq::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const TSquadStatsGetSquadStatsReq* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const TSquadStatsGetSquadStatsReq*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void TSquadStatsGetSquadStatsReq::MergeFrom(const TSquadStatsGetSquadStatsReq& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_htid()) {
      set_htid(from.htid());
    }
    if (from.has_starter()) {
      set_starter(from.starter());
    }
    if (from.has_sorttype()) {
      set_sorttype(from.sorttype());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void TSquadStatsGetSquadStatsReq::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void TSquadStatsGetSquadStatsReq::CopyFrom(const TSquadStatsGetSquadStatsReq& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool TSquadStatsGetSquadStatsReq::IsInitialized() const {

  return true;
}

void TSquadStatsGetSquadStatsReq::Swap(TSquadStatsGetSquadStatsReq* other) {
  if (other != this) {
    std::swap(htid_, other->htid_);
    std::swap(starter_, other->starter_);
    std::swap(sorttype_, other->sorttype_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata TSquadStatsGetSquadStatsReq::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = TSquadStatsGetSquadStatsReq_descriptor_;
  metadata.reflection = TSquadStatsGetSquadStatsReq_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int TSquadStatsGetSquadStatsRsp::kArraySquadStatsFieldNumber;
#endif  // !_MSC_VER

TSquadStatsGetSquadStatsRsp::TSquadStatsGetSquadStatsRsp()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:pb.TSquadStatsGetSquadStatsRsp)
}

void TSquadStatsGetSquadStatsRsp::InitAsDefaultInstance() {
}

TSquadStatsGetSquadStatsRsp::TSquadStatsGetSquadStatsRsp(const TSquadStatsGetSquadStatsRsp& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:pb.TSquadStatsGetSquadStatsRsp)
}

void TSquadStatsGetSquadStatsRsp::SharedCtor() {
  _cached_size_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

TSquadStatsGetSquadStatsRsp::~TSquadStatsGetSquadStatsRsp() {
  // @@protoc_insertion_point(destructor:pb.TSquadStatsGetSquadStatsRsp)
  SharedDtor();
}

void TSquadStatsGetSquadStatsRsp::SharedDtor() {
  if (this != default_instance_) {
  }
}

void TSquadStatsGetSquadStatsRsp::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* TSquadStatsGetSquadStatsRsp::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return TSquadStatsGetSquadStatsRsp_descriptor_;
}

const TSquadStatsGetSquadStatsRsp& TSquadStatsGetSquadStatsRsp::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_net_2fSquadStats_2eproto();
  return *default_instance_;
}

TSquadStatsGetSquadStatsRsp* TSquadStatsGetSquadStatsRsp::default_instance_ = NULL;

TSquadStatsGetSquadStatsRsp* TSquadStatsGetSquadStatsRsp::New() const {
  return new TSquadStatsGetSquadStatsRsp;
}

void TSquadStatsGetSquadStatsRsp::Clear() {
  arraysquadstats_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool TSquadStatsGetSquadStatsRsp::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:pb.TSquadStatsGetSquadStatsRsp)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated .pb.TSquadStats ArraySquadStats = 1;
      case 1: {
        if (tag == 10) {
         parse_ArraySquadStats:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_arraysquadstats()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(10)) goto parse_ArraySquadStats;
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
  // @@protoc_insertion_point(parse_success:pb.TSquadStatsGetSquadStatsRsp)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:pb.TSquadStatsGetSquadStatsRsp)
  return false;
#undef DO_
}

void TSquadStatsGetSquadStatsRsp::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:pb.TSquadStatsGetSquadStatsRsp)
  // repeated .pb.TSquadStats ArraySquadStats = 1;
  for (int i = 0; i < this->arraysquadstats_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->arraysquadstats(i), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:pb.TSquadStatsGetSquadStatsRsp)
}

::google::protobuf::uint8* TSquadStatsGetSquadStatsRsp::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:pb.TSquadStatsGetSquadStatsRsp)
  // repeated .pb.TSquadStats ArraySquadStats = 1;
  for (int i = 0; i < this->arraysquadstats_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        1, this->arraysquadstats(i), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:pb.TSquadStatsGetSquadStatsRsp)
  return target;
}

int TSquadStatsGetSquadStatsRsp::ByteSize() const {
  int total_size = 0;

  // repeated .pb.TSquadStats ArraySquadStats = 1;
  total_size += 1 * this->arraysquadstats_size();
  for (int i = 0; i < this->arraysquadstats_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->arraysquadstats(i));
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

void TSquadStatsGetSquadStatsRsp::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const TSquadStatsGetSquadStatsRsp* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const TSquadStatsGetSquadStatsRsp*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void TSquadStatsGetSquadStatsRsp::MergeFrom(const TSquadStatsGetSquadStatsRsp& from) {
  GOOGLE_CHECK_NE(&from, this);
  arraysquadstats_.MergeFrom(from.arraysquadstats_);
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void TSquadStatsGetSquadStatsRsp::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void TSquadStatsGetSquadStatsRsp::CopyFrom(const TSquadStatsGetSquadStatsRsp& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool TSquadStatsGetSquadStatsRsp::IsInitialized() const {

  return true;
}

void TSquadStatsGetSquadStatsRsp::Swap(TSquadStatsGetSquadStatsRsp* other) {
  if (other != this) {
    arraysquadstats_.Swap(&other->arraysquadstats_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata TSquadStatsGetSquadStatsRsp::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = TSquadStatsGetSquadStatsRsp_descriptor_;
  metadata.reflection = TSquadStatsGetSquadStatsRsp_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace pb

// @@protoc_insertion_point(global_scope)
