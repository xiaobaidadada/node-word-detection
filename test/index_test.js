
function abc(){
    const {node_word_detection} = require("../src/index");
    node_word_detection.use_sys_sensitive_word();
    console.log(node_word_detection.get_word_num())
    console.log(node_word_detection.find_word("傻逼123",-1));
    console.log(node_word_detection.check_word("傻逼吧"))
}
abc()