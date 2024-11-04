# node-word-detection
A very memory-efficient lightweight tool for forbidden word detection.

非常节省内存的轻量级快速违禁词、词典库 检测工具 、 50万个词大约需要300MB内存、被检测的文本100+字内结果在1毫秒左右。本项目没有提供词库请自己在别的项目下载。
# Install
`npm install node-word-detection`
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
console.log(check_word_replace.check_word("4s3单词1dac142test","***"));
// print { have: true, str: '4s3***1dac142***' }
```

# 说明
本项目使用了预构建(支持大部分Node版本最好使用node18以上)，不需要编译而是从github下载编译好的文件，如果你电脑上的网络安装的时候无法访问github则会退化成编译。请安装项目中devDependencies依赖，在windows上编译可能遇到的问题可以参考这个链接https://blog.csdn.net/jjocwc/article/details/134152602
