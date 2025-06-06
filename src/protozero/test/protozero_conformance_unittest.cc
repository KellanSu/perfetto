/*
 * Copyright (C) 2017 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <limits>
#include <memory>
#include <vector>

#include "perfetto/protozero/message_handle.h"
#include "perfetto/protozero/packed_repeated_fields.h"
#include "perfetto/protozero/scattered_heap_buffer.h"
#include "test/gtest_and_gmock.h"

// Autogenerated headers in out/*/gen/
#include "src/protozero/test/example_proto/extensions.pb.h"
#include "src/protozero/test/example_proto/extensions.pbzero.h"
#include "src/protozero/test/example_proto/library.pbzero.h"
#include "src/protozero/test/example_proto/other_package/test_messages.pbzero.h"
#include "src/protozero/test/example_proto/subpackage/test_messages.pbzero.h"
#include "src/protozero/test/example_proto/test_messages.pb.h"
#include "src/protozero/test/example_proto/test_messages.pbzero.h"

// Generated by the protozero plugin.
namespace pbtest = protozero::test::protos::pbzero;
namespace pbtest_subpackage = protozero::test::protos::subpackage::pbzero;
namespace pbtest_otherpackage = other_package::pbzero;

// Generated by the official protobuf compiler.
namespace pbgold = protozero::test::protos;
namespace pbgold_subpackage = protozero::test::protos::subpackage;
namespace pbgold_other_package = other_package;

namespace protozero {
namespace {

constexpr size_t kChunkSize = 42;

TEST(ProtoZeroConformanceTest, SimpleFieldsNoNesting) {
  HeapBuffered<pbtest::EveryField> msg{kChunkSize, kChunkSize};

  msg->set_field_int32(-1);
  msg->set_field_int64(-333123456789ll);
  msg->set_field_uint32(600);
  msg->set_field_uint64(333123456789ll);
  msg->set_field_sint32(-5);
  msg->set_field_sint64(-9000);
  msg->set_field_fixed32(12345);
  msg->set_field_fixed64(444123450000ll);
  msg->set_field_sfixed32(-69999);
  msg->set_field_sfixed64(-200);
  msg->set_field_float(3.14f);
  msg->set_field_double(0.5555);
  msg->set_field_bool(true);
  msg->set_small_enum(pbtest::SmallEnum::TO_BE);
  msg->set_signed_enum(pbtest::SignedEnum::NEGATIVE);
  msg->set_big_enum(pbtest::BigEnum::BEGIN);
  msg->set_very_negative_enum(pbtest::VeryNegativeEnum::VAL);
  msg->set_field_string("FizzBuzz");
  msg->set_field_bytes(reinterpret_cast<const uint8_t*>("\x11\x00\xBE\xEF"), 4);
  msg->add_repeated_int32(1);
  msg->add_repeated_int32(-1);
  msg->add_repeated_int32(100);
  msg->add_repeated_int32(2000000);

  std::string serialized = msg.SerializeAsString();
  pbgold::EveryField gold_msg;
  gold_msg.ParseFromString(serialized);

  EXPECT_EQ(-1, gold_msg.field_int32());
  EXPECT_EQ(-333123456789ll, gold_msg.field_int64());
  EXPECT_EQ(600u, gold_msg.field_uint32());
  EXPECT_EQ(333123456789ull, gold_msg.field_uint64());
  EXPECT_EQ(-5, gold_msg.field_sint32());
  EXPECT_EQ(-9000, gold_msg.field_sint64());
  EXPECT_EQ(12345u, gold_msg.field_fixed32());
  EXPECT_EQ(444123450000ull, gold_msg.field_fixed64());
  EXPECT_EQ(-69999, gold_msg.field_sfixed32());
  EXPECT_EQ(-200, gold_msg.field_sfixed64());
  EXPECT_FLOAT_EQ(3.14f, gold_msg.field_float());
  EXPECT_DOUBLE_EQ(0.5555, gold_msg.field_double());
  EXPECT_EQ(true, gold_msg.field_bool());
  EXPECT_EQ(pbgold::SmallEnum::TO_BE, gold_msg.small_enum());
  EXPECT_EQ(pbgold::SignedEnum::NEGATIVE, gold_msg.signed_enum());
  EXPECT_EQ(pbgold::BigEnum::BEGIN, gold_msg.big_enum());
  EXPECT_EQ(pbgold::VeryNegativeEnum::VAL, gold_msg.very_negative_enum());
  EXPECT_EQ("FizzBuzz", gold_msg.field_string());
  EXPECT_EQ(std::string("\x11\x00\xBE\xEF", 4), gold_msg.field_bytes());
  EXPECT_EQ(4, gold_msg.repeated_int32_size());
  EXPECT_EQ(1, gold_msg.repeated_int32(0));
  EXPECT_EQ(-1, gold_msg.repeated_int32(1));
  EXPECT_EQ(100, gold_msg.repeated_int32(2));
  EXPECT_EQ(2000000, gold_msg.repeated_int32(3));
  EXPECT_EQ(serialized.size(), static_cast<size_t>(gold_msg.ByteSizeLong()));
}

TEST(ProtoZeroConformanceTest, NestedMessages) {
  HeapBuffered<pbtest::NestedA> msg_a{kChunkSize, kChunkSize};

  pbtest::NestedA::NestedB* msg_b = msg_a->add_repeated_a();
  pbtest::NestedA::NestedB::NestedC* msg_c = msg_b->set_value_b();
  msg_c->set_value_c(321);
  msg_b = msg_a->add_repeated_a();
  msg_c = msg_a->set_super_nested();
  msg_c->set_value_c(1000);

  std::string serialized = msg_a.SerializeAsString();
  EXPECT_EQ(serialized.size(), 14u);

  pbgold::NestedA gold_msg_a;
  gold_msg_a.ParseFromString(serialized);
  EXPECT_EQ(2, gold_msg_a.repeated_a_size());
  EXPECT_EQ(321, gold_msg_a.repeated_a(0).value_b().value_c());
  EXPECT_FALSE(gold_msg_a.repeated_a(1).has_value_b());
  EXPECT_EQ(1000, gold_msg_a.super_nested().value_c());
}

TEST(ProtoZeroConformanceTest, Extensions) {
  HeapBuffered<pbtest::BrowserExtension> msg_a{kChunkSize, kChunkSize};

  msg_a->set_base_int(4);

  pbtest::SystemA* msg_b = msg_a->set_extension_a();
  msg_b->set_int_a(3);
  msg_b->set_string_a("string a");

  pbtest::SystemB* msg_c = msg_a->set_extension_b();
  msg_c->set_int_b(10);
  msg_c->set_string_b("string b");

  msg_a->set_base_string("base string");

  std::string serialized = msg_a.SerializeAsString();
  pbgold::RealFakeEvent gold_msg_a;
  gold_msg_a.ParseFromString(serialized);

  EXPECT_EQ(gold_msg_a.base_int(), 4u);
  EXPECT_EQ(gold_msg_a.base_string(), "base string");

  pbgold::SystemA gold_msg_b =
      gold_msg_a.GetExtension(pbgold::BrowserExtension::extension_a);
  EXPECT_EQ(gold_msg_b.int_a(), 3u);
  EXPECT_EQ(gold_msg_b.string_a(), "string a");

  pbgold::SystemB gold_msg_c =
      gold_msg_a.GetExtension(pbgold::BrowserExtension::extension_b);
  EXPECT_EQ(gold_msg_c.int_b(), 10u);
  EXPECT_EQ(gold_msg_c.string_b(), "string b");
}

TEST(ProtoZeroConformanceTest, Import) {
  // Test the includes for indirect public import: library.pbzero.h ->
  // library_internals/galaxies.pbzero.h -> upper_import.pbzero.h .
  EXPECT_LE(0u, sizeof(pbtest::TrickyPublicImport));
}

TEST(ProtoZeroConformanceTest, FieldNumbers) {
  EXPECT_EQ(1, pbtest::CamelCaseFields::kFooBarBazFieldNumber);
  EXPECT_EQ(2, pbtest::CamelCaseFields::kBarBazFieldNumber);
  EXPECT_EQ(3, pbtest::CamelCaseFields::kMooMooFieldNumber);
  EXPECT_EQ(4, pbtest::CamelCaseFields::kURLEncoderFieldNumber);
  EXPECT_EQ(5, pbtest::CamelCaseFields::kXMapFieldNumber);
  EXPECT_EQ(6, pbtest::CamelCaseFields::kUrLENcoDerFieldNumber);
  EXPECT_EQ(7, pbtest::CamelCaseFields::kBigBangFieldNumber);
  EXPECT_EQ(8, pbtest::CamelCaseFields::kU2FieldNumber);
  EXPECT_EQ(9, pbtest::CamelCaseFields::kBangBigFieldNumber);
}

TEST(ProtoZeroConformanceTest, PackedRepeatedVarint) {
  int values[] = {42, 255, -1};

  HeapBuffered<pbtest::PackedRepeatedFields> msg{kChunkSize, kChunkSize};
  PackedVarInt buf;
  for (auto v : values)
    buf.Append(v);
  msg->set_field_int32(buf);
  std::string serialized = msg.SerializeAsString();

  // Serialized as a length-delimited field with a payload of
  // concatenated varints. So the size should be:
  // varint(42) -> 1 byte
  // varint(255) -> 2 bytes
  // varint(-1) -> 10 bytes
  // varint(payload length) -> 1 byte
  // field type & id(1) -> 1 byte
  // total: 6 bytes
  EXPECT_EQ(15u, serialized.size());
  EXPECT_EQ(proto_utils::MakeTagLengthDelimited(
                pbtest::PackedRepeatedFields::kFieldInt32FieldNumber),
            static_cast<uint32_t>(serialized[0]));

  // Correctly parsed by the protobuf library.
  pbgold::PackedRepeatedFields parsed_gold_msg;
  parsed_gold_msg.ParseFromString(serialized);
  ASSERT_THAT(parsed_gold_msg.field_int32(), testing::ElementsAreArray(values));

  // Encoded identically by the protobuf library.
  pbgold::PackedRepeatedFields gold_msg;
  for (auto v : values)
    gold_msg.add_field_int32(v);
  ASSERT_EQ(gold_msg.SerializeAsString(), serialized);
}

TEST(ProtoZeroConformanceTest, PackedRepeatedFixed32) {
  uint32_t values[] = {1, 2, 4, 8};

  HeapBuffered<pbtest::PackedRepeatedFields> msg{kChunkSize, kChunkSize};
  PackedFixedSizeInt<uint32_t> buf;
  for (auto v : values)
    buf.Append(v);
  msg->set_field_fixed32(buf);
  std::string serialized = msg.SerializeAsString();

  // 4x4 bytes payload + 1 byte length + 1 byte tag & field
  EXPECT_EQ(18u, serialized.size());
  EXPECT_EQ(proto_utils::MakeTagLengthDelimited(
                pbtest::PackedRepeatedFields::kFieldFixed32FieldNumber),
            static_cast<uint32_t>(serialized[0]));

  // Correctly parsed by the protobuf library.
  pbgold::PackedRepeatedFields parsed_gold_msg;
  parsed_gold_msg.ParseFromString(serialized);
  ASSERT_THAT(parsed_gold_msg.field_fixed32(),
              testing::ElementsAreArray(values));

  // Encoded identically by the protobuf library.
  pbgold::PackedRepeatedFields gold_msg;
  for (auto v : values)
    gold_msg.add_field_fixed32(v);
  ASSERT_EQ(gold_msg.SerializeAsString(), serialized);
}

TEST(ProtoZeroConformanceTest, PackedRepeatedFixed64) {
  int64_t values[] = {1, -2, 4, -8};

  HeapBuffered<pbtest::PackedRepeatedFields> msg{kChunkSize, kChunkSize};
  PackedFixedSizeInt<int64_t> buf;
  for (auto v : values)
    buf.Append(v);
  msg->set_field_sfixed64(buf);
  std::string serialized = msg.SerializeAsString();

  // 4x8 bytes payload + 1 byte length + 1 byte tag & field
  EXPECT_EQ(34u, serialized.size());
  EXPECT_EQ(proto_utils::MakeTagLengthDelimited(
                pbtest::PackedRepeatedFields::kFieldSfixed64FieldNumber),
            static_cast<uint32_t>(serialized[0]));

  // Correctly parsed by the protobuf library.
  pbgold::PackedRepeatedFields parsed_gold_msg;
  parsed_gold_msg.ParseFromString(serialized);
  ASSERT_THAT(parsed_gold_msg.field_sfixed64(),
              testing::ElementsAreArray(values));

  // Encoded identically by the protobuf library.
  pbgold::PackedRepeatedFields gold_msg;
  for (auto v : values)
    gold_msg.add_field_sfixed64(v);
  ASSERT_EQ(gold_msg.SerializeAsString(), serialized);
}

TEST(ProtoZeroConformanceTest, EmptyPackedRepeatedField) {
  HeapBuffered<pbtest::PackedRepeatedFields> msg;
  PackedVarInt buf;
  msg->set_field_int32(buf);
  std::string serialized = msg.SerializeAsString();

  // Encoded as 2 bytes: tag/field, and a length of zero.
  EXPECT_EQ(2u, serialized.size());
  EXPECT_EQ(proto_utils::MakeTagLengthDelimited(
                pbtest::PackedRepeatedFields::kFieldInt32FieldNumber),
            static_cast<uint32_t>(serialized[0]));
  EXPECT_EQ(0, serialized[1]);

  // Correctly parsed by the protobuf library.
  pbgold::PackedRepeatedFields parsed_gold_msg;
  parsed_gold_msg.ParseFromString(serialized);
  EXPECT_EQ(0, parsed_gold_msg.field_int32_size());
}

// Tests that the stack -> heap expansion dosn't lose data.
TEST(ProtoZeroConformanceTest, PackedRepeatedResize) {
  const int kNumValues = 32768;
  const int64_t kMultiplier = 10000000;
  HeapBuffered<pbtest::PackedRepeatedFields> msg{kChunkSize, kChunkSize};
  PackedFixedSizeInt<int64_t> buf;
  for (int i = 0; i < kNumValues; i++)
    buf.Append(i * kMultiplier);
  msg->set_field_sfixed64(buf);
  std::string serialized = msg.SerializeAsString();

  // Correctly parsed by the protobuf library.
  pbgold::PackedRepeatedFields parsed_gold_msg;
  parsed_gold_msg.ParseFromString(serialized);
  ASSERT_EQ(parsed_gold_msg.field_sfixed64().size(), kNumValues);
  for (int i = 0; i < kNumValues; i++) {
    ASSERT_EQ(parsed_gold_msg.field_sfixed64(i), i * kMultiplier);
  }
}

TEST(ProtoZeroConformanceTest, EnumToString) {
  EXPECT_STREQ(protozero::test::protos::pbzero::SmallEnum_Name(
                   protozero::test::protos::pbzero::SmallEnum::TO_BE),
               "TO_BE");
  EXPECT_STREQ(protozero::test::protos::pbzero::EveryField::NestedEnum_Name(
                   protozero::test::protos::pbzero::EveryField::PING),
               "PING");
}

TEST(ProtoZeroConformanceTest, DifferentPackages) {
  HeapBuffered<pbtest::DifferentPackages> msg{kChunkSize, kChunkSize};

  // Populate fields defined in "protozero.test.protos.subpackage"
  pbtest_subpackage::Message* msgSubpackage = msg->set_subpackage_message();
  msgSubpackage->set_field_int32(1);
  msgSubpackage->set_field_enum(pbtest_subpackage::Enum::A);
  msgSubpackage->set_field_nested_enum(
      pbtest_subpackage::Message::NestedEnum::C);
  msg->set_subpackage_nested_message()->set_field_int32(2);
  msg->set_subpackage_enum(pbtest_subpackage::Enum::B);
  msg->set_subpackage_nested_enum(pbtest_subpackage::Message_NestedEnum::D);

  // Populate fields defined in "other_package"
  pbtest_otherpackage::Message* msgOtherPackage =
      msg->set_otherpackage_message();
  msgOtherPackage->set_field_int32(11);
  msgOtherPackage->set_field_enum(pbtest_otherpackage::Enum::A);
  msgOtherPackage->set_field_nested_enum(
      pbtest_otherpackage::Message::NestedEnum::C);
  msg->set_otherpackage_nested_message()->set_field_int32(12);
  msg->set_otherpackage_enum(pbtest_otherpackage::Enum::B);
  msg->set_otherpackage_nested_enum(pbtest_otherpackage::Message_NestedEnum::D);

  // Deserialize into golden proto
  std::string serialized = msg.SerializeAsString();
  pbgold::DifferentPackages gold_msg;
  gold_msg.ParseFromString(serialized);
  EXPECT_EQ(serialized.size(), static_cast<size_t>(gold_msg.ByteSizeLong()));

  // Check fields defined in "protozero.test.protos.subpackage"
  EXPECT_EQ(1, gold_msg.subpackage_message().field_int32());
  EXPECT_EQ(pbgold_subpackage::Enum::A,
            gold_msg.subpackage_message().field_enum());
  EXPECT_EQ(pbgold_subpackage::Message_NestedEnum_C,
            gold_msg.subpackage_message().field_nested_enum());
  EXPECT_EQ(2, gold_msg.subpackage_nested_message().field_int32());
  EXPECT_EQ(pbgold_subpackage::Enum::B, gold_msg.subpackage_enum());
  EXPECT_EQ(pbgold_subpackage::Message_NestedEnum_D,
            gold_msg.subpackage_nested_enum());

  // Check fields defined in "other_package"
  EXPECT_EQ(11, gold_msg.otherpackage_message().field_int32());
  EXPECT_EQ(pbgold_other_package::Enum::A,
            gold_msg.otherpackage_message().field_enum());
  EXPECT_EQ(pbgold_other_package::Message_NestedEnum_C,
            gold_msg.otherpackage_message().field_nested_enum());
  EXPECT_EQ(12, gold_msg.otherpackage_nested_message().field_int32());
  EXPECT_EQ(pbgold_other_package::Enum::B, gold_msg.otherpackage_enum());
  EXPECT_EQ(pbgold_other_package::Message_NestedEnum_D,
            gold_msg.otherpackage_nested_enum());
}

}  // namespace
}  // namespace protozero
