#include <chrono>
#include <string>
#include <vector>
#include <spdlog/spdlog.h>
#include <glaze/glaze.hpp>
#include <benchmark/cppbenchmark.h>
#include "proto/message.pb.h"

constexpr auto LIMIT = 100000;

struct blob
{
    std::vector<uint32_t> ids;
    std::vector<double> values;
};

static auto fill_in_raw()
{
    blob bg;
    bg.ids.reserve(LIMIT);
    bg.values.reserve(LIMIT);
    for(auto i = 0; i < LIMIT; ++i)
    {
        bg.ids.push_back(i);
        bg.values.push_back(i + 3.5 / (i+1));
    }
    return bg;
}

static auto fill_in_protobuf()
{
    glaze_vs_protobuf::SensorsSnapshot bp;
    for(auto i = 0; i < LIMIT; ++i)
    {
        bp.add_ids(i);
        bp.add_values(i + 3.5 / (i+1));
    }
    return bp;
}

auto gz_obj = fill_in_raw();
std::string gz_beve_serialized;
std::string gz_json_serialized;

auto protobuf_obj = fill_in_protobuf();
std::vector<char> grpc_serialized(protobuf_obj.ByteSizeLong(), 0);

BENCHMARK("glaze_beve_serialize")
{
    gz_beve_serialized = glz::write_binary(gz_obj).value();
}

BENCHMARK("glaze_beve_deserialize")
{
    auto obj = glz::read_binary<blob>(gz_beve_serialized);
}

BENCHMARK("glaze_json_serialize")
{
    gz_json_serialized = glz::write_json(gz_obj).value();
}

BENCHMARK("glaze_json_deserialize")
{
    auto obj = glz::read_json<blob>(gz_json_serialized);
}

BENCHMARK("protobuf_serialize")
{
    size_t size = protobuf_obj.ByteSizeLong();
	protobuf_obj.SerializeToArray(grpc_serialized.data(), size);
}

BENCHMARK("protobuf_deserialize")
{
    glaze_vs_protobuf::SensorsSnapshot obj;
    obj.ParseFromArray((void*)grpc_serialized.data(), grpc_serialized.size());
}

BENCHMARK_MAIN();
