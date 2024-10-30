{
  "targets": [
    {
     "target_name": "word-detection",
     "sources": ["src/c/main.cc","src/c/sensitive_struct.cpp","src/c/sensitive_struct.h","src/hash/hash_util.cpp","src/hash/hash_util.h"],
     'includes': [
            './common.gypi'
          ]
    },
  ]
}
