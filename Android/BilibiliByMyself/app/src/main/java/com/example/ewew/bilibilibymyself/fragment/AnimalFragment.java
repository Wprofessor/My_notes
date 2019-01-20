package com.example.ewew.bilibilibymyself.fragment;

import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;

import com.example.ewew.bilibilibymyself.R;
import com.example.ewew.bilibilibymyself.adapter.AnimalAdapter;
import com.example.ewew.bilibilibymyself.base.BaseFragment;
import com.example.ewew.bilibilibymyself.bean.Animal;

public class AnimalFragment extends BaseFragment {

    private RecyclerView recyclerView;
    private AnimalAdapter adapter;

    @Override
    public int setIdResource() {
        return R.layout.animal_fragment;
    }

    @Override
    public void loaddata() {
        for (int i = 0; i < 10; i++) {
            Animal animal = new Animal(R.drawable.ic_rabbit,"我是一只兔子");
            animals.add(animal);
        }
    }

    @Override
    public void initview() {
        recyclerView = getView().findViewById(R.id.animal_recyler_view);
        adapter = new AnimalAdapter(animals,getContext());
        recyclerView.setLayoutManager(new LinearLayoutManager(getContext()));
        recyclerView.setAdapter(adapter);
    }
}

