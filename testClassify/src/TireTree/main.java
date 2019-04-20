package TireTree;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

public class main {
    public static void main(String[] args) {
        ArrayList<Character> vocaset = new ArrayList<>();
        ArrayList<String> dataSet = new ArrayList<>();
        Map<Character,Integer> trans = new HashMap<>();
        Tiretree tiretree = new Tiretree();
        dataSet = tiretree.InitDataSet();
        vocaset = tiretree.createVocabList(dataSet);
        trans = tiretree.Initmap(vocaset);
        tiretree.tireInsert(trans,vocaset,"王佳豪");
        tiretree.tireInsert(trans,vocaset,"王浩");
        tiretree.tireInsert(trans,vocaset,"王晋浩");
        tiretree.tireInsert(trans,vocaset,"李凯凯");
        tiretree.tireInsert(trans,vocaset,"李三");
        tiretree.PrintTire(trans,vocaset,"王");
    }
}
