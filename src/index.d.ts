export interface node_word_detection {

    /**
     *  add a word : exp test abc
     *  添加一个单词 比如 傻逼 这样的敏感词
     * @param word
     */
    add_word: (word: string) => void;

    /**
     * checks whether a word in a sentence functions
     * 检查这个句子中是否有 某个单词 敏感词
     * @param text
     */
    check_word: (text: string) => boolean;
}

export declare const node_word_detection: node_word_detection;