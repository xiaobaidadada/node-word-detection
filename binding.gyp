{
  "targets": [
    {
     "target_name": "node-word-detection",
     "sources": [
     "src/c/main.cc",
     "src/c/sensitive_struct.cpp",
     "src/c/sensitive_struct.h",
     "src/hash/hash_util.cpp",
     "src/hash/hash_util.h",
     "src/value/string_util.cpp",
     "src/value/string_util.h"],
     'includes': [
            './common.gypi'
          ]
    },
  ]
}
