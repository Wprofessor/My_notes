package TireTree;

import com.sun.xml.internal.ws.util.StringUtils;

public class Trie {
    //各个节点的子树数目即字符串中的字符出现的最多种类
    private final int SIZE = 26;
    //除根节点外其他所有子节点的数目
    private int numNode;
    //树的深度即最长字符串的长度
    private int depth;
    //字典树的根
    private TrieNode root;

    /**
     * 初始化字典树
     */
    public Trie() {
        this.numNode=0;
        this.depth=0;
        this.root = new TrieNode();
    }

    /**
     * 字典树节点类，为私有内部类
     */
    private class TrieNode {

        // 所有的儿子节点或者一级子节点
        private TrieNode[] son;
        // 有多少字符串经过或到达这个节点,即节点字符出现的次数
        private int numPass;
        // 有多少字符串通过这个节点并到此结束的数量
        private int numEnd;
        // 是否有结束节点
        private boolean isEnd;
        // 节点的值
        private char value;

        /**
         * 初始化节点类
         */
        public TrieNode() {
            this.numPass=0;
            this.numEnd=0;
            this.son = new TrieNode[SIZE];
            this.isEnd = false;
        }
    }

//    /**
//     * 对操作的字符串进行一个非法的判断，是否为字母构成的字符串
//     */
//    private boolean isStrOfLetter(String str){
//        //null或者空白字符串，则插入失败
//        if (StringUtils.isBlank(str)){
//            return false;
//        }
//        //如果字符串中有非字母字符，则插入失败
//        if(!CharMatcher.JAVA_LETTER.matchesAllOf(str)){
//            return false;
//        }
//        return true;
//    }


    /**
     * 插入方法，插入字符串，不区分大小写
     */
    public boolean insertStr(String str) {
        //插入的字符为非法字符，则插入失败
//        if(!isStrOfLetter(str)){
//            return false;
//        }
        //插入字符串
        str=str.toLowerCase();//不区分大小写，转为小写
        char[] letters = str.toCharArray();//转成字符数组
        TrieNode node=this.root;//先从父节点开始
        for (char c:letters) {
            int pos = c - 'a';//得到应存son[]中的索引
            if (node.son[pos] == null) {//此字符不存在
                node.son[pos] = new TrieNode();
                node.son[pos].value = c;
                node.son[pos].numPass=1;
                this.numNode++;
            } else {//此字符已经存入
                node.son[pos].numPass++;
            }
            node = node.son[pos];//继续为下一下字符做准备
        }
        node.isEnd = true;//标记：有字符串到了此节点已结束
        node.numEnd++;//这个字符串重复次数
        if(letters.length>this.depth){//记录树的深度
            this.depth=letters.length;
        }

        return true;//插入成功
    }


}
