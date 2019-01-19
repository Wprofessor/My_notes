package com.example.ewew.firstclass;

import android.annotation.SuppressLint;
import android.content.Intent;
import android.os.Build;
import android.support.annotation.RequiresApi;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;

import static com.example.ewew.firstclass.R.color.black;

public class MainActivity extends AppCompatActivity {
    private Button button_1;
    private Button button_2;
    private ImageView imageView;
    private TextView textView;
    private Button jump_button;
    //    private Bundle button;
//    private final String TAG = "MainActivity";
//    private TextView textView;
    private int clickCount = 0;

    //   @SuppressLint("WrongViewCast")
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
//        findViewById(R.id.text_view);
//        findViewById(R.id.button).setOnClickListener(new View.OnClickListener() {
//
//            @RequiresApi(api = Build.VERSION_CODES.M)
//            @SuppressLint("ResourceAsColor")
//            @Override
//            public void onClick(View view) {
//
//            }
//        });
        button_1 = findViewById(R.id.button_1);
        button_2 = findViewById(R.id.button_2);
        imageView = findViewById(R.id.image_view);
        textView = findViewById(R.id.test_view);
        button_1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                clickCount++;
                if (clickCount <= 2) {
                    changUi();
                }
            }
        });
        button_2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                clickCount = 0;
                changUi();
            }
        });
        jump_button = findViewById(R.id.jump_button);
        jump_button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(MainActivity.this,BilibiliActivity.class);
                startActivity(intent);
            }
        });
    }

    private void changUi(){
        int image = ConstantUtils.images[clickCount];
        String title = ConstantUtils.title[clickCount];
        imageView.setImageResource(image);
        textView.setText(title);
    }
}
