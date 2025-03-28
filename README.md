# node-word-detection
A very memory-efficient lightweight tool for forbidden word detection.

非常节省内存的轻量级快速违禁词、词典库 检测工具 、近50万个单词只需要200多MB(数据来源于我自己生成的随机单词，可能不准确。本项目中的近8万个单词，在windows下运行只需要30MB左右)，被检测的文本100+字内结果在1毫秒内。本项目预设置的违禁词来源于网络搜集质量并不怎么好，推荐自己搜集一份。
# Install
`npm install node-word-detection`
# Example
```js
const {node_word_detection} = require("node-word-detection");
node_word_detection.add_word("单词1");
node_word_detection.add_word("word2");
// node_word_detection.remove_word("test"); 
node_word_detection.add_word("test");
console.log(node_word_detection.check_word("0h781单词123njn"));
// print true
console.log(node_word_detection.check_word("4s3142"));
// print false
console.log(node_word_detection.check_word_replace("4s3单词1dac142test","***"));
// print { have: true, str: '4s3***1dac142***' }
console.log(node_word_detection.find_word("4s3单词1dac142test",-1));
// print [ '单词1', 'test' ]
console.log(node_word_detection.find_word_replace("4s3单词1dac142test",-1,"***")); 
// print { word_list: [ '单词1', 'test' ], str: '4s3***dac142***' }

console.log(node_word_detection.get_word_num()) 
// print total sys word num

// node_word_detection.use_sys_sensitive_word(); // 将会使用系统的违禁词 大约8万个中文单词
```

# 说明
本项目使用了预构建(支持大部分Node版本最好使用node18以上)，不需要编译而是从github下载编译好的文件，如果你电脑上的网络安装的时候无法访问github则会退化成编译。请安装项目中devDependencies依赖，在windows上编译可能遇到的问题可以参考这个链接https://blog.csdn.net/jjocwc/article/details/134152602
