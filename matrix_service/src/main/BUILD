load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

package(default_visibility = ["//visibility:public"])

load("@rules_proto//proto:defs.bzl", "proto_library")
load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_proto_library")
load("@com_github_grpc_grpc//bazel:cc_grpc_library.bzl", "cc_grpc_library")

# The following three rules demonstrate the usage of the cc_grpc_library rule in
# in a mode compatible with the native proto_library and cc_proto_library rules.
proto_library(
    name = "schema_proto",
    srcs = ["schema.proto"],
)

cc_proto_library(
    name = "matrix_service_cc_proto",
    deps = [":schema_proto"],
)

cc_grpc_library(
    name = "matrix_service_cc_grpc",
    srcs = [":schema_proto"],
    grpc_only = True,
    deps = [":matrix_service_cc_proto"],
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
        ":matrix_service_cc_grpc",
        # http_archive made this label available for binding
        "@com_github_grpc_grpc//:grpc++",
    ],
)