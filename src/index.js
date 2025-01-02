const path = require('path');
// const node_word_detection = require("../build/Release/node-word-detection.node")
var binding = require('node-gyp-build')(path.join(__dirname,'..')) // 自动找到 .node



module.exports.node_word_detection = binding;
