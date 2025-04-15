const path = require('path');
// const node_word_detection = require("../build/Release/node-word-detection.node")
// var binding = require('node-gyp-build')(path.join(__dirname,'..')) // 自动找到 .node
const node_word_detection = require("../build/Release/node-word-detection.node")
module.exports.node_word_detection = node_word_detection;

function use_sys_sensitive_word (){
    const fs = require("fs");
    const path = require("path");
    const data = fs.readFileSync(path.join(__dirname,"pre-sensitive-word","sensitive-zh.txt"), 'utf8');
    for (const word of data.split("\n")){
        this.add_word(word);
    }
    console.log('sys word reading is completed. ')
}

use_sys_sensitive_word.bind(node_word_detection.NodeWordDetection.prototype );
node_word_detection.NodeWordDetection.prototype.use_sys_sensitive_word = use_sys_sensitive_word;
module.exports.node_word_detection = new node_word_detection.NodeWordDetection();
module.exports.get_instance = function() { return new node_word_detection.NodeWordDetection() ;}
