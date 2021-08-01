load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

cc_library(
    name = "matrix-lib",
    hdrs = ["matrix.h"],
)

cc_binary(
    name = "matrix-service",
    srcs = ["main.cc"],
    deps = [
        ":matrix-lib",
    ],
)