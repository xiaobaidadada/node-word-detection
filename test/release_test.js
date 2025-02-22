let node_word_detection= require("../build/Release/node-word-detection");
node_word_detection = new node_word_detection.NodeWordDetection();
function use_sys_sensitive_word (){
    const fs = require("fs");
    const path = require("path");
    const data = fs.readFileSync(path.join(__dirname,"..","src","pre-sensitive-word","sensitive-zh.txt"), 'utf8');
    for (const word of data.split("\n")){
        this.add_word(word);
    }
    console.log('sys word reading is completed. ')
}
use_sys_sensitive_word.bind(node_word_detection);
node_word_detection.use_sys_sensitive_word = use_sys_sensitive_word;

node_word_detection.use_sys_sensitive_word();
console.log(node_word_detection.check_word("傻逼吧"))
// node_word_detection.add_word("123");
node_word_detection.add_word("123");
node_word_detection.add_word("单词1");
// node_word_detection.remove_word("123");
console.log(node_word_detection.get_word_num())
console.log(node_word_detection.find_word("傻逼123",-1));
console.log(node_word_detection.find_word("六四天安门事件21312",-1))
const now = Date.now();
for (let i = 0 ;i<10000;i++) {
    // node_word_detection.find_word("傻逼123",-1)
    // node_word_detection.find_word_replace("4s3单词1dac142test",-1,"***")
    node_word_detection.check_word("傻逼吧432423re4r434r4f34f4f54f45fdjdhsdhsidhsuifyudsyf7dstf7sd6f7sd56f5s67d5s6d5s765f6sd5f76s5d76s5d76576sa5d67as5d76ad5as76d5a")
}
console.log(`时间:${((Date.now() - now)/1000).toFixed(2)}s`);
setInterval(()=>{
    console.log(node_word_detection.get_word_num())
},2000)