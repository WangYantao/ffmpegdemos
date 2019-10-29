package com.demo.ndkdemo;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.MotionEvent;
import android.widget.TextView;

import com.demo.oboelib.OboeKit;

public class MainActivity extends AppCompatActivity {
    OboeKit oboeKit;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        TextView txvOboe = findViewById(R.id.txvOboe);

        oboeKit = new OboeKit();
        oboeKit.startEngine();
    }

    @Override
    public boolean onTouchEvent(MotionEvent event) {
        oboeKit.touchEvent(event.getAction());
        return super.onTouchEvent(event);
    }

    @Override
    protected void onDestroy() {
        oboeKit.stopEngine();
        super.onDestroy();
    }
}
