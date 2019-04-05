package BayesClassify;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

public class loadData {
    public ArrayList<String> InitData() {
        ArrayList<String> DataSet = new ArrayList<>();
        DataSet.add("玩游戏吧");
        DataSet.add("玩吧");
        DataSet.add("我要学习");
        DataSet.add("学习使我快乐");
        DataSet.add("学习万岁");
        DataSet.add("我要玩耍");
        return DataSet;
    }

    public ArrayList<Integer> InitLab() {
        ArrayList<Integer> Labels = new ArrayList<>();
        Labels.add(1);
        Labels.add(1);
        Labels.add(0);
        Labels.add(0);
        Labels.add(0);
        Labels.add(1);
        return Labels;
    }

    /**
     * 生成不重复词组
     */
    public ArrayList<Character> createVocabList(ArrayList<String> DataSet) {
        Set<Character> vocaset = new HashSet<>();
        for (int i = 0; i < DataSet.size(); i++) {
            for (int j = 0; j < DataSet.get(i).length(); j++) {
                vocaset.add(DataSet.get(i).charAt(j));
            }
        }
        List list = new ArrayList(vocaset);
        return (ArrayList<Character>) list;
    }

    /**
     * 标记词组中是否存在新输入的word
     */
    public ArrayList<Integer> SetWord(ArrayList<Character> listvocaset, String newInput) {
        ArrayList<Integer> newVocaset = new ArrayList<>();
        for (int i = 0; i < listvocaset.size(); i++) {
            newVocaset.add(0);
        }
        for (int i = 0; i < newInput.length(); i++) {
            if (listvocaset.indexOf(newInput.charAt(i)) >= 0)
                newVocaset.set(listvocaset.indexOf(newInput.charAt(i)), 1);
        }
        return newVocaset;
    }

    /**
     * 标记训练数据
     */
    public ArrayList<ArrayList<Integer>> TagTrainData(ArrayList<Character> listvocaset, ArrayList<String> DataSet) {
        ArrayList<ArrayList<Integer>> newListVocaset = new ArrayList<>();
        for (int i = 0; i < DataSet.size(); i++) {
            ArrayList<Integer> temp = new ArrayList<>();
            temp = SetWord(listvocaset, DataSet.get(i));
            newListVocaset.add(temp);
        }
        return newListVocaset;
    }
}
