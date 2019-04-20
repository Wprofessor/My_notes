package TireTree;

import java.util.*;

public class Tiretree {
    //各个节点的子树数目即字符串中的字符出现的最多种类
    private final int SIZE = 8;
    private TrieNode root;

    /**
     * 初始化数据
     */
    public ArrayList<String> InitDataSet() {
        ArrayList<String>dataSet = new ArrayList<>();
        dataSet.add("王佳豪");
        dataSet.add("王浩");
        dataSet.add("王晋浩");
        dataSet.add("李凯凯");
        dataSet.add("李三");

        return dataSet;
    }

    /**
     * 给数据去重
     */
    public ArrayList<Character> createVocabList(ArrayList<String> dataSet) {
        Set<Character> v = new HashSet<>();
        for (int i = 0; i < dataSet.size(); i++) {
            for (int j = 0; j < dataSet.get(i).length(); j++) {
                v.add(dataSet.get(i).charAt(j));
            }
        }
        List list = new ArrayList(v);
        return  (ArrayList<Character>) list;
    }

    /**
     * 给不重复词表形成一一对应关系
     */
    public Map<Character,Integer> Initmap(ArrayList<Character> vocaset) {
        Map<Character,Integer> trans = new HashMap<>();
        for (int i = 0; i < vocaset.size(); i++) {
            trans.put(vocaset.get(i), i + 1);
        }
        return trans;
    }

    public Tiretree() {
        this.root = new TrieNode();
        for (int i = 0; i < 9; i++) {
            this.root.children[i] = null;
        }
    }


    /**
     * 字典树节点类，为私有内部类
     */
    private class TrieNode {

        // 所有的儿子节点或者一级子节点
        private TrieNode[] children;
        // 有多少字符串经过或到达这个节点,即节点字符出现的次数
        private int count;
        // 是否有结束节点
        private boolean isStr;
        // 节点的值
        private String word;

        /**
         * 初始化节点类
         */
        public TrieNode() {
            this.children = new TrieNode[9];
            this.count = 0;
            this.isStr = false;
        }
    }

    /**
     * 插入方法，插入字符串
     */
    public void tireInsert(Map<Character,Integer> trans,ArrayList<Character> vocaset,String InputWord) {
        TrieNode node = this.root;
        int i = 0;
        int id;
        while (i < InputWord.length() && trans.get(InputWord.substring(i, i + 1).charAt(0)) != null) {
            id = trans.get(InputWord.substring(i, i + 1).charAt(0));
            if (node.children[id] == null) {
                node.children[id] = new TrieNode();
                for (int j = 0; j < vocaset.size(); j++) {
                    node.children[id].children[j] = null;
                }
            }
            node = node.children[id];
            node.count++;
            i++;
        }
        node.isStr = true;
        node.word = InputWord;
    }

    /**
     * 根据单词前缀查找前缀所在的节点位置
     */
    public TrieNode TireSearch(Map<Character,Integer> trans,String NewWord) {
        TrieNode node = this.root;
        int i = 0;
        while (i < NewWord.length() && trans.get(NewWord.substring(i, i + 1).charAt(0)) != null) {
            int id = trans.get(NewWord.substring(i, i + 1).charAt(0));
            if (node.children[id] != null) {
                node = node.children[id];
                i++;
            } else
                return null;
        }
        return node;
    }

    /**
     * BFS遍历打印出满足前缀的图书信息
     */
    public void PrintTire(Map<Character,Integer> trans,ArrayList<Character> vocaset,String front) {
        int count = 1;
        TrieNode node = this.TireSearch(trans,front);
        if (node == null)
            System.out.println("未匹配到您需要的信息，请重新输入");
        else {
            TrieNode que[] = new TrieNode[100];
            int left = 0, right = 0;
            que[right++] = node;
            while (left < right) {
                TrieNode p = que[left++];
                if (p.count != 0 && p.isStr) {
                    System.out.println(p.word);
                }
                for (int j = 0; j < vocaset.size(); j++) {
                    if (p.children[j] != null) {
                        que[right++] = p.children[j];
                    }
                }
            }
        }
    }
}
