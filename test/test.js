let node_word_detection= require("../build/Debug/node-word-detection");
node_word_detection = new node_word_detection.NodeWordDetection();
// console.log(node_word_detection);
// return;
require("../build/Debug/node-word-detection");
node_word_detection.add_word("单词1");
node_word_detection.add_word("word2");
node_word_detection.add_word("六");
// node_word_detection.remove_word("六");
node_word_detection.add_word("test");
console.log(node_word_detection.get_word_num())
// node_word_detection.remove_word("test");
console.log(node_word_detection.check_word("0h781单词123njn"));
// print true
console.log(node_word_detection.check_word("4s3142"));
// print false
console.log(node_word_detection.check_word_replace("4s3单词1dac142test","***"));
// print { have: true, str: '4s3***1dac142***' }
console.log(node_word_detection.find_word("4s3单词1dac142test",-1));
// print [ '单词1', 'test' ]
console.log(node_word_detection.find_word_replace("六4s3单词1dac142test",-1,"***")); // 性能不怎么好
// print { word_list: [ '单词1', 'test' ], str: '4s3***dac142***' }
// console.log(node_word_detection.get_word_num())
const { Worker } = require('worker_threads');

// 创建一个新的 Worker 线程，指定子线程文件
const worker = new Worker('./worker.js');