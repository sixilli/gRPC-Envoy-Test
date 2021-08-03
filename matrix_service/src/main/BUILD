load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")
package(default_visibility = ["//visibility:public"])

proto_library(
    name = "schema_grpc",
    srcs = [
        "schema.proto",
    ],
)

load("@rules_proto_grpc//cpp:defs.bzl", "cpp_grpc_library")
cpp_grpc_library(
    name = "schema_grpc_library",
    protos = [":schema_grpc"],
)

cc_library(
    name = "matrix-lib",
    hdrs = ["matrix.h"],
)

cc_binary(
    name = "matrix-service",
    srcs = ["main.cc"],
    deps = [
        ":matrix-lib",
        ":schema_grpc_library",
        "@com_github_grpc_grpc//:grpc++" 
    ],
)