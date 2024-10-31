# node-word-detection
A very memory-efficient lightweight tool for forbidden word detection.
非常节省内存的轻量级违禁词检测工具
# Example
```js
const {node_word_detection} = require("node-word-detection");
node_word_detection.add_word("单词1");
node_word_detection.add_word("word2");
node_word_detection.add_word("test");
console.log(node_word_detection.check_word("0h781单词123njn"));
// print true
console.log(node_word_detection.check_word("4s3142"));
// print false
```

# 说明
本项目使用c，由于只使用了链表作为hash冲突，添加单词的时候比较慢，如果单词量很多，内存节省会非常多，查询速度上比起其它的项目在50万个单词的测试速度下会比js写的速度快个几毫秒。
