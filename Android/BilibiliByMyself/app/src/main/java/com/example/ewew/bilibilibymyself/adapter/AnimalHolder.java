package com.example.ewew.bilibilibymyself.adapter;

import android.support.annotation.NonNull;
import android.support.v7.widget.RecyclerView;
import android.view.View;
import android.widget.ImageView;
import android.widget.TextView;

import com.example.ewew.bilibilibymyself.R;
import com.example.ewew.bilibilibymyself.bean.Animal;

public class AnimalHolder extends RecyclerView.ViewHolder {
    private ImageView imageView;
    private TextView textView;
    public AnimalHolder(@NonNull View itemView) {
        super(itemView);
        imageView = itemView.findViewById(R.id.image_view);
        textView = itemView.findViewById(R.id.text_view);
    }
    public void  bindView(Animal animal){
        imageView.setImageResource(animal.getImage());
        textView.setText(animal.getTitle());
    }
}
