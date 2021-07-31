load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

cc_library(
    name = "matrix-lib",
    srcs = ["matrix.cc"],
    hdrs = ["matrix.h"],
)

cc_binary(
    name = "matrix-service",
    srcs = ["main.cc"],
    deps = [
        ":matrix-lib",
    ],
)