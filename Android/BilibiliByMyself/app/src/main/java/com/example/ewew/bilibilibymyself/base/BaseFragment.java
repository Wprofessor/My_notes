package com.example.ewew.bilibilibymyself.base;

import android.os.Bundle;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.LinearLayout;

import com.example.ewew.bilibilibymyself.bean.Animal;

import java.util.ArrayList;
import java.util.List;

public abstract class BaseFragment extends Fragment {
    public abstract int setIdResource();

    private View view;
    protected List<Animal> animals = new ArrayList<>();

    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        View view = inflater.inflate(setIdResource(), container, false);
        this.view = view;
        loaddata();
        initview();
        return view;
    }

    public abstract void loaddata();

    public View getView() {
        return view;
    }
    public abstract void  initview();
}
